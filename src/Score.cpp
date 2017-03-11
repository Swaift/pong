#include <SFML/Graphics.hpp>
#include "Score.hpp"
#include <string> // to_string()

sf::Score::Score()
{
    setScore(0);
}

int sf::Score::getScore() {
    return score;
}

void sf::Score::setScore(int score) {
    this->score = score;
    setString(std::to_string(score));
}
