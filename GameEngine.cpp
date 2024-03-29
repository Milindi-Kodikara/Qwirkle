#include "GameEngine.h"
#include "getline.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <regex>

using std::cout;
using std::endl;
using std::string;
using std::vector;

void GameEngine::newGame()
{
    // Initialises game state
	viewX = INITIAL_BOARD_SIZE;
	viewY = INITIAL_BOARD_SIZE;
    players = vector<Player*>();
	exitGame = false;
	playerTurnIndex = 0;
	firstTile = true;

	string input;
	int playerCount = 0;
    cout << "Starting a new game" << endl;

    while (playerCount < 2 || playerCount > MAX_PLAYERS)
    {
        cout << "How many players would you like?\n> ";
        getline(std::cin, input);
		if (std::regex_match(input, std::regex("[0-9]+")))
		{
			std::istringstream iss(input);
			iss >> playerCount;
		}
    }

    for (int i = 0; i < playerCount; i++)
    {
		input = "";
		string playerName = "";
		Difficulty difficulty = HUMAN;
        //prompts the user again if the given name does not follow the regex
        while (!std::regex_match(playerName, std::regex("[a-zA-Z]+")))
        {
            cout << "Enter a name for player " << i + 1 
				<< " (no numbers or symbols)\n> ";
            getline(std::cin, playerName);
        }
        while (input != "Y" && input != "N")
        {
            cout << "Would you like this player to be an AI? (Y/N)\n> ";
            getline(std::cin, input);
        }
        if (input == "Y")
        {
            while (input != "EASY" && input != "MEDIUM" && input != "HARD")
            {
                cout << "Select a difficulty (EASY, MEDIUM, HARD)\n> ";
                getline(std::cin, input);
            }
            if (input == "EASY")
            {
                difficulty = EASY;
            }
            if (input == "MEDIUM")
            {
				difficulty = MEDIUM;
            }
            if (input == "HARD")
            {
				difficulty = HARD;
            }
        }
        else if (input == "N")
        {
			difficulty = HUMAN;
        }
        players.push_back(new Player(playerName));
		players.back()->difficulty = difficulty;
    }

    //create an array to store all the colours
    char colours[6] = {'R', 'O', 'Y', 'G', 'B', 'P'};
    //create a temporary linked list
    LinkedList temp;
    int shapes = 6;
    //fill the temporary linked list with two of every tile
    for (int i = 0; i < 6; i++)
    {
        for (int j = 1; j <= shapes; j++)
        {
            temp.addBack(new Tile(colours[i], j));
            temp.addBack(new Tile(colours[i], j));
        }
    }

    std::random_device rd; // obtain a random number from hardware
    std::mt19937 eng(rd()); // seed the generator

    // randomly add tiles
    for (int i = 72; i > 0; i--)
    {
        std::uniform_int_distribution<> distr(0, i - 1);
        tileBag.addBack(temp.removeAt(distr(eng)));
    }
    //distribute six tiles to each player
    for (Player* player : players)
    {
        for (int i = 0; i < 6; ++i)
        {
            player->hand.addBack(tileBag.popFront());
        }
    }

    // Creates the empty board
    board = new Tile**[MAX_BOARD_SIZE];
    for (int i = 0; i < MAX_BOARD_SIZE; ++i)
    {
        board[i] = new Tile*[MAX_BOARD_SIZE];
        for (int j = 0; j < MAX_BOARD_SIZE; ++j)
        {
            board[i][j] = nullptr;
        }
    }
    cout << "Let's Play!" << endl;
    runGame();
}

