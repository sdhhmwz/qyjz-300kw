#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

#include "canthread.h"
#include "syssettingwindow.h"
#include "protcolthread.h"
#include "pccanthread.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    //获取单例对象的方法
    static MainWindow *getInstance();
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    //持有唯一实例，保持全局唯一性
    static MainWindow * mainWin;

    //CAN接受线程
    CanThread canThread;
    ProtcolThread protoTh;
    pccanthread pcthread;
    //界面刷新定时器
    QTimer * timer1;


private slots:
    void updatewin();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
};
#endif // MAINWINDOW_H
