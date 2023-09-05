#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPainter>
#include "qpushbutton.h"
#include "mainwindow.h"
#include "syssettingwindow.h"

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    static LoginWindow *getInstance();
    ~LoginWindow();
    bool syssetclicked = false;

protected:
    void paintEvent(QPaintEvent *event);

private slots:
    void on_btn_login_clicked();

    void on_btn_exit_clicked();


private:
    Ui::LoginWindow *ui;
   static LoginWindow * loginWin;

};

#endif // LOGINWINDOW_H
