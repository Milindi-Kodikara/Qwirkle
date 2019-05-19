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

// Needs fixing
void GameEngine::newGame()
{
    // Initialises game state
	exitGame = false;
	playerTurnIndex = 0;
	firstTile = true;

    Difficulty aiDifficulty = HUMAN;
    string input;
    string difficulty;
    string numOfPlayers;
    int playerCount = 0;
    //regex to ensure player name is only uppercase alphabets
    std::regex r("[a-zA-Z]+");
    std::smatch m;
    cout << "Starting a new game" << endl;
    while (playerCount < 1 || playerCount > MAX_PLAYERS)
    {
        cout << "How many players would you like?" << endl;
        getline(std::cin, numOfPlayers);
        std::istringstream iss(numOfPlayers);
        iss >> playerCount;
    }

    for (int i = 0; i < playerCount; i++)
    {
        string playerName;
        //prompts the user again if the given name does not follow the regex
        while (!std::regex_search(playerName, m, r))
        {
            cout << "Enter a name for player " << i + 1 << " (no numbers or symbols)" << endl;
            getline(std::cin, playerName);
        }
        while (input != "Y" && input != "N")
        {
            cout << "Would you like this player to be an AI?\n" << "Y/N" << endl;
            getline(std::cin, input);
        }
        if (input == "Y")
        {
            while (difficulty != "EASY" && difficulty != "MEDIUM" && difficulty != "HARD")
            {
                cout << "Select a difficulty (EASY, MEDIUM, HARD)" << endl;
                getline(std::cin, difficulty);
            }
            if (difficulty == "EASY")
            {
                aiDifficulty = EASY;
            }
            if (difficulty == "MEDIUM")
            {
                aiDifficulty = MEDIUM;
            }
            if (difficulty == "HARD")
            {
                aiDifficulty = HARD;
            }
        }
        else if (input == "N")
        {
            aiDifficulty = HUMAN;
        }
        players.push_back(new Player(playerName));
        (players[players.size() - 1])->difficulty = aiDifficulty;
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
            temp.add_back(new Tile(colours[i], j));
            temp.add_back(new Tile(colours[i], j));
        }
    }

    std::random_device rd; // obtain a random number from hardware
    std::mt19937 eng(rd()); // seed the generator

    // randomly add tiles
    for (int i = 72; i > 0; i--)
    {
        std::uniform_int_distribution<> distr(0, i - 1);
        tileBag.add_back(temp.removeAt(distr(eng)));
    }
    //distribute six tiles to each player
    for (Player* player : players)
    {
        for (int i = 0; i < 6; ++i)
        {
            player->hand.add_back(tileBag.pop_front());
        }
    }

    // Creates the empty board
    board = new Tile**[BOARD_SIZE];
    for (int i = 0; i < BOARD_SIZE; ++i)
    {
        board[i] = new Tile*[BOARD_SIZE];
        for (int j = 0; j < BOARD_SIZE; ++j)
        {
            board[i][j] = nullptr;
        }
    }
    cout << "Let's Play!" << endl;
    runGame();
}

