#include "GameEngine.h"
#include <iostream>
#include <sstream>
#include <vector>

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
