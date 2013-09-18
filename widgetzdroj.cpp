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

    connect(ui->butStart,SIGNAL(clicked()),timer,SLOT(start()));
    connect(ui->butStop,SIGNAL(clicked()),timer,SLOT(stop()));

    machine = 0;

    // tree init
    //read
    QTreeWidgetItem * read;
    read = new QTreeWidgetItem;
    read->setText(0,"Read");
    ui->treeWidget->addTopLevelItem(read);

    QStringList reads,suffix;
    reads << "voltage" << "current" << "voltageConv"
          << "..";
    suffix << "mV" << "mA" << "mV" << "mV";


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
        tmp[0] = i;
        it->setText(CMD,tmp.toHex());
        it->setData(CMD,Qt::UserRole,tmp);
    }

    //write
    QTreeWidgetItem * write;
    write = new QTreeWidgetItem;
    write->setText(0,"Write");
    ui->treeWidget->addTopLevelItem(write);

    QStringList writes;
    writes << "Voltage" << "Current" << "Output";
    suffix.clear();
    suffix << "mV" << "mA" << "bool";

    for (int i = 0; i < writes.count() ; i++)
    {
        QTreeWidgetItem * item = new QTreeWidgetItem;
        write->addChild(item);

        item->setText(NAME,writes.at(i));
        item->setText(SUFFIX,suffix.at(i));
        tmp[0] = 0x80 + i;
        item->setText(CMD,tmp.toHex());
        item->setData(CMD,Qt::UserRole, tmp);
        item->setFlags(item->flags() | Qt::ItemIsEditable);
    }

}

widgetZdroj::~widgetZdroj()
{
    delete ui;
}


void widgetZdroj::timeout()
{
    //widget->exchangeData();
}

void widgetZdroj::setpreslkj(widgetData *w)
{
    connect(w,SIGNAL(exchangedData(QByteArray)),this,SLOT(newData(QByteArray)));
    widget = w;
}


void widgetZdroj::newData(QByteArray data)
{
//rozparsovat data do stromu
}
