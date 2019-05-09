#include "GameEngine.h"
#include <iostream>
#include <string>
#include <exception>

#define EXIT_SUCCESS    0

void new_game()
{
	GameEngine engine;
	engine.newGame();
}

void load_game()
{
	GameEngine engine;
	engine.loadGame();
}

void show_student_info()
{
	std::cout << std::endl;
	for (int i = 0; i < 30; ++i) std::cout << "-";
	std::cout << std::endl;
	printf("Name: %s\nStudent ID: %s\nEmail: %s\n\n", "Flynn Swainston-Calcutt", "s3720879", "s3720879@student.rmit.edu.au");
	printf("Name: %s\nStudent ID: %s\nEmail: %s\n\n", "Angelo Parlade", "s3688144", "s3688144@student.rmit.edu.au");
	printf("Name: %s\nStudent ID: %s\nEmail: %s\n\n", "TODO", "TODO", "TODO");
	printf("Name: %s\nStudent ID: %s\nEmail: %s\n\n", "TODO", "TODO", "TODO");
	for (int i = 0; i < 30; ++i) std::cout << "-";
	std::cout << std::endl;
}


int main(void) 
{
	std::cout << "Welcome to Qwirkle!" << std::endl;
	std::cout << "-------------------\n" << std::endl;

	bool exit = false;
	while (!exit)
	{
		std::cout << "\nMenu\n"
			<< "----\n"
			<< "1. New Game\n"
			<< "2. Load Game\n"
			<< "3. Show Student Information\n"
			<< "4. Quit\n\n";
		bool valid_input = false;
		while (!valid_input)
		{
			std::cout << "> ";
			std::string input;
			std::getline(std::cin, input);
			if (input[0] == '1')
			{
				new_game();
				valid_input = true;
				exit = true;
			}
			else if (input[0] == '2')
			{
				load_game();
				valid_input = true;
				exit = true;
			}
			else if (input[0] == '3')
			{
				show_student_info();
				valid_input = true;
			}
			else if (input[0] == '4' || std::cin.eof())
			{
				valid_input = true;
				exit = true;
				std::cout << "Goodbye" << std::endl;
			}
			else std::cout << "Invalid input" << std::endl;
		}
	}

	return EXIT_SUCCESS;
}
