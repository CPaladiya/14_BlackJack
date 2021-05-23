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

using namespace std;

class Window : public QWidget{

    Q_OBJECT;

public:
    Window(QWidget *parent = nullptr);

    enum Status{Playing, Bust, BlackJack, YouWin, Reset}; //status of the player

    int GetDealerFund(){ return DealerFund_;} //Function to get dealers fund
    int GetPlayerFund(){ return PlayerFund_;} //Function to get players fund
    void SetDealerFund(int Fund) { DealerFund_ = Fund;} //Function to set Dealers Fund
    void SetPlayerFund(int Fund) { PlayerFund_ = Fund;} //Function to set Players Fund
    QString GetCurrentPlayer() {return CurrentPlayer_;} //Function to know who is playying currently
    void ToggleCurrentPlayer(); //Function to toggle the current player
    QString GetStatus(){return CurrentStatus_;}; //Function to get the current status of the player
    Status GetEnumStatus(){return EnumCurrentStatus_;} //Function to return enum status of the current game
    void SetStatus(Status StatusOfPlayer); //Function to set the current status of the player


private:
    QLabel *SetTileTitle(QString participant, QString FontColor, int FontSize, QString BackGroundColor, bool IfMainTile); //set title of main tiles
    QGroupBox *CardBox(QString participant, QString FontColor); //Generates main Card tiles where cards will appear for both, dealer and player
    QGroupBox *FundBox(QString participant, QString FontColor, int Fund); //Generates smaller tiles on right side where fund will appear
    QGroupBox *WhoIsPlayingBox(); // Generates smaller tile on right side showing who is playing and the message
    QGroupBox *ActionBox(); //Generates smaller tile on right side where prompt will be given for user to act on

    int DealerFund_;
    int PlayerFund_;
    QString CurrentPlayer_;
    QString CurrentStatus_;
    Window::Status EnumCurrentStatus_{Status::Playing};
    int CurrentBet_{100};
    int PlayerAceValue{11};
    int DealerAceValue{11};
};

#endif

