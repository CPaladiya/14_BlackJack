#include "GameGUI.h"

#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QPushButton>

Window::Window(QWidget *parent) : QWidget(parent){

    QGridLayout *GameGrid = new QGridLayout;
    GameGrid->addWidget(CardBox("Dealer"),0,0,2,3);
    GameGrid->addWidget(CardBox("Player"),2,0,2,3);
    GameGrid->addWidget(FundBox("Dealer"),0,3,1,1);
    GameGrid->addWidget(WhoIsPlayingBox(),1,3,1,1);
    GameGrid->addWidget(FundBox("Player"),2,3,1,1);
    GameGrid->addWidget(ActionBox(),3,3,1,1);

    setLayout(GameGrid);
    setWindowTitle(tr("Black Jack Game"));
    resize(1200,800);
}

//Generates main Card tiles where cards will appear for both, dealer and player
QGroupBox *Window::CardBox(QString participant){
    
    QGroupBox *MainBox = new QGroupBox;  //creating a main group box
    QGridLayout *InternalBox = new QGridLayout; //creating a grid to put within the box
    QPushButton *sampleBut1 = new QPushButton(participant); //creating first button
    QPushButton *samplebut2 = new QPushButton(participant); //creating Second button
    InternalBox->addWidget(sampleBut1,0,0,1,1); //Adding first button to grid
    InternalBox->addWidget(samplebut2,1,0,5,1); //Adding second button to grid
    MainBox->setLayout(InternalBox); //Adding grid to the group box

    return MainBox;

}

QGroupBox *Window::FundBox(QString participant){

    QGroupBox *MainBox = new QGroupBox;  //creating a group box
    QGridLayout *InternalBox = new QGridLayout; //creating a grid to put within the box
    QPushButton *sampleBut1 = new QPushButton(participant); //creating first button
    QPushButton *samplebut2 = new QPushButton(participant); //creating Second button
    InternalBox->addWidget(sampleBut1,0,0); //Adding first button to grid
    InternalBox->addWidget(samplebut2,1,0); //Adding second button to grid
    MainBox->setLayout(InternalBox); //Adding grid to the group box

    return MainBox;

}

QGroupBox *Window::WhoIsPlayingBox(){

    QGroupBox *MainBox = new QGroupBox;  //creating a group box
    QGridLayout *InternalBox = new QGridLayout; //creating a grid to put within the box
    QPushButton *sampleBut1 = new QPushButton("Player Sample1"); //creating first button
    QPushButton *samplebut2 = new QPushButton("Player Sample2"); //creating Second button
    InternalBox->addWidget(sampleBut1,0,0); //Adding first button to grid
    InternalBox->addWidget(samplebut2,1,0); //Adding second button to grid
    MainBox->setLayout(InternalBox); //Adding grid to the group box

    return MainBox;

}

QGroupBox *Window::ActionBox(){

    QGroupBox *MainBox = new QGroupBox;  //creating a group box
    QGridLayout *InternalBox = new QGridLayout; //creating a grid to put within the box
    QPushButton *sampleBut1 = new QPushButton("Player Sample1"); //creating first button
    QPushButton *samplebut2 = new QPushButton("Player Sample2"); //creating Second button
    InternalBox->addWidget(sampleBut1,0,0); //Adding first button to grid
    InternalBox->addWidget(samplebut2,1,0); //Adding second button to grid
    MainBox->setLayout(InternalBox); //Adding grid to the group box

    return MainBox;

}