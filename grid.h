//this class holds all card buttons and score label and with the field of timer, it makes necesseray changes on game timer
#ifndef GRID_H
#define GRID_H
#include <QGridLayout>
#include <QMessageBox>
#include <QTimer>
#include "card.h"
#include <QLabel>
#include "timer.h"

class Grid : public QGridLayout
{

    Q_OBJECT

public:
    Grid(Timer* timer, QString names [30]);
    QString names [30];
    Timer* timer;
    QLabel* score;
    int sc;

public slots:
    //when two card is open, this function flips them back or disable them
    void action();
    //this disables all the cards and I use it when the time reaches 180 seconds
    void stop();
    //resets time and score, shuffles words in cards and uncovers all the cards
    void new_game();
    //checks if two cards are opened currently and if so it emits a signal
    void check();
    //blocks signal of all cards
    void block_cards();
    //deblock signals of all cards
    void deblock_cards();

signals:
    //gives signal and tells 2 cards are opened currently
    void two_cards_opened();
};

#endif // MYGRID_H
