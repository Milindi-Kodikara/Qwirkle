# APT-Assignment-2
## Description
A console based version of the game Qwirkle made by me and 3 other RMIT students. The rules are mostly identical to those found [here](https://www.ultraqwirkle.com/game-rules.php) except that only one tile can be placed at a time. The game can host up to 12 players, and any of those players can be chosen to be an AI with a difficulty rating of EASY, MEDIUM or HARD.
## Running and playing
The program can be built from the console with the makefile, using the command "make" while inside the directory. The program can then be run using "./qwirkle". 

After navigating through the main menu and setting up a game, actions can be taken by entering specific commands: 
* "place X at Y" will place a tile X from your hand onto position Y (where the position is a letter number pair, eg. B5). 
* "replace X" will replace a tile in your hand with another tile from the bag. 
* "quit" will quit the game. 
* A game can also be saved to a file during a player's turn by using "save X" where X is a text filename, which can then be loaded later on from the main menu.
