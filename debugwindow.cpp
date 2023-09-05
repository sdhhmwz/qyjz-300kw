#include "debugwindow.h"
#include "ui_debugwindow.h"
#include "GlobalData.h"
#include "syssettingwindow.h"

DebugWindow * DebugWindow::debugWin = NULL;

 DebugWindow * DebugWindow::getInstance()
{
    if(debugWin == NULL)
    {
        debugWin = new DebugWindow();
    }
    return debugWin;
}

DebugWindow::DebugWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DebugWindow)
{
    //去掉标题栏
    this->setWindowFlags(Qt::FramelessWindowHint);
    ui->setupUi(this);

}

DebugWindow::~DebugWindow()
{
    delete ui;
}

//重写paint事件
void DebugWindow::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget,&opt,&p,this);
}

//关闭调试界面
void DebugWindow::on_btnexit_clicked()
{
    timer->stop();
    SysSettingWindow  * systemSetting =  SysSettingWindow::getInstance();
    this->close();  
    systemSetting->show();
}



//DC1
//正极主接触器KM1/KM3控制
void DebugWindow::on_btnKM13ON_clicked()
{
    status_byte0 = ((status_byte0 & 0xFE) | ON);
    sendcmd(0x040020CC,0x0D,status_byte0,status_byte1);
}

void DebugWindow::on_btnKM13OFF_clicked()
{
    status_byte0 = ((status_byte0 & 0xFE) | OFF);
    sendcmd(0x040020CC,0x0D,status_byte0,status_byte1);
}

//负极主接触器KM2/KM4控制
void DebugWindow::on_btnKM24ON_clicked()
{
    status_byte0 = ((status_byte0 & 0xFD) | (ON << 1));
    sendcmd(0x040020CC,0x0D,status_byte0,status_byte1);
}

void DebugWindow::on_btnKM13OFF_2_clicked()
{
    status_byte0 = ((status_byte0 & 0xFD) | (OFF << 1));

    sendcmd(0x040020CC,0x0D,status_byte0,status_byte1);
}

//分档电流接触器KM9/KM10控制
void DebugWindow::on_btnKM910ON_clicked()
{
    status_byte0 = ((status_byte0 & 0xFB) | (ON << 2));
    sendcmd(0x040020CC,0x0D,status_byte0,status_byte1);
}

void DebugWindow::on_btnKM910OFF_clicked()
{
    status_byte0 = ((status_byte0 & 0xFB) | (OFF << 2));
    sendcmd(0x040020CC,0x0D,status_byte0,status_byte1);
}

//直流模块风机控制
void DebugWindow::on_btnKM910ON_2_clicked()
{
    status_byte0 = ((status_byte0 & 0xF7) | (ON << 3));
    sendcmd(0x040020CC,0x0D,status_byte0,status_byte1);
}

void DebugWindow::on_btnKM910OFF_2_clicked()
{
    status_byte0 = ((status_byte0 & 0xF7) | (OFF << 3));
    sendcmd(0x040020CC,0x0D,status_byte0,status_byte1);
}

//通道故障输出到BMS控制
void DebugWindow::on_btnKM910ON_3_clicked()
{
    status_byte0 = ((status_byte0 & 0xEF) | (ON << 4));
    sendcmd(0x040020CC,0x0D,status_byte0,status_byte1);
}

void DebugWindow::on_btnKM910OFF_3_clicked()
{
    status_byte0 = ((status_byte0 & 0xEF) | (OFF << 4));
    sendcmd(0x040020CC,0x0D,status_byte0,status_byte1);
}

//PMW测试指令控制
void DebugWindow::on_btnPMWON_3_clicked()
{
    status_byte0 = ((status_byte0 & 0xDF) | (ON << 5));
    sendcmd(0x040020CC,0x0D,status_byte0,status_byte1);
}

void DebugWindow::on_btnPMWOFF_3_clicked()
{
    status_byte0 = ((status_byte0 & 0xDF) | (OFF << 5));
    sendcmd(0x040020CC,0x0D,status_byte0,status_byte1);
}

