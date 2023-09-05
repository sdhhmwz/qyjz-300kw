#include "pccanthread.h"

#ifndef PF_CAN
#define PF_CAN 29
#endif

#ifndef AF_CAN
#define AF_CAN PF_CAN
#endif

pccanthread::pccanthread()
{
    stopped = false;
}


int pccanthread::Initial(int canRate)
{
    // Use system command init can0
   // QString retStr;
    ExecSysCmd(CMD_CAN1_DOWM);
    ExecSysCmd(CMD_SET1_BITRATE + QString::number(canRate));

    // 创建一个SocketCan
    canSocket = socket(PF_CAN,SOCK_RAW,CAN_RAW);
    if(canSocket < 0)
    {
        return ERR_CREATE;
    }

    // 设置一些参数，这个是使用的can网络的设备号
    strcpy((char *)(ifr.ifr_name), "can1");
    int ret = ioctl(canSocket, SIOCGIFINDEX, &ifr);
    if(ret < 0)
    {
        qDebug() << "CAN IOCTL SIOCGIFINDEX ERROR!";
        return ret;
    }

    // 设置使用CAN协议
    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;

    ret = bind(canSocket, (struct sockaddr*)&addr, sizeof(addr));
    if(ret < 0)
    {

        qDebug() << "BIND CAN_SOCKET ERROR!";
        return ret;
    }

    return 0;
}

void pccanthread::SendMsgPC(canFrame sndframe)
{
    int nbytes = 0;
    struct can_frame frame;

    // 设置发送到的设备id
    frame.can_id = sndframe.canID;
    frame.can_id &= CAN_EFF_MASK;
    frame.can_id |= CAN_EFF_FLAG;//设置帧格式
    frame.can_dlc = sndframe.dataLen;
    memcpy(frame.data, sndframe.data, frame.can_dlc);
    // 发送数据
    nbytes = sendto(canSocket, &frame, sizeof(struct can_frame), 0, (struct sockaddr*)&addr, sizeof(addr));

    //发送失败
    if(nbytes <= 0)
    {
//        errsendcount++;
    }
    //end
    //发送函数增加延时
    QThread::msleep(1);
}

void pccanthread::run()
{
    int nbytes;
    struct can_frame frame;
    while(!stopped)
    {
//       QThread::msleep(5);

       nbytes = read(canSocket, &frame, sizeof(frame));
        if(nbytes > 0)
        {
            recvFrame.canID = frame.can_id;
            recvFrame.dataLen = frame.can_dlc;
            memcpy(recvFrame.data, frame.data, recvFrame.dataLen);
            if(recvFrame.dataLen == 8)
            {
                //发送信号，向MCU转发
                emit DatatoMCU(recvFrame);
                QString test = QString::number(recvFrame.canID&0x7fffffff,16);
                //清理错误信息
                if(test == "1a0cc" || test == "720cc" || test == "721cc" )
                {
                    emit Clearerror();
                }
//                SendMsgPC(recvFrame);
            }
        }
        //读取失败
//        else if(nbytes < 0)
//        {
//            errreadcount++;
//        }
    }
}



QString pccanthread::ExecSysCmd(QString strCmd)
{
    QProcess p;
    p.start("bash", QStringList() <<"-c" << strCmd);
    p.waitForFinished();
    QString strResult = p.readAllStandardOutput();
    return strResult;
}

void pccanthread::stop()
{
    stopped = true;
}
void pccanthread::restart()
{
    stopped = false;
}

