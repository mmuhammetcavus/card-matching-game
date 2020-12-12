#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "card.h"
#include "grid.h"
#include <algorithm>
#include "timer.h"
#include <QPushButton>
QString names[30] = {"way", "front", "grandfather", "dad", "war", "floor", "taste", "plot", "planes", "juice", "elbow", "name", "produce", "men", "chess",
                   "way", "front", "grandfather", "dad", "war", "floor", "taste", "plot", "planes", "juice", "elbow", "name", "produce", "men", "chess"};

int main(int argc, char *argv[])
{

    std::random_shuffle(&names[0], &names[29]);
    QApplication app (argc, argv);
    QWidget *cw = new QWidget;
    Timer *mt = new Timer();
    QVBoxLayout *vb = new QVBoxLayout(cw);
    QHBoxLayout *hb = new QHBoxLayout();
    Grid *gl = new Grid(mt, names);
    QObject::connect(mt, SIGNAL(time_stopped()), gl, SLOT(stop()));
    for(int row = 0; row < 5; row++ ) {
        for(int col = 0; col < 6; col++) {
            Card *card= new Card(names[(row * 6 + col)],"?");
            QTimer *timer = new QTimer();
            timer->start(750);
            QObject::connect(card, SIGNAL(clicked()), card, SLOT(flip()));
            QObject::connect(card, SIGNAL(clicked()), gl, SLOT(check()));
            QObject::connect(gl, SIGNAL(two_cards_opened()), timer, SLOT(start()));
            QObject::connect(gl, SIGNAL(two_cards_opened()), gl, SLOT(block_cards()));
            QObject::connect(timer, SIGNAL(timeout()), gl, SLOT(deblock_cards()));
            QObject::connect(timer, SIGNAL(timeout()), gl, SLOT(action()));
            gl->addWidget(card,row,col,1,1);

        }
    };
    QPushButton *qb = new QPushButton("Quit");
    QObject::connect(qb, SIGNAL(clicked()), &app, SLOT(quit()));
    QPushButton *ng = new QPushButton("New Game");
    QObject::connect(ng, SIGNAL(clicked()), gl, SLOT(new_game()));
    QObject::connect(ng, SIGNAL(clicked()), mt, SLOT(set_zero()));
    hb->addWidget(mt->label);
    hb->addWidget(gl->score);
    hb->addWidget(ng);
    hb->addWidget(qb);
    vb->addLayout(hb);
    vb->addLayout(gl);
    cw->setWindowTitle("Card Match Game");
    cw->setLayout(vb);
    cw->show();
    return app.exec();
}


