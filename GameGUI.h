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
#include <mutex>
#include <chrono>
#include <thread>
#include "CardsField.h"

using namespace std;

//class definition of Window object
class Window : public QWidget{

    Q_OBJECT;

public:

    Window(QWidget *parent = nullptr); //constructor
    ~Window();

    //Setting labels whose values are subject to change
    void SetDynamicHeading(QLabel *LabelToPopulate, int &FundVariable, QString FontColor, int FontSize, QString BackGroundColor);
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

    //GameLogic Functions - Functions implemented to run the game
    void ChangeBet(int NewBetValue);//Changing the current bet value using Betbox QSpinbox button
    void ReducePlayersFundForBet();//Reducing players fund by some amount
    void StartFirstGame();
    void StartTableSetUp();
    void RevealPlayersCard();
    void EndGame();
    void ResetGame();

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


    //buttons and spinbox variables ---------------------
    QSpinBox *BetBox_;//variable to store Betbox where user can select the bet amount
    QPushButton *OkButton_; //variable to store Ok button for the first bet option
    QPushButton *HitButton_; //variable to store hit button
    QPushButton *StayButton_; //variable to store stay button

    //Variables for label that needs to be updated dynamically -------------------
    QLabel *PlayersFundInfoLabel_; //Current Fund of the player
    QLabel *DealersFundInfoLabel_; //Current Fund of the Dealer
    QLabel *CurrentBetInfoLabel_; //Current bet InfoLabel label

    //regular variables ----------------------------
    int CurrentBet_; //variable to store current bet amount
    int DealersFund_; //Dealers fund
    int PlayersFund_; //Players fund

};

#endif