#include "GameGUI.h"

#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QPushButton>
#include <QSpinBox>

//constructor
Window::Window(QWidget *parent) : QWidget(parent), DealerFund_(100000), PlayerFund_(5000), CurrentPlayer_("Player"), CurrentStatus_("Chillin!"){

    QGridLayout *GameGrid = new QGridLayout;
    GameGrid->addWidget(CardBox("Dealer", "red"),0,0,2,3);
    GameGrid->addWidget(CardBox("Player", "white"),2,0,2,3);
    GameGrid->addWidget(FundBox("Dealer's Fund ", "red", GetDealerFund()),0,3,1,1);
    GameGrid->addWidget(WhoIsPlayingBox(),1,3,1,1);
    GameGrid->addWidget(FundBox("Player's Fund ", "white", GetPlayerFund()),2,3,1,1);
    GameGrid->addWidget(ActionBox(),3,3,1,1);

    setLayout(GameGrid);
    setWindowTitle(tr("Black Jack Game"));
    resize(1200,800);
}

//Function to set current player
void Window::ToggleCurrentPlayer() {
        if(Window::CurrentPlayer_ == "Dealer"){
            Window::CurrentPlayer_ = "Player";
        }
        else{
            Window::CurrentPlayer_ = "Dealer";
        }
    }

//Function to set status of the player in game
void Window::SetStatus(Status StatusOfPlayer){

    if (StatusOfPlayer == Status::BlackJack){
        Window::CurrentStatus_ = "Black Jack!! \n You Won!";
    }
    else if (StatusOfPlayer == Status::Bust){
        Window::CurrentStatus_ = "Bust!! \n You lost!";
    }
    else if (StatusOfPlayer == Status::Playing){
        Window::CurrentStatus_ = "Chillin!!";
    }
    else if (StatusOfPlayer == Status::YouWin){
        Window::CurrentStatus_ = "You Won!!";
    }
}

//Function to form title of the tiles
QLabel *Window::SetTileTitle(QString participant, QString FontColor, int FontSize, QString BackGroundColor,bool IfMainTile){

    QLabel *title = new QLabel(this); //creating new title for the tile
    //only set symbols if its a main tile
    if(IfMainTile){
        QString titleSymbolsLeft = " \u2660 \u2663 \u2665 \u2666 ";
        QString titleSymbolsRight = " \u2666 \u2665 \u2663 \u2660 ";
        title->setText(titleSymbolsLeft+participant+titleSymbolsRight); //adding symbols around the name of the participants
    }
    else{
        title->setText(participant); 
    }
    //setting text to label
    title->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);//setting alignment of the label
    title->setStyleSheet("background-color : "+ BackGroundColor+ +" ; font-weight : bold; color : " + FontColor); //setting text format
    QFont reSize("Arial", FontSize); //setting the font size
    title->setFont(reSize);

    return title;
}

//Generates main Card tiles where cards will appear for both, dealer and player
QGroupBox *Window::CardBox(QString participant, QString FontColor){
    
    QGroupBox *MainBox = new QGroupBox;  //creating a main group box
    QGridLayout *InternalBox = new QGridLayout; //creating a grid to put within the box
    QPushButton *samplebut2 = new QPushButton(participant); //creating Second button
    InternalBox->addWidget(SetTileTitle(participant,FontColor,25,"black",true),0,0,1,1); //Adding title
    InternalBox->addWidget(samplebut2,1,0,5,1); //Adding second button to grid
    MainBox->setLayout(InternalBox); //Adding grid to the group box

    return MainBox;

}

//Generates smaller tiles on right side where fund will appear
QGroupBox *Window::FundBox(QString participant, QString FontColor, int Fund){

    QGroupBox *MainBox = new QGroupBox;  //creating a group box
    QGridLayout *InternalBox = new QGridLayout; //creating a grid to put within the box
    InternalBox->addWidget(SetTileTitle(participant,FontColor,20,"black",false),0,0); //Adding first button to grid
    InternalBox->addWidget(SetTileTitle(QString::number(Fund)+" $","black",20,"yellow",false),1,0); //Adding fund
    MainBox->setLayout(InternalBox); //Adding grid to the group box

    return MainBox;
}

// Generates smaller tile on right side showing who is playing and the status of the player
QGroupBox *Window::WhoIsPlayingBox(){

    QGroupBox *MainBox = new QGroupBox;  //creating a group box
    QGridLayout *InternalBox = new QGridLayout; //creating a grid to put within the box
    InternalBox->addWidget(SetTileTitle("Who is playing?","black",20,"gray",false),0,0); //Adding Who is playing title
    InternalBox->addWidget(SetTileTitle(GetCurrentPlayer(),"black",20,"orange",false),1,0); //Adding the name of the player
    //changing the tile color of status of player based on Bust, win or currently playing
    if(GetEnumStatus() == Window::Status::Bust){
        InternalBox->addWidget(SetTileTitle(GetStatus(),"black",15,"red",false),2,0);
    }
    else if(GetEnumStatus() == Window::Status::Playing){
        InternalBox->addWidget(SetTileTitle(GetStatus(),"black",15,"gray",false),2,0);
    }
    else{
        InternalBox->addWidget(SetTileTitle(GetStatus(),"black",15,"green",false),2,0);
    }
    MainBox->setLayout(InternalBox); //Adding grid to the group box

    return MainBox;
}

//Generates smaller tile on right side where prompt will be given for user to act on to select value of Ace and "Hit" and "Stay" option
QGroupBox *Window::ActionBox(){

    QGroupBox *MainBox = new QGroupBox;  //creating a group box
    QGridLayout *InternalBox = new QGridLayout; //creating a grid to put within the box
    
    InternalBox->addWidget(SetTileTitle("First Bet of The Game!","black",15,"orange",false),0,0,1,2); //Adding info of the first bet
    
    QSpinBox *BetBox = new QSpinBox; //creating a new spin box
    BetBox->setRange(50,500); //setting a range of spin box
    BetBox->setSingleStep(50.0); //spin box will jump with range of 50 $
    BetBox->setValue(100);//initial value of the bet box 
    InternalBox->addWidget(SetTileTitle("Min. 50$ and Max. 500$","black",10,"white",false),1,0,1,2);
    InternalBox->addWidget(BetBox,2,0,1,1); //Adding second button to grid
    
    QPushButton *OkButton = new QPushButton("OK");
    InternalBox->addWidget(OkButton,2,1,1,1); //adding okay button to the grid
    
    MainBox->setLayout(InternalBox); //Adding grid to the group box

    return MainBox;

}