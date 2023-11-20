#ifndef ADDBUTTONWINDOW_H
#define ADDBUTTONWINDOW_H

#include <QDialog>
#include <QObject>
#include <QtCore>

extern int amount;
extern int status;
extern QString buttonName1;
extern QString buttonLink1;
extern QString buttonName2;
extern QString buttonLink2;
extern QString buttonName3;
extern QString buttonLink3;
extern QString buttonName4;
extern QString buttonLink4;

namespace Ui {
class AddButtonWindow;
}

class AddButtonWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AddButtonWindow(QWidget *parent = nullptr);
    ~AddButtonWindow();

private slots:
    void on_AddButton_clicked();
    void on_buttonBox_rejected();
    void on_buttonBox_accepted();

private:
    Ui::AddButtonWindow *ui;
};

#endif // ADDBUTTONWINDOW_H
