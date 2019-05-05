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
    //TODO
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
    //TODO
}

bool GameEngine::placeTile(std::string tileLabel, std::string positionLabel)
{
	bool success = false;
   	Player* player = player1Turn ? player1 : player2;
	Position* position;
	Tile* tile = player->hand.find(tileLabel);

	if (tile != nullptr)
	{
		position = Position::labelToPosition(positionLabel);

		if(position != nullptr)
		{
			if(board[position->x][position->y] == nullptr)
			{
				//Indicates whether the surrounding tiles allow the placement
				// of the supplied tile
				bool valid = true;
				Position offsets[4];

				//translation up
				offsets[0].x = 0;
				offsets[0].y = -1;

				//translation right
				offsets[1].x = 1;
				offsets[1].y = 0;

				//translation down
				offsets[2].x = 0;
				offsets[2].y = 1;

				//translation left
				offsets[3].x = -1;
				offsets[3].y = 0;

				//Indicates whether the corresponding offset position contains
				//a valid tile that the supplied tile can be connected to
				bool connected[4] = {false, false, false, false};


				for (int i = 0; i < 4 && valid; i++)
				{
					Position tempPosition = *position + offsets[i];
					if (tempPosition.x < BOARD_SIZE && tempPosition.x >= 0
						&& tempPosition.y < BOARD_SIZE && tempPosition.y >= 0)
					{
						Tile* tempTile = board[tempPosition.x][tempPosition.y];

						if (tempTile != nullptr)
						{
							//Checks whether the two tiles only have one type of similarity
							if ((tile->colour == tempTile->colour) !=
								(tile->shape == tempTile->shape))
							{
								connected[i] = true;
							}
							else
							{
								valid = false;
							}
						}
					}
				}

				if (valid)
				{
					//Starts with 1 for the tile itself
					int score = 1;
					//Keeps track of how many valid tiles are within the segment
					int qwirkleCount = 0;
					bool qwirkle = false;

					for (int i = 0; i < 4; i++)
					{
						//TODO : check opposite segments for tile similarity
						//TODO : Possibility of multiple qwirkles
						if(connected[i])
						{
							//Indicates if there is a tile in tempPosition
							bool empty = false;
							Position tempPosition = *position + offsets[i];
							while (!empty && valid && tempPosition.x < BOARD_SIZE && tempPosition.x >= 0
								   && tempPosition.y < BOARD_SIZE && tempPosition.y >= 0)
							{
								Tile* tempTile = board[tempPosition.x][tempPosition.y];
								if(tempTile != nullptr)
								{
									if ((tile->colour == tempTile->colour) &&
										(tile->shape == tempTile->shape))
									{
										valid = false;
									}
									else
									{
										score++;
										qwirkleCount++;
									}
								}
								else empty = true;

								tempPosition += offsets[i];

								if(qwirkleCount == 6)
								{
									qwirkle = true;
									score += 6;
								}
							}
						}
					}

					if (valid)
					{
						//If tile is part of a vertical and horizontal
						// segment score is increased by 1
						if ((connected[0] || connected[2]) && (connected[1] || connected[3]))
						{
							score++;
						}
						player->hand.remove(tile);
						board[position->x][position->y] = tile;

						Tile* newTile = tileBag.pop_front();
						if (newTile != nullptr)
						{
							player->hand.add_back(newTile);
						}
						success = true;
					}
				}
			}
		}
	}

	delete position;
	return success;

}

bool GameEngine::replaceTile(std::string tileLabel)
{
    bool replaced = false;

    if (playerOneTurn == true)
    {
        if (playerOneHand.remove(playerOneHand.find(tileLabel)) == true)
        {
            playerOneHand.add_back(tileBag.pop_front());

            replaced = true;
        }
    }
    else
    {
        if (playerTwoHand.remove(playerTwoHand.find(tileLabel)) == true)
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