//直流故障信号
void DebugWindow::on_btnPMWON_clicked()
{
    status_byte0 = ((status_byte0 & 0xBF) | (ON << 6));
    sendcmd(0x040020CC,0x0D,status_byte0,status_byte1);
}

void DebugWindow::on_btnPMWOFF_clicked()
{
    status_byte0 = ((status_byte0 & 0xBF) | (OFF << 6));
    sendcmd(0x040020CC,0x0D,status_byte0,status_byte1);
}

//直流故障报警指示灯控制
void DebugWindow::on_btnPMWON_2_clicked()
{
    status_byte0 = ((status_byte0 & 0x7F) | (ON << 7));
    sendcmd(0x040020CC,0x0D,status_byte0,status_byte1);
}

void DebugWindow::on_btnPMWOFF_2_clicked()
{
    status_byte0 = ((status_byte0 & 0x7F) | (OFF << 7));
    sendcmd(0x040020CC,0x0D,status_byte0,status_byte1);
}

//直流运行指示灯控制
void DebugWindow::on_btnKA34ON_clicked()
{
    status_byte1 = ((status_byte1 & 0xFE) | ON);
    sendcmd(0x040020CC,0x0D,status_byte0,status_byte1);
}

void DebugWindow::on_btnKA34OFF_clicked()
{
    status_byte1 = ((status_byte1 & 0xFE) | OFF);
    sendcmd(0x040020CC,0x0D,status_byte0,status_byte1);
}

//直流待机指示灯控制
void DebugWindow::on_btnPMWON_4_clicked()
{
    status_byte1 = ((status_byte1 & 0xFD) | (ON << 1));
    sendcmd(0x040020CC,0x0D,status_byte0,status_byte1);
}

void DebugWindow::on_btnPMWOFF_4_clicked()
{
    status_byte1 = ((status_byte1 & 0xFD) | (OFF << 1));
    sendcmd(0x040020CC,0x0D,status_byte0,status_byte1);
}

//DC2
//正极主接触器KM1/KM3控制
void DebugWindow::on_btnKM13ON_2_clicked()
{
    status_byte0_dc2 = ((status_byte0_dc2 & 0xFE) | ON);
    sendcmd(0x040021CC,0x0D,status_byte0_dc2,status_byte1_dc2);
}

void DebugWindow::on_btnKM13OFF_4_clicked()
{
    status_byte0_dc2 = ((status_byte0_dc2 & 0xFE) | OFF);
    sendcmd(0x040021CC,0x0D,status_byte0_dc2,status_byte1_dc2);
}

//负极主接触器KM2/KM4控制
void DebugWindow::on_btnKM24ON_2_clicked()
{
    status_byte0_dc2 = ((status_byte0_dc2 & 0xFD) | (ON << 1));
    sendcmd(0x040021CC,0x0D,status_byte0_dc2,status_byte1_dc2);
}

void DebugWindow::on_btnKM13OFF_3_clicked()
{
    status_byte0_dc2 = ((status_byte0_dc2 & 0xFD) | (OFF << 1));
    sendcmd(0x040021CC,0x0D,status_byte0_dc2,status_byte1_dc2);
}

//分档电流接触器KM9/KM10控制
void DebugWindow::on_btnKM910ON_6_clicked()
{
    status_byte0_dc2 = ((status_byte0_dc2 & 0xFB) | (ON << 2));
    sendcmd(0x040021CC,0x0D,status_byte0_dc2,status_byte1_dc2);
}

void DebugWindow::on_btnKM910OFF_6_clicked()
{
    status_byte0_dc2 = ((status_byte0_dc2 & 0xFB) | (OFF << 2));
    sendcmd(0x040021CC,0x0D,status_byte0_dc2,status_byte1_dc2);
}

//直流模块风机控制
void DebugWindow::on_btnKM910ON_4_clicked()
{
    status_byte0_dc2 = ((status_byte0_dc2 & 0xF7) | (ON << 3));
    sendcmd(0x040021CC,0x0D,status_byte0_dc2,status_byte1_dc2);
}

