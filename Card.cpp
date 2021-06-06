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

Card::Card(QWidget *parent = nullptr) : QLabel(parent), CardName_("TT"){

    QPixmap loadedImage("/home/cpaladiya/My_prog_projects/14_BlackJack/cards/"+CardName_+".png"); //loading the image
    CardImage_ = new QLabel();//creating a new label
    int LabelHeight = CardImage_->height();
    int LabelWidth = CardImage_->width();
    CardImage_->setPixmap(loadedImage.scaled(LabelWidth/4,LabelHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation));

}

void Card::ReloadTrueCard (QString NewCardQString){

    //clearing the previous content of the blank image label and setting the newCard instead
    CardImage_->clear();
    CardName_ = NewCardQString;
    QPixmap loadedImage("/home/cpaladiya/My_prog_projects/14_BlackJack/cards/"+CardName_+".png"); //loading the image
    int LabelHeight = CardImage_->height();
    int LabelWidth = CardImage_->width();
    CardImage_->setPixmap(loadedImage.scaled(LabelWidth/4,LabelHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    //animating the new card for fade-in effect
    QGraphicsOpacityEffect *effect = new QGraphicsOpacityEffect(this);
    CardImage_->setGraphicsEffect(effect);
    QPropertyAnimation *aniamteCard = new QPropertyAnimation(effect,"opacity");
    aniamteCard->setDuration(1000);
    aniamteCard->setStartValue(0);
    aniamteCard->setEndValue(1);
    aniamteCard->setEasingCurve(QEasingCurve::InBack);
    aniamteCard->start(QPropertyAnimation::DeleteWhenStopped);

    //refreshing the card value as per new card
    RefreshCardValue();

}

//it will help fetch the card value depending on the name of the card
void Card::RefreshCardValue(){

    vector<QString> CardValueNumber {"2","3","4","5","6","7","8","9"};

    if (CardName_[0] == "1"){
        CardValue_ = 11; //if ace we will set card value to 11
    }
    else if(count(CardValueNumber.begin(),CardValueNumber.end(), CardName_[0])){
        CardValue_ = CardName_[0].digitValue(); //converting Qstring char to int
    }
    else{
        CardValue_ = 10;
    }
}

