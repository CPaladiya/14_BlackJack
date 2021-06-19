# 14_BlackJack
## What is it?
It is a GUI based card game called ***Black Jack*** developed using C++ and Qt5.</br>

## Files structure and its content
Here is the list of different files and information on what they contain:
<ul>
<li> <code>GameGUI.h</code>, Header file contains declaration of the class <code>Window</code> with functions responsible to draw and load widgets in main game window. It also contains declaration of the functions for game logic (defined in <code>GameLogic.cpp</code>), animation and sound effects (defined in <code>Blink.cpp</code>). </li>
<li> <code>GameGUI.cpp</code>, file contains definitions of the class <code>Window</code> and functions responsible to draw and load widgets in window. </li>
<li> <code>GameLogic.cpp</code>, file contains definitions of functions responsible to run the logic of the game **Black Jack**. </li>
<li> <code>Blink.cpp</code>, file contains definitions of functions responsible for blinking and sound effects. </li>
<li> <code>CardsField.h</code> and <code>CardsField.cpp</code>, file contains declaration and definition of class <code>CardsField</code>. It holds maximum 4 cards for individual participant and total score of an instance during the game. It also includes the Deck being used to get random cards out of it. </li>
<li> <code>Cards.h</code> and <code>Cards.cpp</code>, file contains declaration and definition of class <code>Card</code>. It holds image and value of an individual Card instance, and functions to apply Fade-In Fade-Out animation effect. </li> </ul> </br>

## How many classes are there?
There are three different classes being used here. 
<ul>
<li> First, the class <code>Window</code> is derived from <code>QObject</code> class of Qt5. Window class houses the main window prompt which enables player to play the game. <em>(NO.1 in the image below)</em> </li>
<li> Second, <code>CardsField</code>, derived from <code>QGroupBox</code> class, is the class which holds four cards for each, player and dealer, and each will have its own instance of this class. It is drawn and added in the main window of the game where fade in and fade out of cards will appear while playing game. <em>(NO.2 in the image below)</em> </li>
<li> Third, <code>Card</code>, derived from <code>QLabel</code> class, is the class, whoes instance holds individual image of the card, its name and its value. It also includes method to animate Fade-In and Fade-Out effects. <em>(NO.3 and NO.4 in the image below)</em> </li> </ul> </br>

![ImageA](Image/UseOfClassInstanceInGame.PNG) 

## Before we go look at the activity table, let's see the variable layout!

Here in the image, all the variables of <code>QGroupBox</code> and <code>QGridLayout</code> are placed in the GameGUI window. They hold relative values of class instance which may be refreshed as the game goes on. These are drawn and loaded with the constructor of <code>Window *window</code> object , as soon as the game is started. If more clarification is required look at the code between  </br>

![](Image/VariableInGame.jpg) </br>

https://github.com/CPaladiya/14_BlackJack/blob/458e3597828f7f070d637ef643651e88f652a973/GameGUI.cpp#L77-L84
