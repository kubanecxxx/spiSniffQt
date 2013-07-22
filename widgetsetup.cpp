#include "widgetsetup.h"
#include "ui_widgetsetup.h"
#include  "stm32f4xx.h"
#include <math.h>

widgetSetup::widgetSetup(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::widgetSetup)
{
    ui->setupUi(this);

    for (int i = 0 ;i < 8; i++)
    {
        QString str ;
        str = QString("Fpclk/%1").arg(pow(2,i+1));
        ui->comboSpeed->addItem(str,i);
    }
}

widgetSetup::~widgetSetup()
{
    delete ui;
}

void widgetSetup::SetCrSetting(QByteArray & data)
{
    if (!data.contains("conf"))
        return;

    QByteArray temp = data;
    temp.remove(0,temp.indexOf("conf "));

    temp.replace("conf","");
    temp.replace("ch>","");
    temp = temp.trimmed();

    bool ok;
    quint32 cr = temp.toInt(&ok);
    Q_ASSERT(ok);

    ui->checkCPHA->setChecked(false);
    ui->checkCPOL->setChecked(false);

    if (cr & SPI_CR1_CPHA)
        ui->checkCPHA->setChecked(true);

    if (cr & SPI_CR1_CPOL)
        ui->checkCPOL->setChecked(true);

    cr = (cr >> 3) & 0b111;

    ui->comboSpeed->setCurrentIndex(cr);
}

void widgetSetup::on_butRead_clicked()
{
    emit writeToCom("read_conf");
}

void widgetSetup::on_butPlay_clicked()
{
    //vygenerovat data
    quint32 cr = 0;

    if (ui->checkCPHA->isChecked())
        cr |= SPI_CR1_CPHA;

    if (ui->checkCPOL->isChecked())
        cr |= SPI_CR1_CPOL;

    int j = ui->comboSpeed->itemData(ui->comboSpeed->currentIndex()).toInt();

    cr |= j << 3;

    QByteArray arr;
    arr = "setup ";
    arr += QByteArray::number(cr);

    emit writeToCom(arr);

}