bool GameEngine::loadGame()
{
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
		std::istringstream iss(input);
		int numberOfPlayers;
		
		//Check if the first line is a vaild number of players
		if (!file.eof() && !iss.bad()) iss >> numberOfPlayers;
		else valid = false;
		if (numberOfPlayers > MAX_PLAYERS) valid = false;

		if (valid)
		{
			std::regex r("[a-zA-Z]+");
			std::smatch m;
			//Checks all player's information
			for (int i = 0; i < numberOfPlayers && valid; i++)
			{
				Player* player = nullptr;

				// Checks player name
				getline(file, input);
				if (!file.eof() && std::regex_search(input, m, r))
				{
					player = new Player(input);
				}
				else valid = false;

				// Checks player score
				if (valid)
				{
					getline(file, input);
					std::istringstream iss(input);
					int score;
					iss >> score;
					if (!file.eof() && !iss.bad()) player->score = score;
					else valid = false;
				}

				// Checks player hand
				if (valid)
				{
					getline(file, input);
					if (!file.eof())
					{
						int tileCount = 0;
						for (unsigned int i = 0; i < input.size() && valid; i += 3)
						{
							Tile* tile = Tile::stringToTile(input[i], input[i + 1]);
							if (tile == nullptr) valid = false;
							else
							{
								player->hand.add_back(tile);
								++tileCount;
							}
							if (tileCount > 6) valid = false;
						}
					}
					else valid = false;
				}

				// Checks if player is an AI + difficulty
				if (valid)
				{
					getline(file, input);
					if (!file.eof())
					{
						if (input == "EASY") player->difficulty = EASY;
						if (input == "MEDIUM") player->difficulty = MEDIUM;
						if (input == "HARD") player->difficulty = HARD;
						if (input == "HUMAN") player->difficulty = HUMAN;
						else valid = false;
					}
					else valid = false;
				}
				players.push_back(player);
			}
		}
		if (valid)
		{
			//Initialize the board
			board = new Tile * *[BOARD_SIZE];
			for (int i = 0; i < BOARD_SIZE; ++i)
			{
				board[i] = new Tile * [BOARD_SIZE];
				for (int j = 0; j < BOARD_SIZE; j++)
				{
					board[i][j] = nullptr;
				}
			}
			getline(file, input);

			if (!file.eof() && input == "   0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25")
			{
				getline(file, input);
				if (file.eof() || input != "  -------------------------------------------------------------------------------") valid = false;
			}
			else valid = false;
			if (valid)
			{
				firstTile = true;
				string rowLabel = "A |";
				for (int i = 0; i < BOARD_SIZE && valid; i++)
				{
					getline(file, input);
					if (file.eof() || input.substr(0, 3) != rowLabel || input.size() > (3 + (BOARD_SIZE * 3))) valid = false;
					//Check all tiles in board are valid
					for (unsigned int j = 3; j < input.size() && valid; j += 3)
					{
						if (input.substr(j, 3) != "  |")
						{
							Tile* tile = Tile::stringToTile(input[j], input[j + 1]);
							if (tile == nullptr) valid = false;
							else
							{
								firstTile = false;
								board[((j - 3) / 3)][i] = tile;
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
					if (tile == nullptr) valid = false;
					else
					{
						tileBag.add_back(tile);
					}
				}
			}
			else valid = false;
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
				if (!found) valid = false;
			}
			else valid = false;
		}

	}
	else valid = false;
	if (valid)
	{
		cout << "\nQwirkle game successfully loaded" << endl;
		adjustBoard(true);
		runGame();
	}
	return valid;
}

void GameEngine::adjustBoard(bool shrinkBoard)
{

	//Move all the tiles in the board in the most top right position possible without
	//breaking the sequence of the tiles
	if (shrinkBoard)
	{
		int minX = BOARD_SIZE;
		int minY = BOARD_SIZE;

		for (int h = 0; h < 2; ++h)
		{
			for (int i = 0; i < BOARD_SIZE; ++i)
			{
				for (int j = 0; j < BOARD_SIZE; ++j)
				{
					if (board[i][j] != nullptr && h == 0)
					{
						if (i < minX) minX = i;
						if (j < minY) minY = j;
					}
					else if (board[i][j] != nullptr && h == 1)
					{
						board[i - minX][j - minY] = board[i][j];
						board[i][j] = nullptr;
					}
				}
			}
		}
	}

	//Flags to know if adjusts should be made
	bool rowChange = true;
	bool colChange = true;

	//Values of how much right or down should the board adjust
	int x = 0;
	int y = 0;

	//First checks the 26th row and col if there is alrady a tile meaning that the max
	//row or col aleady has been met and will set their respective adjust flags to false.
	//Then checks the 1st row and col for tiles to know if the board will need to move
	//right or down to let players place tile above or to the right of the board.
	for (int line = BOARD_SIZE - 1; line >= 0; line -= BOARD_SIZE - 1)
	{
		for (int i = 0; i < BOARD_SIZE; ++i)
		{
			if (board[i][line] != nullptr)
			{
				if (line != 0) rowChange = false;
				else
				{
					y = 1;
				}
			}
			if (board[line][i] != nullptr)
			{
				if (line != 0) colChange = false;
				else
				{
					x = 1;
				}
			}
		}
	}

	//Discards change values if max row or col has been met
	if (!rowChange) y = 0;
	if (!colChange) x = 0;

	//Adjust tiles as needed
	for (int i = BOARD_SIZE - 2; i >= 0; --i)
	{
		for (int j = BOARD_SIZE - 2; j >= 0; --j)
		{
			board[i + x][j + y] = board[i][j];
			if (i == 0 && rowChange)
			{
				board[i][j] = nullptr;
			}
			if (j == 0 && colChange)
			{
				board[i][j] = nullptr;
			}

		}
	}
}

void GameEngine::runGame()
{
	while (!exitGame)
	{
		adjustBoard(false);
		displayGameState();
		if (players[playerTurnIndex]->difficulty == HUMAN) getInput();
		else processAITurn();
		playerTurnIndex = (playerTurnIndex = players.size() - 1) ?
			0 : playerTurnIndex + 1;
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
			std::vector<string> commands;
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

		if (!valid) cout << "\nInvalid input" << endl;
	}
}

string GameEngine::boardToString(bool colouredOutput, bool fullBoard)
{
	std::ostringstream output;

	//Minimum size of the board
	viewX = 6;
	viewY = 6;

	//Returns an output with a 26*26 board for saving a game
	if (fullBoard)
	{
		viewX = BOARD_SIZE;
		viewY = BOARD_SIZE;
	}

	//Looks for the tiles with the highest X coordinate & the highest Y coordinate
	//to know how big the board should be
	for (int i = 0; i < BOARD_SIZE; ++i)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (board[i][j] != nullptr)
			{
				if (i >= viewY-1) viewY = i + 2;
				if (j >= viewX-1) viewX = j + 2;
			}
		}
	}

	output << "   ";

	Tile* tile = nullptr;
	for (int header = 0; header < viewY; header++)
	{
		output << header << " ";
		if (header < 10) output << " ";
	}

	output << "\n  -";
	for (int dash = 0; dash < viewY; dash++)
	{
		output << "---";
	}

	for (int y = 0; y < viewX; y++)
	{
		char ch = 'A' + y;
		output << "\n" << ch << " |";

		for (int x = 0; x < viewY; x++)
		{
			tile = board[x][y];
			if (tile == nullptr) {
				output << "  |";
			}
			else
			{
					output << tile->getLabel(colouredOutput) <<"|";
			}
		}
	}

	return output.str();
}

