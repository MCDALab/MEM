#include "findtable.h"

FindTable::FindTable(QWidget *parent) :
    QWidget(parent)
{
    directionFind = 1;
    indexFind = -1;
    lastTable = NULL;
}

void FindTable::setCloseButton(QToolButton *btn)
{
    btnClose = btn;
    connect( btn, SIGNAL(clicked()), this, SLOT(hide()));
}

void FindTable::setFindButton(QToolButton *btn)
{
    btnFind = btn;
    connect( btn, SIGNAL(clicked()), this, SLOT(find()));
}

void FindTable::setNextButton(QToolButton *btn)
{
    btnNext = btn;
    btnNext->setObjectName("forward");
    connect( btn, SIGNAL(clicked()), this, SLOT(find()));
}

void FindTable::setPrevButton(QToolButton *btn)
{
    btnPrev = btn;
    btnPrev->setObjectName("backward");
    connect( btn, SIGNAL(clicked()), this, SLOT(find()));
}

void FindTable::setFindComboBox(QComboBox *cbx)
{
    cbxFind = cbx;
}

void FindTable::setFindComboBox(QComboBox *cbx, QValidator *v)
{
    setFindComboBox(cbx);
    cbxFind->setValidator(v);
}

void FindTable::setInformationLabel(QLabel *label)
{
    lblInformation = label;
    label->setVisible(false);
}

void FindTable::setSelectAllCheckbox(QCheckBox *ckb)
{
    ckbSelectAll = ckb;
}

void FindTable::setReplaceButton(QToolButton *btn)
{
    btnReplace = btn;
    connect( btn, SIGNAL(clicked()), this, SLOT(replace()));
}

void FindTable::setReplaceComboBox(QComboBox *cbx)
{
    cbxReplace = cbx;
}


void FindTable::setTableForSearch(QTableView *t)
{

    if( lastTable != NULL )
    {
        connect(lastTable->model(), SIGNAL(dataChanged(QModelIndex,QModelIndex)), SLOT(clearFoundList()));
        lastTable = table;
    }
    table = t;
    QStandardItemModel *model = static_cast<QStandardItemModel *>(t->model());
    if(model == NULL)
    {
        this->setEnabled(false);
        return;
    }
    else if( model->rowCount() == 0 && model->columnCount() == 0 )
    {
        this->setEnabled(false);
        connect(t->model(), SIGNAL(dataChanged(QModelIndex,QModelIndex)), SLOT(clearFoundList()));
    }
    else
    {
        this->setEnabled(true);
        cbxFind->setFocus();
        if( !table->selectionModel()->selectedIndexes().isEmpty() )
        {
            table->update();
            QString findValue = table->selectionModel()->selectedIndexes().first().data().toString();
            int textIndex = cbxFind->findText( findValue );
            if( textIndex != 0 )
            {
                if( textIndex > -1 )
                {
                    cbxFind->removeItem( textIndex );
                }
                cbxFind->insertItem( 0, findValue );
                cbxFind->setCurrentIndex(0);
            }
            else
            {
                cbxFind->insertItem(0 , findValue);
            }
        }
        clearFoundList();

    }
}


void FindTable::keyPressEvent(QKeyEvent *event)
{
    if( event->key() == Qt::Key_Return )
    {
        if( cbxFind->hasFocus() )
            find();
        else if( cbxReplace->hasFocus() )
            replace();
    }
    else
        QWidget::keyPressEvent( event );
}

