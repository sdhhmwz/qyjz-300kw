#ifndef WORKSTATUS_H
#define WORKSTATUS_H

#include <QWidget>

namespace Ui {
class WorkStatus;
}

class WorkStatus : public QWidget
{
    Q_OBJECT

public:
    explicit WorkStatus(QWidget *parent = nullptr);
    //获取单例对象的方法
    static WorkStatus *getInstance();
    ~WorkStatus();

    void UpdateWin();
protected:
    void paintEvent(QPaintEvent *event);

private slots:
    void on_btnexit_clicked();

private:
    Ui::WorkStatus *ui;
    //持有唯一实例，保持全局唯一性
    static WorkStatus * WorkStatusWin;

};

#endif // WORKSTATUS_H
