//this class holds a timer for game which keeps track of time passed
#ifndef TIMER_H
#define TIMER_H
#include <QTimer>
#include <QLabel>
#include <QMessageBox>
#include <QObject>

class Timer : public QObject
{

       Q_OBJECT
public:
    Timer();
    QTimer *timer;
    QLabel *label;
    int counter;


public slots:
    //updates the number which indicates how many seconds have passed
    void TimerSlot();
    //resets the time
    void set_zero();

signals:
    //checks if timer field has stopped
    void time_stopped();
};

#endif // MYTIMER_H