void DebugWindow::on_btnKM910OFF_4_clicked()
{
    status_byte0_dc2 = ((status_byte0_dc2 & 0xF7) | (OFF << 3));
    sendcmd(0x040021CC,0x0D,status_byte0_dc2,status_byte1_dc2);
}

//通道故障输出到BMS控制
void DebugWindow::on_btnKM910ON_5_clicked()
{
    status_byte0_dc2 = ((status_byte0_dc2 & 0xEF) | (ON << 4));
    sendcmd(0x040021CC,0x0D,status_byte0_dc2,status_byte1_dc2);
}

void DebugWindow::on_btnKM910OFF_5_clicked()
{
    status_byte0_dc2 = ((status_byte0_dc2 & 0xEF) | (OFF << 4));
    sendcmd(0x040021CC,0x0D,status_byte0_dc2,status_byte1_dc2);
}

//PMW测试指令控制
void DebugWindow::on_btnPMWON_6_clicked()
{
    status_byte0_dc2 = ((status_byte0_dc2 & 0xDF) | (ON << 5));
    sendcmd(0x040021CC,0x0D,status_byte0_dc2,status_byte1_dc2);
}

void DebugWindow::on_btnPMWOFF_6_clicked()
{
    status_byte0_dc2 = ((status_byte0_dc2 & 0xDF) | (OFF << 5));
    sendcmd(0x040021CC,0x0D,status_byte0_dc2,status_byte1_dc2);
}

//直流故障信号
void DebugWindow::on_btnPMWON_7_clicked()
{
    status_byte0_dc2 = ((status_byte0_dc2 & 0xBF) | (ON << 6));
    sendcmd(0x040021CC,0x0D,status_byte0_dc2,status_byte1_dc2);
}

void DebugWindow::on_btnPMWOFF_7_clicked()
{
    status_byte0_dc2 = ((status_byte0_dc2 & 0xBF) | (OFF << 6));
    sendcmd(0x040021CC,0x0D,status_byte0_dc2,status_byte1_dc2);
}

//直流故障报警指示灯控制
void DebugWindow::on_btnPMWON_5_clicked()
{
    status_byte0_dc2 = ((status_byte0_dc2 & 0x7F) | (ON << 7));
    sendcmd(0x040021CC,0x0D,status_byte0_dc2,status_byte1_dc2);
}

void DebugWindow::on_btnPMWOFF_5_clicked()
{
    status_byte0_dc2 = ((status_byte0_dc2 & 0x7F) | (OFF << 7));
    sendcmd(0x040021CC,0x0D,status_byte0_dc2,status_byte1_dc2);
}

//直流运行指示灯控制
void DebugWindow::on_btnKA34ON_2_clicked()
{
    status_byte1_dc2 = ((status_byte1_dc2 & 0xFE) | (ON << 0));
    sendcmd(0x040021CC,0x0D,status_byte0_dc2,status_byte1_dc2);
}

void DebugWindow::on_btnKA34OFF_2_clicked()
{
    status_byte1_dc2 = ((status_byte1_dc2 & 0xFE) | (OFF << 0));
    sendcmd(0x040021CC,0x0D,status_byte0_dc2,status_byte1_dc2);
}

//直流待机指示灯控制
void DebugWindow::on_btnPMWON_8_clicked()
{
    status_byte1_dc2 = ((status_byte1_dc2 & 0xFD) | (ON << 1));
    sendcmd(0x040021CC,0x0D,status_byte0_dc2,status_byte1_dc2);
}

void DebugWindow::on_btnPMWOFF_8_clicked()
{
    status_byte1_dc2 = ((status_byte1_dc2 & 0xFD) | (OFF << 1));
    sendcmd(0x040021CC,0x0D,status_byte0_dc2,status_byte1_dc2);
}


//AC
//交流主接触器KM6控制
void DebugWindow::on_btnKM13ON_4_clicked()
{
    status_byte0_ac = ((status_byte0_ac & 0xFE) | (ON << 0));
    sendcmd(0x0400A0CC,0x10,status_byte0_ac,status_byte1_ac);
}

