#include "syssettingwindow.h"
#include "ui_syssettingwindow.h"
#include "mainwindow.h"
#include <QStyleOption>
#include "GlobalData.h"
#include "errorwindow.h"
#include "monitorwindow.h"

SysSettingWindow * SysSettingWindow::setWin = NULL;

 SysSettingWindow * SysSettingWindow::getInstance()
{
    if(setWin == NULL)
    {
        setWin = new SysSettingWindow();
    }
    return setWin;
}

SysSettingWindow::SysSettingWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SysSettingWindow)
{
    //去掉标题栏
    this->setWindowFlags(Qt::FramelessWindowHint);
    ui->setupUi(this);

    //定时器更新窗口事件
    timer1= new QTimer(this);
    connect(timer1,&QTimer::timeout,this,&SysSettingWindow::timer_update_window);
}

SysSettingWindow::~SysSettingWindow()
{
    delete ui;
}



/**********************************************************/
//函数：监控按钮点击事件
//功能：跳转到监控界面
//date：2023/4/21
/**********************************************************/
void SysSettingWindow::on_pushButton_3_clicked()
{
    timer1->stop();

    MonitorWindow * monitorwin = MonitorWindow::getInstance();
    this->close();
    monitorwin->show();
}

void SysSettingWindow::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget,&opt,&p,this);
}


//参数更新界面
void SysSettingWindow::timer_update_window()
{
    //控制参数
    //DC1
    ui->lineEdit->setText(QString::number(ControlParalDC1.POUTLIMIT*1.0/10,'f',1));
    ui->lineEdit_2->setText(QString::number(ControlParalDC1.HMIIBATL));
    ui->lineEdit_3->setText(QString::number(ControlParalDC1.DEADTIME));
    ui->lineEdit_7->setText(QString::number(ControlParalDC1.MINONTIME));
    ui->lineEdit_4->setText(QString::number(ControlParalDC1.DCDC_SWFR*1.0/100,'f',2));
    ui->lineEdit_5->setText(QString::number(ControlParalDC1.RU_UDCT));
    ui->lineEdit_6->setText(QString::number(ControlParalDC1.RU_IDT));

    //DC2
    ui->lineEdit_8->setText( QString::number(ControlParalDC2.POUTLIMIT*1.0/10,'f',1));
    ui->lineEdit_9->setText(QString::number(ControlParalDC2.HMIIBATL));
    ui->lineEdit_10->setText(QString::number(ControlParalDC2.DEADTIME));
    ui->lineEdit_11->setText(QString::number(ControlParalDC2.MINONTIME));
    ui->lineEdit_12->setText(QString::number(ControlParalDC2.DCDC_SWFR*1.0/100,'f',2));
    ui->lineEdit_13->setText(QString::number(ControlParalDC2.RU_UDCT));
    ui->lineEdit_14->setText(QString::number(ControlParalDC2.RU_IDT));

    //AC
    ui->lineEdit_15->setText( QString::number(ControlParaModelAC.IACLIMIT));
    ui->lineEdit_16->setText( QString::number(ControlParaModelAC.RU_UDCT));
    ui->lineEdit_25->setText( QString::number(ControlParaModelAC.SW_FR*1.0/100,'f',2 ));
    ui->lineEdit_17->setText( QString::number( ControlParaModelAC.MINONTIME ));
    ui->lineEdit_24->setText( QString::number(ControlParaModelAC.DEADTIME));
    ui->lineEdit_18->setText( QString::number( ControlParaModelAC.COMPTIME1));
    ui->lineEdit_19->setText( QString::number(ControlParaModelAC.COMPANGLE));
    ui->lineEdit_20->setText( QString::number(ControlParaModelAC.SC_USTEP1));
    ui->lineEdit_21->setText( QString::number(ControlParaModelAC.SC_ISTEP1));
    ui->lineEdit_23->setText( QString::number(ControlParaModelAC.UDCH));
    ui->lineEdit_22->setText( QString::number(ControlParaModelAC.RU_IDT));

    //保护参数
    //DC1
    ui->lineEdit_26->setText( QString::number(ProtectParaDC1.SC_UDCOV));
    ui->lineEdit_27->setText( QString::number(ProtectParaDC1.SC_EEREPT));
    ui->lineEdit_28->setText( QString::number(ProtectParaDC1.SC_RCOVT));
    ui->lineEdit_29->setText( QString::number(ProtectParaDC1.SC_UBATDV*1.0/10,'f',1));
    //DC2
    ui->lineEdit_43->setText( QString::number(ProtectParaDC2.SC_UDCOV));
    ui->lineEdit_41->setText( QString::number(ProtectParaDC2.SC_EEREPT));
    ui->lineEdit_44->setText( QString::number(ProtectParaDC2.SC_RCOVT));
    ui->lineEdit_42->setText( QString::number(ProtectParaDC2.SC_UBATDV*1.0/10,'f',1));
    //AC
    ui->lineEdit_30->setText( QString::number(ProtectParaAC.SC_UDCOV));
    ui->lineEdit_31->setText( QString::number(ProtectParaAC.SC_UACOV));
    ui->lineEdit_32->setText( QString::number(ProtectParaAC.SC_UACLV));
    ui->lineEdit_33->setText( QString::number(ProtectParaAC.SC_IACOV));
    ui->lineEdit_34->setText( QString::number(ProtectParaAC.SC_EFFHIG*1.0/100,'f',2));
    ui->lineEdit_35->setText( QString::number(ProtectParaAC.SC_EFFLOW*1.0/100,'f',2));
    ui->lineEdit_36->setText( QString::number(ProtectParaAC.SC_DETAOMIGA));
    ui->lineEdit_37->setText( QString::number(ProtectParaAC.SC_IACEQUAL));
    ui->lineEdit_38->setText( QString::number(ProtectParaAC.SC_FINTRT*1.0/100,'f',2));
    ui->lineEdit_39->setText( QString::number(ProtectParaAC.SC_RCOVT));
    ui->lineEdit_40->setText( QString::number(ProtectParaAC.SC_EEREPT));
    ui->lineEdit_45->setText( QString::number(ProtectParaAC.SC_IGBTDOWN));

    //PI参数
    //DC1
    ui->lineEdit_48->setText( QString::number(pIModelDC1.UbatKP));
    ui->lineEdit_46->setText( QString::number(pIModelDC1.UbatTI));
    ui->lineEdit_49->setText( QString::number(pIModelDC1.IbatKP));
    ui->lineEdit_47->setText( QString::number(pIModelDC1.IbatTI));
    //DC2
    ui->lineEdit_52->setText( QString::number(pIModelDC2.UbatKP));
    ui->lineEdit_50->setText( QString::number(pIModelDC2.UbatTI));
    ui->lineEdit_53->setText( QString::number(pIModelDC2.IbatKP));
    ui->lineEdit_51->setText( QString::number(pIModelDC2.IbatTI));
    //AC
    ui->lineEdit_54->setText( QString::number(pIModelAC.UdcKP));
    ui->lineEdit_62->setText( QString::number(pIModelAC.UdcTI));
    ui->lineEdit_61->setText( QString::number(pIModelAC.PLLKP));
    ui->lineEdit_56->setText( QString::number(pIModelAC.PLLTI));
    ui->lineEdit_55->setText( QString::number(pIModelAC.IdKP));
    ui->lineEdit_57->setText( QString::number(pIModelAC.IdTI));
    ui->lineEdit_59->setText( QString::number(pIModelAC.IqKP));
    ui->lineEdit_60->setText( QString::number(pIModelAC.IqTI));

    //校准参数
    //DC1
    ui->lineEdit_58->setText( QString::number(cALModelDC1.A_UBAT));
    ui->lineEdit_63->setText( QString::number(cALModelDC1.B_UBAT));
    ui->lineEdit_64->setText( QString::number(cALModelDC1.A_I1BAT));
    ui->lineEdit_65->setText( QString::number(cALModelDC1.B_I1BAT));
    ui->lineEdit_66->setText( QString::number(cALModelDC1.A_I2BAT));
    ui->lineEdit_67->setText( QString::number(cALModelDC1.B_I2BAT));
    ui->lineEdit_68->setText( QString::number(cALModelDC1.A_IBAT1));
    ui->lineEdit_69->setText( QString::number(cALModelDC1.B_IBAT1));
    ui->lineEdit_70->setText( QString::number(cALModelDC1.A_IBAT2));
    ui->lineEdit_71->setText( QString::number(cALModelDC1.B_IBAT2));
    //DC2
    ui->lineEdit_82->setText( QString::number(cALModelDC2.A_UBAT));
    ui->lineEdit_83->setText( QString::number(cALModelDC2.B_UBAT));
    ui->lineEdit_84->setText( QString::number(cALModelDC2.A_I1BAT));
    ui->lineEdit_85->setText( QString::number(cALModelDC2.B_I1BAT));
    ui->lineEdit_86->setText( QString::number(cALModelDC2.A_I2BAT));
    ui->lineEdit_87->setText( QString::number(cALModelDC2.B_I2BAT));
    ui->lineEdit_88->setText( QString::number(cALModelDC2.A_IBAT1));
    ui->lineEdit_89->setText( QString::number(cALModelDC2.B_IBAT1));
    ui->lineEdit_90->setText( QString::number(cALModelDC2.A_IBAT2));
    ui->lineEdit_91->setText( QString::number(cALModelDC2.B_IBAT2));
    //AC
    ui->lineEdit_102->setText( QString::number(cALModelAC.A_BUSUDC));
    ui->lineEdit_103->setText( QString::number(cALModelAC.B_BUSUDC));
    ui->lineEdit_104->setText( QString::number(cALModelAC.A_UAB));
    ui->lineEdit_105->setText( QString::number(cALModelAC.B_UAB));
    ui->lineEdit_106->setText( QString::number(cALModelAC.A_UAC));
    ui->lineEdit_107->setText( QString::number(cALModelAC.B_UAC));
    ui->lineEdit_108->setText( QString::number(cALModelAC.A_IA));
    ui->lineEdit_109->setText( QString::number(cALModelAC.B_IA));
    ui->lineEdit_110->setText( QString::number(cALModelAC.A_IC));
    ui->lineEdit_111->setText( QString::number(cALModelAC.B_IC));

    //系统参数
    //DC1
    ui->lineEdit_132->setText(QString("%1-%2-%3").arg(S_SystemSetDC1.dataproduct.year).arg(S_SystemSetDC1.dataproduct.month).arg(S_SystemSetDC1.dataproduct.day));
    ui->lineEdit_123->setText(QString("%1%2").arg('V').arg(QString::number(S_SystemSetDC1.softversion*1.0/10,'f',1)));
    ui->lineEdit_124->setText(QString::number(S_SystemSetDC1.projectnum));
    ui->lineEdit_125->setText(QString::number(S_SystemSetDC1.serialnum));
    ui->lineEdit_127->setText(QString::number(S_SystemSetDC1.manufactid));
    //DC2
    ui->lineEdit_128->setText(QString("%1-%2-%3").arg(S_SystemSetDC2.dataproduct.year).arg(S_SystemSetDC2.dataproduct.month).arg(S_SystemSetDC2.dataproduct.day));
    ui->lineEdit_129->setText(QString("%1%2").arg('V').arg(QString::number((float)S_SystemSetDC2.softversion/10,'f',1)));
    ui->lineEdit_130->setText(QString::number(S_SystemSetDC2.projectnum));
    ui->lineEdit_131->setText(QString::number(S_SystemSetDC2.serialnum));
    ui->lineEdit_133->setText(QString::number(S_SystemSetDC2.manufactid));
    //AC
    ui->lineEdit_134->setText(QString("%1-%2-%3").arg(S_SysSetAC.dataproduct.year).arg(S_SysSetAC.dataproduct.month).arg(S_SysSetAC.dataproduct.day));
    ui->lineEdit_135->setText(QString("%1%2").arg('V').arg(QString::number(S_SysSetAC.softversion*1.0/10,'f',1)));
    ui->lineEdit_139->setText(QString::number(S_SysSetAC.modelpara));

    //运动控制参数
    //DC1
    ui->lineEdit_136->setText(QString::number(S_MotionConDC1.resume));
    ui->lineEdit_122->setText(QString::number(S_MotionConDC1.mastandby));
    //DC2
    ui->lineEdit_141->setText(QString::number(S_MotionConDC2.resume));
    ui->lineEdit_138->setText(QString::number(S_MotionConDC2.mastandby));
    //AC
    ui->lineEdit_143->setText(QString::number(S_MotionConAc.resume));
    ui->lineEdit_144->setText(QString::number(S_MotionConAc.dcmodesel));
    ui->lineEdit_145->setText(QString::number(S_MotionConAc.mastandby));
    ui->lineEdit_146->setText(QString::number((S_MotionConAc.modulation >> 0) & 0x01));
    ui->lineEdit_147->setText(QString::number((S_MotionConAc.modulation >> 1) & 0x01));
    ui->lineEdit_148->setText(QString::number((S_MotionConAc.modulation >> 2) & 0x01));
    ui->lineEdit_149->setText(QString::number((S_MotionConAc.modulation >> 3) & 0x01));
    ui->lineEdit_150->setText(QString::number((S_MotionConAc.modulation >> 4) & 0x01));
    ui->lineEdit_151->setText(QString::number((S_MotionConAc.modulation >> 5) & 0x01));
}


