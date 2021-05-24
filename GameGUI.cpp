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
Window::Window(QWidget *parent) : QWidget(parent), DealerFund_(100000), CurrentPlayer_("Player"), CurrentStatus_("Loving it!!"){

    *PlayerFund_ = 5000;
    Window::GameGrid_ = new QGridLayout;
    GameGrid_->addWidget(CardBox("Dealer", "red"),0,0,2,3); //Adding a main Dealer tile
    GameGrid_->addWidget(CardBox("Player", "white"),2,0,2,3); //Adding a main Player tile
    DealersFundBox_ = FundBox("Dealer's Fund ", "red", GetDealerFund());
    GameGrid_->addWidget(DealersFundBox_,0,3,1,1); //Addint tile for dealers fund
    GameGrid_->addWidget(WhoIsPlayingBox(),1,3,1,1); //Addint tile for who is playing currently info
    PlayersFundBox_ = FundBox("Player's Fund ", "white", GetPlayerFund());
    GameGrid_->addWidget(PlayersFundBox_,2,3,1,1); //Adding a tile for players fund
    StartActionBox();
    GameGrid_->addWidget(ActionBox_,3,3,1,1); //Adding a tile for Action box where user will be asked for input

    setLayout(GameGrid_);
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
        InternalBox->addWidget(SetTileTitle("Status : " + GetStatus(),"black",20,"red",false),2,0);
    }
    else if(GetEnumStatus() == Window::Status::Playing){
        InternalBox->addWidget(SetTileTitle("Status : " + GetStatus(),"white",20,"blue",false),2,0);
    }
    else{
        InternalBox->addWidget(SetTileTitle("Status : " + GetStatus(),"black",20,"green",false),2,0);
    }
    MainBox->setLayout(InternalBox); //Adding grid to the group box

    return MainBox;
}

//setting up the first bet prompt
QGroupBox *Window::GetFirstBet(){
    
    QGroupBox *MainBox = new QGroupBox;  //creating a group box
    QGridLayout *InternalBox = new QGridLayout; //creating a grid to put within the box

    InternalBox->addWidget(SetTileTitle("First Bet of The Game!","black",15,"orange",false),0,0,1,2); //Adding info of the first bet

    Window::BetBox_ = new QSpinBox; //creating a new spin box 
    BetBox_->setRange(50,500); //setting a range of spin box
    BetBox_->setSingleStep(50.0); //spin box will jump with range of 50 $
    BetBox_->setValue(100);//initial value of the bet box 
    BetBox_->setPrefix("$"); //setting dollar sign ahead of amount
    InternalBox->addWidget(SetTileTitle("Min. 50$ and Max. 500$","black",15,"white",false),1,0,1,2);//adding information on top
    InternalBox->addWidget(BetBox_,2,0,1,1); //Adding second button to grid
    
    QPushButton *OkButton = new QPushButton("OK"); //adding ok button on the side
    OkButton->setStyleSheet("font-size : 18px; font-weight : bold; color : Green"); //formatting OK Button
    InternalBox->addWidget(OkButton,2,1,1,1); //adding okay button to the grid
    MainBox->setLayout(InternalBox);

    //When pressed okay, sending signal to collect the value from BetBox to CurrentBet_
    connect(OkButton, &QPushButton::clicked, this, &Window::SetBet); 
    //When pressed okay, after setting the SetBet value, we will set status of variable CurrentPrompt_
    connect(OkButton, &QPushButton::clicked, this, &Window::SetPromptStatusHitNStay);
    //When pressed okay, after setting the SetBet value, we will call the new start Action box
    connect(OkButton, &QPushButton::clicked, this, &Window::StartActionBox);
    connect(OkButton, &QPushButton::clicked, this, &Window::SetActionBoxNull);
    //When pressed okay, after setting the SetBet value, we will set status of variable CurrentPrompt_
    

    return MainBox;
}

