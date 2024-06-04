#include "Player.h"

std::string Player::get_name() const {
	return name;
}

int Player::get_score() const {
	return score;
}

void Player::set_name(const std::string& name) {
	this->name = name;
}

void Player::set_score(const int& score) {
	this->score = score;
}

void Player::add_point() {
	this->score += 1;
}