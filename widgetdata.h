#ifndef WIDGETDATA_H
#define WIDGETDATA_H

#include <QWidget>

class QListWidgetItem;
namespace Ui {
class widgetData;
}

class widgetData : public QWidget
{
    Q_OBJECT
    
public:
    explicit widgetData(QWidget *parent = 0);
    ~widgetData();
    void newData(QByteArray & data);
    
private slots:
    void on_butExchangeData_clicked();
    void on_editSend_returnPressed();
    void on_listWidget_itemClicked(QListWidgetItem *item);
    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::widgetData *ui;
    void addItem(const QString & name,const QByteArray & data);
    void addItem(const char * name, const char * data)
    {
        addItem(QString(name), QByteArray(data));
    }

public slots:
    void exchangeData(const QByteArray & in);

signals:
    void SendCom(QByteArray);
    void exchangedData(const QByteArray & data);
};

#endif // WIDGETDATA_H
