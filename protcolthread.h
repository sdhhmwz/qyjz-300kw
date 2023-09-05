#ifndef PROTCOLTHREAD_H
#define PROTCOLTHREAD_H

#include "canthread.h"

class ProtcolThread : public QThread
{
     Q_OBJECT
public:
    ProtcolThread();
    CanThread *pCanTh;
    void Initial();
    void stop();
    void restart();

protected:
    void run();

private:
    bool newData;
    volatile bool stopped;
    canFrame recvFrame;

    void DataAnalysis_AC(canFrame qData);
    void DataAnalysis_DC1(canFrame qData);
    void DataAnalysis_DC2(canFrame qData);


public slots:
    void Update(canFrame qData);
    void DataAnalCanID_DC1(canFrame qData);
    void DataAnalCanID_DC2(canFrame qData);
    void DataAnalCanID_AC(canFrame qData);
};

#endif // PROTCOLTHREAD_H
