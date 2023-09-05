#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "errorwindow.h"
#include "GlobalData.h"
#include "workstatus.h"
#include "monitorwindow.h"

#include <QtNetwork>

MainWindow * MainWindow::mainWin = NULL;

 MainWindow * MainWindow::getInstance()
{
    if(mainWin == NULL)
    {
        mainWin = new MainWindow();
    }

    return mainWin;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    //去掉标题栏
    this->setWindowFlags(Qt::FramelessWindowHint);
    ui->setupUi(this);
    mainWin = this;

    //初始化系统设置界面
    SysSettingWindow * SysSetWindow = SysSettingWindow::getInstance();
    ErrorWindow * errwin = ErrorWindow::getInstance();
    WorkStatus::getInstance();
    MonitorWindow * monitorwin = MonitorWindow::getInstance();

    //波特率500kbps
    //MCU CAN
     int tflage = canThread.Initial(250000);
     if(tflage<0)
     {
//         ui->text->append(tr("can0通信初始化异常！请断电检查"));
     }

     //PC CAN
     int flage = pcthread.Initial(250000);
     if(flage<0)
     {
//         ui->text->append(tr("can1通信初始化异常！请断电检查"));
     }


     //CAN启动线程
     canThread.start();
     canThread.restart();
     //PC CAN启动线程
     pcthread.start();
     pcthread.restart();
     //END

     SysSetWindow->canThreadsend = &canThread;
     //protoTh.pCanTh = &canThread;

    timer1 = new QTimer(this);
    //添加信号与槽
    //调试参数
    //后期考虑取消协议解析线程
     QObject::connect(&canThread, SIGNAL(UpdateMsg(canFrame)),
                          &protoTh, SLOT(Update(canFrame)));
    //DC1运行数据
     QObject::connect(&canThread, SIGNAL(UpdateDc1(canFrame)),
                          &protoTh, SLOT(DataAnalCanID_DC1(canFrame)));
    //DC2运行数据
     QObject::connect(&canThread, SIGNAL(UpdateDc2(canFrame)),
                          &protoTh, SLOT(DataAnalCanID_DC2(canFrame)));
    //AC运行数据
     QObject::connect(&canThread, SIGNAL(UpdateAC(canFrame)),
                          &protoTh, SLOT(DataAnalCanID_AC(canFrame)));
     //MCU向PC转发数据
     QObject::connect(&canThread, SIGNAL(DatatoPC(canFrame)),
                         &pcthread, SLOT(SendMsgPC(canFrame)));
    //PC向MCU转发数据
     QObject::connect(&pcthread, SIGNAL(DatatoMCU(canFrame)),
                         &canThread, SLOT(SendMsg(canFrame)));
    //错误数据刷新
     QObject::connect(&canThread, SIGNAL(DataError(canFrame)),
                         errwin, SLOT(ErrorDataAlysis(canFrame)));
     QObject::connect(&canThread, SIGNAL(DC1DataError(canFrame)),
                         errwin, SLOT(DC1ErrorDataAlysis(canFrame)));
     QObject::connect(&canThread, SIGNAL(DC2DataError(canFrame)),
                         errwin, SLOT(DC2ErrorDataAlysis(canFrame)));
     QObject::connect(&pcthread, SIGNAL(Clearerror()),
                         errwin, SLOT(on_pushButton_4_clicked()));

     //监控界面/主界面/工作状态/错误界面刷新
     connect(timer1,&QTimer::timeout,this,&MainWindow::updatewin);

    //添加线程开始
     protoTh.stop();
     protoTh.Initial();
    // protoTh.IsRunning = false;
     protoTh.start();
     protoTh.restart();

    //主界面刷新定时器
    timer1->start(2000);

    //监控界面显示
    monitorwin->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

/**********************************************************/
//函数：系统设置点击事件
//功能：跳转到系统设置界面
//date：2023/4/10
/**********************************************************/
void MainWindow::on_pushButton_2_clicked()
{
//    SysSettingWindow  * systemSetting =  SysSettingWindow::getInstance();
//     this->close();
//   // systemSetting->init(flageruning,flagejdq);
//    systemSetting->show();
     MonitorWindow * monitorwin = MonitorWindow::getInstance();
     this->close();
     monitorwin->show();
}

/**********************************************************/
//函数：告警信息点击事件
//功能：跳转到系统设置界面
//date：2023/4/20
/**********************************************************/
void MainWindow::on_pushButton_3_clicked()
{
    ErrorWindow * errwin = ErrorWindow::getInstance();
    this->close();
    //errwin->InitTable();
    errwin->show();
}

/**********************************************************/
//函数：工作状态点击事件
//功能：跳转到工作状态
//date：2023/4/26
/**********************************************************/
void MainWindow::on_pushButton_4_clicked()
{
     WorkStatus * StatusWin = WorkStatus::getInstance();
     this->close();
     StatusWin->show();
}


//定时器刷新事件
void MainWindow::updatewin()
{
    //can发送数据监控
    //CAN0
//     ui->text->setText(QString::number((canThread.errsendcount)));
//     //CAN1
//     ui->text->append(QString::number((pcthread.errsendcount)));
     //end

    //监控界面数据刷新
    MonitorWindow::getInstance()->UpdateWin();

    //错误界面刷新
//    ErrorWindow::getInstance()->UpdateWin();

    //工作状态数据刷新，只有在工作状态界面才会刷数据
    WorkStatus::getInstance()->UpdateWin();
    //不在主窗口，停止刷新数据
    if(!this->isActiveWindow())
    {
        return;
    }
    //主窗口数据刷新
    //DC1
    ui->label_229->setText(QString::number(OperMonModelDC1.BA_UBAT,'f',3));
    ui->label_230->setText(QString::number(OperMonModelDC1.BA_IBAT,'f',3));
    ui->label_231->setText(QString::number(OperMonModelDC1.BA_PIN,'f',3));
    ui->label_232->setText(QString::number(OperMonModelDC1.BA_T1_BA_T3,'f',1));
    ui->label_233->setText(QString::number(OperMonModelDC1.BA_T2_BA_T4,'f',1));
    ui->label_234->setText(QString::number(OperMonModelDC1.BA_CHWH,'f',3));
    ui->label_235->setText(QString::number(OperMonModelDC1.BA_DISWH,'f',3));
    ui->label_236->setText(QString::number(OperMonModelDC1.BA_I1_BA_I3,'f',3));
    ui->label_237->setText(QString::number(OperMonModelDC1.BA_I2_BA_I4,'f',3));
    ui->label_238->setText(QString::number(OperMonModelDC1.BA_CHAH,'f',3));
    ui->label_239->setText(QString::number(OperMonModelDC1.BA_DISAH,'f',3));
    ui->label_244->setText(QString::number(OperMonModelDC1.BA_UBAT_IN,'f',1));
    ui->label_245->setText(QString::number(OperMonModelDC1.BA_UDC,'f',1));
    //DC2
    ui->label_111->setText(QString::number(OperMonModelDC2.BA_UBAT,'f',3));
    ui->label_112->setText(QString::number(OperMonModelDC2.BA_IBAT,'f',3));
    ui->label_113->setText(QString::number(OperMonModelDC2.BA_PIN,'f',3));
    ui->label_114->setText(QString::number(OperMonModelDC2.BA_T1_BA_T3,'f',1));
    ui->label_115->setText(QString::number(OperMonModelDC2.BA_T2_BA_T4,'f',1));
    ui->label_116->setText(QString::number(OperMonModelDC2.BA_CHWH,'f',3));
    ui->label_117->setText(QString::number(OperMonModelDC2.BA_DISWH,'f',3));
    ui->label_118->setText(QString::number(OperMonModelDC2.BA_I1_BA_I3,'f',3));
    ui->label_119->setText(QString::number(OperMonModelDC2.BA_I2_BA_I4,'f',3));
    ui->label_140->setText(QString::number(OperMonModelDC2.BA_CHAH,'f',3));
    ui->label_141->setText(QString::number(OperMonModelDC2.BA_DISAH,'f',3));
    ui->label_182->setText(QString::number(OperMonModelDC2.BA_UBAT_IN,'f',1));
    ui->label_191->setText(QString::number(OperMonModelDC2.BA_UDC,'f',1));
    //AC
    ui->label_163->setText(QString::number(OperMonModelAC.BA_UAB1,'f',2));
    ui->label_164->setText(QString::number(OperMonModelAC.BA_UBC1,'f',2));
    ui->label_165->setText(QString::number(OperMonModelAC.BA_UCA1,'f',2));
    ui->label_166->setText(QString::number(OperMonModelAC.BA_IA1,'f',2));
    ui->label_167->setText(QString::number(OperMonModelAC.BA_IB1,'f',2));
    ui->label_168->setText(QString::number(OperMonModelAC.BA_IC1,'f',2));
    ui->label_169->setText(QString::number(OperMonModelAC.BA_AT*1.0/10,'f',1));
    ui->label_170->setText(QString::number(OperMonModelAC.BA_BT*1.0/10,'f',1));
    ui->label_171->setText(QString::number(OperMonModelAC.BA_CT*1.0/10,'f',1));
    ui->label_172->setText(QString::number(OperMonModelAC.BA_ENERGY,'f',3));
    ui->label_173->setText(QString::number(OperMonModelAC.BA_CHENERGY,'f',3));
    ui->label_174->setText(QString::number(OperMonModelAC.BA_UNd,'f',0));
    ui->label_175->setText(QString::number(OperMonModelAC.BA_UNq,'f',0));
    ui->label_176->setText(QString::number(OperMonModelAC.BA_UDC*1.0/10,'f',1));
    ui->label_177->setText(QString::number(OperMonModelAC.BA_UDCREF*1.0/10,'f',1));
    ui->label_178->setText(QString::number(OperMonModelAC.BA_POWFACTOR*1.0/100,'f',2));
    ui->label_179->setText(QString::number(OperMonModelAC.BA_FREQ,'f',2));
    ui->label_180->setText(QString::number(OperMonModelAC.BA_POUT*1.0/100,'f',2));
    ui->label_181->setText(QString::number(OperMonModelAC.BA_QOUT*1.0/100,'f',2));


}

//登录界面
void MainWindow::on_pushButton_5_clicked()
{

    LoginWindow * loginwin = LoginWindow::getInstance();
    loginwin->syssetclicked = true;
    this->close();
    loginwin->show();
}

