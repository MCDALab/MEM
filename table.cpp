#include "table.h"

Table::Table(QWidget *pai) : QTableView(pai)
{
    //connect( verticalHeader(), &QHeaderView::sectionPressed, this, &Table::rowSelected );
    connect(verticalHeader(), SIGNAL(sectionPressed(int)), this, SLOT(rowSelected(int)));
    connect(verticalHeader(), SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(customMenuContextVerticalHeader(QPoint)));

    connect(horizontalHeader(), SIGNAL(sectionPressed(int)), this, SLOT(columnSelected(int)));
    connect(horizontalHeader(), SIGNAL(customContextMenuRequested(QPoint)),SLOT(customMenuContextHorizontalHeader(QPoint)));

    horizontalHeader()->setContextMenuPolicy(Qt::CustomContextMenu);

    verticalHeader()->setContextMenuPolicy(Qt::CustomContextMenu);

    menu = new QMenu(this);
    actExport = new QAction(QIcon(":/imagens/table_exports.png"), Language::language("export_table"), this);
    actImport = new QAction(QIcon(":/imagens/table_imports.png"), Language::language("import_table"), this);
    actClear = new QAction(QIcon(":/imagens/table_select.png"), "Limpar", this);
    QAction *separator = new QAction(this);
    separator->setSeparator(true);
    QList<QAction *> list;
    list << actExport << actImport << separator << actClear;
    menu->insertActions(NULL,list);
    connect(actExport, SIGNAL(triggered()), this, SLOT(exportFileMEM()));
    connect(actClear, SIGNAL(triggered()), this, SLOT(clearSelect()));

    menuHeaderHorizontal = new QMenu(this->horizontalHeader());
    colSelected = -1;
    rSelected = -1;
    cMirror = false;
    mirror = false;

    menuHeaderVertical = new QMenu(verticalHeader());
}

void Table::commitData(QWidget *editor)
{

    QString value;

    if(QLineEdit *edit = qobject_cast<QLineEdit *>(editor) )
    {
        value = edit->text();
    }
    else if( QSpinBox *spb = qobject_cast<QSpinBox *>(editor) )
    {
        value = TR(spb->value());
    }
    else if( QDoubleSpinBox *spb = qobject_cast<QDoubleSpinBox *>(editor) )
    {
        value = TR(spb->value());
    }
    else if( QComboBox *cbx = qobject_cast<QComboBox *>(editor) )
    {
        value = TR(cbx->currentIndex());
    }
    if( value.isEmpty() )
        return;

    if( value == selectionModel()->selectedIndexes().at(0).data().toString() )
        return;

    if( mirror )
    {
        const QModelIndex& idxActual = model()->index(currentIndex().row(), currentIndex().column());
        const QModelIndex& idxMirror = model()->index(currentIndex().column(), currentIndex().row());

        QModelIndexList list;

        list << idxActual << idxMirror;

        emit valueTableChanged(model(),list, value);
    }
    else if( selectionModel()->selectedIndexes().size() > 0 )
    {
        emit valueTableChanged(model(),selectionModel()->selectedIndexes(), value);
    }
    QTableView::commitData(editor);
}


void Table::contextMenuEvent ( QContextMenuEvent * e )
{
    if( model()->rowCount() == 0 && model()->columnCount() == 0 )
        actExport->setEnabled(false);
    else
        actExport->setEnabled(true);

    menu->exec(QCursor::pos());
}

void Table::setMirror(bool value)
{
    mirror = value;
}

void Table::customMenuContextHorizontalHeader(QPoint pos)
{
    int column=this->horizontalHeader()->logicalIndexAt(pos);

    selectColumn(column);
    columnSelected(column);

    menuHeaderHorizontal->exec(QCursor::pos());
}

void Table::customMenuContextVerticalHeader(QPoint pos)
{
    int row = verticalHeader()->logicalIndexAt(pos);
    selectRow(row);
    rowSelected(row);
    menuHeaderVertical->exec(QCursor::pos());
}


void Table::exportFileMEM()
{
    QString fileName = QFileDialog::getSaveFileName(this,Language::language("save_file"), "C:\\", tr("%1 csv(*.csv)").arg(Language::language("file")));

    if( fileName.isNull() )
        return;

    QFile fileExport(fileName);
    if (fileExport.open(QIODevice::WriteOnly | QIODevice::Text)){

        int rowCount = this->model()->rowCount();
        int colCount = this->model()->columnCount();

        QStringList listaCriterios;

        for(int i = 0; i < colCount; i++ ) listaCriterios << HEADERTABLE(this, i, Qt::Horizontal);

        QModelIndex indice;
        QString result;
        result += DELIMITATION+listaCriterios.join(DELIMITATION)+"\n";
        for( int i = 0; i < rowCount; i++ )
        {
            result += HEADERTABLE(this, i, Qt::Vertical)+DELIMITATION;
            for( int j = 0; j < colCount; j++ )
            {
                indice = model()->index(i,j);
                result += indice.data().toString();
                if(j != colCount-1)
                    result += DELIMITATION;
            }
            result += "\n";
        }
        QTextStream out(&fileExport);
        out << result;
        fileExport.close();
    }
}

