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

/*
void FundRedTile(); //Tile to blink with Red color background
void FundGreenTile(); //Tile to blink with Green color background
void FundDefaultTile(); //Default color
void MessgaePromptGreenTile(); //Tile to blink with green color background
void MessgaePromptRedTile(); //Tile to blink with green color background
void MessgaePromptDefaultTile(); //Tile to blink with green color background
void PlayerWonBlink(); //Player winning status blink
void PlayerLostBlink(); //Player loosing status blink
*/

