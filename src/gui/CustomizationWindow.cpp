#include "CustomizationWindow.h"
#include "systray.h"
#include "ui_CustomizationWindow.h"
#include "addbuttonwindow.h"
#include "personaltab.h"

#include <QProcess>
#include <QDir>
#include <QComboBox>
#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>

bool isFiu;
bool isBeige;
bool isDark;
bool isBlue;
bool isRed;
bool isYellow;

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

//Theme booleans and checks
void CustomizationWindow::on_ThemeApplyButton_clicked()
{
    if(ui->LoginFiuRadioButton->isChecked()){
        isFiu = true;
        isBeige = false;
        isDark = false;
        isBlue = false;
        isRed = false;
        isYellow = false;
    } else if (ui->LoginBeigeRadioButton->isChecked()){
        isBeige = true;
        isFiu = false;
        isDark = false;
        isBlue = false;
        isRed = false;
        isYellow = false;
    } else if(ui->LoginDarkRadioButton->isChecked()){
        isDark = true;
        isFiu = false;
        isBeige = false;
        isBlue = false;
        isRed = false;
        isYellow = false;
    } else if(ui->LoginBlueRadioButton->isChecked()){
        isDark = false;
        isFiu = false;
        isBeige = false;
        isBlue = true;
        isRed = false;
        isYellow = false;
    } else if(ui->LoginRedRadioButton->isChecked()){
        isDark = false;
        isFiu = false;
        isBeige = false;
        isBlue = false;
        isRed = true;
        isYellow = false;
    } else if(ui->LoginYellowRadioButton->isChecked()){
        isDark = false;
        isFiu = false;
        isBeige = false;
        isBlue = false;
        isRed = false;
        isYellow = true;
    }

    if(ui->TrayThemeFiuButton->isChecked()){
        status = 2;
        QMessageBox::information(nullptr, tr("User Button Theme"), tr("Fiu button theme set."));
    } else if(ui->TrayThemeDarkButton->isChecked()){
        if(amount > 0){
            status = 3;
            QMessageBox::information(nullptr, tr("User Button Theme"), tr("Dark button theme set."));
        } else {
            QMessageBox::information(nullptr, tr("Add User Button"), tr("Please create buttons to use this theme."));
            status = 0;
        }
    } else if(ui->TrayThemeBeigeButton->isChecked()){
        if(amount > 0){
            status = 4;
            QMessageBox::information(nullptr, tr("User Button Theme"), tr("Beige button theme set."));
        } else {
            QMessageBox::information(nullptr, tr("Add User Button"), tr("Please create buttons to use this theme."));
            status = 0;
        }
    } else if(ui->TrayThemeBlueButton->isChecked()){
        if(amount > 0){
            status = 5;
            QMessageBox::information(nullptr, tr("User Button Theme"), tr("Blue button theme set."));
        } else {
            QMessageBox::information(nullptr, tr("Add User Button"), tr("Please create buttons to use this theme."));
            status = 0;
        }
    }
}

void CustomizationWindow::on_ThemeResetButton_clicked()
{
    isFiu = false;
    isBeige = false;
    isDark = false;
    isBlue = false;
    isRed = false;
    isYellow = false;
    status = 0;
    amount = 0;
    QMessageBox::information(nullptr, tr("Customization Window"), tr("Reset all themes to default."));
}

void CustomizationWindow::on_ThemeCreateButton_clicked()
{
    AddButtonWindow *window = new AddButtonWindow(static_cast<QWidget*>(QApplication::activeWindow()));
    window->show();
}

