#ifndef CUSTOMIZATIONWINDOW_H
#define CUSTOMIZATIONWINDOW_H

#include <QDialog>

namespace Ui {
class CustomizationWindow;
}

class CustomizationWindow : public QDialog
{
    Q_OBJECT

public:
    explicit CustomizationWindow(QWidget *parent = nullptr);
    ~CustomizationWindow();

private:
    Ui::CustomizationWindow *ui;
    void FillComboBox();
    void ChangeTheme();
};

#endif // CUSTOMIZATIONWINDOW_H
