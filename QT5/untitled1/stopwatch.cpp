#include "stopwatch.h"

Stopwatch::Stopwatch(QObject *parent) : QObject{parent}
{
    timer = new QTimer(this);
    time = new QTime(0,0,0,0);
    time_now=time->addMSecs(0);
    old_time=time->addMSecs(0);
    numloop = 0;
    temp=0;
    showloopstr="";
    connect(timer,&QTimer::timeout,this, &Stopwatch::UpdateTime);

}

Stopwatch::~Stopwatch()
{

}

void Stopwatch::SendStopSignal()
{
    emit sig_SendStop();
}



QString Stopwatch::ShowLoop()
{
   return showloopstr;
}



void Stopwatch::Stop()
{
    timer->stop();
}

void Stopwatch::Clear()
{
    time_now=time->addMSecs(0);
    old_time=time->addMSecs(0);
    numloop=0;

}

void Stopwatch::Loop()
{
    int temp= old_time.msecsTo(time_now);
    loops=time->addMSecs(temp);
    old_time=time_now;
    numloop++;

    QString::number(numloop);
    showloopstr ="Круг № "+ QString::number(numloop)+ " Время: " + loops.toString("mm:ss:z");

}

void Stopwatch::UpdateTime()
{  timer->start(100);
   time_now= time_now.addMSecs(100);
   emit sig_SendStart(time_now.toString("mm:ss:z"));

}
