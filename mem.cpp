#include "mem.h"

MEM::MEM()
{
}

bool MEM::readFileName(QWidget *w, const QString &fileName)
{
    QFile fileImport(fileName);

    QTextCodec::setCodecForLocale( QTextCodec::codecForName("utf8") );

    QString file;

    if (fileImport.open(QFile::ReadOnly)) {
        directory.setPath(fileName);
        file = fileImport.readAll();
        file = QString::fromUtf8(file.toStdString().c_str());

        QStringList list;
        file.remove(QRegExp("\n|\t"));
        list << file.split(QRegExp(";"));
        QRegExp rx("(\\w+)");
        int pos = 0;
        while ((pos = rx.indexIn(list[0], pos)) != -1) {
            criteriasList << rx.cap(1);
            pos += rx.matchedLength();
        }

        criteriasList.removeFirst();

        pos = 0;
        while ((pos = rx.indexIn(list[1], pos)) != -1) {
            alternativesList << rx.cap(1);
            pos += rx.matchedLength();
        }

        alternativesList.removeFirst();

        pos = 0;

        rx.setPattern("(\\d+|\\d+\\.\\d+)");
        while ((pos = rx.indexIn(list[2], pos)) != -1) {
            paymentList << rx.cap(1).toFloat();
            pos += rx.matchedLength();
        }


        pos = 0;

        while ((pos = rx.indexIn(list[3], pos)) != -1) {
            weightList << rx.cap(1).toFloat();
            pos += rx.matchedLength();
        }

        pos = 0;

        while ((pos = rx.indexIn(list[4], pos)) != -1) {
            complementarityList << rx.cap(1).toFloat();
            pos += rx.matchedLength();
        }

        w->setWindowTitle(Language::language("title")+" - "+path());
        return true;
    }
    return false;
}

bool MEM::read(QWidget *w)
{
    QString fileName = QFileDialog::getOpenFileName(w, Language::language("open_file"), QString(), tr("%1 MEM(*.mem)").arg(Language::language("file")));
    if( fileName.isNull() )
        return false;

    return readFileName(w, fileName);
}

QStringList MEM::criterias()
{
    return criteriasList;
}

QStringList MEM::alternatives()
{
    return alternativesList;
}

QList<qreal> MEM::payment()
{
    return paymentList;
}

QList<qreal> MEM::weight()
{
    return weightList;
}

QList<qreal> MEM::complementarity()
{
    return complementarityList;
}

void MEM::setPayment(QList<qreal> list)
{
    paymentList = list;
}

void MEM::setWeight(QList<qreal> list)
{
    weightList = list;
}

void MEM::setComplementarity(QList<qreal> list)
{
    complementarityList = list;
}

void MEM::setCriterias(QStringList list)
{
    criteriasList = list;
}

void MEM::setAlternatives(QStringList list)
{
    alternativesList = list;
}

bool MEM::writeAs( QWidget *w )
{
    QString fileName = QFileDialog::getSaveFileName(w,Language::language("save_file"), QString(), tr("%1 MEM(*.mem)").arg(Language::language("file")));

    if( fileName.isNull() )
        return false;

    return write(w, fileName);
}

bool MEM::write(QWidget *w, QString fileName)
{
    QFile fileWrite(fileName);
    if (fileWrite.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        directory.setPath(fileName);
        QString str = "CRITERIA: [" + criterias().join(", ") + "];\n";
        str += "ALTERNATIVE: [" + alternatives().join(", ") + "];\n";
        str += "PAYMENT: \n";
        for( int i = 0, k = 0; i < alternatives().size(); i++ )
        {
            QStringList aux;
            str += "[";
            for( int j = 0; j < criterias().size(); j++ )
            {
                QString s;
                aux << s.setNum(payment().at(k));
                k++;
            }
            if( i+1 == alternatives().size() )
                str += aux.join(", ") + "];\n";
            else
                str += aux.join(", ") + "]\n";
        }

        str += "WEIGHT: \n";
        for( int i = 0, k = 0; i < 2; i++ )
        {
            QStringList aux;
            str += "[";
            for( int j = 0; j < criterias().size(); j++ )
            {
                QString s;
                aux << s.setNum(weight().at(k));
                k++;
            }
            if( i+1 == 2 )
                str += aux.join(", ") + "];\n";
            else
                str += aux.join(", ") + "]\n";
        }

        str += "COMPLEMENTARITY: \n";
        for( int i = 0, k = 0; i < criterias().size(); i++ )
        {
            QStringList aux;
            str += "[";
            for( int j = 0; j < criterias().size(); j++ )
            {
                QString s;
                aux << s.setNum(complementarity().at(k));
                k++;
            }
            if( i+1 == criterias().size() )
                str += aux.join(", ") + "];\n";
            else
                str += aux.join(", ") + "]\n";
        }

        w->setWindowTitle(Language::language("title")+" - "+path());
        QTextStream out(&fileWrite);
        out.setCodec("UTF-8");
        out << QString::fromUtf8(str.toStdString().c_str()) << endl;
        fileWrite.close();

        return true;
    }

    return false;

}

QString MEM::path()
{
    return directory.path();
}
