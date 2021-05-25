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

    //Drawing all the required widgets
    DrawFirstBetPrompt();
    DrawHitNStayPrompt();
    DrawOneNElevenPrompt();
    DrawFundPrompt(DealersFundPrompt_, "Dealer", DealersFundInfoLabel, "red", "black");
    DrawFundPrompt(PlayersFundPrompt_, "Player", PlayersFundInfoLabel, "red", "black");
    DrawCurrentPlayerPrompt();

    //populating main grid with drawn widgets
    GameGrid_ = new QGridLayout;
    GameGrid_->addWidget(DealersFundPrompt_,0,0,2,3); //Adding a main Dealer tile
    GameGrid_->addWidget(PlayersFundPrompt_,0,3,1,1); //Addint tile for dealers fund
    GameGrid_->addWidget(FirstBetPrompt_,1,3,1,1); //Addint tile for who is playing currently info
    GameGrid_->addWidget(HitNStayPrompt_,2,3,1,1); //Adding a tile for players fund
    GameGrid_->addWidget(CurrentPlayerPrompt_,3,3,1,1); //Adding a tile for Action box where user will be asked for input

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

//setting those headings where we need to modify values as game goes on
void Prompt::SetDynamicHeading(QLabel *LabelToCreate, QString StringToShow, QString FontColor, int FontSize, QString BackGroundColor){

    LabelToCreate = new QLabel(); //creating new LabelToCreate for the tile
    LabelToCreate->setText(StringToShow); 
    //setting text to label
    LabelToCreate->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);//setting alignment of the label
    LabelToCreate->setStyleSheet("background-color : "+ BackGroundColor +" ; font-size : "+ QString::number(FontSize) +"px; font-weight : bold; color : " + FontColor); //setting text format
}

//setting those headings which will not be need to change with game
QLabel *Prompt::SetStaticHeading(QString StringToShow, QString FontColor, int FontSize, QString BackGroundColor){

     QLabel *title = new QLabel(); //creating new title for the tile
    title->setText(StringToShow); 
    //setting text to label
    title->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);//setting alignment of the label
    title->setStyleSheet("background-color : "+ BackGroundColor +" ; font-size : "+ QString::number(FontSize) +"px; font-weight : bold; color : " + FontColor); //setting text format

    return title;
}; 

//drawing the DrawFundPrompt for given variable
void Prompt::DrawFundPrompt(QGroupBox *QBoxFund, QString Participant, QLabel *FundLabel, QString FontColor, QString BackGroundColor){


    QBoxFund = new QGroupBox;  //creating a group box
    QGridLayout *InternalBox = new QGridLayout; //creating a grid to put within the box
    InternalBox->addWidget(SetStaticHeading(Participant,FontColor,20,BackGroundColor),0,0); //Adding first button to grid
    SetDynamicHeading(DealersFundInfoLabel, QString::number(DealersFund_), FontColor,20, BackGroundColor);//setting up DealersFundInfoLabel label
    InternalBox->addWidget(DealersFundInfoLabel,1,0); //Adding fund
    QBoxFund->setLayout(InternalBox); //Adding grid to the group box
}

//drawing CurrentPlayerPrompt
void Prompt::DrawCurrentPlayerPrompt(){

    CurrentPlayerPrompt_ = new QGroupBox;  //creating a group box
    QGridLayout *InternalBox = new QGridLayout; //creating a grid to put within the box
    InternalBox->addWidget(SetStaticHeading("Who is playing?","black",20,"gray"),0,0); //Adding Who is playing title
    SetDynamicHeading(CurrentBetInfoLabel, CurrentPlayer_, "black",20,"gray");
    InternalBox->addWidget(CurrentBetInfoLabel,1,0); //Adding the name of the player
    //changing the tile color of status of player based on Bust, win or currently playing
    SetDynamicHeading(CurrentStatusInfoLabel, CurrentStatus_, "black",20,"gray");
    InternalBox->addWidget(CurrentStatusInfoLabel,2,0);
    CurrentPlayerPrompt_->setLayout(InternalBox); //Adding grid to the group box

}

