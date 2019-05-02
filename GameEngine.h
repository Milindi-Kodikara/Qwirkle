#ifndef ASSIGN2_GAMEENGINE_H
#define ASSIGN2_GAMEENGINE_H

#include <string>
#include "Tile.h"
#include "LinkedList.h"
#include "Position.h"


class GameEngine
{
public:
	/*
	 * Initialises the GameEngine's state from scratch, and then 
	 * begins the game
	 */
	GameEngine();

	/*
	 * Initialises the GameEngine's state from the provided file,
	 * and then begins the game
	 */
    GameEngine(std::string fileName);

	/*
	 * Contains the main game loop, performing each player's turn
	 * until the game ends
	 */
	void runGame();

	/*
	 * Prompts the player for input, then processes and validates the
	 * supplied command, calling corresponding function if the input
	 * is valid. If the input is invalid, the player is re-prompted for
	 * input until valid input is supplied
	 */
    void getInput();

	/*
	 * Returns a string that contains the formatted representation of the
	 * board as detailed in the assignment specification
	 */
	std::string boardToString();

    /*
     * Prints out the details of the current game state as specified in
	 * the assignment specification
     */
    void displayGameState();

    /*
     * Attempts to remove the specified tile from the current player's 
	 * hand and place it on the board in the specified postion, calculating
	 * and adding points to the current player's total if the placement is 
	 * successful, and then adding a new tile to the player's hand from the
	 * bag. If the tile is not contained within the player's hand or the 
	 * placement is invalid, then the function returns false
     */
    bool placeTile(std::string tile, std::string position);

	/*
	 * Attemps to remove the specified tile from the current player's hand,
	 * place it back in the bag, and add a new tile from the bag to the
	 * player's hand. If the tile is not contained within the player's hand
	 * then the function returns false
	 */
    bool replaceTile(std::string tile);

	/*
	 * Opens the specified file and saves within it the current game state
	 * using the format specified in the assignment specification
	 */
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