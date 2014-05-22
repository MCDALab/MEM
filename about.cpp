#include "about.h"
#include "ui_about.h"

About::About(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::About)
{
    ui->setupUi(this);
    setWindowFlags(Qt::WindowTitleHint | Qt::CustomizeWindowHint );
    ui->lblContact->setText(Language::language("contact"));
    ui->lblContactLink->setText("<html><head/><body><p><a href=\""+Language::language("contact_link")+"\"><span style=\" text-decoration: underline; color:#0000ff;\">"+Language::language("contact_link")+"</span></a></p></body></html>");
    ui->lblLicense->setText(Language::language("license"));
    ui->lblVersion->setText(Language::language("version"));
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
