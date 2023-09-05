#include "mainwindow.h"
#include "keyboard.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //主窗口
//    MainWindow w;
//    w.show();
    MainWindow * w = MainWindow::getInstance();
    //软键盘
    keyBoard keyBoard;
    keyBoard.show();
    keyBoard.hide();

    return a.exec();
}
