#include "GameEngine.h"
#include "getline.h"
#include <iostream>
#include <string>
#include <exception>

#define EXIT_SUCCESS    0

using std::cout;
using std::endl;
using std::string;

void show_student_info()
{
	cout << endl;
	for (int i = 0; i < 30; ++i) cout << "-";
	cout << endl;
	printf("Name: %s\nStudent ID: %s\nEmail: %s\n\n", "Angelo Parlade", "s3688144", "s3688144@student.rmit.edu.au");
	printf("Name: %s\nStudent ID: %s\nEmail: %s\n\n", "Flynn Swainston-Calcutt", "s3720879", "s3720879@student.rmit.edu.au");
	printf("Name: %s\nStudent ID: %s\nEmail: %s\n\n", "Milindi Kodikara", "s3667779", "s3667779@student.rmit.edu.au");
	printf("Name: %s\nStudent ID: %s\nEmail: %s\n\n", "Ye Wyn Woon", "s3675485", "s3675485@student.rmit.edu.au");
	for (int i = 0; i < 30; ++i) cout << "-";
	cout << endl;
}


int main(void) 
{
	cout << "Welcome to Qwirkle!" << endl;
	cout << "-------------------" << endl;

	bool exit = false;
	while (!exit)
	{
		cout << "\nMenu\n"
			<< "----\n"
			<< "1. New Game\n"
			<< "2. Load Game\n"
			<< "3. Show Student Information\n"
			<< "4. Quit\n\n";
		bool valid_input = false;
		while (!valid_input)
		{
			cout << "> ";
			string input;
			getline(std::cin, input);
			if (input == "1")
			{
				GameEngine engine;
				engine.newGame();
				valid_input = true;
				exit = true;
			}
			else if (input == "2")
			{
				GameEngine engine;
				// Exits if the load was successful, returns to menu if it wasn't
				if (engine.loadGame()) exit = true;
				valid_input = true;
			}
			else if (input == "3")
			{
				show_student_info();
				valid_input = true;
			}
			else if (input == "4" || std::cin.eof())
			{
				valid_input = true;
				exit = true;
			}
			else cout << "Invalid input" << endl;
		}
	}
	cout << "\nGoodbye" << endl;

	return EXIT_SUCCESS;
}
