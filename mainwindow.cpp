#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QTextCodec* codec = QTextCodec::codecForName("CP1256");
    QTextCodec::setCodecForLocale(codec);
    ui->setupUi(this);


    qDebug() << tr("????");
    qDebug() << codec->toUnicode("????");


    QSettings::setDefaultFormat( QSettings::IniFormat );


    tableMatrixALine = NULL;
    tableMatrixBLine = NULL;
    tableResultRelative = NULL;


    setWindowFilePath(QString());


    ui->tableFindValue->setVisible(false);
    ui->tableFindValue->setCloseButton(ui->btnFindClose);
    ui->tableFindValue->setNextButton(ui->btnFindNext);
    ui->tableFindValue->setPrevButton(ui->btnFindPrev);
    ui->tableFindValue->setFindButton(ui->btnFind);
    ui->tableFindValue->setFindComboBox(ui->cbxFind);
    ui->tableFindValue->setInformationLabel(ui->lblInfomation);
    ui->tableFindValue->setSelectAllCheckbox(ui->ckbSelectAll);
    ui->tableFindValue->setReplaceButton(ui->btnReplace);
    ui->tableFindValue->setReplaceComboBox(ui->cbxReplace);
    ui->tableFindValue->setTableForSearch(ui->tableMatrixPayment);

    ui->mainToolBar->setMovable(false);

    ui->tableMatrixPayment->setItemDelegate(new ItemValidacaoDelegate());
    ui->tableMatrixRelationship->setItemDelegate(new ItemDoubleSpinBoxDelegate());
    ui->tableMatrixWeight->setItemDelegateForRow(0,new ItemDoubleSpinBoxDelegate());
    ui->tableMatrixRelationship->canMirror(true);
    ui->tableMatrixRelationship->setMirror(true);


    ui->tableMatrixWeight->setItemDelegateForRow(1,new ItemComboBoxDelegate());

    ui->tableMatrixPayment->setModel(new QStandardItemModel());
    ui->tableMatrixWeight->setModel(new QStandardItemModel());
    ui->tableMatrixRelationship->setModel(new QStandardItemModel());

    connect(ui->tableMatrixPayment->actionImportFile(), SIGNAL(triggered()), this, SLOT(importPaymentFileMEM()));

    connect(ui->tableMatrixPayment, SIGNAL(valueTableChanged(QAbstractItemModel*,QModelIndexList,QString)), this, SLOT(updateValueTable(QAbstractItemModel*,QModelIndexList,QString)));
    connect(ui->tableMatrixRelationship, SIGNAL(valueTableChanged(QAbstractItemModel*,QModelIndexList,QString)), this, SLOT(updateValueTable(QAbstractItemModel*,QModelIndexList,QString)));
    connect(ui->tableMatrixWeight, SIGNAL(valueTableChanged(QAbstractItemModel*,QModelIndexList,QString)), this, SLOT(updateValueTable(QAbstractItemModel*,QModelIndexList,QString)));
    connect(ui->tableFindValue, SIGNAL(valueTableChanged(QAbstractItemModel*,QModelIndexList,QString)), this, SLOT(updateValueTable(QAbstractItemModel*,QModelIndexList,QString)));


    QActionGroup* group = new QActionGroup(this);
    ui->actPortuguese->setActionGroup(group);
    ui->actEnglish->setActionGroup(group);
    ui->actEspanish->setActionGroup(group);
    ui->actFrench->setActionGroup(group);
    Criteria = NULL;
    CriteriaEdit = NULL;
    Alternative = NULL;
    Build = NULL;

    stackCommands = new QUndoStack(this);
    connect(stackCommands, SIGNAL(indexChanged(int)), this, SLOT(alterationChanged(int)));

    ui->mainToolBar->insertSeparator(NULL);
    QAction *actUndo = stackCommands->createUndoAction(this);
    actUndo->setIcon(QIcon(":/imagens/undo_32.png"));
    actUndo->setShortcut(QKeySequence::Undo);

    QAction *actRedo = stackCommands->createRedoAction(this);
    actRedo->setIcon(QIcon(":/imagens/redo_32.png"));
    actRedo->setShortcut(QKeySequence::Redo);

    ui->mainToolBar->insertAction(NULL, actUndo);
    ui->mainToolBar->insertAction(NULL, actRedo);

    lastSaveAlterationValue = 0;
    path = QString();

    ui->actSave->setEnabled(false);

    ui->tableMatrixPayment->setMenuVertical(ui->menuAlternative);
    ui->tableMatrixPayment->setMenuHorizontal(ui->menuCriteria);

    ui->tableMatrixRelationship->setMenuHorizontal(ui->menuCriteria);
    ui->tableMatrixRelationship->setMenuVertical(ui->menuAlternative);

    ui->tableMatrixWeight->setMenuHorizontal(ui->menuCriteria);
    ui->tableMatrixWeight->setMenuVertical(ui->menuAlternative);

    for (int i = 0; i < MaxRecentFiles; ++i) {
        recentFileActs[i] = new QAction(this);
        recentFileActs[i]->setVisible(false);
        recentFileActs[i]->setEnabled(false);
        recentFileActs[i]->setShortcut(tr( "Ctrl+R+%1" ).arg(i+1));
        connect(recentFileActs[i], SIGNAL(triggered()),
                this, SLOT(openRecentFile()));
    }
    recentFilesMenu = new QMenu(Language::language("recent_files"),this);
    ui->menuArquivos->insertMenu(ui->actOpenMenu, recentFilesMenu);

    actNone = new QAction(Language::language("recent_files"),this);
    recentFilesMenu->addAction(actNone);
    for (int i = 0; i < MaxRecentFiles; ++i)
    {
        recentFilesMenu->addAction(recentFileActs[i]);
    }
    updateRecentFileActions();

    ui->actEditAlternative->setEnabled(false);
    ui->actDeleteAlternative->setEnabled(false);

    ui->actEditCriteria->setEnabled(false);
    ui->actDeleteCriteria->setEnabled(false);

    ui->actBuild->setEnabled(false);

    enableSave(false);
    enableTable(false);
    enableMatrixC(false);

    ui->actGraphResult->setEnabled(false);

    tableResult = new Table();
    tableResult->canImport(false);
    //QAction *act = new QAction(Language::language("show_graphic"),this);
    tableResult->menuVertical()->insertAction(NULL,ui->actGraphResult);

    //connect(ui->actGraphResult, SIGNAL(triggered()), this, SLOT(on_actGraphResult_triggered()));

    statusProgressBar = new QProgressBar(this);
    statusProgressBar->setMaximumWidth(150);
    ui->statusBar->addPermanentWidget(statusProgressBar);

    statusProgressBar->setEnabled(false);

    readConfiguration();
    readLanguage(Configuration::configuration("language"));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setWindowTitle(const QString &title)
{
    if( path.isEmpty() )
        QMainWindow::setWindowTitle(title);
    else
        QMainWindow::setWindowTitle(title + " - " + QDir::toNativeSeparators(path));
}

void MainWindow::enableSave(bool value)
{
    ui->actSave->setEnabled(value);
    ui->actSaveMenu->setEnabled(value);
}

void MainWindow::enableTable(bool value)
{
    ui->tabWidget->setEnabled(value);
}

void MainWindow::enableMatrixC(bool value)
{
    ui->actMatrixC->setEnabled(value);
    ui->actMatrixCMenu->setEnabled(value);
}

void MainWindow::matrixB(int k,
                         const qreal &tau ,
                         const int &rowCount,
                         const int &colCount,
                         QStandardItemModel *model,
                         QStandardItemModel *modelResult,
                         bool progress)
{
    QStandardItemModel *modelWeights = CAST_MODEL(ui->tableMatrixWeight);
    QStandardItemModel *modelComp = CAST_MODEL(ui->tableMatrixRelationship);
    QStringList listHorizontal;
    QStringList listVertical;

    model->clear();
    modelResult->clear();

    QStandardItemModel *modelA = CAST_MODEL(tableMatrixALine);
    for( int i = 0; i < colCount; i++ )
        listHorizontal << modelA->horizontalHeaderItem(i)->text();

    QStringList listOrdenateHorizontal = ordenateStringList(listHorizontal, k);
    model->setHorizontalHeaderLabels(listOrdenateHorizontal);
    for( int i = 0; i < rowCount; i++ )
    {
        listVertical << modelA->verticalHeaderItem(i)->text();
    }

    int precision = Configuration::configuration("precision").toInt();

    QStringList listOrdenateVertical = ordenateStringList(listVertical, k);
    model->setVerticalHeaderLabels(listOrdenateVertical);

    modelResult->setVerticalHeaderLabels(listOrdenateVertical);
    modelResult->setHorizontalHeaderLabels(listOrdenateHorizontal);

    if( progress )
    {
        statusProgressBar->setEnabled(true);
        statusProgressBar->setValue(0);
        statusProgressBar->setRange(0, listOrdenateHorizontal.count() * listOrdenateVertical.count());
    }

    std::string h_mask( k, 1 );
    int j = 0, l = 0, pRow = 0, pRowAux = 0, pCol = 0;
    h_mask.resize(listHorizontal.size(), 0);
    std::string v_mask( k, 1 );
    v_mask.resize(listVertical.size(), 0);
    int init = 0;

    do
    {
        QList<qreal> listCol, listWeight, listComp;
        l = 0;
        for( int i = 0; i < listHorizontal.size(); ++i )
        {
            if( h_mask[i] )
            {
                listCol << i;
            }
        }
        for( int i = 0 ; i < listCol.size() ; i++ )
        {
            for( int j = 0; j < listCol.size(); j++ )
            {
                if( i != j )
                {
                    listComp << modelComp->index(listCol.at(i),listCol.at(j)).data().toFloat();
                }
            }
        }
        do
        {
            QList<qreal> listRow;
            for( int i = 0, a = 0; i < listVertical.size(); ++i )
            {
                if( v_mask[i] )
                {
                    foreach( qreal pos, listCol )
                    {
                        listRow << modelA->index(i,pos).data().toFloat();
                    }
                    ++a;
                }
            }
            foreach( qreal pos, listCol )
            {
                listWeight << modelWeights->index(0,pos).data().toFloat();
            }
            qreal calc = normal(listRow)*normal(listWeight)*normal(listComp);
            model->setData(model->index(pRow, pCol), floatFormat(calc, precision));
            model->item(pRow, pCol)->setEditable(false);
            modelResult->setData(modelResult->index(pRow, pCol), floatFormat((calc <= tau ? 0 : 1 ),precision));
            modelResult->item(pRow, pCol)->setEditable(false);
            listRow.clear();
            listWeight.clear();
            qApp->processEvents();

            l++;
            pRow++;
            pRowAux++;

            if( progress ) statusProgressBar->setValue(statusProgressBar->value() + 1);

        }while(std::prev_permutation(v_mask.begin(), v_mask.end()));

        listCol.clear();
        listComp.clear();
        pRow = 0;
        pCol++;
        init++;
        j++;
    }while(std::prev_permutation(h_mask.begin(), h_mask.end()));
    if( progress )
    {
        statusProgressBar->setValue(statusProgressBar->value() + 1);
        statusProgressBar->setEnabled(false);
    }
}


