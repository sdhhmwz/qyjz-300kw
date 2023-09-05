#include "errorwindow.h"
#include "ui_errorwindow.h"
#include "mainwindow.h"
#include <QStyleOption>
#include "syssettingwindow.h"
#include "GlobalData.h"
#include "monitorwindow.h"

ErrorWindow * ErrorWindow::ErrorWin = NULL;

 ErrorWindow * ErrorWindow::getInstance()
{
    if(ErrorWin == NULL)
    {
        ErrorWin = new ErrorWindow();
    }
    return ErrorWin;
}

ErrorWindow::ErrorWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ErrorWindow)
{
    //去掉标题栏
    this->setWindowFlags(Qt::FramelessWindowHint);
    ui->setupUi(this);
}

ErrorWindow::~ErrorWindow()
{
    delete ui;
}

//重写paint事件
void ErrorWindow::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget,&opt,&p,this);
}




void ErrorWindow::on_pushButton_clicked()
{
    MainWindow * diaglog = MainWindow::getInstance();
    this->close();
    //diaglog->initUI();
    diaglog->show();
}

//void ErrorWindow::on_pushButton_2_clicked()
//{

//    MonitorWindow * monitorwin = MonitorWindow::getInstance();
//    this->close();
//    monitorwin->show();
//}

void ErrorWindow::on_pushButton_4_clicked()
{
    ui->textEdit->clear();
    dc1errcode = 0xFF;
    dc2errcode = 0xFF;
    acerrcode = 0xFF;
}

void ErrorWindow::ErrorDataAlysis(canFrame qData)
{

    this->recvFrame = qData;
    errcode = recvFrame.data[0];
    //解析错误数据
    QString test = QString::number(recvFrame.canID&0x7fffffff,16);
    //获取当前时间
    QTime tim = QTime::currentTime();
    QString time = tim.toString();
    //判断

    if(acerrcode != errcode)
    {
        acerrcode = errcode;
        errchannel = "AC";
        err = err_ac[acerrcode];
        QString date_msg = QString("%1-%2-%3").arg(time).arg(errchannel).arg(err);
        ui->textEdit->append(date_msg);
    }
    else
    {

    }
}

void ErrorWindow::DC1ErrorDataAlysis(canFrame qData)
{
    this->recvFrame = qData;
    errcode = recvFrame.data[0];
    //解析错误数据
    QString test = QString::number(recvFrame.canID&0x7fffffff,16);
    //获取当前时间
    QTime tim = QTime::currentTime();
    QString time = tim.toString();
    //判断
    if(dc1errcode != errcode)
    {
        dc1errcode = errcode;
        errchannel = "DC1";
        err = err_dc[dc1errcode];
        QString date_msg = QString("%1-%2-%3").arg(time).arg(errchannel).arg(err);
        ui->textEdit->append(date_msg);
    }
    else
    {

    }
}
void ErrorWindow::DC2ErrorDataAlysis(canFrame qData)
{
    this->recvFrame = qData;
    errcode = recvFrame.data[0];
    //解析错误数据
    QString test = QString::number(recvFrame.canID&0x7fffffff,16);
    //获取当前时间
    QTime tim = QTime::currentTime();
    QString time = tim.toString();
    //判断
    if(dc2errcode != errcode)
    {
        dc2errcode = errcode;
        errchannel = "DC2";
        err = err_dc[dc2errcode];
        QString date_msg = QString("%1-%2-%3").arg(time).arg(errchannel).arg(err);
        ui->textEdit->append(date_msg);
    }
    else
    {

    }
}

//初始化表格
void ErrorWindow::InitTable()
{
//    this->modelerror = new QStandardItemModel();   //创建一个标准的条目模型
//    this->ui->tableView->setModel(modelerror);   //将tableview设置成model这个标准条目模型的模板, model设置的内容都将显示在tableview上

//    this->modelerror->setHorizontalHeaderItem(0, new QStandardItem(tr("通道")));
//    this->modelerror->setHorizontalHeaderItem(1, new QStandardItem(tr("日期")) );
//    this->modelerror->setHorizontalHeaderItem(2, new QStandardItem(tr("时间")));
//    this->modelerror->setHorizontalHeaderItem(3, new QStandardItem(tr("故障")));

//    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
//    // 设置最小的宽度
//    ui->tableView->horizontalHeader()->setMinimumSectionSize(180);

    /*setItem设置条目栏中的一个格子的信息*/
//    QTime tim = QTime::currentTime();//获取当前时间
//    QDate date = QDate::currentDate();//获取当前日期
//    QString date_msg = QString("%1-%2-%3").arg(date.year()).arg(date.month()).arg(date.day());

//    for (int var = 0; var < 5; var++)
//    {
//        InsertRow("示例",
//                  date_msg,
//                  tim.toString(),
//                  err_dc[10]
//                   );
//    }
}

//void ErrorWindow::InsertRow(QString weizhi,QString riqi,QString shijian,QString guzhang)
//{
//    int num = modelerror->rowCount();

//QStandardItem * postion = new QStandardItem(weizhi);
//QStandardItem * date = new QStandardItem(riqi);
//QStandardItem * time = new QStandardItem(shijian);
//QStandardItem * error = new QStandardItem(guzhang);

//this->modelerror->setItem(num, 0, postion);
//this->modelerror->setItem(num, 1, new QStandardItem(riqi));
//this->modelerror->setItem(num, 2, time);
//this->modelerror->setItem(num, 3, error);

    //背景颜色，数据对齐
//    if(num % 2)
//    {
//        for (int var = 0; var < 4; var++)
//        {
//            this->modelerror->item(num,var)->setBackground(QBrush(Qt::lightGray));
//        }
//    }
//    else
//    {
//        for (int var = 0; var < 4; var++)
//        {
//            this->modelerror->item(num,var)->setBackground(QBrush(Qt::white));
//        }
//    }
//    for (int var = 0; var < 4; var++)
//    {
//        this->modelerror->item(num,var)->setTextAlignment(Qt::AlignCenter);
//    }

//}
