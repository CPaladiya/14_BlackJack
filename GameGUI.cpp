#include "GameGUI.h"

#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QPushButton>
#include <QSpinBox>

QTextStream out(stdout);

//constructor
Window::Window(QWidget *parent) : QWidget(parent){

    Window::GameGrid_ = new QGridLayout;
    GameGrid_->addWidget(Window::ActionBox->DealersFundPrompt_,0,0,2,3); //Adding a main Dealer tile
    //GameGrid_->addWidget(CardBox("Player", "white"),2,0,2,3); //Adding a main Player tile
    GameGrid_->addWidget(Window::ActionBox->PlayersFundPrompt_,0,3,1,1); //Addint tile for dealers fund
    GameGrid_->addWidget(Window::ActionBox->FirstBetPrompt_,1,3,1,1); //Addint tile for who is playing currently info
    GameGrid_->addWidget(Window::ActionBox->HitNStayPrompt_,2,3,1,1); //Adding a tile for players fund
    GameGrid_->addWidget(Window::ActionBox->CurrentPlayerPrompt_,3,3,1,1); //Adding a tile for Action box where user will be asked for input

    setLayout(GameGrid_);
    setWindowTitle(tr("Black Jack Game"));
    resize(1200,800);
}

/*
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
        Window::CurrentStatus_ = "Loving it!!";
    }
    else if (StatusOfPlayer == Status::YouWin){
        Window::CurrentStatus_ = "You Won!!";
    }
    else{
        Window::CurrentStatus_ = "Resetting the \n Game...";
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
    title->setStyleSheet("background-color : "+ BackGroundColor +" ; font-size : "+ QString::number(FontSize) +"px; font-weight : bold; color : " + FontColor); //setting text format

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
*/