//CAN数据组帧
void SysSettingWindow::sendcmd(long canid, uint8_t commmand,uint8_t mode,uint8_t ch)
{
    canFrame sendFrame;
    //判断何种参数
    //控制参数
    if(CONPARA == mode)
    {
        //判断通道
        //DC1
        if(0 == ch)
        {
            if(0x03 == commmand)
            {
                sendFrame.data[0] = commmand;
                sendFrame.data[1] = 0;
                sendFrame.data[2] = 0;
                sendFrame.data[3] = ControlParalDC1.POUTLIMIT & 0x00FF;
                sendFrame.data[4] = (ControlParalDC1.POUTLIMIT >> 8) & 0x00FF;
                sendFrame.data[5] = ControlParalDC1.HMIIBATL;
                sendFrame.data[6] = ControlParalDC1.DEADTIME;
                sendFrame.data[7] = ControlParalDC1.MINONTIME;
            }
            //0x04
            else
            {
                sendFrame.data[0] = commmand;
                sendFrame.data[1] = ControlParalDC1.DCDC_SWFR & 0x00FF;;
                sendFrame.data[2] = (ControlParalDC1.DCDC_SWFR >> 8) & 0x00FF;
                sendFrame.data[3] = ControlParalDC1.RU_UDCT & 0x00FF;
                sendFrame.data[4] = (ControlParalDC1.RU_UDCT >> 8) & 0x00FF;
                sendFrame.data[5] = ControlParalDC1.RU_IDT & 0x00FF;
                sendFrame.data[6] = (ControlParalDC1.RU_IDT >> 8) & 0x00FF;
                sendFrame.data[7] = 0;
            }
        }
        //DC2
        else if(1 == ch)
        {
            if(0x03 == commmand)
            {
                sendFrame.data[0] = commmand;
                sendFrame.data[1] = 0;
                sendFrame.data[2] = 0;
                sendFrame.data[3] = ControlParalDC2.POUTLIMIT & 0x00FF;
                sendFrame.data[4] = (ControlParalDC2.POUTLIMIT >> 8) & 0x00FF;
                sendFrame.data[5] = ControlParalDC2.HMIIBATL;
                sendFrame.data[6] = ControlParalDC2.DEADTIME;
                sendFrame.data[7] = ControlParalDC2.MINONTIME;
            }
            //0x04
            else
            {
                sendFrame.data[0] = commmand;
                sendFrame.data[1] = ControlParalDC2.DCDC_SWFR & 0x00FF;;
                sendFrame.data[2] = (ControlParalDC2.DCDC_SWFR >> 8) & 0x00FF;
                sendFrame.data[3] = ControlParalDC2.RU_UDCT & 0x00FF;
                sendFrame.data[4] = (ControlParalDC2.RU_UDCT >> 8) & 0x00FF;
                sendFrame.data[5] = ControlParalDC2.RU_IDT & 0x00FF;
                sendFrame.data[6] = (ControlParalDC2.RU_IDT >> 8) & 0x00FF;
                sendFrame.data[7] = 0;
            }
        }
        //AC
        else
        {
            if(0x02 == commmand)
            {
                sendFrame.data[0] = commmand;
                sendFrame.data[1] = ControlParaModelAC.IACLIMIT;
                sendFrame.data[2] = ControlParaModelAC.RU_UDCT & 0x00FF;
                sendFrame.data[3] = (ControlParaModelAC.RU_UDCT >> 8) & 0x00FF;
                sendFrame.data[4] = ControlParaModelAC.SW_FR & 0x00FF;
                sendFrame.data[5] = (ControlParaModelAC.SW_FR >> 8) & 0x00FF;
                sendFrame.data[6] = ControlParaModelAC.MINONTIME;
                sendFrame.data[7] = ControlParaModelAC.DEADTIME;
            }
            //0x03
            else
            {
                sendFrame.data[0] = commmand;
                sendFrame.data[1] = ControlParaModelAC.COMPTIME1;
                sendFrame.data[2] = ControlParaModelAC.COMPANGLE;
                sendFrame.data[3] = ControlParaModelAC.SC_USTEP1;
                sendFrame.data[4] = ControlParaModelAC.SC_ISTEP1;
                sendFrame.data[5] = ControlParaModelAC.UDCH;
                sendFrame.data[6] = ControlParaModelAC.RU_IDT;
                sendFrame.data[7] = 0;
            }
        }

    }
    //保护参数
    else if(PROTPARA == mode)
    {
        //DC1
        if(0 == ch)
        {
            sendFrame.data[0] = commmand;
            sendFrame.data[1] = ProtectParaDC1.SC_UDCOV & 0x00FF;
            sendFrame.data[2] = (ProtectParaDC1.SC_UDCOV >> 8) & 0x00FF;
            sendFrame.data[3] = ProtectParaDC1.SC_EEREPT & 0x00FF;
            sendFrame.data[4] = (ProtectParaDC1.SC_EEREPT >> 8) & 0x00FF;
            sendFrame.data[5] = ProtectParaDC1.SC_RCOVT & 0x00FF;
            sendFrame.data[6] = (ProtectParaDC1.SC_RCOVT >> 8) & 0x00FF;
            sendFrame.data[7] = ProtectParaDC1.SC_UBATDV;
        }
         //DC2
        else if(1 == ch)
        {
            sendFrame.data[0] = commmand;
            sendFrame.data[1] = ProtectParaDC2.SC_UDCOV & 0x00FF;
            sendFrame.data[2] = (ProtectParaDC2.SC_UDCOV >> 8) & 0x00FF;
            sendFrame.data[3] = ProtectParaDC2.SC_EEREPT & 0x00FF;
            sendFrame.data[4] = (ProtectParaDC2.SC_EEREPT >> 8) & 0x00FF;
            sendFrame.data[5] = ProtectParaDC2.SC_RCOVT & 0x00FF;
            sendFrame.data[6] = (ProtectParaDC2.SC_RCOVT >> 8) & 0x00FF;
            sendFrame.data[7] = ProtectParaDC2.SC_UBATDV;
        }
         //AC
        else
        {
           if(0x04 == commmand)
           {
               sendFrame.data[0] = commmand;
               sendFrame.data[1] = ProtectParaAC.SC_UDCOV & 0x00FF;
               sendFrame.data[2] = (ProtectParaAC.SC_UDCOV >> 8) & 0x00FF;
               sendFrame.data[3] = ProtectParaAC.SC_UACOV & 0x00FF;
               sendFrame.data[4] = (ProtectParaAC.SC_UACOV >> 8) & 0x00FF;
               sendFrame.data[5] = ProtectParaAC.SC_UACLV & 0x00FF;
               sendFrame.data[6] = (ProtectParaAC.SC_UACLV >> 8) & 0x00FF;
               sendFrame.data[7] = ProtectParaAC.SC_IACOV;
           }
           else if(0x05 == commmand)
           {
               sendFrame.data[0] = commmand;
               sendFrame.data[1] = ProtectParaAC.SC_EFFHIG & 0x00FF;
               sendFrame.data[2] = (ProtectParaAC.SC_EFFHIG >> 8) & 0x00FF;
               sendFrame.data[3] = ProtectParaAC.SC_EFFLOW & 0x00FF;
               sendFrame.data[4] = (ProtectParaAC.SC_EFFLOW >> 8) & 0x00FF;
               sendFrame.data[5] = ProtectParaAC.SC_DETAOMIGA & 0x00FF;
               sendFrame.data[6] = (ProtectParaAC.SC_DETAOMIGA >> 8) & 0x00FF;
               sendFrame.data[7] = ProtectParaAC.SC_IACEQUAL;
           }
           else
           {
               sendFrame.data[0] = commmand;
               sendFrame.data[1] = ProtectParaAC.SC_FINTRT & 0x00FF;
               sendFrame.data[2] = (ProtectParaAC.SC_FINTRT >> 8) & 0x00FF;
               sendFrame.data[3] = ProtectParaAC.SC_RCOVT & 0x00FF;
               sendFrame.data[4] = (ProtectParaAC.SC_RCOVT >> 8) & 0x00FF;
               sendFrame.data[5] = ProtectParaAC.SC_EEREPT & 0x00FF;
               sendFrame.data[6] = (ProtectParaAC.SC_EEREPT >> 8) & 0x00FF;
               sendFrame.data[7] = ProtectParaAC.SC_IGBTDOWN;
           }
        }
    }
    //PI参数
    else if(PIPARA == mode)
    {
        //DC1
        if(0 == ch)
        {
            if(0x06 == commmand)
            {
                sendFrame.data[0] = commmand;
                sendFrame.data[1] = pIModelDC1.UbatKP & 0x00FF;
                sendFrame.data[2] = (pIModelDC1.UbatKP  >> 8) & 0x00FF;
                sendFrame.data[3] = pIModelDC1.UbatTI  & 0x00FF;
                sendFrame.data[4] = (pIModelDC1.UbatTI  >> 8) & 0x00FF;
                sendFrame.data[5] = 0;
                sendFrame.data[6] = 0;
                sendFrame.data[7] = 0;
            }
            else
            {
                sendFrame.data[0] = commmand;
                sendFrame.data[1] = pIModelDC1.IbatKP & 0x00FF;
                sendFrame.data[2] = (pIModelDC1.IbatKP  >> 8) & 0x00FF;
                sendFrame.data[3] = pIModelDC1.IbatTI  & 0x00FF;
                sendFrame.data[4] = (pIModelDC1.IbatTI  >> 8) & 0x00FF;
                sendFrame.data[5] = 0;
                sendFrame.data[6] = 0;
                sendFrame.data[7] = 0;
            }
        }
        //DC2
        else if(1 == ch)
        {
            if(0x06 == commmand)
            {
                sendFrame.data[0] = commmand;
                sendFrame.data[1] = pIModelDC2.UbatKP & 0x00FF;
                sendFrame.data[2] = (pIModelDC2.UbatKP  >> 8) & 0x00FF;
                sendFrame.data[3] = pIModelDC2.UbatTI  & 0x00FF;
                sendFrame.data[4] = (pIModelDC2.UbatTI  >> 8) & 0x00FF;
                sendFrame.data[5] = 0;
                sendFrame.data[6] = 0;
                sendFrame.data[7] = 0;
            }
            else
            {
                sendFrame.data[0] = commmand;
                sendFrame.data[1] = pIModelDC2.IbatKP & 0x00FF;
                sendFrame.data[2] = (pIModelDC2.IbatKP  >> 8) & 0x00FF;
                sendFrame.data[3] = pIModelDC2.IbatTI  & 0x00FF;
                sendFrame.data[4] = (pIModelDC2.IbatTI  >> 8) & 0x00FF;
                sendFrame.data[5] = 0;
                sendFrame.data[6] = 0;
                sendFrame.data[7] = 0;
            }
        }
        //AC
        else
        {
            if(0x07 == commmand)
            {
                sendFrame.data[0] = commmand;
                sendFrame.data[1] = pIModelAC.UdcKP & 0x00FF;
                sendFrame.data[2] = (pIModelAC.UdcKP  >> 8) & 0x00FF;
                sendFrame.data[3] = pIModelAC.UdcTI  & 0x00FF;
                sendFrame.data[4] = (pIModelAC.UdcTI  >> 8) & 0x00FF;
                sendFrame.data[5] = 0;
                sendFrame.data[6] = 0;
                sendFrame.data[7] = 0;
            }
            else if(0x08 == commmand)
            {
                sendFrame.data[0] = commmand;
                sendFrame.data[1] = pIModelAC.PLLKP & 0x00FF;
                sendFrame.data[2] = (pIModelAC.PLLKP  >> 8) & 0x00FF;
                sendFrame.data[3] = pIModelAC.PLLTI  & 0x00FF;
                sendFrame.data[4] = (pIModelAC.PLLTI  >> 8) & 0x00FF;
                sendFrame.data[5] = 0;
                sendFrame.data[6] = 0;
                sendFrame.data[7] = 0;
            }
            else if(0x09 == commmand)
            {
                sendFrame.data[0] = commmand;
                sendFrame.data[1] = pIModelAC.IdKP & 0x00FF;
                sendFrame.data[2] = (pIModelAC.IdKP  >> 8) & 0x00FF;
                sendFrame.data[3] = pIModelAC.IdTI  & 0x00FF;
                sendFrame.data[4] = (pIModelAC.IdTI  >> 8) & 0x00FF;
                sendFrame.data[5] = 0;
                sendFrame.data[6] = 0;
                sendFrame.data[7] = 0;
            }
            else
            {
                sendFrame.data[0] = commmand;
                sendFrame.data[1] = pIModelAC.IqKP & 0x00FF;
                sendFrame.data[2] = (pIModelAC.IqKP  >> 8) & 0x00FF;
                sendFrame.data[3] = pIModelAC.IqTI  & 0x00FF;
                sendFrame.data[4] = (pIModelAC.IqTI  >> 8) & 0x00FF;
                sendFrame.data[5] = 0;
                sendFrame.data[6] = 0;
                sendFrame.data[7] = 0;
            }
        }
    }
    //校准参数
    else if(CALPARA == mode)
    {
        if(0 == ch)
        {
            //DC1
            if(0x08 == commmand)
            {
                sendFrame.data[0] = commmand;
                sendFrame.data[1] = cALModelDC1.A_UBAT & 0x00FF;
                sendFrame.data[2] = (cALModelDC1.A_UBAT  >> 8) & 0x00FF;
                sendFrame.data[3] = cALModelDC1.B_UBAT  & 0x00FF;
                sendFrame.data[4] = (cALModelDC1.B_UBAT  >> 8) & 0x00FF;
                sendFrame.data[5] = 0;
                sendFrame.data[6] = 0;
                sendFrame.data[7] = 0;
            }
            else if(0x09 == commmand)
            {
                sendFrame.data[0] = commmand;
                sendFrame.data[1] = cALModelDC1.A_I1BAT & 0x00FF;
                sendFrame.data[2] = (cALModelDC1.A_I1BAT  >> 8) & 0x00FF;
                sendFrame.data[3] = cALModelDC1.B_I1BAT  & 0x00FF;
                sendFrame.data[4] = (cALModelDC1.B_I1BAT  >> 8) & 0x00FF;
                sendFrame.data[5] = 0;
                sendFrame.data[6] = 0;
                sendFrame.data[7] = 0;
            }
            else if(0x0A == commmand)
            {
                sendFrame.data[0] = commmand;
                sendFrame.data[1] = cALModelDC1.A_I2BAT & 0x00FF;
                sendFrame.data[2] = (cALModelDC1.A_I2BAT  >> 8) & 0x00FF;
                sendFrame.data[3] = cALModelDC1.B_I2BAT  & 0x00FF;
                sendFrame.data[4] = (cALModelDC1.B_I2BAT  >> 8) & 0x00FF;
                sendFrame.data[5] = 0;
                sendFrame.data[6] = 0;
                sendFrame.data[7] = 0;
            }
            else if(0x0B == commmand)
            {
                sendFrame.data[0] = commmand;
                sendFrame.data[1] = cALModelDC1.A_IBAT1 & 0x00FF;
                sendFrame.data[2] = (cALModelDC1.A_IBAT1  >> 8) & 0x00FF;
                sendFrame.data[3] = cALModelDC1.B_IBAT1  & 0x00FF;
                sendFrame.data[4] = (cALModelDC1.B_IBAT1  >> 8) & 0x00FF;
                sendFrame.data[5] = 0;
                sendFrame.data[6] = 0;
                sendFrame.data[7] = 0;
            }
            else
            {
                sendFrame.data[0] = commmand;
                sendFrame.data[1] = cALModelDC1.A_IBAT2 & 0x00FF;
                sendFrame.data[2] = (cALModelDC1.A_IBAT2  >> 8) & 0x00FF;
                sendFrame.data[3] = cALModelDC1.B_IBAT2  & 0x00FF;
                sendFrame.data[4] = (cALModelDC1.B_IBAT2  >> 8) & 0x00FF;
                sendFrame.data[5] = 0;
                sendFrame.data[6] = 0;
                sendFrame.data[7] = 0;
            }
        }
        //DC1
        else if(1 == ch)
        {
            if(0x08 == commmand)
            {
                sendFrame.data[0] = commmand;
                sendFrame.data[1] = cALModelDC2.A_UBAT & 0x00FF;
                sendFrame.data[2] = (cALModelDC2.A_UBAT  >> 8) & 0x00FF;
                sendFrame.data[3] = cALModelDC2.B_UBAT  & 0x00FF;
                sendFrame.data[4] = (cALModelDC2.B_UBAT  >> 8) & 0x00FF;
                sendFrame.data[5] = 0;
                sendFrame.data[6] = 0;
                sendFrame.data[7] = 0;
            }
            else if(0x09 == commmand)
            {
                sendFrame.data[0] = commmand;
                sendFrame.data[1] = cALModelDC2.A_I1BAT & 0x00FF;
                sendFrame.data[2] = (cALModelDC2.A_I1BAT  >> 8) & 0x00FF;
                sendFrame.data[3] = cALModelDC2.B_I1BAT  & 0x00FF;
                sendFrame.data[4] = (cALModelDC2.B_I1BAT  >> 8) & 0x00FF;
                sendFrame.data[5] = 0;
                sendFrame.data[6] = 0;
                sendFrame.data[7] = 0;
            }
            else if(0x0A == commmand)
            {
                sendFrame.data[0] = commmand;
                sendFrame.data[1] = cALModelDC2.A_I2BAT & 0x00FF;
                sendFrame.data[2] = (cALModelDC2.A_I2BAT  >> 8) & 0x00FF;
                sendFrame.data[3] = cALModelDC2.B_I2BAT  & 0x00FF;
                sendFrame.data[4] = (cALModelDC2.B_I2BAT  >> 8) & 0x00FF;
                sendFrame.data[5] = 0;
                sendFrame.data[6] = 0;
                sendFrame.data[7] = 0;
            }
            else if(0x0B == commmand)
            {
                sendFrame.data[0] = commmand;
                sendFrame.data[1] = cALModelDC2.A_IBAT1 & 0x00FF;
                sendFrame.data[2] = (cALModelDC2.A_IBAT1  >> 8) & 0x00FF;
                sendFrame.data[3] = cALModelDC2.B_IBAT1  & 0x00FF;
                sendFrame.data[4] = (cALModelDC2.B_IBAT1  >> 8) & 0x00FF;
                sendFrame.data[5] = 0;
                sendFrame.data[6] = 0;
                sendFrame.data[7] = 0;
            }
            else
            {
                sendFrame.data[0] = commmand;
                sendFrame.data[1] = cALModelDC2.A_IBAT2 & 0x00FF;
                sendFrame.data[2] = (cALModelDC2.A_IBAT2  >> 8) & 0x00FF;
                sendFrame.data[3] = cALModelDC2.B_IBAT2  & 0x00FF;
                sendFrame.data[4] = (cALModelDC2.B_IBAT2  >> 8) & 0x00FF;
                sendFrame.data[5] = 0;
                sendFrame.data[6] = 0;
                sendFrame.data[7] = 0;
            }
        }
        //AC
        else
        {
            if(0x0B == commmand)
            {
                sendFrame.data[0] = commmand;
                sendFrame.data[1] = cALModelAC.A_BUSUDC & 0x00FF;
                sendFrame.data[2] = (cALModelAC.A_BUSUDC  >> 8) & 0x00FF;
                sendFrame.data[3] = cALModelAC.B_BUSUDC  & 0x00FF;
                sendFrame.data[4] = (cALModelAC.B_BUSUDC  >> 8) & 0x00FF;
                sendFrame.data[5] = 0;
                sendFrame.data[6] = 0;
                sendFrame.data[7] = 0;
            }
            else if(0x0C == commmand)
            {
                sendFrame.data[0] = commmand;
                sendFrame.data[1] = cALModelAC.A_UAB & 0x00FF;
                sendFrame.data[2] = (cALModelAC.A_UAB  >> 8) & 0x00FF;
                sendFrame.data[3] = cALModelAC.B_UAB  & 0x00FF;
                sendFrame.data[4] = (cALModelAC.B_UAB  >> 8) & 0x00FF;
                sendFrame.data[5] = 0;
                sendFrame.data[6] = 0;
                sendFrame.data[7] = 0;
            }
            else if(0x0D == commmand)
            {
                sendFrame.data[0] = commmand;
                sendFrame.data[1] = cALModelAC.A_UAC & 0x00FF;
                sendFrame.data[2] = (cALModelAC.A_UAC  >> 8) & 0x00FF;
                sendFrame.data[3] = cALModelAC.B_UAC  & 0x00FF;
                sendFrame.data[4] = (cALModelAC.B_UAC  >> 8) & 0x00FF;
                sendFrame.data[5] = 0;
                sendFrame.data[6] = 0;
                sendFrame.data[7] = 0;
            }
            else if(0x0E == commmand)
            {
                sendFrame.data[0] = commmand;
                sendFrame.data[1] = cALModelAC.A_IA & 0x00FF;
                sendFrame.data[2] = (cALModelAC.A_IA  >> 8) & 0x00FF;
                sendFrame.data[3] = cALModelAC.B_IA  & 0x00FF;
                sendFrame.data[4] = (cALModelAC.B_IA  >> 8) & 0x00FF;
                sendFrame.data[5] = 0;
                sendFrame.data[6] = 0;
                sendFrame.data[7] = 0;
            }
            else
            {
                sendFrame.data[0] = commmand;
                sendFrame.data[1] = cALModelAC.A_IC & 0x00FF;
                sendFrame.data[2] = (cALModelAC.A_IC  >> 8) & 0x00FF;
                sendFrame.data[3] = cALModelAC.B_IC  & 0x00FF;
                sendFrame.data[4] = (cALModelAC.B_IC  >> 8) & 0x00FF;
                sendFrame.data[5] = 0;
                sendFrame.data[6] = 0;
                sendFrame.data[7] = 0;
            }
        }
    }
    //系统参数
    else if(SYSPARA == mode)
    {
        //DC1
        if(0 == ch)
        {
            if(0x01 == commmand)
            {
                sendFrame.data[0] = commmand;
                sendFrame.data[1] = (S_SystemSetDC1.dataproduct.year >> 0) & 0x00FF;
                sendFrame.data[2] = (S_SystemSetDC1.dataproduct.year  >> 8) & 0x00FF;
                sendFrame.data[3] = S_SystemSetDC1.dataproduct.month;
                sendFrame.data[4] = S_SystemSetDC1.dataproduct.day;
                sendFrame.data[5] = 0;
                sendFrame.data[6] = 0;
                sendFrame.data[7] = 0;
            }
            else
            {
                sendFrame.data[0] = commmand;
                sendFrame.data[1] = (S_SystemSetDC1.projectnum >> 0) & 0x00FF;
                sendFrame.data[2] = (S_SystemSetDC1.projectnum  >> 8) & 0x00FF;
                sendFrame.data[3] = (S_SystemSetDC1.projectnum  >> 16) & 0x00FF;
                sendFrame.data[4] = (S_SystemSetDC1.projectnum  >> 24) & 0x00FF;
                sendFrame.data[5] = (S_SystemSetDC1.serialnum >> 0) & 0x00FF;
                sendFrame.data[6] = (S_SystemSetDC1.serialnum >> 8) & 0x00FF;;
                sendFrame.data[7] = S_SystemSetDC1.manufactid;
            }
        }
        //DC2
        else if(1 == ch)
        {
            if(0x01 == commmand)
            {
                sendFrame.data[0] = commmand;
                sendFrame.data[1] = (S_SystemSetDC1.dataproduct.year >> 0) & 0x00FF;
                sendFrame.data[2] = (S_SystemSetDC1.dataproduct.year  >> 8) & 0x00FF;
                sendFrame.data[3] = S_SystemSetDC1.dataproduct.month;
                sendFrame.data[4] = S_SystemSetDC1.dataproduct.day;
                sendFrame.data[5] = 0;
                sendFrame.data[6] = 0;
                sendFrame.data[7] = 0;
            }
            else
            {
                sendFrame.data[0] = commmand;
                sendFrame.data[1] = (S_SystemSetDC1.projectnum >> 0) & 0x00FF;
                sendFrame.data[2] = (S_SystemSetDC1.projectnum  >> 8) & 0x00FF;
                sendFrame.data[3] = (S_SystemSetDC1.projectnum  >> 16) & 0x00FF;
                sendFrame.data[4] = (S_SystemSetDC1.projectnum  >> 24) & 0x00FF;
                sendFrame.data[5] = (S_SystemSetDC1.serialnum >> 0) & 0x00FF;
                sendFrame.data[6] = (S_SystemSetDC1.serialnum >> 8) & 0x00FF;;
                sendFrame.data[7] = S_SystemSetDC1.manufactid;
            }
        }
        //AC
        else
        {
            sendFrame.data[0] = commmand;
            sendFrame.data[1] = (S_SysSetAC.modelpara >> 0) & 0x00FF;
            sendFrame.data[2] = (S_SysSetAC.modelpara  >> 8) & 0x00FF;
            sendFrame.data[3] = (S_SysSetAC.dataproduct.year >> 0) & 0x00FF;
            sendFrame.data[4] = (S_SysSetAC.dataproduct.year  >> 8) & 0x00FF;
            sendFrame.data[5] = S_SysSetAC.dataproduct.month;
            sendFrame.data[6] = S_SysSetAC.dataproduct.day;
            sendFrame.data[7] = S_SysSetAC.softversion;
        }
    }
    //系统参数
    else if(MONTPARA == mode)
    {
        sendFrame.data[0] = commmand;
        sendFrame.data[1] = S_MotionConAc.resume;
        sendFrame.data[2] = S_MotionConAc.dcmodesel;
        sendFrame.data[3] = S_MotionConAc.mastandby;
        sendFrame.data[4] = S_MotionConAc.modulation;
        sendFrame.data[5] = 0;
        sendFrame.data[6] = 0;
        sendFrame.data[7] = 0;
    }
    else
    {

    }

    sendFrame.canID = canid;
    sendFrame.dataLen = 8;
    canThreadsend->SendMsg(sendFrame);
}


