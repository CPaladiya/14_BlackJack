#include "GameGUI.h"

#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QPushButton>

Window::Window(QWidget *parent) : QWidget(parent){

    QGridLayout *GameGrid = new QGridLayout;
    GameGrid->addWidget(DealersBox(),0,0,2,3);
    GameGrid->addWidget(PlayersBox(),2,0,2,3);
    GameGrid->addWidget(DealerFundBox(),0,3,1,1);
    GameGrid->addWidget(PlayerFundBox(),1,3,1,1);
    GameGrid->addWidget(WhoIsPlayingBox(),2,3,1,1);
    GameGrid->addWidget(ActionBox(),3,3,1,1);

    setLayout(GameGrid);
    setWindowTitle(tr("Black Jack Game"));
    resize(1200,800);


}

QGroupBox *Window::DealersBox(){

    QGroupBox *DealerGroupBox = new QGroupBox;  //creating a group box
    QGridLayout *InternalBox = new QGridLayout; //creating a grid to put within the box
    QPushButton *sampleBut1 = new QPushButton("Dealer Sample1"); //creating first button
    QPushButton *samplebut2 = new QPushButton("Dealer Sample2"); //creating Second button
    InternalBox->addWidget(sampleBut1,0,0,1,1); //Adding first button to grid
    InternalBox->addWidget(samplebut2,1,0,5,1); //Adding second button to grid
    DealerGroupBox->setLayout(InternalBox); //Adding grid to the group box

    return DealerGroupBox;

}


QGroupBox *Window::PlayersBox(){

    QGroupBox *PlayerGroupBox = new QGroupBox;  //creating a group box
    QGridLayout *InternalBox = new QGridLayout; //creating a grid to put within the box
    QPushButton *sampleBut1 = new QPushButton("Player Sample1"); //creating first button
    QPushButton *samplebut2 = new QPushButton("Player Sample2"); //creating Second button
    InternalBox->addWidget(sampleBut1,0,0,1,1); //Adding first button to grid
    InternalBox->addWidget(samplebut2,1,0,5,1); //Adding second button to grid
    PlayerGroupBox->setLayout(InternalBox); //Adding grid to the group box

    return PlayerGroupBox;

}

QGroupBox *Window::DealerFundBox(){

    QGroupBox *DealerFundBox = new QGroupBox;  //creating a group box
    QGridLayout *InternalBox = new QGridLayout; //creating a grid to put within the box
    QPushButton *sampleBut1 = new QPushButton("Player Sample1"); //creating first button
    QPushButton *samplebut2 = new QPushButton("Player Sample2"); //creating Second button
    InternalBox->addWidget(sampleBut1,0,0); //Adding first button to grid
    InternalBox->addWidget(samplebut2,1,0); //Adding second button to grid
    DealerFundBox->setLayout(InternalBox); //Adding grid to the group box

    return DealerFundBox;

}

QGroupBox *Window::PlayerFundBox(){

    QGroupBox *PlayerFundBox = new QGroupBox;  //creating a group box
    QGridLayout *InternalBox = new QGridLayout; //creating a grid to put within the box
    QPushButton *sampleBut1 = new QPushButton("Player Sample1"); //creating first button
    QPushButton *samplebut2 = new QPushButton("Player Sample2"); //creating Second button
    InternalBox->addWidget(sampleBut1,0,0); //Adding first button to grid
    InternalBox->addWidget(samplebut2,1,0); //Adding second button to grid
    PlayerFundBox->setLayout(InternalBox); //Adding grid to the group box

    return PlayerFundBox;

}

QGroupBox *Window::WhoIsPlayingBox(){

    QGroupBox *WhoIsBox = new QGroupBox;  //creating a group box
    QGridLayout *InternalBox = new QGridLayout; //creating a grid to put within the box
    QPushButton *sampleBut1 = new QPushButton("Player Sample1"); //creating first button
    QPushButton *samplebut2 = new QPushButton("Player Sample2"); //creating Second button
    InternalBox->addWidget(sampleBut1,0,0); //Adding first button to grid
    InternalBox->addWidget(samplebut2,1,0); //Adding second button to grid
    WhoIsBox->setLayout(InternalBox); //Adding grid to the group box

    return WhoIsBox;

}


QGroupBox *Window::ActionBox(){

    QGroupBox *ActionBox = new QGroupBox;  //creating a group box
    QGridLayout *InternalBox = new QGridLayout; //creating a grid to put within the box
    QPushButton *sampleBut1 = new QPushButton("Player Sample1"); //creating first button
    QPushButton *samplebut2 = new QPushButton("Player Sample2"); //creating Second button
    InternalBox->addWidget(sampleBut1,0,0); //Adding first button to grid
    InternalBox->addWidget(samplebut2,1,0); //Adding second button to grid
    ActionBox->setLayout(InternalBox); //Adding grid to the group box

    return ActionBox;

}






//int main(int argc, char *argv[]){



//}
