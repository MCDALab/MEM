#ifndef ABOUT_H
#define ABOUT_H

#include <QDialog>
#include <QMouseEvent>

namespace Ui {
    class About;
}

class About : public QDialog
{
    Q_OBJECT

public:
    explicit About(QWidget *parent = 0);
    ~About();
protected:
    void mousePressEvent(QMouseEvent *e);
private:
    Ui::About *ui;
};

#endif // ABOUT_H
