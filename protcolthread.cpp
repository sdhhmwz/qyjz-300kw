#include "protcolthread.h"
#include "GlobalData.h"

ProtcolThread::ProtcolThread()
{
    Initial();
}

//初始化
void ProtcolThread:: Initial()
{
    memset(&this->recvFrame, 0, sizeof(canFrame));
    //保证run函数循环执行
    stopped = false;
    //未收到新数据
    newData = false;

}

//接入线程
void ProtcolThread::run()
{
    while(!stopped)
    {
        //每执行一次 挂起5ms
//        QThread::msleep(5);
        if(newData)
        {

          //==============================DC1==================================

            test_pro = recvFrame.canID&0x7fffffff;
            QString test = QString::number(recvFrame.canID&0x7fffffff,16);

           if(test == "800cc20" )
            {
                DataAnalysis_DC1(recvFrame);
                newData = false;
                continue;
            }

          //==============================DC2==================================

           if(test == "800cc21" )
            {
               DataAnalysis_DC2(recvFrame);
                newData = false;
                continue;
            }

           //==============================AC==================================

           // 后面分开  状态和返回的一些报文   如果判断解析时间长
          if(test == "800cca0"  )
           {
               DataAnalysis_AC(recvFrame);
               newData = false;
               continue;
           }
           newData = false;
        }
    }

}

void ProtcolThread::stop()
{
    stopped = true;

}
void ProtcolThread::restart()
{
    stopped = false;
}

void ProtcolThread::Update(canFrame qData)
{
    if(!newData){

        this->recvFrame = qData;

        newData = true;
    }
}

void ProtcolThread::DataAnalysis_DC1(canFrame qData)
{
    switch (qData.data[0])
    {
        case 13: //0x0d 调试模式设定
            DebugModelDC1.KM1CTRL_KM3CTRL = qData.data[1] & 0x01;
            DebugModelDC1.KM2CTRL_KM4CTRL = (qData.data[1] >> 1) & 0x01;
            DebugModelDC1.KM9CTRL_KM10CTRL = (qData.data[1] >> 2) & 0x01;
            DebugModelDC1.KA3CTRL_KA4CTRL = (qData.data[1] >> 3) & 0x01;
            DebugModelDC1.ERRORTOBMS = (qData.data[1] >> 4) & 0x01;
            DebugModelDC1.PWMTESTCTRL = (qData.data[1] >> 5) & 0x01;
            DebugModelDC1.DCERRORCTRL = (qData.data[1] >> 6) & 0x01;
            DebugModelDC1.LEDERRORCTRL = (qData.data[1] >> 7) & 0x01;
            DebugModelDC1.LEDRUNCTRL = (qData.data[2]) & 0x01;
            DebugModelDC1.LEDSTANDBYCTRL = (qData.data[2]>>1) & 0x01;
           break;
        case 3: //0x03 0x04 控制参数
            ControlParalDC1.POUTLIMIT = qData.data[3] | (qData.data[4] << 8);
            ControlParalDC1.HMIIBATL = qData.data[5];
            ControlParalDC1.DEADTIME = qData.data[6];
            ControlParalDC1.MINONTIME = qData.data[7];
            break;
        case 4:
            ControlParalDC1.DCDC_SWFR = qData.data[1] | (qData.data[2] << 8);
            ControlParalDC1.RU_UDCT = qData.data[3] | (qData.data[4] << 8);
            ControlParalDC1.RU_IDT = qData.data[5] | (qData.data[6] << 8);
            break;
        case 5://0x05 保护参数
            ProtectParaDC1.SC_UDCOV = qData.data[1] | (qData.data[2] << 8);
            ProtectParaDC1.SC_EEREPT = qData.data[3] | (qData.data[4] << 8);
            ProtectParaDC1.SC_RCOVT = qData.data[5] | (qData.data[6] << 8);
            ProtectParaDC1.SC_UBATDV = qData.data[7];
            break;
        case 6://0x06 0x07 PI参数
            pIModelDC1.UbatKP = qData.data[1] | (qData.data[2] << 8);
            pIModelDC1.UbatTI = qData.data[3] | (qData.data[4] << 8);
            break;
        case 7:
            pIModelDC1.IbatKP = qData.data[1] | (qData.data[2] << 8);
            pIModelDC1.IbatTI = qData.data[3] | (qData.data[4] << 8);
            break;
        case 8://0x08 0x09 0x0A 0x0B 0x0C 控制参数
            cALModelDC1.A_UBAT = qData.data[1] | (qData.data[2] << 8);
            cALModelDC1.B_UBAT = qData.data[3] | (qData.data[4] << 8);
            break;
        case 9:
            cALModelDC1.A_I1BAT = qData.data[1] | (qData.data[2] << 8);
            cALModelDC1.B_I1BAT = qData.data[3] | (qData.data[4] << 8);
            break;
        case 10:
            cALModelDC1.A_I2BAT = qData.data[1] | (qData.data[2] << 8);
            cALModelDC1.B_I2BAT = qData.data[3] | (qData.data[4] << 8);
            break;
        case 11:
            cALModelDC1.A_IBAT1 = qData.data[1] | (qData.data[2] << 8);
            cALModelDC1.B_IBAT1 = qData.data[3] | (qData.data[4] << 8);
            break;
        case 12:
            cALModelDC1.A_IBAT2 = qData.data[1] | (qData.data[2] << 8);
            cALModelDC1.B_IBAT2 = qData.data[3] | (qData.data[4] << 8);
            break;
        case 1://系统参数
            S_SystemSetDC1.dataproduct.year  = qData.data[1] | (qData.data[2] << 8);
            S_SystemSetDC1.dataproduct.month = qData.data[3];
            S_SystemSetDC1.dataproduct.day = qData.data[4];
            S_SystemSetDC1.softversion = qData.data[5];
            break;
        case 2:
            S_SystemSetDC1.projectnum = qData.data[1] | (qData.data[2] << 8)| (qData.data[3] << 16)| (qData.data[4] << 24);
            S_SystemSetDC1.serialnum = qData.data[5] | (qData.data[6] << 8);
            S_SystemSetDC1.manufactid = qData.data[7];
            break;
        case 14:
            S_MotionConDC1.resume= qData.data[1];
            S_MotionConDC1.mastandby = qData.data[2];
            break;
        default:
            break;
    }
}

