#ifndef CARDSFIELD_H
#define CARDSFIELD_H

#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QLabel>
#include <vector>
#include <QTextStream>
#include <QGroupBox>
#include "Card.h"

QTextStream out(stdout);
using namespace std;

class CardsField : public QGroupBox{

    Q_OBJECT

public:
    explicit CardsField(const QString Participant, QWidget *parent = nullptr);

    //func
    void ResetCardDeck();//Resetting the card deck for next play
    void RevealNextCard();//Getttin the random QString for next card
    void LoadCards();//loading first blank cards in ParticipantCards_ vector

    QGroupBox *CardsFieldQGroupBoxVar_; //QGroupBox variable of the instance
    vector<Card> ParticipantCards_; //the cards of player/dealer is stored here
    static vector<QString> CardDeck_; //static variable that will hold cards in current deck being used
    int TotalCardInCurrentDeck_{52}; //number of total card remaining in current deck
    int TotalScore; // will store the total score of the card for instance
    QString WhoIsIt; //who is this instance belongs to? "Player" or "Dealer"
    int ParticipantLatestCardIndex{0}; //latest card index currently shown on screen
    
}


#endif //CARDSFIELD_H