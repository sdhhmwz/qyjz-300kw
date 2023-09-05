#ifndef PARADEFIN_H
#define PARADEFIN_H

#include <QString>

//调试参数
//0x0D DC调试模式设定
struct DebugModelDC{
    int KM1CTRL_KM3CTRL ; //正极主接触器KM1/KM3控制
    int KM2CTRL_KM4CTRL;   // 负极主接触器KM2/KM4控制
    int KM9CTRL_KM10CTRL;   //分档电流接触器KM9/KM10控制
    int KA3CTRL_KA4CTRL;  //直流模块风机控制
    int ERRORTOBMS ; //通道故障输出到BMS控制
    int PWMTESTCTRL;   //PMW测试指令控制
    int DCERRORCTRL;    //直流故障信号
    int LEDERRORCTRL; //直流故障报警指示灯控制
    int LEDRUNCTRL;//直流运行指示灯控制
    int LEDSTANDBYCTRL; // 直流待机指示灯控制
};
//0x10 AC调试模式设定
struct DebugModelAC{

    //0x0F
    int KM6CTRL ; //交流主接触器KM6控制
    int KM7CTRL;   // 交流充电接触器KM7控制
    int KM5CTRL;   //母线放电接触器KM5控制
    int SFUNCTRL;  //交流模块风机控制
    int  LFUNRUNCTRL ; //机柜风机控制
    int  RUNLEDCTRL;   //运行指示灯控制
    int PWMTESTCTRL;    //PMW测试指令控制
    int ACERRORCTRL; //交流故障输出控制
};

//控制参数
//DC
struct ControlParamModelDC{
    //0x03
    int  POUTLIMIT;   // 功率给定限值
    int  HMIIBATL;   // 直流电流给定限值
    int DEADTIME; //死区时间
    int MINONTIME;      //最小导通时间

    //0x04
    int  DCDC_SWFR ; //DC开关频率
    int  RU_UDCT;   // 电压给定变化率
    int RU_IDT;      //电流给定变化率
};
//AC
struct ControlParamModelAC{
    //0x03
    int  IACLIMIT ; //电流给定限值
    int  RU_UDCT;   // 直流电压给定变化率
    int SW_FR;      //开关频率
    int MINONTIME; //最小导通时间
    int DEADTIME;     //死区时间

    //0x04
    int  COMPTIME1 ; //死区补偿时间
    int  COMPANGLE;   // 死区补偿角度
    int SC_USTEP1;    //dq电压滤波拍数
    int SC_ISTEP1; //dq电流滤波拍数
    int UDCH;      //低穿电流给定变化率
    int RU_IDT;      //电流给定变化率
};

//保护参数
//DC
struct ProtectParamModelDC{
    //0x05
    int SC_UDCOV ; //母线过压保护值
    int SC_EEREPT;   //故障最大重试次数
    int SC_RCOVT ; //两次故障重试间隔时间
    int SC_UBATDV;    //直流电压压差保护值
};
//AC
struct ProtectParamModelAC{

    //0x04
    int SC_UDCOV ; //母线过压保护值
    int SC_UACOV;   // 交流过压保护值
    int SC_UACLV;   //交流欠压保护值
    int SC_IACOV;  //交流过流保护值
    //0x05
    int  SC_EFFHIG ; //频率保护上限值
    int  SC_EFFLOW;   //频率保护下限值
    int SC_DETAOMIGA;    //角频率保护阈值
    int SC_IACEQUAL; //交流电流不平衡阈值
    //0x06
    int SC_FINTRT ; //频率扰动阈值
    int SC_RCOVT;   //两次故障重试间隔时间
    int SC_EEREPT;    //故障最大重试次数
    int SC_IGBTDOWN; //高温降容阈值
};

//PI参数
//DC
struct PIModelDC{

    //蓄电池电压环
    int UbatKP ; //蓄电池电压环比例系数
    int UbatTI;   // 蓄电池电压环积分时间

    // 蓄电池电流环
    int IbatKP;  //电流环比例系数
    int IbatTI ; //电流积分时间

};
//AC
struct PIModelAC{
    //0x16 PI参数设置-母线电压
    int UdcKP ; //母线电压环-比例系数
    int UdcTI;   // 母线电压环-积分时间

    //0x17 PI参数设置-锁相环
    int PLLKP;  //锁相环比例系数
    int PLLTI ; //锁相环积分时间

    //0x18 PI参数设置-电流d轴
    int IdKP;  //电流d轴环比例系数
    int IdTI ; //电流d轴环积分时间

    //0x19 PI参数设置-电流d轴
    int IqKP;  //电流q轴环比例系数
    int IqTI ; //电流q轴环积分时间
};

//校准参数
//DC
struct CALModelDC{
    //0x1A 校准参数-1
    int A_UBAT ; //电池电压比例系数
    int B_UBAT;   //电池电压零点系数

    //0x1B 校准参数-2
    int A_I1BAT ; //第一支路电流比例系数
    int B_I1BAT;   //第一支路电流零点系数

