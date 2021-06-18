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
Window::Window(QWidget *parent) : QWidget(parent),CurrentBet_ (100), DealersFund_(100000),PlayersFund_(5000), 
                                TimeInBetweenCards_(1000), BlinkDelay_(1000){

    //Sound being played in the background and loading instance of sounds to play based on outcome of the game
    LoadSound();

    //Drawing all the prompts required for game. 
    //i.e prompt means here, main QGroupBox widgets required for game
    DrawAllPrompts(); 
    
    //Once we have all the widgets drawn, 
    //Total of six QGroupBox widgets are added to the QGridLayout Widget that is one main window here
    AddPromptToWindow();

    //Once all the widgets are drawn we will start the game now
    StartFirstGame();
}

Window::~Window(){}

void Window::LoadSound(){
    
    //Loading the Playlist with infininte loop for background sound of the game
    BackGSoundPlaylist_ = new QMediaPlaylist();
    BackGSoundPlaylist_->addMedia(QUrl::fromLocalFile("/home/cpaladiya/My_prog_projects/14_BlackJack/cards/Song.mp3"));
    BackGSoundPlaylist_->setPlaybackMode(QMediaPlaylist::Loop);

    //Adding the play list to the QMediaPlayer object
    BackGSound_ = new QMediaPlayer();
    BackGSound_->setPlaylist(BackGSoundPlaylist_);
    BackGSound_->setVolume(70);
    BackGSound_->play(); //Playing the sound with infinite loop

    //Adding the sound to play when won
    WonSound_= new QMediaPlayer();
    WonSound_->setMedia(QUrl::fromLocalFile("/home/cpaladiya/My_prog_projects/14_BlackJack/cards/Won.mp3"));
    //Adding the sound to play when lost
    LostSound_= new QMediaPlayer();
    LostSound_->setMedia(QUrl::fromLocalFile("/home/cpaladiya/My_prog_projects/14_BlackJack/cards/Lost.mp3"));
    //Adding the sound to play when game Draw
    DrawSound_= new QMediaPlayer();
    DrawSound_->setMedia(QUrl::fromLocalFile("/home/cpaladiya/My_prog_projects/14_BlackJack/cards/Draw.mp3"));
}

//Drawing all the required widgets and storing it in respective QGroupBox variables
void Window::DrawAllPrompts(){

    GameGrid_ = new QGridLayout; //Starting main game grid that will hold all the prompts
    DrawFirstBetPrompt(); // Draw First bet prompt
    DrawHitNStayPrompt(); //Draw Hit and Stay button prompt
    DrawMessageBoxPrompt(); //Draw message box prompts
    DrawScoreBoard();//Draw the score board for the current game
    DealersFundPrompt_ = DrawFundPrompt("Dealer", DealersFund_, "red", "black"); //Draw Dealers Fund prompt and add it to variable
    PlayersFundPrompt_ = DrawFundPrompt("Player", PlayersFund_, "white", "black"); //Draw Players Fund prompt and add it to variable
    Dealer_ = new CardsField("Dealer"); //Start Dealer_ instance of the CardsField class, that will hold all cards for Dealer_
    Player_ = new CardsField("Player"); //Start Player_ instance of the CardsField class, that will hold all cards for Player_
}

//Adding all the widgets/QGroupBox variables to GameGrid_ which is the main window of the game
void Window::AddPromptToWindow(){

    GameGrid_->addWidget(Dealer_->CardsFieldQGroupBoxVar_,0,0,4,4); //Adding Cards Window for dealers
    GameGrid_->addWidget(Player_->CardsFieldQGroupBoxVar_,4,0,4,4); //Adding Cards Window for Players
    GameGrid_->addWidget(DealersFundPrompt_,0,4,2,1); //Adding Dealers Fund box
    GameGrid_->addWidget(ScoreBoardPrompt_,2,4,2,1); //Adding ScoreBoard Box for current game
    GameGrid_->addWidget(MessageBoxPrompt_,4,4,2,1); //Adding message box prompt
    GameGrid_->addWidget(FirstBetPrompt_,4,4,2,1); //Adding First bet prompt
    GameGrid_->addWidget(HitNStayPrompt_,4,4,2,1); //Adding Hit and Stay prompt
    GameGrid_->addWidget(PlayersFundPrompt_,6,4,2,1); //Adding Players Fund box
    

    //Setting the grid, its title and Size of the window
    setLayout(GameGrid_);
    setWindowTitle(tr("Black Jack Game"));
    resize(1000,600);

}

