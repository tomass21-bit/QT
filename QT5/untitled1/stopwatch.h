#ifndef STOPWATCH_H
#define STOPWATCH_H
#include <QObject>
#include <QTimer>
#include <QTime>



class Stopwatch :public QObject
{
   Q_OBJECT
public:
   explicit Stopwatch(QObject *parent =nullptr);
   ~Stopwatch(void);

   void SendStopSignal(void);
   QString ShowLoop();
   void Stop();
   void Clear();
   void Loop();

private:
   QTimer *timer;
   QTime  *time;
   QTime   time_now;
   QTime   old_time;
   QTime   loops;
   QString showloopstr;
   unsigned numloop;
   int temp;

public slots:
   void UpdateTime();

signals:
   void sig_SendStart(QString);
   void sig_SendStop(void);
};

#endif // STOPWATCH_H
