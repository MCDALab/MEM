#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <QDialog>
#include <QMenu>
#include <QMenuBar>
#include "language.h"
#include "configuration.h"
#include <QFileDialog>
#include <QMessageBox>
#include "customplot/qcustomplot.h"

namespace Ui {
    class Graphic;
}

class Graphic : public QDialog
{
       Q_OBJECT

public:
    explicit Graphic(QWidget *parent = 0);
    ~Graphic();

    Ui::Graphic * getUi() { return ui; }

private slots:
    void saveImage();
    void savePdf();
private:
    Ui::Graphic *ui;

    QAction *actImage;
    QAction *actPdf;
};


#endif // GRAPHIC_H
