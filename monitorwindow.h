#ifndef MONITORWINDOW_H
#define MONITORWINDOW_H

#include <QWidget>
#include "loginwindow.h"


namespace Ui {
class MonitorWindow;
}

class MonitorWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MonitorWindow(QWidget *parent = nullptr);
    //获取单例对象的方法
    static MonitorWindow *getInstance();
    ~MonitorWindow();
    //界面数据刷新
    void UpdateWin();
protected:
    void paintEvent(QPaintEvent *event);

private slots:
    void on_pushButton_clicked();

private:
    Ui::MonitorWindow *ui;
    static MonitorWindow * monitorwin;
};

#endif // MONITORWINDOW_H