bool GameEngine::loadGame()
{
	board = nullptr;
	exitGame = false;
	std::ifstream file;
	string input;
	bool valid = true;

	cout << "\nEnter the filename from which to load a game\n> ";

	getline(std::cin, input);
	file.open(input);

	//Check if file exists
	if (file)
	{
		getline(file, input);
		int numberOfPlayers;
		
		//Check if the first line is a vaild number of players
		if (!file.eof() && std::regex_match(input, std::regex("[0-9]+")))
		{
			std::istringstream(input) >> numberOfPlayers;
			if (numberOfPlayers < 2 || numberOfPlayers > MAX_PLAYERS)
			{
				cout << "\nInvalid file: invalid number of players" << endl;
				valid = false;
			}
		}
		else
		{
			cout << "\nInvalid file: invalid number of players" << endl;
			valid = false;
		}

		if (valid)
		{
			//Checks all player's information
			for (int i = 0; i < numberOfPlayers && valid; i++)
			{
				Player* player = nullptr;

				// Checks player name
				getline(file, input);
				if (!file.eof() && std::regex_match(input, std::regex("[a-zA-Z]+")))
				{
					player = new Player(input);
				}
				else
				{
					cout << "\nInvalid file: invalid player " << i + 1 << " name" 
						<< endl;
					valid = false;
				}

				// Checks player score
				if (valid)
				{
					getline(file, input);
					if (!file.eof() && std::regex_match(input, std::regex("[0-9]+"))) 
						std::istringstream(input) >> player->score;
					else
					{
						cout << "\nInvalid file: invalid player " << i + 1 
							<< " score" << endl;
						valid = false;
					}
				}

				// Checks player hand
				if (valid)
				{
					getline(file, input);
					if (!file.eof())
					{
						int tileCount = 0;
						for (unsigned int j = 0; j < input.size() && valid; j += 3)
						{
							Tile* tile = Tile::stringToTile(input[j], input[j + 1]);
							if (tile != nullptr)
							{
								player->hand.addBack(tile);
								++tileCount;
							}
							else
							{
								cout << "\nInvalid file: invalid player " << i + 1 
									<< " hand" << endl;
								valid = false;
							}
							if (tileCount > 6)
							{
								cout << "\nInvalid file: invalid player " << i + 1 
									<< " hand" << endl;
								valid = false;
							}
						}
					}
					else
					{
						cout << "\nInvalid file: invalid player " << i + 1 << " hand" 
							<< endl;
						valid = false;
					}
				}

				// Checks if player is an AI + difficulty
				if (valid)
				{
					getline(file, input);
					if (!file.eof())
					{
						if (input == "EASY") player->difficulty = EASY;
						else if (input == "MEDIUM") player->difficulty = MEDIUM;
						else if (input == "HARD") player->difficulty = HARD;
						else if (input == "HUMAN") player->difficulty = HUMAN;
						else
						{
							cout << "\nInvalid file: invalid player " << i + 1
								<< " difficulty" << endl;
							valid = false;
						}
					}
					else
					{
						cout << "\nInvalid file: invalid player " << i + 1
							<< " difficulty" << endl;
						valid = false;
					}
				}
				players.push_back(player);
			}
		}
		if (valid)
		{
			//Initialize the board
			board = new Tile**[MAX_BOARD_SIZE];
			for (int i = 0; i < MAX_BOARD_SIZE; ++i)
			{
				board[i] = new Tile * [MAX_BOARD_SIZE];
				for (int j = 0; j < MAX_BOARD_SIZE; j++)
				{
					board[i][j] = nullptr;
				}
			}
			getline(file, input);

			if (!file.eof() && input == 
				"   0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 ")
			{
				getline(file, input);
				if (file.eof() || input !=
					"  -------------------------------------------------------------------------------")
				{
					cout << "\nInvalid file: invalid board format" << endl;
					valid = false;
				}
			}
			else
			{
				cout << "\nInvalid file: invalid board format" << endl;
				valid = false;
			}
			if (valid)
			{
				firstTile = true;
				string rowLabel = "A |";
				for (int i = 0; i < MAX_BOARD_SIZE && valid; i++)
				{
					getline(file, input);
					if (file.eof() || input.substr(0, 3) != rowLabel
						|| input.size() > (3 + (MAX_BOARD_SIZE * 3)))
					{
						cout << "\nInvalid file: invalid board format" << endl;
						valid = false;
					}

					// Checks all tiles in board are valid
					for (unsigned int j = 3; j < input.size() && valid; j += 3)
					{
						if (input.substr(j, 3) != "  |")
						{
							Tile* tile = Tile::stringToTile(input[j], input[j + 1]);
							if (tile != nullptr)
							{
								firstTile = false;
								board[((j - 3) / 3)][i] = tile;
							}
							else
							{
								cout << "\nInvalid file: invalid board format" << endl;
								valid = false;
							}
						}
					}
					//Update row label to next letter
					++rowLabel[0];
				}
			}
		}
		if (valid)
		{
			getline(file, input);
			if (!file.eof())
			{
				for (unsigned int i = 0; i < input.size() && valid; i += 3)
				{
					Tile* tile = Tile::stringToTile(input[i], input[i + 1]);
					if (tile != nullptr)
					{
						tileBag.addBack(tile);
					}
					else
					{
						cout << "\nInvalid file: invalid tilebag" << endl;
						valid = false;
					}
				}
			}
			else
			{
				cout << "\nInvalid file: invalid tilebag" << endl;
				valid = false;
			}
		}
		if (valid)
		{
			getline(file, input);
			//Checks if this is the eof rather than not eof
			if (file.eof())
			{
				// Finds which player's turn it is
				bool found = false;
				for (unsigned int i = 0; i < players.size() && !found; ++i)
				{
					if (players[i]->name == input)
					{
						playerTurnIndex = i;
						found = true;
					}
				}
				if (!found)
				{
					cout << "\nInvalid file: invalid current player name" << endl;
					valid = false;
				}
			}
			else
			{
				cout << "\nInvalid file: invalid current player name" << endl;
				valid = false;
			}
		}
	}
	else
	{
		cout << "\nInvalid file: file does not exist" << endl;
		valid = false;
	}
	if (valid)
	{
		cout << "\nQwirkle game successfully loaded" << endl;
		shrinkBoard();
		runGame();
	}
	return valid;
}

