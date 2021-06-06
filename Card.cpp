#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QLabel>
#include <QTextStream>
#include "Card.h"

Card::Card(QWidget *parent = nullptr) : QLabel(parent), CardName_("TT"){

    QPixmap loadedImage("/home/cpaladiya/My_prog_projects/14_BlackJack/cards/"+CardName_+".png"); //loading the image
    CardImage_ = new QLabel();//creating a new label
    int LabelHeight = CardImage_->height();
    int LabelWidth = CardImage_->width();
    CardImage_->setPixmap(loadedImage.scaled(LabelWidth/4,LabelHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation));

}

void Card::ReloadTrueCard (QString NewCardQString){

    CardImage_

}