//Generates smaller tile on right side where prompt will be given for user to act "Hit" and "Stay" option
QGroupBox *Window::GetHitNStay(){

    QGroupBox *MainBox = new QGroupBox;  //creating a group box
    QGridLayout *InternalBox = new QGridLayout; //creating a grid to put within the box
    InternalBox->addWidget(SetTileTitle("Current Bet : " + QString::number(Window::GetBet()),"black",20,"green",false),0,0,1,2);
    InternalBox->addWidget(SetTileTitle("Make Your Move!","black",20,"orange",false),1,0,1,2); //Adding Hit and Stay Button
    
    QPushButton *HitButton = new QPushButton("Hit");
    HitButton->setStyleSheet("font-size : 20px; font-weight : bold; color : green");
    QPushButton *StayButton = new QPushButton("Stay");
    StayButton->setStyleSheet("font-size : 20px; font-weight : bold; color : red");

    InternalBox->addWidget(HitButton,2,0,1,1); //Adding Hit Button to internal grid
    InternalBox->addWidget(StayButton,2,1,1,1); //Adding Stay Button to internal grid
    
    MainBox->setLayout(InternalBox); //Adding grid to the group box
    return MainBox;

}

//Generates smaller tile //Generates smaller tile on right side where prompt will be given for user to act on to select value of Ace 1 or 11
QGroupBox *Window::GetOneNEleven(){}

void Window::StartActionBox(){

    if (GetPromptStatus() == PromptStatus::FirstBet){
        ActionBox_ = GetFirstBet();
    }
    else if (GetPromptStatus()== PromptStatus::HitNStay){
        GameGrid_->removeWidget(PlayersFundBox_);
        GameGrid_->removeWidget(ActionBox_); //removing the old ActionBox Widget
        ActionBox_ = GetHitNStay(); //Redrawing the ActionBox
        GameGrid_->addWidget(ActionBox_,3,3,1,1); //Adding a new ActionBox
        GameGrid_->addWidget(PlayersFundBox_,2,3,1,1); //Refreshing the Fund
    }
    else if (GetPromptStatus() == PromptStatus::OneNEleven){
        ActionBox_ = GetOneNEleven();
    }
    else{
        cout << "There as an prompt error!";
    }
    
    
}



/*The first bet program

    */

/* The Hit and Stay Button Logic
    InternalBox->addWidget(SetTileTitle("Current Bet : " + QString::number(Window::CurrentBet_),"black",20,"green",false),0,0,1,2);
    InternalBox->addWidget(SetTileTitle("Make Your Move!","black",20,"orange",false),1,0,1,2); //Adding Hit and Stay Button
    
    QPushButton *HitButton = new QPushButton("Hit");
    HitButton->setStyleSheet("font-size : 20px; font-weight : bold; color : green");
    QPushButton *StayButton = new QPushButton("Stay");
    StayButton->setStyleSheet("font-size : 20px; font-weight : bold; color : red");

    InternalBox->addWidget(HitButton,2,0,1,1); //Adding Hit Button to internal grid
    InternalBox->addWidget(StayButton,2,1,1,1); //Adding Stay Button to internal grid
    
    MainBox->setLayout(InternalBox); //Adding grid to the group box
    */

/*Adding one and eleven button
    InternalBox->addWidget(SetTileTitle("Current Bet : " + QString::number(Window::CurrentBet_),"black",20,"green",false),0,0,1,2);
    InternalBox->addWidget(SetTileTitle("Value of Ace?","black",20,"orange",false),1,0,1,2); 
    
    QPushButton *oneButton = new QPushButton("1");
    oneButton->setStyleSheet("font-size : 20px; font-weight : bold; color : black");
    QPushButton *elevenButton = new QPushButton("11");
    elevenButton->setStyleSheet("font-size : 20px; font-weight : bold; color : black");

    InternalBox->addWidget(oneButton,2,0,1,1); //Adding Hit Button to internal grid
    InternalBox->addWidget(elevenButton,2,1,1,1); //Adding Stay Button to internal grid
    
    MainBox->setLayout(InternalBox); //Adding grid to the group box
    */