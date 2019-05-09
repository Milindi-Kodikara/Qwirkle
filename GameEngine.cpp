#include "GameEngine.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <unordered_set>

void GameEngine::newGame()
{
    std::string player1Name;
    std::string player2Name;
    //regex to ensure player name is only uppercase alphabets
    std::regex r("[a-zA-Z\\s]+");
    std::smatch m;
    std::cout << "Starting a new game" << std::endl;

    //prompts the user again if the given name does not follow the regex
    while (!std::regex_search(player1Name,m,r)
    {
        std::cout << "Enter a name for player 1 (no numbers or symbols)" << std::endl;
        std::getline(std::cin, player1Name);
    }
    player1->name = player1Name;

    while (!std::regex_search(player2Name,m,r)
    {
        std::cout << "Enter a name for player 2 (no numbers or symbols)" << std::endl;
        std::getline(std::cin, player2Name);
    }
    player2->name = player2Name;

    //fill the tile bag
    tileBag.add_back()

    //distribute six tiles to each player

    std::cout << "Let's Play!" << std::endl;
    runGame();
}

void GameEngine::loadGame()
{
    //TODO
}

void GameEngine::runGame()
{
	while (!exitGame)
	{
		displayGameState();
		getInput();
	}
	std::cout << "Goodbye" << std::endl;
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
			if (commands.size() == 1)
			{
				if (commands[0] == "quit") exitGame = true;
			}
			else if (commands.size() == 2)
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

std::string GameEngine::boardToString()
{
	std::string output = "   ";

	Tile* boardPiece = nullptr;

	for (int header = 0; header < BOARD_SIZE; header++)
	{
		output += header + " ";
	}

	output += "\n  -";

	for (int dash = 0; dash < BOARD_SIZE; dash++)
	{
		output += "---";
	}

	for (int y = 0; y < BOARD_SIZE; y++)
	{
		char ch = 'A' + y;
		output += "\n";
		output += ch;
		output += " |";

		for (int x = 0; x < BOARD_SIZE; x++)
		{
			boardPiece = board[x][y];
			if (boardPiece == nullptr) {
				output += "  |";
			}
			else
			{
				output += boardPiece->label + "|";
			}
		}
	}

	return output;
}

void GameEngine::displayGameState()
{
	Player* player = player1Turn ? player1 : player2;

	std::cout << player->name << ", it's your turn" << std::endl;

	std::cout << "Score for " << player1->name << ": " << player->score << std::endl;
	std::cout << "Score for " << player2->name << ": " << player->score << std::endl;

	std::cout << boardToString();

	std::cout << "\n\nYour hand is" << std::endl;
	player->hand.display();
}

bool GameEngine::placeTile(std::string tileLabel, std::string positionLabel)
{
	bool success = false;
   	Player* player = player1Turn ? player1 : player2;
	Position* position;
	Tile* tile = player->hand.find(tileLabel);

	// Tile found in player's hand
	if (tile != nullptr)
	{
		position = Position::labelToPosition(positionLabel);

		// Position is within board bounds
		if(position != nullptr)
		{
			// Position on the board is empty
			if(board[position->x][position->y] == nullptr)
			{
				// Indicates whether the surrounding tiles allow the placement
				// of the supplied tile
				bool valid = true;
				Position offsets[4];

				// Translation up
				offsets[0].x = 0;
				offsets[0].y = -1;

				// Translation right
				offsets[1].x = 1;
				offsets[1].y = 0;

				// Translation down
				offsets[2].x = 0;
				offsets[2].y = 1;

				// Translation left
				offsets[3].x = -1;
				offsets[3].y = 0;

				// Indicates whether the corresponding offset tile is a valid connection
				bool connected[4] = { false, false, false, false };

				// Indicates each dimension's similarity type (colour or shape)
				bool verColourSimilarity = false;
				bool horColourSimilarity = false;

				for (int i = 0; i < 4 && valid; ++i)
				{
					Position offsetPosition = *position + offsets[i];
					if (offsetPosition.x < BOARD_SIZE && offsetPosition.x >= 0
						&& offsetPosition.y < BOARD_SIZE && offsetPosition.y >= 0)
					{
						Tile* currTile = board[offsetPosition.x][offsetPosition.y];

						if (currTile != nullptr)
						{
							// Checks whether the two tiles only have one type of similarity
							if ((tile->colour == currTile->colour) !=
								(tile->shape == currTile->shape))
							{
								connected[i] = true;
								if (i < 2)
								{
									// Sets the similarity type for the current diemsion
									(i == 0 ? verColourSimilarity : horColourSimilarity)
										= tile->colour == currTile->colour;
								}
								else
								{
									// If the opposite tile is also connected
									if (connected[i - 2])
									{
										// If the opposite tile has a different similarity type
										if ((i == 2 ? verColourSimilarity : horColourSimilarity)
											!= (tile->colour == currTile->colour)) valid = false;
									}
								}
							}
							else
							{
								valid = false;
							}
						}
					}
				}

				if (valid && (connected[0] || connected[1] || connected[2] || connected[3]))
				{
					// Score starts with 1 for the tile itself
					int score = 1;

					// Indicates which elements of the similarity type have been found
					// in each dimension
					std::unordered_set<int> verTypeSet;
					std::unordered_set<int> horTypeSet;
					verTypeSet.insert(verColourSimilarity ? tile->shape : tile->colour);
					horTypeSet.insert(horColourSimilarity ? tile->shape : tile->colour);

					for (int i = 0; i < 4 && valid; ++i)
					{
						if (connected[i])
						{
							Position currPosition = *position + offsets[i];
							while (valid && currPosition.x < BOARD_SIZE && currPosition.x >= 0
								&& currPosition.y < BOARD_SIZE && currPosition.y >= 0)
							{
								Tile* currTile = board[currPosition.x][currPosition.y];
								if (currTile != nullptr)
								{
									// Indicates the current dimension
									bool vertical = i % 2 == 0;

									// The type set for the current dimension
									std::unordered_set<int>& typeSet =
										(vertical ? verTypeSet : horTypeSet);

									// Indicates the current dimension's similarity type
									bool colorSimilarity =
										(vertical ? verColourSimilarity : horColourSimilarity);

									// Used to check for duplicate tiles in the segment
									int signature =
										(colorSimilarity ? currTile->colour : currTile->shape);

									// If a tile is found that is already contained 
									// within the segment
									if (typeSet.count(signature) != 0)
									{
										valid = false;
									}
									else
									{
										typeSet.insert(signature);
										++score;
									}

									currPosition += offsets[i];
								}
							}
						}
					}

					if (valid)
					{
						// If tile is part of a vertical and horizontal
						// segment score is increased by 1
						if (verTypeSet.size() > 0 && horTypeSet.size() > 0)
						{
							++score;
						}

						// Qwirkle checking
						bool qwirkle = false;
						if (verTypeSet.size() == 6)
						{
							score += 6;
							qwirkle = true;
						}
						if (horTypeSet.size() == 6)
						{
							score += 6;
							qwirkle = true;
						}
						if (qwirkle) std::cout << "QWIRKLE!!!" << std::endl;

						player->score += score;
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
    Player* player = player1Turn ? player1 : player2;
    Tile* tile = find(tileLabel);
    bool replaced = false;

    if (tile != nullptr)
    {
        player->hand.remove(tile);
        tileBag.add_back(tile);
        replaced = true;
    }
    return replaced;
}

bool GameEngine::saveGame(std::string fileName)
{
    //TODO
	return false;
}