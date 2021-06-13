#include "GameGUI.h"

//Will set tile to yellow color background to player score
void Window::PlayerScoreYellowTile(){
    PlayerScore_->setStyleSheet("background-color : yellow ; font-size : 30 px; font-weight : bold; color : black");
}

//Will set tile to yellow color background to dealer score
void Window::DealerScoreYellowTile(){
    DealerScore_->setStyleSheet("background-color : yellow ; font-size : 30 px; font-weight : bold; color : black");
}

//Func will set tile to green color background to dealer score
void Window::ScoreDefaultTile(){
    DealerScore_->setStyleSheet("background-color : black ; font-size : 22 px; font-weight : bold; color : red");
    PlayerScore_->setStyleSheet("background-color : black ; font-size : 22 px; font-weight : bold; color : white");
}

//Func to blink score tile when player's score is updated
void Window::PlayerScoreUpdateBlink(){
    mutex_.lock();
    QTimer::singleShot(100,this,&Window::PlayerScoreYellowTile);
    QTimer::singleShot(200,this,&Window::ScoreDefaultTile);
    mutex_.unlock();
}

//Func to blink score tile when dealer's score is updated
void Window::DealerScoreUpdateBlink(){
    mutex_.lock();
    QTimer::singleShot(100,this,&Window::DealerScoreYellowTile);
    QTimer::singleShot(200,this,&Window::ScoreDefaultTile);
    mutex_.unlock();
}

//Tile to blink with Red color background for players fund
void Window::FundRedTile(){
    PlayersFundInfoLabel_->setStyleSheet("background-color : red ; font-size : 30 px; font-weight : bold; color : black");
} 

//Tile to blink with Green color background for players fund
void Window::FundGreenTile(){
    PlayersFundInfoLabel_->setStyleSheet("background-color : green ; font-size : 30 px; font-weight : bold; color : black");
} 

//Tile to blink with Default color background for players fund
void Window::FundDefaultTile(){
    PlayersFundInfoLabel_->setStyleSheet("background-color : black ; font-size : 20 px; font-weight : bold; color : white");
}

//Player winning status blink
void Window::PlayerWonFundBlink(){
    mutex_.lock();
    for(int i=0; i<2; i++){
    QTimer::singleShot(100,this,&Window::FundGreenTile);
    QTimer::singleShot(200,this,&Window::FundDefaultTile);
    }
    mutex_.unlock();
}

//Player winning status blink
void Window::PlayerLostFundBlink(){
    mutex_.lock();
    for(int i=0; i<2; i++){
    QTimer::singleShot(100,this,&Window::FundRedTile);
    QTimer::singleShot(200,this,&Window::FundDefaultTile);
    }
    mutex_.unlock();
}

/*

void MessgaePromptGreenTile(); //Tile to blink with green color background
void MessgaePromptRedTile(); //Tile to blink with green color background
void MessgaePromptDefaultTile(); //Tile to blink with green color background

void PlayerLostFundBlink(); //Player loosing status blink
*/