void GameEngine::runGame()
{
	while (!exitGame)
	{
		displayGameState();
		if (players[playerTurnIndex]->difficulty == HUMAN) getInput();
		else processAITurn();
		playerTurnIndex = (playerTurnIndex == (int)(players.size() - 1)) ?
			0 : playerTurnIndex + 1;
		stalemateCheck();
	}
}

void GameEngine::stalemateCheck()
{
	bool possiblePlacement = false;
	for (unsigned int i = 0; i < players.size() && !possiblePlacement; ++i)
	{
		// If there is a possible placement
		if (findPossiblePlacements(players[i]->hand.toVector()).size() != 0)
		{
			possiblePlacement = true;
		}
	}

	// If neither the tilebag nor any player's hand 
	// contains a tile that can be placed
	if (!possiblePlacement && 
		findPossiblePlacements(tileBag.toVector()).size() == 0)
	{
		cout << "\nStalemate reached..." << endl;
		gameOver();
		exitGame = true;
	}
}

void GameEngine::getInput()
{
	bool valid = false;
    while (!valid && !exitGame)
	{
		cout << "> ";
		string input;
		getline(std::cin, input);

		// Causes the game to exit if eof is encountered
		if (std::cin.eof())
		{
			exitGame = true;
			valid = true;
		}

		if (input.size() != 0)
		{
			vector<string> commands;
			std::istringstream iss(input);
			string word;

			// Splits the input line into individual words
			// and puts them into a vector
			while (iss >> word) commands.push_back(word);

			// Checks whether the correct number of words was inputted
			if (commands.size() == 1)
			{
				if (commands[0] == "quit")
				{
					valid = true;
					exitGame = true;
				}
			}
			else if (commands.size() == 2)
			{
				if (commands[0] == "replace")
				{
					valid = replaceTile(commands[1]);
				}
				else if (commands[0] == "save")
				{
					saveGame(commands[1]);
					valid = true;

					// Allows the current player's information to 
					// be displayed again
					playerTurnIndex = (playerTurnIndex == 0 ?
						players.size() - 1 : playerTurnIndex - 1);
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

		if (!valid) cout << "\nInvalid input" << endl;
	}
}

string GameEngine::boardToString(bool colouredOutput, bool fullBoard)
{
	int width = (fullBoard ? MAX_BOARD_SIZE : viewX);
	int height = (fullBoard ? MAX_BOARD_SIZE : viewY);
	
	std::ostringstream output;

	output << "   ";

	Tile* tile = nullptr;
	for (int header = 0; header < width; header++)
	{
		output << header << " ";
		if (header < 10) output << " ";
	}

	output << "\n  -";
	for (int dash = 0; dash < width; dash++)
	{
		output << "---";
	}

	for (int y = 0; y < height; y++)
	{
		char ch = 'A' + y;
		output << "\n" << ch << " |";

		for (int x = 0; x < width; x++)
		{
			tile = board[x][y];
			if (tile == nullptr) output << "  |";
			else output << tile->getLabel(colouredOutput) <<"|";
		}
	}

	return output.str();
}

void GameEngine::adjustBoard(Position position)
{
	int xOffset = 0;
	int yOffset = 0;

	// Determines the x offset and updates viewX
	if (position.x == 0 && viewX != MAX_BOARD_SIZE)
	{
		xOffset = 1;
		bool found = false;
		for (int i = 0; i < MAX_BOARD_SIZE && !found; ++i)
		{
			if (board[viewX - 2][i] != nullptr)
			{
				++viewX;
				found = true;
			}
		}
	}
	else if (position.x == viewX - 1 && viewX != MAX_BOARD_SIZE) ++viewX;

	// Determines the y offset and updates viewY
	if (position.y == 0 && viewY != MAX_BOARD_SIZE)
	{
		yOffset = 1;
		bool found = false;
		for (int i = 0; i < MAX_BOARD_SIZE && !found; ++i)
		{
			if (board[i][viewY - 2] != nullptr)
			{
				++viewY;
				found = true;
			}
		}
	}
	else if (position.y == viewY - 1 && viewY != MAX_BOARD_SIZE) ++viewY;

	// Adjust tiles as needed
	if (xOffset == 1 || yOffset == 1)
	{
		for (int i = MAX_BOARD_SIZE - 1; i >= 0; --i)
		{
			for (int j = MAX_BOARD_SIZE - 1; j >= 0; --j)
			{
				if (board[i][j] != nullptr)
				{
					board[i + xOffset][j + yOffset] = board[i][j];
					board[i][j] = nullptr;
				}
			}
		}
	}
}

void GameEngine::shrinkBoard() 
{
	int minX = MAX_BOARD_SIZE;
	int minY = MAX_BOARD_SIZE;
	
	for (int i = 0; i < MAX_BOARD_SIZE; ++i)
	{
		for (int j = 0; j < MAX_BOARD_SIZE; ++j)
		{
			if (board[i][j] != nullptr)
			{
				minX = std::min(minX, i);
				minY = std::min(minY, j);
			}
		}
	}

	int maxX = 0;
	int maxY = 0;

	for (int i = 0; i < MAX_BOARD_SIZE; ++i)
	{
		for (int j = 0; j < MAX_BOARD_SIZE; ++j)
		{
			if (board[i][j] != nullptr)
			{
				board[i - minX][j - minY] = board[i][j];
				board[i][j] = nullptr;
				maxX = std::max(maxX, i - minX);
				maxY = std::max(maxY, j - minY);
			}
		}
	}

	// If the board was emtpy
	if (minX == MAX_BOARD_SIZE)
	{
		viewX = INITIAL_BOARD_SIZE;
		viewY = INITIAL_BOARD_SIZE;
	}
	else
	{
		viewX = std::min(maxX + 2, MAX_BOARD_SIZE);
		viewY = std::min(maxY + 2, MAX_BOARD_SIZE);
		adjustBoard(Position(0, 0));
	}
}

void GameEngine::displayGameState()
{
    cout << "\n" << players[playerTurnIndex]->name << ", it's your turn" << endl;

    for (Player* player : players)
    {
        cout << "Score for " << player->name << ": " << player->score << endl;
    }

	cout << boardToString(true, false) << endl;;

    cout << "\nYour hand is" << endl;
    cout << players[playerTurnIndex]->hand.display(true) << endl;
}

void GameEngine::processAITurn()
{
	Player* player = players[playerTurnIndex];
	vector<Tile*> handVector = player->hand.toVector();
	std::random_device rd;
	std::mt19937 eng(rd());

	if (firstTile)
	{
		// Randomely chooses a tile to place
		std::uniform_int_distribution<> randomIndex(0, handVector.size() - 1);
		Tile *tile = handVector[randomIndex(eng)];
		++player->score;
		player->hand.remove(tile);

		// Places it in the center
		board[2][2] = tile;
		Tile* newTile = tileBag.popFront();
		if (newTile != nullptr)
		{
			player->hand.addBack(newTile);
		}
		firstTile = false;
	}
	else
	{
		// Used for AI choice generation
		std::uniform_real_distribution<> choiceDistributions[3] = {
			std::uniform_real_distribution<>(0, 0.3) ,
			std::uniform_real_distribution<>(0.3, 0.6) ,
			std::uniform_real_distribution<>(0.6, 1) };

		vector<Placement> validPlacements = findPossiblePlacements(handVector);

		// Sorts placements in terms of score
		sort(validPlacements.begin(), validPlacements.end(), Placement::compare);

		// If no valid placements are possible, replaces a random tile in hand
		if (validPlacements.empty())
		{
			std::uniform_int_distribution<> randomIndex(0, handVector.size() - 1);
			Tile *tile = handVector[randomIndex(eng)];
			replaceTile(tile->label);
		}
		else
		{
			// Randomly picks from validPlacements from a distribution based on the aiDifficulty
			Placement aiPlacement = validPlacements[round((validPlacements.size() - 1) * choiceDistributions[players[playerTurnIndex]->difficulty](eng))];

			//checks if placement gives qwirkle
			if (aiPlacement.qwirkle) cout << "\nQWIRKLE!!!" << endl;

			//Updates AI's score and places the tile
			player->score += aiPlacement.score;
			player->hand.remove(aiPlacement.tile);
			board[aiPlacement.x][aiPlacement.y] = aiPlacement.tile;

			//Replenishes the AI's hand
			Tile *newTile = tileBag.popFront();
			if (newTile != nullptr)
			{
				player->hand.addBack(newTile);
			}

			adjustBoard(Position(aiPlacement.x, aiPlacement.y));

			//Game over checking
			if (player->hand.isEmpty()) gameOver();
		}
	}
}

int GameEngine::testPlacement(Tile* tile, Position position, bool& qwirkle)
{
	int score = 0;
	if (board[position.x][position.y] == nullptr)
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
			Position offsetPosition = position + offsets[i];
			if (offsetPosition.x < MAX_BOARD_SIZE && offsetPosition.x >= 0
				&& offsetPosition.y < MAX_BOARD_SIZE && offsetPosition.y >= 0)
			{
				Tile* currTile = board[offsetPosition.x][offsetPosition.y];

				if (currTile != nullptr)
				{
					// Checks whether the two tiles only have one type of similarity
					if ((tile->colour == currTile->colour) !=
						(tile->shape == currTile->shape))
					{
						connected[i] = true;
						// If there are two connected segments in the current dimension
						if (i >= 2 && connected[i - 2])
						{
							// If the opposite tile has a different similarity type
							if ((i == 2 ? verColourSimilarity : horColourSimilarity)
								!= (tile->colour == currTile->colour))
							{
								valid = false;
							}
						}
						else
						{
							// Sets the current dimension's similarity type
							(i % 2 == 0 ? verColourSimilarity : horColourSimilarity)
								= tile->colour == currTile->colour;
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
					// Indicates the current dimension
					bool vertical = i % 2 == 0;

					// The type set for the current dimension
					std::unordered_set<int>& typeSet =
						(vertical ? verTypeSet : horTypeSet);

					// Indicates the current dimension's similarity type
					bool colorSimilarity =
						(vertical ? verColourSimilarity : horColourSimilarity);

					Position currPosition = position + offsets[i];
					Tile* currTile;
					bool empty = false;
					while (valid && currPosition.x < MAX_BOARD_SIZE && currPosition.x >= 0
						&& currPosition.y < MAX_BOARD_SIZE && currPosition.y >= 0 && !empty)
					{
						currTile = board[currPosition.x][currPosition.y];
						if (currTile != nullptr)
						{
							// Used to check for duplicate tiles in the segment
							int signature =
								(colorSimilarity ? currTile->shape : currTile->colour);

							// If a tile is found that is already contained 
							// within the segment
							if (typeSet.count(signature) != 0)
							{
								score = 0;
								valid = false;
							}
							else
							{
								typeSet.insert(signature);
								++score;
							}
							currPosition += offsets[i];
						}
						else empty = true;
					}
				}
			}

			if (valid)
			{
				// Adds 1 point for the tile itself
				++score;
				
				// If tile is part of a vertical and horizontal
				// segment score is increased by 1
				if (verTypeSet.size() > 1 && horTypeSet.size() > 1)
				{
					++score;
				}

				// Qwirkle checking
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
			}
		}
	}
	return score;
}

vector<Placement> GameEngine::findPossiblePlacements(vector<Tile*> tiles)
{
	vector<Placement> validPlacements;

	for (int x = 0; x < viewX; ++x)
	{
		for (int y = 0; y < viewY; ++y)
		{
			// Tries every empty position in the board
			if (board[x][y] == nullptr)
			{
				for (Tile *tile : tiles)
				{
					bool qwirkle = false;
					int score = testPlacement(tile, Position(x, y), qwirkle);
					if (score > 0)
					{
						validPlacements.push_back(Placement(tile, x, y, score, qwirkle));
					}
				}
			}
		}
	}
	return validPlacements;
}

bool GameEngine::placeTile(string tileLabel, string positionLabel)
{
	bool success = false;
    Position* position;
    Tile* tile = players[playerTurnIndex]->hand.find(tileLabel);
    // Tile found in player's hand
    if (tile != nullptr)
    {
        position = Position::labelToPosition(positionLabel);
        // Position is within board bounds
        if(position != nullptr)
        {
            if (firstTile)
            {
				//First tile of a new game must be played only inside shown board
                if (position->x <= 5 && position->y <= 5)
                {
                    ++players[playerTurnIndex]->score;
                    players[playerTurnIndex]->hand.remove(tile);
                    board[position->x][position->y] = tile;
                    Tile* newTile = tileBag.popFront();
                    if (newTile != nullptr)
                    {
                        players[playerTurnIndex]->hand.addBack(newTile);
                    }
                    firstTile = false;
                    success = true;
                }
            }
            else
            {
				bool qwirkle = false;
                int score = testPlacement(tile, *position, qwirkle);

                // If placement was successful
                if (score > 0)
                {
					if (qwirkle) cout << "\nQWIRKLE!!!" << endl;

                    // Score updating and tile placement
                    players[playerTurnIndex]->score += score;
                    players[playerTurnIndex]->hand.remove(tile);
                    board[position->x][position->y] = tile;

                    // Tile replenishment
                    Tile* newTile = tileBag.popFront();
                    if (newTile != nullptr)
                    {
                        players[playerTurnIndex]->hand.addBack(newTile);
                    }

					adjustBoard(*position);

					// Game over checking
					if (players[playerTurnIndex]->hand.isEmpty()) gameOver();
					success = true;
                }
            }
            delete position;
        }
    }
    return success;
}

bool GameEngine::replaceTile(string tileLabel)
{
    Tile* tile = players[playerTurnIndex]->hand.find(tileLabel);
    bool replaced = false;

    if (tile != nullptr)
    {
        if (!tileBag.isEmpty())
        {
            Tile* newTile = tileBag.popFront();
            players[playerTurnIndex]->hand.remove(tile);
            tileBag.addBack(tile);
            players[playerTurnIndex]->hand.addBack(newTile);
            replaced = true;
        }
        else
        {
            cout << "\nTile Bag is empty!" << endl;
        }
    }
    return replaced;
}

void GameEngine::saveGame(string fileName)
{
	std::ofstream outFile(fileName);
	outFile << players.size() << endl;
	for (Player* player : players)
	{
		outFile << player->name << endl;
		outFile << player->score << endl;
		outFile << player->hand.display(false) << endl;
		if (player->difficulty == EASY) outFile << "EASY" << endl;
		else if (player->difficulty == MEDIUM) outFile << "MEDIUM" << endl;
		else if (player->difficulty == HARD) outFile << "HARD" << endl;
		else outFile << "HUMAN" << endl;
	}
	outFile << boardToString(false, true) << endl;
	outFile << tileBag.display(false) << endl;
	outFile << players[playerTurnIndex]->name;
	outFile.close();
	cout << "\nGame saved" << endl;
}

void GameEngine::gameOver()
{
	cout << "\nGame Over" << endl;
	cout << "Final board:" << endl;
	cout << boardToString(true, false) << endl;
	for (Player* currPlayer : players)
	{
		cout << "Score for " << currPlayer->name << " is " << currPlayer->score << endl;
	}
	sort(players.begin(), players.end(), Player::compare);
	if (players[players.size() - 1]->score == players[players.size() - 2]->score)
	{
		cout << "Draw... " << endl;
	}
	else
	{
		cout << "Player " << (players[(players.size() - 1)])->name << " won!" << endl;
	}
	exitGame = true;
}

GameEngine::~GameEngine()
{
	for (Player* player : players)
	{
		if (player != nullptr) delete player;
	}

	if (board != nullptr)
	{
		for (int x = 0; x < MAX_BOARD_SIZE; ++x)
		{
			for (int y = 0; y < MAX_BOARD_SIZE; ++y)
			{
				if (board[x][y] != nullptr)
				{
					delete board[x][y];
				}
			}
			delete[] board[x];
		}
		delete[] board;
	}
}
