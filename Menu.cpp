#include "Menu.h"
#include <iostream>

bool Menu::StartMenu(Menu option)
{

	int decision;

	do {

		std::cout << "Quit" << '\n' << "Play" << '\n';
		std::cin >> option;

		switch(decision) {

		case 0:

			std::cout << "Gee, thanks..." << '\n';
			return 0;

		case 1:

			std::cout << "Ayy let's go play the game" << '\n';
			break;

		}
	}
	
	while(option != 0);
}
