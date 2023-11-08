#ifndef CUSTOMIZATIONWINDOW_H
#define CUSTOMIZATIONWINDOW_H

#include <QDialog>
#include <QObject>
#include <QtCore>

extern bool isFiu;
extern bool isBeige;
extern bool isDark;

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
    void on_ThemeEditButton_clicked();

private:
    Ui::CustomizationWindow *ui;
};

#endif // CUSTOMIZATIONWINDOW_H

