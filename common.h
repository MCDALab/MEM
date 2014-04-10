#ifndef COMMON_H
#define COMMON_H

class Language;

#define HEADERTABLE( table, position,  orientation ) table->horizontalHeader()->model()->headerData(position, orientation).toString()
#define DELIMITATION ","

#define COUNTROW(table) table->model()->rowCount()
#define COUNTCOL(table) table->model()->columnCount()

#define ALTERFINDTABLE(index) ui->tableFindValue->setTableForSearch(qobject_cast<Table *>(ui->tabWidget->widget(index)->children().at(1)))

#define ALTERLANGUAGE(field, texto) field->setText(Language::language(texto)); \
    if(Language::language(texto"_tooltip").isEmpty()) field->setToolTip(Language::language(texto)); else field->setToolTip(Language::language(texto"_tooltip"));

#define ALTERLANGUAGEMENU(menu, texto) menu->setTitle(Language::language(texto)); \
    if(Language::language(texto"_tooltip").isEmpty()) menu->setToolTip(Language::language(texto)); else menu->setToolTip(Language::language(texto"_tooltip"));

#define CAST_MODEL(table) static_cast<QStandardItemModel *>(table->model())

#define MAX(x, y) (x > y) ? x : y
#define MIN(x, y) (x < y) ? x : y

#define floatFormat(x,c) QString::number(x, 'f', c)

#include <QList>
#include <QDebug>
#include <QtGui>

#define TR(x) QObject::tr("%1").arg(x)
qreal normal( QList<qreal> list );


void combinations(int n, int c, int combs[] , int size, QStandardItemModel *model);
void comb(int n, int r, int *arr, int sz, QStandardItemModel *model, int row, int col);

#endif // COMMON_H
