#include "loginwindow.h"
#include "ui_loginwindow.h"
#include <QStyleOption>
#include "monitorwindow.h"

LoginWindow * LoginWindow::loginWin = NULL;

 LoginWindow * LoginWindow::getInstance()
{
    if(loginWin  == NULL)
    {
       loginWin = new LoginWindow();
    }
    return loginWin;
}

LoginWindow::LoginWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWindow)
{
    this->setWindowFlags(Qt::FramelessWindowHint);
    ui->setupUi(this);
    ui->lineEdit_paaword->setEchoMode(QLineEdit::Password);

     //仅仅通过鼠标点击获得焦点
//    ui->lineEdit_paaword->clearFocus();
//    setFocusPolicy(Qt::ClickFocus);

}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget,&opt,&p,this);
}


void LoginWindow::on_btn_login_clicked()
{
    //主界面登陆
    if(!syssetclicked)
    {
        if(ui->lineEdit_user->text()==tr("13")&&ui->lineEdit_paaword->text()==tr("6"))
        {
            //主界面申请内存
            MainWindow * mainwin = MainWindow::getInstance();
            ui->lineEdit_paaword->clear();
            ui->lineEdit_user->clear();
            ui->label_4->clear();
            this->close();
            mainwin->show();
        }
        else
        {
             ui->label_4->setText(tr("用户名或密码错误!"));
        }
    }
    //系统设置界面登陆
    else
    {
        if(ui->lineEdit_user->text()==tr("13")&&ui->lineEdit_paaword->text()==tr("7"))
        {
            //调试界面申请内存
            SysSettingWindow * syswin = SysSettingWindow::getInstance();
            ui->lineEdit_paaword->clear();
            ui->lineEdit_user->clear();
            ui->label_4->clear();
            this->close();
            syswin->show();
        }
        else
        {
             ui->label_4->setText(tr("用户名或密码错误!"));
        }
    }


}

void LoginWindow::on_btn_exit_clicked()
{   MonitorWindow * monwin = MonitorWindow::getInstance();
    ui->lineEdit_paaword->clear();
    ui->lineEdit_user->clear();
    ui->label_4->clear();
    this->close();
    monwin->show();
}


