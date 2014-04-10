#include "undocommands.h"
#include "QDebug"

UndoUpdateValue::UndoUpdateValue(QAbstractItemModel *model, const QModelIndexList &list, QString value, QUndoCommand *parent) : QUndoCommand(parent)
{
    this->model = static_cast<QStandardItemModel *>(model);
    listIndex = list;
    this->newValue = value;
    foreach( QModelIndex index, list )
        oldList << index.data().toString();
}

UndoUpdateValue::UndoUpdateValue(QAbstractItemModel *model, const QModelIndex &index, QString value, QUndoCommand *parent) : QUndoCommand(parent)
{
    QModelIndexList list;
    list << index;
    ::UndoUpdateValue(model, list, value, parent);
}

void UndoUpdateValue::undo()
{
    int i = 0;
    foreach(QModelIndex index, listIndex)
    {
        model->setData(index, floatFormat(oldList.at(i).toDouble(),Configuration::configuration("precision").toInt()));
        i++;
    }
}

void UndoUpdateValue::redo()
{
    foreach(QModelIndex index, listIndex)
    {
        model->setData(index, floatFormat(newValue.toDouble(),Configuration::configuration("precision").toInt()));
    }
}

UndoUpdateModel::UndoUpdateModel(const QList<Table *> &listTable, const QList<QStandardItemModel *> &listOldModel, const QList<QStandardItemModel *> &listNewModel, QUndoCommand *parent)
    : QUndoCommand(parent)
{
    this->listTable = listTable;
    this->listNewModel = listNewModel;
    this->listOldModel = listOldModel;
}

UndoUpdateModel::UndoUpdateModel(Table *table, QStandardItemModel *oldModel, QStandardItemModel *newModel, QUndoCommand *parent)
    : QUndoCommand(parent)
{
    listTable << table;
    listOldModel << oldModel;
    listNewModel << newModel;
}

void UndoUpdateModel::undo()
{
    int i = 0;
    foreach( Table *table, listTable )
    {
        table->setModel(listOldModel[i]);
        i++;
    }
}

void UndoUpdateModel::redo()
{
    int i = 0;
    foreach( Table *table, listTable )
    {
        table->setModel(listNewModel[i]);
        i++;
    }
}

UndoUpdateVerticalHeader::UndoUpdateVerticalHeader(QStandardItemModel *model, int index, const QString &oldStr, const QString &newStr, QUndoCommand *parent) : QUndoCommand(parent)
{
    this->model = model;
    this->oldStr = oldStr;
    this->newStr = newStr;
    this->index = index;
}

void UndoUpdateVerticalHeader::undo()
{
    model->verticalHeaderItem(index)->setText(oldStr);
}

void UndoUpdateVerticalHeader::redo()
{
    model->verticalHeaderItem(index)->setText(newStr);
}
