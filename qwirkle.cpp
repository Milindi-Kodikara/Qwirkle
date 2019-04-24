#include "GameEngine.h"
#include <iostream>
#include <string>
#include <exception>

#define EXIT_SUCCESS    0

void new_game()
{
	//TODO
}

void load_game()
{
	//TODO
}

void show_student_info()
{
	//TODO
}

void display_menu()
{
	bool exit = false;
	while (!exit)
	{
		std::cout << "Menu\n"
			<< "----\n"
			<< "1. New Game\n"
			<< "2. Load Game\n"
			<< "3. Show Student Information\n"
			<< "4. Quit\n\n";
		bool valid_input = false;
		while (valid_input)
		{
			// This system for checking EOF won't work, find better solution
			std::cout << "> ";
			std::string input;
			std::cin >> input;
			try
			{
				int choice = std::stoi(input);
				exit = true;
				valid_input = true;
				if (choice == 1) new_game();
				else if (choice == 2) load_game();
				else if (choice == 3)
				{
					// Allows the menu to be shown again after the info is displayed
					exit = false;
					show_student_info();
				}
				else
				{
					valid_input = false;
					cout << "Invalid Input" << endl;
				}
			}
			catch (std::exception e)
			{
				// Checks if Ctrl D (EOF) was entered
				if (input[0] == EOF)
				{
					valid_input = true;
					exit = true;
				}
				cout << "Invalid Input" << endl;
			}
		}
	}
}

int main(void) 
{
	std::cout << "Welcome to Qwirkle!" << std::endl;
	std::cout << "-------------------" << std::endl;
	display_menu();
	return EXIT_SUCCESS;
}
