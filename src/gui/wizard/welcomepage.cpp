/*
 * Copyright (C) 2021 by Felix Weilbach <felix.weilbach@nextcloud.com>
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

#include "welcomepage.h"
#include "guiutility.h"
#include "theme.h"
#include "wizard/owncloudwizard.h"
#include "wizard/slideshow.h"
#include "ui_welcomepage.h"
#include "CustomizationWindow.h"

namespace OCC {

WelcomePage::WelcomePage(OwncloudWizard *ocWizard)
    : QWizardPage()
    , _ui(new Ui::WelcomePage)
    , _ocWizard(ocWizard)
{
    setupUi();
}

WelcomePage::~WelcomePage() = default;

void WelcomePage::setupUi()
{
    _ui->setupUi(this);
    setupSlideShow();
    setupLoginButton();
    setupCreateAccountButton();
    setupHostYourOwnServerLabel();
}

void WelcomePage::initializePage()
{
    customizeStyle();
}

void WelcomePage::setLoginButtonDefault()
{
    _ui->loginButton->setDefault(true);
    _ui->loginButton->setFocus();
}

void WelcomePage::styleSlideShow()
{
    const auto theme = Theme::instance();
    const auto backgroundColor = palette().window().color();

    const auto wizardNextcloudIconFileName = theme->isBranded() ? Theme::hidpiFileName("wizard-nextcloud.png", backgroundColor)
                                                                : Theme::hidpiFileName(":/client/theme/colored/wizard-nextcloud.png");
    const auto wizardFilesIconFileName = theme->isBranded() ? Theme::hidpiFileName("wizard-files.png", backgroundColor)
                                                            : Theme::hidpiFileName(":/client/theme/colored/wizard-files.png");
    const auto wizardGroupwareIconFileName = theme->isBranded() ? Theme::hidpiFileName("wizard-groupware.png", backgroundColor)
                                                                : Theme::hidpiFileName(":/client/theme/colored/wizard-groupware.png");
    const auto wizardTalkIconFileName = theme->isBranded() ? Theme::hidpiFileName("wizard-talk.png", backgroundColor)
                                                           : Theme::hidpiFileName(":/client/theme/colored/wizard-talk.png");

    if(isFiu == true){
        _ui->slideShow->addSlide(wizardNextcloudIconFileName, tr("Welcome to FIU's NextCloud Service"));
        _ui->slideShow->addSlide(wizardFilesIconFileName, tr("Access your academic materials anytime, anywhere"));
        _ui->slideShow->addSlide(wizardGroupwareIconFileName, tr("Collaborate with peers and faculty seamlessly"));
        _ui->slideShow->addSlide(wizardTalkIconFileName, tr("Stay connected with FIU's community"));
    } else {
        _ui->slideShow->addSlide(wizardNextcloudIconFileName, tr("Keep your data secure and under your control"));
        _ui->slideShow->addSlide(wizardFilesIconFileName, tr("Secure collaboration & file exchange"));
        _ui->slideShow->addSlide(wizardGroupwareIconFileName, tr("Easy-to-use web mail, calendaring & contacts"));
        _ui->slideShow->addSlide(wizardTalkIconFileName, tr("Screensharing, online meetings & web conferences"));
    }

    const auto isDarkBackground = Theme::isDarkColor(backgroundColor);
    _ui->slideShowNextButton->setIcon(theme->uiThemeIcon(QString("control-next.svg"), isDarkBackground));
    _ui->slideShowPreviousButton->setIcon(theme->uiThemeIcon(QString("control-prev.svg"), isDarkBackground));
}

void WelcomePage::setupSlideShow()
{
    connect(_ui->slideShow, &SlideShow::clicked, _ui->slideShow, &SlideShow::stopShow);
    connect(_ui->slideShowNextButton, &QPushButton::clicked, _ui->slideShow, &SlideShow::nextSlide);
    connect(_ui->slideShowPreviousButton, &QPushButton::clicked, _ui->slideShow, &SlideShow::prevSlide);
}

void WelcomePage::setupLoginButton()
{
    const auto appName = Theme::instance()->appNameGUI();

    _ui->loginButton->setText(tr("Log in to your %1").arg(appName));
    connect(_ui->loginButton, &QPushButton::clicked, this, [this](bool /*checked*/) {
        _nextPage = WizardCommon::Page_ServerSetup;
        _ocWizard->next();
    });
}

void WelcomePage::setupCreateAccountButton()
{
    if(isFiu == true){
        _ui->createAccountButton->setText(tr("Login to my FIU Server"));
#ifdef WITH_WEBENGINE
        // If your application is compiled with web engine support, you'll need to handle it as per your app's logic.
        // For simplicity, I'm just opening the link here, but you might need to adjust it based on your app's flow.
        connect(_ui->createAccountButton, &QPushButton::clicked, this, [this](bool /*checked*/) {
            Utility::openBrowser(QStringLiteral("https://capstone-cloud2.cs.fiu.edu/"));
        });
#else // WITHOUT_WEBENGINE
        // This will open the default web browser to the FIU server login page when the button is clicked.
        connect(_ui->createAccountButton, &QPushButton::clicked, this, [](bool /*checked*/) {
            Utility::openBrowser(QStringLiteral("https://capstone-cloud2.cs.fiu.edu/"));
        });
#endif // WITH_WEBENGINE
    } else {
#ifdef WITH_WEBENGINE
connect(_ui->createAccountButton, &QPushButton::clicked, this, [this](bool /*checked*/) {
        _ocWizard->setRegistration(true);
        _nextPage = WizardCommon::Page_WebView;
        _ocWizard->next();
});
#else // WITH_WEBENGINE
    connect(_ui->createAccountButton, &QPushButton::clicked, this, [this](bool /*checked*/) {
        _ocWizard->setRegistration(true);
        Utility::openBrowser(QStringLiteral("https://nextcloud.com/register"));
        });
#endif // WITH_WEBENGINE
    }
}