void MainWindow::alterationChanged(int index)
{
    if( index != lastSaveAlterationValue )
    {
        setWindowTitle("* "+Language::language("title"));
        enableSave(true);
    }
    else
    {
        setWindowTitle(Language::language("title"));
        enableSave(false);
    }
}

void MainWindow::importPaymentFileMEM()
{
    if( ui->tableMatrixPayment->importFileMEM() )
    {
        int colCount = ui->tableMatrixPayment->model()->columnCount();

        QStandardItemModel *modelActual = static_cast<QStandardItemModel *>(ui->tableMatrixPayment->model());

        QStringList list;
        for( int i = 0; i < colCount; i++ )
            list << modelActual->horizontalHeaderItem(i)->text();

        if( colCount > 0 )
            ui->actEditCriteria->setEnabled(true);

        QStandardItemModel *modelRelationship = new QStandardItemModel;
        modelRelationship->setHorizontalHeaderLabels(list);
        modelRelationship->setVerticalHeaderLabels(list);

        QStandardItem *itemAux;
        for( int i = 0; i < list.size(); i++ )
        {
          itemAux = new QStandardItem("0");
          itemAux->setEditable(false);
          modelRelationship->setItem(i,i,itemAux);
        }

        if( list.size() > 0 )
        {
            ui->actEditAlternative->setEnabled(true);
        }

        if( modelRelationship->columnCount() > 0 )
        {
            enableMatrixC(true);
        }
        else
        {
            enableMatrixC(false);
        }

        ui->tableMatrixRelationship->setModel(modelRelationship);

        QStandardItemModel *modelWeight = new QStandardItemModel;
        modelWeight->setHorizontalHeaderLabels(list);
        list.clear();
        list << Language::language("weight") << Language::language("preference");
        modelWeight->setVerticalHeaderLabels(list);
        ui->tableMatrixWeight->setModel(modelWeight);
    }
}

void MainWindow::readConfiguration()
{
    Configuration::loadConfiguration();

    if( Configuration::configuration("language") == "pt-BR" )
        ui->actPortuguese->setChecked(true);
    else if(Configuration::configuration("language") == "en" )
        ui->actEnglish->setChecked(true);
    else if(Configuration::configuration("language") == "es" )
        ui->actEspanish->setChecked(true);
    else if( Configuration::configuration("language") == "fr" )
        ui->actFrench->setChecked(true);

}

void MainWindow::on_actNew_triggered()
{
    if( saveFileQuestion() )
    {
        enableTable(true);
        ui->tableMatrixPayment->setModel(new QStandardItemModel());
        ui->tableMatrixRelationship->setModel(new QStandardItemModel());
        ui->tableMatrixWeight->setModel(new QStandardItemModel());
        for( int i = 0; i < ui->tabWidget->count(); i++ )
            ui->tabWidget->removeTab(3);

        stackCommands->clear();
        path = QString();
        setWindowTitle(Language::language("title"));
        recentFileActs[0]->setEnabled(true);
        enableMatrixC(false);
    }
}

void MainWindow::on_actOpen_triggered()
{
    openFileMEM(QString());
}

void MainWindow::openFileMEM(const QString &fileName)
{
    MEM *mem = new MEM;
    if( fileName.isEmpty() )
    {
        if( !mem->read(this) )
            return;
    }
    else
    {
        if( !mem->readFileName(this, fileName) )
            return;
    }

    QStandardItemModel *modelPay = new QStandardItemModel();//static_cast<QStandardItemModel *>(ui->tableMatrixPayment->model());
    QStandardItemModel *modelWeights = new QStandardItemModel();//static_cast<QStandardItemModel *>(ui->tableMatrixWeight->model());
    QStandardItemModel *modelComp = new QStandardItemModel();//static_cast<QStandardItemModel *>(ui->tableMatrixRelationship->model());

    modelPay->setHorizontalHeaderLabels(mem->criterias());
    modelPay->setVerticalHeaderLabels(mem->alternatives());

    int rowCount = modelPay->rowCount();
    int colCount = modelPay->columnCount();

    QList<qreal> payment = mem->payment();
    for( int i = 0, k = 0; i < rowCount; i++ )
    {
        for( int j = 0; j < colCount; j++ )
        {
            modelPay->setItem(i,j, new QStandardItem( floatFormat(payment.at(k),Configuration::configuration("precision").toFloat())));
            k++;
        }
    }

    if( colCount > 0 )
    {
        ui->actEditCriteria->setEnabled(true);
        enableMatrixC(true);
    }

    if( rowCount > 0)
        ui->actEditAlternative->setEnabled(true);


    modelWeights->setHorizontalHeaderLabels(mem->criterias());
    QStringList list;
    modelWeights->setVerticalHeaderLabels(list);

    QList<qreal> weights = mem->weight();
    int k = 0;
    for( int i = 0; i < colCount; i++ )
    {
        modelWeights->setItem(0,i, new QStandardItem( floatFormat(weights.at(k),Configuration::configuration("precision").toInt())));
        k++;

    }

    for( int i = 0; i < colCount; i++ )
    {
        modelWeights->setItem(1,i, new QStandardItem( tr("%1").arg(weights.at(k)) ) );
        k++;
    }


    modelComp->setHorizontalHeaderLabels(mem->criterias());
    modelComp->setVerticalHeaderLabels(mem->criterias());


    QStandardItem *itemAux;
    QList<qreal> comp = mem->complementarity();
    for( int i = 0, k = 0; i < colCount; i++ )
    {
        for( int j = 0; j < colCount; j++ )
        {
            if( i == j )
            {
              itemAux = new QStandardItem("0");
              itemAux->setEditable(false);
              modelComp->setItem(i,i,itemAux);
            }
            else
            {
                modelComp->setItem(i,j, new QStandardItem( floatFormat(comp.at(k),Configuration::configuration("precision").toInt())));
            }
            k++;
        }
    }
    // Insere os valores recuperados do arquivo em suas respectivas tabelas.
    ui->tableMatrixPayment->setModel(modelPay);
    ui->tableMatrixWeight->setModel(modelWeights);
    ui->tableMatrixRelationship->setModel(modelComp);

    // Limpa configurações.
    //path = mem->path();
    stackCommands->clear();
    lastSaveAlterationValue = 0;

    setCurrentFile(mem->path());
    recentFileActs[0]->setEnabled(false);

    ui->actBuild->setEnabled(true);
    //ui->actTableClean->setEnabled(true);

    enableSave(false);
    enableTable(true);

    if( ui->tabWidget->count() >= 4 )
    {
        closeTabResult();
    }

    ui->tabWidget->setCurrentIndex(0);
}

void MainWindow::on_actSave_triggered()
{
    MEM *mem = new MEM;
    mem->setAlternatives(ui->tableMatrixPayment->valuesHeader(Qt::Vertical));
    mem->setCriterias(ui->tableMatrixPayment->valuesHeader());
    mem->setPayment(ui->tableMatrixPayment->values());
    mem->setWeight(ui->tableMatrixWeight->values());
    mem->setComplementarity(ui->tableMatrixRelationship->values());
    if( path.isEmpty() )
        mem->writeAs(this);
    else
        mem->write(this, path);
    lastSaveAlterationValue = stackCommands->index();
    path = mem->path();
    enableSave(false);
    //exportFileMEM(ui->tableMatrixPayment);
}
void MainWindow::readLanguage(QString trad)
{  
    Language::loadLanguage(trad);
    setWindowTitle(Language::language("title"));

    ALTERLANGUAGE(ui->actOpen, "open");
    ALTERLANGUAGE(ui->actClose,"close");
    ALTERLANGUAGE(ui->actEnglish,"english");
    ALTERLANGUAGE(ui->actPortuguese,"portuguese");
    ALTERLANGUAGE(ui->actEspanish,"spanish");
    ALTERLANGUAGE(ui->actFrench,"franch");
    ALTERLANGUAGE(ui->actSave,"save");
    ALTERLANGUAGE(ui->actConfiguration,"configuration");
    ALTERLANGUAGE(ui->actMirror,"mirroring");
    ALTERLANGUAGE(ui->actAbout,"about");
    ALTERLANGUAGE(ui->actHelp,"help");
    ALTERLANGUAGE(ui->actAddCriteria,"add_criteria_title");
    ALTERLANGUAGE(ui->actAddAlternative,"add_alternative_title");
    ALTERLANGUAGE(ui->actSensibilityGraphic,"menu_sensibility_graphic");
    ALTERLANGUAGE(ui->actNew, "new");
    ALTERLANGUAGE(ui->actNewMenu,"new");
    ALTERLANGUAGE(ui->actOpenMenu,"open");
    ALTERLANGUAGE(ui->actOpen,"open");
    ALTERLANGUAGE(ui->actSave,"save");
    ALTERLANGUAGE(ui->actSaveMenu,"save");
    ALTERLANGUAGE(ui->actFindInTable,"find");
    ALTERLANGUAGE(ui->actReplaceTable,"replace");
    ALTERLANGUAGE(ui->actAddAlternative,"add_alternative_title");
    ALTERLANGUAGE(ui->actAddAlternativeMenu,"add_alternative_title");
    ALTERLANGUAGE(ui->actAddCriteria,"add_criteria_title");
    ALTERLANGUAGE(ui->actAddCriteriaMenu,"add_criteria_title");

    ALTERLANGUAGE(ui->actDeleteAlternative,"delete_alternative_title");
    ALTERLANGUAGE(ui->actDeleteCriteria,"delete_criteria_title");

    ALTERLANGUAGE(ui->actEditAlternative,"edit_alternative_title");
    ALTERLANGUAGE(ui->actEditCriteria,"edit_criteria_title");

    ALTERLANGUAGE(ui->actMatrixALine,"matrix_a_line");
    ALTERLANGUAGE(ui->actMatrixBLine,"matrix_b_line");
    ALTERLANGUAGE(ui->actResultRelative,"partial_result");

    ALTERLANGUAGE(ui->actBuild,"build");

    ALTERLANGUAGE(ui->actMatrixC,"matrix_c");
    ALTERLANGUAGE(ui->actMatrixCMenu,"matrix_c");


    ALTERLANGUAGE(ui->actGraphResult, "menu_graphic_performace");

    ALTERLANGUAGEMENU(ui->menuArquivos,"files");
    ALTERLANGUAGEMENU(ui->menuLinguagem,"language");
    ALTERLANGUAGEMENU(ui->menuEdit,"edit");
    ALTERLANGUAGEMENU(ui->menuAbout,"about");    
    ALTERLANGUAGEMENU(ui->menuGraphics,"graphics");
    ALTERLANGUAGEMENU(ui->menuTabela,"table");

    ALTERLANGUAGEMENU(ui->menuCriteria,"criteria");
    ALTERLANGUAGEMENU(ui->menuAlternative,"alternative");

    ALTERLANGUAGEMENU(recentFilesMenu,"recent_files");

    ui->tabWidget->setTabText(0, Language::language("matrix_payment"));
    ui->tabWidget->setTabText(1, Language::language("matrix_weight"));
    ui->tabWidget->setTabText(2, Language::language("matrix_relationship"));
    if( ui->tabWidget->count() >= 4 )
    {
        ui->tabWidget->setTabText(3, Language::language("result"));
    }
}

