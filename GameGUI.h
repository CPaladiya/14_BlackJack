#ifndef GAMEGUI_H
#define GAMEGUI_H

#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QPushButton>

class Window : public QWidget{

    Q_OBJECT;

public:
    Window(QWidget *parent = nullptr);

private:
    QGroupBox *DealersBox();
    QGroupBox *PlayersBox();
    QGroupBox *DealerFundBox();
    QGroupBox *PlayerFundBox();
    QGroupBox *WhoIsPlayingBox();
    QGroupBox *ActionBox();
};

#endif

