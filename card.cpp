#include "card.h"

Card::Card(QString word, QString text, QWidget* parent)
    : QPushButton (text, parent) {
    this->text = text;
    this->word = word;

}

void Card::flip() {

    if(this->text == "?") {
        this->text = this->word;
        this->setText(this->text);
    }
    else {
        this->text = "?";
        this->setText(this->text);
    }

}


void Card::disable() {
    this->setText("");
    this->setDisabled(true);

}
