#include "keyboard.h"
#include "qdesktopwidget.h"
#include <QApplication>
#include <QStackedWidget>
#include <QMouseEvent>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QDebug>

keyBoard::keyBoard(QWidget *parent) :
    QWidget(parent)
{
    this->InitWindow();
//    this->InitProperty();
    this->InitForm();

    //设置背景透明
//    setAttribute(Qt::WA_TranslucentBackground);
    //end

    QDesktopWidget* w = QApplication::desktop();
    deskWidth = w->screenGeometry().width();
    deskHeight = w->screenGeometry().height();
    frmWidth = this->width();
    frmHeight = this->height();

    // 自动填充在底部
    //this->setGeometry(0,deskHeight-frmWidth,deskWidth,frmWidth);
    // 居中显示
    //QPoint movePoint(deskWidth / 2 - frmWidth / 2, deskHeight / 2 - frmHeight / 2);
    //this->move(movePoint);
}

keyBoard::~keyBoard()
{
}

void keyBoard::mouseMoveEvent(QMouseEvent *e)
{
    if (mousePressed && (e->buttons() && Qt::LeftButton))
    {
        this->move(e->globalPos() - mousePoint);
        this->repaint();
        e->accept();
    }
}

void keyBoard::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton)
    {
        mousePressed = true;
        mousePoint = e->globalPos() - this->pos();
        e->accept();
    }

}

void keyBoard::mouseReleaseEvent(QMouseEvent *)
{
    mousePressed = false;
}

//============================================================
// 函数名称： focusChanged
// 功能描述： 槽:控件输入焦点处理
// 输入参数： 无
// 输出参数： 无
// 返 回 值： 无
// 修改日期        版本号     修改人	      修改内容
// -----------------------------------------------
// 2017/10/27	  V1.0	    	        创建
//============================================================
void keyBoard::focusChanged(QWidget *, QWidget *nowWidget)
{
#if 1
    if (nowWidget != 0 && !this->isAncestorOf(nowWidget))
    {
        if (nowWidget->inherits("QLineEdit"))
        {
            if(currentLineEdit == nowWidget){
                return;
            }
            currentLineEdit = (QLineEdit *)nowWidget;
            QPoint movePoint;

            // 鼠标点击位置坐标
            if (QCursor::pos().y() > deskHeight / 2)
            {
                // 靠上居中显示
                movePoint = QPoint(deskWidth/2 - frmWidth/2, 0);
            }
            else
            {
                // 靠下居中显示
                movePoint = QPoint(deskWidth/2 - frmWidth/2, deskHeight - frmHeight -5);
            }

            this->move(movePoint);
            this->repaint();
            this->hide();
            this->setVisible(true);
        }

    }

#endif
}

//============================================================
// 函数名称： slotBtnClicked
// 功能描述： 槽:所有按键的处理函数,根据objectName
// 输入参数： 无
// 输出参数： 无
// 返 回 值： 无
// 修改日期        版本号     修改人	      修改内容
// -----------------------------------------------
// 2017/10/27	  V1.0	    	        创建
//============================================================
void keyBoard::slotBtnClicked()
{
    QPushButton *btn = (QPushButton *)sender();
    QString objectName = btn->objectName();

    if (objectName == "delBtn")
    {
        if (currentLineEdit != 0)
        {
            //currentLineEdit->backspace();
            LineEdit->backspace();
        }
    }

    else if (objectName == "closeBtn")
    {
        LineEdit->setText("");

        //清除焦点
//        currentLineEdit->clearFocus();
//        LineEdit->clearFocus();
        //end

        #ifdef Q_OS_WIN     //如果是windows系统
                this->move(-500, -500);
        #else
                this->setVisible(false);
        #endif
    }
    //确认按钮
    else if (objectName == "confirmBtn")
    {
        QString textline = this->LineEdit->text();
        currentLineEdit->setText("");
        currentLineEdit->insert(textline);
        //标志位置位
        flag_confirm = 0xAA;
        //清显示区
        LineEdit->setText("");
        this->setVisible(false);

        //清除焦点
//        currentLineEdit->clearFocus();
        //end
    }
    else
    {
        QString value = btn->text();

        // 当前不是中文模式,则单击按钮对应text为传递参数
        if (currentType != "chinese")
        {
            if (currentLineEdit != 0)
            {
                //标志位没有置位，继续添加数据
                if(0xAA != flag_confirm)
                    LineEdit->insert(value);
                //置位清除数据，插入值
                else
                {
                    flag_confirm = 0;
                    LineEdit->setText("");
                    LineEdit->insert(value);
                }
            }
        }

    }
}