//Dynamic Heading  Set for all the labels which value is supposed to change
void Window::SetDynamicHeading(QLabel *LabelToPopulate, int StringToShow, QString FontColor, int FontSize, QString BackGroundColor){

    LabelToPopulate->setNum(StringToShow); //setting text to label
    LabelToPopulate->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);//setting alignment of the label, line below setting text format
    //Formatting the style of font, its color and background color
    LabelToPopulate->setStyleSheet("background-color : "+ BackGroundColor +" ; font-size : "+ QString::number(FontSize) +"px; font-weight : bold; color : " + FontColor);
}

//setting those headings which will not be need to change during the game
QLabel *Window::SetStaticHeading(QString StringToShow, QString FontColor, int FontSize, QString BackGroundColor){

    QLabel *title = new QLabel(); //creating new title for the tile
    title->setText(StringToShow); //setting the text to label
    //setting text to label
    title->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);//setting alignment of the label
    title->setStyleSheet("background-color : "+ BackGroundColor +" ; font-size : "+ QString::number(FontSize) +"px; font-weight : bold; color : " + FontColor); //setting text format

    return title;
}; 

//drawing the DrawFundPrompt for given variable
QGroupBox *Window::DrawFundPrompt(QString Participant, int &FundVar, QString FontColor, QString BackGroundColor){

    QGroupBox *QBoxFund = new QGroupBox;  //creating a group box
    QGridLayout *InternalGridInsideGroupBox = new QGridLayout; //creating a grid to put within the box
    InternalGridInsideGroupBox->addWidget(SetStaticHeading(Participant+" $",FontColor,20,BackGroundColor),0,0); //Adding first button to grid
    
    //Adding fund for dealer if dealer
    if(Participant == "Dealer"){ 
        DealersFundInfoLabel_ = new QLabel();
        SetDynamicHeading(DealersFundInfoLabel_,FundVar, FontColor,16, BackGroundColor);//setting up DealersFundInfoLabel label
        InternalGridInsideGroupBox->addWidget(DealersFundInfoLabel_,1,0);
    } //Adding fund for Player if Player
    else if(Participant == "Player"){ 
        PlayersFundInfoLabel_ = new QLabel();
        SetDynamicHeading(PlayersFundInfoLabel_,FundVar, FontColor,16, BackGroundColor);//setting up DealersFundInfoLabel label
        InternalGridInsideGroupBox->addWidget(PlayersFundInfoLabel_,1,0);
    }
    else { cout << "There is an error at DrawFundPrompt Func!" << endl;}
    
    QBoxFund->setLayout(InternalGridInsideGroupBox); //Adding grid to the group box

    return QBoxFund;
}

//drawing score board for current game for dealer and player i.e who's score is what for example, dealer's score is 18, player's 20 etc.
void Window::DrawScoreBoard(){

    ScoreBoardPrompt_ = new QGroupBox;  //starting a group box
    QGridLayout *InternalGridInsideGroupBox = new QGridLayout; //creating a grid to put within the box

    int InitialScore = 0;
    //Creating static heading to show current score of the dealer, if not initiated it will show garbage
    InternalGridInsideGroupBox->addWidget(SetStaticHeading("Dealer's Score","red",16,"black"),0,0,1,3);
    DealerScore_ = new QLabel(); //setting up DealerScore label
    SetDynamicHeading(DealerScore_, InitialScore, "red",16,"black");
    InternalGridInsideGroupBox->addWidget(DealerScore_,0,3,1,1); 
    
    //creating static heading to show current score of the player
    InternalGridInsideGroupBox->addWidget(SetStaticHeading("Player's Score","white",16,"black"),1,0,1,3);
    PlayerScore_ = new QLabel(); //setting up PlayerScore label
    SetDynamicHeading(PlayerScore_, InitialScore, "white",16,"black");
    InternalGridInsideGroupBox->addWidget(PlayerScore_,1,3,1,1);  
    
    ScoreBoardPrompt_->setLayout(InternalGridInsideGroupBox); //Adding grid to the group box
}

