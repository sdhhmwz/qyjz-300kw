#ifndef DEBUGWINDOW_H
#define DEBUGWINDOW_H

#include <QWidget>
#include <QPainter>
#include "canthread.h"


namespace Ui {
class DebugWindow;
}

class DebugWindow : public QWidget
{
    Q_OBJECT

public:
    explicit DebugWindow(QWidget *parent = nullptr);
    //获取单例对象的方法
    static DebugWindow *getInstance();
    ~DebugWindow();

    CanThread *canThreadsenddc1;
    void init();

protected:
    void paintEvent(QPaintEvent *event);

private slots:
    void on_btnexit_clicked();

    void on_btnKM13ON_clicked();

    void on_btnKM13OFF_clicked();

    void on_btnKM24ON_clicked();

    void on_btnKM13OFF_2_clicked();

    void on_btnKM910ON_clicked();

    void on_btnKM910OFF_clicked();

    void on_btnKM910ON_2_clicked();

    void on_btnKM910OFF_2_clicked();

    void on_btnKM910ON_3_clicked();

    void on_btnKM910OFF_3_clicked();

    void on_btnPMWON_3_clicked();

    void on_btnPMWOFF_3_clicked();

    void on_btnPMWON_clicked();

    void on_btnPMWOFF_clicked();

    void on_btnPMWON_2_clicked();

    void on_btnPMWOFF_2_clicked();

    void on_btnKA34ON_clicked();

    void on_btnKA34OFF_clicked();

    void on_btnPMWON_4_clicked();

    void on_btnPMWOFF_4_clicked();

    void on_btnKM13ON_2_clicked();

    void on_btnKM13OFF_4_clicked();

    void on_btnKM24ON_2_clicked();

    void on_btnKM13OFF_3_clicked();

    void on_btnKM910ON_6_clicked();

    void on_btnKM910OFF_6_clicked();

    void on_btnKM910ON_4_clicked();

    void on_btnKM910OFF_4_clicked();

    void on_btnKM910ON_5_clicked();

    void on_btnKM910OFF_5_clicked();

    void on_btnPMWON_6_clicked();

    void on_btnPMWOFF_6_clicked();

    void on_btnPMWON_7_clicked();

    void on_btnPMWOFF_7_clicked();

    void on_btnPMWON_5_clicked();

    void on_btnPMWOFF_5_clicked();

    void on_btnKA34ON_2_clicked();

    void on_btnKA34OFF_2_clicked();

    void on_btnPMWON_8_clicked();

    void on_btnPMWOFF_8_clicked();

    void on_btnKM13ON_4_clicked();

    void on_btnKM13OFF_7_clicked();

    void on_btnKM24ON_4_clicked();

    void on_btnKM13OFF_8_clicked();

    void on_btnKM910ON_11_clicked();

    void on_btnKM910OFF_11_clicked();

    void on_btnKM910ON_10_clicked();

    void on_btnKM910OFF_10_clicked();

    void on_btnPMWON_15_clicked();

    void on_btnPMWOFF_15_clicked();

    void on_btnPMWON_13_clicked();

    void on_btnPMWOFF_13_clicked();

    void on_btnPMWON_14_clicked();

    void on_btnPMWOFF_14_clicked();

    void on_btnKA34ON_4_clicked();

    void on_btnKA34OFF_4_clicked();



private:
    Ui::DebugWindow *ui;
    static DebugWindow * debugWin;

    void  sendcmd(long canid,uint8_t commmand,int bytenum,uint8_t value);

    QTimer *timer;


};

#endif // DEBUGWINDOW_H
