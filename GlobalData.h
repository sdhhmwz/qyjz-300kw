#ifndef GLOBALDATA_H
#define GLOBALDATA_H

#include "ParaDefin.h"
#include<QString>

#define ON 1
#define OFF 0

#define CONPARA     0
#define PROTPARA    1
#define PIPARA      2
#define CALPARA     3
#define SYSPARA     4
#define MONTPARA    5
#define DEBUGPARA   6

//DC1
extern __UINT8_TYPE__  status_byte0;
extern __UINT8_TYPE__  status_byte1;

//DC12
extern __UINT8_TYPE__  status_byte0_dc2;
extern __UINT8_TYPE__  status_byte1_dc2;

//AC
extern __UINT8_TYPE__  status_byte0_ac;
extern __UINT8_TYPE__  status_byte1_ac;

//DC1数据
extern DebugModelDC DebugModelDC1;
extern ControlParamModelDC ControlParalDC1;
extern ProtectParamModelDC ProtectParaDC1;
extern PIModelDC pIModelDC1;
extern CALModelDC cALModelDC1;
extern OperationMonitoringModelDC OperMonModelDC1;
extern S_SystemSetDC S_SystemSetDC1;
extern S_MotionConDC S_MotionConDC1;
extern S_WorkStatusDC S_WorkStatusDC1;

//DC2数据
extern DebugModelDC DebugModelDC2;
extern ControlParamModelDC ControlParalDC2;
extern ProtectParamModelDC ProtectParaDC2;
extern PIModelDC pIModelDC2;
extern CALModelDC cALModelDC2;
extern OperationMonitoringModelDC OperMonModelDC2;
extern S_SystemSetDC S_SystemSetDC2;
extern S_MotionConDC S_MotionConDC2;
extern S_WorkStatusDC S_WorkStatusDC2;

//AC数据
extern DebugModelAC DebugModelAC0;
extern ControlParamModelAC ControlParaModelAC;
extern ProtectParamModelAC ProtectParaAC;
extern PIModelAC pIModelAC;
extern CALModelAC cALModelAC;
extern OperationMonitoringModelAC OperMonModelAC;
extern S_SystemSetAC S_SysSetAC;
extern S_MotionConAC S_MotionConAc;
extern S_WorkStatusAC S_WorkStatusAc;


//错误代码
extern QString err_dc[28];
extern QString err_ac[31];
//ACDC
extern QString WorkStatusACDC[];
extern QString WorkStatusACDC_RUNNING[];
//DC
extern QString WorkStatusDC_DOMODE[];
extern QString WorkStatusDC_RUNNING[];
extern QString WorkStatusDC_STOP_CASE[];
extern QString WorkStatusDC_CHANNELMODE[];
extern QString WorkStatusDC_ACERRORFB[];
//AC
extern QString WorkStatusAC_GRIDMODEFB[];
extern QString WorkStatusAC_T1OTPFB[];
extern QString WorkStatusAC_T1OTWFB[];
extern QString WorkStatusAC_PHASEFB[];


//TEST
extern long test_can;
extern long test_pro;
extern int test;

#endif // GLOBALDATA_H
