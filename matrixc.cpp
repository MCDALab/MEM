#include "matrixc.h"
#include "ui_matrixc.h"
#include "delegates.h"
#include <QDebug>

MatrixC::MatrixC(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MatrixC)
{
    ui->setupUi(this);
    ui->matrixC->setItemDelegateForColumn(1, new ItemDoubleSpinBoxDelegate());
    ui->mirror->setText(Language::language("mirroring"));
    ui->next->setText(Language::language("next"));
    ui->btnCancel->setText(Language::language("cancel"));
    ui->btnClean->setText(Language::language("clean"));
}

MatrixC::~MatrixC()
{
    delete ui;
}

void MatrixC::setMainMatrixC(QStandardItemModel *model)
{
    matrixC = model;
}

void MatrixC::setModel(QStandardItemModel *model)
{
    ui->matrixC->setModel(model);
    this->model = model;
    //QObject::connect(model,&QStandardItemModel::itemChanged,this,&MatrixC::updateRow);
    connect(model, SIGNAL(itemChanged(QStandardItem*)), this, SLOT(updateRow(QStandardItem*)));
}

void MatrixC::setModelNext(QStandardItemModel *model)
{
    this->modelNext = model;
    //QObject::connect(model,&QStandardItemModel::itemChanged,this,&MatrixC::updateRow);
    connect(model, SIGNAL(itemChanged(QStandardItem*)), this, SLOT(updateRow(QStandardItem*)));
}

void MatrixC::setMirror(bool value)
{
    ui->mirror->setChecked(value);
}

void MatrixC::updateRow(QStandardItem *item)
{

    int colCount = matrixC->columnCount(), index = item->index().row(), col, row;
    for( int i = 0, k = 0; i < colCount; i++ )
    {
        for( int j = i+1; j < colCount; j++, k++ )
        if( k == index )
        {
            col = j;
            row = i;
        }
    }

    QModelIndexList list;


    if( ui->matrixC->model() == modelNext )
    {
        int aux = row;
        row = col;
        col = aux;
    }

    const QModelIndex& idxActual = matrixC->index(row, col);
    list << idxActual;
    if( ui->mirror->isChecked() )
    {
        const QModelIndex& idxMirror = matrixC->index(col, row);
        list << idxMirror;
    }

    emit valueTableChanged(matrixC,list, item->index().data().toString());
}

void MatrixC::on_next_clicked()
{
    if( ui->matrixC->model() == model )
    {
        ui->matrixC->setModel(modelNext);
        ui->next->setText(Language::language("prev"));
    }
    else
    {
        ui->matrixC->setModel(model);
        ui->next->setText(Language::language("next"));
    }
}

void MatrixC::on_btnClean_clicked()
{
    int colCount = matrixC->columnCount();

    QModelIndexList list;

    for( int i = 0; i < colCount; i++ )
        for( int j = 0; j < colCount; j++ )
            if( i != j )
                list << matrixC->index(i, j);

    for( int i = 0, k = 0; i < colCount; i++ )
    {
        for( int j = i+1; j < colCount; j++, k++ )
        {
            model->setData(model->index(k,1), "");
            modelNext->setData(modelNext->index(k,1), "");
        }
    }

    emit valueTableChanged(matrixC,list, "");
}
