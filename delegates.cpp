#include "delegates.h"

ItemValidacaoDelegate::ItemValidacaoDelegate(QObject *pai) :
    QStyledItemDelegate(pai)
{
}

QWidget * ItemValidacaoDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
        QRegExp expressao("\\d+|\\d+\\.\\d+");
        QRegExpValidator *validador = new QRegExpValidator(expressao,NULL);
        QWidget* editor = QStyledItemDelegate::createEditor(parent, option, index);
        QLineEdit* lineEditEditor = qobject_cast<QLineEdit*>(editor);
        if( lineEditEditor )
            lineEditEditor->setValidator(validador);
        return editor;
}

void ItemValidacaoDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QLineEdit* lineEditEditor = qobject_cast<QLineEdit*>(editor);
    QString strNew = lineEditEditor->text();
    qDebug() << "Valor" << floatFormat(strNew.toDouble(),Configuration::configuration("precision").toInt());
    if( strNew == index.data().toString() )
        return;
    //QModelIndexList list;
    //list << index;
    //emit valueTableChanged(list, strNew);

    qDebug() << "Valor" << floatFormat(strNew.toDouble(),Configuration::configuration("precision").toInt());
    model->setData(index, floatFormat(strNew.toDouble(),Configuration::configuration("precision").toInt()));
}

ItemDoubleSpinBoxDelegate::ItemDoubleSpinBoxDelegate( QObject *pai):
    QStyledItemDelegate(pai)
{

}

QWidget * ItemDoubleSpinBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QDoubleSpinBox *editor = new QDoubleSpinBox(parent);
    editor->setMinimum(0);
    editor->setMaximum(1);
    editor->setSingleStep(0.01);
    editor->setLocale(QLocale::English);

    return editor;
}

void ItemDoubleSpinBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    qreal value = index.model()->data(index, Qt::EditRole).toFloat();

    QDoubleSpinBox *spinBox = static_cast<QDoubleSpinBox*>(editor);
    spinBox->setLocale(QLocale::English);
    spinBox->setDecimals(Configuration::configuration("precision").toInt());
    spinBox->setValue(floatFormat(value,Configuration::configuration("precision").toInt()).toDouble());
}

void ItemDoubleSpinBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QDoubleSpinBox *spinBox = static_cast<QDoubleSpinBox*>(editor);
    spinBox->setLocale(QLocale::English);
    spinBox->interpretText();
    spinBox->setDecimals(Configuration::configuration("precision").toInt());
    qreal value = spinBox->value();
    model->setData(index, floatFormat(value,Configuration::configuration("precision").toInt()), Qt::EditRole);
}

void ItemDoubleSpinBoxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}

ItemComboBoxDelegate::ItemComboBoxDelegate( QObject *pai) : QStyledItemDelegate(pai)
{
}

QWidget * ItemComboBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QComboBox *cbx = new QComboBox(parent);
    cbx->addItem(Language::language("crescente"));
    cbx->addItem(Language::language("decrescente"));
    return cbx;
}

void ItemComboBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    if(QComboBox *cbx = qobject_cast<QComboBox *>(editor)) {
        QString currentText = index.data(Qt::EditRole).toString();
        int cbxIndex = cbx->findText(currentText);
        if(cbxIndex >= 0)
            cbx->setCurrentIndex(cbxIndex);
    } else {
       QStyledItemDelegate::setEditorData(editor, index);
    }

}

void ItemComboBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    qDebug() << "Inseriu dado";
    if(QComboBox *cbx = qobject_cast<QComboBox *>(editor))
           model->setData(index, cbx->currentIndex(), Qt::EditRole);
       else
        QStyledItemDelegate::setModelData(editor, model, index);
}

void ItemComboBoxDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->save();
    QStyleOptionViewItemV4 opt = option;

    QStyle *style = QApplication::style();
    style->drawControl(QStyle::CE_ItemViewItem, &opt, painter);

    QString image;
    QFontMetrics font(painter->font());
    QString text;
    int fontWidth;
    if( index.data().toInt() == 0 )
    {
        image = ":/imagens/arrow_up.png";
        text = Language::language("crescente");
    }
    else
    {
        text = Language::language("decrescente");
        image = ":/imagens/arrow_down.png";
    }

    //qDebug() << "Index combo: " << index.data().toInt();

    const QPixmap pixmap(image);

    fontWidth = font.width(text);
    painter->drawText(option.rect.x() + 15 + (option.rect.width()/2) - ((pixmap.width() + fontWidth)/2), option.rect.y() + ( option.rect.height() /2 ) + (font.height() / 2) - 2, text);
    painter->drawPixmap(option.rect.x() +(option.rect.width()/2) - ((pixmap.width() + fontWidth)/2), option.rect.y() + ( option.rect.height() /2 ) - (pixmap.height() / 2) , pixmap );

    painter->setClipRect(option.rect.translated(-option.rect.topLeft()));

    painter->restore();
    //QStyledItemDelegate::paint(painter,option,index);
}
