#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QLabel>
#include <vector>
#include <QTextStream>
#include <QGroupBox>
#include <random>
#include <QtWidgets/QGridLayout>
#include "CardsField.h"


CardsField::CardsField(const QString participant, QWidget *parent = nullptr): WhoIsIt(participant), QGroupBox(parent){

    LoadCards();//loading the blank cards

    CardsFieldQGroupBoxVar_ = new QGroupBox; //creating a groupbox
    QGridLayout *ParticipantCardGrid_ = new QGridLayout; //creating a grid layout
    
    ParticipantCardGrid_->addWidget(ParticipantCards_[0].CardImage,0,0,1,1);
    ParticipantCardGrid_->addWidget(ParticipantCards_[1].CardImage,0,1,1,1);
    ParticipantCardGrid_->addWidget(ParticipantCards_[2].CardImage,0,2,1,1);
    ParticipantCardGrid_->addWidget(ParticipantCards_[3].CardImage,0,3,1,1);
    ParticipantCardGrid_->addWidget(ParticipantCards_[4].CardImage,0,4,1,1);
    CardsFieldQGroupBoxVar_->setLayout(ParticipantCardGrid_);

}

//Defining a vector of CardDeck_
vector<QString> CardsField::CardDeck_ {"1C","1D","1H","1S","2C","2D","2H","2S",
                                       "3C","3D","3H","3S","4C","4D","4H","4S",
                                       "5C","5D","5H","5S","6C","6D","6H","6S",
                                       "7C","7D","7H","7S","8C","8D","8H","8S",
                                       "9C","9D","9H","9S","XC","XD","XH","XS",
                                       "JC","JD","JH","JS","QC","QD","QH","QS",
                                       "KC","KD","KH","KS"};


void CardsField :: ResetCardDeck(){

        //Vector will be used to repopulate CardDeck_ to reset deck
    vector<QString> NewDeck_ {"1C","1D","1H","1S","2C","2D","2H","2S",
                              "3C","3D","3H","3S","4C","4D","4H","4S",
                              "5C","5D","5H","5S","6C","6D","6H","6S",
                              "7C","7D","7H","7S","8C","8D","8H","8S",
                              "9C","9D","9H","9S","XC","XD","XH","XS",
                              "JC","JD","JH","JS","QC","QD","QH","QS",
                              "KC","KD","KH","KS"};
    CardDeck_.clear();
    CardDeck_ = NewDeck_;
    TotalCardInCurrentDeck_ = 52; //number of total card remaining in current deck

}

//l0ading 5 blank cards for the player
void CardsField::LoadCards(){
    for(int i=0; i++; i<5){
        ParticipantCards_.push_back(Card());
    }
}

void CardsField::RevealNextCard(){

    //obtaining random index for new next card--------
    random_device rd; //obtaining a random number from hardware
    mt19937 generator(rd()); // seed the generator
    uniform_int_distribution<> distribution(0,TotalCardInCurrentDeck_);
    int CardDeckRandomIndex = distribution(generator);
    TotalCardInCurrentDeck_--;//one card used so reduce the qty by 1

    //setting a newcard string for the next card----------
    QString NewCard = CardDeck_[CardDeckRandomIndex];
    ParticipantCards_[ParticipantLatestCardIndex].ReloadTrueCard(NewCard);
    //removing the card being used from current deck since its already used
    CardDeck_.erase(CardDeck_.begin()+CardDeckRandomIndex);
    //next card to reveal would be the next one so moving latest card index by one
    ParticipantLatestCardIndex++;

    //updating the latest score of the player-----------
    

}