void FindTable::find()
{
    findModelIndexList();

    lblInformation->setVisible(true);
    if( foundList.isEmpty() )
    {
        lblInformation->setText(tr(Language::language("table_result_not_found_info").toStdString().c_str()).arg(lastFind));
        return;
    }

    if( ckbSelectAll->isChecked() )
    {
        for( int i = 0; i < foundList.size(); i++ )
            table->selectionModel()->select(foundList.at(i), QItemSelectionModel::Select);
        return;
    }

    if( sender() )
    {
        if( sender()->objectName() == "forward" )
            directionFind = 1;
        else if( sender()->objectName() == "backward" )
            directionFind = -1;
    }

    indexFind += directionFind;
    if( indexFind >= foundList.size() )
        indexFind = 0;
    else if( indexFind < 0 )
        indexFind = foundList.size()-1;

    lblInformation->setText(tr(Language::language("table_result_find_info").toStdString().c_str()).arg(indexFind+1).arg(foundList.size()).arg(lastFind));

    table->selectionModel()->clear();
    table->selectionModel()->select(foundList.at(indexFind), QItemSelectionModel::Select);
    table->scrollTo(foundList.at(indexFind));
}

void FindTable::findModelIndexList()
{
    QString findValue = cbxFind->currentText();

    if( findValue.isEmpty() )
        return;

    if( lastFind != findValue )
    {
        lastFind = findValue;
        foundList.clear();

        int rowCount = COUNTROW(table);
        int colCount = COUNTCOL(table);

        int textIndex = cbxFind->findText( findValue );
        if( textIndex != 0 )
        {
            if( textIndex > -1 )
            {
                cbxFind->removeItem( textIndex );
            }
            cbxFind->insertItem( 0, findValue );
            cbxFind->setCurrentIndex(0);
        }


        QPoint init(0,0);

        if( !table->selectionModel()->selection().indexes().isEmpty() )
        {
            init.setX(table->selectionModel()->selection().indexes().first().column());
            init.setY(table->selectionModel()->selection().indexes().first().row());
        }

        int loopRow = rowCount;
        int loopCol = colCount;
        int lastLoopCol = 0;
        int i = init.y();
        int j = init.x();
        bool invert = false;

        while(i < loopRow)
        {
            while(j <  loopCol)
            {
                if( table->model()->index(i,j).data().toFloat() == findValue.toFloat() )
                {
                    foundList << table->model()->index(i,j);
                }
                if( i+1 == loopRow && j+1 == loopCol && !invert)
                {
                    if( init.y() > 0 )
                        loopRow = init.y() + 1;
                    else
                        loopRow = init.y();
                    //loopCol = init.x();
                    lastLoopCol = init.x();
                    i = -1;
                    j = 0;
                    invert = true;
                    break;
                }
                if( (i + 1 == loopRow) && invert && lastLoopCol )
                {
                    loopCol = lastLoopCol-1;
                }
                j++;
            }
            j = 0;
            i++;
        }
        indexFind = -1;

    }
}

bool FindTable::findModeSelect()
{
    return ckbSelectAll->isChecked();
}

void FindTable::clearFoundList()
{
    foundList.clear();
    lastFind = "";
    indexFind = -1;
}

void FindTable::replace()
{

    QString replaceValue = cbxReplace->currentText();
    if( replaceValue == lastFind )
    {
        cbxReplace->setFocus();
        return;
    }

    if( foundList.isEmpty() )
    {
        if( cbxFind->currentText().isEmpty() )
        {
            cbxFind->setFocus();
            return;
        }
        find();
        if( foundList.isEmpty() )
            return;
    }


    QModelIndexList list;
    if( ckbSelectAll->isChecked() )
    {

        emit valueTableChanged(table->model(), foundList, replaceValue);
        for( int i = 0; i < foundList.size(); i++ )
        {
            table->model()->setData(foundList.at(i), replaceValue);
        }
        foundList.clear();

        return;
    }

    QModelIndex index = foundList.at(indexFind);

    list << index;
    emit valueTableChanged(table->model(), list, replaceValue);

    table->selectionModel()->clear();
    table->selectionModel()->select(index, QItemSelectionModel::Select);
    table->model()->setData(index, replaceValue);

    foundList.removeAt(indexFind);

    if( indexFind == foundList.size() )
        indexFind--;
}
