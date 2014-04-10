#ifndef UNDOCOMMANDS_H
#define UNDOCOMMANDS_H

#include <QUndoCommand>
#include <QStandardItemModel>
#include "table.h"
#include "configuration.h"
class UndoUpdateValue : public QUndoCommand
{
public:
    UndoUpdateValue( QAbstractItemModel *model,  const QModelIndexList &list, QString value , QUndoCommand *parent = 0);
    UndoUpdateValue( QAbstractItemModel *model,  const QModelIndex &index, QString value , QUndoCommand *parent = 0);
    void undo();
    void redo();

private:
    QStandardItemModel *model;
    QModelIndexList listIndex;
    QString newValue;
    QStringList oldList;
};

class UndoUpdateModel : public QUndoCommand
{
public:
    UndoUpdateModel( const QList<Table *> &listTable, const QList<QStandardItemModel *> &listOldModel, const QList<QStandardItemModel *> &listNewModel, QUndoCommand *parent = 0 );
    UndoUpdateModel( Table *table, QStandardItemModel* oldModel, QStandardItemModel *newModel, QUndoCommand *parent = 0 );
    void undo();
    void redo();
private:
    QList<QStandardItemModel *> listOldModel, listNewModel;
    QList<Table *> listTable;
};

class UndoUpdateVerticalHeader : public QUndoCommand
{
public:
    UndoUpdateVerticalHeader( QStandardItemModel *model, int index, const QString& oldStr, const QString& newStr, QUndoCommand *parent = 0 );
    void undo();
    void redo();

private:
    QStandardItemModel *model;
    QString newStr, oldStr;
    int index;
};

#endif // UNDOCOMMANDS_H