/***************************************************************控制参数******************************************/
/***************************************************************控制参数******************************************/
/***************************************************************控制参数******************************************/
/*******************DC1*****************************/
/*******************DC1*****************************/
/*******************DC1*****************************/
//0x03
//功率给定限值
void SysSettingWindow::on_lineEdit_textChanged(const QString &arg1)
{
    ControlParalDC1.POUTLIMIT = arg1.toDouble()*10;
}

void SysSettingWindow::on_pushButton_4_clicked()
{
    sendcmd(0x040020CC,0x03,CONPARA,0);
}

//直流电流给定限值
void SysSettingWindow::on_lineEdit_2_textChanged(const QString &arg1)
{
    ControlParalDC1.HMIIBATL = arg1.toInt();
}

void SysSettingWindow::on_pushButton_5_clicked()
{
    sendcmd(0x040020CC,0x03,CONPARA,0);
}

//死区时间
void SysSettingWindow::on_lineEdit_3_textChanged(const QString &arg1)
{
    ControlParalDC1.DEADTIME = arg1.toInt();
}

void SysSettingWindow::on_pushButton_7_clicked()
{
    sendcmd(0x040020CC,0x03,CONPARA,0);
}

//最小导通时间
void SysSettingWindow::on_lineEdit_7_textChanged(const QString &arg1)
{
    ControlParalDC1.MINONTIME = arg1.toInt();
}

void SysSettingWindow::on_pushButton_8_clicked()
{
    sendcmd(0x040020CC,0x03,CONPARA,0);
}

//0x04
//DC开关频率
void SysSettingWindow::on_lineEdit_4_textChanged(const QString &arg1)
{
    ControlParalDC1.DCDC_SWFR = arg1.toDouble()*100;
}

