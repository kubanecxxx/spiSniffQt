#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "widgetsetup.h"
#include <QTimer>
#include <qextserialenumerator.h>
#include <QTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    PortSettings nastaveni;
    nastaveni.BaudRate = BAUD1152000;
    nastaveni.DataBits = DATA_8;
    nastaveni.FlowControl = FLOW_HARDWARE;
    nastaveni.Parity = PAR_NONE;
    nastaveni.StopBits = STOP_1;
    nastaveni.Timeout_Millisec = 10;
    comport = new QextSerialPort(nastaveni,QextSerialPort::EventDriven,this);

    ui->tab_4->comport = comport;
    connect(ui->tab_4,SIGNAL(roznout(bool)),this,SLOT(roznout(bool)));
    connect(ui->tab_4,SIGNAL(message(QString)),statusBar(),SLOT(showMessage(QString)));

    connect(ui->tab,SIGNAL(writeToCom(QByteArray)),this,SLOT(comportSendData(QByteArray)));

    connect(ui->tab_2,SIGNAL(SendCom(QByteArray)),this,SLOT(comportSendData(QByteArray)));

    led = new HLed;
    statusBar()->addPermanentWidget(led);
    roznout(false);

    connect(comport,SIGNAL(readyRead()),this,SLOT(comportNewData()));
    ui->plainTextEdit->setContextMenuPolicy(Qt::CustomContextMenu);

}

MainWindow::~MainWindow()
{

    delete ui;
}

void MainWindow::roznout(bool enabled)
{
    led->turnOn(enabled);
    ui->tab->setEnabled(enabled);
    ui->tab_2->setEnabled(enabled);
}

void MainWindow::comportNewData()
{
    QTimer::singleShot(20,this,SLOT(comportTimeout()));
}

#define TIME (QTime::currentTime().toString("hh:mm:ss") + QString(".%1:\n ").arg(QTime::currentTime().msec()))

void MainWindow::comportTimeout()
{

    QByteArray arr = comport->readAll();

    ui->plainTextEdit->appendPlainText(TIME + " Rec <--: " + arr+ " | " + arr.toHex());

    ui->tab->SetCrSetting(arr);
    ui->tab_2->newData(arr);
}

void MainWindow::comportSendData(QByteArray data)
{
    if (!comport->isWritable())
    {
        statusBar()->showMessage("Nelze psát do komportu");
        return;
    }

    ui->plainTextEdit->appendPlainText(TIME + " Send -->: " + data + " | " + data.toHex());

    comport->write(data + "\r\n");

}

void MainWindow::on_plainTextEdit_customContextMenuRequested(const QPoint &pos)
{
    ui->plainTextEdit->clear();
}
