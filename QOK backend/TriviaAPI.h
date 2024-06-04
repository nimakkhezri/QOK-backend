#ifndef TRIVIAAPI_H
#define TRIVIAAPI_H

#include <iostream>
#include <vector>
#include <string>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <map>
#include "Category.h"
#include "Question.h"

class TriviaAPI {
private:
	std::string base_url;
	std::vector<Category> categories;
public:
	TriviaAPI() {
		this->base_url = "https://opentdb.com/api.php?amount=5&category=";
		this->download_categories();
	}

	std::vector<Question> get_questions(const Category& category, const std::string& difficulty);
	void download_categories();
	void show_categories();
	std::vector<Category> get_categories() const;
};

#endif