QAction * Table::actionImportFile()
{
    return actImport;
}

void Table::canMirror(bool value)
{
    if( value )
    {
        actMirror = new QAction(QIcon(":/imagens/table_mirror.png"), Language::language("mirroring"), this);
        actMirror->setCheckable(true);
        actMirror->setChecked(true);
        menu->insertSeparator(actImport);
        menu->insertAction(actImport, actMirror);
        connect( actMirror, SIGNAL(triggered(bool)), this, SLOT(setMirror(bool)) );
    }
    else
    {
        disconnect( actMirror, SIGNAL(triggered(bool)), this, SLOT(setMirror(bool)) );
        menu->removeAction(actMirror);
        delete actMirror;
    }
    cMirror = value;
}

bool Table::hasMirror()
{
    return cMirror;
}

bool Table::hasImport()
{
    return cImport;
}

void Table::canImport(bool value)
{
    if( value )
    {
        actImport = new QAction(QIcon(":/imagens/table_imports.png"), Language::language("import_table"), this);
        menu->insertAction(actExport, actImport);
    }
    else
    {
        menu->removeAction(actImport);
        delete actImport;
    }
    cImport = value;
}

bool Table::importFileMEM()
{
    QString fileName = QFileDialog::getOpenFileName(this, Language::language("open_file"), QString(), tr("%1 csv(*.csv)").arg(Language::language("file")));
    if( fileName.isNull() )
        return false;

    QFile fileImport(fileName);

    QString line;

    QStringList listCriterias;
    QStringList listAlternatives;

    QStandardItemModel *model =new QStandardItemModel();
    if (fileImport.open(QFile::ReadOnly)) {
          line = fileImport.readLine(200);
          listCriterias = line.simplified().split(DELIMITATION);
          listCriterias.removeAt(0);
          model->setHorizontalHeaderLabels(listCriterias);

          int row=0;
          QStandardItem *item=0;
          QStringList list;
          while(fileImport.canReadLine()){
                line = fileImport.readLine();
                if(line.contains(DELIMITATION)){
                      list = line.simplified().split(DELIMITATION);
                      listAlternatives.append(list.first());
                      for(int col=0; col<list.length()-1; col++){
                            item = new QStandardItem(list.at(col+1));
                            model->setItem(row ,col, item);
                      }
                      row++;
                }
          }

          model->setVerticalHeaderLabels(listAlternatives);
          fileImport.close();
          setModel(model);

          return true;
    }
    return false;
}

QList<qreal> Table::values()
{
    int rowCount = COUNTROW(this);
    int colCount = COUNTCOL(this);
    QList<qreal> list;

    for( int i = 0; i < rowCount; i++ )
    {
        for( int j = 0; j < colCount; j++)
        {
            list << model()->index(i,j).data().toFloat();
        }
    }
    return list;
}

QStringList Table::valuesHeader(Qt::Orientation orientation)
{
    int rowCount = COUNTROW(this);
    int colCount = COUNTCOL(this);

    QStringList list;
    if( orientation == Qt::Horizontal )
    {
        for(int i = 0; i < colCount; i++)
        {
            list << HEADERTABLE(this, i, orientation);
        }
    }else
    {
        for(int i = 0; i < rowCount; i++)
        {
            list << HEADERTABLE(this, i, orientation);
        }
    }
    return list;
}

float Table::searchMaxValueTable(QAbstractItemModel *model, int position, Qt::Orientation orientation)
{
    if( orientation == Qt::Vertical )
    {
        float max = 0;
        float tmp = 0;
        for( int i = 0; i < model->rowCount(); i++ )
        {
            tmp = model->index(i,position).data().toFloat();
            if( tmp > max )
                max = tmp;
        }
        return max;
    }
    else
    {
        float max = 0;
        float tmp = 0;
        for( int i = 0; i < model->columnCount(); i++ )
        {
            tmp = model->index(position,i).data().toFloat();
            if( tmp > max )
                max = tmp;
        }
        return max;
    }

}

