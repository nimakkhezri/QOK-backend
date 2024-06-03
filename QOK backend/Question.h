#ifndef QUESTION_H
#define QUESTION_H

#include <iostream>
#include <vector>

class Question {
private:
	std::string type, category, difficulty, question, correct_answer;
	std::vector <std::string> incorrect_answers;
public:
	Question(std::string type, std::string category, std::string difficulty, std::string question, std::string correct_answer, std::vector<std::string> incorrect_answers) {
		this->type = type;
		this->category = category;
		this->difficulty = difficulty;
		this->question = question;
		this->correct_answer = correct_answer;
		this->incorrect_answers = incorrect_answers;
	}
	Question(){}

	std::string get_type() const;
	std::string get_category() const;
	std::string get_difficulty() const;
	std::string get_question() const;
	std::string get_correct_answer() const;
	std::vector<std::string> get_incorrect_answers() const;

	void set_type(const std::string& type);
	void set_category(const std::string& category);
	void set_difficulty(const std::string& difficulty);
	void set_question(const std::string& question);
	void set_correct_answer(const std::string& correct_answer);
	void set_incorrect_answers(const std::vector<std::string>& incorrect_answers);
};

#endif