//drawing First bet prompt
void Window::DrawFirstBetPrompt(){

    FirstBetPrompt_ = new QGroupBox;  //creating a group box
    QGridLayout *InternalGridInsideGroupBox = new QGridLayout; //creating a grid to put within the box

    InternalGridInsideGroupBox->addWidget(SetStaticHeading("First Bet of The Game!","black",15,"orange"),0,0,1,4); //Adding InfoLabel of the first bet

    BetBox_ = new QSpinBox; //creating a new spin box 
    BetBox_->setRange(50,500); //setting a range of spin box
    BetBox_->setSingleStep(50);//setting a step of 50 to increase with up and down arrow
    BetBox_->setValue(100);//initial value of the bet box 
    //set the steps here
    BetBox_->setPrefix("$"); //setting dollar sign ahead of amount
    InternalGridInsideGroupBox->addWidget(SetStaticHeading("Min. 50$ and Max. 500$","black",15,"white"),1,0,1,4);//adding InfoLabelrmation on top
    InternalGridInsideGroupBox->addWidget(BetBox_,2,0,1,2); //Adding spin box to grid
    
    OkButton_ = new QPushButton("OK"); //adding ok button on the side
    OkButton_->setStyleSheet("font-size : 15px; font-weight : bold; color : Green"); //formatting OK Button
    InternalGridInsideGroupBox->addWidget(OkButton_,2,2,1,2); //adding okay button to the grid
    FirstBetPrompt_->setLayout(InternalGridInsideGroupBox);

}

//drawing Hit and Stay prompt
void Window::DrawHitNStayPrompt(){

    HitNStayPrompt_ = new QGroupBox;  //starting a group box
    QGridLayout *InternalGridInsideGroupBox = new QGridLayout; //creating a grid to put within the box

    //creating static heading to show current bet while deciding hit or stay
    InternalGridInsideGroupBox->addWidget(SetStaticHeading("Current Bet","white",15,"black"),0,0,1,3);
    CurrentBetInfoLabel_ = new QLabel(); //setting up CurrentBetInfoLabel dynamic label
    SetDynamicHeading(CurrentBetInfoLabel_, CurrentBet_, "white",15,"black");
    InternalGridInsideGroupBox->addWidget(CurrentBetInfoLabel_,0,3,1,1);

    //Adding Hit and Stay Button
    InternalGridInsideGroupBox->addWidget(SetStaticHeading("Make Your Move!","black",15,"orange"),1,0,1,4); 
    HitButton_ = new QPushButton("Hit");
    HitButton_->setStyleSheet("font-size : 15px; font-weight : bold; color : green");
    StayButton_ = new QPushButton("Stay");
    StayButton_->setStyleSheet("font-size : 15px; font-weight : bold; color : red");

    InternalGridInsideGroupBox->addWidget(HitButton_,2,0,1,2); //Adding Hit Button to internal grid
    InternalGridInsideGroupBox->addWidget(StayButton_,2,2,1,2); //Adding Stay Button to internal grid
    
    HitNStayPrompt_->setLayout(InternalGridInsideGroupBox); //Adding grid to the group box
}

//Drawing the message box prompt that shows the message on winning and loosing
void Window::DrawMessageBoxPrompt(){
    
    MessageBoxPrompt_ = new QGroupBox;  //starting a group box
    QGridLayout *InternalGridInsideGroupBox = new QGridLayout; //creating a grid to put within the box

    //Adding the message box that will show the if the player won or lost
    MessageLabel_ = new QLabel();
    MessageLabel_->setText("You won!");
    MessageLabel_->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);//setting alignment of the label, line below setting text format
    MessageLabel_->setStyleSheet("background-color : black ; font-size : 25 px; font-weight : bold; color : white");

    QLabel *AskForNextGame = new QLabel();
    AskForNextGame->setText("Next game?");
    AskForNextGame->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);//setting alignment of the label, line below setting text format
    AskForNextGame->setStyleSheet("background-color : black ; font-size : 20 px; font-weight : bold; color : white");

    YesButton_ = new QPushButton("Yes");
    YesButton_->setStyleSheet("font-size : 15px; font-weight : bold; color : green");

    InternalGridInsideGroupBox->addWidget(MessageLabel_,0,0,1,1);
    InternalGridInsideGroupBox->addWidget(AskForNextGame,1,0,1,1);
    InternalGridInsideGroupBox->addWidget(YesButton_,2,0,1,1);

    //setting up CurrentBetInfoLabel dynamic label
    MessageBoxPrompt_->setLayout(InternalGridInsideGroupBox); //Adding grid to the group box

}