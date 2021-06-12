#include <QtWidgets/QApplication>
#include <iostream>
#include <QtWidgets/QWidget>
#include <QLabel>
#include <vector>
#include <QTextStream>
#include <QGroupBox>
#include <random>
#include <QThread>
#include <QtWidgets/QGridLayout>
#include "CardsField.h"

using namespace std;
QTextStream out(stdout);

CardsField::CardsField(QString Participant,QWidget *parent): 
    QGroupBox(parent),WhoIsIt_(Participant),TotalScore_(0),ParticipantLatestCardIndex_(0){

    LoadCards();//loading the blank cards

    CardsFieldQGroupBoxVar_ = new QGroupBox; //creating a groupbox
    QGridLayout *ParticipantCardGrid_ = new QGridLayout; //creating a grid layout
    
    if (WhoIsIt_ == "Dealer"){ TileTitle_ = SetTileTitle("red", 22, "black");}
    else{TileTitle_ = SetTileTitle("white", 22, "black");}
    

    ParticipantCardGrid_->addWidget(TileTitle_,0,0,1,5);
    ParticipantCardGrid_->addWidget(ParticipantCards_[0]->CardImageQLabel_,1,0,7,1);
    ParticipantCardGrid_->addWidget(ParticipantCards_[1]->CardImageQLabel_,1,1,7,1);
    ParticipantCardGrid_->addWidget(ParticipantCards_[2]->CardImageQLabel_,1,2,7,1);
    ParticipantCardGrid_->addWidget(ParticipantCards_[3]->CardImageQLabel_,1,3,7,1);
    ParticipantCardGrid_->addWidget(ParticipantCards_[4]->CardImageQLabel_,1,4,7,1);
    CardsFieldQGroupBoxVar_->setLayout(ParticipantCardGrid_);

}

CardsField::~CardsField(){}

//Defining a vector of CardDeck_, here we are adding 44 cards.
// we have added 44 instead of 52 because we want max 5 card shown in worst case
//per player. In that case even if we have smallest 4 Card with value of 4,
//we will have score of more than 20

vector<QString> CardsField::CardDeck_ {"1C","1D","1H","1S","4C","4D","4H","4S",
                                       "5C","5D","5H","5S","6C","6D","6H","6S",
                                       "7C","7D","7H","7S","8C","8D","8H","8S",
                                       "9C","9D","9H","9S","XC","XD","XH","XS",
                                       "JC","JD","JH","JS","QC","QD","QH","QS",
                                       "KC","KD","KH","KS"};
//Static variable to store number of cards in the current deck
int CardsField::TotalCardInCurrentDeck_{44};

//l0ading 5 blank cards for the player
void CardsField::LoadCards(){
    for(int i=0; i<5; i++){
        ParticipantCards_.emplace_back(new Card());
    }
}

//Function to form title of the tiles
QLabel *CardsField::SetTileTitle(QString FontColor, int FontSize, QString BackGroundColor){

    QLabel *title = new QLabel(this); //creating new title for the tile
    //only set symbols if its a main tile
    QString titleSymbolsLeft = " \u2660 \u2663 \u2665 \u2666 ";
    QString titleSymbolsRight = " \u2666 \u2665 \u2663 \u2660 ";
    title->setText(titleSymbolsLeft+WhoIsIt_+titleSymbolsRight); //adding symbols around the name of the participants
    //setting text to label
    title->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);//setting alignment of the label
    title->setStyleSheet("background-color : "+ BackGroundColor +" ; font-size : "+ QString::number(FontSize) +"px; font-weight : bold; color : " + FontColor); //setting text format

    return title;
}

int CardsField::GetRandomCardIndex(){
        
    //1.obtaining random index for new next card-------
    random_device rd; //obtaining a random number from hardware
    mt19937 generator(rd()); // seed the generator
    int LastIndexOfCardDeck = TotalCardInCurrentDeck_-1;
    out << "Last index of the card deck : " << TotalCardInCurrentDeck_<< endl;
    uniform_int_distribution<> distribution(0,LastIndexOfCardDeck);
    int CardDeckRandomIndex = distribution(generator);
    TotalCardInCurrentDeck_--;//one card used so reduce the qty by 1
    return CardDeckRandomIndex;
}

void CardsField::RevealNextCard(){
    
    //1.Reloading the new random card
    int RandomCardIndexForNewCard = GetRandomCardIndex();
    QString NewCard = CardDeck_[RandomCardIndexForNewCard];
    out << NewCard << endl;
    ParticipantCards_[ParticipantLatestCardIndex_]->ReloadTrueCard(NewCard);
    
    //2.Removing the card being used from current deck since its already used
    CardDeck_.erase(CardDeck_.begin()+RandomCardIndexForNewCard);
    
    //3.updating the latest score of the player-----------
    TotalScore_ += ParticipantCards_[ParticipantLatestCardIndex_]->CardValue_;
    out <<  WhoIsIt_<<"'s current score :" <<TotalScore_<<endl; 

    //4.next card to reveal would be on the next position
    //so moving latest card index by one
    if (ParticipantLatestCardIndex_<4) {ParticipantLatestCardIndex_++;}
    //else{cout << "Participant index is more than 4!"<<endl;}
}

void CardsField::ResetCards(){

    //Fading out all the cards shown in screen
    for (int i=ParticipantLatestCardIndex_; i>=0; i--){
        ParticipantCards_[i]->FadeOutAnimation();
    }

    //clearing all the QLable and its old cards and inserting blank cards
    for (int i=0; i<5; i++){
        ParticipantCards_[i]->ReloadTrueCard("TT"); //TT is the name of blank image
    }
    TotalScore_ = 0; //setting total card score of participant to 0
    TotalCardInCurrentDeck_ = 44; //setting total cards in deck to 44 again
    ParticipantLatestCardIndex_ = 0; //moving latest showing card to 0
    

    //Vector will be used to repopulate CardDeck_ to reset deck for the current game
    vector<QString> NewDeck_ {"1C","1D","1H","1S","4C","4D","4H","4S",
                              "5C","5D","5H","5S","6C","6D","6H","6S",
                              "7C","7D","7H","7S","8C","8D","8H","8S",
                              "9C","9D","9H","9S","XC","XD","XH","XS",
                              "JC","JD","JH","JS","QC","QD","QH","QS",
                              "KC","KD","KH","KS"};
    CardDeck_.clear();
    CardDeck_ = NewDeck_;

}