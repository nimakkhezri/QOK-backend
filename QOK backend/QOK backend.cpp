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

Category category_initializer(const TriviaAPI& api, const std::string& category_name);
void show_questions(const std::vector<Question>& questions);

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
			game.start();
		}
	} while (choice != 0);
}

Category category_initializer(const TriviaAPI& api, const std::string& category_name) {
	std::vector<Category> categories = api.get_categories();
	for (const Category& category : categories) {
		if (category.get_name() == category_name) {
			return category;
		}
	}
	Category category("Any", 0);
	return category;
}

void show_questions(const std::vector<Question>& questions) {
	for (const Question& question : questions) {
		std::cout << question.get_question() << std::endl;
	}
}