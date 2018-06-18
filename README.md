<a href="http://www.youtube.com/watch?feature=player_embedded&v=A-xpt22AKas" target="_blank"><img src="http://img.youtube.com/vi/A-xpt22AKas/0.jpg" 
alt="IMAGE ALT TEXT HERE" width="820" height="480" border="10" /></a>

===============================================================================

Object Oriented Programming ; 2018 b

Project : Michael Shriki , Kfir Matityahu

This program is an end of Semester OOP Course

We make a ButtleShip MultiPlayer Game.

===============================================================================

Files: 
--------------------------------
(^ X : inheritance from Class X)

Menu.h & Menu.cpp:

an abstract class for the Menus.

OptionMenu.h & OptionMenu.cpp	

Handle the option menu.(^ Menu)

MainMenu.h & MainMenu.cpp

Handle the main menu.(^ Menu)

PauseMenu.h & PauseMenu.cpp

Handle the pause menu.(^ Menu)

ChooseGameTypeMenu.h & ChooseGameTypeMenu.cpp

Handle the on-line or local play menu.(^ Menu)

ChooseReadyMenu.h & ChooseReadyMenu.cpp

Handle the predefined map for game.(^ Menu)

EndGameMenu.h & EndGameMenu.cpp

Handle the end of game.(^ Menu)

HelpMenu.h & HelpMenu.cpp

Handle the help menu.(^ Menu)

MapMenu.h & MapMenu.cpp

Handle the choosing map menu.(^ Menu)

MenuButton.h & MenuButton.cpp		

an abstract class for menu Buttons.

ImageMenuButton.h &	ImageMenuButton.cpp	

Button with image.(^ MenuButton)

OptionButton.h & OptionButton.cpp	

Button with multi options.(^ MenuButton)

TextMenuButton.h & TextMenuButton.cpp	

Button with Text.(^ MenuButton)

Player.h & Player.cpp

an abstract class for Players.

AiRival.h & AiRival.cpp

Handle computer player rival.(^ Player)

MultiPlayer.h &	MultiPlayer.cpp

Handle On-line player rival.(^ Player)

SinglePlayer.h & SinglePlayer.cpp

Handle the Player.(^ Player)

Ship.h & Ship.cpp

an abstract class for Ships.(^ Ship)

ButtleShip6.h & ButtleShip6.cpp

6 Size ship.(^ Ship)

ButtleShip4.h & ButtleShip4.cpp

4 Size ship.(^ Ship)

ButtleShip2.h & ButtleShip2.cpp

2 Size ship.(^ Ship)

Editor.h & Editor.cpp

an abstract class for MapEditor.

Editor2D.h & Editor2D.cpp

Handle 2D Editor.(^ Editor)

Editor3D.h & Editor3D.cpp

Handle 3D Editor.(^ Editor)

Board.cpp & Board.h:

Handle the game board.

Button.h & Button.cpp

Handle Editor Buttons.

Chat.h & Chat.cpp

Handle Game Chat communication.

ChatBox.h & ChatBox.cpp

Handle Chat behavior.

EditorControler.h & EditorControler.cpp

Handle Editor.

EditorMenu.h & EditorMenu.cpp

Handle EditorMenu.

Game.h & Game.cpp

Engine of the Game.
 
Language.h & Language.cpp

Manage languages.

Map.h & Map.cpp

Handle the map of the Player.

ShipFactory.h & ShipFactory.cpp

Handle ship creator (Factory design pattern).

TextBox.h & TextBox.cpp

Handle EditorButton text box.

SrcManager.cpp & SrcManager.h:

The source manager for all the images & font (Singleton design pattern).

AudioManager.h & AudioManager.cpp

The source manager for all the Sounds & Music (Singleton design pattern).

settings.h

Defines the game settings. 

utilities.h

Contains utilities for the game. 

===============================================================================

Data Structures:
-------------------------------

Vector for all Game Texture (Singleton)

Array for Map 

Stack for Menus

Map for ChatServer Clients

Vector for GameServer Clients

Map for ShipFactory (Factory)

===============================================================================

Remarkable Algorithms:
--------------------------------

All communication with the server and data transfer.

===============================================================================

Known bugs:
--------------------------------

None.

===============================================================================

Other Notes:
--------------------------------

On-line Game support. 

To play on-line make sure that there is someone else to play with you, 

otherwise after 30 seconds the server will disconnect you automatic,

(if there are no server running you will disconnect yourself after 30 seconds).

**Make sure that the server run and you have his IP and port's on your server.txt file.

**On the Server Program make sure you enter the correct port's on the port.txt file.

***There is a running Server on Microsoft Azure until April 2019 his IP & port's are included.

We provide an Installer for the Game and for the Server programs.

Hebrew & English supported.

Windows SDK used in program is 16299

E N J O Y!!
===============================================================================
