#include "canthread.h"
#include "GlobalData.h"

#ifndef PF_CAN
#define PF_CAN 29
#endif

#ifndef AF_CAN
#define AF_CAN PF_CAN
#endif

CanThread::CanThread()
{
    //使用信号槽时，跨线程容易报错
    qRegisterMetaType<canFrame>("canFrame");
    stopped = false;
}

int CanThread::Initial(int canRate)
{
    // Use system command init can0
   // QString retStr;
    ExecSysCmd(CMD_CAN_DOWM);
    ExecSysCmd(CMD_SET_BITRATE + QString::number(canRate));

    // 创建一个SocketCan
    canSocket = socket(PF_CAN,SOCK_RAW,CAN_RAW);
    if(canSocket < 0)
    {
        return ERR_CREATE;
    }

    // 设置一些参数，这个是使用的can网络的设备号
    strcpy((char *)(ifr.ifr_name), "can0");
    int ret = ioctl(canSocket, SIOCGIFINDEX, &ifr);
    if(ret < 0)
    {
        qDebug() << "CAN IOCTL SIOCGIFINDEX ERROR!";
        return ret;
    }

    // 设置使用CAN协议
    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;
    //套接字与can0绑定
    ret = bind(canSocket, (struct sockaddr*)&addr, sizeof(addr));
    if(ret < 0)
    {

        qDebug() << "BIND CAN_SOCKET ERROR!";
        return ret;
    }

    return 0;
}

void CanThread::SendMsg(canFrame sndframe)
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
    if(nbytes <= 0)
    {
//        errsendcount++;
    }

}

void CanThread::run()
{
    int nbytes;
    struct can_frame frame;
//    QByteArray qData;
//    qData.resize(sizeof(canFrame));

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
                //MCU向PC上传数据
                //暂不使用转发
//                emit DatatoPC(recvFrame);

                QString test = QString::number(recvFrame.canID&0x7fffffff,16);
                //调试参数
                if(test == "800cc20" || test == "800cc21" || test == "800cca0" )
                {
                    emit UpdateMsg(recvFrame);
                }

                //DC1运行数据
                else if(test == "2cc20" || test == "3cc20" || test == "4cc20"
                        || test == "5cc20" || test == "6cc20" || test == "1cc20" || test == "bcc20" )
                {
                   emit UpdateDc1(recvFrame);
                }

                //DC2运行数据
                else if(test == "2cc21" || test == "3cc21" || test == "4cc21"
                        || test == "5cc21" || test == "6cc21" || test == "1cc21" || test == "bcc21")
                {
                    emit UpdateDc2(recvFrame);
                }

                //AC运行数据
                else if(test == "2cca0" || test == "3cca0" || test == "4cca0"
                        || test == "5cca0" || test == "6cca0" || test == "7cca0" || test == "1cca0" )
                {
                   emit UpdateAC(recvFrame);
                }
//                //AC/DC错误数据
//                else if(test == "8cca0")
//                {
//                    emit DataError(recvFrame);
//                }
//                else if(test == "7cc20" )
//                {
//                    emit DC1DataError(recvFrame);
//                }
//                else if(test == "7cc21" )
//                {
//                    emit DC2DataError(recvFrame);
//                }

            }
        }
    }
}



QString CanThread::ExecSysCmd(QString strCmd)
{
    QProcess p;
    p.start("bash", QStringList() <<"-c" << strCmd);
    p.waitForFinished();
    QString strResult = p.readAllStandardOutput();
    return strResult;
}

void CanThread::stop()
{
    stopped = true;
}
void CanThread::restart()
{
    stopped = false;
}
