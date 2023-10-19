/*
 * Copyright (C) by Daniel Molkentin <danimo@owncloud.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
 * for more details.
 */

#include "themesettings.h"
#include "ui_themesettings.h"

#if defined(BUILD_UPDATER)
#include "updater/updater.h"
#include "updater/ocupdater.h"
#ifdef Q_OS_MAC
// FIXME We should unify those, but Sparkle does everything behind the scene transparently
#include "updater/sparkleupdater.h"
#endif
#endif

#include <QFileDialog>
#include <QMessageBox>
#include <QNetworkProxy>
#include <QDir>
#include <QScopedValueRollback>
#include <QMessageBox>

#include <private/qzipwriter_p.h>

#define QTLEGACY (QT_VERSION < QT_VERSION_CHECK(5,9,0))

#if !(QTLEGACY)
#include <QOperatingSystemVersion>
#endif

namespace {
struct ZipEntry {
    QString localFilename;
    QString zipFilename;
};
}

namespace OCC {

ThemeSettings::ThemeSettings(QWidget *parent)
    : QWidget(parent)
    , _ui(new Ui::ThemeSettings)
{
    _ui->setupUi(this);


    // Rename 'Explorer' appropriately on non-Windows
#ifdef Q_OS_MAC
    QString txt = _ui->showInExplorerNavigationPaneCheckBox->text();
    txt.replace(QString::fromLatin1("Explorer"), QString::fromLatin1("Finder"));
    _ui->showInExplorerNavigationPaneCheckBox->setText(txt);
#endif

    // Hide on non-Windows, or WindowsVersion < 10.
    // The condition should match the default value of ConfigFile::showInExplorerNavigationPane.

    /* Set the left contents margin of the layout to zero to make the checkboxes
     * align properly vertically , fixes bug #3758
     */

    // OEM themes are not obliged to ship mono icons, so there
    // is no point in offering an option

    // accountAdded means the wizard was finished and the wizard might change some options.

    customizeStyle();
}

ThemeSettings::~ThemeSettings()
{
    delete _ui;
}



#if defined(BUILD_UPDATER)
void GeneralSettings::slotUpdateInfo()
{
    if (ConfigFile().skipUpdateCheck() || !Updater::instance()) {
        // updater disabled on compile
        _ui->updatesGroupBox->setVisible(false);
        return;
    }

    // Note: the sparkle-updater is not an OCUpdater
    auto *ocupdater = qobject_cast<OCUpdater *>(Updater::instance());
    if (ocupdater) {
        connect(ocupdater, &OCUpdater::downloadStateChanged, this, &GeneralSettings::slotUpdateInfo, Qt::UniqueConnection);
        connect(_ui->restartButton, &QAbstractButton::clicked, ocupdater, &OCUpdater::slotStartInstaller, Qt::UniqueConnection);
        connect(_ui->restartButton, &QAbstractButton::clicked, qApp, &QApplication::quit, Qt::UniqueConnection);
        connect(_ui->updateButton, &QAbstractButton::clicked, this, &GeneralSettings::slotUpdateCheckNow, Qt::UniqueConnection);
        connect(_ui->autoCheckForUpdatesCheckBox, &QAbstractButton::toggled, this, &GeneralSettings::slotToggleAutoUpdateCheck);

        QString status = ocupdater->statusString(OCUpdater::UpdateStatusStringFormat::Html);
        Theme::replaceLinkColorStringBackgroundAware(status);

        _ui->updateStateLabel->setOpenExternalLinks(false);
        connect(_ui->updateStateLabel, &QLabel::linkActivated, this, [](const QString &link) {
            Utility::openBrowser(QUrl(link));
        });
        _ui->updateStateLabel->setText(status);

        _ui->restartButton->setVisible(ocupdater->downloadState() == OCUpdater::DownloadComplete);

        _ui->updateButton->setEnabled(ocupdater->downloadState() != OCUpdater::CheckingServer &&
                                      ocupdater->downloadState() != OCUpdater::Downloading &&
                                      ocupdater->downloadState() != OCUpdater::DownloadComplete);

        _ui->autoCheckForUpdatesCheckBox->setChecked(ConfigFile().autoUpdateCheck());
    }
#if defined(Q_OS_MAC) && defined(HAVE_SPARKLE)
    else if (auto sparkleUpdater = qobject_cast<SparkleUpdater *>(Updater::instance())) {
        _ui->updateStateLabel->setText(sparkleUpdater->statusString());
        _ui->restartButton->setVisible(false);
    }
#endif

    // Channel selection
    _ui->updateChannel->setCurrentIndex(ConfigFile().updateChannel() == "beta" ? 1 : 0);
    connect(_ui->updateChannel, &QComboBox::currentTextChanged,
        this, &GeneralSettings::slotUpdateChannelChanged, Qt::UniqueConnection);
}

void GeneralSettings::slotUpdateChannelChanged(const QString &channel)
{
    if (channel == ConfigFile().updateChannel())
        return;

    auto msgBox = new QMessageBox(
        QMessageBox::Warning,
        tr("Change update channel?"),
        tr("The update channel determines which client updates will be offered "
           "for installation. The \"stable\" channel contains only upgrades that "
           "are considered reliable, while the versions in the \"beta\" channel "
           "may contain newer features and bugfixes, but have not yet been tested "
           "thoroughly."
           "\n\n"
           "Note that this selects only what pool upgrades are taken from, and that "
           "there are no downgrades: So going back from the beta channel to "
           "the stable channel usually cannot be done immediately and means waiting "
           "for a stable version that is newer than the currently installed beta "
           "version."),
        QMessageBox::NoButton,
        this);
    auto acceptButton = msgBox->addButton(tr("Change update channel"), QMessageBox::AcceptRole);
    msgBox->addButton(tr("Cancel"), QMessageBox::RejectRole);
    connect(msgBox, &QMessageBox::finished, msgBox, [this, channel, msgBox, acceptButton] {
        msgBox->deleteLater();
        if (msgBox->clickedButton() == acceptButton) {
            ConfigFile().setUpdateChannel(channel);
            if (auto updater = qobject_cast<OCUpdater *>(Updater::instance())) {
                updater->setUpdateUrl(Updater::updateUrl());
                updater->checkForUpdate();
            }
#if defined(Q_OS_MAC) && defined(HAVE_SPARKLE)
            else if (auto updater = qobject_cast<SparkleUpdater *>(Updater::instance())) {
                updater->setUpdateUrl(Updater::updateUrl());
                updater->checkForUpdate();
            }
#endif
        } else {
            _ui->updateChannel->setCurrentText(ConfigFile().updateChannel());
        }
    });
    msgBox->open();
}

void GeneralSettings::slotUpdateCheckNow()
{
    auto *updater = qobject_cast<OCUpdater *>(Updater::instance());
    if (ConfigFile().skipUpdateCheck()) {
        updater = nullptr; // don't show update info if updates are disabled
    }

    if (updater) {
        _ui->updateButton->setEnabled(false);

        updater->checkForUpdate();
    }
}

void GeneralSettings::slotToggleAutoUpdateCheck()
{
    ConfigFile cfgFile;
    bool isChecked = _ui->autoCheckForUpdatesCheckBox->isChecked();
    cfgFile.setAutoUpdateCheck(isChecked, QString());
}
#endif // defined(BUILD_UPDATER)





} // namespace OCC