void ProtcolThread::DataAnalysis_DC2(canFrame qData)
{
    switch (qData.data[0])
    {
        case 13: //0x0d 调试模式设定
            DebugModelDC2.KM1CTRL_KM3CTRL = qData.data[1] & 0x01;
            DebugModelDC2.KM2CTRL_KM4CTRL = (qData.data[1] >> 1) & 0x01;
            DebugModelDC2.KM9CTRL_KM10CTRL = (qData.data[1] >> 2) & 0x01;
            DebugModelDC2.KA3CTRL_KA4CTRL = (qData.data[1] >> 3) & 0x01;
            DebugModelDC2.ERRORTOBMS = (qData.data[1] >> 4) & 0x01;
            DebugModelDC2.PWMTESTCTRL = (qData.data[1] >> 5) & 0x01;
            DebugModelDC2.DCERRORCTRL = (qData.data[1] >> 6) & 0x01;
            DebugModelDC2.LEDERRORCTRL = (qData.data[1] >> 7) & 0x01;
            DebugModelDC2.LEDRUNCTRL = (qData.data[2]) & 0x01;
            DebugModelDC2.LEDSTANDBYCTRL = (qData.data[2]>>1) & 0x01;
            break;
        case 3: //0x03 0x04 控制参数
            ControlParalDC2.POUTLIMIT = qData.data[3] | (qData.data[4] << 8);
            ControlParalDC2.HMIIBATL = qData.data[5];
            ControlParalDC2.DEADTIME = qData.data[6];
            ControlParalDC2.MINONTIME = qData.data[7];
            break;
        case 4:
            ControlParalDC2.DCDC_SWFR = qData.data[1] | (qData.data[2] << 8);
            ControlParalDC2.RU_UDCT = qData.data[3] | (qData.data[4] << 8);
            ControlParalDC2.RU_IDT = qData.data[5] | (qData.data[6] << 8);
            break;
        case 5://0x05 保护参数
            ProtectParaDC2.SC_UDCOV = qData.data[1] | (qData.data[2] << 8);
            ProtectParaDC2.SC_EEREPT = qData.data[3] | (qData.data[4] << 8);
            ProtectParaDC2.SC_RCOVT = qData.data[5] | (qData.data[6] << 8);
            ProtectParaDC2.SC_UBATDV = qData.data[7];
            break;
        case 6://0x06 0x07 PI参数
            pIModelDC2.UbatKP = qData.data[1] | (qData.data[2] << 8);
            pIModelDC2.UbatTI = qData.data[3] | (qData.data[4] << 8);
            break;
        case 7:
            pIModelDC2.IbatKP = qData.data[1] | (qData.data[2] << 8);
            pIModelDC2.IbatTI = qData.data[3] | (qData.data[4] << 8);
            break;
        case 8://0x08 0x09 0x0A 0x0B 0x0C
            cALModelDC2.A_UBAT = qData.data[1] | (qData.data[2] << 8);
            cALModelDC2.B_UBAT = qData.data[3] | (qData.data[4] << 8);
            break;
        case 9:
            cALModelDC2.A_I1BAT = qData.data[1] | (qData.data[2] << 8);
            cALModelDC2.B_I1BAT = qData.data[3] | (qData.data[4] << 8);
            break;
        case 10:
            cALModelDC2.A_I2BAT = qData.data[1] | (qData.data[2] << 8);
            cALModelDC2.B_I2BAT = qData.data[3] | (qData.data[4] << 8);
            break;
        case 11:
            cALModelDC2.A_IBAT1 = qData.data[1] | (qData.data[2] << 8);
            cALModelDC2.B_IBAT1 = qData.data[3] | (qData.data[4] << 8);
            break;
        case 12:
            cALModelDC2.A_IBAT2 = qData.data[1] | (qData.data[2] << 8);
            cALModelDC2.B_IBAT2 = qData.data[3] | (qData.data[4] << 8);
            break;
        case 1://系统参数
            S_SystemSetDC2.dataproduct.year  = qData.data[1] | (qData.data[2] << 8);
            S_SystemSetDC2.dataproduct.month = qData.data[3];
            S_SystemSetDC2.dataproduct.day = qData.data[4];
            S_SystemSetDC2.softversion = qData.data[5];
            break;
        case 2:
            S_SystemSetDC2.projectnum = qData.data[1] | (qData.data[2] << 8)| (qData.data[3] << 16)| (qData.data[4] << 24);
            S_SystemSetDC2.serialnum = qData.data[5] | (qData.data[6] << 8);
            S_SystemSetDC2.manufactid = qData.data[7];
            break;
        case 14:
            S_MotionConDC2.resume= qData.data[1];
            S_MotionConDC2.mastandby = qData.data[2];
            break;
        default:
            break;
    }
}

