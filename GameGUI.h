#ifndef GAMEGUI_H
#define GAMEGUI_H

#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QPushButton>
#include <vector>
#include <QTextStream>
#include <QLabel>

using namespace std;

class Window : public QWidget{

    Q_OBJECT;
    enum Color {Red, Green}; //enum color used in defining color of the tile headings

public:
    Window(QWidget *parent = nullptr);

private:
    QGroupBox *CardBox(QString participant, QString color); //Generates main Card tiles where cards will appear for both, dealer and player
    QGroupBox *FundBox(QString participant); //Generates smaller tiles on right side where fund will appear
    QGroupBox *WhoIsPlayingBox(); // Generates smaller tile on right side showing who is playing and the message
    QGroupBox *ActionBox(); //Generates smaller tile on right side where prompt will be given for user to act on
};

#endif

