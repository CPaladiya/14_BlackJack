#ifndef CARD_H
#define CARD_H

#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QLabel>
#include <QTextStream>

QTextStream out(stdout);

class Card : public QLabel{
    
    Q_OBJECT

public:
    explicit Card(QWidget *parent = nullptr);


    //Func of the Card class
    //void AnimateCard_FadeIn(); //Func to "Fade-in" animate current instance
    //void AnimateCard_FadeOut(); //Func to "Fade-out" animate current instance
    void ReloadTrueCard(QString NewCardQString); //Func to store new card and remove the old stock image
    void SetAceOne(); //Setting ACE card value to 1
    void SetAceEleven(); //Setting ACE card value to 11
    void RefreshCardValue();//refreshing the card value as per new CardName_
    
    //Var of the Card class
    QLabel *CardImage_;
    int CardValue_; //storing the value of card 
    //bool IsItAce_; //will store if the card is Ace
    QString CardName_;



}

#endif //CARD_H