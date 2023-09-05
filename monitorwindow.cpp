#include "monitorwindow.h"
#include "ui_monitorwindow.h"
#include <QStyleOption>
#include "GlobalData.h"

MonitorWindow * MonitorWindow::monitorwin = NULL;

 MonitorWindow * MonitorWindow::getInstance()
{
    if(monitorwin == NULL)
    {
        monitorwin = new MonitorWindow();
    }
    return monitorwin;
}

MonitorWindow::MonitorWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MonitorWindow)
{
    //去掉标题栏
    this->setWindowFlags(Qt::FramelessWindowHint);
    ui->setupUi(this);
}

MonitorWindow::~MonitorWindow()
{
    delete ui;
}

//重写paint事件
void MonitorWindow::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget,&opt,&p,this);
}

void MonitorWindow::on_pushButton_clicked()
{
    LoginWindow * loginwin = LoginWindow::getInstance();
//    loginwin->syssetclicked = false;
    this->close();
    loginwin->show();
}

void MonitorWindow::UpdateWin()
{
    //DC1电压电流功率
    ui->label_229->setText(QString::number(OperMonModelDC1.BA_UBAT,'f',3));
    ui->label_239->setText(QString::number(OperMonModelDC1.BA_IBAT,'f',3));
    ui->label_243->setText(QString::number(OperMonModelDC1.BA_PIN,'f',3));
    //DC2电压电流功率
    ui->label_230->setText(QString::number(OperMonModelDC2.BA_UBAT,'f',3));
    ui->label_241->setText(QString::number(OperMonModelDC2.BA_IBAT,'f',3));
    ui->label_244->setText(QString::number(OperMonModelDC2.BA_PIN,'f',3));

}



