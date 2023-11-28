#include "personaltab.h"
#include "ui_personaltab.h"
#include "addbuttonwindow.h"
#include "CustomizationWindow.h"
#include "generalsettings.h"

#include <QShortcut>
#include <QDir>
#include <QDebug>
#include <QProcess>
#include <iostream>
#include <string>
#include <QVBoxLayout>
#include <QPushButton>
#include <QFileDialog>
#include <QDesktopServices>
#include <QLabel>

PersonalTab::PersonalTab(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PersonalTab)
{
    ui->setupUi(this);
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q), this, SLOT(close())); //close
    //All cases for different themes
    switch(status)
    {
    case 0:
        defaultNextcloudTheme();
        break;
    case 1:
        makeCustomButton(amount);
        break;
    case 2:
        fiuTheme();
        break;
    case 3:
        darkTheme(amount);
        break;
    case 4:
        beigeTheme(amount);
        break;
    case 5:
        blueTheme(amount);
        break;
    default:
        defaultNextcloudTheme();
        break;
    }

}

PersonalTab::~PersonalTab()
{
    delete ui;
}

void PersonalTab::defaultNextcloudTheme()
{
    ui->button1->setVisible(true);
    ui->button2->setVisible(true);
    ui->button3->setVisible(true);
    ui->button4->setVisible(true);

    ui->button1->setText("Nextcloud Website");
    ui->button2->setText("Support Portal");
    ui->button3->setText("Portal Login Page");
    ui->button4->setText("Setup Page");

    connect(ui->button1, &QPushButton::clicked, this, []{
        QDesktopServices::openUrl(QUrl("https://nextcloud.com/"));
    });
    connect(ui->button2, &QPushButton::clicked, this, []{
        QDesktopServices::openUrl(QUrl("https://portal.nextcloud.com/"));
    });
    connect(ui->button3, &QPushButton::clicked, this, []{
        QDesktopServices::openUrl(QUrl("https://portal.nextcloud.com/login"));
    });
    connect(ui->button4, &QPushButton::clicked, this, []{
        QDesktopServices::openUrl(QUrl("https://nextcloud.com/install/"));
    });
}

