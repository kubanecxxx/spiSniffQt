#include "widgetzdroj.h"
#include "ui_widgetzdroj.h"

#define NAME 0
#define CMD 1
#define VALUE 2
#define SUFFIX 3

widgetZdroj::widgetZdroj(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::widgetZdroj)
{
    ui->setupUi(this);
    timer = new QTimer;
    timer->setInterval(10);
    connect(timer,SIGNAL(timeout()),this,SLOT(timeout()));

    connect(ui->butStart,SIGNAL(clicked()),timer,SLOT(start()));
    connect(ui->butStop,SIGNAL(clicked()),timer,SLOT(stop()));
    disconnect(ui->treeWidget,SIGNAL(itemChanged(QTreeWidgetItem*,int)),
               this,SLOT(on_treeWidget_itemChanged(QTreeWidgetItem*,int)));

    machine = 0;

    // tree init
    //read
    QTreeWidgetItem * read;
    read = new QTreeWidgetItem;
    read->setText(0,"Read");
    ui->treeWidget->addTopLevelItem(read);

    QStringList reads,suffix;
    reads << "voltage" << "current" << "voltageConv"
          << "Output enabled" << "thermal failure"
          << "current limited";
    suffix << "mV" << "mA" << "mV" << "bool" << "bool" << "bool";


    QByteArray tmp;
    tmp.resize(3);
    char b = 0;
    tmp[0] = b;
    tmp[1] = b;
    tmp[2] = b;


    for (int i = 0 ; i < reads.count(); i++)
    {
        QTreeWidgetItem * it = new QTreeWidgetItem;
        read->addChild(it);

        it->setText(NAME,reads.at(i));
        it->setText(SUFFIX,suffix.at(i));
        tmp[0] = i+0;
        it->setText(CMD,tmp.toHex());
        it->setData(CMD,Qt::UserRole,tmp);
        it->setFlags(it->flags() & ~Qt::ItemIsEditable);
    }

    //write
    QTreeWidgetItem * write;
    write = new QTreeWidgetItem;
    write->setText(0,"Write");
    ui->treeWidget->addTopLevelItem(write);

    QStringList writes;
    writes << "Current limit" << "Voltage" << "enable output";
    suffix.clear();
    suffix << "mA" << "mV" << "bool";

    for (int i = 0; i < writes.count() ; i++)
    {
        QTreeWidgetItem * item = new QTreeWidgetItem;
        write->addChild(item);

        item->setText(NAME,writes.at(i));
        item->setText(SUFFIX,suffix.at(i));
        tmp[0] = 0x80 + i;
        item->setText(CMD,tmp.toHex());
        item->setData(CMD,Qt::UserRole, tmp);
        item->setData(CMD,Qt::UserRole+ 1 ,false);
        item->setFlags(item->flags() | Qt::ItemIsEditable);
        item->setData(VALUE,Qt::DisplayRole,0);

    }
    ui->treeWidget->expandAll();

    connect(ui->treeWidget,SIGNAL(itemChanged(QTreeWidgetItem*,int)),
               this,SLOT(on_treeWidget_itemChanged(QTreeWidgetItem*,int)));

}

widgetZdroj::~widgetZdroj()
{
    delete ui;
}


void widgetZdroj::timeout()
{
    for (int i = 0; i < 3; i++)
    {
        QTreeWidgetItem * it = ui->treeWidget->topLevelItem(1)->child(i);
        if(it->data(CMD,Qt::UserRole+1).toBool())
        {
            QByteArray ar = it->data(CMD,Qt::UserRole).toByteArray();
            it->setData(CMD,Qt::UserRole+1,false);
            widget->exchangeData(ar);
            return;
        }
    }

    QByteArray ar = ui->treeWidget->topLevelItem(0)->
            child(machine)->data(CMD,Qt::UserRole).toByteArray();

    widget->exchangeData(ar);
    last = machine;

    machine++;
    if (machine == 6)
        machine = 0;
}

void widgetZdroj::setpreslkj(widgetData *w)
{
    connect(w,SIGNAL(exchangedData(QByteArray)),this,SLOT(newData(QByteArray)));
    widget = w;
}


void widgetZdroj::newData(QByteArray data)
{
//rozparsovat data do stromu
    if (data.count() != 3)
        return;
    int cmd = data.at(0);
    data.remove(0,1);

    QVariant cislo;
    int i = data.at(0) | (data.at(1) << 8);
    cislo = i;
    ui->treeWidget->topLevelItem(0)->child(last)->setData(VALUE,Qt::DisplayRole,cislo);

}

void widgetZdroj::on_treeWidget_itemChanged(QTreeWidgetItem *item, int column)
{
    if (column != VALUE)
        return;
    if (item->parent()->text(0) != "Write")
        return;

    bool ok;
    int val = item->data(VALUE,Qt::DisplayRole).toInt(&ok);
    Q_ASSERT(ok);

    //převyst a nechat poslat
    QByteArray ar = item->data(CMD,Qt::UserRole).toByteArray();
    ar[1] = val & 0xff;
    ar[2] = (val >> 8) & 0xff;
    item->setData(CMD,Qt::UserRole,ar);
    item->setData(CMD,Qt::UserRole+1,true);

}