void DebugWindow::on_btnKM13OFF_7_clicked()
{
    status_byte0_ac = ((status_byte0_ac & 0xFE) | (OFF << 0));
    sendcmd(0x0400A0CC,0x10,status_byte0_ac,status_byte1_ac);
}

//交流充电接触器KM7控制
void DebugWindow::on_btnKM24ON_4_clicked()
{
    status_byte0_ac = ((status_byte0_ac & 0xFD) | (ON << 1));
    sendcmd(0x0400A0CC,0x10,status_byte0_ac,status_byte1_ac);
}

void DebugWindow::on_btnKM13OFF_8_clicked()
{
    status_byte0_ac = ((status_byte0_ac & 0xFD) | (OFF << 1));
    sendcmd(0x0400A0CC,0x10,status_byte0_ac,status_byte1_ac);
}

//母线放电接触器KM5控制
void DebugWindow::on_btnKM910ON_11_clicked()
{
    status_byte0_ac = ((status_byte0_ac & 0xFB) | (ON << 2));
    sendcmd(0x0400A0CC,0x10,status_byte0_ac,status_byte1_ac);
}

void DebugWindow::on_btnKM910OFF_11_clicked()
{
    status_byte0_ac = ((status_byte0_ac & 0xFB) | (OFF << 2));
    sendcmd(0x0400A0CC,0x10,status_byte0_ac,status_byte1_ac);
}

//交流模块风机控制
void DebugWindow::on_btnKM910ON_10_clicked()
{
    status_byte0_ac = ((status_byte0_ac & 0xF7) | (ON << 3));
    sendcmd(0x0400A0CC,0x10,status_byte0_ac,status_byte1_ac);
}

void DebugWindow::on_btnKM910OFF_10_clicked()
{
    status_byte0_ac = ((status_byte0_ac & 0xF7) | (OFF << 3));
    sendcmd(0x0400A0CC,0x10,status_byte0_ac,status_byte1_ac);
}

//机柜风机控制
void DebugWindow::on_btnPMWON_15_clicked()
{
    status_byte0_ac = ((status_byte0_ac & 0xEF) | (ON << 4));
    sendcmd(0x0400A0CC,0x10,status_byte0_ac,status_byte1_ac);
}

void DebugWindow::on_btnPMWOFF_15_clicked()
{
    status_byte0_ac = ((status_byte0_ac & 0xEF) | (OFF << 4));
    sendcmd(0x0400A0CC,0x10,status_byte0_ac,status_byte1_ac);
}

//运行指示灯控制
void DebugWindow::on_btnPMWON_13_clicked()
{
    status_byte0_ac = ((status_byte0_ac & 0xDF) | (ON << 5));
    sendcmd(0x0400A0CC,0x10,status_byte0_ac,status_byte1_ac);
}

void DebugWindow::on_btnPMWOFF_13_clicked()
{
    status_byte0_ac = ((status_byte0_ac & 0xDF) | (OFF << 5));
    sendcmd(0x0400A0CC,0x10,status_byte0_ac,status_byte1_ac);
}

//PMW测试指令控制
void DebugWindow::on_btnPMWON_14_clicked()
{
    status_byte0_ac = ((status_byte0_ac & 0x7F) | (ON << 7));
    sendcmd(0x0400A0CC,0x10,status_byte0_ac,status_byte1_ac);
}

void DebugWindow::on_btnPMWOFF_14_clicked()
{
    status_byte0_ac = ((status_byte0_ac & 0x7F) | (OFF << 7));
    sendcmd(0x0400A0CC,0x10,status_byte0_ac,status_byte1_ac);
}

//交流故障输出控制
void DebugWindow::on_btnKA34ON_4_clicked()
{
    status_byte1_ac = ((status_byte1_ac & 0xFE) | (ON << 0));
    sendcmd(0x0400A0CC,0x10,status_byte0_ac,status_byte1_ac);
}

void DebugWindow::on_btnKA34OFF_4_clicked()
{
    status_byte1_ac = ((status_byte1_ac & 0xFE) | (OFF << 0));
    sendcmd(0x0400A0CC,0x10,status_byte0_ac,status_byte1_ac);
}


















