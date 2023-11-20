#include "addbuttonwindow.h"
#include "ui_addbuttonwindow.h"
#include "CustomizationWindow.h"
#include "personaltab.h"

#include <QDir>
#include <QDebug>
#include <QProcess>
#include <QString>
#include <QMessageBox>

int amount;
int status = 0;
QString buttonName1;
QString buttonLink1;
QString buttonName2;
QString buttonLink2;
QString buttonName3;
QString buttonLink3;
QString buttonName4;
QString buttonLink4;

AddButtonWindow::AddButtonWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddButtonWindow)

{
    ui->setupUi(this);
}

AddButtonWindow::~AddButtonWindow()
{
    delete ui;
}

void AddButtonWindow::on_buttonBox_rejected()
{
    status = 0;
    close();
}

//Inserts button names and links on add slot
void AddButtonWindow::on_AddButton_clicked()
{
    if(!(ui->ButtonNameLineEdit->text().isEmpty() && ui->ButtonLinkLineEdit->text().isEmpty()))
    {
        QMessageBox::information(nullptr, tr("User Button"), tr("Added user button."));
        amount++;
        if(amount == 1){
            buttonName1 = ui->ButtonNameLineEdit->text();
            buttonLink1 = ui->ButtonLinkLineEdit->text();
        } else if(amount == 2){
            buttonName2 = ui->ButtonNameLineEdit->text();
            buttonLink2 = ui->ButtonLinkLineEdit->text();
        } else if(amount == 3){
            buttonName3 = ui->ButtonNameLineEdit->text();
            buttonLink3 = ui->ButtonLinkLineEdit->text();
        } else if(amount == 4){
            buttonName4 = ui->ButtonNameLineEdit->text();
            buttonLink4 = ui->ButtonLinkLineEdit->text();
        } else {
            QMessageBox::information(nullptr, tr("User Button"), tr("The minimum number of buttons is: 1, the maximum number of buttons is: 4"));
            if(amount == 5){
                amount = 4;
            }
        }
    } else {
        QMessageBox::information(nullptr, tr("User Button"), tr("Please write in a button name and a button link with the format https://www.<link>"));
    }
}

void AddButtonWindow::on_buttonBox_accepted()
{
    status = 1;
    close();
}

