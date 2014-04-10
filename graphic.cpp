#include "graphic.h"
#include "ui_graphic.h"
#include <QMainWindow>
#include <QVBoxLayout>

Graphic::Graphic(QWidget *parent):
    QDialog(parent),
    ui(new Ui::Graphic)
{
    setContextMenuPolicy(Qt::DefaultContextMenu);

    ui->setupUi(this);
    QMenuBar *menuBar = new QMenuBar(this);
    menuBar->setMaximumHeight(21);
    QVBoxLayout *lay = new QVBoxLayout(this);
    lay->setContentsMargins(0, 0, 0, 0);
    lay->setSpacing(0);
    QMenu *menu = new QMenu(Language::language("export"),this);
    lay->addWidget(menuBar);
    lay->addWidget(ui->customPlot);
    menuBar->addMenu(menu);

    actImage = new QAction(Language::language("image"),this);
    connect(actImage, SIGNAL(triggered()), this, SLOT(saveImage()));
    menu->addAction(actImage);

    actPdf = new QAction(Language::language("pdf"),this);
    connect(actPdf, SIGNAL(triggered()), this, SLOT(savePdf()));
    menu->addAction(actPdf);
}

Graphic::~Graphic()
{
    delete ui;
}

void Graphic::saveImage()
{
    QPixmap pm = QPixmap::grabWidget(this, ui->customPlot->x()+2, ui->customPlot->y()+2, ui->customPlot->width()-4, ui->customPlot->height()-4);
    QString save = QFileDialog::getSaveFileName(this,Language::language("save_as"),QString(),Configuration::configuration("formats_save_img"));
    if( !save.isEmpty() )
    {
        const char *format = save.split(".").last().toStdString().c_str();
        QMessageBox::information(this,Language::language("title"),pm.save(save,format) ? Language::language("save_img_success") : Language::language("save_img_error"));
    }
}

void Graphic::savePdf()
{
    QString save = QFileDialog::getSaveFileName(this,Language::language("save_as"),QString(),"PDF (*.pdf)");
    if( !save.isEmpty() )
    {
        QMessageBox::information(this,Language::language("title"),ui->customPlot->savePdf(save) ? Language::language("save_img_success") : Language::language("save_img_error"));
    }
}
