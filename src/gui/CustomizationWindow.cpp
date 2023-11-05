#include "CustomizationWindow.h"
#include "ui_CustomizationWindow.h"

#include <QDir>

CustomizationWindow::CustomizationWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CustomizationWindow)
{
    ui->setupUi(this);
    FillComboBox();
}


CustomizationWindow::~CustomizationWindow()
{
    delete ui;
}

void CustomizationWindow::ChangeTheme()
{
    /*
    QDir filename = QFileDialog::getExistingDirectory(this, tr("Open Directory"), "/home", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    //const auto filename = QFileDialog::getExistingDirectory(this);
    if (filename.isEmpty()) {
        return;
    }

    QDir tempFilename = filename;
    QDir dir =QDir("/home/cynth/theme");
    */
}

void CustomizationWindow::FillComboBox()
{
    QDir const filename = QDir("/home/cynth/themes");
    for(const auto& i : filename.entryList() )
    {
        ui->GeneralThemeComboBox->addItem(i);
    }
}
