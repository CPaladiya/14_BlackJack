#include "GameGUI.h"

#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QPushButton>
#include <QSpinBox>
#include <QtWidgets/QGraphicsOpacityEffect>
#include <QPropertyAnimation>

QTextStream out(stdout);
using namespace std;

//constructor
Window::Window(QWidget *parent) : QWidget(parent){

    //Drawing all the required widgets
    DrawDealersCardPrompt();
    DrawPlayersCardPrompt();
    DrawFirstBetPrompt();
    DrawHitNStayPrompt();
    DrawCurrentPlayerPrompt();
    DrawOneNElevenPrompt();
    DealersFundPrompt_ = DrawFundPrompt("Dealer", DealersFund_, "red", "black");
    PlayersFundPrompt_ = DrawFundPrompt("Player", PlayersFund_, "red", "black");
    

    //populating main grid with drawn widgets
    GameGrid_ = new QGridLayout;
    GameGrid_->addWidget(DealersCardPrompt_,0,0,2,4); //Adding Cards Window for dealers
    GameGrid_->addWidget(PlayersCardPrompt_,2,0,2,4); //Adding Cards Window for Players
    GameGrid_->addWidget(DealersFundPrompt_,0,4,1,1); //Adding a main Dealer tile
    GameGrid_->addWidget(CurrentPlayerPrompt_,1,4,1,1); //Adding a tile for Action box where user will be asked for input
    GameGrid_->addWidget(PlayersFundPrompt_,2,4,1,1); //Adding tile for dealers fund
    GameGrid_->addWidget(FirstBetPrompt_,3,4,1,1); //Adding tile for who is playing currently info 
    GameGrid_->addWidget(OneNElevenPrompt_,3,4,1,1);//Adding tile for one and eleven option for ace card
    GameGrid_->addWidget(HitNStayPrompt_,3,4,1,1); //Adding a tile for players fund

    //Setting the grid, its title and Size of the window
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

//Dynamic Heading  Set
void Window::SetDynamicHeading(QLabel *LabelToPopulate, QString StringToShow, QString FontColor, int FontSize, QString BackGroundColor){

    LabelToPopulate->setText(StringToShow); //setting text to label
    LabelToPopulate->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);//setting alignment of the label, line below setting text format
    LabelToPopulate->setStyleSheet("background-color : "+ BackGroundColor +" ; font-size : "+ QString::number(FontSize) +"px; font-weight : bold; color : " + FontColor);
}

//setting those headings which will not be need to change with game
QLabel *Window::SetStaticHeading(QString StringToShow, QString FontColor, int FontSize, QString BackGroundColor){

    QLabel *title = new QLabel(); //creating new title for the tile
    title->setText(StringToShow); 
    //setting text to label
    title->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);//setting alignment of the label
    title->setStyleSheet("background-color : "+ BackGroundColor +" ; font-size : "+ QString::number(FontSize) +"px; font-weight : bold; color : " + FontColor); //setting text format

    return title;
}; 

