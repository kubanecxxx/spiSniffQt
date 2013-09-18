#ifndef WIDGETZDROJ_H
#define WIDGETZDROJ_H

#include <QWidget>
#include <QTimer>
#include <widgetdata.h>

namespace Ui {
class widgetZdroj;
}

class widgetZdroj : public QWidget
{
    Q_OBJECT

public:
    explicit widgetZdroj(QWidget *parent = 0);
    ~widgetZdroj();
    void setpreslkj(widgetData * w);

private:
    Ui::widgetZdroj *ui;
    QTimer * timer;
    int machine;
    widgetData * widget;


private slots:
    void timeout(void);
    void newData(QByteArray data);
};

#endif // WIDGETZDROJ_H