//============================================================
// 函数名称： InitWindow
// 功能描述： 初始化窗口布局
// 输入参数： 无
// 输出参数： 无
// 返 回 值： 无
// 修改日期        版本号     修改人	      修改内容
// -----------------------------------------------
// 2017/10/27	  V1.0	    	        创建
//============================================================
void keyBoard::InitWindow()
{
    this->setProperty("Form", true);
    this->setWindowFlags(Qt::Tool | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);

    //this->setFixedSize(6 * BTN_SIZE_WIDTH, 5 * BTN_SIZE_HEIGHT);
    this->setFixedSize(400, 6 * BTN_SIZE_HEIGHT);

    this->setFocusPolicy(Qt::NoFocus);


//    keyWindow = new QStackedWidget(this);
//    keyWindow->setFixedSize(5 * BTN_SIZE_WIDTH, 4 * BTN_SIZE_HEIGHT);

     changeStyle(2);
    // 填加功能按钮
    closeBtn = new QPushButton(this);
    closeBtn->setObjectName("closeBtn");
    closeBtn->setProperty("function", true);
    closeBtn->setText(tr("X"));
    closeBtn->setFixedSize(BTN_SIZE_WIDTH, BTN_SIZE_HEIGHT);
//    //背景透明
//    closeBtn->setFlat(true);

    // 删除一个字符
    delBtn = new QPushButton(this);
    delBtn->setObjectName("delBtn");
    delBtn->setProperty("function", true);
    delBtn->setText(tr("Del"));
    delBtn->setFixedSize(BTN_SIZE_WIDTH, BTN_SIZE_HEIGHT);


    // 填加数字键盘
    btn1 = new QPushButton(this);
    btn1->setText(tr("1"));
    btn1->setProperty("num", true);
    btn1->setFixedSize(BTN_SIZE_WIDTH, BTN_SIZE_HEIGHT);

    btn2 = new QPushButton(this);
    btn2->setText(tr("2"));
    btn2->setProperty("num", true);
    btn2->setFixedSize(BTN_SIZE_WIDTH, BTN_SIZE_HEIGHT);

    btn3 = new QPushButton(this);
    btn3->setText(tr("3"));
    btn3->setProperty("num", true);
    btn3->setFixedSize(BTN_SIZE_WIDTH, BTN_SIZE_HEIGHT);

    btn4 = new QPushButton(this);
    btn4->setFixedSize(BTN_SIZE_WIDTH, BTN_SIZE_HEIGHT);
    btn4->setProperty("num", true);
    btn4->setText(tr("4"));

    btn5 = new QPushButton(this);
    btn5->setFixedSize(BTN_SIZE_WIDTH, BTN_SIZE_HEIGHT);
    btn5->setProperty("num", true);
    btn5->setText(tr("5"));

    btn6 = new QPushButton(this);
    btn6->setFixedSize(BTN_SIZE_WIDTH, BTN_SIZE_HEIGHT);
    btn6->setProperty("num", true);
    btn6->setText(tr("6"));

    btn7 = new QPushButton(this);
    btn7->setFixedSize(BTN_SIZE_WIDTH, BTN_SIZE_HEIGHT);
    btn7->setProperty("num", true);
    btn7->setText(tr("7"));

    btn8 = new QPushButton(this);
    btn8->setFixedSize(BTN_SIZE_WIDTH, BTN_SIZE_HEIGHT);
    btn8->setProperty("num", true);
    btn8->setText(tr("8"));

    btn9 = new QPushButton(this);
    btn9->setFixedSize(BTN_SIZE_WIDTH, BTN_SIZE_HEIGHT);
    btn9->setProperty("num", true);
    btn9->setText(tr("9"));

    btn0 = new QPushButton(this);
    btn0->setFixedSize(BTN_SIZE_WIDTH, BTN_SIZE_HEIGHT);
    btn0->setProperty("num", true);
    btn0->setText(tr("0"));




    // 填加符号键盘
    btnSign0 = new QPushButton(this);
    btnSign0->setFixedSize(BTN_SIZE_WIDTH, BTN_SIZE_HEIGHT);//============================================================
    btnSign0->setProperty("sign", true);
    btnSign0->setText(tr("."));

//    btnSign1 = new QPushButton(this);
//    btnSign1->setFixedSize(BTN_SIZE_WIDTH, BTN_SIZE_HEIGHT);
//    btnSign1->setProperty("sign", true);
//    btnSign1->setText(tr("/"));


    btnSign2 = new QPushButton(this);
    btnSign2->setFixedSize(BTN_SIZE_WIDTH, BTN_SIZE_HEIGHT);
    btnSign2->setProperty("num", true);
    btnSign2->setText(tr("-"));

    //test
     LineEdit = new QLineEdit(this);
    // LineEdit->setFixedSize(BTN_SIZE_WIDTH,BTN_SIZE_HEIGHT);

     LineEdit->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
     LineEdit->setMinimumSize(BTN_SIZE_WIDTH,BTN_SIZE_HEIGHT);

    LineEdit->setFont(QFont("黑体",25));
    QPalette palette;
    palette.setColor(QPalette::Text,Qt::white);
    LineEdit->setPalette(palette);
    LineEdit->setStyleSheet("background:transparent;border:2px solid white;");

     btnconfirm = new QPushButton(this);
     btnconfirm->setFixedSize(BTN_SIZE_WIDTH, BTN_SIZE_HEIGHT*2);
     btnconfirm->setObjectName("confirmBtn");
     btnconfirm->setProperty("function", true);
     btnconfirm->setText(tr("OK"));

    // 全局步局
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(btn7, 2,1,1,1);
    layout->addWidget(btn8, 2,2,1,1);
    layout->addWidget(btn9, 2,3,1,1);
    layout->addWidget(btn4, 3,1,1,1);
    layout->addWidget(btn5, 3,2,1,1);
    layout->addWidget(btn6, 3,3,1,1);
    layout->addWidget(btn1, 4,1,1,1);
    layout->addWidget(btn2, 4,2,1,1);
    layout->addWidget(btn3, 4,3,1,1);
    layout->addWidget(btn0, 5,1,1,1);
    layout->addWidget(btnSign0,  5,2,1,1);


    layout->addWidget(closeBtn, 2,4,1,1);
    layout->addWidget(btnSign2,  5,3,1,1);
    layout->addWidget(delBtn,   3,4,1,1);
    //占4列
    layout->addWidget(LineEdit,  1,1,1,4);
    //占2行
    layout->addWidget(btnconfirm,  4,4,2,1);

    layout->setHorizontalSpacing(0);

//    layout->addWidget(btnSign3,  3,4,1,1);
//    layout->setSpacing(0);
//    layout->setMargin(0);
//    layout->setVerticalSpacing(0);
//    layout->setContentsMargins(0, 0, 0, 0);
    this->setLayout(layout);
}