void SysSettingWindow::on_pushButton_9_clicked()
{
    sendcmd(0x040020CC,0x04,CONPARA,0);
}

//电压给定变化率
void SysSettingWindow::on_lineEdit_5_textChanged(const QString &arg1)
{
    ControlParalDC1.RU_UDCT = arg1.toInt();
}

void SysSettingWindow::on_pushButton_10_clicked()
{
    sendcmd(0x040020CC,0x04,CONPARA,0);
}

//电流给定变化率
void SysSettingWindow::on_lineEdit_6_textChanged(const QString &arg1)
{
    ControlParalDC1.RU_IDT = arg1.toInt();
}

void SysSettingWindow::on_pushButton_11_clicked()
{
    sendcmd(0x040020CC,0x04,CONPARA,0);
}

/*******************DC2*****************************/
/*******************DC2*****************************/
/*******************DC2*****************************/
//0x03
//功率给定限值
void SysSettingWindow::on_lineEdit_8_textChanged(const QString &arg1)
{
    ControlParalDC2.POUTLIMIT = arg1.toDouble()*10;
}

void SysSettingWindow::on_pushButton_12_clicked()
{
    sendcmd(0x040021CC,0x03,CONPARA,1);
}

//直流电流给定限值
void SysSettingWindow::on_lineEdit_9_textChanged(const QString &arg1)
{
    ControlParalDC2.HMIIBATL = arg1.toInt();
}

void SysSettingWindow::on_pushButton_13_clicked()
{
    sendcmd(0x040021CC,0x03,CONPARA,1);
}

//死区时间
void SysSettingWindow::on_lineEdit_10_textChanged(const QString &arg1)
{
    ControlParalDC2.DEADTIME = arg1.toInt();
}

void SysSettingWindow::on_pushButton_14_clicked()
{
    sendcmd(0x040021CC,0x03,CONPARA,1);
}

//最小导通时间
void SysSettingWindow::on_lineEdit_11_textChanged(const QString &arg1)
{
    ControlParalDC2.MINONTIME = arg1.toInt();
}

void SysSettingWindow::on_pushButton_15_clicked()
{
    sendcmd(0x040021CC,0x03,CONPARA,1);
}

//0x04
//DC开关频率
void SysSettingWindow::on_lineEdit_12_textChanged(const QString &arg1)
{
     ControlParalDC2.DCDC_SWFR = arg1.toDouble()*100;
}

void SysSettingWindow::on_pushButton_16_clicked()
{
    sendcmd(0x040021CC,0x04,CONPARA,1);
}

//电压给定变化率
void SysSettingWindow::on_lineEdit_13_textChanged(const QString &arg1)
{
    ControlParalDC2.RU_UDCT = arg1.toInt();
}

void SysSettingWindow::on_pushButton_17_clicked()
{
    sendcmd(0x040021CC,0x04,CONPARA,1);
}

//电流给定变化率
void SysSettingWindow::on_lineEdit_14_textChanged(const QString &arg1)
{
    ControlParalDC2.RU_IDT = arg1.toInt();
}

void SysSettingWindow::on_pushButton_18_clicked()
{
    sendcmd(0x040021CC,0x04,CONPARA,1);
}

/*******************AC*****************************/
/*******************AC*****************************/
/*******************AC*****************************/

//0x02
//电流给定限值
void SysSettingWindow::on_lineEdit_15_textChanged(const QString &arg1)
{
    ControlParaModelAC.IACLIMIT = arg1.toInt();
}

void SysSettingWindow::on_pushButton_19_clicked()
{
    sendcmd(0x0400A0CC,0x02,CONPARA,2);
}

//直流电压给定变化率
void SysSettingWindow::on_lineEdit_16_textChanged(const QString &arg1)
{
    ControlParaModelAC.RU_UDCT = arg1.toInt();
}

void SysSettingWindow::on_pushButton_20_clicked()
{
    sendcmd(0x0400A0CC,0x02,CONPARA,2);
}

//开关频率
void SysSettingWindow::on_lineEdit_25_textChanged(const QString &arg1)
{
    ControlParaModelAC.SW_FR = arg1.toDouble()*100;
}

void SysSettingWindow::on_pushButton_21_clicked()
{
    sendcmd(0x0400A0CC,0x02,CONPARA,2);
}

//最小导通时间
void SysSettingWindow::on_lineEdit_17_textChanged(const QString &arg1)
{
    ControlParaModelAC.MINONTIME = arg1.toInt();
}

void SysSettingWindow::on_pushButton_22_clicked()
{
    sendcmd(0x0400A0CC,0x02,CONPARA,2);
}

//死区时间
void SysSettingWindow::on_lineEdit_24_textChanged(const QString &arg1)
{
    ControlParaModelAC.DEADTIME = arg1.toInt();
}

void SysSettingWindow::on_pushButton_23_clicked()
{
    sendcmd(0x0400A0CC,0x02,CONPARA,2);
}

//0x03
//死区补偿时间
void SysSettingWindow::on_lineEdit_18_textChanged(const QString &arg1)
{
    ControlParaModelAC.COMPTIME1 = arg1.toInt();
}


void SysSettingWindow::on_pushButton_24_clicked()
{
    sendcmd(0x0400A0CC,0x03,CONPARA,2);
}

//死区补偿角度
void SysSettingWindow::on_lineEdit_19_textChanged(const QString &arg1)
{
    ControlParaModelAC.COMPANGLE = arg1.toInt();
}

void SysSettingWindow::on_pushButton_25_clicked()
{
    sendcmd(0x0400A0CC,0x03,CONPARA,2);
}

//dq电压滤波拍数
void SysSettingWindow::on_lineEdit_20_textChanged(const QString &arg1)
{
    ControlParaModelAC.SC_USTEP1 = arg1.toInt();
}

void SysSettingWindow::on_pushButton_28_clicked()
{
    sendcmd(0x0400A0CC,0x03,CONPARA,2);
}

//dq电流滤波拍数
void SysSettingWindow::on_lineEdit_21_textChanged(const QString &arg1)
{
    ControlParaModelAC.SC_ISTEP1 = arg1.toInt();
}

void SysSettingWindow::on_pushButton_26_clicked()
{
    sendcmd(0x0400A0CC,0x03,CONPARA,2);
}

//低穿电流给定变化率
void SysSettingWindow::on_lineEdit_23_textChanged(const QString &arg1)
{
    ControlParaModelAC.UDCH = arg1.toInt();
}

void SysSettingWindow::on_pushButton_27_clicked()
{
    sendcmd(0x0400A0CC,0x03,CONPARA,2);
}

//电流给定变化率
void SysSettingWindow::on_lineEdit_22_textChanged(const QString &arg1)
{
    ControlParaModelAC.RU_IDT = arg1.toInt();
}

void SysSettingWindow::on_pushButton_29_clicked()
{
    sendcmd(0x0400A0CC,0x03,CONPARA,2);
}

//读取DC1参数
void SysSettingWindow::on_pushButton_6_clicked()
{
    canFrame sendFrame;
    sendFrame.data[0] = 0x03;
    sendFrame.data[1] = 0;
    sendFrame.data[2] = 0;
    sendFrame.data[3] = 0;
    sendFrame.data[4] = 0;
    sendFrame.data[5] = 0;
    sendFrame.data[6] = 0;
    sendFrame.data[7] = 0;
    sendFrame.dataLen = 8;
    sendFrame.canID = 0x080020CC;
    canThreadsend->SendMsg(sendFrame);
    QThread::msleep(20);

    sendFrame.data[0] = 0x04;
    canThreadsend->SendMsg(sendFrame);

    if(timer1->isActive() != true)
        timer1->start(1000);
}

//读取DC2参数
void SysSettingWindow::on_pushButton_30_clicked()
{
    canFrame sendFrame;
    sendFrame.data[0] = 0x03;
    sendFrame.data[1] = 0;
    sendFrame.data[2] = 0;
    sendFrame.data[3] = 0;
    sendFrame.data[4] = 0;
    sendFrame.data[5] = 0;
    sendFrame.data[6] = 0;
    sendFrame.data[7] = 0;
    sendFrame.dataLen = 8;
    sendFrame.canID = 0x080021CC;
    canThreadsend->SendMsg(sendFrame);
    QThread::msleep(20);

    sendFrame.data[0] = 0x04;
    canThreadsend->SendMsg(sendFrame);

    if(timer1->isActive() != true)
        timer1->start(1000);
}

//读取AC参数
void SysSettingWindow::on_pushButton_31_clicked()
{
    canFrame sendFrame;
    sendFrame.data[0] = 0x02;
    sendFrame.data[1] = 0;
    sendFrame.data[2] = 0;
    sendFrame.data[3] = 0;
    sendFrame.data[4] = 0;
    sendFrame.data[5] = 0;
    sendFrame.data[6] = 0;
    sendFrame.data[7] = 0;
    sendFrame.dataLen = 8;
    sendFrame.canID = 0x0800A0CC;
    canThreadsend->SendMsg(sendFrame);
    QThread::msleep(20);

    sendFrame.data[0] = 0x03;
    canThreadsend->SendMsg(sendFrame);

    if(timer1->isActive() != true)
        timer1->start(1000);
}

/***************************************************************保护参数******************************************/
/***************************************************************保护参数******************************************/
/***************************************************************保护参数******************************************/
/*******************DC1*****************************/
/*******************DC1*****************************/
/*******************DC1*****************************/
void SysSettingWindow::on_lineEdit_26_textChanged(const QString &arg1)
{
    ProtectParaDC1.SC_UDCOV = arg1.toInt();
}

void SysSettingWindow::on_pushButton_33_clicked()
{
    sendcmd(0x040020CC,0x05,PROTPARA,0);
}

void SysSettingWindow::on_lineEdit_27_textChanged(const QString &arg1)
{
    ProtectParaDC1.SC_EEREPT = arg1.toInt();
}

void SysSettingWindow::on_pushButton_34_clicked()
{
    sendcmd(0x040020CC,0x05,PROTPARA,0);
}

void SysSettingWindow::on_lineEdit_28_textChanged(const QString &arg1)
{
    ProtectParaDC1.SC_RCOVT = arg1.toInt();
}

void SysSettingWindow::on_pushButton_35_clicked()
{
    sendcmd(0x040020CC,0x05,PROTPARA,0);
}

void SysSettingWindow::on_lineEdit_29_textChanged(const QString &arg1)
{
    ProtectParaDC1.SC_UBATDV = arg1.toDouble()*10;
}

void SysSettingWindow::on_pushButton_36_clicked()
{
    sendcmd(0x040020CC,0x05,PROTPARA,0);
}

/*******************DC2*****************************/
/*******************DC2*****************************/
/*******************DC2*****************************/

void SysSettingWindow::on_lineEdit_43_textChanged(const QString &arg1)
{
    ProtectParaDC2.SC_UDCOV = arg1.toInt();
}

void SysSettingWindow::on_pushButton_50_clicked()
{
    sendcmd(0x040021CC,0x05,PROTPARA,1);
}

void SysSettingWindow::on_lineEdit_41_textChanged(const QString &arg1)
{
    ProtectParaDC2.SC_EEREPT = arg1.toInt();
}

void SysSettingWindow::on_pushButton_52_clicked()
{
     sendcmd(0x040021CC,0x05,PROTPARA,1);
}

void SysSettingWindow::on_lineEdit_44_textChanged(const QString &arg1)
{
    ProtectParaDC2.SC_RCOVT = arg1.toInt();
}

void SysSettingWindow::on_pushButton_51_clicked()
{
     sendcmd(0x040021CC,0x05,PROTPARA,1);
}

void SysSettingWindow::on_lineEdit_42_textChanged(const QString &arg1)
{
    ProtectParaDC2.SC_UBATDV = arg1.toDouble()*10;
}

void SysSettingWindow::on_pushButton_53_clicked()
{
     sendcmd(0x040021CC,0x05,PROTPARA,1);
}



/*******************AC*****************************/
/*******************AC*****************************/
/*******************AC*****************************/
//0x04
void SysSettingWindow::on_lineEdit_30_textChanged(const QString &arg1)
{
    ProtectParaAC.SC_UDCOV = arg1.toInt();
}

void SysSettingWindow::on_pushButton_38_clicked()
{
    sendcmd(0x0400A0CC,0x04,PROTPARA,2);
}

void SysSettingWindow::on_lineEdit_31_textChanged(const QString &arg1)
{
    ProtectParaAC.SC_UACOV = arg1.toInt();
}

void SysSettingWindow::on_pushButton_39_clicked()
{
    sendcmd(0x0400A0CC,0x04,PROTPARA,2);
}

void SysSettingWindow::on_lineEdit_32_textChanged(const QString &arg1)
{
    ProtectParaAC.SC_UACLV = arg1.toInt();
}

void SysSettingWindow::on_pushButton_40_clicked()
{
    sendcmd(0x0400A0CC,0x04,PROTPARA,2);
}

void SysSettingWindow::on_lineEdit_33_textChanged(const QString &arg1)
{
    ProtectParaAC.SC_IACOV = arg1.toInt();
}

void SysSettingWindow::on_pushButton_41_clicked()
{
    sendcmd(0x0400A0CC,0x04,PROTPARA,2);
}

//0x05
void SysSettingWindow::on_lineEdit_34_textChanged(const QString &arg1)
{
    ProtectParaAC.SC_EFFHIG = arg1.toDouble()*100;
}

void SysSettingWindow::on_pushButton_42_clicked()
{
    sendcmd(0x0400A0CC,0x05,PROTPARA,2);
}

void SysSettingWindow::on_lineEdit_35_textChanged(const QString &arg1)
{
    ProtectParaAC.SC_EFFLOW = arg1.toDouble()*100;
}

void SysSettingWindow::on_pushButton_43_clicked()
{
    sendcmd(0x0400A0CC,0x05,PROTPARA,2);
}