void MainWindow::on_actPortuguese_triggered()
{
    readLanguage("pt-BR");
}

void MainWindow::on_actEnglish_triggered()
{
    readLanguage("en");
}

void MainWindow::on_actEspanish_triggered()
{
    readLanguage("es");
}

void MainWindow::on_actFrench_triggered()
{
    readLanguage("fr");
}

void MainWindow::on_actConfiguration_triggered()
{
    setEnabledActions(false);
    readConfiguration();

    Configurator = new Ui_Configurator();
    window = new QDialog(this);
    Configurator->setupUi(window);
    Configurator->bntCancel->setText(Language::language("cancel"));
    Configurator->btnApply->setText(Language::language("apply"));
    Configurator->lblLanguage->setText(Language::language("language"));
    Configurator->gbxConfiguration->setTitle(Language::language("configuration"));
    Configurator->cbxLanguage->setItemText(0,Language::language("portuguese"));
    Configurator->cbxLanguage->setItemText(1,Language::language("english"));
    Configurator->cbxLanguage->setItemText(2,Language::language("spanish"));
    Configurator->cbxLanguage->setItemText(3, Language::language("franch"));
    Configurator->spbPrecision->setValue(Configuration::configuration("precision").toInt());


    if( Configuration::configuration("language") == "pt-BR" )
        Configurator->cbxLanguage->setCurrentIndex(0);
    else if( Configuration::configuration("language") == "en" )
        Configurator->cbxLanguage->setCurrentIndex(1);
    else if( Configuration::configuration("language") == "es" )
        Configurator->cbxLanguage->setCurrentIndex(2);
    else if( Configuration::configuration("language") == "fr" )
        Configurator->cbxLanguage->setCurrentIndex(3);

    connect(Configurator->btnApply, SIGNAL(clicked()), this,SLOT(writerConfiguration()));
    connect(Configurator->btnApply, SIGNAL(clicked()),window, SLOT(close()));
    connect(window,SIGNAL(finished(int)), this, SLOT(closeConfigurator()));

    window->setWindowTitle(Language::language("configuration"));

    window->show();
}


void MainWindow::closeConfigurator()
{
    setEnabledActions(true);
    disconnect(Configurator->btnApply, SIGNAL(clicked()), this,SLOT(writerConfiguration()));
    disconnect(Configurator->btnApply, SIGNAL(clicked()),window, SLOT(close()));
    disconnect(window,SIGNAL(finished(int)), this, SLOT(closeConfigurator()));
    window = NULL;
    Configurator = NULL;
}

void MainWindow::writerConfiguration()
{
    QSettings settings (QCoreApplication::applicationDirPath()+"/conf.ini", QSettings::IniFormat );
    settings.beginGroup("configuration");

    QString lang;
    switch(Configurator->cbxLanguage->currentIndex())
    {
        case 0: lang = "pt-BR"; break;
        case 1: lang = "en"; break;
        case 2: lang = "es"; break;
        case 3: lang = "fr"; break;
    }
    settings.setValue("language", lang);
    settings.setValue("precision", Configurator->spbPrecision->value());

    readConfiguration();
    readLanguage(Configuration::configuration("language"));
}


/* Referente a critérios */
void MainWindow::on_actAddCriteria_triggered()
{
    setEnabledActions(false);
    Criteria = new Ui_Criteria;
    window = new QDialog(this);
    Criteria->setupUi(window);
    window->setWindowTitle(Language::language("add_criteria_title"));
    Criteria->btnAdd->setText(Language::language("add"));
    Criteria->btnCancel->setText(Language::language("cancel"));
    Criteria->lblNameCriteria->setText(Language::language("name_criteria"));
    Criteria->lblWeight->setText(Language::language("weight"));
    Criteria->lblPreference->setText(Language::language("preference"));
    Criteria->cbxPreference->setItemText(0,Language::language("growing"));
    Criteria->cbxPreference->setItemText(1,Language::language("decreasing"));

    connect(Criteria->btnAdd, SIGNAL(clicked()), this, SLOT(addNewCriteria()));
    connect(Criteria->sldWeight, SIGNAL(valueChanged(int)), this, SLOT(slideCriteriaWeight(int)) );
    connect(window, SIGNAL(finished(int)), this, SLOT(closeWindowCriteria()));
    ALTERFINDTABLE(ui->tabWidget->currentIndex());

    ui->actAddCriteria->setEnabled(false);


    window->show();
}

void MainWindow::closeWindowCriteria()
{
    setEnabledActions(true);
    disconnect(Criteria->btnAdd, SIGNAL(clicked()), this, SLOT(addNewCriteria()));
    disconnect(window, SIGNAL(finished(int)), this, SLOT(closeWindowCriteria()));
    disconnect(Criteria->sldWeight, SIGNAL(valueChanged(int)), this, SLOT(slideCriteriaWeight(int)) );
    ui->actAddCriteria->setEnabled(true);
    window = NULL;
    Criteria = NULL;
}

void MainWindow::slideCriteriaWeight(int weight)
{
    if( Criteria != NULL )
        Criteria->lblWeightResult->setText(tr("%1").arg((qreal)weight/100));
    else if( CriteriaEdit != NULL )
        CriteriaEdit->lblWeightResult->setText(tr("%1").arg((qreal)weight/100));
}

void MainWindow::addNewCriteria()
{
    if( Criteria->edtNomeCriterio->text().isEmpty())
    {
        QMessageBox::information(this, Language::language("add_criteria_title"), Language::language("message_null_value_criteria"));
        Criteria->edtNomeCriterio->setFocus();
        return;
    }


    int rowCount = ui->tableMatrixPayment->model()->rowCount();
    int colCount = ui->tableMatrixPayment->model()->columnCount();
    QStandardItemModel *model = new QStandardItemModel();
    QStandardItemModel *modelActual = static_cast<QStandardItemModel *>(ui->tableMatrixPayment->model());

    QStringList lista;
    QString str;
    for( int i = 0; i < colCount; i++ )
    {
        str = modelActual->horizontalHeaderItem(i)->text();
        if( str == Criteria->edtNomeCriterio->text() )
        {

            Criteria->edtNomeCriterio->setText("");
            Criteria->edtNomeCriterio->setFocus();
            QMessageBox::information(this, Language::language("add_criteria_title"), Language::language("message_existing_criteria"));
            return;
        }
        if( i == ui->tableMatrixPayment->selectedColumn() )
            lista << Criteria->edtNomeCriterio->text();

        lista << str;
    }

    if( ui->tableMatrixPayment->selectedColumn() == -1)
        lista << Criteria->edtNomeCriterio->text();

    model->setHorizontalHeaderLabels(lista);

    QStandardItemModel *modelRelationship = new QStandardItemModel;
    modelRelationship->setHorizontalHeaderLabels(lista);
    modelRelationship->setVerticalHeaderLabels(lista);

    // Preenche linhas e colunas da tabela em que houver algum valor
    ui->tableMatrixRelationship->copyTableValuesMirror( modelRelationship, ui->tableMatrixPayment->selectedColumn());
    QStandardItem *itemAux;

    for( int i = 0; i < lista.size(); i++ )
    {
        itemAux = new QStandardItem("0");
        itemAux->setEditable(false);
        modelRelationship->setItem(i,i,itemAux);
    }

    if( lista.size() > 0 )
        enableMatrixC(true);

    //ui->tableMatrixRelationship->setModel(modelRelationship);

    QStandardItemModel *modelWeight = new QStandardItemModel;
    modelWeight->setHorizontalHeaderLabels(lista);

    lista.clear();
    lista << Language::language("weight") << Language::language("preference");
    modelWeight->setVerticalHeaderLabels(lista);
    ui->tableMatrixWeight->copyTableValues(modelWeight, ui->tableMatrixPayment->selectedColumn(), Qt::Vertical);
    itemAux = new QStandardItem(Criteria->lblWeightResult->text());
    int selCol = ui->tableMatrixPayment->selectedColumn() == -1 ? colCount : ui->tableMatrixPayment->selectedColumn();
    modelWeight->setItem(0, selCol, itemAux);

    itemAux = new QStandardItem(tr("%1").arg(Criteria->cbxPreference->currentIndex()));
    modelWeight->setItem(1, selCol, itemAux);

    lista.clear();
    for( int i = 0; i < rowCount; i++ )
        lista << modelActual->verticalHeaderItem(i)->text();


    model->setVerticalHeaderLabels(lista);
    // Preenche linhas e colunas da tabela em que houver algum valor
    ui->tableMatrixPayment->copyTableValues( model, ui->tableMatrixPayment->selectedColumn(), Qt::Vertical);

    QList<QStandardItemModel *> listNew;
    listNew << model << modelWeight << modelRelationship;
    QList<QStandardItemModel *> listOld;
    listOld << modelActual << static_cast<QStandardItemModel *>(ui->tableMatrixWeight->model()) << static_cast<QStandardItemModel *>(ui->tableMatrixRelationship->model());
    QList<Table *> listTable;
    listTable << ui->tableMatrixPayment << ui->tableMatrixWeight << ui->tableMatrixRelationship;
    stackCommands->push(new UndoUpdateModel(listTable, listOld, listNew));

    Criteria->edtNomeCriterio->setText("");
    Criteria->edtNomeCriterio->setFocus();
    Criteria->sldWeight->setValue(0);
    Criteria->cbxPreference->setCurrentIndex(0);
    ui->tableMatrixPayment->columnSelected(-1);
    ALTERFINDTABLE(ui->tabWidget->currentIndex());

    ui->actEditCriteria->setEnabled(true);
    ui->actDeleteCriteria->setEnabled(true);

    if( rowCount >= 1 )
    {
        ui->actBuild->setEnabled(true);
        enableTable(true);
    }
}

