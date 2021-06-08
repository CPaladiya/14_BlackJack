#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QLabel>
#include <QTextStream>
#include <QtWidgets/QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <vector>
#include <algorithm>
#include "Card.h"

using namespace std;

Card::Card(QWidget *parent) : 
    QLabel(parent), CardName_("00"), CardValue_(0) {

    QPixmap loadedImage("/home/cpaladiya/My_prog_projects/14_BlackJack/cards/"+CardName_+".png"); //loading the image
    CardImageQLabel_ = new QLabel();//creating a new label
    int LabelHeight = CardImageQLabel_->height();
    int LabelWidth = CardImageQLabel_->width();
    CardImageQLabel_->setPixmap(loadedImage.scaled(LabelWidth/5,LabelHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation));

}

Card::~Card(){}

void Card::ReloadTrueCard (QString NewCardQString){

    //clearing the previous content of the blank image label and setting the newCard instead
    CardImageQLabel_->clear();
    CardName_ = NewCardQString;
    QPixmap loadedImage("/home/cpaladiya/My_prog_projects/14_BlackJack/cards/"+CardName_+".png"); //loading the image
    int LabelHeight = CardImageQLabel_->height();
    int LabelWidth = CardImageQLabel_->width();
    CardImageQLabel_->setPixmap(loadedImage.scaled(LabelWidth/5,LabelHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    FadeInAnimation();
    //refreshing the card value as per new card
    RefreshCardValue();

}

//animating the new card for fade-in effect
void Card::FadeInAnimation(){

    QGraphicsOpacityEffect *effect = new QGraphicsOpacityEffect(this); //Adding new opacity effect
    CardImageQLabel_->setGraphicsEffect(effect); //Setting that effect to the card image
    QPropertyAnimation *aniamteCard = new QPropertyAnimation(effect,"opacity"); //adding new animation property and its effect
    aniamteCard->setDuration(1000); //Setting how long will be the effect in ms
    aniamteCard->setStartValue(0);//amount of opacity at start
    aniamteCard->setEndValue(1); //amount of opacity at end
    aniamteCard->setEasingCurve(QEasingCurve::InBack); //smoothness of the transition
    aniamteCard->start(QPropertyAnimation::DeleteWhenStopped); //Deleting Animation property once used

}

//animating the new card for fade-out effect
void Card::FadeOutAnimation(){

    QGraphicsOpacityEffect *effect = new QGraphicsOpacityEffect(this);//Adding new opacity effect
    CardImageQLabel_->setGraphicsEffect(effect); //Setting that effect to the card image
    QPropertyAnimation *aniamteCard = new QPropertyAnimation(effect,"opacity");//adding new animation property and its effect
    aniamteCard->setDuration(1000); //Setting how long will be the effect in ms
    aniamteCard->setStartValue(1); //amount of opacity at start
    aniamteCard->setEndValue(0); //amount of opacity at end
    aniamteCard->setEasingCurve(QEasingCurve::InBack); //smoothness of the transition
    aniamteCard->start(QPropertyAnimation::DeleteWhenStopped); //Deleting Animation property once used

}

//it will help fetch the card value depending on the name of the card
void Card::RefreshCardValue(){

    vector<QString> CardValueNumber {"2","3","4","5","6","7","8","9"};

    if (CardName_[0] == "1"){
        CardValue_ = 11; //if ace we will set card value to 11
    }
    else if (CardName_[0] == "T"){
        CardValue_ = 0;
    }
    else if(count(CardValueNumber.begin(),CardValueNumber.end(), CardName_[0])){
        CardValue_ = CardName_[0].digitValue(); //converting Qstring char to int
    }
    else{
        CardValue_ = 10;
    }
}

