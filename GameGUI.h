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

    //Setting labels whose values are subject to change
    void SetDynamicHeading(QLabel *LabelToPopulate, QString StringToShow, QString FontColor, int FontSize, QString BackGroundColor); 
    QLabel *SetStaticHeading(QString StringToShow, QString FontColor, int FontSize, QString BackGroundColor); 

    //Functions to draw all the boxes in GUI
    QGroupBox *DrawFundPrompt(QString Participant, int FundVar, QString FontColor, QString BackGroundColor);//draws the fund InfoLabel boxes for dealer and player
    void DrawHitNStayPrompt(); //draws gropbox and stores it to variable HitNStayPrompt_
    void DrawFirstBetPrompt(); //draws gropbox and stores it to variable FirstBetPrompt_



    //Main Game Grid variable that houses all the QGroupBox variables
    QGridLayout *GameGrid_;

    //CardsField Class two instances for each player and dealer
    CardsField Player_;
    CardsField Dealer_;

    //Group box variables ------------
    QGroupBox *DealersCardPrompt_; //variable to store Dealers card box
    QGroupBox *PlayersCardPrompt_; //variable to store Players Card box
    QGroupBox *HitNStayPrompt_; //variable to store Hit and Stay option box QGroupBox
    QGroupBox *FirstBetPrompt_; //variable to store First bet option box
    QGroupBox *PlayersFundPrompt_; //variable to store Players Fund prompt
    QGroupBox *DealersFundPrompt_; //variable to store Dealers Fund Prompt

    //buttons and spinbox variables ---------------------
    QSpinBox *BetBox;//variable to store Betbox where user can select the bet amount
    QPushButton *OkButton; //variable to store Ok button for the first bet option
    QPushButton *HitButton; //variable to store hit button
    QPushButton *StayButton; //variable to store stay button

    //Variables for label that needs to be updated dynamically -------------------
    QLabel *PlayersFundInfoLabel; //Current Fund of the player
    QLabel *DealersFundInfoLabel; //Current Fund of the Dealer
    QLabel *CurrentBetInfoLabel; //Current bet InfoLabel label

    //regular variables ----------------------------
    int CurrentBet_{0}; //variable to store current bet amount
    int DealersFund_{100000}; //Dealers fund
    int PlayersFund_{5000}; //Players fund

};

#endif