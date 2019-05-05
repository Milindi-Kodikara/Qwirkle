#include "GameEngine.h"
#include <iostream>
#include <sstream>
#include <vector>

GameEngine::GameEngine()
{
    //TODO
}

GameEngine::GameEngine(std::string fileName)
{
    //TODO
}

std::string GameEngine::boardToString()
{
	std::string output = "   ";

	Tile boardPiece = NULL;

	for (int header = 0; header < 26; header++)
	{
		output += std::to_string(header) + " ";
	}

	output += "\n  -"

	for (int dash = 0; dash < 26; dash++)
	{
		output += "---"
	}

	for (int y = 0; y < 26; y++)
	{
		char ch = char(65 + y);
		output += "\n" + ch + " |"

		for (int x = 0, x < 26, x++)
		{
			boardPiece = board[x][y];
			if (boardPiece == NULL) {
				output += "  |"
			}
			else
			{
				output += boardPiece->label + "|"
			}
		}
	}

	return output;
}

void GameEngine::displayGameState()
{
    //TODO
}

void GameEngine::getInput()
{
	bool valid = false;
	while (!valid)
	{
		std::cout << "> ";
		std::string input;
		std::getline(std::cin, input);

		// Causes the game to exit if eof is encountered
		if (std::cin.eof())
		{
			exitGame = true;
			valid = true;
		}

		if (input.size() != 0)
		{
			std::vector<std::string> commands;
			std::istringstream is(input);
			std::string word;

			// Splits the input line insto individual words
			// and puts them into a vector
			while (is >> word) commands.push_back(word);

			// Checks whether the correct number of words was inputted
			if (commands.size() == 2)
			{
				if (commands[0] == "replace")
				{
					// Input is valid if the action was successful
					valid = replaceTile(commands[1]);
				}
				else if (commands[0] == "save")
				{
					// Input is valid if the action was successful
					valid = saveGame(commands[1]);
				}
			}
			else if (commands.size() == 4)
			{
				if (commands[0] == "place" && commands[2] == "at")
				{
					// Input is valid if the action was successful
					valid = placeTile(commands[1], commands[3]);
				}
			}
		}

		if (!valid) std::cout << "Invalid input" << std::endl;
	}
}

void GameEngine::displayGameState()
{
	LinkedList playerHand = NULL;
	

	if (playerOneTurn == true)
	{
		playerHand = playerOneHand;
		std::cout << playerOneName << ", it's your turn"<< endl;

	}
	else 
	{
		playerHand = playerTwoHand;
		std::cout << playerTwoName << ", it's your turn" << endl;
	}

	std::cout << "Score for " << playerOneName << ": " << playerOneScore << endl;
	std::cout << "Score for " << playerTwoName << ": " << playerTwoScore << endl;

	std::cout << boardToString;

	printf("\n\nYour hand is\n");
	playerHand.display();
}

bool GameEngine::placeTile(std::string tile, std::string position)
{
    //TODO
}

bool GameEngine::replaceTile(std::string tile)
{
    bool replaced = false;

    if (playerOneTurn == true)
    {
        if (playerOneHand.remove(playerOneHand.find(tile)) == true)
        {
            playerOneHand.add_back(tileBag.pop_front());

            replaced = true;
        }
    }
    else
    {
        if (playerTwoHand.remove(playerTwoHand.find(tile)) == true)
        {
            playerTwoHand.add_back(tileBag.pop_front());

            replaced = true;
        }
    }

    return replaced;
}

void GameEngine::runGame()
{
    //TODO
}

bool GameEngine::saveGame(std::string fileName)
{
    //TODO
}