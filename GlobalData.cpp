#include "GlobalData.h"
#include <QString>


//DC1
__UINT8_TYPE__  status_byte0;
__UINT8_TYPE__  status_byte1;

//DC12
__UINT8_TYPE__  status_byte0_dc2;
__UINT8_TYPE__  status_byte1_dc2;

//AC
__UINT8_TYPE__  status_byte0_ac;
__UINT8_TYPE__  status_byte1_ac;

/**********DC1数据***********/
//调试参数
DebugModelDC DebugModelDC1;
//控制参数
ControlParamModelDC ControlParalDC1;
//保护参数
ProtectParamModelDC ProtectParaDC1;
//PI参数
PIModelDC pIModelDC1;
//校准参数
CALModelDC cALModelDC1;
//运行数据监控
OperationMonitoringModelDC OperMonModelDC1;
//系统参数
S_SystemSetDC S_SystemSetDC1;
//运动控制参数
S_MotionConDC S_MotionConDC1;
//工作状态
S_WorkStatusDC S_WorkStatusDC1{
    .DOMODE = "停机",
    .RUNNING = "待机",
    .STOP_CASE = "正常",
    .CHANNELMODE = "通道独立运行",
    .KA5FB = "断开",
    .BMSFB = "断开",
    .L1OTFB = "断开",
    .L2OTFB = "断开",
    .ACERRORFB = "正常",
};


/**********DC2数据***********/
//调试参数
DebugModelDC DebugModelDC2;
//控制参数
ControlParamModelDC ControlParalDC2;
//保护参数
ProtectParamModelDC ProtectParaDC2;
//PI参数
PIModelDC pIModelDC2;
//校准参数
CALModelDC cALModelDC2;
//运行数据监控
OperationMonitoringModelDC OperMonModelDC2;
//系统参数
S_SystemSetDC S_SystemSetDC2;
//运动控制参数
S_MotionConDC S_MotionConDC2;
//工作状态
S_WorkStatusDC S_WorkStatusDC2
{
    .DOMODE = "停机",
    .RUNNING = "待机",
    .STOP_CASE = "正常",
    .CHANNELMODE = "通道独立运行",
    .KA5FB = "断开",
    .BMSFB = "断开",
    .L1OTFB = "断开",
    .L2OTFB = "断开",
    .ACERRORFB = "正常",
};

/**********AC数据***********/
//调试参数
DebugModelAC DebugModelAC0;
//控制参数
ControlParamModelAC ControlParaModelAC;
//保护参数
ProtectParamModelAC ProtectParaAC;
//PI参数
PIModelAC pIModelAC;
//校准参数
CALModelAC cALModelAC;
//运行数据监控
OperationMonitoringModelAC OperMonModelAC;
//系统参数
S_SystemSetAC S_SysSetAC;
//运动控制参数
S_MotionConAC S_MotionConAc;
//工作状态
S_WorkStatusAC S_WorkStatusAc{
    .GRIDMODEFB = "0",
    .RUNNING = "待机",
    .KM6FB = "断开",
    .KM7FB = "断开",
    .DCERRORFB = "断开",
    .Q2FB = "断开",
    .S1FB = "断开",
    .T1OTPFB = "正常",
    .T1OTWFB = "正常",
    .PHASEFB = "负相序 ",
};

//ACDC
QString WorkStatusACDC[] ={"断开","闭合"};
QString WorkStatusACDC_RUNNING[] ={"待机","启动过程","运行","停机过程","故障"};

//DC
QString WorkStatusDC_DOMODE[] ={"停机","恒功率充电","恒压充电","恒流充电","恒流限压充电","搁置","静置","脉冲充电",
                               "阶梯充电","恒阻值充电","斜坡功率","无","无","无","无","无","无","无","无","无"
                               ,"无","恒功率放电","恒压放电","恒流放电","恒流限压放电","无","无","脉冲放电","阶梯放电",
                                "恒阻值放电","无","无","无","无","无","无","无","无","阶梯充放电","无","无",
                                "无","无","无","无","无","无","无"};

QString WorkStatusDC_RUNNING[] ={"待机","启动过程","运行","停机过程","故障"};
QString WorkStatusDC_STOP_CASE[] ={"手动停机 ","充满停机","放空停机","电压超限停机 ","手动停机"};
QString WorkStatusDC_CHANNELMODE[] ={"通道独立运行 ","通道并联运行"};
QString WorkStatusDC_ACERRORFB[] ={"正常","故障"};

//AC
QString WorkStatusAC_GRIDMODEFB[] ={"","恒定并网直流恒压"};
QString WorkStatusAC_T1OTPFB[] ={"正常","报警"};
QString WorkStatusAC_T1OTWFB[] ={"正常","预警"};
QString WorkStatusAC_PHASEFB[] ={"负相序","正相序"};

//错误参数
QString err_dc[28] = {"无故障","DSP与flash通信错误","功能码超出范围或属性错误","支路1IGBT硬过流",
                      "支路2IGBT硬过流","驱动板故障信号受干扰","蓄电池硬过压故障",
                      "直流母线硬过压故障","硬过流故障","分档硬过流故障",
                      "电压压差过大故障","急停按钮动作","BMS干接点故障",
                      "蓄电池极性反接故障","通讯故障","蓄电池软过压故障",
                      "直流母线软过压故障","蓄电池软欠压故障","蓄电池软过流故障",
                      "蓄电池软欠流故障","蓄电池过功率故障","蓄电池欠功率故障",
                      "直流电流不均故障","支路1超温故障","支路2超温故障",
                      "IGBT温差大故障","支路1电抗器过温故障","支路2电抗器过温故障"
                     };

QString err_ac[31] = {"无故障","DSP与flash通信错误","功能码超出范围或属性错误","A相硬过流故障",
                      "B相硬过流故障","C相硬过流故障","驱动板故障信号受干扰",
                      "直流电压硬过压","交流电流硬过流","交流电压硬过压",
                      "交流接触器故障","交流预充电接触器故障","断路器断开",
                      "急停按钮动作","交流预充电回路故障","交流主回路故障",
                      "放电回路故障","相序反故障","通讯故障",
                      "母线电压软过压","交流电压软过压","交流电压软欠压",
                      "交流电流软过流","三相电流不平衡","频率不符",
                      "A相超温","B相超温","C相超温",
                      "IGBT温差过大","变压器超温报警","变压器超温预警"
                     };
//TEST
long test_can = 0;
long test_pro = 0;
int test = 0;
