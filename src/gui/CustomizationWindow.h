#ifndef CUSTOMIZATIONWINDOW_H
#define CUSTOMIZATIONWINDOW_H

#include <QDialog>
#include <QObject>
#include <QtCore>

extern bool themeFiu;
extern bool isFiu;
extern bool isBeige;
extern bool isDark;
extern bool isBlue;
extern bool isRed;
extern bool isYellow;

namespace Ui {
class CustomizationWindow;
}

class CustomizationWindow : public QDialog
{
    Q_OBJECT

public:
    explicit CustomizationWindow(QWidget *parent = nullptr);
    ~CustomizationWindow();

private slots:
    void on_ThemeResetButton_clicked();
    void on_ThemeApplyButton_clicked();
    void on_ThemeCreateButton_clicked();

private:
    Ui::CustomizationWindow *ui;
    void fillComboBox();
    void openMainDialog();
    void openPersonalTab();
};

#endif // CUSTOMIZATIONWINDOW_H

