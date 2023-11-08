#include "personaltab.h"
#include "ui_personaltab.h"

#include <QDir>
#include <QDebug>
#include <QProcess>

PersonalTab::PersonalTab(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PersonalTab)
{
    ui->setupUi(this);
}


PersonalTab::~PersonalTab()
{
    delete ui;
}
