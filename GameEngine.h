#ifndef ASSIGN2_GAMEENGINE_H
#define ASSIGN2_GAMEENGINE_H

#include <string>
#include <random>
#include "Tile.h"
#include "LinkedList.h"
#include "Position.h"
#include "Player.h"

#define MAX_BOARD_SIZE  26
#define INITIAL_BOARD_SIZE 5
#define MAX_PLAYERS 12

struct Placement
{
	Placement(Tile* tile, int x, int y, int score, bool qwirkle)
		: tile{ tile }, x{ x }, y{ y }, score{ score }, qwirkle{ qwirkle }{}

	static bool compare(Placement& p1, Placement& p2)
	{
		return p1.score < p2.score;
	}

	Tile* tile;
	int x;
	int y;
	int score;
	bool qwirkle;
};

class GameEngine
{
public:
	/*
	 * Initialises the GameEngine's state from scratch, and then 
	 * begins the game
	 */
	void newGame();

	/*
	 * Requests a file name from the user, uses the contents
	 * to initialise the game state and then continues with the
	 * game. If the file does not exist or the format is invalid,
	 * then the load is aborted. Returns whether the load was 
	 * successful
	 */
    bool loadGame();

	/*
	 * Contains the main game loop, displaying the game state, performing
	 * the current player's turn, checking for a stalemate, and then 
	 * repeating until the game is over
	 */
	void runGame();


	/*
	 * Checks if a stalemate has occured, and if it has ends the game
	 */
	void stalemateCheck();

	/*
	 * Prompts the player for input, then processes and validates the
	 * syntax of the supplied command, calling the requisite functions
	 * and passing them the parsed values if valid, and re-prompting the
	 * user for input if it is invalid
	 */
    void getInput();

	/*
	 * Returns a string that contains the formatted representation of the
	 * board, with either the full board or the shrunk version and with 
	 * colour or no colour depending on the parameters supplied
	 */
	std::string boardToString(bool colouredOutput, bool fullBoard);

	/*
	 * Adjusts the position of all the tiles in the board, as well as viewX
	 * and viewY to accommodate for a tile placed at the supplied position,
	 * ensuring a single space border around the edge of the board if possible
	 */
	void adjustBoard(Position position);


	/*
	 * Used to shrink the board as small as possible after loading in a game
	 */
	void shrinkBoard();

    /*
     * Prints out the current player's name, each player's score, the current 
	 * board state and the current player's hand
     */
    void displayGameState();

	/*
	 * Completes an AI player's turn (explained exactly how in the report)
	 */
	void processAITurn();

	/*
	 * Tests if the specified tile can be placed at the specified postition,
	 * return the resulting score if it can and returning 0 if it can't. The
	 * qwirkle parameter is updated if the placement would result in a qwirkle
	 */
	int testPlacement(Tile* tile, Position position, bool& qwirkle);

	/*
	 * Returns a vector containing all possible placements of the supplied 
	 * set of tiles
	 */
	std::vector<Placement> findPossiblePlacements(std::vector<Tile*> tiles);

    /*
     * Attempts to remove the specified tile from the current player's 
	 * hand and place it on the board in the specified postion, calculating
	 * and adding points to the current player's total if the placement is 
	 * successful, and then adding a new tile to the player's hand from the
	 * bag. If the tile is not contained within the player's hand or the 
	 * placement is invalid, then the function returns false
     */
    bool placeTile(std::string tileLabel, std::string positionLabel);

	/*
	 * Attemps to remove the specified tile from the current player's hand,
	 * place it back in the bag, and add a new tile from the bag to the
	 * player's hand. If the tile is not contained within the player's hand
	 * then the function returns false
	 */
    bool replaceTile(std::string tileLabel);

	/*
	 * Opens the specified file and saves within it the number of players,
	 * each player's name, score, hand and difficulty, the board state, the
	 * tilebag, and the name of the current player
	 */
    void saveGame(std::string fileName);

	/*
	 * Used to print out the game over message, final game state and scores,
	 * and name the winning player
	 */
	void gameOver();

	~GameEngine();


private:
	// 2D array of tile pointers
    Tile*** board;
    LinkedList tileBag;
	std::vector<Player*> players;
	int playerTurnIndex;

	// Holds the current display dimensions of the board
	int viewX;
	int viewY;
	
	bool firstTile;
	bool exitGame;
};

#endif // ASSIGN2_GAMEENGINE_H