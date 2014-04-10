#include "about.h"
#include "ui_about.h"

About::About(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::About)
{
    ui->setupUi(this);
    setWindowFlags(Qt::WindowTitleHint | Qt::CustomizeWindowHint );
}

About::~About()
{
    delete ui;
}

void About::mousePressEvent(QMouseEvent *e)
{
    if( childAt(e->pos()) )
    {
        QWidget::mousePressEvent(e);
    }
    else
    {
        close();
    }

}
