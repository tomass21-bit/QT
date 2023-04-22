#include "stopwatch.h"

Stopwatch::Stopwatch(QObject *parent) : QObject{parent}
{
    timer = new QTimer(this);
    time = new QTime(0,0,0,0);
   t=time->addMSecs(0);

    NumLoop = 0;
       temp=0;
       ShowLoop="";
}

Stopwatch::~Stopwatch()
{

}

void Stopwatch::SendStartSignal()
{
    emit sig_SendStart();

}
void Stopwatch::SendStopSignal()
{
    emit sig_SendStop();

}

QString Stopwatch::showtime()
{
    return t.toString("mm:ss:z");
}

QString Stopwatch::showloop()
{
   return ShowLoop;
}

void Stopwatch::Start()
{
    connect(timer,SIGNAL(timeout()),this,SLOT(updateTime()));
    connect(timer,SIGNAL(timeout()),this,SIGNAL(emit sig_SendStart()));
    timer->start(100);

}

void Stopwatch::Stop()
{
    timer->stop();
}

void Stopwatch::Clear()
{
    t=time->addMSecs(0);
    NumLoop=0;
    loop.clear();


}

void Stopwatch::Loop()
{
    if(loop.empty()==true){
        loops=t;
        loop.push_back(loops);
        NumLoop++;
    }
    else
    {
     int temp= t.msecsTo(loop.back());

    loops=time->addMSecs(-temp);
    loop.push_back(loops);
    NumLoop++;}
    QString::number(NumLoop);
    ShowLoop ="Круг № "+ QString::number(NumLoop)+ " Время: " + loops.toString("mm:ss:z");

}

void Stopwatch::updateTime()
{
   t= t.addMSecs(100);


}