void ProtcolThread::DataAnalysis_AC(canFrame qData)
{
    switch (qData.data[0])
    {
        case 16: //0x0d 调试模式设定
            DebugModelAC0.KM6CTRL = (qData.data[1] >> 0) & 0x01;
            DebugModelAC0.KM7CTRL = (qData.data[1] >> 1) & 0x01;
            DebugModelAC0.KM5CTRL = (qData.data[1] >> 2) & 0x01;
            DebugModelAC0.SFUNCTRL = (qData.data[1] >> 3) & 0x01;
            DebugModelAC0.LFUNRUNCTRL = (qData.data[1] >> 4) & 0x01;
            DebugModelAC0.RUNLEDCTRL = (qData.data[1] >> 5) & 0x01;
            DebugModelAC0.PWMTESTCTRL = (qData.data[1] >> 7) & 0x01;
            DebugModelAC0.ACERRORCTRL = (qData.data[2] >> 0) & 0x01;
            break;
        case 2: //0x02 0x03 控制参数
            ControlParaModelAC.IACLIMIT = qData.data[1];
            ControlParaModelAC.RU_UDCT = qData.data[2] | (qData.data[3] << 8);
            ControlParaModelAC.SW_FR = qData.data[4] | (qData.data[5] << 8);
            ControlParaModelAC.MINONTIME = qData.data[6];
            ControlParaModelAC.DEADTIME = qData.data[7];
            break;
        case 3:
            ControlParaModelAC.COMPTIME1 = qData.data[1];
            ControlParaModelAC.COMPANGLE = qData.data[2];
            ControlParaModelAC.SC_USTEP1 = qData.data[3];
            ControlParaModelAC.SC_ISTEP1 = qData.data[4];
            ControlParaModelAC.UDCH = qData.data[5];
            ControlParaModelAC.RU_IDT = qData.data[6];
            break;
        case 4: //0x04 0x05 0x06保护参数
            ProtectParaAC.SC_UDCOV = qData.data[1] | (qData.data[2] << 8);
            ProtectParaAC.SC_UACOV = qData.data[3] | (qData.data[4] << 8);
            ProtectParaAC.SC_UACLV = qData.data[5] | (qData.data[6] << 8);
            ProtectParaAC.SC_IACOV = qData.data[7];
            break;
        case 5:
            ProtectParaAC.SC_EFFHIG = qData.data[1] | (qData.data[2] << 8);
            ProtectParaAC.SC_EFFLOW = qData.data[3] | (qData.data[4] << 8);
            ProtectParaAC.SC_DETAOMIGA = qData.data[5] | (qData.data[6] << 8);
            ProtectParaAC.SC_IACEQUAL = qData.data[7];
            break;
        case 6:
            ProtectParaAC.SC_FINTRT = qData.data[1] | (qData.data[2] << 8);
            ProtectParaAC.SC_RCOVT = qData.data[3] | (qData.data[4] << 8);
            ProtectParaAC.SC_EEREPT = qData.data[5] | (qData.data[6] << 8);
            ProtectParaAC.SC_IGBTDOWN = qData.data[7];
            break;
        case 7://0x07 0x08 0x09 0x0aPI参数
            pIModelAC.UdcKP = qData.data[1] | (qData.data[2] << 8);
            pIModelAC.UdcTI = qData.data[3] | (qData.data[4] << 8);
            break;
        case 8:
            pIModelAC.PLLKP = qData.data[1] | (qData.data[2] << 8);
            pIModelAC.PLLTI = qData.data[3] | (qData.data[4] << 8);
            break;
        case 9:
            pIModelAC.IdKP = qData.data[1] | (qData.data[2] << 8);
            pIModelAC.IdTI = qData.data[3] | (qData.data[4] << 8);
            break;
        case 10:
            pIModelAC.IqKP = qData.data[1] | (qData.data[2] << 8);
            pIModelAC.IqTI = qData.data[3] | (qData.data[4] << 8);
            break;
        case 11://0x0B 0x0C 0x0D 0x0E 0x0F
            cALModelAC.A_BUSUDC = qData.data[1] | (qData.data[2] << 8);
            cALModelAC.B_BUSUDC = qData.data[3] | (qData.data[4] << 8);
            break;
        case 12://0x0B 0x0C 0x0D 0x0E 0x0F
            cALModelAC.A_UAB = qData.data[1] | (qData.data[2] << 8);
            cALModelAC.B_UAB = qData.data[3] | (qData.data[4] << 8);
            break;
        case 13://0x0B 0x0C 0x0D 0x0E 0x0F
            cALModelAC.A_UAC = qData.data[1] | (qData.data[2] << 8);
            cALModelAC.B_UAC = qData.data[3] | (qData.data[4] << 8);
            break;
        case 14://0x0B 0x0C 0x0D 0x0E 0x0F
            cALModelAC.A_IA = qData.data[1] | (qData.data[2] << 8);
            cALModelAC.B_IA = qData.data[3] | (qData.data[4] << 8);
            break;
        case 15://0x0B 0x0C 0x0D 0x0E 0x0F
            cALModelAC.A_IC = qData.data[1] | (qData.data[2] << 8);
            cALModelAC.B_IC = qData.data[3] | (qData.data[4] << 8);
            break;
        case 1://系统参数
            S_SysSetAC.modelpara = qData.data[1] | (qData.data[2] << 8);
            S_SysSetAC.dataproduct.year  = qData.data[3] | (qData.data[4] << 8);
            S_SysSetAC.dataproduct.month = qData.data[5];
            S_SysSetAC.dataproduct.day = qData.data[6];
            S_SysSetAC.softversion = qData.data[7];
            break;
        case 17://运动控制参数
            S_MotionConAc.resume = qData.data[1];
            S_MotionConAc.dcmodesel = qData.data[2];
            S_MotionConAc.mastandby= qData.data[3];
            S_MotionConAc.modulation = qData.data[4];
            break;
        default:
            break;
    }
}

