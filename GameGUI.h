#ifndef GAMEGUI_H
#define GAMEGUI_H

#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QPushButton>
#include <vector>
#include <QTextStream>
#include <QLabel>
#include <QMutex>
#include <QSound>
#include <QSpinBox>
#include <iostream>
#include <QTextStream>
#include <QThread>
#include <QTimer>
#include "CardsField.h"

using namespace std;

//class definition of Window object
class Window : public QWidget{

    Q_OBJECT;

public:

    Window(QWidget *parent = nullptr); //constructor
    ~Window();

    ////################## ------------  part of GameGUI.cpp -----Func to Draw GUI ------------ ############# //

    //Drawing labels
    void SetDynamicHeading(QLabel *LabelToPopulate, int FundVariable, QString FontColor, int FontSize, QString BackGroundColor); //Setting labels whose values are subject to change
    QLabel *SetStaticHeading(QString StringToShow, QString FontColor, int FontSize, QString BackGroundColor); //Setting labels whose values are static 

    //Functions to draw all the boxes in GUI
    void DrawAllPrompts(); //method to draw all the prompts that has not yet added to windows
    void AddPromptToWindow(); //method to add all drawn prompts to game window
    QGroupBox *DrawFundPrompt(QString Participant, int &FundVar, QString FontColor, QString BackGroundColor);    //draws the fund InfoLabel boxes for dealer and player
    void DrawScoreBoard();//draws the score board for current game
    void DrawHitNStayPrompt(); //draws gropbox and stores it to variable HitNStayPrompt_
    void DrawFirstBetPrompt(); //draws gropbox and stores it to variable FirstBetPrompt_
    void DrawMessageBoxPrompt(); //draws the message box showing winning or loosing status of player

    //Main Game Grid variable that houses all the QGroupBox variables
    QGridLayout *GameGrid_;

    //CardsField Class two instances for each player and dealer
    CardsField *Player_;
    CardsField *Dealer_;
    QMutex mutex_;

    //Group box variables ------------
    QGroupBox *DealersCardPrompt_; //variable to store Dealers card box
    QGroupBox *PlayersCardPrompt_; //variable to store Players Card box
    QGroupBox *PlayersFundPrompt_; //variable to store Players Fund prompt
    QGroupBox *DealersFundPrompt_; //variable to store Dealers Fund Prompt
    QGroupBox *ScoreBoardPrompt_; //Blackjack score board for current game
    QGroupBox *HitNStayPrompt_; //variable to store Hit and Stay option box QGroupBox
    QGroupBox *FirstBetPrompt_; //variable to store First bet option box
    QGroupBox *MessageBoxPrompt_; //variable to store message of "Won"/"Lost"

    //Variables for label that needs to be updated dynamically -------------------
    QLabel *PlayersFundInfoLabel_; //Current Fund of the player
    QLabel *DealersFundInfoLabel_; //Current Fund of the Dealer
    QLabel *CurrentBetInfoLabel_; //Current bet InfoLabel label
    QLabel *MessageLabel_;//Message box variable will fetch this QLabel
    QLabel *PlayerScore_;//Player Score QLabel
    QLabel *DealerScore_;//Dealer Score QLabel

    //regular variables ----------------------------
    int CurrentBet_; //variable to store current bet amount
    int DealersFund_; //Dealers fund
    int PlayersFund_; //Players fund
    int TimeInBetweenCards_; //setting time in beetween cards to showup in ms
    int BlinkDelay_; //setting for blinking of scores/tiles after card is beggining to fade in

    //buttons and spinbox variables ---------------------
    QSpinBox *BetBox_;//variable to store Betbox where user can select the bet amount
    QPushButton *OkButton_; //variable to store Ok button for the first bet option
    QPushButton *HitButton_; //variable to store hit button
    QPushButton *StayButton_; //variable to store stay button
    QPushButton *YesButton_; //Variable to store yes button for the next game

    //################## ------------  part of GameLogic.cpp ----- GUI Slots and functions ------------ ############# //
    
    //Refresh value function to update socors/Fund as game moves on
    void ChangeBet(int NewBetValue); //Changing the current bet value using Betbox QSpinbox button
    void ReducePlayersFundForBet(); //Reducing players fund by some amount
    void RefreshCurrentBet(); //Refresh the current bet shown in window
    void RefreshPlayerScore(); //Refresh the score being shown in window for player
    void RefreshDealerScore(); //Refresh the score being shown in window for dealer
    void RefreshPlayersFund(); //Refreshing the fund shown in window for player
    void RefreshDealersFund(); //Refreshing the fund shown in window for Dealer

    //Hide and show various prompts
    void HideFirstBetPrompt(); //Hide First Bet prompt
    void ShowFirstBetPrompt(); //Showing the first bet prompt
    void HideHitNStayPrompt(); //Hiding the Hit and stay prompt
    void ShowHitNStayPrompt(); //Showing the Hit and Stay Prompt
    void HideMessageBoxPrompt(); //Hide message box showing messages on game status
    void ShowMessageBoxPrompt(); //show message box showing messages on game status

    //GameLogic Functions - Functions implemented to run the game
    void StartFirstGame(); //Starting the game with showing first two cards for players
    void StartTableSetupPlayer(); //Setting up first two cards for player
    void ShowPlayersCard(); //Showing next card of the player
    void CheckIfBlackJackOrBurst(); //After dealing the first two cards we will check if its a blackjack or burst, if not move on the game
    void StartTableSetupDealer(); //Setting up first two cards for Dealer
    void ShowDealersCard(); //Showing next card of the dealer
    void DealersTurn();//Now dealer will count his score
    void TurnDealersSecondCard(); //Turning dealers second card at the end of the game
    void EndGame(); //Ending the game once player has pressed "Stay"
    void CompareScoresAndMoveOn(); //Function to compare scores and act accordingly
    void ScoreAfterGame(); //Refreshes score after game and hides/shows relevant prompts
    void ResetGame(); //Resetting the game once the game is over
    void DoNothingForSecond(){} //Just a place holder to delay the showing of card for a second

    //Game status functions
    void PlayerHasBlackJack(); //Changing funds of player and dealer if player has a blackjack
    void PlayerWon(); //Changing funds of player and dealer if player won
    void PlayerLost(); //Changing funds of player and dealer if player won
    void GameDraw(); //Game draw if player and dealer has the same score

    //################## ------------  part of Blink.cpp ----- Blinking animations on score update ------------ ############# //

    //Blinking animation func for various tiles
    void PlayerScoreYellowTile(); //Tile to blink with yellow color backgound
    void DealerScoreYellowTile(); //Tile to blink with yellow color backgound
    void ScoreDefaultTile(); //Tile to blink for default color for score
    void PlayerScoreUpdateBlink(); //Player score update blink
    void DealerScoreUpdateBlink(); //Dealer score update blink
    void FundRedTile(); //Tile to blink with Red color background
    void FundGreenTile(); //Tile to blink with Green color background
    void FundDefaultTile(); //Default color
    void PlayerWonFundBlink(); //Player winning status blink
    void PlayerLostFundBlink(); //Player loosing status blink
    void MessgaePromptGreenTile(); //Tile to blink with green color background
    void MessgaePromptRedTile(); //Tile to blink with green color background
    void MessgaePromptDefaultTile(); //Tile to blink with green color background
    void PlayerWonBlink(); //Player winning status blink
    void PlayerBlackJackBlink(); //Player winning black jack blink
    void PlayerLostBlink(); //Player loosing status blink
    void GameDrawBlink(); //Game draw blink

};

#endif