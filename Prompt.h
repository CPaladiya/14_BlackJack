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


class Prompt{

Prompt(QWidget *parent = nullptr){}; //cpnstructor

public:

void DrawHitNStayPrompt(); //draws gropbox and stores it to variable HitNStayPrompt_
void DrawFirstBetPrompt(); //draws gropbox and stores it to variable FirstBetPrompt_
void DrawOneNElevenPrompt(); //draws groupbox and stores it to variable OneNElevenPrompt_
void DrawFundPrompt(QString Participant, QLabel *FundLabel, QString FontColor, QString BackGroundColor);//draws the fund info boxes for dealer and player
//Setting title tile format - font, color, details etc. MainTiles are only where cards will appear - true for IFMainTile for those only
void SetDynamicHeading(QLabel *LabelToCreate, QString StringToShow, QString FontColor, int FontSize, QString BackGroundColor); 
QLabel *SetStaticHeading(QString StringToShow, QString FontColor, int FontSize, QString BackGroundColor); 

//Group box variables ------------
QGroupBox *HitNStayPrompt_; //variable to store Hit and Stay option box QGroupBox
QGroupBox *FirstBetPrompt_; //variable to store First bet option box
QGroupBox *OneNElevenPrompt_; //Variable to store one and eleven value for Ace box
QGroupBox *PlayersFundPrompt_; //variable to store Players Fund prompt
QGroupBox *DealersFundPrompt_; //variable to store Dealers Fund Prompt

//buttons and spinbox variables ---------------------
QSpinBox *BetBox;//variable to store Betbox where user can select the bet amount
QPushButton *OkButton; //variable to store Ok button for the first bet option
QPushButton *HitButton; //variable to store hit button
QPushButton *StayButton; //variable to store stay button
QPushButton *OneButton; //variable to store "one" button for Ace value
QPushButton *ElevenButton; //variable to store "eleven" button for the Ace value

//Variables for label that needs to be updated dynamically -------------------
QLabel *WhoIsPlayingInfo; //variable to store info on who is currently playing
QLabel *PlayersFundInfo; //Current Fund of the player
QLabel *DealersFundInfo; //Current Fund of the Dealer
QLabel *StatusOfGameInfo; //Current status of the game
QLabel *CurrentBetInfo; //Current bet info label

//regular variables ----------------------------
int CurrentBet_{0}; //variable to store current bet amount
int DealersFund_{100000}; //Dealers fund
int PlayersFund_{5000}; //Players fund


};

#endif