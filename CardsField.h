#ifndef CARDSFIELD_H
#define CARDSFIELD_H

#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QLabel>
#include <vector>
#include <QTextStream>
#include <QGroupBox>

using namespace std;

class CardsField : public QGroupBox{

    Q_OBJECT

public:
    explicit CardsField(const QString participant, QWidget *parent = nullptr);

    //func
    void ResetCardDeck();//Resetting the card deck for next play
    void GetNextCardQString();//Getttin the random QString for next card


    int totalScore; // will store the total score of the card for instance
    static vector<QString> CardDeck_; //static variable that will hold all the cards and will
    //be loaded as soon as the first instance of the card is created
    QString WhoIsIt; //who is this instance belongs to? "Player" or "Dealer"
    //Vector will be used to repopulate CardDeck_
    vector<QString> NewDeck_ {"1C","1D","1H","1S","2C","2D","2H","2S",
                              "3C","3D","3H","3S","4C","4D","4H","4S",
                              "5C","5D","5H","5S","6C","6D","6H","6S",
                              "7C","7D","7H","7S","8C","8D","8H","8S",
                              "9C","9D","9H","9S","XC","XD","XH","XS",
                              "JC","JD","JH","JS","QC","QD","QH","QS",
                              "KC","KD","KH","KS"};

    //this will be used as index to get next card from CardDeck_
    int NextCardIndex{0};

}


#endif //CARDSFIELD_H