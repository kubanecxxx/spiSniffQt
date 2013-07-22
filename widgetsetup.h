#ifndef WIDGETSETUP_H
#define WIDGETSETUP_H

#include <QWidget>

namespace Ui {
class widgetSetup;
}

class widgetSetup : public QWidget
{
    Q_OBJECT
    
public:
    explicit widgetSetup(QWidget *parent = 0);
    ~widgetSetup();
    void SetCrSetting(QByteArray & data);
    
private:
    Ui::widgetSetup *ui;

signals:
    void writeToCom(QByteArray data);
private slots:
    void on_butRead_clicked();
    void on_butPlay_clicked();
};

#endif // WIDGETSETUP_H