float Table::searchMinValueTable(QAbstractItemModel *model, int position, Qt::Orientation orientation)
{
    if( orientation == Qt::Vertical )
    {
        float min = (float)INT_MAX;
        float tmp = 0;
        for( int i = 0; i < model->rowCount(); i++ )
        {
            tmp = model->index(i,position).data().toFloat();
            if( tmp < min )
                min = tmp;
        }
        return min;
    }
    else
    {
        float min = (float)INT_MAX;
        float tmp = 0;
        for( int i = 0; i < model->columnCount(); i++ )
        {
            tmp = model->index(position,i).data().toFloat();
            if( tmp > min )
                min = tmp;
        }
        return min;
    }
}

float Table::searchMaxValueTable( int position, Qt::Orientation orientation)
{
    return searchMaxValueTable(CAST_MODEL(this), position, orientation);
}

float Table::searchMinValueTable(int position, Qt::Orientation orientation)
{
    return searchMinValueTable(CAST_MODEL(this), position, orientation);
}

void Table::clearSelect()
{
    emit valueTableChanged(model(),selectionModel()->selectedIndexes(), "");
}

void Table::columnSelected(int col)
{
    colSelected = col;
}

void Table::rowSelected(int row)
{
    rSelected = row;
}

int Table::selectedRow()
{
    return rSelected;
}

int Table::selectedColumn()
{
    return colSelected;
}

int Table::countFindValue(QStandardItemModel *model, qreal value, int position, Qt::Orientation orientation)
{
    if( orientation == Qt::Vertical )
    {
        qreal tmp;
        int count = 0;
        for( int i = 0; i < model->rowCount(); i++ )
        {
            tmp = model->index(i,position).data().toFloat();
            if( tmp == value )
                count++;
        }
        return count;
    }
    else
    {
        qreal tmp;
        int count = 0;
        for( int i = 0; i < model->columnCount(); i++ )
        {
            tmp = model->index(position,i).data().toFloat();
            if( tmp == value )
                count++;
        }
        return count;
    }
}

int Table::countFindValue(qreal value, int position , Qt::Orientation orientation)
{
    return countFindValue(CAST_MODEL(this), value, position, orientation);
}

void Table::copyTableValues(QAbstractItemModel *src, QAbstractItemModel *dst, int idxInsert, Qt::Orientation orientation)
{
    if( src == NULL || dst == NULL )
        return;
    int rowCount = src->rowCount();
    int colCount = src->columnCount();
    QStandardItemModel *s = static_cast<QStandardItemModel *>(src);
    QStandardItemModel *d = static_cast<QStandardItemModel *>(dst);

    for( int i = 0; i < rowCount; i++ )
    {
        for( int j = 0; j < colCount; j++ )
        {
            if( !s->index(i,j).data().toString().isEmpty() )
            {
                if( orientation == Qt::Horizontal  )
                    d->setItem((i < idxInsert || idxInsert == -1 ? i : (i + 1)),j, new QStandardItem(s->index(i,j).data().toString()));
                else
                {
                    d->setItem(i ,(j < idxInsert || idxInsert == -1 ? j : (j + 1)), new QStandardItem(s->index(i,j).data().toString()));
                }
            }
        }
    }
}

void Table::copyTableValues(QAbstractItemModel *dst, int idxInsert, Qt::Orientation orientation)
{
    copyTableValues(model(), dst, idxInsert, orientation);
}

void Table::copyTableValuesMirror(QAbstractItemModel *dst, int idxInsert)
{

    if( model() == NULL || dst == NULL )
        return;
    int rowCount = model()->rowCount();
    int colCount = model()->columnCount();
    QStandardItemModel *s = static_cast<QStandardItemModel *>(model());
    QStandardItemModel *d = static_cast<QStandardItemModel *>(dst);

    for( int i = 0; i < rowCount; i++ )
    {
        for( int j = 0; j < colCount; j++ )
        {
            if( !s->index(i,j).data().toString().isEmpty() )
            {
                    d->setItem((i < idxInsert || idxInsert == -1 ? i : (i + 1)),(j < idxInsert || idxInsert == -1 ? j : (j + 1)), new QStandardItem(s->index(i,j).data().toString()));
            }
        }
    }

}

QMenu * Table::menuVertical()
{
    return menuHeaderVertical;
}

void Table::setMenuVertical(QMenu *menu)
{
    menuHeaderVertical = menu;
}

QMenu * Table::menuHorizontal()
{
    return menuHeaderHorizontal;
}

void Table::setMenuHorizontal(QMenu *menu)
{
    menuHeaderHorizontal = menu;
}


