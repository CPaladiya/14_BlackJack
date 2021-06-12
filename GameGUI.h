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

    //Setting labels whose values are subject to change
    void SetDynamicHeading(QLabel *LabelToPopulate, int FundVariable, QString FontColor, int FontSize, QString BackGroundColor);
    //Setting labels whose values are static 
    QLabel *SetStaticHeading(QString StringToShow, QString FontColor, int FontSize, QString BackGroundColor); 

    //Functions to draw all the boxes in GUI
    void DrawAllPrompts(); //method to draw all the prompts that has not yet added to windows
    void AddPromptToWindow(); //method to add all drawn prompts to game window
    //draws the fund InfoLabel boxes for dealer and player
    QGroupBox *DrawFundPrompt(QString Participant, int &FundVar, QString FontColor, QString BackGroundColor);
    void DrawScoreBoard();//draws the score board for current game
    void DrawHitNStayPrompt(); //draws gropbox and stores it to variable HitNStayPrompt_
    void DrawFirstBetPrompt(); //draws gropbox and stores it to variable FirstBetPrompt_
    void DrawMessageBoxPrompt(); //draws the message box showing winning or loosing status of player

    //Main Game Grid variable that houses all the QGroupBox variables
    QGridLayout *GameGrid_;

    //CardsField Class two instances for each player and dealer
    CardsField *Player_;
    CardsField *Dealer_;

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

    //buttons and spinbox variables ---------------------
    QSpinBox *BetBox_;//variable to store Betbox where user can select the bet amount
    QPushButton *OkButton_; //variable to store Ok button for the first bet option
    QPushButton *HitButton_; //variable to store hit button
    QPushButton *StayButton_; //variable to store stay button

    //################## ------------  GUI Slots and functions ------------ ############# //

    //GameLogic Functions - Functions implemented to run the game
    void StartFirstGame(); //Starting the game with showing first two cards for players
    void RevealPlayersCard(); //Reveal first two players card and check for blackjack
    void RefreshPlayersFund(); //Refreshing the fund shown in window for player
    void RefreshDealersFund(); //Refreshing the fund shown in window for Dealer
    void RefreshCurrentBet(); //Refresh the current bet shown in window
    void RefreshPlayerScore();//Refresh the score being shown in window for player
    void RefreshDealerScore();//Refresh the score being shown in window for dealer
    void EndGame(); //Ending the game once player has pressed "Stay"
    void ResetGame(); //Resetting the game once the game is over
    void PlayerHasBlackJack(); //Changing funds of player and dealer if player has a blackjack
    void PlayerWon(); //Changing funds of player and dealer if player won
    void PlayerLost(); //Changing funds of player and dealer if player won
    void GameDraw();//Game draw if player and dealer has the same score
    void CompareScoresAndMoveOn(); //Function to compare scores and act accordingly

    public slots:

    void ChangeBet(int NewBetValue);//Changing the current bet value using Betbox QSpinbox button
    void ReducePlayersFundForBet();//Reducing players fund by some amount
    void HideHitNStayPrompt(); //Hiding the Hit and stay prompt
    void ShowHitNStayPrompt(); //Showing the Hit and Stay Prompt
    void HideFirstBetPrompt(); //Hide First Bet prompt
    void ShowFirstBetPrompt(); //Showing the first bet prompt
    void HideMessageBoxPrompt();//Hide message box showing messages on game status
    void ShowMessageBoxPrompt();//show message box showing messages on game status
    void ShowPlayersCard();//Showing next card of the player
    void ShowDealersCard();//Showing next card of the dealer
    void StartTableSetupPlayer();//Setting up first two cards for player
    void StartTableSetupDealer();//Setting up first two cards for Dealer
    void CheckIfBlackJack();//After dealing the first two cards we will check if its a blackjack, if not move on the game

};

#endif