/* Referente a edição de critérios. */

void MainWindow::on_actEditCriteria_triggered()
{
    setEnabledActions(false);
    CriteriaEdit = new Ui_criteriaEdit;
    window = new QDialog(this);
    CriteriaEdit->setupUi(window);

    QStandardItemModel *modelActual = static_cast<QStandardItemModel *>(ui->tableMatrixPayment->model());
    int colCount = modelActual->columnCount();
    QString str;
    for( int i = 0; i < colCount; i++ )
    {
        str = modelActual->horizontalHeaderItem(i)->text();
        CriteriaEdit->cbxCriteria->insertItem(i,str);
    }


    window->setWindowTitle(Language::language("add_criteria_title"));
    CriteriaEdit->btnUpdate->setText(Language::language("atualizar"));
    CriteriaEdit->btnCancel->setText(Language::language("cancel"));
    CriteriaEdit->lblNameCriteria->setText(Language::language("name_criteria"));
    CriteriaEdit->lblWeight->setText(Language::language("weight"));
    CriteriaEdit->lblPreference->setText(Language::language("preference"));
    CriteriaEdit->cbxPreference->setItemText(0,Language::language("growing"));
    CriteriaEdit->cbxPreference->setItemText(1,Language::language("decreasing"));

    connect(CriteriaEdit->cbxCriteria, SIGNAL(currentIndexChanged(int)), this, SLOT(currentCriteriaChanged(int)));
    connect(CriteriaEdit->btnUpdate, SIGNAL(clicked()), this, SLOT(criteriaEditChanged()));
    connect(CriteriaEdit->sldWeight, SIGNAL(valueChanged(int)), this, SLOT(slideCriteriaWeight(int)) );
    connect(window, SIGNAL(finished(int)), this, SLOT(closeWindowCriteriaEdit()));

    int selCol = ui->tableMatrixPayment->selectedColumn() == -1 ? 0 : ui->tableMatrixPayment->selectedColumn();
    currentCriteriaChanged(selCol);
    CriteriaEdit->cbxCriteria->setCurrentIndex(selCol);

    window->show();
}

void MainWindow::currentCriteriaChanged(int index)
{
    QStandardItemModel *modelActual = static_cast<QStandardItemModel *>(ui->tableMatrixWeight->model());
    QString str = modelActual->horizontalHeaderItem(index)->text();
    CriteriaEdit->edtNomeCriterio->setText(str);
    qreal weight = modelActual->index(0,index).data().toFloat() * 100;
    CriteriaEdit->sldWeight->setValue(weight);
    int preference = modelActual->index(1, index).data().toInt();
    CriteriaEdit->cbxPreference->setCurrentIndex(preference);
}

void MainWindow::criteriaEditChanged()
{

    if( CriteriaEdit->edtNomeCriterio->text().isEmpty())
    {
        QMessageBox::information(this, Language::language("add_criteria_title"), Language::language("message_null_value_criteria"));
        Criteria->edtNomeCriterio->setFocus();
        return;
    }

    QStandardItemModel *modelActual = static_cast<QStandardItemModel *>(ui->tableMatrixPayment->model());

    QString str;
    int colCount = modelActual->columnCount();
    for( int i = 0; i < colCount; i++ )
    {
        str = modelActual->horizontalHeaderItem(i)->text();
        if( str == CriteriaEdit->edtNomeCriterio->text() )
        {

            CriteriaEdit->edtNomeCriterio->setText("");
            CriteriaEdit->edtNomeCriterio->setFocus();
            QMessageBox::information(this, Language::language("add_criteria_title"), Language::language("message_existing_criteria"));
            return;
        }
    }

    int index = CriteriaEdit->cbxCriteria->currentIndex();
    str = CriteriaEdit->edtNomeCriterio->text();
    modelActual->horizontalHeaderItem(index)->setText(str);
    modelActual = static_cast<QStandardItemModel *>(ui->tableMatrixWeight->model());
    modelActual->horizontalHeaderItem(index)->setText(str);
    modelActual->setItem(0, index, new QStandardItem(TR(CriteriaEdit->lblWeightResult->text().toFloat())));
    modelActual->setItem(1, index, new QStandardItem(TR(CriteriaEdit->cbxPreference->currentIndex())));

    modelActual = static_cast<QStandardItemModel *>(ui->tableMatrixRelationship->model());
    modelActual->horizontalHeaderItem(index)->setText(str);
}


void MainWindow::closeWindowCriteriaEdit()
{
    setEnabledActions(true);
    disconnect(CriteriaEdit->cbxCriteria, SIGNAL(currentIndexChanged(int)), this, SLOT(currentCriteriaChanged(int)));
    disconnect(CriteriaEdit->btnUpdate, SIGNAL(clicked()), this, SLOT(criteriaEditChanged()));
    disconnect(CriteriaEdit->sldWeight, SIGNAL(valueChanged(int)), this, SLOT(slideCriteriaWeight(int)) );
    disconnect(window, SIGNAL(finished(int)), this, SLOT(closeWindowCriteriaEdit()));
}

/* Referente a remoção critério */

void MainWindow::on_actDeleteCriteria_triggered()
{
    int selCol = ui->tableMatrixPayment->selectedColumn() == -1 ? 0 : ui->tableMatrixPayment->selectedColumn();
    if( selCol != 0 )
    {
        criteriaRemove();
        return;
    }
    setEnabledActions(false);
    CriteriaRemove = new Ui_criteriaRemove;
    window = new QDialog(this);
    CriteriaRemove->setupUi(window);

    QStandardItemModel *modelActual = static_cast<QStandardItemModel *>(ui->tableMatrixPayment->model());
    int colCount = modelActual->columnCount();
    QString str;
    for( int i = 0; i < colCount; i++ )
    {
        str = modelActual->horizontalHeaderItem(i)->text();
        CriteriaRemove->cbxCriteria->insertItem(i,str);
    }

    connect(CriteriaRemove->btnUpdate, SIGNAL(clicked()), this, SLOT(criteriaRemove()));
    connect(CriteriaRemove->btnUpdate, SIGNAL(clicked()), window, SLOT(close()));
    connect(window, SIGNAL(finished(int)), this, SLOT(closeWindowCriteriaRemove()));

    window->show();
}

void MainWindow::criteriaRemove()
{
    QList<QStandardItemModel *> listOld;
    QStandardItemModel *modelPay = new QStandardItemModel();
    QStandardItemModel *modelWeight = new QStandardItemModel();
    QStandardItemModel *modelRel = new QStandardItemModel();

    QStandardItemModel *actualPay = CAST_MODEL(ui->tableMatrixPayment);
    QStandardItemModel *actualWeight = CAST_MODEL(ui->tableMatrixWeight);
    QStandardItemModel *actualRel = CAST_MODEL(ui->tableMatrixRelationship);

    ui->tableMatrixPayment->copyTableValues(modelPay, -1);
    ui->tableMatrixWeight->copyTableValues(modelWeight, -1);
    ui->tableMatrixRelationship->copyTableValuesMirror(modelRel);

    int colCount = actualPay->columnCount();
    int rowCount = actualPay->rowCount();

    QStringList list;
    QString str;
    for( int i = 0; i < colCount; i++ )
    {
        str = actualPay->horizontalHeaderItem(i)->text();
        list << str;
    }

    if( colCount-1 <= 0 )
    {
        ui->actEditCriteria->setEnabled(false);
        ui->actDeleteCriteria->setEnabled(false);
        ui->actBuild->setEnabled(false);
        enableTable(false);
        enableMatrixC(false);
    }

    modelPay->setHorizontalHeaderLabels(list);

    modelRel->setHorizontalHeaderLabels(list);
    modelRel->setVerticalHeaderLabels(list);

    modelWeight->setHorizontalHeaderLabels(list);
    list.clear();
    list << Language::language("weights") << Language::language("preferences");
    modelWeight->setVerticalHeaderLabels(list);
    list.clear();


    for( int i = 0; i < rowCount; i++ )
    {
        str = actualPay->verticalHeaderItem(i)->text();
        list << str;
    }

    modelPay->setVerticalHeaderLabels(list);

    listOld << modelPay << modelWeight << modelRel;

    int selCol = ui->tableMatrixPayment->selectedColumn() == -1 ? CriteriaRemove->cbxCriteria->currentIndex() : ui->tableMatrixPayment->selectedColumn();

    ui->tableMatrixPayment->model()->removeColumn(selCol);
    ui->tableMatrixWeight->model()->removeColumn(selCol);
    ui->tableMatrixRelationship->model()->removeColumn(selCol);
    ui->tableMatrixRelationship->model()->removeRow(selCol);

    QList<QStandardItemModel *> listNew;
    listNew << actualPay << actualWeight << actualRel;

    QList<Table *> listTable;
    listTable << ui->tableMatrixPayment << ui->tableMatrixWeight << ui->tableMatrixRelationship;

    stackCommands->push(new UndoUpdateModel(listTable, listOld, listNew));
    ui->tableMatrixPayment->columnSelected(-1);
}

