#include "widgetcom.h"
#include "ui_widgetcom.h"
#include "qextserialenumerator.h"
#include "qextserialport.h"

widgetCom::widgetCom(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::widgetCom)
{
    ui->setupUi(this);
    FillCombo();
}

widgetCom::~widgetCom()
{
    on_butClose_clicked();
    delete ui;
}

void widgetCom::FillCombo()
{
    ui->comboPorts->clear();
    QList<QextPortInfo> ports = QextSerialEnumerator::getPorts();

    QStringList list;

    for (int i = 0 ; i < ports.count() ; i++)
    {

    #ifdef Q_OS_WIN
         list << ports.at(i).portName;
    #else
        list << ports.at(i).physName;

    #endif

    }

    #ifndef Q_OS_WIN
    list << "/tmp/interceptty";
    #endif

    ui->comboPorts->addItems(list);
}

void widgetCom::on_butRefresh_clicked(bool )
{
    FillCombo();
}

void widgetCom::on_butOpen_clicked()
{
    comport->setPortName(ui->comboPorts->currentText());
    comport->open(QextSerialPort::ReadWrite);

    emit roznout(comport->isOpen());

    if (comport->isOpen())
    {
        emit message(trUtf8("Připojeno k zařízení"));
    }
    else
    {
         emit message(trUtf8("Nepovedlo se připojit k zařízení"));
    }
}

void widgetCom::on_butClose_clicked()
{
    emit message (trUtf8("odpojeno od zařízení"));
    emit roznout(false);
    comport->close();
}