    //0x1C 校准参数-3
    int A_I2BAT ; //第二支路电流比例系数
    int B_I2BAT;   //第二支路电流零点系数

    //0x1D 校准参数-4
    int A_IBAT1 ; //电池电流比例系数1
    int B_IBAT1;   //电池电流零点系数1

    //0x1E 校准参数-5
    int A_IBAT2 ; //电池电流比例系数2
    int B_IBAT2;   //电池电流零点系数2

};
//AC
struct CALModelAC{
    //0x1A 校准参数-1
    int A_BUSUDC ; //母线电压比例系数
    int B_BUSUDC;   //母线电压零点系数

    //0x1B 校准参数-2
    int A_UAB ; //交流电压AB比例系数
    int B_UAB;   //交流电压AB零点系数

    //0x1C 校准参数-3
    int A_UAC ; //交流电压AC比例系数
    int B_UAC;   //交流电压AC零点系数

    //0x1D 校准参数-4
    int A_IA ; //交流电流A比例系数
    int B_IA;   //交流电流A零点系数

    //0x1E 校准参数-5
    int A_IC ; //交流电流C比例系数
    int B_IC;   //交流电流C零点系数

};


// 运行监控
//DC
struct  OperationMonitoringModelDC
{
    float BA_UBAT ; //蓄电池电压
    float BA_IBAT;   // 输出电流
    float BA_PIN;   //输出功率
    float BA_T1_BA_T3;    //第一支路IGBT温度
    float BA_T2_BA_T4; //第二支路IGBT温度
    float BA_CHWH;   //通道充电能量
    float BA_DISWH;   //通道放电能量
    float BA_I1_BA_I3 ; //第一支路电流
    float BA_I2_BA_I4;   //第二支路电流
    float BA_CHAH ;  //通道容量
    float BA_DISAH ;  //通道容量
    float BA_UBAT_IN;
    float BA_UDC;
};
//AC
struct  OperationMonitoringModelAC
{
    float BA_UAB1 ;   //AB线电压值
    float BA_UBC1;    //BC线电压值
    float BA_UCA1;    //CA线电压值
    float BA_IA1 ;    //A相电流值
    float BA_IB1;     //B相电流值
    float BA_IC1;     //C相电流值

    __INT16_TYPE__ BA_AT;   //A相桥臂温度
    __INT16_TYPE__ BA_BT;   //B相桥臂温度
    __INT16_TYPE__ BA_CT;   //C相桥臂温度

    float BA_ENERGY;      //累计放电量
    float BA_CHENERGY;    //累计充电量
    __INT16_TYPE__ BA_UNd ;        //d轴电压矢量
    __INT16_TYPE__ BA_UNq;         //q轴电压矢量
    __INT16_TYPE__ BA_UDC ;        //母线电压值
    int16_t BA_UDCREF;      //母线电压给定值
//    float BA_POWFACTOR;   //功率因数
    __INT16_TYPE__ BA_POWFACTOR;
    float BA_FREQ;        //电网频率
    __INT16_TYPE__ BA_POUT;        //交流有功功率值
    __INT16_TYPE__ BA_QOUT;        //交流无功功率值

};

//日期
struct S_Data
{
   int year;
   int month;
   int day;
   int hour;
   int min;
   int sec;
};

//系统设置
//DC
struct S_SystemSetDC
{
   struct S_Data dataproduct;     //出场日期
   int softversion;     //软件版本
   int projectnum;      //项目号
   int serialnum;       //序号
   int manufactid;      //厂商识别码
};

//AC
struct S_SystemSetAC
{
   int modelpara;       //机型参数
   int softversion;     //软件版本
   struct S_Data dataproduct;     //出场日期
};

//运动控制模式
//DC
struct S_MotionConDC
{
    int resume;     //恢复出厂参数
    int mastandby;  //调试使能
};
//AC
struct S_MotionConAC
{
    int resume;         //恢复出厂参数
    int dcmodesel;      //直流工作模式选择
    int mastandby;      //调试使能
    int modulation;     //调制模式
};

//工作状态
//DC
struct S_WorkStatusDC
{
    QString DOMODE;     //运行模式状态
    QString RUNNING;    //设备运行状态
    QString STOP_CASE;  //停机原因
    QString CHANNELMODE;//通道运行状态
    QString KA5FB;      //急停信号反馈
    QString BMSFB;      //BMS接点反馈
    QString L1OTFB;     //电抗1/3过温
    QString L2OTFB;     //电抗2/4过温
    QString ACERRORFB;  //交流故障信号
};
//AC
struct S_WorkStatusAC
{
    QString GRIDMODEFB; //运行模式状态
    QString RUNNING;    //设备运行状态
    QString KM6FB;      //交流主接触器KM6反馈
    QString KM7FB;      //交流充电接触器KM7反馈
    QString DCERRORFB;  //直流故障信号反馈
    QString Q2FB;       //主断路器Q2反馈
    QString S1FB;       //急停开关S1反馈
    QString T1OTPFB;    //变压器超温报警
    QString T1OTWFB;    //变压器超温预警
    QString PHASEFB;    //相序反馈

};


#endif // PARADEFIN_H
