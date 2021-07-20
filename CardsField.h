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

/*This class will hold cards for player and dealer, each will have its own instance
 On the main screen while playing the game, where the card shows up that field is
 instance of the CardsField class.
 
 It stores socore for each player, holds cards in a vector also has random card generator and static variable for deck*/

class CardsField : public QGroupBox{

    Q_OBJECT

public:
    CardsField(QString Participant, QWidget *parent = nullptr);
    ~CardsField();

    QLabel *SetTileTitle(QString FontColor, int FontSize, QString BackGroundColor);//Set the title of the tile for relevant player
    void LoadCards();//loading first four blank cards in ParticipantCards_ vector
    //i.e random number between 0 to 41. Later on 0 to however many card is available
    int GetRandomCardIndex(); //Getting random index out of all the number of cards available 
    void RevealNextCard();//Getttin the random QString name of the card for next card
    void FlipDealersCard();//Turning Dealers second card
    void ResetCards();//Resetting the card images to blank and getting new batch of 44 cards and reloading the CardDeck_
    void ReloadBlankCards();//Reloading the blank images into card

    QGroupBox *CardsFieldQGroupBoxVar_; //QGroupBox variable of the instance
    vector<Card*> ParticipantCards_; //the cards of player/dealer is stored here
    QString WhoIsIt_; //who is this instance belongs to? "Player" or "Dealer"
    QString titleSymbolsLeft_; //Left string of the title "Player or dealer"
    QString titleSymbolsRight_;//Right string of the title "Player or dealer"
    QString DealerSecondCard_;//specifically saves the QString name of a second car for dealer which will be revealed later on
    QLabel *TileTitle_; //stores the tile title layout
    int TotalScore_; // will store the total score of the card for the instance i.e, dealer or player
    int ParticipantLatestCardIndex_; //card index for currently latest card shown on screen, 
    //to decide where on the grid to show card for any given instance when revealnext card is commanded

    static vector<QString> CardDeck_; //static variable that will hold cards in current deck being used
    //The vector is static because both instance will use the same deck for a game
    static int TotalCardInCurrentDeck_; //number of total card remaining in current deck. At the beginning it will be 44
};


#endif //CARDSFIELD_H