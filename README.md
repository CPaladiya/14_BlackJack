# 14_BlackJack
## What is it?
It is a GUI based card game developed using C++ and Qt5

## How is the code structured?
There are three different classes being used here. 
<ul>
<li> First, instance of a class <code>Window</code> derived from <code>QObject</code> class of Qt5 houses the main window prompt which enables player to play the game. </li>
<li> Second, <code>CardsField</code>, derived from <code>QGroupBox</code> class, is the class which holds four cards for player and dealer, each will have its own instance of this class. It is the place where fade in and fade out of cards will appear while playing game. </li>
<li> Third, <code>Card</code>, derived from <code>QLabel</code> class, is the class, whoes instance holds individual card and its value. It also includes method to Fade-In and Fade-Out cards. </li>
