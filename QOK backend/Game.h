#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "Question.h"
#include "Player.h"
#include "TriviaAPI.h"
#include "Category.h"

class Game {
private:
	Player roundWinner;
	std::vector<Player> players;
	std::string currentTurn;
	int currentRound;
	std::vector<Question> currentQuestions;
	TriviaAPI api;
public:
	Game() {
		currentRound = 1;
	}

	void set_currentTurn();
	void startPVPMode();
	void get_players_info();
	void set_players(const Player& player1, const Player& player2);
	void playRound();
	Category selectCategory(const std::vector<Category>& categories);
	std::string selectDifficulty();
	bool isGoldenRound();
	int get_currentTurn_player_index() const;
	int get_otherTurn_player_index() const;
	int ask_questions(const std::string& player_name);
	void nextRound();
	void checkAnswers(const int& score1, const int& score2);
	void setRoundWinnerPlayer(const Player& player);
	void endRound();
	bool isGameEnd();
	void playGoldenRound();
	void endGame();
};

#endif