void MainWindow::closeWindowCriteriaRemove()
{
    setEnabledActions(true);
    disconnect(CriteriaRemove->btnUpdate, SIGNAL(clicked()), this, SLOT(criteriaRemove()));
    disconnect(CriteriaRemove->btnUpdate, SIGNAL(clicked()), window, SLOT(close()));
    disconnect(window, SIGNAL(finished(int)), this, SLOT(closeWindowCriteriaRemove()));

    CriteriaRemove = NULL;
    window = NULL;
}

/*Referente a alternativas*/

void MainWindow::on_actAddAlternative_triggered()
{
    setEnabledActions(false);
    Alternative = new Ui_Alternative;
    window = new QDialog(this);
    Alternative->setupUi(window);
    window->setWindowTitle(Language::language("add_alternative_title"));
    Alternative->btnAdd->setText(Language::language("add"));
    Alternative->btnCancel->setText(Language::language("cancel"));
    Alternative->lblNameAlternative->setText(Language::language("name_alternative"));

    connect(Alternative->btnAdd, SIGNAL(clicked()), this, SLOT(addNewAlternative()));
    connect(window, SIGNAL(finished(int)), this, SLOT(closeWindowAlternative()));

    window->show();
}

void MainWindow::closeWindowAlternative()
{
    setEnabledActions(true);
    disconnect(Alternative->btnAdd, SIGNAL(clicked()), this, SLOT(addNewAlternative()));
    disconnect(window, SIGNAL(finished(int)), this, SLOT(closeWindowAlternative()));


    window = NULL;
    Alternative = NULL;
}

void MainWindow::addNewAlternative()
{
    if( Alternative->edtNameAlternative->text().isEmpty())
    {
        QMessageBox::information(this, Language::language("add_alternative_title"), Language::language("message_null_value_alternative"));
        Alternative->edtNameAlternative->setFocus();
        return;
    }

    int rowCount = ui->tableMatrixPayment->model()->rowCount();
    int colCount = ui->tableMatrixPayment->model()->columnCount();
    QStandardItemModel *model = new QStandardItemModel();
    QStandardItemModel *modelActual = static_cast<QStandardItemModel *>(ui->tableMatrixPayment->model());

    QStringList list;
    for( int i = 0; i < colCount; i++ )
        list << modelActual->horizontalHeaderItem(i)->text();

    model->setHorizontalHeaderLabels(list);

    list.clear();
    QString str;
    for( int i = 0; i < rowCount; i++ )
    {
        str = modelActual->verticalHeaderItem(i)->text();
        if( str == Alternative->edtNameAlternative->text() )
        {
            Alternative->edtNameAlternative->setText("");
            Alternative->edtNameAlternative->setFocus();
            QMessageBox::information(this, Language::language("add_alternative_title"), Language::language("message_existing_alternative"));
            return;
        }
        if( i == ui->tableMatrixPayment->selectedRow() )
            list << Alternative->edtNameAlternative->text();
        list << str;
    }

    if( ui->tableMatrixPayment->selectedRow() == -1 )
        list << Alternative->edtNameAlternative->text();

    model->setVerticalHeaderLabels(list);

    // Preenche linhas e colunas da tabela em que houver algum valor
    ui->tableMatrixPayment->copyTableValues( model , ui->tableMatrixPayment->selectedRow() );

    stackCommands->push(new UndoUpdateModel( ui->tableMatrixPayment, CAST_MODEL(ui->tableMatrixPayment), model ));

    //ui->tableMatrixPayment->setModel(model);

    ui->tableMatrixPayment->rowSelected(-1);
    Alternative->edtNameAlternative->setText("");
    Alternative->edtNameAlternative->setFocus();

    ui->actEditAlternative->setEnabled(true);
    ui->actDeleteAlternative->setEnabled(true);

    if( colCount >= 1 )
    {
        ui->actBuild->setEnabled(true);
        //ui->actTableClean->setEnabled(true);
        enableTable(true);
    }
}

// Referente a editar alternativa.

void MainWindow::on_actEditAlternative_triggered()
{
    setEnabledActions(false);
    AlternativeEdit = new Ui_alternativeEdit();
    window = new QDialog();
    AlternativeEdit->setupUi(window);

    QStandardItemModel *modelActual = static_cast<QStandardItemModel *>(ui->tableMatrixPayment->model());
    int colCount = modelActual->rowCount();
    QString str;
    for( int i = 0; i < colCount; i++ )
    {
        str = modelActual->verticalHeaderItem(i)->text();
        AlternativeEdit->cbxAlternative->insertItem(i,str);
    }

    int selCol = ui->tableMatrixPayment->selectedRow() == -1 ? 0 : ui->tableMatrixPayment->selectedRow();
    currentAlternativeChanged(selCol);
    AlternativeEdit->cbxAlternative->setCurrentIndex(selCol);

    connect( AlternativeEdit->cbxAlternative, SIGNAL(currentIndexChanged(int)), this, SLOT(currentAlternativeChanged(int)));
    connect( AlternativeEdit->btnUpdate, SIGNAL(clicked()), this, SLOT(alternativeEditChanged()));
    connect(AlternativeEdit->btnUpdate, SIGNAL(clicked()), window, SLOT(close()));
    connect(window, SIGNAL(finished(int)), this, SLOT(closeWindowAlternativeEdit()));

    window->show();
}

void MainWindow::currentAlternativeChanged(int index)
{
    QStandardItemModel *modelActual = static_cast<QStandardItemModel *>(ui->tableMatrixPayment->model());
    QString str = modelActual->verticalHeaderItem(index)->text();
    AlternativeEdit->edtNameAlternative->setText(str);
}

void MainWindow::closeWindowAlternativeEdit()
{
    setEnabledActions(true);
    disconnect( AlternativeEdit->cbxAlternative, SIGNAL(currentIndexChanged(int)), this, SLOT(currentAlternativeChanged(int)));
    disconnect( AlternativeEdit->btnUpdate, SIGNAL(clicked()), this, SLOT(alternativeEditChanged()));
    disconnect(AlternativeEdit->btnUpdate, SIGNAL(clicked()), window, SLOT(close()));
    disconnect(window, SIGNAL(finished(int)), this, SLOT(closeWindowAlternativeEdit()));

    window = NULL;
    AlternativeEdit = NULL;
}

void MainWindow::alternativeEditChanged()
{
    if( AlternativeEdit->edtNameAlternative->text().isEmpty())
    {
        QMessageBox::information(this, Language::language("add_alternative_title"), Language::language("message_null_value_alternative"));
        Criteria->edtNomeCriterio->setFocus();
        return;
    }

    QStandardItemModel *modelActual = static_cast<QStandardItemModel *>(ui->tableMatrixPayment->model());

    QString str;
    int rowCount = modelActual->rowCount();
    for( int i = 0; i < rowCount; i++ )
    {
        str = modelActual->verticalHeaderItem(i)->text();
        if( str == AlternativeEdit->edtNameAlternative->text() )
        {

            AlternativeEdit->edtNameAlternative->setText("");
            AlternativeEdit->edtNameAlternative->setFocus();
            QMessageBox::information(this, Language::language("add_alternative_title"), Language::language("message_existing_alternative"));
            return;
        }
    }
    int index = AlternativeEdit->cbxAlternative->currentIndex();
    str = AlternativeEdit->edtNameAlternative->text();

    ui->tableMatrixPayment->rowSelected(-1);
    stackCommands->push(new UndoUpdateVerticalHeader(modelActual, index, modelActual->verticalHeaderItem(index)->text(), str));
}

// Referente a deletar alternativa.

void MainWindow::on_actDeleteAlternative_triggered()
{

    if( ui->tableMatrixPayment->selectedRow() != -1 )
    {
        alternativeRemove();
        return;
    }
    setEnabledActions(false);
    AlternativeRemove = new Ui_alternativeRemove();
    window = new QDialog();
    AlternativeRemove->setupUi(window);

    QStandardItemModel *modelActual = static_cast<QStandardItemModel *>(ui->tableMatrixPayment->model());
    int rowCount = modelActual->rowCount();
    QString str;
    for( int i = 0; i < rowCount; i++ )
    {
        str = modelActual->verticalHeaderItem(i)->text();
        AlternativeRemove->cbxAlternative->insertItem(i,str);
    }

    int selCol = ui->tableMatrixPayment->selectedRow() == -1 ? 0 : ui->tableMatrixPayment->selectedRow();
    AlternativeRemove->cbxAlternative->setCurrentIndex(selCol);

    connect( AlternativeRemove->btnUpdate, SIGNAL(clicked()), this, SLOT(alternativeRemove()));
    connect(AlternativeRemove->btnUpdate, SIGNAL(clicked()), window, SLOT(close()));
    connect(window, SIGNAL(finished(int)), this, SLOT(closeWindowAlternativeRemove()));

    window->show();
}

void MainWindow::alternativeRemove()
{
    QStandardItemModel *modelActual = CAST_MODEL(ui->tableMatrixPayment);
    QStandardItemModel *model = new QStandardItemModel();

    int selRow = ui->tableMatrixPayment->selectedRow() == -1 ? AlternativeRemove->cbxAlternative->currentIndex() : ui->tableMatrixPayment->selectedRow();

    ui->tableMatrixPayment->copyTableValues(model, -1);

    int colCount = modelActual->columnCount();
    int rowCount = modelActual->rowCount();

    QString str;
    QStringList list;

    for( int i = 0; i < colCount; i++ )
    {
        str = modelActual->horizontalHeaderItem(i)->text();
        list << str;
    }

    model->setHorizontalHeaderLabels(list);

    list.clear();
    for( int i = 0; i < rowCount; i++ )
    {
        str = modelActual->verticalHeaderItem(i)->text();
        list << str;
    }

    if( rowCount-1 <= 0 )
    {
        ui->actEditAlternative->setEnabled(false);
        ui->actDeleteAlternative->setEnabled(false);
        ui->actBuild->setEnabled(false);
    }

    if( colCount <= 0 )
        enableTable(false);

    model->setVerticalHeaderLabels(list);


    model->removeRow(selRow);

    ui->tableMatrixPayment->rowSelected(-1);

    stackCommands->push(new UndoUpdateModel(ui->tableMatrixPayment, modelActual, model));

}

