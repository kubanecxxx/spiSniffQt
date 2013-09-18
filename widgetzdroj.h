#ifndef WIDGETZDROJ_H
#define WIDGETZDROJ_H

#include <QWidget>
#include <QTimer>
#include <widgetdata.h>

namespace Ui {
class widgetZdroj;
}

class QTreeWidgetItem;
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
    int last;


private slots:
    void timeout(void);
    void newData(QByteArray data);
    void on_treeWidget_itemChanged(QTreeWidgetItem *item, int column);
};

#endif // WIDGETZDROJ_H
