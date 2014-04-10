#ifndef CSV_H
#define CSV_H

#include <QtGui>
#include <QTextCodec>
#include <QWidget>
#include <QFileDialog>
#include <QString>
#include "language.h"

namespace Ui {
    class MainWindow;
}
class MainWindow;
class MEM : public QObject
{
public:
    MEM();
    bool read(QWidget *w);
    bool readFileName( QWidget *w, const QString &fileName );
    bool write(QWidget *w, QString fileName);
    bool writeAs( QWidget *w );
    QStringList criterias();
    QStringList alternatives();
    QList<qreal> payment();
    QList<qreal> weight();
    QList<qreal> complementarity();

    void setPayment( QList<qreal> list);
    void setWeight( QList<qreal> list);
    void setComplementarity( QList<qreal> list);

    void setCriterias(QStringList list);
    void setAlternatives(QStringList list);

    QString path();


private:
    QStringList criteriasList;
    QStringList alternativesList;
    QList<qreal> paymentList;
    QList<qreal> weightList;
    QList<qreal> complementarityList;
    QDir directory;
};

#endif // CSV_H
