#ifndef DELEGATES_H
#define DELEGATES_H

#include <QStyledItemDelegate>
#include "language.h"
#include "table.h"
#include "configuration.h"
#include "common.h"
#include <QLineEdit>
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QApplication>


class ItemValidacaoDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    ItemValidacaoDelegate(QObject *pai = 0);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

};

class ItemDoubleSpinBoxDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    ItemDoubleSpinBoxDelegate(QObject *pai = 0);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

class ItemComboBoxDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
        ItemComboBoxDelegate(QObject *pai = 0);
        QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
        void setEditorData(QWidget *editor, const QModelIndex &index) const;
        void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
        void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
private:
        QStringList lista;

};
#endif // DELEGATES_H