void ProtcolThread::DataAnalCanID_DC1(canFrame qData)
{
    this->recvFrame = qData;
    switch (recvFrame.canID&0x7fffffff)
    {
        case 0x0002CC20:
            OperMonModelDC1.BA_UBAT = (float)(recvFrame.data[0] | (recvFrame.data[1] << 8)| (recvFrame.data[2] << 16)| (recvFrame.data[3] << 24))/1000;
            OperMonModelDC1.BA_IBAT = (float)(recvFrame.data[4] | (recvFrame.data[5] << 8)| (recvFrame.data[6] << 16)| (recvFrame.data[7] << 24))/1000;
            break;
        case 0x0003cc20:
            OperMonModelDC1.BA_PIN = (float)(recvFrame.data[0] | (recvFrame.data[1] << 8)| (recvFrame.data[2] << 16)| (recvFrame.data[3] << 24))/1000;
            OperMonModelDC1.BA_T1_BA_T3 = (float)(recvFrame.data[4] | (recvFrame.data[5] << 8))/10;
            OperMonModelDC1.BA_T2_BA_T4 = (float)(recvFrame.data[6] | (recvFrame.data[7] << 8))/10;
            break;
        case 0x0004CC20:
            OperMonModelDC1.BA_CHWH = (float)(recvFrame.data[0] | (recvFrame.data[1] << 8)| (recvFrame.data[2] << 16)| (recvFrame.data[3] << 24))/1000;
            OperMonModelDC1.BA_DISWH = (float)(recvFrame.data[4] | (recvFrame.data[5] << 8)| (recvFrame.data[6] << 16)| (recvFrame.data[7] << 24))/1000;
            break;
        case 0x0005CC20:
            OperMonModelDC1.BA_I1_BA_I3 = (float)(recvFrame.data[0] | (recvFrame.data[1] << 8)| (recvFrame.data[2] << 16)| (recvFrame.data[3] << 24))/1000;
            OperMonModelDC1.BA_I2_BA_I4 = (float)(recvFrame.data[4] | (recvFrame.data[5] << 8)| (recvFrame.data[6] << 16)| (recvFrame.data[7] << 24))/1000;
            break;
        case 0x0006CC20:
            OperMonModelDC1.BA_CHAH = (float)(recvFrame.data[0] | (recvFrame.data[1] << 8)| (recvFrame.data[2] << 16)| (recvFrame.data[3] << 24))/1000;
            OperMonModelDC1.BA_DISAH = (float)(recvFrame.data[4] | (recvFrame.data[5] << 8)| (recvFrame.data[6] << 16)| (recvFrame.data[7] << 24))/1000;
            break;

        case 0x0001CC20:
            S_WorkStatusDC1.DOMODE = WorkStatusDC_DOMODE[recvFrame.data[0]];

            if(0xFF == recvFrame.data[1])
            {
                S_WorkStatusDC1.RUNNING = WorkStatusACDC_RUNNING[4];
            }
            else
            {
                S_WorkStatusDC1.RUNNING = WorkStatusDC_RUNNING[recvFrame.data[1]];
            }

            S_WorkStatusDC1.STOP_CASE = WorkStatusDC_STOP_CASE[recvFrame.data[2]];
            S_WorkStatusDC1.CHANNELMODE = WorkStatusDC_CHANNELMODE[recvFrame.data[3]];
            S_WorkStatusDC1.KA5FB = WorkStatusACDC[(recvFrame.data[7] >> 0) & 0x01];
            S_WorkStatusDC1.BMSFB = WorkStatusACDC[(recvFrame.data[7] >> 1) & 0x01];
            S_WorkStatusDC1.L1OTFB = WorkStatusACDC[(recvFrame.data[7] >> 2) & 0x01];
            S_WorkStatusDC1.L2OTFB = WorkStatusACDC[(recvFrame.data[7] >> 3) & 0x01];
            S_WorkStatusDC1.ACERRORFB = WorkStatusDC_ACERRORFB[(recvFrame.data[7] >> 4) & 0x01];
            break;
        case 0x000BCC20:
            OperMonModelDC1.BA_UBAT_IN = (float)(recvFrame.data[0] | (recvFrame.data[1] << 8))/10;
            OperMonModelDC1.BA_UDC = (float)(recvFrame.data[2] | (recvFrame.data[3] << 8))/10;
        break;

        default:
            break;
    }
}

