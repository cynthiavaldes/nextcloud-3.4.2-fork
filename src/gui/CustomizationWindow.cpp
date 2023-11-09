#include "CustomizationWindow.h"
#include "systray.h"
#include "ui_CustomizationWindow.h"

#include <QProcess>
#include <QDir>
#include <QComboBox>
#include <QFileDialog>
#include <QDebug>

bool isFiu;
bool isBeige;
bool isDark;


CustomizationWindow::CustomizationWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CustomizationWindow)
{
    ui->setupUi(this);
}


CustomizationWindow::~CustomizationWindow()
{
    delete ui;
}

void CustomizationWindow::on_ThemeApplyButton_clicked()
{
    if(ui->LoginFiuRadioButton->isChecked()){
        isFiu = true;
        isBeige = false;
        isDark = false;
        QProcess process;
        process.execute("echo " + QVariant(isFiu).toString());
    } else if (ui->LoginBeigeRadioButton->isChecked()){
        isBeige = true;
        isFiu = false;
        isDark = false;
        QProcess process;
        process.execute("echo " + QVariant(isBeige).toString());
    } else if(ui->LoginDarkRadioButton->isChecked()){
        isDark = true;
        isFiu = false;
        isBeige = false;
        QProcess process;
        process.execute("echo " + QVariant(isDark).toString());
    }
}

void CustomizationWindow::on_ThemeResetButton_clicked()
{
    isFiu = false;
    isBeige = false;
    isDark = false;
}



void CustomizationWindow::on_ThemeEditButton_clicked()
{

}

