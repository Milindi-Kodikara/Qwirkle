#ifndef ASSIGN2_GAMEENGINE_H
#define ASSIGN2_GAMEENGINE_H

#include <string>
#include "Tile.h"
#include "LinkedList.h"
#include "Position.h"


class GameEngine
{
    GameEngine();
    GameEngine(std::string fileName);

    /*Get the input line
    Validate by checking if it matches the existing commands
    Convert the objects as necessary i.e Tiles and stuff and validate


    1.Check if the line length i.e 2 or 4  words in the array
    If 2 --> replace or save
    Check the first word and compare etc

    2.Convert the string tile to Tile etc
    3.Check the player hand etc.
    4.Call required functions

    */

    void getInputFromPlayer();

    //Display current game state
    /*
     * Print out the details
     */
    void displayGameState();


    /*
     Loop until the user inputs the command for quitting
     The Tile that we are passing isn't a new Tile, it's the actual Tile
     Return true if the tile is placed
     */
    bool placeTile(Tile* tile, Position position);
    void replaceTile(Tile* tile);
    void saveGame(std::string fileName);


private:
    //2D array of tiles as board 26*26
    Tile*** board;
    LinkedList tileBag;
    LinkedList playerOneHand;
    LinkedList playerTwoHand;

    int playerOneScore;
    int playerTwoScore;
    bool playerOneTurn;

    std::string playerOneName;
    std::string playerTwoName;

};

#endif // ASSIGN2_GAMEENGINE_H