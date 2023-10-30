#include "CustomizationWindow.h"
#include "ui_CustomizationWindow.h"

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

