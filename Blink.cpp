#include "GameGUI.h"

//Will set tile to yellow color background to player score
void Window::PlayerScoreYellowTile(){
    PlayerScore_->setStyleSheet("background-color : yellow ; font-size : 60 px; font-weight : bold; color : black");
}

//Will set tile to yellow color background to dealer score
void Window::DealerScoreYellowTile(){
    DealerScore_->setStyleSheet("background-color : yellow ; font-size : 60 px; font-weight : bold; color : black");
}

//Func will set tile to green color background to dealer score
void Window::ScoreDefaultTile(){
    DealerScore_->setStyleSheet("background-color : black ; font-size : 60 px; font-weight : bold; color : red");
    PlayerScore_->setStyleSheet("background-color : black ; font-size : 60 px; font-weight : bold; color : white");
}

//Func to blink score tile when player's score is updated
void Window::PlayerScoreUpdateBlink(){
    QTimer::singleShot(100,this,&Window::PlayerScoreYellowTile);
    QTimer::singleShot(200,this,&Window::ScoreDefaultTile);
}

//Func to blink score tile when dealer's score is updated
void Window::DealerScoreUpdateBlink(){
    QTimer::singleShot(100,this,&Window::DealerScoreYellowTile);
    QTimer::singleShot(200,this,&Window::ScoreDefaultTile);
}

//Tile to blink with Red color background for players fund
void Window::FundRedTile(){
    PlayersFundInfoLabel_->setStyleSheet("background-color : red ; font-size : 60 px; font-weight : bold; color : black");
} 

//Tile to blink with Green color background for players fund
void Window::FundGreenTile(){
    PlayersFundInfoLabel_->setStyleSheet("background-color : green ; font-size : 60 px; font-weight : bold; color : black");
} 

//Tile to blink with Default color background for players fund
void Window::FundDefaultTile(){
    PlayersFundInfoLabel_->setStyleSheet("background-color : black ; font-size : 60 px; font-weight : bold; color : white");
}

//Player winning status blink - blinking 3 times with distance of 200 ms
void Window::PlayerWonFundBlink(){
    QTimer::singleShot(0,this,&Window::FundGreenTile);
    QTimer::singleShot(200,this,&Window::FundDefaultTile);
    QTimer::singleShot(400,this,&Window::FundGreenTile);
    QTimer::singleShot(600,this,&Window::FundDefaultTile);
    QTimer::singleShot(800,this,&Window::FundGreenTile);
    QTimer::singleShot(1000,this,&Window::FundDefaultTile);
}

//Player winning status blink - blinking 3 times with distance of 200 ms
void Window::PlayerLostFundBlink(){
    QTimer::singleShot(0,this,&Window::FundRedTile);
    QTimer::singleShot(200,this,&Window::FundDefaultTile);
    QTimer::singleShot(400,this,&Window::FundRedTile);
    QTimer::singleShot(600,this,&Window::FundDefaultTile);
    QTimer::singleShot(800,this,&Window::FundRedTile);
    QTimer::singleShot(1000,this,&Window::FundDefaultTile);
}

//Tile to blink with green color background for status of the game
void Window::MessgaePromptGreenTile(){
    MessageLabel_->setStyleSheet("background-color : green ; font-size : 60 px; font-weight : bold; color : black");
} 

//Tile to blink with red color background for status of the game
void Window::MessgaePromptRedTile(){
    MessageLabel_->setStyleSheet("background-color : red ; font-size : 60 px; font-weight : bold; color : black");
} 

//Tile to blink with default color background for status of the game
void Window::MessgaePromptDefaultTile(){
    MessageLabel_->setStyleSheet("background-color : black ; font-size : 60 px; font-weight : bold; color : white");
} 

//Tile to blink when player wins
void Window::PlayerWonBlink(){
    MessageLabel_->setText("You Won "+QString::number(CurrentBet_)+"$!");
    QTimer::singleShot(0,this,&Window::MessgaePromptGreenTile);
    QTimer::singleShot(200,this,&Window::MessgaePromptDefaultTile);
    QTimer::singleShot(400,this,&Window::MessgaePromptGreenTile);
    QTimer::singleShot(600,this,&Window::MessgaePromptDefaultTile);
    QTimer::singleShot(800,this,&Window::MessgaePromptGreenTile);
    QTimer::singleShot(1000,this,&Window::MessgaePromptDefaultTile);
}

//Tile to blink when player wins blackjack
void Window::PlayerBlackJackBlink(){
    MessageLabel_->setText("Black Jack of "+QString::number(CurrentBet_*1.5)+"$!");
    QTimer::singleShot(0,this,&Window::MessgaePromptGreenTile);
    QTimer::singleShot(200,this,&Window::MessgaePromptDefaultTile);
    QTimer::singleShot(400,this,&Window::MessgaePromptGreenTile);
    QTimer::singleShot(600,this,&Window::MessgaePromptDefaultTile);
    QTimer::singleShot(800,this,&Window::MessgaePromptGreenTile);
    QTimer::singleShot(1000,this,&Window::MessgaePromptDefaultTile);
}

//Tile to blink when player loses
void Window::PlayerLostBlink(){
    MessageLabel_->setText("You Lost "+QString::number(CurrentBet_)+"$!");
    QTimer::singleShot(0,this,&Window::MessgaePromptRedTile);
    QTimer::singleShot(200,this,&Window::MessgaePromptDefaultTile);
    QTimer::singleShot(400,this,&Window::MessgaePromptRedTile);
    QTimer::singleShot(600,this,&Window::MessgaePromptDefaultTile);
    QTimer::singleShot(800,this,&Window::MessgaePromptRedTile);
    QTimer::singleShot(1000,this,&Window::MessgaePromptDefaultTile);
}

//Tile to blink when game is draw
void Window::GameDrawBlink(){
    MessageLabel_->setText("Game Draw!");
    QTimer::singleShot(0,this,&Window::MessgaePromptGreenTile);
    QTimer::singleShot(200,this,&Window::MessgaePromptDefaultTile);
    QTimer::singleShot(400,this,&Window::MessgaePromptGreenTile);
    QTimer::singleShot(600,this,&Window::MessgaePromptDefaultTile);
    QTimer::singleShot(800,this,&Window::MessgaePromptGreenTile);
    QTimer::singleShot(1000,this,&Window::MessgaePromptDefaultTile);
}

void Window::PlayWinningSound(){
    WonSound_->play();
}

void Window::PlayLostSound(){
    LostSound_->play();
}

void Window::PlayDrawSound(){
    DrawSound_->play();
}