void MainWindow::closeWindowAlternativeRemove()
{
    setEnabledActions(true);
    disconnect( AlternativeRemove->btnUpdate, SIGNAL(clicked()), this, SLOT(alternativeRemove()));
    disconnect(AlternativeRemove->btnUpdate, SIGNAL(clicked()), window, SLOT(close()));
    disconnect(window, SIGNAL(finished(int)), this, SLOT(closeWindowAlternativeRemove()));

    window = NULL;
    AlternativeRemove = NULL;
}


void MainWindow::matrixALine()
{
    QList<qreal> best;
    QList<qreal> worst;

    for( int i = 0; i < COUNTCOL(ui->tableMatrixWeight); i++ )
    {
        if( ui->tableMatrixWeight->model()->index(1,i).data().toInt() == 0 )
        {
            best.append(ui->tableMatrixPayment->searchMaxValueTable(i));
            worst.append(ui->tableMatrixPayment->searchMinValueTable(i));
        }
        else
        {
            best.append(ui->tableMatrixPayment->searchMinValueTable(i));
            worst.append(ui->tableMatrixPayment->searchMaxValueTable(i));
        }
    }

    int rowCount = COUNTROW(ui->tableMatrixPayment);
    int colCount = COUNTCOL(ui->tableMatrixPayment);

    tableMatrixALine = new Table();
    tableMatrixALine->canImport(false);

    QStandardItemModel *model = new QStandardItemModel;
    QStandardItemModel *modelActual = static_cast<QStandardItemModel *>(ui->tableMatrixPayment->model());

    QStringList list;
    for( int i = 0; i < colCount; i++ )
        list << modelActual->horizontalHeaderItem(i)->text();

    model->setHorizontalHeaderLabels(list);

    list.clear();
    for( int i = 0; i < rowCount; i++ )
    {
        list << modelActual->verticalHeaderItem(i)->text();
    }

    model->setVerticalHeaderLabels(list);

    QStandardItem *item;
    for( int i = 0; i < colCount; i++ )
    {
        for( int j = 0; j < rowCount; j++ )
        {
            float payValue = ui->tableMatrixPayment->model()->index(j,i).data().toFloat();
            float calc = ( payValue - worst.at(i) )/ (best.at(i) - worst.at(i));
            item = new QStandardItem(floatFormat(calc,Configuration::configuration("precision").toInt()));
            item->setEditable(false);
            model->setItem(j,i, item);
        }
    }
    modelMatrixALine = model;
    tableMatrixALine->setModel(modelMatrixALine);
}

void MainWindow::matrixBLine()
{
    int rowCount = COUNTROW(tableMatrixALine);
    int colCount = COUNTCOL(tableMatrixALine);

    int k = Build->cbxChoices->currentText().toInt();

    tableMatrixBLine = new Table();
    tableMatrixBLine->canImport(false);

    QStandardItemModel *model = new QStandardItemModel();
    QStandardItemModel *modelResult = new QStandardItemModel();
    qreal tau = Build->dSpbTau->value();
    matrixB(k, tau , rowCount, colCount ,model, modelResult);

    modelMatrixRelativeResult = modelResult;

    modelMatrixBLine = model;
    modelMatrixResult = new QStandardItemModel();

    colCount = model->columnCount();
    modelMatrixResult->setHorizontalHeaderItem(0, new QStandardItem("%"));
    for( int i = 0; i < model->rowCount(); i++ )
    {
        QStandardItem *item = new QStandardItem(floatFormat( ((qreal)Table::countFindValue(modelMatrixRelativeResult, 1, i )/colCount)*100, Configuration::configuration("precision").toInt()));
        item->setEditable(false);
        modelMatrixResult->setItem(i, item);
    }

    tableResultRelative = new Table();
    tableResultRelative->canImport(false);
    tableResultRelative->setModel(modelMatrixRelativeResult);

    tableMatrixBLine->setModel(modelMatrixBLine);

    modelMatrixResult->setVerticalHeaderLabels(tableMatrixBLine->valuesHeader(Qt::Vertical));
    tableResult->setModel(modelMatrixResult);
}

void MainWindow::on_actFindInTable_triggered()
{
    ALTERFINDTABLE(ui->tabWidget->currentIndex());
    if( !ui->tableFindValue->isVisible() )
    {
        ui->tableFindValue->setVisible(true);
        ui->wgtReplaceTable->setVisible(false);
    }
    else
    {
        if( qobject_cast<Table *>(ui->tabWidget->widget(ui->tabWidget->currentIndex())->children().at(1))->selectionModel()->selectedIndexes().isEmpty() )
            ui->tableFindValue->setVisible(false);
    }
}

void MainWindow::on_actReplaceTable_triggered()
{
    if( !ui->tableFindValue->isVisible() )
    {
        ui->tableFindValue->setVisible(true);
        ui->wgtReplaceTable->setVisible(true);
    }
    if( !ui->wgtReplaceTable->isVisible() )
    {
        ui->wgtReplaceTable->setVisible(true);
        if( !ui->cbxFind->currentText().isEmpty() )
            ui->cbxReplace->setFocus();
    }
    else
        ui->wgtReplaceTable->setVisible(false);

}


void MainWindow::on_tabWidget_currentChanged(int index)
{
    ALTERFINDTABLE(index);
}

QStringList MainWindow::ordenateStringList(QStringList set, int k )
{
    QStringList list;
    std::string bitmask( k, 1 );
    bitmask.resize(set.size(), 0);
    do
    {
        QString tmp;
        for( int i = 0; i < set.size(); ++i )
        {
            if( bitmask[i] ) tmp += set.at(i) + " - ";
        }

        tmp.remove(QRegExp(" - $"));
        list << tmp;
        qApp->processEvents();
    }while(std::prev_permutation(bitmask.begin(), bitmask.end()));
    return list;
}

void MainWindow::on_actMatrixALine_toggled(bool arg1)
{
    if( tableMatrixALine == NULL ) return;

    if( arg1 == true )
    {
        tabMatrixALine = new QWidget(ui->tabWidget);
        ui->tabWidget->addTab(tabMatrixALine,Language::language("matriz_a_linha"));

        QHBoxLayout *horizontalLayout = new QHBoxLayout(tabMatrixALine);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(0, 0, 0, 0);

        tableMatrixALine->setParent(tabMatrixALine);
        horizontalLayout->addWidget(tableMatrixALine);

        ui->tabWidget->setCurrentIndex(ui->tabWidget->count()-1);
    }
    else
    {
        for( int i = 2; i < ui->tabWidget->count(); i++)
            if( ui->tabWidget->widget(i) == tabMatrixALine )
                ui->tabWidget->removeTab(i);
    }
}

void MainWindow::on_actMatrixBLine_toggled(bool arg1)
{
    if( tableMatrixBLine == NULL ) return;

    if( arg1 == true )
    {
        tabMatrixBLine = new QWidget(ui->tabWidget);
        ui->tabWidget->addTab(tabMatrixBLine,Language::language("matrix_b_line"));

        QHBoxLayout *horizontalLayout = new QHBoxLayout(tabMatrixBLine);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        tableMatrixBLine->setParent(tabMatrixBLine);

        horizontalLayout->addWidget(tableMatrixBLine);
        ui->tabWidget->setCurrentIndex(ui->tabWidget->count()-1);
    }
    else
    {
        for( int i = 2; i < ui->tabWidget->count(); i++)
            if( ui->tabWidget->widget(i) == tabMatrixBLine )
                ui->tabWidget->removeTab(i);
    }
}

void MainWindow::on_actResultRelative_toggled(bool arg1)
{
    if( tableResultRelative == NULL ) return;

    if( arg1 == true )
    {
        tabRelativeResult = new QWidget(ui->tabWidget);
        ui->tabWidget->addTab(tabRelativeResult,Language::language("matrix_a_line"));

        QHBoxLayout *horizontalLayout = new QHBoxLayout(tabRelativeResult);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        tableResultRelative->setParent(tabRelativeResult);

        horizontalLayout->addWidget(tableResultRelative);

        ui->tabWidget->setCurrentIndex(ui->tabWidget->count()-1);
    }
    else
    {
        for( int i = 2; i < ui->tabWidget->count(); i++)
            if( ui->tabWidget->widget(i) == tabRelativeResult )
                ui->tabWidget->removeTab(i);
    }
}

void MainWindow::on_actBuild_triggered()
{
    if( Build != NULL )
    {
        disconnect( Build->btnApply, SIGNAL(clicked()), this, SLOT(buildBLine()));
        disconnect( Build->btnApply, SIGNAL(clicked()), window, SLOT(close()));
        disconnect(window, SIGNAL(finished(int)), this, SLOT(closeWindowBuild()));
    }

    Build = new Ui_Build;
    window = new QDialog(this);
    Build->setupUi(window);
    window->setWindowTitle(Language::language("build"));

    ALTERLANGUAGE( Build->lblChoices, "choices" );

    int rowCount = COUNTROW(ui->tableMatrixPayment);
    int colCount = COUNTCOL(ui->tableMatrixPayment);
    if( rowCount == 0 || colCount == 0 )
    {
        QMessageBox::information(this, Language::language("title_information"), Language::language("table_is_empty"));
        return;
    }

    int min = MIN(rowCount,colCount);

    if( rowCount <= 2 && colCount <= 2 )
    {
        QMessageBox::information(this, Language::language("title_information"), Language::language("table_is_small"));
        return;
    }

    for(int i = 0; i < rowCount; i++)
    {
        for( int j = 0; j < colCount; j++ )
        {
            if( ui->tableMatrixPayment->model()->index(i, j).data().toString().isEmpty() )
            {
                QMessageBox::information(this, Language::language("title_information"), Language::language("validate_alternative").arg(HEADERTABLE(ui->tableMatrixPayment, i, Qt::Vertical)).arg(HEADERTABLE(ui->tableMatrixPayment, j, Qt::Horizontal)));//QString::fromUtf16(tr(Language::language("validate_alternative").toStdString().c_str()).arg(HEADERTABLE(ui->tableMatrixPayment, i, Qt::Vertical)).arg(HEADERTABLE(ui->tableMatrixPayment, i, Qt::Horizontal)).toStdString().c_str()));
                return;
            }
        }
    }


    for(int i = 0; i < colCount; i++)
    {
        for( int j = 0; j < colCount; j++ )
        {
            if( ui->tableMatrixRelationship->model()->index(i, j).data().toString().isEmpty() )
            {
                QMessageBox::information(this, Language::language("title_information"), Language::language("validate_criteria").arg(HEADERTABLE(ui->tableMatrixRelationship, i, Qt::Vertical)).arg(HEADERTABLE(ui->tableMatrixRelationship, j, Qt::Horizontal)));//QString::fromUtf16(tr(Language::language("validate_alternative").toStdString().c_str()).arg(HEADERTABLE(ui->tableMatrixPayment, i, Qt::Vertical)).arg(HEADERTABLE(ui->tableMatrixPayment, i, Qt::Horizontal)).toStdString().c_str()));
                return;
            }
        }
    }

    for( int i = 0; i < colCount; i++ )
    {
        if( ui->tableMatrixWeight->model()->index(0, i).data().toString().isEmpty() )
        {
            QMessageBox::information(this, Language::language("title_information"), Language::language("validate_weight").arg(HEADERTABLE(ui->tableMatrixWeight, i, Qt::Horizontal)));//QString::fromUtf16(tr(Language::language("validate_alternative").toStdString().c_str()).arg(HEADERTABLE(ui->tableMatrixPayment, i, Qt::Vertical)).arg(HEADERTABLE(ui->tableMatrixPayment, i, Qt::Horizontal)).toStdString().c_str()));
            return;
        }
    }

    for( int i = 2; i < min; i++ )
        Build->cbxChoices->addItem(TR(i));

    setEnabledActions(false);
    window->show();

    connect( Build->btnApply, SIGNAL(clicked()), window, SLOT(close()));
    connect( Build->btnApply, SIGNAL(clicked()), this, SLOT(buildBLine()));
    connect(window, SIGNAL(finished(int)), this, SLOT(closeWindowBuild()));
}

