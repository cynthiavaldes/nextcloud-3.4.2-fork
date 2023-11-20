#ifndef PERSONALTAB_H
#define PERSONALTAB_H

#include <QDialog>
#include <QObject>
#include <QtCore>

namespace Ui {
class PersonalTab;
}

class PersonalTab : public QDialog
{
    Q_OBJECT

public:
    explicit PersonalTab(QWidget *parent = nullptr);
    ~PersonalTab();
    void defaultNextcloudTheme();
    void makeCustomButton(int amount);
private:
    Ui::PersonalTab *ui;
    void fiuTheme();
    void beigeTheme(int amount);
    void darkTheme(int amount);
    void blueTheme(int amount);
};

#endif // PERSONALTAB_H
