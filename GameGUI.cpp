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

using namespace std;

//constructor
Window::Window(QWidget *parent) : QWidget(parent),CurrentBet_ (0), DealersFund_(100000),PlayersFund_(5000){

    //Drawing all the prompts required for game. 
    //i.e prompt means here, main QGroupBox widgets required for game
    DrawAllPrompts(); 
    
    //Once we have all the widgets drawn, 
    //Total of six QGroupBox widgets are added to the QGridLayout Widget that is one main window here
    AddPromptToWindow();

}

Window::~Window(){}

//Drawing all the required widgets
void Window::DrawAllPrompts(){

    GameGrid_ = new QGridLayout; //Starting main game grid that will hold all the prompts
    DrawFirstBetPrompt(); // Draw First bet prompt
    DrawHitNStayPrompt(); //Draw Hit and Stay button prompt
    DealersFundPrompt_ = DrawFundPrompt("Dealer", DealersFund_, "red", "black"); //Draw Dealers Fund prompt and add it to variable
    PlayersFundPrompt_ = DrawFundPrompt("Player", PlayersFund_, "white", "black"); //Draw Players Fund prompt and add it to variable
    Dealer_ = new CardsField("Dealer"); //Start Dealer_ instance of the CardsField class, that will hold all cards for Dealer_
    Player_ = new CardsField("Player"); //Start Player_ instance of the CardsField class, that will hold all cards for Player_
}

//Adding all the widgets to GameGrid_ which is the main window of the game
void Window::AddPromptToWindow(){

    GameGrid_->addWidget(Dealer_->CardsFieldQGroupBoxVar_,0,0,4,4); //Adding Cards Window for dealers
    GameGrid_->addWidget(Player_->CardsFieldQGroupBoxVar_,4,0,4,4); //Adding Cards Window for Players
    GameGrid_->addWidget(DealersFundPrompt_,0,4,2,1); //Adding Dealers Fund box
    //GameGrid_->addWidget(GameScorePrompt_,2,4,2,1); 
    GameGrid_->addWidget(PlayersFundPrompt_,4,4,2,1); //Adding Players Fund box
    GameGrid_->addWidget(FirstBetPrompt_,6,4,2,1); //Adding First bet prompt
    GameGrid_->addWidget(HitNStayPrompt_,6,4,2,1); //Adding Hit and Stay prompt

    //Setting the grid, its title and Size of the window
    setLayout(GameGrid_);
    setWindowTitle(tr("Black Jack Game"));
    resize(1000,600);

}

//Dynamic Heading  Set
void Window::SetDynamicHeading(QLabel *LabelToPopulate, int &StringToShow, QString FontColor, int FontSize, QString BackGroundColor){

    LabelToPopulate->setNum(StringToShow); //setting text to label
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


//drawing the DrawFundPrompt for given variable
QGroupBox *Window::DrawFundPrompt(QString Participant, int &FundVar, QString FontColor, QString BackGroundColor){

    QGroupBox *QBoxFund = new QGroupBox;  //creating a group box
    QGridLayout *InternalBox = new QGridLayout; //creating a grid to put within the box
    InternalBox->addWidget(SetStaticHeading(Participant,FontColor,20,BackGroundColor),0,0); //Adding first button to grid
    
    //Adding fund for dealer if dealer
    if(Participant == "Dealer"){ 
        DealersFundInfoLabel = new QLabel();
        SetDynamicHeading(DealersFundInfoLabel,FundVar, FontColor,20, BackGroundColor);//setting up DealersFundInfoLabel label
        InternalBox->addWidget(DealersFundInfoLabel,1,0);
    } 
    else if(Participant == "Player"){ 
        PlayersFundInfoLabel = new QLabel();
        SetDynamicHeading(PlayersFundInfoLabel,FundVar, FontColor,20, BackGroundColor);//setting up DealersFundInfoLabel label
        InternalBox->addWidget(PlayersFundInfoLabel,1,0);
    }//Adding fund for Player if Player
    else { cout << "There is an error at DrawFundPrompt Func!" << endl;}
    
    QBoxFund->setLayout(InternalBox); //Adding grid to the group box

    return QBoxFund;
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


    HitNStayPrompt_ = new QGroupBox;  //starting a group box
    QGridLayout *InternalBox = new QGridLayout; //creating a grid to put within the box

    //creating static heading to show current bet while deciding hit or stay
    InternalBox->addWidget(SetStaticHeading("Current Bet : ","black",20,"green"),0,0,1,1);
    CurrentBetInfoLabel = new QLabel();
    //setting up CurrentBetInfoLabel dynamic label
    SetDynamicHeading(CurrentBetInfoLabel, CurrentBet_, "black",20,"green");
    InternalBox->addWidget(CurrentBetInfoLabel,0,1,1,1);

    //Adding Hit and Stay Button
    InternalBox->addWidget(SetStaticHeading("Make Your Move!","black",20,"orange"),1,0,1,2); 
    HitButton = new QPushButton("Hit");
    HitButton->setStyleSheet("font-size : 20px; font-weight : bold; color : green");
    StayButton = new QPushButton("Stay");
    StayButton->setStyleSheet("font-size : 20px; font-weight : bold; color : red");

    InternalBox->addWidget(HitButton,2,0,1,1); //Adding Hit Button to internal grid
    InternalBox->addWidget(StayButton,2,1,1,1); //Adding Stay Button to internal grid
    
    HitNStayPrompt_->setLayout(InternalBox); //Adding grid to the group box
}