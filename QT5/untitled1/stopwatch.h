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
    void SendStartSignal(void);
    void SendStopSignal(void);
   QString showtime();
   QString showloop();
   void Start();
   void Stop();
   void Clear();
   void Loop();
private:
QTimer *timer;
QTime  *time;
QTime   t;
QTime   loops;
QString ShowLoop;
unsigned NumLoop;
int temp;
QVector<QTime> loop;
private slots:
void updateTime();
signals:
void sig_SendStart(void);
void sig_SendStop(void);
};



#endif // STOPWATCH_H
