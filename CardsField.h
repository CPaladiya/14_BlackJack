#ifndef CARDSFIELD_H
#define CARDSFIELD_H

#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QLabel>
#include <vector>
#include <QTextStream>
#include <QGroupBox>
#include <QMutex>
#include "Card.h"

using namespace std;

class CardsField : public QGroupBox{

    Q_OBJECT

public:
    CardsField(QString Participant, QWidget *parent = nullptr);
    ~CardsField();

    //func
    void LoadCards();//loading first blank cards in ParticipantCards_ vector
    //Set the title of the tile for relevant player
    QLabel *SetTileTitle(QString FontColor, int FontSize, QString BackGroundColor);
    void RevealNextCard();//Getttin the random QString for next card
    void ResetCards();//Resetting the card images to blank and getting new batch of 44 cards
    void ReloadBlankCards();//Reloading the blank images into card
    int GetRandomCardIndex(); //Getting random index out of all the number of cards available 
    //i.e random number between 0 to 41. Later on 0 to however many card is available

    QGroupBox *CardsFieldQGroupBoxVar_; //QGroupBox variable of the instance
    vector<Card*> ParticipantCards_; //the cards of player/dealer is stored here
    QString WhoIsIt_; //who is this instance belongs to? "Player" or "Dealer"
    static vector<QString> CardDeck_; //static variable that will hold cards in current deck being used
    static int TotalCardInCurrentDeck_; //number of total card remaining in current deck. At the beginning it will be 44
    int TotalScore_; // will store the total score of the card for the instance
    int ParticipantLatestCardIndex_; //card index for currently latest card shown on screen
    QLabel *TileTitle_; //stores the tile title layout
    QMutex mutex;
};


#endif //CARDSFIELD_H