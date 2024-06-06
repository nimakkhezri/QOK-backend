#include "Game.h"

void Game::startPVPMode() {
	get_players_info();

	playRound();

	while (!isGameEnd()) {
		nextRound();
	}
}

void Game::playRound() {
	int score1, score2;
	if (!isGoldenRound()) {
		std::cout << "\n\n\tCurrent Turn: " << currentTurn << std::endl;
		api.show_categories();
		Category category = selectCategory(api.get_categories());
		std::string difficulty = selectDifficulty();
		currentQuestions = api.get_questions(category, difficulty);
		score1 = ask_questions(currentTurn);
		currentRound++;
		set_currentTurn();
		score2 = ask_questions(currentTurn);
		currentRound--;
		set_currentTurn();
		checkAnswers(score1, score2);
		endRound();
	}
	else {
		playGoldenRound();
	}
}

void Game::playGoldenRound() {
	int score1, score2;
	std::cout << "\n\n\t\t*Golden Round!*" << std::endl;
	std::cout << "\n\n\t** In the \"Golden Round\", the categories and the difficulty of the questions are randomly selected! **" << std::endl;
	std::cout << "\n\n\tCurrent Turn: " << currentTurn << std::endl;
	currentQuestions = api.get_questions();
	score1 = ask_questions(currentTurn);
	currentRound++;
	set_currentTurn();
	score2 = ask_questions(currentTurn);
	currentRound--;
	set_currentTurn();
	checkAnswers(score1, score2);
	endRound();
}

void Game::nextRound() {
	currentRound++;
	set_currentTurn();
	playRound();
}

void Game::set_players(const Player& player1, const Player& player2) {
	players.push_back(player1);
	players.push_back(player2);
	set_currentTurn();
}

void Game::get_players_info() {
	std::string player1_name, player2_name;
	std::cout << "\n\n\tPlease enter the name of player1: ";
	std::cin >> player1_name;
	std::cout << "\n\n\tPlease enter the name of player2: ";
	std::cin >> player2_name;
	set_players(Player(player1_name), Player(player2_name));
}

void Game::set_currentTurn() {
	if (currentRound % 2 == 0) {
		currentTurn = players[1].get_name();
	}
	else {
		currentTurn = players[0].get_name();
	}
}

bool Game::isGoldenRound() {
	if (currentRound > 4) {
		return true;
	}
	else {
		return false;
	}
}

int Game::get_currentTurn_player_index() const {
	for (int i = 0; i <= 1; i++) {
		if (players[i].get_name() == currentTurn) {
			return i;
		}
	}
}

int Game::get_otherTurn_player_index() const {
	for (int i = 0; i <= 1; i++) {
		if (players[i].get_name() != currentTurn) {
			return i;
		}
	}
}

Category Game::selectCategory(const std::vector<Category>& categories) {
	std::cout << "\n\n\tEnter the number of Category you want to select: ";
	int choice;
	std::cin >> choice;
	for (const Category& category : categories) {
		if (category.get_id() == choice) {
			return category;
		}
	}
	Category category("Any", 0);
	return category;
}

std::string Game::selectDifficulty() {
	std::string difficulty;
	do {
		std::cout << "\n\n\tSelect Difficulty (easy, medium, hard): ";
		std::cin >> difficulty;
		if (difficulty != "easy" && difficulty != "medium" && difficulty != "hard") {
			std::cout << "\n\n\tTry Again! ..." << std::endl;
	}
	} while (difficulty != "easy" && difficulty != "medium" && difficulty != "hard");
	return difficulty;
}

int Game::ask_questions(const std::string& player_name) {
	int score = 0;
	std::cout << "\n\n\tAre you Ready " << player_name << " ?\n\n";
	system("Pause");
	int i = 1;
	for (const Question& question : currentQuestions) {
		int choice;
		std::vector<std::string> answers;
		answers.push_back(question.get_correct_answer());
		for (const std::string& incorrect_answer : question.get_incorrect_answers()) {
			answers.push_back(incorrect_answer);
		}
		std::random_shuffle(answers.begin(), answers.end());

		std::cout << "\n\n\tQuestion 1: " << question.get_question() << std::endl;
		std::cout << "\n\tCategory: " << question.get_category().get_name() << "\t\t\tDifficulty: " << question.get_difficulty() << std::endl;
		std::cout << "\n\n\tChoices: " << std::endl;
		std::cout << "\n\n";
		int j = 1;
		for (const std::string& answer : answers) {
			std::cout << "\t\t" << j++ << ". " << answer;
		}
		std::cout << "\n\n\n\tYour Choice (30 seconds): ";
		std::cin >> choice;
		if (answers[choice - 1] == question.get_correct_answer()) {
			score++;
		}
	}
	return score;
}

void Game::checkAnswers(const int& score1, const int& score2) {
	if (score1 == score2) {
		players[0].add_point();
		players[1].add_point();
		Player player3("We dont have a winner !!");
		setRoundWinnerPlayer(player3);
	}
	else if (score1 > score2) {
		players[get_currentTurn_player_index()].add_point();
		setRoundWinnerPlayer(players[get_currentTurn_player_index()]);
	}
	else {
		players[get_otherTurn_player_index()].add_point();
		setRoundWinnerPlayer(players[get_otherTurn_player_index()]);
	}
}

void Game::setRoundWinnerPlayer(const Player& player) {
	this->roundWinner = player;
}

void Game::endRound() {
	std::cout << "\n\n\tThe round is over!" << std::endl;
	std::cout << "\n\n\tWinner: " << roundWinner.get_name() << std::endl;
	std::cout << "\n\n\n\tScores: " << std::endl;
	std::cout << "\n\n\tPlayer1: " << std::left << std::setw(20) << players[0].get_name() << std::setw(20) << "Score: " << players[0].get_score() << std::endl;
	std::cout << "\n\n\tPlayer2: " << std::left << std::setw(20) << players[1].get_name() << std::setw(20) << "Score: " << players[1].get_score() << std::endl;
	std::cout << "\n\n\n\tQuestions: " << std::endl;
	int i = 1;
	for (const Question& question : currentQuestions) {
		std::cout << "\n\n\t" << i++ << ". " << std::left << std::setw(50) << question.get_question() << std::setw(40) << "Correct Answer: " << question.get_correct_answer() << std::endl;
	}
	system("Pause");
}

bool Game::isGameEnd() {
	if (currentRound >= 4) {
		if (players[0].get_score() == players[1].get_score()) {
			return false;
		}
		else {
			return true;
		}
	}
	else {
		return false;
	}
}