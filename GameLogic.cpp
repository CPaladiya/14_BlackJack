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

void Window::HideFirstBetPrompt(){
    FirstBetPrompt_->setVisible(false);
}

void Window::ShowFirstBetPrompt(){
    FirstBetPrompt_->setVisible(true);
}

void Window::HideHitNStayPrompt(){
    HitNStayPrompt_->setVisible(false);
}

void Window::ShowHitNStayPrompt(){
    HitNStayPrompt_->setVisible(true);
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
}