void ProtcolThread::DataAnalCanID_DC2(canFrame qData)
{
    this->recvFrame = qData;
    switch (recvFrame.canID&0x7fffffff)
    {
    case 0x0002CC21:
        OperMonModelDC2.BA_UBAT = (float)(recvFrame.data[0] | (recvFrame.data[1] << 8)| (recvFrame.data[2] << 16)| (recvFrame.data[3] << 24))/1000;
        OperMonModelDC2.BA_IBAT = (float)(recvFrame.data[4] | (recvFrame.data[5] << 8)| (recvFrame.data[6] << 16)| (recvFrame.data[7] << 24))/1000;
        break;
    case 0x0003cc21:
        OperMonModelDC2.BA_PIN = (float)(recvFrame.data[0] | (recvFrame.data[1] << 8)| (recvFrame.data[2] << 16)| (recvFrame.data[3] << 24))/1000;
        OperMonModelDC2.BA_T1_BA_T3 = (float)(recvFrame.data[4] | (recvFrame.data[5] << 8))/10;
        OperMonModelDC2.BA_T2_BA_T4 = (float)(recvFrame.data[6] | (recvFrame.data[7] << 8))/10;
        break;
    case 0x0004CC21:
        OperMonModelDC2.BA_CHWH = (float)(recvFrame.data[0] | (recvFrame.data[1] << 8)| (recvFrame.data[2] << 16)| (recvFrame.data[3] << 24))/1000;
        OperMonModelDC2.BA_DISWH = (float)(recvFrame.data[4] | (recvFrame.data[5] << 8)| (recvFrame.data[6] << 16)| (recvFrame.data[7] << 24))/1000;
        break;
    case 0x0005CC21:
        OperMonModelDC2.BA_I1_BA_I3 = (float)(recvFrame.data[0] | (recvFrame.data[1] << 8)| (recvFrame.data[2] << 16)| (recvFrame.data[3] << 24))/1000;
        OperMonModelDC2.BA_I2_BA_I4 = (float)(recvFrame.data[4] | (recvFrame.data[5] << 8)| (recvFrame.data[6] << 16)| (recvFrame.data[7] << 24))/1000;
        break;
    case 0x0006CC21:
        OperMonModelDC2.BA_CHAH = (float)(recvFrame.data[0] | (recvFrame.data[1] << 8)| (recvFrame.data[2] << 16)| (recvFrame.data[3] << 24))/1000;
        OperMonModelDC2.BA_DISAH = (float)(recvFrame.data[4] | (recvFrame.data[5] << 8)| (recvFrame.data[6] << 16)| (recvFrame.data[7] << 24))/1000;
        break;
    case 0x0001CC21:
        S_WorkStatusDC2.DOMODE = WorkStatusDC_DOMODE[recvFrame.data[0]];

        if(0xFF == recvFrame.data[1])
        {
            S_WorkStatusDC2.RUNNING = WorkStatusACDC_RUNNING[4];
        }
        else
        {
            S_WorkStatusDC2.RUNNING = WorkStatusDC_RUNNING[recvFrame.data[1]];
        }

        S_WorkStatusDC2.STOP_CASE = WorkStatusDC_STOP_CASE[recvFrame.data[2]];
        S_WorkStatusDC2.CHANNELMODE = WorkStatusDC_CHANNELMODE[recvFrame.data[3]];
        S_WorkStatusDC2.KA5FB = WorkStatusACDC[(recvFrame.data[7] >> 0) & 0x01];
        S_WorkStatusDC2.BMSFB = WorkStatusACDC[(recvFrame.data[7] >> 1) & 0x01];
        S_WorkStatusDC2.L1OTFB = WorkStatusACDC[(recvFrame.data[7] >> 2) & 0x01];
        S_WorkStatusDC2.L2OTFB = WorkStatusACDC[(recvFrame.data[7] >> 3) & 0x01];
        S_WorkStatusDC2.ACERRORFB = WorkStatusDC_ACERRORFB[(recvFrame.data[7] >> 4) & 0x01];
        break;
    case 0x000BCC21:
        OperMonModelDC2.BA_UBAT_IN = (float)(recvFrame.data[0] | (recvFrame.data[1] << 8))/10;
        OperMonModelDC2.BA_UDC = (float)(recvFrame.data[2] | (recvFrame.data[3] << 8))/10;
    break;

    default:
        break;
    }
}

