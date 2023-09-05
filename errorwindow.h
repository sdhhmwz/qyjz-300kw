#ifndef ERRORWINDOW_H
#define ERRORWINDOW_H

#include <QWidget>
#include <QPainter>
#include <QStandardItemModel>
#include <QTime>
#include "canthread.h"

namespace Ui {
class ErrorWindow;
}

class ErrorWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ErrorWindow(QWidget *parent = nullptr);
    //获取单例对象的方法
    static ErrorWindow *getInstance();
    ~ErrorWindow();
    //初始化列表
    void InitTable();
// void InsertRow(QString weizhi,QString  riqi,QString shijian,QString guzhang);
//    void UpdateWin();

protected:
    void paintEvent(QPaintEvent *event);

private slots:
    void on_pushButton_clicked();
//    void on_pushButton_2_clicked();
    void on_pushButton_4_clicked();

    void ErrorDataAlysis(canFrame qData);
    void DC1ErrorDataAlysis(canFrame qData);
    void DC2ErrorDataAlysis(canFrame qData);

private:
    Ui::ErrorWindow *ui;
    //持有唯一实例，保持全局唯一性
    static ErrorWindow * ErrorWin;
    QStandardItemModel * modelerror;
    //接收传来的数据
    canFrame recvFrame;
    uint8_t errcode = 0;
    uint8_t dc1errcode = 0xFF;
    uint8_t dc2errcode = 0xFF;
    uint8_t acerrcode = 0xFF;
    //错误通道,错误代码
    QString errchannel,err;
    bool update = false;

};

#endif // ERRORWINDOW_H
