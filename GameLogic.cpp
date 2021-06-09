#include "GameGUI.h"

void Window::ChangeBet(int NewBetValue){
    Window::CurrentBet_ = NewBetValue;
}

void Window::ReducePlayersFundForBet(){
    PlayersFund_-= CurrentBet_;
    PlayersFundInfoLabel_->setNum(PlayersFund_);
}
void Window::StartFirstGame(){

    HitNStayPrompt_->setVisible(false); //Hiding the Hit and Stay prompt, 
    //we only need first bet while we ask user for the bet they want to put

    //now we will connect the spin box to the current bet so that changing it will change currentBet variable
    connect(BetBox_, qOverload<int>(&QSpinBox::valueChanged), this, &Window::ChangeBet);
    //Next we will connect okay button where we will show Players fund reduced when bet is placed
    connect(OkButton_,&QPushButton::clicked, this, &Window::ReducePlayersFundForBet);
}