void ProtcolThread::DataAnalCanID_AC(canFrame qData)
{
    this->recvFrame = qData;
    switch (recvFrame.canID&0x7fffffff)
    {
        case 0x0002CCA0:
            OperMonModelAC.BA_UAB1 = (float)(recvFrame.data[0] | (recvFrame.data[1] << 8))/100;
            OperMonModelAC.BA_UBC1 = (float)(recvFrame.data[2] | (recvFrame.data[3] << 8))/100;
            OperMonModelAC.BA_UCA1 = (float)(recvFrame.data[4] | (recvFrame.data[5] << 8))/100;
            break;
        case 0x0003CCA0:
            OperMonModelAC.BA_IA1 = (float)(recvFrame.data[0] | (recvFrame.data[1] << 8))/100;
            OperMonModelAC.BA_IB1 = (float)(recvFrame.data[2] | (recvFrame.data[3] << 8))/100;
            OperMonModelAC.BA_IC1 = (float)(recvFrame.data[4] | (recvFrame.data[5] << 8))/100;
            break;
        case 0x0004CCA0:
            OperMonModelAC.BA_AT = recvFrame.data[0] | (recvFrame.data[1] << 8);
            OperMonModelAC.BA_BT = recvFrame.data[2] | (recvFrame.data[3] << 8);
            OperMonModelAC.BA_CT = recvFrame.data[4] | (recvFrame.data[5] << 8);
            break;
        case 0x0005CCA0:
            OperMonModelAC.BA_ENERGY = (float)(recvFrame.data[0] | (recvFrame.data[1] << 8)| (recvFrame.data[2] << 16)| (recvFrame.data[3] << 24))/1000;
            OperMonModelAC.BA_CHENERGY = (float)(recvFrame.data[4] | (recvFrame.data[5] << 8)| (recvFrame.data[6] << 16)| (recvFrame.data[7] << 24))/1000;
            break;
        case 0x0006CCA0:
            OperMonModelAC.BA_UNd = (float)(recvFrame.data[0] | (recvFrame.data[1] << 8));
            OperMonModelAC.BA_UNq = (float)(recvFrame.data[2] | (recvFrame.data[3] << 8));
            OperMonModelAC.BA_UDC = (recvFrame.data[4] | (recvFrame.data[5] << 8));
            OperMonModelAC.BA_UDCREF = (recvFrame.data[6] | (recvFrame.data[7] << 8));
            break;
        case 0x0007CCA0:
            OperMonModelAC.BA_POWFACTOR = recvFrame.data[0] | (recvFrame.data[1] << 8);
            OperMonModelAC.BA_FREQ = (float)(recvFrame.data[2] | (recvFrame.data[3] << 8))/100;
            OperMonModelAC.BA_POUT = recvFrame.data[4] | (recvFrame.data[5] << 8);
            OperMonModelAC.BA_QOUT = recvFrame.data[6] | (recvFrame.data[7] << 8);
            break;
        case 0x0001CCA0:

            S_WorkStatusAc.GRIDMODEFB = WorkStatusAC_GRIDMODEFB[recvFrame.data[0]];
            if(0xFF == recvFrame.data[1])
            {
                S_WorkStatusAc.RUNNING = WorkStatusACDC_RUNNING[4];
            }
            else
            {
                S_WorkStatusAc.RUNNING = WorkStatusACDC_RUNNING[recvFrame.data[1]];
            }
            S_WorkStatusAc.KM6FB = WorkStatusACDC[(recvFrame.data[7] >> 0) & 0x01];
            S_WorkStatusAc.KM7FB = WorkStatusACDC[(recvFrame.data[7] >> 1) & 0x01];
            S_WorkStatusAc.DCERRORFB = WorkStatusACDC[(recvFrame.data[7] >> 2) & 0x01];
            S_WorkStatusAc.Q2FB = WorkStatusACDC[(recvFrame.data[7] >> 3) & 0x01];
            S_WorkStatusAc.S1FB = WorkStatusACDC[(recvFrame.data[7] >> 4) & 0x01];
            S_WorkStatusAc.T1OTPFB = WorkStatusAC_T1OTPFB[(recvFrame.data[7] >> 5) & 0x01];
            S_WorkStatusAc.T1OTWFB = WorkStatusAC_T1OTWFB[(recvFrame.data[7] >> 6) & 0x01];
            S_WorkStatusAc.PHASEFB = WorkStatusAC_PHASEFB[(recvFrame.data[7] >> 7) & 0x01];

            break;

        default:
            break;
    }
}
