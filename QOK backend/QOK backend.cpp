#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <nlohmann/json.hpp>
#include <curl/curl.h>
#include "Question.h"

std::vector<Question> getTriviaQuestions(const std::string& category, const std::string& difficulty);
std::vector<Question> readQuestionsFromJSON(const std::string& filename);
void show_questions(const std::vector<Question>& questions);
size_t writeCallback(void* ptr, size_t size, size_t nmemb, void* userdata);
int category_initializer(const std::string& category);

int main() {
	std::vector<Question> questions = getTriviaQuestions("music", "easy");
	show_questions(questions);
}

std::vector<Question> readQuestionsFromJSON(const std::string& filename) {
	std::vector<Question> questions;
	std::ifstream file(filename);
	
	if (!file.is_open()) {
		std::cout << "Could not open file " << filename << std::endl;
		return questions;
	}

	nlohmann::json data;
	file >> data;
	file.close();

	const auto& results = data["results"];
	for (const auto& result : results) {
		Question question;
		question.set_type(result["type"]);
		question.set_category(result["category"]);
		question.set_difficulty(result["difficulty"]);
		question.set_question(result["question"]);
		question.set_correct_answer(result["correct_answer"]);
		question.set_incorrect_answers(result["incorrect_answers"]);

		questions.push_back(question);
	}

	return questions;
}

void show_questions(const std::vector<Question>& questions) {
	int i = 1;
	for (const Question& question : questions) {
		std::cout << "Question " << i++ << ": " << std::endl;
		std::cout << "\tType: " << question.get_type() << std::endl;
		std::cout << "\tCategory: " << question.get_category() << std::endl;
		std::cout << "\tDifficulty: " << question.get_difficulty() << std::endl;
		std::cout << "\tQuestion: " << question.get_question() << std::endl;
		std::cout << "\tCorrect answer: " << question.get_correct_answer() << std::endl;
		std::cout << "\tIncorrect answers: " << std::endl;
		for (const std::string& incorrect_answer : question.get_incorrect_answers()) {
			std::cout << "\t\t" << incorrect_answer << std::endl;
		}
	}
}

size_t writeCallback(void* ptr, size_t size, size_t nmemb, void* userdata) {
	((std::string*)userdata)->append((char*)ptr, size * nmemb);
	return size * nmemb;
}


std::vector<Question> getTriviaQuestions(const std::string& category, const std::string& difficulty) {
	std::vector<Question> questions;

	CURL* curl = curl_easy_init();
	if (curl) {
		std::string responce;
		std::string url = "https://opentdb.com/api.php?amount=5&category=" + std::to_string(category_initializer(category)) + "&difficulty=" + difficulty + "&type=multiple";
		
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responce);

		CURLcode res = curl_easy_perform(curl);
		if (res == CURLE_OK) {
			nlohmann::json data = nlohmann::json::parse(responce);

			const auto& results = data["results"];
			for (const auto& result : results) {
				Question question;
				question.set_type(result["type"]);
				question.set_category(result["category"]);
				question.set_difficulty(result["difficulty"]);
				question.set_question(result["question"]);
				question.set_correct_answer(result["correct_answer"]);
				question.set_incorrect_answers(result["incorrect_answers"]);

				questions.push_back(question);
			}
		}

		curl_easy_cleanup(curl);
	}
	return questions;
}

int category_initializer(const std::string& category) {
	if (category == "videogames") {
		return 15;
	}
	else if (category == "music") {
		return 12;
	}
	else if (category == "math") {
		return 19;
	}
	else {
		return 0;
	}
}