void PersonalTab::fiuTheme()
{
    setStyleSheet("background-color: #081E3F;");
    ui->TitleLabel->setText("FIU");
    ui->TitleLabel->setStyleSheet("color: #B6862C;");
    ui->SubtitleLabel->setText("Spes Scientia Facultas");
    ui->SubtitleLabel->setStyleSheet("color: #B6862C;");

    ui->button1->setVisible(true);
    ui->button2->setVisible(true);
    ui->button3->setVisible(true);
    ui->button4->setVisible(true);

    ui->button1->setStyleSheet(R"(
        QPushButton {
            background-color: #002F65;
            color: #B6862C;
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
    ui->button2->setStyleSheet(R"(
        QPushButton {
            background-color: #002F65;
            color: #B6862C;
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
    ui->button3->setStyleSheet(R"(
        QPushButton {
            background-color: #002F65;
            color: #B6862C;
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
    ui->button4->setStyleSheet(R"(
        QPushButton {
            background-color: #002F65;
            color: #B6862C;
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

    ui->button1->setText("FIU Website");
    ui->button2->setText("FIU Canvas");
    ui->button3->setText("FIU Mail");
    ui->button4->setText("FIU News");

    connect(ui->button1, &QPushButton::clicked, this, []{
        QDesktopServices::openUrl(QUrl("https://www.fiu.edu/"));
    });
    connect(ui->button2, &QPushButton::clicked, this, []{
        QDesktopServices::openUrl(QUrl("https://fiu.instructure.com/"));
    });
    connect(ui->button3, &QPushButton::clicked, this, []{
        QDesktopServices::openUrl(QUrl("https://outlook.office365.com/mail/"));
    });
    connect(ui->button4, &QPushButton::clicked, this, []{
        QDesktopServices::openUrl(QUrl("https://news.fiu.edu/"));
    });
}

void PersonalTab::beigeTheme(int amount)
{
    setStyleSheet("background-color: #B0926A;");
    ui->TitleLabel->setStyleSheet("color: #706233;");
    ui->SubtitleLabel->setStyleSheet("color: #706233;");
    makeCustomButton(amount);
    ui->button1->setStyleSheet(R"(
        QPushButton {
            background-color: #E1C78F;
            color: #706233;
            border: none;
            padding: 10px;
            border-radius: 5px;
            font-weight: bold;
        }
        QPushButton:hover {
            background-color: #ebcf94;
        }
        QPushButton:pressed {
            background-color: #d4ba85;
        }
    )");
    ui->button2->setStyleSheet(R"(
        QPushButton {
            background-color: #E1C78F;
            color: #706233;
            border: none;
            padding: 10px;
            border-radius: 5px;
            font-weight: bold;
        }
        QPushButton:hover {
            background-color: #ebcf94;
        }
        QPushButton:pressed {
            background-color: #d4ba85;
        }
    )");
    ui->button3->setStyleSheet(R"(
        QPushButton {
            background-color: #E1C78F;
            color: #706233;
            border: none;
            padding: 10px;
            border-radius: 5px;
            font-weight: bold;
        }
        QPushButton:hover {
            background-color: #ebcf94;
        }
        QPushButton:pressed {
            background-color: #d4ba85;
        }
    )");
    ui->button4->setStyleSheet(R"(
        QPushButton {
            background-color: #E1C78F;
            color: #706233;
            border: none;
            padding: 10px;
            border-radius: 5px;
            font-weight: bold;
        }
        QPushButton:hover {
            background-color: #ebcf94;
        }
        QPushButton:pressed {
            background-color: #d4ba85;
        }
    )");
}

void PersonalTab::darkTheme(int amount)
{
    setStyleSheet("background-color: #505050;");
    ui->TitleLabel->setStyleSheet("color: #dedede;");
    ui->SubtitleLabel->setStyleSheet("color: #dedede;");
    makeCustomButton(amount);
    ui->button1->setStyleSheet(R"(
        QPushButton {
            background-color: #2b2b2b;
            color: #dedede;
            border: none;
            padding: 10px;
            border-radius: 5px;
            font-weight: bold;
        }
        QPushButton:hover {
            background-color: #363636;
        }
        QPushButton:pressed {
            background-color: #3f3f3f;
        }
    )");
    ui->button2->setStyleSheet(R"(
        QPushButton {
            background-color: #2b2b2b;
            color: #dedede;
            border: none;
            padding: 10px;
            border-radius: 5px;
            font-weight: bold;
        }
        QPushButton:hover {
            background-color: #363636;
        }
        QPushButton:pressed {
            background-color: #3f3f3f;
        }
    )");
    ui->button3->setStyleSheet(R"(
        QPushButton {
            background-color: #2b2b2b;
            color: #dedede;
            border: none;
            padding: 10px;
            border-radius: 5px;
            font-weight: bold;
        }
        QPushButton:hover {
            background-color: #363636;
        }
        QPushButton:pressed {
            background-color: #3f3f3f;
        }
    )");
    ui->button4->setStyleSheet(R"(
        QPushButton {
            background-color: #2b2b2b;
            color: #dedede;
            border: none;
            padding: 10px;
            border-radius: 5px;
            font-weight: bold;
        }
        QPushButton:hover {
            background-color: #363636;
        }
        QPushButton:pressed {
            background-color: #3f3f3f;
        }
    )");
}

void PersonalTab::blueTheme(int amount)
{
    setStyleSheet("background-color: #427D9D;");
    ui->TitleLabel->setStyleSheet("color: #DDF2FD;");
    ui->SubtitleLabel->setStyleSheet("color: #DDF2FD;");
    makeCustomButton(amount);
    ui->button1->setStyleSheet(R"(
        QPushButton {
            background-color: #164863;
            color: #DDF2FD;
            border: none;
            padding: 10px;
            border-radius: 5px;
            font-weight: bold;
        }
        QPushButton:hover {
            background-color: #195373;
        }
        QPushButton:pressed {
            background-color: #103447;
        }
    )");
    ui->button2->setStyleSheet(R"(
        QPushButton {
            background-color: #164863;
            color: #DDF2FD;
            border: none;
            padding: 10px;
            border-radius: 5px;
            font-weight: bold;
        }
        QPushButton:hover {
            background-color: #195373;
        }
        QPushButton:pressed {
            background-color: #103447;
        }
    )");
    ui->button3->setStyleSheet(R"(
        QPushButton {
            background-color: #164863;
            color: #DDF2FD;
            border: none;
            padding: 10px;
            border-radius: 5px;
            font-weight: bold;
        }
        QPushButton:hover {
            background-color: #195373;
        }
        QPushButton:pressed {
            background-color: #103447;
        }
    )");
    ui->button4->setStyleSheet(R"(
        QPushButton {
            background-color: #164863;
            color: #DDF2FD;
            border: none;
            padding: 10px;
            border-radius: 5px;
            font-weight: bold;
        }
        QPushButton:hover {
            background-color: #195373;
        }
        QPushButton:pressed {
            background-color: #103447;
        }
    )");
}

void PersonalTab::makeCustomButton(int amount)
{
    if(amount == 1){
        auto shortcut1 = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_1), this); //general settings
        QObject::connect(shortcut1, &QShortcut::activated, this, [ this ] { QDesktopServices::openUrl(QUrl(buttonLink1));} );
        ui->button1->setVisible(true);
        ui->button2->setVisible(false);
        ui->button3->setVisible(false);
        ui->button4->setVisible(false);
        ui->button1->setText(buttonName1);
        connect(ui->button1, &QPushButton::clicked, this, []{
            QDesktopServices::openUrl(QUrl(buttonLink1));
        });
    }else if(amount == 2){
        auto shortcut1 = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_1), this); //general settings
        QObject::connect(shortcut1, &QShortcut::activated, this, [ this ] { QDesktopServices::openUrl(QUrl(buttonLink1));} );
        auto shortcut2 = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_2), this); //general settings
        QObject::connect(shortcut2, &QShortcut::activated, this, [ this ] { QDesktopServices::openUrl(QUrl(buttonLink2));} );
        ui->button1->setVisible(true);
        ui->button2->setVisible(true);
        ui->button3->setVisible(false);
        ui->button4->setVisible(false);
        ui->button1->setText(buttonName1);
        connect(ui->button1, &QPushButton::clicked, this, []{
            QDesktopServices::openUrl(QUrl(buttonLink1));
        });
        ui->button2->setText(buttonName2);
        connect(ui->button2, &QPushButton::clicked, this, []{
            QDesktopServices::openUrl(QUrl(buttonLink2));
        });
    }else if(amount == 3){
        auto shortcut1 = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_1), this); //general settings
        QObject::connect(shortcut1, &QShortcut::activated, this, [ this ] { QDesktopServices::openUrl(QUrl(buttonLink1));} );
        auto shortcut2 = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_2), this); //general settings
        QObject::connect(shortcut2, &QShortcut::activated, this, [ this ] { QDesktopServices::openUrl(QUrl(buttonLink2));} );
        auto shortcut3 = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_3), this); //general settings
        QObject::connect(shortcut3, &QShortcut::activated, this, [ this ] { QDesktopServices::openUrl(QUrl(buttonLink3));} );
        ui->button1->setVisible(true);
        ui->button2->setVisible(true);
        ui->button3->setVisible(true);
        ui->button4->setVisible(false);
        ui->button1->setText(buttonName1);
        connect(ui->button1, &QPushButton::clicked, this, []{
            QDesktopServices::openUrl(QUrl(buttonLink1));
        });

        ui->button2->setText(buttonName2);
        connect(ui->button2, &QPushButton::clicked, this, []{
            QDesktopServices::openUrl(QUrl(buttonLink2));
        });

        ui->button3->setText(buttonName3);
        connect(ui->button3, &QPushButton::clicked, this, []{
            QDesktopServices::openUrl(QUrl(buttonLink3));
        });
    }else if(amount == 4){
        auto shortcut1 = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_1), this); //general settings
        QObject::connect(shortcut1, &QShortcut::activated, this, [ this ] { QDesktopServices::openUrl(QUrl(buttonLink1));} );
        auto shortcut2 = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_2), this); //general settings
        QObject::connect(shortcut2, &QShortcut::activated, this, [ this ] { QDesktopServices::openUrl(QUrl(buttonLink2));} );
        auto shortcut3 = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_3), this); //general settings
        QObject::connect(shortcut3, &QShortcut::activated, this, [ this ] { QDesktopServices::openUrl(QUrl(buttonLink3));} );
        auto shortcut4 = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_4), this); //general settings
        QObject::connect(shortcut1, &QShortcut::activated, this, [ this ] { QDesktopServices::openUrl(QUrl(buttonLink1));} );
        ui->button1->setVisible(true);
        ui->button2->setVisible(true);
        ui->button3->setVisible(true);
        ui->button4->setVisible(true);
        ui->button1->setText(buttonName1);
        connect(ui->button1, &QPushButton::clicked, this, []{
            QDesktopServices::openUrl(QUrl(buttonLink1));
        });
        ui->button2->setText(buttonName2);
        connect(ui->button2, &QPushButton::clicked, this, []{
            QDesktopServices::openUrl(QUrl(buttonLink2));
        });
        ui->button3->setText(buttonName3);
        connect(ui->button3, &QPushButton::clicked, this, []{
            QDesktopServices::openUrl(QUrl(buttonLink3));
        });
        ui->button4->setText(buttonName4);
        connect(ui->button4, &QPushButton::clicked, this, []{
            QDesktopServices::openUrl(QUrl(buttonLink4));
        });
    }
}

void openCustomization(){
    CustomizationWindow *window = new CustomizationWindow(static_cast<QWidget*>(QApplication::activeWindow()));
    window->show();
}

void openGeneralSettings(){
    OCC::GeneralSettings *window = new OCC::GeneralSettings(static_cast<QWidget*>(QApplication::activeWindow()));
    window->show();
}
