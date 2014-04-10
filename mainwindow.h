#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "table.h"
#include "delegates.h"
#include "common.h"
#include "language.h"
#include "mem.h"
#include "undocommands.h"
#include "configuration.h"
#include <ui_alternative.h>
#include <ui_alternativeEdit.h>
#include <ui_alternativeRemove.h>
#include <ui_criteria.h>
#include <ui_configurator.h>
#include <ui_criteriaEdit.h>
#include <ui_build.h>
#include <ui_criteriaRemove.h>
#include <ui_selectGraphic.h>
#include <ui_selectNForGraphic.h>
#include <about.h>
#include <matrixc.h>
#include <algorithm>
#include <iostream>
#include <string>
#include "customplot/qcustomplot.h"
#include <ui_graphic.h>
#include <graphic.h>
#include <QMessageBox>
#include <QProgressBar>
#include <QWizard>
#include <QWizardPage>



//#define DELIMITADOR ","
//#define CABECALHOTABELA( tabela, posicao,  orientacao ) tabela->horizontalHeader()->model()->headerData(posicao, orientacao).toString()

//

namespace Ui {
    class MainWindow;
}

class ItemValidacaoDelegate;
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setWindowTitle(const QString &title);

    void enableSave( bool value );
    void enableTable( bool value );
    void enableMatrixC( bool value );

    void matrixB(int k, const qreal &tau, const int &rowCount, const int &colCount, QStandardItemModel *model, QStandardItemModel *modelResult, bool progress = true);

    //void matrixB( qreal tau, QTable )

protected:
    void closeEvent(QCloseEvent *event);


private slots:


    void buildBLine();
    void openFileMEM( const QString &fileName );

    void importPaymentFileMEM();

    void closeWindowCriteria();
    void slideCriteriaWeight(int peso);
    void addNewCriteria();

    void closeTabResult();

    // Editar critério.
    void currentCriteriaChanged(int index);
    void closeWindowCriteriaEdit();
    void criteriaEditChanged();

    // Remover critério.
    void criteriaRemove();
    void closeWindowCriteriaRemove();

    // Adicionar alternativa.
    void closeWindowAlternative();
    void addNewAlternative();

    // Editar alternative.
    void currentAlternativeChanged(int index);
    void alternativeEditChanged();
    void closeWindowAlternativeEdit();

    // Remover alternativa.
    void alternativeRemove();
    void closeWindowAlternativeRemove();

    // Alteração
    void alterationChanged(int index);

    // Abrir arquivos recentes.
    void openRecentFile();


    void closeWindowBuild();

    void writerConfiguration();
    void closeConfigurator();

    void updateValueTable(QAbstractItemModel *model, const QModelIndexList &list, const QString &str);

    void on_actNew_triggered();

    void on_actOpen_triggered();

    void on_actSave_triggered();

    void on_actPortuguese_triggered();

    void on_actEnglish_triggered();

    void on_actEspanish_triggered();

    void on_actFrench_triggered();

    void on_actAddCriteria_triggered();

    void on_actAddAlternative_triggered();

    void on_actConfiguration_triggered();

    void on_actFindInTable_triggered();

    void on_tabWidget_currentChanged(int index);

    void on_actMatrixALine_toggled(bool arg1);

    void on_actMatrixBLine_toggled(bool arg1);

    void on_actBuild_triggered();

    void on_actReplaceTable_triggered();

    void on_actEditCriteria_triggered();

    void on_actDeleteCriteria_triggered();

    void on_actAbout_triggered();

    void on_actEditAlternative_triggered();

    void on_actDeleteAlternative_triggered();

    void on_actResultRelative_toggled(bool arg1);

    void on_actGraphResult_triggered();

    void on_actSensibilityGraphic_triggered();

    void on_actMatrixC_triggered();

private:


    void readLanguage( QString trad = "pt-BR" );
    void readConfiguration();
    void matrixALine();
    void matrixBLine();

    bool saveFileQuestion();

    void setCurrentFile(const QString &fileName);
    void updateRecentFileActions();
    QString strippedName(const QString &fullFileName);
    QString pathName( const QString &fullFileName );

    void setEnabledActions(bool value);

    QStringList ordenateStringList(QStringList set, int k );
    Ui::MainWindow *ui;

    QDialog *window;
    Ui_Criteria *Criteria;
    Ui_criteriaEdit *CriteriaEdit;
    Ui_criteriaRemove *CriteriaRemove;
    Ui_Alternative *Alternative;
    Ui_alternativeEdit *AlternativeEdit;
    Ui_alternativeRemove *AlternativeRemove;
    Ui_Configurator *Configurator;
    Ui_Build *Build;

    Ui_selectGraphic *selectGraphic;
    Ui_SelectNForGraphic *SelectNForGraphic;

    float tau;
    int alternatives_num;

    Table *tableMatrixALine;
    Table *tableMatrixBLine;
    Table *tableResultRelative;
    Table *tableResult;

    QWidget *tabMatrixBLine;
    QWidget *tabMatrixALine;
    QWidget *tabRelativeResult;
    QWidget *tabResult;

    QUndoStack *stackCommands;

    QString path;

    // Para saber quando foi feita a última alteração, serve para quando uma alteração for feita,
    // e o usuário fechar o programa, limpar as tabelas ou abrir um novo arquivo, perguntar
    // se sele quer salvar.
    int lastSaveAlterationValue;

    QStandardItemModel *modelMatrixBLine;
    QStandardItemModel *modelMatrixALine;
    QStandardItemModel *modelMatrixRelativeResult;
    QStandardItemModel *modelMatrixResult;

    QMenu *recentFilesMenu;
    enum { MaxRecentFiles = 5 };
    QAction *recentFileActs[MaxRecentFiles];
    QAction *actNone;

    QProgressBar *statusProgressBar;

    QPushButton *tabResultButtonClose;

    MatrixC *max;

};


#endif // MAINWINDOW_H
