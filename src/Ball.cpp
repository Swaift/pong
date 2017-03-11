#include <SFML/Graphics.hpp>
#include "constants.hpp"
#include "Ball.hpp"
#include <cstdlib> // srand() rand()
#include <ctime> // time()

sf::Ball::Ball(float radius)
    : CircleShape(radius)
    , dx(0)
    , dy(0)
{
    std::srand((int) std::time(NULL));
    reset();
}

void sf::Ball::reset() {
    // place ball randomly along center axis
    setPosition(
            WINDOW_WIDTH/2 - BALL_RADIUS/2,
            std::rand() % (WINDOW_HEIGHT - WALL_THICKNESS * 2 - BALL_RADIUS * 2) + WALL_THICKNESS
            );
    dx = -BALL_STEP;
    // ballDy goes either straight or at either angle toward the player
    dy = (std::rand() % 3 - 1) * BALL_STEP/2;
}

float sf::Ball::getDx() {
    return dx;
}
float sf::Ball::getDy() {
    return dy;
}
void sf::Ball::setDx(float dx) {
    this->dx = dx;
}
void sf::Ball::setDy(float dy) {
    this->dy = dy;
}

float sf::Ball::getCenter() {
    return getPosition().y + BALL_RADIUS;
}