//============================================================
// 函数名称： InitForm
// 功能描述： 初始化窗口数据
// 输入参数： 无
// 输出参数： 无
// 返 回 值： 无
// 修改日期        版本号     修改人	      修改内容
// -----------------------------------------------
// 2017/10/27	  V1.0	    	        创建
//============================================================
void keyBoard::InitForm()
{

    currentLineEdit = 0;
    mousePressed = false;


    QList<QPushButton *> btn = this->findChildren<QPushButton *>();
    foreach (QPushButton * b, btn) {
        connect(b, SIGNAL(clicked()), this, SLOT(slotBtnClicked()));
    }

    // 绑定全局改变焦点信号槽
    connect(qApp, SIGNAL(focusChanged(QWidget *, QWidget *)),
            this, SLOT(focusChanged(QWidget *, QWidget *)));
    // 绑定按键事件过滤器
//    qApp->installEventFilter(this);
}



//============================================================
// 函数名称： changeStyle
// 功能描述： 改变键盘风格
// 输入参数： 无
// 输出参数： 无
// 返 回 值： 无
// 修改日期        版本号     修改人	      修改内容
// -----------------------------------------------
// 2017/10/29	  V1.0	    	        创建
//============================================================
void keyBoard::changeStyle(int style)
{
    switch (style)
    {
        case 0:
        {
            // 灰色
            setStyle("#E4E4E4", "#A2A2A2", "#DCDCDC", "#000000");

            break;
        }
        case 1:
        {
            // 蓝色
            setStyle("#DEF0FE", "#C0DEF6", "#C0DCF2", "#386487");

            break;
        }
        case 2:
        {
            // 黑色
            setStyle("#4D4D4D", "#292929", "#C2CCD8", "#F0F0F0");

            break;
        }
    }
}

//============================================================
// 函数名称： setStyle
// 功能描述： 设置键盘风格
// 输入参数：
// 输出参数： 无
// 返 回 值： 无
// 修改日期        版本号     修改人	      修改内容
// -----------------------------------------------
// 2017/10/29	  V1.0	    	        创建
//============================================================
void keyBoard::setStyle(QString topColor, QString bottomColor, QString borderColor, QString textColor)
{
    QStringList qss;

    // 设置键盘背景色,从上到下渐变效果
    qss.append(QString("QWidget{background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 %1,stop:1 %2);}")
               .arg(topColor).arg(bottomColor));

    // 设置字按钮字体
    qss.append(QString("QLabel,QPushButton{font:%1px;color:%2;}").arg(BTN_SIZE_HEIGHT/2).arg(textColor));

    // 按钮边框
    qss.append(QString("QPushButton{border:1px solid %1;}").arg(borderColor));

    // 去掉按钮焦点虚线框和圆角
    qss.append("QPushButton{outline:0px;border-radius:5px;}");

    // 按钮有按下的效果
    qss.append(QString("QPushButton:pressed{padding-left:5px;padding-top:5px;}"));

    // 删除按钮设为蓝色背景,白色字体
   // qss.append("QPushButton#delBtn{font:bold;background:blue;color:white;}");

    // 关闭按钮设为红色背景,白色字体
    qss.append("QPushButton#closeBtn{font:bold;background:gray;color:white;}");

    this->setStyleSheet(qss.join(""));
}


