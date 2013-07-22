#ifndef WIDGETCOM_H
#define WIDGETCOM_H

#include <QWidget>
#include "qextserialport.h"

namespace Ui {
class widgetCom;
}

class widgetCom : public QWidget
{
    Q_OBJECT
    
public:
    explicit widgetCom(QWidget *parent = 0);
    ~widgetCom();
    QextSerialPort * comport;
    
private slots:
    void on_butRefresh_clicked(bool checked);
    void on_butOpen_clicked();
    void on_butClose_clicked();

private:
    Ui::widgetCom *ui;
    void FillCombo();

signals:
    void roznout(bool);
    void message(QString);

};

#endif // WIDGETCOM_H
