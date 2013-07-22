#include "widgetdata.h"
#include "ui_widgetdata.h"

widgetData::widgetData(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::widgetData)
{
    ui->setupUi(this);

    addItem(("whats"),("4466208877"));
}

widgetData::~widgetData()
{
    delete ui;
}

void widgetData::addItem(const QString &name, const QByteArray &data)
{
    QListWidgetItem * it = new QListWidgetItem();
    it->setText(name);
    it->setData(Qt::UserRole,data);

    ui->listWidget->addItem(it);
}

void widgetData::on_butExchangeData_clicked()
{
    QByteArray dat = "data ";
    QByteArray m = ui->editSend->text().toLocal8Bit();
    QByteArray temp = m.fromHex(m);

    //dat += m.number(m.fromHex(m).count()) +" " + m.fromHex(m);
    dat += m.number(temp.count()) + " " + temp.toHex();

    emit SendCom(dat);

}

void widgetData::newData(QByteArray &data)
{
    if (!data.startsWith("data"))
        return;

    data.remove(0,data.indexOf("\r\n"));
    data.replace("ch>","");
    data = data.trimmed();
    data.remove(0,4);

    ui->editRead->setText(data.toHex());

}

void widgetData::on_editSend_returnPressed()
{
    on_butExchangeData_clicked();
}

void widgetData::on_listWidget_itemClicked(QListWidgetItem *item)
{
    ui->editSend->setText(item->data(Qt::UserRole).toByteArray());
}

void widgetData::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{

    on_listWidget_itemClicked(item);
    on_butExchangeData_clicked();
}
