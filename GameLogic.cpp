#include "GameGUI.h"

//Func to change Current bet as the value of spin box being changed
void Window::ChangeBet(int NewBetValue){
    Window::CurrentBet_ = NewBetValue;
}

//Func to reduce the players fund once bet has been placed
void Window::ReducePlayersFundForBet(){
    PlayersFund_-= CurrentBet_;
    RefreshPlayersFund();
}

//Func to refresh the current bet shown in window
void Window::RefreshCurrentBet(){
    CurrentBetInfoLabel_->setNum(CurrentBet_);
}

//Func to refresh the current score of dealer shown in window
void Window::RefreshDealerScore(){
    DealerScore_->setNum(Dealer_->TotalScore_);
}

//Func to refresh the current score of dealer shown in window
void Window::RefreshPlayerScore(){
    PlayerScore_->setNum(Player_->TotalScore_);
}

//Refreshing Player Fund shown in the window
void Window::RefreshPlayersFund(){
    PlayersFundInfoLabel_->setNum(PlayersFund_);
}

//Refreshing Dealers Fund shown in the window
void Window::RefreshDealersFund(){
    DealersFundInfoLabel_->setNum(DealersFund_);
}

//Update the fund for player and dealer if player has blackjack
void Window::PlayerHasBlackJack(){
    //since we have already reduced the bet amount from player if, it won
    // we will have to add 2.5 times of it
    PlayersFund_+= (CurrentBet_ * 2.5);
    DealersFund_-= (CurrentBet_*1.5);
    RefreshPlayersFund();
    RefreshDealersFund();
    QTimer::singleShot(1000,this,&Window::ResetGame);
}

//Update the fund for player and dealer if player won
void Window::PlayerWon(){
    PlayersFund_+= (CurrentBet_ * 2);
    DealersFund_-= (CurrentBet_);
    RefreshPlayersFund();
    RefreshDealersFund();
    QTimer::singleShot(1000,this,&Window::ResetGame);
}

//Update the fund for player and dealer if player lost
void Window::PlayerLost(){
    //we have already taken money from dealer so no need to deduct it anymore
    DealersFund_+= (CurrentBet_);
    RefreshPlayersFund();
    RefreshDealersFund();
    QTimer::singleShot(1000,this,&Window::ResetGame);
}

//Update the fund for player and dealer if game is draw
void Window::GameDraw(){
    PlayersFund_+= (CurrentBet_);
    RefreshPlayersFund();
    QTimer::singleShot(1000,this,&Window::ResetGame);
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

//Hide message box from the main window
void Window::HideMessageBoxPrompt(){
    MessageBoxPrompt_->setVisible(false);
}

//show message box on the main window
void Window::ShowMessageBoxPrompt(){
    MessageBoxPrompt_->setVisible(true);
}

//Show players card and check the score if its nore more than 21, if it is reset the game
void Window::ShowPlayersCard(){
    
    Player_->RevealNextCard(); //first revealing the new card
    RefreshPlayerScore(); //Refreshing the score value shown in window
    //If now score is more than 21 Player is burst
    if ((Player_->TotalScore_) > 21){
        PlayerLost(); //Player loses if the score is more than 21 and resets the game
    }
}

//Show dealers card and check if its not more than 21, if it is reset the game
void Window::ShowDealersCard(){
    
    Dealer_->RevealNextCard();//First revealing the new card
    RefreshDealerScore(); //Refreshing the score value shown in window
    if ((Dealer_->TotalScore_) > 21){
        PlayerWon(); //Player wins if the dealers score is more than 21 and resets the game
    }
}

//Check if first two cards dealt has black jack for player, if not move on the game
void Window::CheckIfBlackJack(){
    if(Player_->TotalScore_ ==21){
        PlayerHasBlackJack();
    }
    else{
        StartTableSetupDealer();
    }
}

//Setting up table and revealing two cards
void Window::StartTableSetupPlayer(){
    
    ShowPlayersCard();//Showing players first two cards
    QTimer::singleShot(TimeInBetweenCards_,this,&Window::ShowPlayersCard);
    QTimer::singleShot(TimeInBetweenCards_*2,this,&Window::CheckIfBlackJack);
    //Checking if player has black jack!
}

//Setting up table and revealing first and booking second closed card
void Window::StartTableSetupDealer(){
    ShowDealersCard();
    QTimer::singleShot(TimeInBetweenCards_,this,&Window::ShowDealersCard);
}

//Compare delaer and palyer score and declare win/lose
void Window::CompareScoresAndMoveOn(){
    if ((Dealer_->TotalScore_) > 21){
        PlayerWon();
        }
    else if((Dealer_->TotalScore_)<(Player_->TotalScore_)){
        PlayerWon();
        }
    else if((Dealer_->TotalScore_)>(Player_->TotalScore_)){
        PlayerLost();
        }
    else if((Dealer_->TotalScore_)==(Player_->TotalScore_)){
        GameDraw();
        }
}
//Func to reset game once the game is done
void Window::ResetGame(){
    Dealer_->ResetCards();
    Player_->ResetCards();
    HideHitNStayPrompt();
    ShowFirstBetPrompt();
    RefreshDealerScore();
    RefreshPlayerScore();
}

//Ending the game when player press "Stay" button
//We will first Check if the Dealers point is 17 or above
//if not than we reveal next cards untill we reach above 16
//After that we compare the scores
void Window::EndGame(){

    if(Dealer_->TotalScore_<= 16){
        while(Dealer_->TotalScore_<= 16){
            ShowDealersCard();
            RefreshDealerScore();
            }
        }
    CompareScoresAndMoveOn();
    RefreshDealerScore();
    RefreshPlayerScore();
}

void Window::StartFirstGame(){

    Window::HideHitNStayPrompt(); //Hiding the Hit and Stay prompt, 
    Window::HideMessageBoxPrompt(); //Hiding the Message box showing winning and loosing of the game
    //we only need first bet while we ask user for the bet they want to put

    //now we will connect the spin box to the current bet so that changing it will change currentBet variable
    connect(BetBox_, qOverload<int>(&QSpinBox::valueChanged), this, &Window::ChangeBet);
    
    //Next we will connect okay button where we will show Players fund reduced when bet is placed
    connect(OkButton_,&QPushButton::clicked, this, &Window::ReducePlayersFundForBet);
    connect(OkButton_,&QPushButton::clicked, this, &Window::RefreshCurrentBet);
    connect(OkButton_,&QPushButton::clicked, this, &Window::HideFirstBetPrompt);
    connect(OkButton_,&QPushButton::clicked, this, &Window::ShowHitNStayPrompt);
    connect(OkButton_,&QPushButton::clicked, this, &Window::StartTableSetupPlayer);

    //Hit and stay button
    connect(HitButton_,&QPushButton::clicked, this, &Window::ShowPlayersCard);
    connect(StayButton_,&QPushButton::clicked, this, &Window::EndGame);
    //timer to time the first table setup of the game
}