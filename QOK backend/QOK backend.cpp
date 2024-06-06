#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <nlohmann/json.hpp>
#include <curl/curl.h>
#include "Question.h"
#include "TriviaAPI.h"
#include "Category.h"
#include "Game.h"

int main() {
	int choice;
	do {
		std::cout << "\n\n\t\t\tQOK Backend" << std::endl;
		std::cout << "\n\n\t1.NEW GAME .................................... BAZI-E JADID.1" << std::endl;
		std::cout << "\n\n\t0.EXIT ................................................ EXIT.0" << std::endl;
		std::cout << "\n\n\tChoose : ";
		std::cin >> choice;
		if (choice == 1) {
			Game game;
			game.startPVPMode();
		}
	} while (choice != 0);
}