//Drawing the Crads window for Dealer
void Window::DrawDealersCardPrompt(){
    DealersCardPrompt_ = new QGroupBox; //creating a groupbox
    DealersCardGrid_ = new QGridLayout; //creating a grid layout
    QPixmap loadedImage("/home/cpaladiya/My_prog_projects/14_BlackJack/cards/1C.png"); //loading the image
    QLabel *NewImage = new QLabel();//creating a new label
    int LabelHeight = NewImage->height();
    int LabelWidth = NewImage->width();
    NewImage->setPixmap(loadedImage.scaled(LabelWidth/4,LabelHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    QGraphicsOpacityEffect *eff = new QGraphicsOpacityEffect(this);
    NewImage->setGraphicsEffect(eff);
    QPropertyAnimation *a = new QPropertyAnimation(eff,"opacity");
    a->setDuration(2000);
    a->setStartValue(0);
    a->setEndValue(1);
    a->setEasingCurve(QEasingCurve::InBack);
    a->start(QPropertyAnimation::DeleteWhenStopped);

    DealersCardGrid_->addWidget(NewImage);
    DealersCardPrompt_->setLayout(DealersCardGrid_);
    
}

//Drawing the Crads window for Dealer
void Window::DrawPlayersCardPrompt(){
    PlayersCardPrompt_ = new QGroupBox; //creating a groupbox
    PlayersCardGrid_ = new QGridLayout; //creating a grid layout
    QPixmap loadedImage("/home/cpaladiya/My_prog_projects/14_BlackJack/cards/00.png"); //loading the image
    QLabel *NewImage = new QLabel();//creating a new label
    int LabelHeight = NewImage->height();
    int LabelWidth = NewImage->width();
    NewImage->setPixmap(loadedImage.scaled(LabelWidth/4,LabelHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    PlayersCardGrid_->addWidget(NewImage);
    PlayersCardPrompt_->setLayout(PlayersCardGrid_);
    
}

//drawing the DrawFundPrompt for given variable
QGroupBox *Window::DrawFundPrompt(QString Participant, int FundVar, QString FontColor, QString BackGroundColor){

    QGroupBox *QBoxFund = new QGroupBox;  //creating a group box
    QGridLayout *InternalBox = new QGridLayout; //creating a grid to put within the box
    InternalBox->addWidget(SetStaticHeading(Participant,FontColor,20,BackGroundColor),0,0); //Adding first button to grid
    
    //Adding fund for dealer if dealer
    if(Participant == "Dealer"){ 
        DealersFundInfoLabel = new QLabel();
        SetDynamicHeading(DealersFundInfoLabel,QString::number(FundVar), FontColor,20, BackGroundColor);//setting up DealersFundInfoLabel label
        InternalBox->addWidget(DealersFundInfoLabel,1,0);
    } 
    else if(Participant == "Player"){ 
        PlayersFundInfoLabel = new QLabel();
        SetDynamicHeading(PlayersFundInfoLabel,QString::number(FundVar), FontColor,20, BackGroundColor);//setting up DealersFundInfoLabel label
        InternalBox->addWidget(DealersFundInfoLabel,1,0);
    }//Adding fund for Player if Player
    else { cout << "There is an error at DrawFundPrompt Func!" << endl;}
    
    QBoxFund->setLayout(InternalBox); //Adding grid to the group box

    return QBoxFund;
}

//drawing CurrentPlayerPrompt
void Window::DrawCurrentPlayerPrompt(){

    CurrentPlayerPrompt_ = new QGroupBox;  //creating a group box
    QGridLayout *InternalBox = new QGridLayout; //creating a grid to put within the box
    
    InternalBox->addWidget(SetStaticHeading("Who is playing?","black",20,"gray"),0,0); //Adding Who is playing title
    CurrentPlayerInfoLabel = new QLabel();
    SetDynamicHeading(CurrentPlayerInfoLabel, CurrentPlayer_, "black",20,"gray");
    InternalBox->addWidget(CurrentPlayerInfoLabel,1,0); //Adding the name of the player
    
    CurrentStatusInfoLabel = new QLabel(); //Adding the current status of the game
    SetDynamicHeading(CurrentStatusInfoLabel, CurrentStatus_, "black",20,"gray");
    InternalBox->addWidget(CurrentStatusInfoLabel,2,0);
    
    CurrentPlayerPrompt_->setLayout(InternalBox); //Adding grid to the group box

}

//drawing First bet prompt
void Window::DrawFirstBetPrompt(){


    FirstBetPrompt_ = new QGroupBox;  //creating a group box
    QGridLayout *InternalBox = new QGridLayout; //creating a grid to put within the box

    InternalBox->addWidget(SetStaticHeading("First Bet of The Game!","black",15,"orange"),0,0,1,2); //Adding InfoLabel of the first bet

    BetBox = new QSpinBox; //creating a new spin box 
    BetBox->setRange(50,500); //setting a range of spin box
    BetBox->setSingleStep(50);//setting a step of 50 to increase with up and down arrow
    BetBox->setValue(100);//initial value of the bet box 
    //set the steps here
    BetBox->setPrefix("$"); //setting dollar sign ahead of amount
    InternalBox->addWidget(SetStaticHeading("Min. 50$ and Max. 500$","black",15,"white"),1,0,1,2);//adding InfoLabelrmation on top
    InternalBox->addWidget(BetBox,2,0,1,1); //Adding second button to grid
    
    OkButton = new QPushButton("OK"); //adding ok button on the side
    OkButton->setStyleSheet("font-size : 18px; font-weight : bold; color : Green"); //formatting OK Button
    InternalBox->addWidget(OkButton,2,1,1,1); //adding okay button to the grid
    FirstBetPrompt_->setLayout(InternalBox);

}

//drawing Hit and Stay prompt
void Window::DrawHitNStayPrompt(){


    HitNStayPrompt_ = new QGroupBox;  //creating a group box
    QGridLayout *InternalBox = new QGridLayout; //creating a grid to put within the box

    InternalBox->addWidget(SetStaticHeading("Current Bet : ","black",20,"green"),0,0,1,1);//creating static heading
    CurrentBetInfoLabel = new QLabel();
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

void Window::DrawOneNElevenPrompt(){

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