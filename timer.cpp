#include "timer.h"

Timer::Timer() {
    timer = new QTimer(this);
    label = new QLabel("Time (secs): 0");
    counter = 0;

    connect(timer,SIGNAL(timeout()),
            this, SLOT(TimerSlot()));
    timer->start(1000);
}

void Timer::TimerSlot() {

    counter += 1;
    label->setText("Time (secs): " +
                   QString::number(this->counter));
    if(counter>=180) {
        this->timer->stop();
        QMessageBox msgBox;
        msgBox.setText("You Lost.");
        msgBox.setStandardButtons(QMessageBox::Cancel);
        msgBox.exec();
        emit time_stopped();
    }

}

void Timer::set_zero() {
    this->label->setText("Time (secs): 0");
}
