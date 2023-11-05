#include "studentresources.h"
#include "ui_studentresources.h"

#include <QDesktopServices>
#include <QUrl>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QApplication>
#include <QGuiApplication>

StudentResources::StudentResources(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StudentResources)
{
// Connect buttons to web links
    ui->setupUi(this);
    connect(ui->FiuPortalButton, &QPushButton::clicked, this, &StudentResources::MyFiuLink);

    connect(ui->FiuEmailButton, &QPushButton::clicked, this, &StudentResources::MyFiuLink);

    connect(ui->FiuCalendarButton, &QPushButton::clicked, this, &StudentResources::MyFiuLink);

    connect(ui->FiuCanvasButton, &QPushButton::clicked, this, &StudentResources::MyFiuLink);
    /*
    connect(emailButton, &QPushButton::clicked, this, []{
        QDesktopServices::openUrl(QUrl("https://outlook.office365.com/mail/"));
    };
    connect(calendarButton, &QPushButton::clicked, this, []{
        QDesktopServices::openUrl(QUrl("https://outlook.office365.com/calendar/view/month"));
    };
    connect(canvasButton, &QPushButton::clicked, this, []{
       QDesktopServices::openUrl(QUrl("https://canvas.fiu.edu/"));
    };
    */

}




StudentResources::~StudentResources()
{
    delete ui;
}

void StudentResources::MyFiuLink(){
    QDesktopServices::openUrl(QUrl("https://my.fiu.edu/"));
}
void StudentResources::MailLink(){
    QDesktopServices::openUrl(QUrl("https://outlook.office365.com/mail/"));
}
void StudentResources::CalendarLink(){
    QDesktopServices::openUrl(QUrl("https://outlook.office365.com/calendar/view/month"));
}
void StudentResources::CanvasLink(){
    QDesktopServices::openUrl(QUrl("https://canvas.fiu.edu/"));
}
