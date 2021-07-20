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
    CardImageQLabel_ = new QLabel();//creating a new label

}

Card::~Card(){}

//Function to reload the true card using given argument of QString
void Card::ReloadTrueCard (QString NewCardQString){

    //clearing the previous content of the blank image label and setting the newCard instead

    CardImageQLabel_->clear(); //Clearing of the previous blank image, so the size will remain same just the content is cleared
    CardName_ = NewCardQString;
    QPixmap loadedImage("/home/cpaladiya/My_prog_projects/14_BlackJack/cards/"+CardName_+".png"); //loading the image
    //Defining variables to resize the image according to the size of the label itself
    int LabelHeight = CardImageQLabel_->height(); //setting height and width of QLabel
    int LabelWidth = CardImageQLabel_->width();
    //Setting Pixmap to the QLabel
    CardImageQLabel_->setPixmap(loadedImage.scaled(LabelWidth,LabelHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation)); //

    //Fade in animation for newly loaded card
    FadeInAnimation();
    //refreshing the card value as per new card name.
    //storing the value of card .i.e 11 for Ace, 2 for 2 of Hearts and 10 for any face values
    //For example, "3D.jpg", CardName_ would be "3D" and its value will be 3
    RefreshCardValue();

}

//animating the new card for fade-in effect
void Card::FadeInAnimation(){

    QGraphicsOpacityEffect *effect = new QGraphicsOpacityEffect(this); //Adding new opacity effect
    CardImageQLabel_->setGraphicsEffect(effect); //Setting that effect to the card image
    QPropertyAnimation *aniamteCard = new QPropertyAnimation(effect,"opacity"); //adding new animation property and its effect
    aniamteCard->setDuration(1200); //Setting how long will be the effect in ms
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
    aniamteCard->setDuration(1200); //Setting how long will be the effect in ms
    aniamteCard->setStartValue(1); //amount of opacity at start
    aniamteCard->setEndValue(0); //amount of opacity at end
    aniamteCard->setEasingCurve(QEasingCurve::InBack); //smoothness of the transition
    aniamteCard->start(QPropertyAnimation::DeleteWhenStopped); //Deleting Animation property once used

}

//it will help fetch the card value depending on the name of the card
void Card::RefreshCardValue(){

    vector<QString> CardValueNumber {"2","3","4","5","6","7","8","9"};
    //Comparing first letter of the CardName_ to determine the card value
    if (CardName_[0] == "1"){
        CardValue_ = 11; //if ace we will set card value to 11
    }
    else if (CardName_[0] == "0" ){
        CardValue_ = 0; //If dummy blank card or closed card, value will be 0
    }//Now, we will loop through all the number in CardValueNumber to see if the value CardName_[0] is in it, 
    //if it is not, it will return 0 which means false. Otherwise it would be a number other than 0
    //and it will act as True
    else if(count(CardValueNumber.begin(),CardValueNumber.end(), CardName_[0])){
        CardValue_ = CardName_[0].digitValue(); //converting Qstring char to int
    }
    else{
        CardValue_ = 10; //For any face value other than Ace, its 10
    }
}

