#ifndef STUDENTRESOURCES_H
#define STUDENTRESOURCES_H

#include <QDialog>

namespace Ui {
class StudentResources;
}

class StudentResources : public QDialog
{
    Q_OBJECT

public:
    explicit StudentResources(QWidget *parent = nullptr);
    ~StudentResources();

private:
    Ui::StudentResources *ui;
    void MyFiuLink();
    void MailLink();
    void CalendarLink();
    void CanvasLink();
};

#endif // STUDENTRESOURCES_H

