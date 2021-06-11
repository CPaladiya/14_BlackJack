#ifndef CARD_H
#define CARD_H

#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QLabel>
#include <QTextStream>
#include <QThread>

//QTextStream out(stdout);

class Card : public QLabel{
    
    Q_OBJECT

public:
    Card(QWidget *parent = nullptr);
    ~Card();

    void ReloadTrueCard(QString NewCardQString); //Func to store new card and remove the old blank image
    void RefreshCardValue();//refreshing the card value as per new CardName_
    void FadeInAnimation();//Animation for Card to Fade-in the window
    void FadeOutAnimation();//Animation for Card to Fade-out the window 
    
    //Var of the Card class
    QLabel *CardImageQLabel_; //Main QLabel of the instance
    QString CardName_; //storing the name of the card i.e "1J" from "1J.PNG"
    int CardValue_; //storing the value of card .i.e 11 for Ace, 2 for 2 of Hearts and 10 for any face values

};

#endif