//drawing First bet prompt
void Prompt::DrawFirstBetPrompt(){

    HitNStayPrompt_ = new QGroupBox;  //creating a group box
    QGridLayout *InternalBox = new QGridLayout; //creating a grid to put within the box

    InternalBox->addWidget(SetStaticHeading("First Bet of The Game!","black",15,"orange"),0,0,1,2); //Adding InfoLabel of the first bet

    BetBox = new QSpinBox; //creating a new spin box 
    BetBox->setRange(50,500); //setting a range of spin box
    BetBox->setValue(100);//initial value of the bet box 
    BetBox->setPrefix("$"); //setting dollar sign ahead of amount
    InternalBox->addWidget(SetStaticHeading("Min. 50$ and Max. 500$","black",15,"white"),1,0,1,2);//adding InfoLabelrmation on top
    InternalBox->addWidget(BetBox,2,0,1,1); //Adding second button to grid
    
    OkButton = new QPushButton("OK"); //adding ok button on the side
    OkButton->setStyleSheet("font-size : 18px; font-weight : bold; color : Green"); //formatting OK Button
    InternalBox->addWidget(OkButton,2,1,1,1); //adding okay button to the grid
    HitNStayPrompt_->setLayout(InternalBox);

}

//drawing Hit and Stay prompt
void Prompt::DrawHitNStayPrompt(){


    HitNStayPrompt_ = new QGroupBox;  //creating a group box
    QGridLayout *InternalBox = new QGridLayout; //creating a grid to put within the box

    InternalBox->addWidget(SetStaticHeading("Current Bet : ","black",20,"green"),0,0,1,1);//creating static heading
    SetDynamicHeading(CurrentBetInfoLabel, QString::number(CurrentBet_), "black",20,"green");//setting up CurrentBetInfoLabel dynamic label
    InternalBox->addWidget(CurrentBetInfoLabel,0,1,1,1);

    InternalBox->addWidget(SetStaticHeading("Make Your Move!","black",20,"orange"),1,0,1,2); //Adding Hit and Stay Button
    HitButton = new QPushButton("Hit");
    HitButton->setStyleSheet("font-size : 20px; font-weight : bold; color : green");
    StayButton = new QPushButton("Stay");
    StayButton->setStyleSheet("font-size : 20px; font-weight : bold; color : red");

    InternalBox->addWidget(HitButton,2,0,1,1); //Adding Hit Button to internal grid
    InternalBox->addWidget(StayButton,2,1,1,1); //Adding Stay Button to internal grid
    
    HitNStayPrompt_->setLayout(InternalBox); //Adding grid to the group box

}

void Prompt::DrawOneNElevenPrompt(){

    OneNElevenPrompt_= new QGroupBox;  //creating a group box
    QGridLayout *InternalBox = new QGridLayout; //creating a grid to put within the box

    InternalBox->addWidget(SetStaticHeading("Current Bet : ","black",20,"green"),0,0,1,1);//creating static heading
    InternalBox->addWidget(CurrentBetInfoLabel,0,1,1,1);
    InternalBox->addWidget(SetStaticHeading("Value of Ace?","black",20,"orange"),1,0,1,2); 
    
    OneButton = new QPushButton("1");
    OneButton->setStyleSheet("font-size : 20px; font-weight : bold; color : black");
    ElevenButton = new QPushButton("11");
    ElevenButton->setStyleSheet("font-size : 20px; font-weight : bold; color : black");

    InternalBox->addWidget(OneButton,2,0,1,1); //Adding Hit Button to internal grid
    InternalBox->addWidget(ElevenButton,2,1,1,1); //Adding Stay Button to internal grid
    
    OneNElevenPrompt_->setLayout(InternalBox); //Adding grid to the group box
}