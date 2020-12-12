#include "grid.h"
#include "card.h"

Grid::Grid(Timer *timer, QString names [30]) : QGridLayout() {
    for(int i=0 ; i<30; i++) {
        this->names[i] = names[i];
    }
    this->timer = timer;
    this->score = new QLabel("Score: 0");
    this->sc = 0;
}


void Grid::action() {
    int number_of_enables = 0;
    int open1 = -1;
    int open2 = -1;
    QString text1 = "";
    QString text2 = "";
    bool countered = false;
    for(int i=0; i<this->count(); i++) {
        Card *card = qobject_cast<Card*>(this->itemAt(i)->widget());
        if(card->isEnabled())
            number_of_enables++;
        if(card->isEnabled() and !countered and card->text!="?") {
            open1 = i;
            text1 = card->word;
            countered = true;
            continue;
        } else if(card->isEnabled() and countered and card->text!="?") {
            open2 = i;
            countered = false;
            text2= card->word;
        }

    }
    if(number_of_enables == 0 and this->timer->timer->isActive()) {
        this->timer->timer->stop();
        this->stop();
        QMessageBox msgBox;
        msgBox.setText("You Won.");
        msgBox.exec();
        msgBox.setStandardButtons(QMessageBox::Cancel);

    }
    if(open1 != -1 and open2 != -1) {
        Card *card1 = qobject_cast<Card*>(this->itemAt(open1)->widget());
        Card *card2 = qobject_cast<Card*>(this->itemAt(open2)->widget());

        if(text1==text2 and text1!="") {
            card1->disable();
            card2->disable();
            this->sc+=1;
            score->setText("Score: " +
                           QString::number(this->sc));

        } else if (text1!=text2) {
            card1->flip();
            card2->flip();
        }

    }

}
void Grid::stop() {
    for(int i=0; i<this->count(); i++) {
        Card *card = qobject_cast<Card*>(this->itemAt(i)->widget());
        card->setDisabled(true);
    }
}

void Grid::new_game() {
    this->timer->counter = 0;
    this->timer->timer->start(1000);
    this->sc =0;
    score->setText("Score: " +
                   QString::number(sc));
    std::random_shuffle(&names[0], &names[29]);
    for(int i=0; i<this->count(); i++) {
        Card *card = qobject_cast<Card*>(this->itemAt(i)->widget());
        card->setEnabled(true);
        card->setText("?");
        card->text = "?";
        card->word = this->names[i];
    }
}

void Grid::block_cards() {
    for(int i=0; i<this->count(); i++) {
        Card *card = qobject_cast<Card*>(this->itemAt(i)->widget());
        card->blockSignals(true);
    }
}

void Grid::deblock_cards() {
    for(int i=0; i<this->count(); i++) {
        Card *card = qobject_cast<Card*>(this->itemAt(i)->widget());
        card->blockSignals(false);
    }
}

void Grid::check() {
    int no_of_opens = 0;
    for(int i=0; i<this->count(); i++) {
        Card *card = qobject_cast<Card*>(this->itemAt(i)->widget());

        if(card->isEnabled() and card->text!="?") {
            no_of_opens++;
        }

    }
    if(no_of_opens == 2) {
        emit two_cards_opened();
    }
}
