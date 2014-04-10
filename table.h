#ifndef TABELARELACIONAMENTO_H
#define TABELARELACIONAMENTO_H

#include <QTableView>
#include <QHeaderView>
#include <QMenu>
#include <QLineEdit>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QComboBox>
#include <QFileDialog>
#include "common.h"
#include "language.h"


class Table : public QTableView
{
    //enum { Insert, Copy } Copy ;
    Q_OBJECT
signals:
    void valueTableChanged(QAbstractItemModel *model, const QModelIndexList &listOld, const QString &strew) const;
public slots:
    void setMirror(bool value);
    void customMenuContextHorizontalHeader(QPoint pos);
    void customMenuContextVerticalHeader(QPoint pos);
    void exportFileMEM();
    bool importFileMEM();
    void clearSelect();
    void columnSelected(int col);
    void rowSelected(int row);
public:
    explicit Table(QWidget *pai = 0);
    void contextMenuEvent(QContextMenuEvent *event);
    QAction *actionImportFile();
    QAction *actionInsertNewColumn();
    QAction *actionEditColumn();
    QAction *actionRemoveColumn();
    bool hasMirror();
    bool hasImport();
    void canMirror( bool value);
    void canImport( bool value );
    int selectedColumn();
    int selectedRow();

    QList<qreal> values();
    QStringList valuesHeader( Qt::Orientation orientation = Qt::Horizontal );


    static float searchMaxValueTable( QAbstractItemModel *model, int position = 0, Qt::Orientation orientation = Qt::Vertical );
    static float searchMinValueTable( QAbstractItemModel *model, int position = 0, Qt::Orientation orientation = Qt::Vertical );

    float searchMaxValueTable(int position = 0, Qt::Orientation orientation = Qt::Vertical );
    float searchMinValueTable(int position = 0, Qt::Orientation orientation = Qt::Vertical );

    void copyTableValues( QAbstractItemModel *src, QAbstractItemModel *dst, int idxInsert = 0, Qt::Orientation orientation = Qt::Horizontal );
    void copyTableValues( QAbstractItemModel *dst, int idxInsert = 0, Qt::Orientation orientation = Qt::Horizontal );
    void copyTableValuesMirror( QAbstractItemModel *dst, int idxInsert = -1);


    static int countFindValue( QStandardItemModel *model, qreal value, int position, Qt::Orientation orientation = Qt::Horizontal );
    int countFindValue( qreal value, int position, Qt::Orientation orientation = Qt::Horizontal );

    QMenu* menuVertical();
    void setMenuVertical( QMenu* menu );

    QMenu* menuHorizontal();
    void setMenuHorizontal( QMenu* menu );


protected Q_SLOTS:
    void commitData(QWidget *editor);
protected:
    bool mirror;
    bool cMirror;
    bool cImport;
    QMenu *menu;
    QAction *actExport;
    QAction *actImport;
    QAction *actMirror;
    QAction *actClear;

    QMenu *menuHeaderHorizontal;

    QMenu *menuHeaderVertical;

    int colSelected;
    int rSelected;
};


#endif // TABELARELACIONAMENTO_H
