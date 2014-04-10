#ifndef FINDTABLE_H
#define FINDTABLE_H

#include <QWidget>
#include <QToolButton>
#include <QComboBox>
#include <QTableView>
#include <QStandardItemModel>
#include <QKeyEvent>
#include <QLabel>
#include <QCheckBox>

#include "common.h"
#include "language.h"

class FindTable : public QWidget
{
    Q_OBJECT
signals:
    void valueTableChanged(QAbstractItemModel *model, const QModelIndexList &listOld, const QString &strew) const;
public:

    explicit FindTable(QWidget *parent = 0);
    void setCloseButton( QToolButton *btn );
    void setFindButton( QToolButton *btn );
    void setNextButton( QToolButton *btn );
    void setPrevButton( QToolButton *btn );
    void setFindComboBox( QComboBox *cbx );
    void setInformationLabel( QLabel *label );
    void setSelectAllCheckbox( QCheckBox *ckb );

    void setReplaceComboBox( QComboBox *cbx );
    void setReplaceButton( QToolButton *btn );
    void setFindComboBox(QComboBox *cbx, QValidator *v);
    void setTableForSearch( QTableView *t );
    bool findModeSelect();

signals:

public slots:
    void find();
    void replace();
    void clearFoundList();
protected:
    void keyPressEvent( QKeyEvent* event );

private:
    QToolButton *btnClose;
    QToolButton *btnFind;
    QToolButton *btnNext;
    QToolButton *btnPrev;
    QComboBox *cbxFind;
    QLabel *lblInformation;
    QCheckBox *ckbSelectAll;

    /* REPLACE */
    QToolButton *btnReplace;
    QComboBox *cbxReplace;
    QTableView *table;
    int directionFind;
    QModelIndexList foundList;
    int indexFind;
    QString lastFind;
    QTableView *lastTable;
    void findModelIndexList();

};

#endif // FINDTABLE_H
