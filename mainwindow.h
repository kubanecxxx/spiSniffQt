#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qextserialport.h"
#include "hled.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QextSerialPort * comport;

    HLed * led;

private slots:
    void roznout(bool );
    void comportNewData(void);
    void comportSendData(QByteArray);
    void comportTimeout(void);

};

#endif // MAINWINDOW_H