// Needs fixing
void GameEngine::displayGameState()
{
    cout << "\n" << players[playerTurnIndex]->name << ", it's your turn" << endl;

    for (Player* player : players)
    {
        cout << "Score for " << player->name << ": " << player->score << endl;
    }

    cout << boardToString(true, false);

    cout << "\n\nYour hand is" << endl;
    cout << players[playerTurnIndex]->hand.display(true) << endl;
}

// Needs fixing
void GameEngine::processAITurn()
{
    std::vector<Placement> validPlacements;
    std::vector<Tile*> hand = players[playerTurnIndex]->hand.toVector();

    // Finds all valid placements
    for (int x = 0; x < viewX; ++x)
    {
        for (int y = 0; y < viewY; ++y)
        {
            if (board[x][y] == nullptr)
            {
                for (Tile *tile : hand)
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

    // Sorts placements in terms of score
    sort(validPlacements.begin(), validPlacements.end(), Placement::compare);

    std::random_device rd;
    std::mt19937 eng(rd());

    // If no valid placements are possible, replaces a random tile in hand
    if (validPlacements.empty())
    {
        std::uniform_int_distribution<> randomIndex(0, hand.size() - 1);
        Tile *tile = hand[randomIndex(eng)];
        replaceTile(tile->label);
    }
    else
    {
        // Randomly picks from validPlacements from a distribution based on the aiDifficulty
        Placement aiPlacement = validPlacements[round((validPlacements.size() - 1) * choiceDistributions[players[playerTurnIndex]->difficulty](eng))];

        //checks if placement gives qwirkle
        if (aiPlacement.qwirkle) cout << "QWIRKLE!!!" << endl;

        //Updates AI's score and places the tile
        players[playerTurnIndex]->score += aiPlacement.score;
        players[playerTurnIndex]->hand.remove(aiPlacement.tile);
        board[aiPlacement.x][aiPlacement.y] = aiPlacement.tile;

        //Replenishes the AI's hand
        Tile *newTile = tileBag.pop_front();
        if (newTile != nullptr)
        {
            players[playerTurnIndex]->hand.add_back(newTile);
        }

        //Game over checking
        if (players[playerTurnIndex]->hand.isEmpty())
        {
            cout << "\nGame Over" << endl;
            for (Player* player : players)
            {
                cout << "Score for " << player->name << " is " << player->score << endl;
            }
            sort(players.begin(),players.end(),Player::compare);
            if (players[players.size()-1]->score == (players[players.size()-2]->score))
            {
                cout << "Draw... " << endl;
            }
            else
            {
                cout << "Player " << (players[(players.size() - 1)])->name << " won!" << endl;
            }
            exitGame = true;
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
					while (valid && currPosition.x < BOARD_SIZE && currPosition.x >= 0
						&& currPosition.y < BOARD_SIZE && currPosition.y >= 0 && !empty)
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

// Needs fixing
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
                    Tile* newTile = tileBag.pop_front();
                    if (newTile != nullptr)
                    {
                        players[playerTurnIndex]->hand.add_back(newTile);
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
                    if (qwirkle) cout << "QWIRKLE!!!" << endl;

                    // Score updating and tile placement
                    players[playerTurnIndex]->score += score;
                    players[playerTurnIndex]->hand.remove(tile);
                    board[position->x][position->y] = tile;

                    // Tile replenishment
                    Tile* newTile = tileBag.pop_front();
                    if (newTile != nullptr)
                    {
                        players[playerTurnIndex]->hand.add_back(newTile);
                    }

                    // Game over checking
                    if (players[playerTurnIndex]->hand.isEmpty())
                    {
                        cout << "\nGame Over" << endl;
                        for (Player* player : players)
                        {
                            cout << "Score for " << player->name << " is " << player->score << endl;
                        }
                        sort(players.begin(),players.end(),Player::compare);
                        if (players[players.size()-1]->score == (players[players.size()-2]->score))
                        {
                            cout << "Draw... " << endl;
                        }
                        else
                        {
                            cout << "Player " << (players[(players.size() - 1)])->name << " won!" << endl;
                        }
                        exitGame = true;
                    }
                }
                success = true;
            }
            delete position;
        }
    }
    return success;
}

// Needs fixing
bool GameEngine::replaceTile(string tileLabel)
{
    Tile* tile = players[playerTurnIndex]->hand.find(tileLabel);
    bool replaced = false;

    if (tile != nullptr)
    {
        if (!tileBag.isEmpty())
        {
            Tile* newTile = tileBag.pop_front();
            players[playerTurnIndex]->hand.remove(tile);
            tileBag.add_back(tile);
            players[playerTurnIndex]->hand.add_back(newTile);
            replaced = true;
        }
        else
        {
            cout << "Tile Bag is empty!" << endl;
        }
    }
    return replaced;
}

bool GameEngine::saveGame(string fileName)
{
	std::ofstream outFile(fileName);
	// Line below may be uneeded
	// outFile.open(fileName, std::ofstream::app);
	for (unsigned int i = 0; i < players.size(); ++i)
	{
		Player* player = players[i];
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
	outFile << players[playerTurnIndex]->name << endl;
	outFile.close();
	return true;
}