void MainWindow::closeWindowBuild()
{
    setEnabledActions(true);
}

void MainWindow::buildBLine()
{
    tau = (float)Build->dSpbTau->value();
    alternatives_num = (int)Build->cbxChoices->currentText().toInt();
    matrixALine();
    matrixBLine();

    float max = tableResult->searchMaxValueTable(0);
    float min = tableResult->searchMinValueTable(0);


    QStandardItemModel *model = static_cast<QStandardItemModel *>(tableResult->model());

    int rowCount = COUNTROW(tableResult);

    QModelIndexList listIndex;

    for( int i = 0; i < rowCount; i++)
    {
        model->setData(model->index(i,0), QVariant(QColor("#FFFFFF")), Qt::ForegroundRole);
        float value = model->data(model->index(i,0)).toReal();

        if( (float) value == (float)max  )
        {
            model->setData(model->index(i,0), QVariant(QColor("#8EDE21")), Qt::BackgroundColorRole);
        }
        else if( (float) value == (float)min  )
        {
            model->setData(model->index(i,0), QVariant(QColor("#FF0000")), Qt::BackgroundColorRole);
        }
        else
        {
            model->setData(model->index(i,0), QVariant(QColor("#000000")), Qt::ForegroundRole);
        }

        listIndex << model->index(i,0);
    }

    setEnabledActions(true);

    tabResult = new QWidget(ui->tabWidget);
    int index = ui->tabWidget->addTab(tabResult,Language::language("result"));

    QTabBar *tabBar = ui->tabWidget->findChild<QTabBar *>();
    tabResultButtonClose = new QPushButton(QIcon(":/imagens/cancel.png"),"");
    tabResultButtonClose->setFlat(true);
    tabResultButtonClose->setGeometry(0,0,20,20);
    tabBar->setTabButton(index,QTabBar::RightSide, tabResultButtonClose);
    connect(tabResultButtonClose, SIGNAL(clicked()), this, SLOT(closeTabResult()));



    QHBoxLayout *horizontalLayout = new QHBoxLayout(tabResult);
    horizontalLayout->setSpacing(6);
    horizontalLayout->setContentsMargins(0, 0, 0, 0);

    tableResult->setParent(tabResult);
    horizontalLayout->addWidget(tableResult);

    ui->tabWidget->setCurrentWidget(tableResult);

    if( ui->actMatrixALine->isChecked() )
        on_actMatrixALine_toggled(true);
    else
        on_actMatrixALine_toggled(false);

    if( ui->actMatrixBLine->isChecked() )
        on_actMatrixBLine_toggled(true);
    else
        on_actMatrixBLine_toggled(false);

    if( ui->actResultRelative->isChecked() )
        on_actResultRelative_toggled(true);
    else
        on_actResultRelative_toggled(false);

    ui->tabWidget->setCurrentIndex(3);


    disconnect( Build->btnApply, SIGNAL(clicked()), this, SLOT(buildBLine()));
    disconnect( Build->btnApply, SIGNAL(clicked()), window, SLOT(close()));
    disconnect(window, SIGNAL(finished(int)), this, SLOT(closeWindowBuild()));

    window = NULL;
    Build = NULL;

    ui->tableMatrixPayment->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableMatrixRelationship->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableMatrixWeight->setEditTriggers(QAbstractItemView::NoEditTriggers);

    setEnabledActions(false);

    ui->actDeleteAlternative->setEnabled(false);
    ui->actDeleteCriteria->setEnabled(false);

    ui->actAddAlternative->setEnabled(false);
    ui->actAddCriteria->setEnabled(false);

    ui->actEditAlternative->setEnabled(false);
    ui->actEditCriteria->setEnabled(false);

    ui->actGraphResult->setEnabled(true);

}

void MainWindow::updateValueTable(QAbstractItemModel *model, const QModelIndexList &list, const QString &str)
{
    stackCommands->push(new UndoUpdateValue(model, list, str));
}

bool MainWindow::saveFileQuestion()
{
    int save;
    if( lastSaveAlterationValue != stackCommands->index() )
    {
        save = QMessageBox::question(this,Language::language("save"), Language::language("save_new_file_MEM"), QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel);
        if( save == QMessageBox::Yes )
        {
            on_actSave_triggered();
            return true;
        }
        else if( save == QMessageBox::Cancel )
            return false;
    }
    return true;
}
void MainWindow::closeEvent(QCloseEvent *event)
{
    if( !saveFileQuestion() )
        event->ignore();
    else
    {
        event->accept();
        exit(0);
    }

}

void MainWindow::on_actAbout_triggered()
{
    About *about = new About;
    about->setWindowTitle("Sobre");
    about->show();
    about->setWindowIcon(QIcon(":/imagens/about.png"));
}

void MainWindow::setCurrentFile(const QString &fileName)
{
    path = fileName;
    setWindowFilePath(path);


    QSettings settings;
    QStringList files = settings.value("recentFileList").toStringList();
    files.removeAll(fileName);
    files.prepend(fileName);
    while (files.size() > MaxRecentFiles)
        files.removeLast();

    settings.setValue("recentFileList", files);
    updateRecentFileActions();
}

void MainWindow::updateRecentFileActions()
{
    QSettings settings;
    QStringList files = settings.value("recentFileList").toStringList();

    int numRecentFiles = qMin(files.size(), (int)MaxRecentFiles);

    for (int i = 0; i < numRecentFiles; ++i) {
        QString text = tr("&%1 %2\t(%3)")
                .arg(i + 1)
                .arg(strippedName(files[i]))
                .arg(QDir::toNativeSeparators(pathName(files[i])));
        recentFileActs[i]->setText(text);
        recentFileActs[i]->setData(files[i]);
        recentFileActs[i]->setVisible(true);
        recentFileActs[i]->setEnabled(true);
        recentFileActs[i]->setShortcut(tr( "Ctrl+R+%1" ).arg(i+1));
    }
    for (int j = numRecentFiles; j < MaxRecentFiles; ++j)
        recentFileActs[j]->setVisible(false);

    actNone->setVisible(numRecentFiles == 0);
}

QString MainWindow::strippedName(const QString &fullFileName)
{
    return QFileInfo(fullFileName).fileName();
}

QString MainWindow::pathName(const QString &fullFileName)
{
    const int maxLen = 11;
    QString path = fullFileName;
    if( path.length() > maxLen*2 + 1 )
        path = path.left( maxLen ) + QChar( 8230 ) + path.right( maxLen );
    return path;
}

void MainWindow::openRecentFile()
{
    QAction *action = qobject_cast<QAction *>(sender());
    if (action)
        openFileMEM(action->data().toString());
}

void MainWindow::setEnabledActions(bool value)
{
    ui->mainToolBar->setEnabled(value);
    ui->actAddAlternativeMenu->setEnabled(value);;
    ui->actAddCriteriaMenu->setEnabled(value);
}

