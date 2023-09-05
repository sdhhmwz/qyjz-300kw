#ifndef PCCANTHREAD_H
#define PCCANTHREAD_H

#include <QThread>
#include <QDebug>
#include <QProcess>
#include <QTimer>
#include <QString>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <linux/can.h>
#include <linux/can/raw.h>
#include <QDebug>
#include <QMetaType>
#include "canthread.h"

#define ERR_CREATE -10

#define CMD_CAN1_DOWM    "ip link set can1 down"
#define CMD_CAN1_UP      "ip link set can1 up"
#define CMD_SET1_BITRATE "ip link set can1 up type can bitrate "

//struct canFramePC{
//    long canID;
//    int dataLen;
//    uint8_t data[8];
//};

class pccanthread: public QThread
{
    Q_OBJECT
public:
    pccanthread();
    int Initial(int canRate);
    void stop();
    void restart();
    canFrame recvFrame;
    //
    int64_t errsendcount = 0;
    int64_t errreadcount = 0;
protected:
    void run();

private:
    //canFramePC recvFrame;
    volatile bool stopped;
    int canSocket;
    struct sockaddr_can addr;
    struct ifreq ifr;

public:
    QString ExecSysCmd(QString cmd);

public slots:
    void SendMsgPC(canFrame sendFrame);

signals:
   void DatatoMCU(canFrame recvFrame);
   void Clearerror();
};

#endif // PCCANTHREAD_H