void WelcomePage::setupHostYourOwnServerLabel()
{
    _ui->hostYourOwnServerLabel->setText(tr("Host your own server"));
    _ui->hostYourOwnServerLabel->setAlignment(Qt::AlignCenter);
    _ui->hostYourOwnServerLabel->setUrl(QUrl("https://docs.nextcloud.com/server/latest/admin_manual/installation/#installation"));
}

int WelcomePage::nextId() const
{
    return _nextPage;
}

void WelcomePage::customizeStyle()
{
    if(isFiu == true){
// Ensure that the stylesheet is applied to the whole wizard window
// Set a lighter blue background color for the overall widget
QString lighterBlueBackground = "#5F9EA0"; // Cadet Blue, a soft blue that should work well
_ocWizard->setStyleSheet(QString("QWizard { background-color: %1; }").arg(lighterBlueBackground));
_ocWizard->setAttribute(Qt::WA_StyledBackground, true);

       // Style the slideshow with a semi-transparent background and rounded corners
_ui->slideShow->setStyleSheet("QWidget { background-color: rgba(255, 255, 255, 150); border-radius: 10px; }");

       // Style the slideshow with a semi-transparent background and rounded corners
_ui->slideShow->setStyleSheet("QWidget { background-color: rgba(255, 255, 255, 150); border-radius: 10px; }");

       // Style the login button with FIU colors and a shadow effect
_ui->loginButton->setStyleSheet(R"(
        QPushButton {
            background-color: #002F65;
            color: #F37021;
            border: none;
            padding: 10px;
            border-radius: 5px;
            font-weight: bold;
        }
        QPushButton:hover {
            background-color: #013A6B;
        }
        QPushButton:pressed {
            background-color: #012A4A;
        }
    )");

       // Style the "Login to my FIU Server" button with a gold background and a shadow effect
_ui->createAccountButton->setText(tr("Login to my FIU Server"));
_ui->createAccountButton->setStyleSheet(R"(
        QPushButton {
            background-color: #F37021;
            color: #002F65;
            border: none;
            padding: 10px;
            border-radius: 5px;
            font-weight: bold;
        }
        QPushButton:hover {
            background-color: #F48031;
        }
        QPushButton:pressed {
            background-color: #C06020;
        }
    )");

       // Adjust the host-your-own-server label to be more subtle and match the new styling
_ui->hostYourOwnServerLabel->setStyleSheet("QLabel { color: #F37021; text-decoration: underline; }");

       // Other style customizations
styleSlideShow();

       // Setup the custom behavior for the "Login to my FIU Server" button
#ifdef WITH_WEBENGINE
connect(_ui->createAccountButton, &QPushButton::clicked, this, [this](bool /*checked*/) {
    Utility::openBrowser(QStringLiteral("https://capstone-cloud2.cs.fiu.edu/"));
});
#else // WITHOUT_WEBENGINE
    connect(_ui->createAccountButton, &QPushButton::clicked, this, [](bool /*checked*/) {
        Utility::openBrowser(QStringLiteral("https://capstone-cloud2.cs.fiu.edu/"));
    });
#endif // WITH_WEBENGINE
    } else if(isBeige == true){
QString beigeBackground = "#FFFBEC";
_ocWizard->setStyleSheet(QString("QWizard { background-color: %1; }").arg(beigeBackground));
_ocWizard->setAttribute(Qt::WA_StyledBackground, true);

_ui->loginButton->setStyleSheet(R"(
        QPushButton {
            background-color: #FFF7D6;
            color: #5a5a5a;
            border: none;
            padding: 10px;
            border-radius: 5px;
            font-weight: bold;
        }
        QPushButton:hover {
            background-color: #FFFBE9;
        }
        QPushButton:pressed {
            background-color: #FFF3C3;
        }
    )");
_ui->createAccountButton->setStyleSheet(R"(
        QPushButton {
            background-color: #FFF7D6;
            color: #5a5a5a;
            border: none;
            padding: 10px;
            border-radius: 5px;
            font-weight: bold;
        }
        QPushButton:hover {
            background-color: #FFFBE9;
        }
        QPushButton:pressed {
            background-color: #FFF3C3;
        }
    )");
_ui->hostYourOwnServerLabel->setStyleSheet("QLabel { color: #5a5a5a; text-decoration: underline; }");
styleSlideShow();
    } else if(isDark == true){
QString darkBackground = "#505050";
_ocWizard->setStyleSheet(QString("QWizard { background-color: %1; }").arg(darkBackground));
_ocWizard->setAttribute(Qt::WA_StyledBackground, true);

_ui->loginButton->setStyleSheet(R"(
        QPushButton {
            background-color: #4b4b4b;
            color: #000000;
            border: none;
            padding: 10px;
            border-radius: 5px;
            font-weight: bold;
        }
        QPushButton:hover {
            background-color: #666666;
        }
        QPushButton:pressed {
            background-color: #3f3f3f;
        }
    )");
_ui->createAccountButton->setStyleSheet(R"(
        QPushButton {
            background-color: #4b4b4b;
            color: #000000;
            border: none;
            padding: 10px;
            border-radius: 5px;
            font-weight: bold;
        }
        QPushButton:hover {
            background-color: #666666;
        }
        QPushButton:pressed {
            background-color: #3f3f3f;
        }
    )");
_ui->hostYourOwnServerLabel->setStyleSheet("QLabel { color: #000000; text-decoration: underline; }");
styleSlideShow();
    } else {
   styleSlideShow();
    }
}

}
