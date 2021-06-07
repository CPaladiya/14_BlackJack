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

    void ReloadTrueCard(QString NewCardQString); //Func to store new card and remove the old blank image
    void RefreshCardValue();//refreshing the card value as per new CardName_
    
    //Var of the Card class
    QLabel *CardImageQLabel_; //Main QLabel of the instance
    int CardValue_; //storing the value of card .i.e 11 for Ace, 2 for 2 of Hearts and 10 for any face values
    QString CardName_; //storing the name of the card i.e "1J" from "1J.PNG"

};

#endif