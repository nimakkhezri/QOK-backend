#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>

class Player {
private:
	std::string name;
	int score;
public:
	Player(std::string name, int score): name(name), score(score){}
	Player(){}

	std::string get_name() const;
	int get_score() const;

	void set_name(const std::string& name);
	void set_score(const int& score);
};

#endif