#include "workstatus.h"
#include "ui_workstatus.h"
#include "mainwindow.h"
#include <QStyleOption>
#include "GlobalData.h"

WorkStatus * WorkStatus::WorkStatusWin = NULL;

 WorkStatus * WorkStatus::getInstance()
{
    if(WorkStatusWin == NULL)
    {
        WorkStatusWin = new WorkStatus();
    }

    return WorkStatusWin;
}

WorkStatus::WorkStatus(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WorkStatus)
{
    //去掉标题栏
    this->setWindowFlags(Qt::FramelessWindowHint);
    ui->setupUi(this);
}

WorkStatus::~WorkStatus()
{
    delete ui;
}

void WorkStatus::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget,&opt,&p,this);
}

/**********************************************************/
//函数：主界面按钮点击事件
//功能：跳转到主界面
//date：2023/4/26
/**********************************************************/
void WorkStatus::on_btnexit_clicked()
{
    MainWindow * diaglog = MainWindow::getInstance();
    this->close();
    //diaglog->initUI();
    diaglog->show();
}

void WorkStatus::UpdateWin()
{
    //不在此窗口，停止刷新数据
    if(!this->isActiveWindow())
    {
        return;
    }

  ui->label_229->setText(S_WorkStatusDC1.DOMODE);
  ui->label_230->setText(S_WorkStatusDC1.RUNNING);
  ui->label_231->setText(S_WorkStatusDC1.STOP_CASE);
  ui->label_232->setText(S_WorkStatusDC1.CHANNELMODE);
  ui->label_233->setText(S_WorkStatusDC1.KA5FB);
  ui->label_234->setText(S_WorkStatusDC1.BMSFB);
  ui->label_235->setText(S_WorkStatusDC1.L1OTFB);
  ui->label_236->setText(S_WorkStatusDC1.L2OTFB);
  ui->label_237->setText(S_WorkStatusDC1.ACERRORFB);

  ui->label_238->setText(S_WorkStatusDC2.DOMODE);
  ui->label_239->setText(S_WorkStatusDC2.RUNNING);
  ui->label_241->setText(S_WorkStatusDC2.STOP_CASE);
  ui->label_242->setText(S_WorkStatusDC2.CHANNELMODE);
  ui->label_243->setText(S_WorkStatusDC2.KA5FB);
  ui->label_244->setText(S_WorkStatusDC2.BMSFB);
  ui->label_245->setText(S_WorkStatusDC2.L1OTFB);
  ui->label_246->setText(S_WorkStatusDC2.L2OTFB);
  ui->label_247->setText(S_WorkStatusDC2.ACERRORFB);

  ui->label_250->setText(S_WorkStatusAc.GRIDMODEFB);
  ui->label_251->setText(S_WorkStatusAc.RUNNING);
  ui->label_252->setText(S_WorkStatusAc.KM6FB);
  ui->label_253->setText(S_WorkStatusAc.KM7FB);
  ui->label_254->setText(S_WorkStatusAc.DCERRORFB);
  ui->label_255->setText(S_WorkStatusAc.Q2FB);
  ui->label_256->setText(S_WorkStatusAc.S1FB);
  ui->label_257->setText(S_WorkStatusAc.T1OTPFB);
  ui->label_258->setText(S_WorkStatusAc.T1OTWFB);
  ui->label_259->setText(S_WorkStatusAc.PHASEFB);

}