void SysSettingWindow::on_lineEdit_36_textChanged(const QString &arg1)
{
    ProtectParaAC.SC_DETAOMIGA = arg1.toInt();
}

void SysSettingWindow::on_pushButton_44_clicked()
{
    sendcmd(0x0400A0CC,0x05,PROTPARA,2);
}

void SysSettingWindow::on_lineEdit_37_textChanged(const QString &arg1)
{
    ProtectParaAC.SC_IACEQUAL = arg1.toInt();
}

void SysSettingWindow::on_pushButton_45_clicked()
{
    sendcmd(0x0400A0CC,0x05,PROTPARA,2);
}

//0x06
void SysSettingWindow::on_lineEdit_38_textChanged(const QString &arg1)
{
    ProtectParaAC.SC_FINTRT = arg1.toDouble()*100;
}

void SysSettingWindow::on_pushButton_46_clicked()
{
    sendcmd(0x0400A0CC,0x06,PROTPARA,2);
}

void SysSettingWindow::on_lineEdit_39_textChanged(const QString &arg1)
{
    ProtectParaAC.SC_RCOVT = arg1.toInt();
}

void SysSettingWindow::on_pushButton_47_clicked()
{
    sendcmd(0x0400A0CC,0x06,PROTPARA,2);
}

void SysSettingWindow::on_lineEdit_40_textChanged(const QString &arg1)
{
    ProtectParaAC.SC_EEREPT = arg1.toInt();
}

void SysSettingWindow::on_pushButton_48_clicked()
{
    sendcmd(0x0400A0CC,0x06,PROTPARA,2);
}

void SysSettingWindow::on_lineEdit_45_textChanged(const QString &arg1)
{
    ProtectParaAC.SC_IGBTDOWN = arg1.toInt();
}

void SysSettingWindow::on_pushButton_54_clicked()
{
    sendcmd(0x0400A0CC,0x06,PROTPARA,2);
}

//读取DC1
void SysSettingWindow::on_pushButton_32_clicked()
{
    canFrame sendFrame;
    sendFrame.data[0] = 0x05;
    sendFrame.data[1] = 0;
    sendFrame.data[2] = 0;
    sendFrame.data[3] = 0;
    sendFrame.data[4] = 0;
    sendFrame.data[5] = 0;
    sendFrame.data[6] = 0;
    sendFrame.data[7] = 0;
    sendFrame.dataLen = 8;
    sendFrame.canID = 0x080020CC;
    canThreadsend->SendMsg(sendFrame);

    if(timer1->isActive() != true)
        timer1->start(1000);
}

//读取DC2
void SysSettingWindow::on_pushButton_49_clicked()
{
    canFrame sendFrame;
    sendFrame.data[0] = 0x05;
    sendFrame.data[1] = 0;
    sendFrame.data[2] = 0;
    sendFrame.data[3] = 0;
    sendFrame.data[4] = 0;
    sendFrame.data[5] = 0;
    sendFrame.data[6] = 0;
    sendFrame.data[7] = 0;
    sendFrame.dataLen = 8;
    sendFrame.canID = 0x080021CC;
    canThreadsend->SendMsg(sendFrame);

    if(timer1->isActive() != true)
        timer1->start(1000);
}

//读取AC
void SysSettingWindow::on_pushButton_37_clicked()
{
    canFrame sendFrame;
    sendFrame.data[0] = 0x04;
    sendFrame.data[1] = 0;
    sendFrame.data[2] = 0;
    sendFrame.data[3] = 0;
    sendFrame.data[4] = 0;
    sendFrame.data[5] = 0;
    sendFrame.data[6] = 0;
    sendFrame.data[7] = 0;
    sendFrame.dataLen = 8;
    sendFrame.canID = 0x0800A0CC;
    canThreadsend->SendMsg(sendFrame);
    QThread::msleep(20);

    sendFrame.data[0] = 0x05;
    canThreadsend->SendMsg(sendFrame);
    QThread::msleep(20);

    sendFrame.data[0] = 0x06;
    canThreadsend->SendMsg(sendFrame);

    if(timer1->isActive() != true)
        timer1->start(1000);
}

/***************************************************************PI参数******************************************/
/***************************************************************PI参数******************************************/
/***************************************************************PI参数******************************************/
/*******************DC1*****************************/
/*******************DC1*****************************/
/*******************DC1*****************************/
void SysSettingWindow::on_lineEdit_48_textChanged(const QString &arg1)
{
    pIModelDC1.UbatKP = arg1.toInt();
}

void SysSettingWindow::on_pushButton_56_clicked()
{
    sendcmd(0x040020CC,0x06,PIPARA,0);
}

void SysSettingWindow::on_lineEdit_46_textChanged(const QString &arg1)
{
    pIModelDC1.UbatTI = arg1.toInt();
}

void SysSettingWindow::on_pushButton_58_clicked()
{
    sendcmd(0x040020CC,0x06,PIPARA,0);
}

void SysSettingWindow::on_lineEdit_49_textChanged(const QString &arg1)
{
    pIModelDC1.IbatKP = arg1.toInt();
}

void SysSettingWindow::on_pushButton_57_clicked()
{
    sendcmd(0x040020CC,0x07,PIPARA,0);
}

void SysSettingWindow::on_lineEdit_47_textChanged(const QString &arg1)
{
    pIModelDC1.IbatTI = arg1.toInt();
}


void SysSettingWindow::on_pushButton_59_clicked()
{
    sendcmd(0x040020CC,0x07,PIPARA,0);
}

/*******************DC2*****************************/
/*******************DC2*****************************/
/*******************DC2*****************************/
void SysSettingWindow::on_lineEdit_52_textChanged(const QString &arg1)
{
    pIModelDC2.UbatKP = arg1.toInt();
}

void SysSettingWindow::on_pushButton_61_clicked()
{
    sendcmd(0x040021CC,0x06,PIPARA,1);
}

void SysSettingWindow::on_lineEdit_50_textChanged(const QString &arg1)
{
    pIModelDC2.UbatTI = arg1.toInt();
}

void SysSettingWindow::on_pushButton_63_clicked()
{
    sendcmd(0x040021CC,0x06,PIPARA,1);
}

void SysSettingWindow::on_lineEdit_53_textChanged(const QString &arg1)
{
    pIModelDC2.IbatKP = arg1.toInt();
}

void SysSettingWindow::on_pushButton_62_clicked()
{
    sendcmd(0x040021CC,0x07,PIPARA,1);
}

void SysSettingWindow::on_lineEdit_51_textChanged(const QString &arg1)
{
    pIModelDC2.IbatTI = arg1.toInt();
}

void SysSettingWindow::on_pushButton_64_clicked()
{
    sendcmd(0x040021CC,0x07,PIPARA,1);
}

/*******************AC*****************************/
/*******************AC*****************************/
/*******************AC*****************************/

void SysSettingWindow::on_lineEdit_54_textChanged(const QString &arg1)
{
    pIModelAC.UdcKP = arg1.toInt();
}

void SysSettingWindow::on_pushButton_66_clicked()
{
    sendcmd(0x0400A0CC,0x07,PIPARA,2);
}

void SysSettingWindow::on_lineEdit_62_textChanged(const QString &arg1)
{
    pIModelAC.UdcTI = arg1.toInt();
}

void SysSettingWindow::on_pushButton_67_clicked()
{
    sendcmd(0x0400A0CC,0x07,PIPARA,2);
}

void SysSettingWindow::on_lineEdit_61_textChanged(const QString &arg1)
{
    pIModelAC.PLLKP = arg1.toInt();
}

void SysSettingWindow::on_pushButton_68_clicked()
{
    sendcmd(0x0400A0CC,0x08,PIPARA,2);
}

void SysSettingWindow::on_lineEdit_56_textChanged(const QString &arg1)
{
    pIModelAC.PLLTI = arg1.toInt();
}

void SysSettingWindow::on_pushButton_69_clicked()
{
    sendcmd(0x0400A0CC,0x08,PIPARA,2);
}

void SysSettingWindow::on_lineEdit_55_textChanged(const QString &arg1)
{
    pIModelAC.IdKP = arg1.toInt();
}

void SysSettingWindow::on_pushButton_71_clicked()
{
    sendcmd(0x0400A0CC,0x09,PIPARA,2);
}

void SysSettingWindow::on_lineEdit_57_textChanged(const QString &arg1)
{
    pIModelAC.IdTI = arg1.toInt();
}

void SysSettingWindow::on_pushButton_72_clicked()
{
    sendcmd(0x0400A0CC,0x09,PIPARA,2);
}

void SysSettingWindow::on_lineEdit_59_textChanged(const QString &arg1)
{
    pIModelAC.IqKP = arg1.toInt();
}

void SysSettingWindow::on_pushButton_73_clicked()
{
    sendcmd(0x0400A0CC,0x0A,PIPARA,2);
}

void SysSettingWindow::on_lineEdit_60_textChanged(const QString &arg1)
{
    pIModelAC.IqTI = arg1.toInt();
}

void SysSettingWindow::on_pushButton_70_clicked()
{
    sendcmd(0x0400A0CC,0x0A,PIPARA,2);
}

//DC1
void SysSettingWindow::on_pushButton_55_clicked()
{
    canFrame sendFrame;
    sendFrame.data[0] = 0x06;
    sendFrame.data[1] = 0;
    sendFrame.data[2] = 0;
    sendFrame.data[3] = 0;
    sendFrame.data[4] = 0;
    sendFrame.data[5] = 0;
    sendFrame.data[6] = 0;
    sendFrame.data[7] = 0;
    sendFrame.dataLen = 8;
    sendFrame.canID = 0x080020CC;
    canThreadsend->SendMsg(sendFrame);
    QThread::msleep(20);

    sendFrame.data[0] = 0x07;
    canThreadsend->SendMsg(sendFrame);

    if(timer1->isActive() != true)
        timer1->start(1000);
}

void SysSettingWindow::on_pushButton_60_clicked()
{
    canFrame sendFrame;
    sendFrame.data[0] = 0x06;
    sendFrame.data[1] = 0;
    sendFrame.data[2] = 0;
    sendFrame.data[3] = 0;
    sendFrame.data[4] = 0;
    sendFrame.data[5] = 0;
    sendFrame.data[6] = 0;
    sendFrame.data[7] = 0;
    sendFrame.dataLen = 8;
    sendFrame.canID = 0x080021CC;
    canThreadsend->SendMsg(sendFrame);
    QThread::msleep(20);

    sendFrame.data[0] = 0x07;
    canThreadsend->SendMsg(sendFrame);

    if(timer1->isActive() != true)
        timer1->start(1000);
}

void SysSettingWindow::on_pushButton_65_clicked()
{
    canFrame sendFrame;
    sendFrame.data[0] = 0x07;
    sendFrame.data[1] = 0;
    sendFrame.data[2] = 0;
    sendFrame.data[3] = 0;
    sendFrame.data[4] = 0;
    sendFrame.data[5] = 0;
    sendFrame.data[6] = 0;
    sendFrame.data[7] = 0;
    sendFrame.dataLen = 8;
    sendFrame.canID = 0x0800A0CC ;
    canThreadsend->SendMsg(sendFrame);
    QThread::msleep(20);

    sendFrame.data[0] = 0x08;
    canThreadsend->SendMsg(sendFrame);
    QThread::msleep(20);

    sendFrame.data[0] = 0x09;
    canThreadsend->SendMsg(sendFrame);
    QThread::msleep(20);

    sendFrame.data[0] = 0x0A;
    canThreadsend->SendMsg(sendFrame);

    if(timer1->isActive() != true)
        timer1->start(1000);
}

/***************************************************************校准参数******************************************/
/***************************************************************校准参数******************************************/
/***************************************************************校准参数******************************************/
/*******************DC1*****************************/
/*******************DC1*****************************/
/*******************DC1*****************************/

void SysSettingWindow::on_lineEdit_58_textChanged(const QString &arg1)
{
    cALModelDC1.A_UBAT = arg1.toInt();
}

void SysSettingWindow::on_pushButton_75_clicked()
{
    sendcmd(0x040020CC,0x08,CALPARA,0);
}

void SysSettingWindow::on_lineEdit_63_textChanged(const QString &arg1)
{
    cALModelDC1.B_UBAT = arg1.toInt();
}

void SysSettingWindow::on_pushButton_76_clicked()
{
    sendcmd(0x040020CC,0x08,CALPARA,0);
}

void SysSettingWindow::on_lineEdit_64_textChanged(const QString &arg1)
{
    cALModelDC1.A_I1BAT = arg1.toInt();
}

void SysSettingWindow::on_pushButton_77_clicked()
{
    sendcmd(0x040020CC,0x09,CALPARA,0);
}

void SysSettingWindow::on_lineEdit_65_textChanged(const QString &arg1)
{
    cALModelDC1.B_I1BAT = arg1.toInt();
}

void SysSettingWindow::on_pushButton_78_clicked()
{
    sendcmd(0x040020CC,0x09,CALPARA,0);
}

void SysSettingWindow::on_lineEdit_66_textChanged(const QString &arg1)
{
    cALModelDC1.A_I2BAT = arg1.toInt();
}

void SysSettingWindow::on_pushButton_79_clicked()
{
    sendcmd(0x040020CC,0x0A,CALPARA,0);
}

void SysSettingWindow::on_lineEdit_67_textChanged(const QString &arg1)
{
    cALModelDC1.B_I2BAT = arg1.toInt();
}

void SysSettingWindow::on_pushButton_80_clicked()
{
    sendcmd(0x040020CC,0x0A,CALPARA,0);
}

void SysSettingWindow::on_lineEdit_68_textChanged(const QString &arg1)
{
    cALModelDC1.A_IBAT1 = arg1.toInt();
}

