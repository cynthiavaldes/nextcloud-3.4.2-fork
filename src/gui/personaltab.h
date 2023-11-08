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
private:
    Ui::PersonalTab *ui;
    
};

#endif // PERSONALTAB_H
