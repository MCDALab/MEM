#ifndef MATRIXC_H
#define MATRIXC_H

#include <QDialog>
#include <QStandardItemModel>
#include "language.h"

namespace Ui {
class MatrixC;
}

class MatrixC : public QDialog
{
    Q_OBJECT
signals:
    void valueTableChanged(QAbstractItemModel *model, const QModelIndexList &listOld, const QString &strew) const;
public:
    explicit MatrixC(QWidget *parent = 0);
    ~MatrixC();

     Ui::MatrixC *getUi() { return ui; }

     void setMainMatrixC( QStandardItemModel *model );
     void setModel( QStandardItemModel *model );
     void setModelNext( QStandardItemModel *model );

     void setMirror( bool value );

private slots:
     void updateRow(QStandardItem *item);

     void on_next_clicked();

     void on_btnClean_clicked();

private:
    Ui::MatrixC *ui;
    QStandardItemModel *matrixC;
    QStandardItemModel *model;
    QStandardItemModel *modelNext;
};

#endif // MATRIXC_H