void SysSettingWindow::on_pushButton_81_clicked()
{
    sendcmd(0x040020CC,0x0B,CALPARA,0);
}

void SysSettingWindow::on_lineEdit_69_textChanged(const QString &arg1)
{
    cALModelDC1.B_IBAT1 = arg1.toInt();
}

void SysSettingWindow::on_pushButton_82_clicked()
{
     sendcmd(0x040020CC,0x0B,CALPARA,0);
}

void SysSettingWindow::on_lineEdit_70_textChanged(const QString &arg1)
{
    cALModelDC1.A_IBAT2 = arg1.toInt();
}

void SysSettingWindow::on_pushButton_83_clicked()
{
     sendcmd(0x040020CC,0x0C,CALPARA,0);
}

void SysSettingWindow::on_lineEdit_71_textChanged(const QString &arg1)
{
    cALModelDC1.B_IBAT2 = arg1.toInt();
}

void SysSettingWindow::on_pushButton_84_clicked()
{
    sendcmd(0x040020CC,0x0C,CALPARA,0);
}

/*******************DC2*****************************/
/*******************DC2*****************************/
/*******************DC2*****************************/

void SysSettingWindow::on_lineEdit_82_textChanged(const QString &arg1)
{
     cALModelDC2.A_UBAT = arg1.toInt();
}

void SysSettingWindow::on_pushButton_97_clicked()
{
    sendcmd(0x040021CC,0x08,CALPARA,1);
}

void SysSettingWindow::on_lineEdit_83_textChanged(const QString &arg1)
{
    cALModelDC2.B_UBAT = arg1.toInt();
}

void SysSettingWindow::on_pushButton_98_clicked()
{
    sendcmd(0x040021CC,0x08,CALPARA,1);
}

void SysSettingWindow::on_lineEdit_84_textChanged(const QString &arg1)
{
    cALModelDC2.A_I1BAT = arg1.toInt();
}

void SysSettingWindow::on_pushButton_99_clicked()
{
    sendcmd(0x040021CC,0x09,CALPARA,1);
}

void SysSettingWindow::on_lineEdit_85_textChanged(const QString &arg1)
{
    cALModelDC2.B_I1BAT = arg1.toInt();
}

void SysSettingWindow::on_pushButton_100_clicked()
{
    sendcmd(0x040021CC,0x09,CALPARA,1);
}

void SysSettingWindow::on_lineEdit_86_textChanged(const QString &arg1)
{
    cALModelDC2.A_I2BAT = arg1.toInt();
}

void SysSettingWindow::on_pushButton_101_clicked()
{
    sendcmd(0x040021CC,0x0A,CALPARA,1);
}

void SysSettingWindow::on_lineEdit_87_textChanged(const QString &arg1)
{
    cALModelDC2.B_I2BAT = arg1.toInt();
}

void SysSettingWindow::on_pushButton_102_clicked()
{
    sendcmd(0x040021CC,0x0A,CALPARA,1);
}

void SysSettingWindow::on_lineEdit_88_textChanged(const QString &arg1)
{
    cALModelDC2.A_IBAT1 = arg1.toInt();
}

void SysSettingWindow::on_pushButton_103_clicked()
{
     sendcmd(0x040021CC,0x0B,CALPARA,1);
}

void SysSettingWindow::on_lineEdit_89_textChanged(const QString &arg1)
{
    cALModelDC2.B_IBAT1 = arg1.toInt();
}

void SysSettingWindow::on_pushButton_104_clicked()
{
    sendcmd(0x040021CC,0x0B,CALPARA,1);
}

void SysSettingWindow::on_lineEdit_90_textChanged(const QString &arg1)
{
    cALModelDC2.A_IBAT2 = arg1.toInt();
}

void SysSettingWindow::on_pushButton_105_clicked()
{
    sendcmd(0x040021CC,0x0C,CALPARA,1);
}

void SysSettingWindow::on_lineEdit_91_textChanged(const QString &arg1)
{
    cALModelDC2.B_IBAT2 = arg1.toInt();
}

void SysSettingWindow::on_pushButton_106_clicked()
{
    sendcmd(0x040021CC,0x0C,CALPARA,1);
}

/*******************AC*****************************/
/*******************AC*****************************/
/*******************AC*****************************/

void SysSettingWindow::on_lineEdit_102_textChanged(const QString &arg1)
{
    cALModelAC.A_BUSUDC = arg1.toInt();
}

void SysSettingWindow::on_pushButton_119_clicked()
{
    sendcmd(0x0400A0CC,0x0B,CALPARA,2);
}

void SysSettingWindow::on_lineEdit_103_textChanged(const QString &arg1)
{
     cALModelAC.B_BUSUDC = arg1.toInt();
}

void SysSettingWindow::on_pushButton_120_clicked()
{
     sendcmd(0x0400A0CC,0x0B,CALPARA,2);
}

void SysSettingWindow::on_lineEdit_104_textChanged(const QString &arg1)
{
     cALModelAC.A_UAB = arg1.toInt();
}

void SysSettingWindow::on_pushButton_121_clicked()
{
     sendcmd(0x0400A0CC,0x0C,CALPARA,2);
}

void SysSettingWindow::on_lineEdit_105_textChanged(const QString &arg1)
{
     cALModelAC.B_UAB = arg1.toInt();
}

void SysSettingWindow::on_pushButton_122_clicked()
{
     sendcmd(0x0400A0CC,0x0C,CALPARA,2);
}

void SysSettingWindow::on_lineEdit_106_textChanged(const QString &arg1)
{
     cALModelAC.A_UAC = arg1.toInt();
}

void SysSettingWindow::on_pushButton_123_clicked()
{
     sendcmd(0x0400A0CC,0x0D,CALPARA,2);
}

void SysSettingWindow::on_lineEdit_107_textChanged(const QString &arg1)
{
     cALModelAC.B_UAC = arg1.toInt();
}

void SysSettingWindow::on_pushButton_124_clicked()
{
     sendcmd(0x0400A0CC,0x0D,CALPARA,2);
}

void SysSettingWindow::on_lineEdit_108_textChanged(const QString &arg1)
{
     cALModelAC.A_IA = arg1.toInt();
}

void SysSettingWindow::on_pushButton_125_clicked()
{
     sendcmd(0x0400A0CC,0x0E,CALPARA,2);
}

void SysSettingWindow::on_lineEdit_109_textChanged(const QString &arg1)
{
     cALModelAC.B_IA = arg1.toInt();
}

void SysSettingWindow::on_pushButton_126_clicked()
{
     sendcmd(0x0400A0CC,0x0E,CALPARA,2);
}

void SysSettingWindow::on_lineEdit_110_textChanged(const QString &arg1)
{
     cALModelAC.A_IC = arg1.toInt();
}

void SysSettingWindow::on_pushButton_127_clicked()
{
     sendcmd(0x0400A0CC,0x0F,CALPARA,2);
}

void SysSettingWindow::on_lineEdit_111_textChanged(const QString &arg1)
{
     cALModelAC.B_IC = arg1.toInt();
}

void SysSettingWindow::on_pushButton_128_clicked()
{
     sendcmd(0x0400A0CC,0x0F,CALPARA,2);
}

//读取DC1
void SysSettingWindow::on_pushButton_74_clicked()
{
    canFrame sendFrame;
    sendFrame.data[0] = 0x08;
    sendFrame.data[1] = 0;
    sendFrame.data[2] = 0;
    sendFrame.data[3] = 0;
    sendFrame.data[4] = 0;
    sendFrame.data[5] = 0;
    sendFrame.data[6] = 0;
    sendFrame.data[7] = 0;
    sendFrame.dataLen = 8;
    sendFrame.canID = 0x080020CC ;
    canThreadsend->SendMsg(sendFrame);
    QThread::msleep(5);

    sendFrame.data[0] = 0x09;
    canThreadsend->SendMsg(sendFrame);
    QThread::msleep(5);

    sendFrame.data[0] = 0x0A;
    canThreadsend->SendMsg(sendFrame);
    QThread::msleep(5);

    sendFrame.data[0] = 0x0B;
    canThreadsend->SendMsg(sendFrame);
    QThread::msleep(5);

    sendFrame.data[0] = 0x0C;
    canThreadsend->SendMsg(sendFrame);

    if(timer1->isActive() != true)
        timer1->start(1000);
}

//读取DC2
void SysSettingWindow::on_pushButton_96_clicked()
{
    canFrame sendFrame;
    sendFrame.data[0] = 0x08;
    sendFrame.data[1] = 0;
    sendFrame.data[2] = 0;
    sendFrame.data[3] = 0;
    sendFrame.data[4] = 0;
    sendFrame.data[5] = 0;
    sendFrame.data[6] = 0;
    sendFrame.data[7] = 0;
    sendFrame.dataLen = 8;
    sendFrame.canID = 0x080021CC ;
    canThreadsend->SendMsg(sendFrame);
    QThread::msleep(20);

    sendFrame.data[0] = 0x09;
    canThreadsend->SendMsg(sendFrame);
    QThread::msleep(20);

    sendFrame.data[0] = 0x0A;
    canThreadsend->SendMsg(sendFrame);
    QThread::msleep(20);

    sendFrame.data[0] = 0x0B;
    canThreadsend->SendMsg(sendFrame);
    QThread::msleep(20);

    sendFrame.data[0] = 0x0C;
    canThreadsend->SendMsg(sendFrame);

    if(timer1->isActive() != true)
        timer1->start(1000);
}
//读取AC
void SysSettingWindow::on_pushButton_118_clicked()
{
    canFrame sendFrame;
    sendFrame.data[0] = 0x0B;
    sendFrame.data[1] = 0;
    sendFrame.data[2] = 0;
    sendFrame.data[3] = 0;
    sendFrame.data[4] = 0;
    sendFrame.data[5] = 0;
    sendFrame.data[6] = 0;
    sendFrame.data[7] = 0;
    sendFrame.dataLen = 8;
    sendFrame.canID = 0x0800A0CC ;
    canThreadsend->SendMsg(sendFrame);
    QThread::msleep(20);

    sendFrame.data[0] = 0x0C;
    canThreadsend->SendMsg(sendFrame);
    QThread::msleep(20);

    sendFrame.data[0] = 0x0D;
    canThreadsend->SendMsg(sendFrame);
    QThread::msleep(20);

    sendFrame.data[0] = 0x0E;
    canThreadsend->SendMsg(sendFrame);
    QThread::msleep(20);

    sendFrame.data[0] = 0x0F;
    canThreadsend->SendMsg(sendFrame);

    if(timer1->isActive() != true)
        timer1->start(1000);
}

/***************************************************************校准参数******************************************/
/***************************************************************校准参数******************************************/
/***************************************************************校准参数******************************************/
/*******************DC1*****************************/
/*******************DC1*****************************/
/*******************DC1*****************************/


/*******************DC2*****************************/
/*******************DC2*****************************/
/*******************DC2*****************************/


/*******************AC*****************************/
/*******************AC*****************************/
/*******************AC*****************************/


//读取系统参数
void SysSettingWindow::on_pushButton_140_clicked()
{
    canFrame sendFrame;
    sendFrame.data[0] = 0x01;
    sendFrame.data[1] = 0;
    sendFrame.data[2] = 0;
    sendFrame.data[3] = 0;
    sendFrame.data[4] = 0;
    sendFrame.data[5] = 0;
    sendFrame.data[6] = 0;
    sendFrame.data[7] = 0;
    sendFrame.dataLen = 8;
    sendFrame.canID = 0x080020CC ;
    canThreadsend->SendMsg(sendFrame);
    QThread::msleep(20);

    sendFrame.data[0] = 0x02;
    canThreadsend->SendMsg(sendFrame);

    if(timer1->isActive() != true)
        timer1->start(1000);
}

void SysSettingWindow::on_pushButton_147_clicked()
{
    canFrame sendFrame;
    sendFrame.data[0] = 0x01;
    sendFrame.data[1] = 0;
    sendFrame.data[2] = 0;
    sendFrame.data[3] = 0;
    sendFrame.data[4] = 0;
    sendFrame.data[5] = 0;
    sendFrame.data[6] = 0;
    sendFrame.data[7] = 0;
    sendFrame.dataLen = 8;
    sendFrame.canID = 0x080021CC ;
    canThreadsend->SendMsg(sendFrame);
    QThread::msleep(20);

    sendFrame.data[0] = 0x02;
    canThreadsend->SendMsg(sendFrame);

    if(timer1->isActive() != true)
        timer1->start(1000);
}

void SysSettingWindow::on_pushButton_154_clicked()
{
    canFrame sendFrame;
    sendFrame.data[0] = 0x01;
    sendFrame.data[1] = 0;
    sendFrame.data[2] = 0;
    sendFrame.data[3] = 0;
    sendFrame.data[4] = 0;
    sendFrame.data[5] = 0;
    sendFrame.data[6] = 0;
    sendFrame.data[7] = 0;
    sendFrame.dataLen = 8;
    sendFrame.canID = 0x0800A0CC ;
    canThreadsend->SendMsg(sendFrame);

    if(timer1->isActive() != true)
        timer1->start(1000);
}

//出厂日期设置
void SysSettingWindow::on_calendarWidget_selectionChanged()
{
    S_SystemSetDC1.dataproduct.year = ui->calendarWidget->selectedDate().year();
    S_SystemSetDC1.dataproduct.month = ui->calendarWidget->selectedDate().month();
    S_SystemSetDC1.dataproduct.day = ui->calendarWidget->selectedDate().day();

    S_SystemSetDC2.dataproduct.year = ui->calendarWidget->selectedDate().year();
    S_SystemSetDC2.dataproduct.month = ui->calendarWidget->selectedDate().month();
    S_SystemSetDC2.dataproduct.day = ui->calendarWidget->selectedDate().day();

    S_SysSetAC.dataproduct.year = ui->calendarWidget->selectedDate().year();
    S_SysSetAC.dataproduct.month = ui->calendarWidget->selectedDate().month();
    S_SysSetAC.dataproduct.day = ui->calendarWidget->selectedDate().day();
}

