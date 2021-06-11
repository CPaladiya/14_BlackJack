#include "GameGUI.h"

//Func to change Current bet as the value of spin box being changed
void Window::ChangeBet(int NewBetValue){
    Window::CurrentBet_ = NewBetValue;
}

//Func to reduce the players fund once bet has been placed
void Window::ReducePlayersFundForBet(){
    PlayersFund_-= CurrentBet_;
    PlayersFundInfoLabel_->setNum(PlayersFund_);
}

//Hiding the first best prompt
void Window::HideFirstBetPrompt(){
    FirstBetPrompt_->setVisible(false);
}

//showing first bet prompt
void Window::ShowFirstBetPrompt(){
    FirstBetPrompt_->setVisible(true);
}

//Hide Hit and Stay prompt
void Window::HideHitNStayPrompt(){
    HitNStayPrompt_->setVisible(false);
}

//Show Hit and Stay prompt
void Window::ShowHitNStayPrompt(){
    HitNStayPrompt_->setVisible(true);
}

//Show players card
void Window::ShowPlayersCard(){
    Player_->RevealNextCard();
}

//Show dealers card
void Window::ShowDealersCard(){
    Dealer_->RevealNextCard();
}

//Setting up table and revealing two cards
void Window::StartTableSetupPlayer(){
    ShowPlayersCard();
    QTimer::singleShot(500,this,&Window::ShowPlayersCard);
    QTimer::singleShot(1000,this,&Window::StartTableSetupDealer);
}

//Setting up 
void Window::StartTableSetupDealer(){
    ShowDealersCard();
    QTimer::singleShot(500,this,&Window::ShowDealersCard);
}

void Window::StartFirstGame(){

    Window::HideHitNStayPrompt(); //Hiding the Hit and Stay prompt, 
    //we only need first bet while we ask user for the bet they want to put

    //now we will connect the spin box to the current bet so that changing it will change currentBet variable
    connect(BetBox_, qOverload<int>(&QSpinBox::valueChanged), this, &Window::ChangeBet);
    //Next we will connect okay button where we will show Players fund reduced when bet is placed
    connect(OkButton_,&QPushButton::clicked, this, &Window::ReducePlayersFundForBet);
    connect(OkButton_,&QPushButton::clicked, this, &Window::HideFirstBetPrompt);
    connect(OkButton_,&QPushButton::clicked, this, &Window::ShowHitNStayPrompt);
    connect(HitButton_,&QPushButton::clicked, this, &Window::StartTableSetupPlayer);

    //timer to time the first table setup of the game
}