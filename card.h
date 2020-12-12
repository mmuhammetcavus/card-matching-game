//this class is for cardd buttons and in it, it has some functionalities
#ifndef CARD_H
#define CARD_H
#include <QPushButton>


class Card : public QPushButton
{

    Q_OBJECT
public:
    Card(QString word, QString text, QWidget* parent = 0);
    QString text;
    QString word;
    //disable all cards and removes the texts on the cards
    void disable();
public slots:
    //flips a card; which means if cards visible text is "?", reveals cards actual word
    //or if cards visible text is its actual words, hides the actual word and shows "?"
    void flip();
};

#endif // CARD_H