//下发出厂日期
void SysSettingWindow::on_pushButton_152_clicked()
{
    canFrame sendFrame;
    sendFrame.data[0] = 0x01;
    sendFrame.data[1] = (S_SystemSetDC1.dataproduct.year >> 0) & 0x00FF;
    sendFrame.data[2] = (S_SystemSetDC1.dataproduct.year >> 8) & 0x00FF;
    sendFrame.data[3] = S_SystemSetDC1.dataproduct.month;
    sendFrame.data[4] = S_SystemSetDC1.dataproduct.day;
    sendFrame.data[5] = 0;
    sendFrame.data[6] = 0;
    sendFrame.data[7] = 0;
    sendFrame.dataLen = 8;
    sendFrame.canID = 0x040020CC ;
    canThreadsend->SendMsg(sendFrame);

    sendFrame.data[0] = 0x01;
    sendFrame.data[1] = (S_SystemSetDC2.dataproduct.year >> 0) & 0x00FF;
    sendFrame.data[2] = (S_SystemSetDC2.dataproduct.year >> 8) & 0x00FF;
    sendFrame.data[3] = S_SystemSetDC2.dataproduct.month;
    sendFrame.data[4] = S_SystemSetDC2.dataproduct.day;
    sendFrame.canID = 0x040021CC ;
    canThreadsend->SendMsg(sendFrame);

    sendFrame.data[0] = 0x01;
    sendFrame.data[1] = (S_SysSetAC.dataproduct.year >> 0) & 0x00FF;
    sendFrame.data[2] = (S_SysSetAC.dataproduct.year >> 8) & 0x00FF;
    sendFrame.data[3] = S_SysSetAC.dataproduct.month;
    sendFrame.data[4] = S_SysSetAC.dataproduct.day;;
    sendFrame.canID = 0x0400A0CC ;
    canThreadsend->SendMsg(sendFrame);
}

/***************************************************************运动控制参数******************************************/
/***************************************************************运动控制参数******************************************/
/***************************************************************运动控制参数******************************************/
/*******************DC1*****************************/
/*******************DC1*****************************/
/*******************DC1*****************************/

void SysSettingWindow::on_lineEdit_136_textChanged(const QString &arg1)
{
    S_MotionConDC1.resume = arg1.toInt();
}

void SysSettingWindow::on_pushButton_158_clicked()
{
    canFrame sendFrame;
    sendFrame.data[0] = 0x0E;
    sendFrame.data[1] = S_MotionConDC1.resume;
    sendFrame.data[2] = S_MotionConDC1.mastandby;
    sendFrame.data[3] = 0;
    sendFrame.data[4] = 0;
    sendFrame.data[5] = 0;
    sendFrame.data[6] = 0;
    sendFrame.data[7] = 0;
    sendFrame.dataLen = 8;
    sendFrame.canID = 0x040020CC ;
    canThreadsend->SendMsg(sendFrame);
}

void SysSettingWindow::on_lineEdit_122_textChanged(const QString &arg1)
{
    S_MotionConDC1.mastandby = arg1.toInt();
}

void SysSettingWindow::on_pushButton_160_clicked()
{
    canFrame sendFrame;
    sendFrame.data[0] = 0x0E;
    sendFrame.data[1] = S_MotionConDC1.resume;
    sendFrame.data[2] = S_MotionConDC1.mastandby;
    sendFrame.data[3] = 0;
    sendFrame.data[4] = 0;
    sendFrame.data[5] = 0;
    sendFrame.data[6] = 0;
    sendFrame.data[7] = 0;
    sendFrame.dataLen = 8;
    sendFrame.canID = 0x040020CC ;
    canThreadsend->SendMsg(sendFrame);
}

/*******************DC2*****************************/
/*******************DC2*****************************/
/*******************DC2*****************************/

void SysSettingWindow::on_lineEdit_141_textChanged(const QString &arg1)
{
    S_MotionConDC2.resume = arg1.toInt();
}

void SysSettingWindow::on_pushButton_163_clicked()
{
    canFrame sendFrame;
    sendFrame.data[0] = 0x0E;
    sendFrame.data[1] = S_MotionConDC2.resume;
    sendFrame.data[2] = S_MotionConDC2.mastandby;
    sendFrame.data[3] = 0;
    sendFrame.data[4] = 0;
    sendFrame.data[5] = 0;
    sendFrame.data[6] = 0;
    sendFrame.data[7] = 0;
    sendFrame.dataLen = 8;
    sendFrame.canID = 0x040021CC ;
    canThreadsend->SendMsg(sendFrame);
}

void SysSettingWindow::on_lineEdit_138_textChanged(const QString &arg1)
{
     S_MotionConDC2.mastandby = arg1.toInt();
}

void SysSettingWindow::on_pushButton_165_clicked()
{
    canFrame sendFrame;
    sendFrame.data[0] = 0x0E;
    sendFrame.data[1] = S_MotionConDC2.resume;
    sendFrame.data[2] = S_MotionConDC2.mastandby;
    sendFrame.data[3] = 0;
    sendFrame.data[4] = 0;
    sendFrame.data[5] = 0;
    sendFrame.data[6] = 0;
    sendFrame.data[7] = 0;
    sendFrame.dataLen = 8;
    sendFrame.canID = 0x040021CC ;
    canThreadsend->SendMsg(sendFrame);
}

/*******************AC*****************************/
/*******************AC*****************************/
/*******************AC*****************************/

void SysSettingWindow::on_lineEdit_143_textChanged(const QString &arg1)
{
   S_MotionConAc.resume =  arg1.toInt();
}

void SysSettingWindow::on_pushButton_168_clicked()
{
    sendcmd(0x0400A0CC,0x11,MONTPARA,2);
}

void SysSettingWindow::on_lineEdit_144_textChanged(const QString &arg1)
{
    S_MotionConAc.dcmodesel =  arg1.toInt();
}

void SysSettingWindow::on_pushButton_169_clicked()
{
     sendcmd(0x0400A0CC,0x11,MONTPARA,2);
}

void SysSettingWindow::on_lineEdit_145_textChanged(const QString &arg1)
{
    S_MotionConAc.mastandby = arg1.toInt();
}

void SysSettingWindow::on_pushButton_170_clicked()
{
     sendcmd(0x0400A0CC,0x11,MONTPARA,2);
}

void SysSettingWindow::on_lineEdit_146_textChanged(const QString &arg1)
{
    S_MotionConAc.modulation = (S_MotionConAc.modulation & 0xFE ) | (arg1.toInt() << 0);
}

void SysSettingWindow::on_pushButton_171_clicked()
{
     sendcmd(0x0400A0CC,0x11,MONTPARA,2);
}

void SysSettingWindow::on_lineEdit_147_textChanged(const QString &arg1)
{
    S_MotionConAc.modulation = (S_MotionConAc.modulation & 0xFD ) | (arg1.toInt() << 1);
}

void SysSettingWindow::on_pushButton_172_clicked()
{
     sendcmd(0x0400A0CC,0x11,MONTPARA,2);
}

void SysSettingWindow::on_lineEdit_148_textChanged(const QString &arg1)
{
    S_MotionConAc.modulation = (S_MotionConAc.modulation & 0xFB ) | (arg1.toInt() << 2);
}

void SysSettingWindow::on_pushButton_173_clicked()
{
     sendcmd(0x0400A0CC,0x11,MONTPARA,2);
}

void SysSettingWindow::on_lineEdit_149_textChanged(const QString &arg1)
{
    S_MotionConAc.modulation = (S_MotionConAc.modulation & 0xF7 ) | (arg1.toInt() << 3);
}

void SysSettingWindow::on_pushButton_174_clicked()
{
    sendcmd(0x0400A0CC,0x11,MONTPARA,2);
}

void SysSettingWindow::on_lineEdit_150_textChanged(const QString &arg1)
{
     S_MotionConAc.modulation = (S_MotionConAc.modulation & 0xEF ) | (arg1.toInt() << 4);
}

void SysSettingWindow::on_pushButton_175_clicked()
{
     sendcmd(0x0400A0CC,0x11,MONTPARA,2);
}

void SysSettingWindow::on_lineEdit_151_textChanged(const QString &arg1)
{
     S_MotionConAc.modulation = (S_MotionConAc.modulation & 0xDF ) | (arg1.toInt() << 5);
}

void SysSettingWindow::on_pushButton_176_clicked()
{
    sendcmd(0x0400A0CC,0x11,MONTPARA,2);
}

//读取运动控制参数

void SysSettingWindow::on_pushButton_145_clicked()
{
    canFrame sendFrame;
    sendFrame.data[0] = 0x0E;
    sendFrame.data[1] = 0;
    sendFrame.data[2] = 0;
    sendFrame.data[3] = 0;
    sendFrame.data[4] = 0;
    sendFrame.data[5] = 0;
    sendFrame.data[6] = 0;
    sendFrame.data[7] = 0;
    sendFrame.dataLen = 8;
    sendFrame.canID = 0x080020CC ;
    canThreadsend->SendMsg(sendFrame);

    if(timer1->isActive() != true)
        timer1->start(1000);
}

void SysSettingWindow::on_pushButton_162_clicked()
{
    canFrame sendFrame;
    sendFrame.data[0] = 0x0E;
    sendFrame.data[1] = 0;
    sendFrame.data[2] = 0;
    sendFrame.data[3] = 0;
    sendFrame.data[4] = 0;
    sendFrame.data[5] = 0;
    sendFrame.data[6] = 0;
    sendFrame.data[7] = 0;
    sendFrame.dataLen = 8;
    sendFrame.canID = 0x080021CC ;
    canThreadsend->SendMsg(sendFrame);

    if(timer1->isActive() != true)
        timer1->start(1000);
}

void SysSettingWindow::on_pushButton_167_clicked()
{
    canFrame sendFrame;
    sendFrame.data[0] = 0x11;
    sendFrame.data[1] = 0;
    sendFrame.data[2] = 0;
    sendFrame.data[3] = 0;
    sendFrame.data[4] = 0;
    sendFrame.data[5] = 0;
    sendFrame.data[6] = 0;
    sendFrame.data[7] = 0;
    sendFrame.dataLen = 8;
    sendFrame.canID = 0x0800A0CC ;
    canThreadsend->SendMsg(sendFrame);

    if(timer1->isActive() != true)
        timer1->start(1000);
}

//详细数据
void SysSettingWindow::on_pushButton_159_clicked()
{
    //主界面申请内存
    MainWindow * mainwin = MainWindow::getInstance();
    this->close();
    mainwin->show();
}

/***************************************************************调试参数******************************************/
/***************************************************************调试参数******************************************/
/***************************************************************调试参数******************************************/
//调试模式数据发送函数
void SysSettingWindow::senddata(long canid, uint8_t commmand,int byte0,uint8_t byte1)
{
    canFrame sendFrame;
    sendFrame.data[0] = commmand;
    sendFrame.data[1] = byte0;
    sendFrame.data[2] = byte1;
    sendFrame.data[3] = 0;
    sendFrame.data[4] = 0;
    sendFrame.data[5] = 0;
    sendFrame.data[6] = 0;
    sendFrame.data[7] = 0;

   // sendFrame.data[bytenum] = value;

    sendFrame.canID = canid;
    sendFrame.dataLen = 8;
    canThreadsend->SendMsg(sendFrame);
}

/*******************DC1*****************************/
/*******************DC1*****************************/
/*******************DC1*****************************/
//调试模式设定
//正极主接触器KM1/KM3控制
void SysSettingWindow::on_btnKM13ON_clicked()
{
    status_byte0 = ((status_byte0 & 0xFE) | ON);
    senddata(0x040020CC,0x0D,status_byte0,status_byte1);
}

void SysSettingWindow::on_btnKM13OFF_clicked()
{
    status_byte0 = ((status_byte0 & 0xFE) | OFF);
    senddata(0x040020CC,0x0D,status_byte0,status_byte1);
}

//负极主接触器KM2/KM4控制
void SysSettingWindow::on_btnKM24ON_clicked()
{
    status_byte0 = ((status_byte0 & 0xFD) | (ON << 1));
    senddata(0x040020CC,0x0D,status_byte0,status_byte1);
}

void SysSettingWindow::on_btnKM13OFF_2_clicked()
{
    status_byte0 = ((status_byte0 & 0xFD) | (OFF << 1));
    senddata(0x040020CC,0x0D,status_byte0,status_byte1);
}

//分档电流接触器KM9/KM10控制
void SysSettingWindow::on_btnKM910ON_clicked()
{
    status_byte0 = ((status_byte0 & 0xFB) | (ON << 2));
    senddata(0x040020CC,0x0D,status_byte0,status_byte1);
}

void SysSettingWindow::on_btnKM910OFF_clicked()
{
    status_byte0 = ((status_byte0 & 0xFB) | (OFF << 2));
    senddata(0x040020CC,0x0D,status_byte0,status_byte1);
}

//直流模块风机控制
void SysSettingWindow::on_btnKM910ON_2_clicked()
{
    status_byte0 = ((status_byte0 & 0xF7) | (ON << 3));
    senddata(0x040020CC,0x0D,status_byte0,status_byte1);
}

void SysSettingWindow::on_btnKM910OFF_2_clicked()
{
    status_byte0 = ((status_byte0 & 0xF7) | (OFF << 3));
    senddata(0x040020CC,0x0D,status_byte0,status_byte1);
}

//通道故障输出到BMS控制
void SysSettingWindow::on_btnKM910ON_3_clicked()
{
    status_byte0 = ((status_byte0 & 0xEF) | (ON << 4));
    senddata(0x040020CC,0x0D,status_byte0,status_byte1);
}

