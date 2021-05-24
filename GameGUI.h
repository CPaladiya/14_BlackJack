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

using namespace std;

class Window : public QWidget{

    Q_OBJECT;

public:

    Window(QWidget *parent = nullptr);

    enum Status {Playing, Bust, BlackJack, YouWin, Reset}; //status of the player
    enum PromptStatus {FirstBet, OneNEleven, HitNStay}; //Which prompt do we have running currently

    std::mutex mutex;

    int GetDealerFund(){ return DealerFund_;} //Function to get dealers fund
    int GetPlayerFund(){ return PlayerFund_;} //Function to get players fund
    void SetDealerFund(int Fund) { DealerFund_ = Fund;} //Function to set Dealers Fund
    void SetPlayerFund(int Fund) { PlayerFund_ = Fund;} //Function to set Players Fund
    QString GetCurrentPlayer() {return CurrentPlayer_;} //Function to know who is playying currently
    void ToggleCurrentPlayer(); //Function to toggle the current player
    QString GetStatus(){return CurrentStatus_;}; //Function to get the current status of the player
    Status GetEnumStatus(){return EnumCurrentStatus_;} //Function to return enum status of the current game
    void SetStatus(Status StatusOfPlayer); //Function to set the current status of the player
    
    //setting the bet amount while making sure it is not read wrong by subsequent function
    void SetBet(){
        mutex.lock();
        CurrentBet_ = BetBox_->value();
        cout << "CurrentBet Value : \n" << CurrentBet_;
        PlayerFund_ = PlayerFund_ - CurrentBet_; //removing bet money from player's fund
        mutex.unlock();
    }
    int GetBet(){
        std::this_thread::sleep_for(chrono::microseconds(500));
        return CurrentBet_;
    }

    //Set Prompt Status Hit N Stay
    void SetPromptStatusHitNStay(){
        mutex.lock();
        CurrentPrompt_ = PromptStatus::HitNStay;
        mutex.unlock();
    }
    //Set Prompt Status One N Eleven
    void SetPromptStatusOneNEleven(){
        mutex.lock();
        CurrentPrompt_ = PromptStatus::OneNEleven;
        mutex.unlock();
    }
    //Get Prompt Status
    PromptStatus GetPromptStatus(){
        std::this_thread::sleep_for(chrono::microseconds(500));
        return CurrentPrompt_;
    }
    //set Action box to show nothing
    void SetActionBoxNull(){
        ActionBox_ = nullptr;
    }


private:

    
    QGroupBox *CardBox(QString participant, QString FontColor); //Generates main Card tiles where cards will appear for both, dealer and player
    QGroupBox *FundBox(QString participant, QString FontColor, int Fund); //Generates smaller tiles on right side where fund will appear
    QGroupBox *WhoIsPlayingBox(); // Generates smaller tile on right side showing who is playing and the message
    void StartActionBox(); //Generates smaller tile on right side where prompt will be given for user to act on
    QGroupBox *GetFirstBet();
    QGroupBox *GetHitNStay();
    QGroupBox *GetOneNEleven();



    int DealerFund_;
    int PlayerFund_{5000};
    QString CurrentPlayer_;
    QString CurrentStatus_;
    Window::Status EnumCurrentStatus_{Status::Playing};
    int CurrentBet_{0};
    int PlayerAceValue{11};
    int DealerAceValue{11};
    QGridLayout *GameGrid_;
    QGroupBox *ActionBox_; //Box that will hold value of FirstBet, HitNStay and OneNEleven as needed
    QGroupBox *DealersFundBox_; //Box that will Fund value for Dealer
    QGroupBox *PlayersFundBox_; //Box that will Fund value for Player
    PromptStatus CurrentPrompt_{PromptStatus::FirstBet};
    QLabel *SetTileTitle(QString participant, QString FontColor, int FontSize, QString BackGroundColor, bool IfMainTile); //set title of main tiles
    QSpinBox *BetBox_; //BetBox will be the one holding value for our first bet and will help assign the value of CurrentBet_
};

#endif

