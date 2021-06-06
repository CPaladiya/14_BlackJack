#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QLabel>
#include <vector>
#include <QTextStream>
#include <QGroupBox>
#include <random>
#include <QtWidgets/QGridLayout>
#include "CardsField.h"


CardsField::CardsField(const QString Participant, QWidget *parent = nullptr): WhoIsIt(participant), QGroupBox(parent){

    LoadCards();//loading the blank cards

    CardsFieldQGroupBoxVar_ = new QGroupBox; //creating a groupbox
    QGridLayout *ParticipantCardGrid_ = new QGridLayout; //creating a grid layout
    
    ParticipantCardGrid_->addWidget(ParticipantCards_[0].CardImageQLabel_,0,0,1,1);
    ParticipantCardGrid_->addWidget(ParticipantCards_[1].CardImageQLabel_,0,1,1,1);
    ParticipantCardGrid_->addWidget(ParticipantCards_[2].CardImageQLabel_,0,2,1,1);
    ParticipantCardGrid_->addWidget(ParticipantCards_[3].CardImageQLabel_,0,3,1,1);
    ParticipantCardGrid_->addWidget(ParticipantCards_[4].CardImageQLabel_,0,4,1,1);
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
    ParticipantCards_[ParticipantLatestCardIndex_].ReloadTrueCard(NewCard);
    //removing the card being used from current deck since its already used
    CardDeck_.erase(CardDeck_.begin()+CardDeckRandomIndex);
    //next card to reveal would be the next one so moving latest card index by one
    ParticipantLatestCardIndex_++;

    //updating the latest score of the player-----------
    TotalScore_ += ParticipantCards_[ParticipantLatestCardIndex_].CardValue_;
}

void CardsField::ResetCards(){

    //clearing all the QLable and its old cards and inserting blank cards
    for (int i=0; i++; i<5){
        ParticipantCards_[i].ReloadTrueCard("TT"); //TT is the name of blank image
    }
    TotalScore_ = 0; //setting total card score of participant to 0
    TotalCardInCurrentDeck_ = 52; //setting total cards in deck to 52 again
    ParticipantLatestCardIndex_ = 0; //moving latest showing card to 0
    

    //Vector will be used to repopulate CardDeck_ to reset deck for the current game
    vector<QString> NewDeck_ {"1C","1D","1H","1S","2C","2D","2H","2S",
                              "3C","3D","3H","3S","4C","4D","4H","4S",
                              "5C","5D","5H","5S","6C","6D","6H","6S",
                              "7C","7D","7H","7S","8C","8D","8H","8S",
                              "9C","9D","9H","9S","XC","XD","XH","XS",
                              "JC","JD","JH","JS","QC","QD","QH","QS",
                              "KC","KD","KH","KS"};
    CardDeck_.clear();
    CardDeck_ = NewDeck_;

}