void SysSettingWindow::on_btnKM910OFF_3_clicked()
{
    status_byte0 = ((status_byte0 & 0xEF) | (OFF << 4));
    senddata(0x040020CC,0x0D,status_byte0,status_byte1);
}

//PMW测试指令控制
void SysSettingWindow::on_btnPMWON_3_clicked()
{
    status_byte0 = ((status_byte0 & 0xDF) | (ON << 5));
    senddata(0x040020CC,0x0D,status_byte0,status_byte1);
}

void SysSettingWindow::on_btnPMWOFF_3_clicked()
{
    status_byte0 = ((status_byte0 & 0xDF) | (OFF << 5));
    senddata(0x040020CC,0x0D,status_byte0,status_byte1);
}

//直流故障信号
void SysSettingWindow::on_btnPMWON_clicked()
{
    status_byte0 = ((status_byte0 & 0xBF) | (ON << 6));
    senddata(0x040020CC,0x0D,status_byte0,status_byte1);
}

void SysSettingWindow::on_btnPMWOFF_clicked()
{
    status_byte0 = ((status_byte0 & 0xBF) | (OFF << 6));
    senddata(0x040020CC,0x0D,status_byte0,status_byte1);
}

//直流故障报警指示灯控制
void SysSettingWindow::on_btnPMWON_2_clicked()
{
    status_byte0 = ((status_byte0 & 0x7F) | (ON << 7));
    senddata(0x040020CC,0x0D,status_byte0,status_byte1);
}

void SysSettingWindow::on_btnPMWOFF_2_clicked()
{
    status_byte0 = ((status_byte0 & 0x7F) | (OFF << 7));
    senddata(0x040020CC,0x0D,status_byte0,status_byte1);
}

//直流运行指示灯控制
void SysSettingWindow::on_btnKA34ON_clicked()
{
    status_byte1 = ((status_byte1 & 0xFE) | ON);
    senddata(0x040020CC,0x0D,status_byte0,status_byte1);
}

void SysSettingWindow::on_btnKA34OFF_clicked()
{
    status_byte1 = ((status_byte1 & 0xFE) | OFF);
    senddata(0x040020CC,0x0D,status_byte0,status_byte1);
}

//直流待机指示灯控制
void SysSettingWindow::on_btnPMWON_4_clicked()
{
    status_byte1 = ((status_byte1 & 0xFD) | (ON << 1));
    senddata(0x040020CC,0x0D,status_byte0,status_byte1);
}

void SysSettingWindow::on_btnPMWOFF_4_clicked()
{
    status_byte1 = ((status_byte1 & 0xFD) | (OFF << 1));
    senddata(0x040020CC,0x0D,status_byte0,status_byte1);
}

/*******************DC2*****************************/
/*******************DC2*****************************/
/*******************DC2*****************************/
//正极主接触器KM1/KM3控制
void SysSettingWindow::on_btnKM13ON_2_clicked()
{
    status_byte0_dc2 = ((status_byte0_dc2 & 0xFE) | ON);
    senddata(0x040021CC,0x0D,status_byte0_dc2,status_byte1_dc2);
}

void SysSettingWindow::on_btnKM13OFF_4_clicked()
{
    status_byte0_dc2 = ((status_byte0_dc2 & 0xFE) | OFF);
    senddata(0x040021CC,0x0D,status_byte0_dc2,status_byte1_dc2);
}

//负极主接触器KM2/KM4控制
void SysSettingWindow::on_btnKM24ON_2_clicked()
{
    status_byte0_dc2 = ((status_byte0_dc2 & 0xFD) | (ON << 1));
    senddata(0x040021CC,0x0D,status_byte0_dc2,status_byte1_dc2);
}

void SysSettingWindow::on_btnKM13OFF_3_clicked()
{
    status_byte0_dc2 = ((status_byte0_dc2 & 0xFD) | (OFF << 1));
    senddata(0x040021CC,0x0D,status_byte0_dc2,status_byte1_dc2);
}

//分档电流接触器KM9/KM10控制
void SysSettingWindow::on_btnKM910ON_6_clicked()
{
    status_byte0_dc2 = ((status_byte0_dc2 & 0xFB) | (ON << 2));
    senddata(0x040021CC,0x0D,status_byte0_dc2,status_byte1_dc2);
}

void SysSettingWindow::on_btnKM910OFF_6_clicked()
{
    status_byte0_dc2 = ((status_byte0_dc2 & 0xFB) | (OFF << 2));
    senddata(0x040021CC,0x0D,status_byte0_dc2,status_byte1_dc2);
}

//直流模块风机控制
void SysSettingWindow::on_btnKM910ON_4_clicked()
{
    status_byte0_dc2 = ((status_byte0_dc2 & 0xF7) | (ON << 3));
    senddata(0x040021CC,0x0D,status_byte0_dc2,status_byte1_dc2);
}

void SysSettingWindow::on_btnKM910OFF_4_clicked()
{
    status_byte0_dc2 = ((status_byte0_dc2 & 0xF7) | (OFF << 3));
    senddata(0x040021CC,0x0D,status_byte0_dc2,status_byte1_dc2);
}

//通道故障输出到BMS控制
void SysSettingWindow::on_btnKM910ON_5_clicked()
{
    status_byte0_dc2 = ((status_byte0_dc2 & 0xEF) | (ON << 4));
    senddata(0x040021CC,0x0D,status_byte0_dc2,status_byte1_dc2);
}

void SysSettingWindow::on_btnKM910OFF_5_clicked()
{
    status_byte0_dc2 = ((status_byte0_dc2 & 0xEF) | (OFF << 4));
    senddata(0x040021CC,0x0D,status_byte0_dc2,status_byte1_dc2);
}

//PMW测试指令控制
void SysSettingWindow::on_btnPMWON_6_clicked()
{
    status_byte0_dc2 = ((status_byte0_dc2 & 0xDF) | (ON << 5));
    senddata(0x040021CC,0x0D,status_byte0_dc2,status_byte1_dc2);
}

void SysSettingWindow::on_btnPMWOFF_6_clicked()
{
    status_byte0_dc2 = ((status_byte0_dc2 & 0xDF) | (OFF << 5));
    senddata(0x040021CC,0x0D,status_byte0_dc2,status_byte1_dc2);
}

//直流故障信号
void SysSettingWindow::on_btnPMWON_7_clicked()
{
    status_byte0_dc2 = ((status_byte0_dc2 & 0xBF) | (ON << 6));
    senddata(0x040021CC,0x0D,status_byte0_dc2,status_byte1_dc2);
}

void SysSettingWindow::on_btnPMWOFF_7_clicked()
{
    status_byte0_dc2 = ((status_byte0_dc2 & 0xBF) | (OFF << 6));
    senddata(0x040021CC,0x0D,status_byte0_dc2,status_byte1_dc2);
}

//直流故障报警指示灯控制
void SysSettingWindow::on_btnPMWON_5_clicked()
{
    status_byte0_dc2 = ((status_byte0_dc2 & 0x7F) | (ON << 7));
    senddata(0x040021CC,0x0D,status_byte0_dc2,status_byte1_dc2);
}

void SysSettingWindow::on_btnPMWOFF_5_clicked()
{
    status_byte0_dc2 = ((status_byte0_dc2 & 0x7F) | (OFF << 7));
    senddata(0x040021CC,0x0D,status_byte0_dc2,status_byte1_dc2);
}

//直流运行指示灯控制
void SysSettingWindow::on_btnKA34ON_2_clicked()
{
    status_byte1_dc2 = ((status_byte1_dc2 & 0xFE) | (ON << 0));
    senddata(0x040021CC,0x0D,status_byte0_dc2,status_byte1_dc2);
}

void SysSettingWindow::on_btnKA34OFF_2_clicked()
{
    status_byte1_dc2 = ((status_byte1_dc2 & 0xFE) | (OFF << 0));
    senddata(0x040021CC,0x0D,status_byte0_dc2,status_byte1_dc2);
}

//直流待机指示灯控制
void SysSettingWindow::on_btnPMWON_8_clicked()
{
    status_byte1_dc2 = ((status_byte1_dc2 & 0xFD) | (ON << 1));
    senddata(0x040021CC,0x0D,status_byte0_dc2,status_byte1_dc2);
}

void SysSettingWindow::on_btnPMWOFF_8_clicked()
{
    status_byte1_dc2 = ((status_byte1_dc2 & 0xFD) | (OFF << 1));
    senddata(0x040021CC,0x0D,status_byte0_dc2,status_byte1_dc2);
}

/*******************AC*****************************/
/*******************AC*****************************/
/*******************AC*****************************/
//交流主接触器KM6控制
void SysSettingWindow::on_btnKM13ON_4_clicked()
{
    status_byte0_ac = ((status_byte0_ac & 0xFE) | (ON << 0));
    senddata(0x0400A0CC,0x10,status_byte0_ac,status_byte1_ac);
}

void SysSettingWindow::on_btnKM13OFF_7_clicked()
{
    status_byte0_ac = ((status_byte0_ac & 0xFE) | (OFF << 0));
    senddata(0x0400A0CC,0x10,status_byte0_ac,status_byte1_ac);
}

//交流充电接触器KM7控制
void SysSettingWindow::on_btnKM24ON_4_clicked()
{
    status_byte0_ac = ((status_byte0_ac & 0xFD) | (ON << 1));
    senddata(0x0400A0CC,0x10,status_byte0_ac,status_byte1_ac);
}

void SysSettingWindow::on_btnKM13OFF_8_clicked()
{
    status_byte0_ac = ((status_byte0_ac & 0xFD) | (OFF << 1));
    senddata(0x0400A0CC,0x10,status_byte0_ac,status_byte1_ac);
}

//母线放电接触器KM5控制
void SysSettingWindow::on_btnKM910ON_11_clicked()
{
    status_byte0_ac = ((status_byte0_ac & 0xFB) | (ON << 2));
    senddata(0x0400A0CC,0x10,status_byte0_ac,status_byte1_ac);
}

void SysSettingWindow::on_btnKM910OFF_11_clicked()
{
    status_byte0_ac = ((status_byte0_ac & 0xFB) | (OFF << 2));
    senddata(0x0400A0CC,0x10,status_byte0_ac,status_byte1_ac);
}

//交流模块风机控制
void SysSettingWindow::on_btnKM910ON_10_clicked()
{
    status_byte0_ac = ((status_byte0_ac & 0xF7) | (ON << 3));
    senddata(0x0400A0CC,0x10,status_byte0_ac,status_byte1_ac);
}

void SysSettingWindow::on_btnKM910OFF_10_clicked()
{
    status_byte0_ac = ((status_byte0_ac & 0xF7) | (OFF << 3));
    senddata(0x0400A0CC,0x10,status_byte0_ac,status_byte1_ac);
}

//机柜风机控制
void SysSettingWindow::on_btnPMWON_15_clicked()
{
    status_byte0_ac = ((status_byte0_ac & 0xEF) | (ON << 4));
    senddata(0x0400A0CC,0x10,status_byte0_ac,status_byte1_ac);
}

void SysSettingWindow::on_btnPMWOFF_15_clicked()
{
    status_byte0_ac = ((status_byte0_ac & 0xEF) | (OFF << 4));
    senddata(0x0400A0CC,0x10,status_byte0_ac,status_byte1_ac);
}

//运行指示灯控制
void SysSettingWindow::on_btnPMWON_13_clicked()
{
    status_byte0_ac = ((status_byte0_ac & 0xDF) | (ON << 5));
    senddata(0x0400A0CC,0x10,status_byte0_ac,status_byte1_ac);
}

void SysSettingWindow::on_btnPMWOFF_13_clicked()
{
    status_byte0_ac = ((status_byte0_ac & 0xDF) | (OFF << 5));
    senddata(0x0400A0CC,0x10,status_byte0_ac,status_byte1_ac);
}

//故障指示灯控制
void SysSettingWindow::on_btnKA34ON_5_clicked()
{
    status_byte0_ac = ((status_byte0_ac & 0xBF) | (ON << 6));
    senddata(0x0400A0CC,0x10,status_byte0_ac,status_byte1_ac);
}
void SysSettingWindow::on_btnKA34OFF_5_clicked()
{
    status_byte0_ac = ((status_byte0_ac & 0xBF) | (OFF << 6));
    senddata(0x0400A0CC,0x10,status_byte0_ac,status_byte1_ac);
}

//PMW测试指令控制
void SysSettingWindow::on_btnPMWON_14_clicked()
{
    status_byte0_ac = ((status_byte0_ac & 0x7F) | (ON << 7));
    senddata(0x0400A0CC,0x10,status_byte0_ac,status_byte1_ac);
}

void SysSettingWindow::on_btnPMWOFF_14_clicked()
{
    status_byte0_ac = ((status_byte0_ac & 0x7F) | (OFF << 7));
    senddata(0x0400A0CC,0x10,status_byte0_ac,status_byte1_ac);
}

//交流故障输出控制
void SysSettingWindow::on_btnKA34ON_4_clicked()
{
    status_byte1_ac = ((status_byte1_ac & 0xFE) | (ON << 0));
    senddata(0x0400A0CC,0x10,status_byte0_ac,status_byte1_ac);
}

void SysSettingWindow::on_btnKA34OFF_4_clicked()
{
    status_byte1_ac = ((status_byte1_ac & 0xFE) | (OFF << 0));
    senddata(0x0400A0CC,0x10,status_byte0_ac,status_byte1_ac);
}

//告警信息界面
void SysSettingWindow::on_pushButton_161_clicked()
{
    ErrorWindow * errwin = ErrorWindow::getInstance();
    this->close();
    //errwin->InitTable();
    errwin->show();
}