void MainWindow::on_actGraphResult_triggered()
{

    int selCol = tableResult->selectedRow();

    if( selCol == -1 )
    {
        selectGraphic = new Ui_selectGraphic;
        window = new QDialog(this);
        selectGraphic->setupUi(window);
        selectGraphic->cbxAlternative->insertItems(0,tableMatrixBLine->valuesHeader(Qt::Vertical));
        window->exec();
        selCol = selectGraphic->cbxAlternative->currentIndex();
        delete selectGraphic;
        delete window;

    }

    Graphic *graphic = new Graphic(this);
    graphic->setWindowTitle(Language::language("alternative") +": "+ tableMatrixBLine->valuesHeader(Qt::Vertical).at(selCol));
    graphic->getUi()->customPlot->legend->setVisible(true);

    graphic->getUi()->customPlot->xAxis->setAutoTicks(false);
    graphic->getUi()->customPlot->xAxis->setAutoTickLabels(false);
    graphic->getUi()->customPlot->xAxis->setLabel(Language::language("abscissa_performace_graphic"));
    graphic->getUi()->customPlot->yAxis->setLabel(Language::language("ordered_performace_graphic"));

    QVector<double> ticks;
    QVector<QString> labels = tableMatrixBLine->valuesHeader(Qt::Horizontal).toVector();

    graphic->getUi()->customPlot->addGraph();
    graphic->getUi()->customPlot->graph()->setName(Language::language("criteria"));
    QPen pen;
    pen.setColor(QColor(0, 0, 255, 200));
    graphic->getUi()->customPlot->graph()->setLineStyle(QCPGraph::lsLine);
    graphic->getUi()->customPlot->graph()->setPen(pen);
    graphic->getUi()->customPlot->graph()->setBrush(QBrush(QColor(255,160,50,150)));



    QVector<double> x, y, v_tau;

    statusProgressBar->setRange(0,labels.size());
    for( int i = 1; i <= labels.size(); i++)
    {
        v_tau << tau;
        ticks << i;
        x << i;
        y <<(float) tableMatrixBLine->model()->index(selCol,i-1).data().toReal();
        statusProgressBar->setValue(statusProgressBar->value() + 1);
    }
    statusProgressBar->setValue(statusProgressBar->value() + 1);
    statusProgressBar->setEnabled(false);

    graphic->getUi()->customPlot->graph()->setData(x,y);

    graphic->getUi()->customPlot->addGraph();
    graphic->getUi()->customPlot->graph()->setName("Tau");
    pen.setColor(Qt::red);
    graphic->getUi()->customPlot->graph()->setLineStyle(QCPGraph::lsLine);
    graphic->getUi()->customPlot->graph()->setPen(pen);
    graphic->getUi()->customPlot->graph()->setBrush(Qt::NoBrush);
    graphic->getUi()->customPlot->graph()->setData(x, v_tau);

    graphic->getUi()->customPlot->plotLayout()->insertRow(0);
    graphic->getUi()->customPlot->plotLayout()->addElement(0, 0, new QCPPlotTitle( graphic->getUi()->customPlot, tr("Desempenho das alternativas %1 combinadas").arg(alternatives_num)));

    graphic->getUi()->customPlot->xAxis->setTickVectorLabels(labels);
    graphic->getUi()->customPlot->xAxis->setTickVector(ticks);
    graphic->getUi()->customPlot->xAxis->setTickLabelRotation(60);
    graphic->getUi()->customPlot->xAxis->setSubTickCount(0);
    graphic->getUi()->customPlot->xAxis->setTickLength(0,1);
    graphic->getUi()->customPlot->xAxis->grid()->setVisible(true);
    graphic->getUi()->customPlot->xAxis->setRange(0, labels.size()+1);
    graphic->getUi()->customPlot->xAxis->setPadding(0);

    graphic->getUi()->customPlot->yAxis->setRange(0, 1.01);
    graphic->getUi()->customPlot->yAxis->setTickLength(0,0.1);

    graphic->show();
    tableResult->rowSelected(-1);

    statusProgressBar->setValue(0);

}

void MainWindow::closeTabResult()
{
   int size = ui->tabWidget->count();
   for( int i = 3, j = 3; i <= size; i++)
       ui->tabWidget->removeTab(j);

   disconnect(tabResultButtonClose, SIGNAL(clicked()), this, SLOT(closeTabResult()));

   setEnabledActions(true);

   ui->actDeleteAlternative->setEnabled(true);
   ui->actDeleteCriteria->setEnabled(true);

   ui->actAddAlternative->setEnabled(true);
   ui->actAddCriteria->setEnabled(true);

   ui->actEditAlternative->setEnabled(true);
   ui->actEditCriteria->setEnabled(true);
   ui->actGraphResult->setEnabled(false);
}

void MainWindow::on_actSensibilityGraphic_triggered()
{
    SelectNForGraphic = new Ui_SelectNForGraphic;
    window = new QDialog(this);
    SelectNForGraphic->setupUi(window);



    int rowCount = COUNTROW(ui->tableMatrixPayment);
    int colCount = COUNTCOL(ui->tableMatrixPayment);

    int min = MIN(rowCount,colCount);

    for( int i = 2; i < min; i++ )
        SelectNForGraphic->cbxChoices->addItem(TR(i));

    window->setWindowTitle(Language::language("title_graphic_sensibility"));

    window->exec();

    if( window->result() == QDialog::Rejected )
    {
        delete window;
        delete SelectNForGraphic;
        return;
    }

    int n = SelectNForGraphic->cbxChoices->currentText().toInt();


    delete window;
    delete SelectNForGraphic;

    matrixALine();
    rowCount = COUNTROW(tableMatrixALine);
    colCount = COUNTCOL(tableMatrixALine);
    qreal maior = 0;
    qreal tau;
    int col, quantidade = 0;

    QStandardItemModel *model = new QStandardItemModel();
    QStandardItemModel *modelResult = new QStandardItemModel();

    QVector<double> quants, moreAlternatives, x, quantsX;

    statusProgressBar->setEnabled(true);
    statusProgressBar->setValue(0);


    for( float i = 0; i <= 100; i++  )
    {
        tau = static_cast<float>(i) / static_cast<float>(100);
        matrixB(n, tau , rowCount, colCount ,model, modelResult, false);

        col = model->columnCount();

        QStandardItemModel *modelAux = new QStandardItemModel(model->rowCount(), 1);

        for( int j = 0; j < model->rowCount(); j++ )
        {
            qreal aux = ((qreal)Table::countFindValue(modelResult, 1, j )/col)*100;
            modelAux->setData(modelAux->index(j,0), aux);
        }
        statusProgressBar->setValue(statusProgressBar->value()+1);
        maior = Table::searchMaxValueTable(modelAux,0);
        quantidade = Table::countFindValue( modelAux, maior, 0, Qt::Vertical );

        moreAlternatives << maior;
        quants << quantidade;
        quantidade = 0;

        maior = 0;
        x << tau;
    }

    statusProgressBar->setEnabled(false);

    Graphic *graphic = new Graphic(this);

    graphic->getUi()->customPlot->addGraph();
    graphic->getUi()->customPlot->graph()->setName(Language::language("criteria"));
    QPen pen;
    pen.setColor(QColor(200,200,200));
    graphic->getUi()->customPlot->graph()->setPen(pen);
    graphic->getUi()->customPlot->graph()->setBrush(QBrush(QColor(200,200,200)));
    graphic->getUi()->customPlot->graph(0)->setData(x, moreAlternatives);

    graphic->getUi()->customPlot->yAxis->setRange(0,100);

    graphic->getUi()->customPlot->xAxis->setLabel(Language::language("abicissa_sensibility_graphic"));
    graphic->getUi()->customPlot->yAxis->setLabel(Language::language("sensibility_graphic_percent"));
    graphic->getUi()->customPlot->yAxis2->setLabel(Language::language("sensibility_graphic_quantity"));


    graphic->getUi()->customPlot->xAxis->setRange(0,1);
    graphic->getUi()->customPlot->xAxis2->setPadding(0.01);
    graphic->getUi()->customPlot->replot();



    graphic->getUi()->customPlot->addGraph(graphic->getUi()->customPlot->xAxis2,graphic->getUi()->customPlot->yAxis2);

    QCPBars *myBars = new QCPBars(graphic->getUi()->customPlot->xAxis2,graphic->getUi()->customPlot->yAxis2);
    graphic->getUi()->customPlot->addPlottable(myBars);
    myBars->setPen(QPen(Qt::black));
    myBars->setBrush(QBrush(Qt::black));
    myBars->setData(x, quants);
    myBars->setWidth(0.001 );
    graphic->getUi()->customPlot->yAxis2->setVisible(true);
    graphic->getUi()->customPlot->yAxis2->setRange(0, modelResult->rowCount());
    graphic->getUi()->customPlot->xAxis2->setRange(0,1);
    graphic->getUi()->customPlot->xAxis2->setTickLength(0,0.04);
    graphic->getUi()->customPlot->rescaleAxes();
    graphic->getUi()->customPlot->replot();

    graphic->setWindowTitle(Language::language("title_graphic_sensibility"));

    graphic->show();
}

void MainWindow::on_actMatrixC_triggered()
{
    max = new MatrixC;

    connect( max, SIGNAL(valueTableChanged(QAbstractItemModel*,QModelIndexList,QString)), this, SLOT(updateValueTable(QAbstractItemModel*,QModelIndexList,QString)));

    //int rowCount = COUNTROW(ui->tableMatrixPayment);
    int colCount = COUNTCOL(ui->tableMatrixPayment);

    QStandardItemModel *model = new QStandardItemModel;
    QStandardItemModel *modelNext = new QStandardItemModel;


    QList<QStandardItem *> listTitles, listValues;
    for( int i = 0; i < colCount; i++ )
    {
        for(int  j = i + 1; j < colCount; j++ )
        {
            QStandardItem *item = new QStandardItem(tr("%1 : %2").arg(HEADERTABLE(ui->tableMatrixPayment,i, Qt::Horizontal)).arg(HEADERTABLE(ui->tableMatrixPayment,j, Qt::Horizontal)));
            item->setEditable(false);
            listTitles << item;

            listValues << new QStandardItem(tr("%1").arg(ui->tableMatrixRelationship->model()->index(i,j).data().toString()));
        }
    }

    model->insertColumn(0,listTitles);
    model->insertColumn(1,listValues);

    model->setHeaderData(0,Qt::Horizontal,Language::language("title_col"));
    model->setHeaderData(1,Qt::Horizontal,Language::language("value"));


    max->setModel(model);

    listTitles.clear();
    listValues.clear();

    for( int i = 1; i < colCount; i++ )
    {
        for(int  j = 0; j < i; j++ )
        {
            QStandardItem *item = new QStandardItem(tr("%1 : %2").arg(HEADERTABLE(ui->tableMatrixPayment,i, Qt::Horizontal)).arg(HEADERTABLE(ui->tableMatrixPayment,j, Qt::Horizontal)));
            item->setEditable(false);
            listTitles << item;

            listValues << new QStandardItem(tr("%1").arg(ui->tableMatrixRelationship->model()->index(i,j).data().toString()));
        }
    }
    modelNext->insertColumn(0,listTitles);
    modelNext->insertColumn(1,listValues);


    max->setModelNext(modelNext);
    modelNext->setHeaderData(0,Qt::Horizontal,Language::language("title"));
    modelNext->setHeaderData(1,Qt::Horizontal,Language::language("value"));

    max->setMainMatrixC(CAST_MODEL(ui->tableMatrixRelationship));

    max->setMirror( ui->actMirror->isChecked() );
    max->setWindowTitle(Language::language("matrix_c"));

    max->exec();
    disconnect( max, SIGNAL(valueTableChanged(QAbstractItemModel*,QModelIndexList,QString)), this, SLOT(updateValueTable(QAbstractItemModel*,QModelIndexList,QString)));
    max = NULL;
}
