#include <QtWidgets/QApplication>
#include <iostream>
#include <QtWidgets/QWidget>
#include <QLabel>
#include <vector>
#include <QTextStream>
#include <QGroupBox>
#include <random>
#include <QThread>
#include <QTimer>
#include <QtWidgets/QGridLayout>
#include "CardsField.h"

using namespace std;
QTextStream out(stdout);

//------------------#########----------Defining static variables---------#######--------------//

//Defining a vector of CardDeck_, here we are adding 44 cards.
//we have added 44 instead of 52 because we want max 4 card shown in worst case
//per player, so we will have to remove small number cards just to make sure that game
//does not require more cards than 4 otherwise it might crash

vector<QString> CardsField::CardDeck_ {"1C","1D","1H","1S","4C","4D","4H","4S",
                                       "5C","5D","5H","5S","6C","6D","6H","6S",
                                       "7C","7D","7H","7S","8C","8D","8H","8S",
                                       "9C","9D","9H","9S","XC","XD","XH","XS",
                                       "JC","JD","JH","JS","QC","QD","QH","QS",
                                       "KC","KD","KH","KS"};
//Static variable to store number of cards in the current deck
int CardsField::TotalCardInCurrentDeck_{44};

//------------------#########----------Constructor and Destructor---------#######--------------//

CardsField::CardsField(QString Participant,QWidget *parent): 
    QGroupBox(parent),WhoIsIt_(Participant),TotalScore_(0),ParticipantLatestCardIndex_(0){

    LoadCards();//loading the blank cards

    CardsFieldQGroupBoxVar_ = new QGroupBox; //creating a groupbox
    QGridLayout *ParticipantCardGrid_ = new QGridLayout; //creating a grid layout
    
    if (WhoIsIt_ == "Dealer"){ TileTitle_ = SetTileTitle("red", 22, "black");}
    else{TileTitle_ = SetTileTitle("white", 22, "black");}

    ParticipantCardGrid_->addWidget(TileTitle_,0,0,1,4);
    ParticipantCardGrid_->addWidget(ParticipantCards_[0]->CardImageQLabel_,1,0,7,1);
    ParticipantCardGrid_->addWidget(ParticipantCards_[1]->CardImageQLabel_,1,1,7,1);
    ParticipantCardGrid_->addWidget(ParticipantCards_[2]->CardImageQLabel_,1,2,7,1);
    ParticipantCardGrid_->addWidget(ParticipantCards_[3]->CardImageQLabel_,1,3,7,1);
    CardsFieldQGroupBoxVar_->setLayout(ParticipantCardGrid_);

}

CardsField::~CardsField(){}


//------------------#########----------Main Functions of the class---------#######--------------//

//Function to form title of the tiles, setting heading of the CardsField instance
QLabel *CardsField::SetTileTitle(QString FontColor, int FontSize, QString BackGroundColor){

    QLabel *title = new QLabel(this); //creating new title for the tile
    //only set symbols if its a main tile
    titleSymbolsLeft_ = " \u2660 \u2663 \u2665 \u2666               ";
    titleSymbolsRight_ = "               \u2666 \u2665 \u2663 \u2660 ";
    title->setText(titleSymbolsLeft_+WhoIsIt_+titleSymbolsRight_); //adding symbols around the name of the participants
    //setting text to label
    title->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);//setting alignment of the label
    title->setStyleSheet("background-color : "+ BackGroundColor +" ; font-size : "+ QString::number(FontSize) +"px; font-weight : bold; color : " + FontColor); //setting text format

    return title;
}

//loading 4 blank cards for the player
void CardsField::LoadCards(){
    for(int i=0; i<4; i++){
        ParticipantCards_.emplace_back(new Card());
    }
}
//This will get a random index from the available number of cards
int CardsField::GetRandomCardIndex(){
        
    //1.obtaining random index for new next card-------
    random_device rd; //obtaining a random number from hardware
    mt19937 generator(rd()); // seed the generator
    int LastIndexOfCardDeck = TotalCardInCurrentDeck_-1; //Index is one smaller than total number of cards since it starts with 0
    uniform_int_distribution<> distribution(0,LastIndexOfCardDeck);
    int CardDeckRandomIndex = distribution(generator);
    TotalCardInCurrentDeck_--;//one card used so reduce the qty by 1
    return CardDeckRandomIndex;
}

//This will reveal the next card using the random index in the deck
void CardsField::RevealNextCard(){
    
    int RandomCardIndexForNewCard = GetRandomCardIndex(); //Getting the random index for CardDeck_ to pick a card

    //1.Cheching if its dealers second card then it would be closed card and we will save the QString name of the card in a variable to reveal later on
    // otherwise reloading the new random card
    if(WhoIsIt_ == "Dealer" && ParticipantLatestCardIndex_ == 1){
        DealerSecondCard_ = CardDeck_[RandomCardIndexForNewCard]; //Saving the actual Qstring name of the closed card
        ParticipantCards_[ParticipantLatestCardIndex_]->ReloadTrueCard("00"); //Reloading the closed card just to show card closed
    }
    else{
        QString NewCard = CardDeck_[RandomCardIndexForNewCard]; 
        ParticipantCards_[ParticipantLatestCardIndex_]->ReloadTrueCard(NewCard); //Reloading the new random card with QString value
    }
    //2.Removing the card being used from current deck since its already used
    CardDeck_.erase(CardDeck_.begin()+RandomCardIndexForNewCard);
    
    //3.updating the latest score of the player-----------
    TotalScore_ += ParticipantCards_[ParticipantLatestCardIndex_]->CardValue_;

    //4.next card to reveal would be on the next position
    //so moving latest card index by one if the card position is less than 4
    if (ParticipantLatestCardIndex_<4) {ParticipantLatestCardIndex_++;}
    else{cout << "Participant index is more than 4!"<<endl;}
}

//the dealers second closed card revealed
void CardsField::FlipDealersCard(){
    ParticipantCards_[1]->FadeOutAnimation(); //Fade out the shown dummy closed card
    ParticipantCards_[1]->ReloadTrueCard(DealerSecondCard_); //Fade in the true second card using the value we stored in DealersSecondCard_ variable
    TotalScore_ += ParticipantCards_[1]->CardValue_; //Recalculating the score of the dealer
}

void CardsField::ResetCards(){
    //Fading out all the cards shown in screen
    for (int i=ParticipantLatestCardIndex_-1; i>=0; i--){
        ParticipantCards_[i]->FadeOutAnimation();
        ParticipantCards_[i]->CardValue_ = 0;
        //Making sure the card faded does not have any card value even though 
        //its QLabel might have previously used cards still in it
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