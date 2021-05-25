#ifndef PROMPT_H
#define PROMPT_H

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
#include "GameGUI.h"

class Prompt {

public:


Prompt(){}; //cpnstructor (QWidget *parent) : QWidget(parent)
~Prompt();

void FirstSetUPDraw();
void DrawHitNStayPrompt(); //draws gropbox and stores it to variable HitNStayPrompt_
void DrawFirstBetPrompt(); //draws gropbox and stores it to variable FirstBetPrompt_
void DrawOneNElevenPrompt(); //draws groupbox and stores it to variable OneNElevenPrompt_
void DrawFundPrompt(QGroupBox *QBoxFund, QString Participant, QLabel *FundLabel, QString FontColor, QString BackGroundColor);//draws the fund InfoLabel boxes for dealer and player
void DrawCurrentPlayerPrompt();//Drawing current player prompt
//Setting title tile format - font, color, details etc. MainTiles are only where cards will appear - true for IFMainTile for those only
void SetDynamicHeading(QLabel *LabelToCreate, QString StringToShow, QString FontColor, int FontSize, QString BackGroundColor); 
QLabel *SetStaticHeading(QString StringToShow, QString FontColor, int FontSize, QString BackGroundColor); 

//Group box variables ------------
QGroupBox *HitNStayPrompt_; //variable to store Hit and Stay option box QGroupBox
QGroupBox *FirstBetPrompt_; //variable to store First bet option box
QGroupBox *OneNElevenPrompt_; //Variable to store one and eleven value for Ace box
QGroupBox *PlayersFundPrompt_; //variable to store Players Fund prompt
QGroupBox *DealersFundPrompt_; //variable to store Dealers Fund Prompt
QGroupBox *CurrentPlayerPrompt_;//Variable to store CurrentPlayer prompt

//buttons and spinbox variables ---------------------
QSpinBox *BetBox;//variable to store Betbox where user can select the bet amount
QPushButton *OkButton; //variable to store Ok button for the first bet option
QPushButton *HitButton; //variable to store hit button
QPushButton *StayButton; //variable to store stay button
QPushButton *OneButton; //variable to store "one" button for Ace value
QPushButton *ElevenButton; //variable to store "eleven" button for the Ace value

//Variables for label that needs to be updated dynamically -------------------
QLabel *WhoIsPlayingInfoLabel; //variable to store InfoLabel on who is currently playing
QLabel *PlayersFundInfoLabel; //Current Fund of the player
QLabel *DealersFundInfoLabel; //Current Fund of the Dealer
QLabel *StatusOfGameInfoLabel; //Current status of the game
QLabel *CurrentBetInfoLabel; //Current bet InfoLabel label
QLabel *CurrentPlayerInfoLabel;//Current player InfoLabel label
QLabel *CurrentStatusInfoLabel; //Current status InfoLabelr such as "bust" , "Win" , "Blackjack"

//regular variables ----------------------------
int CurrentBet_{0}; //variable to store current bet amount
int DealersFund_{100000}; //Dealers fund
int PlayersFund_{5000}; //Players fund
QString CurrentPlayer_{"Player"}; //Current player InfoLabelrmation
QString CurrentStatus_{"Game On!"};//Current Status of the game

};

#endif