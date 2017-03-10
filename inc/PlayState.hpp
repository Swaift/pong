#ifndef PLAYSTATE_HPP
#define PLAYSTATE_HPP

#include <SFML/Graphics.hpp>
#include "params.hpp"
#include "State.hpp"
#include "Ball.hpp"
#include <cstdlib>
#include <cmath>

class PlayState: public State {
    public:
        PlayState();

        void execute(sf::RenderWindow& window);
    private:
        sf::Vertex divider[2];
        sf::RectangleShape topWall, bottomWall, leftWall, rightWall, lPaddle, rPaddle;
        sf::Ball ball;

        float getPaddleCenter(sf::Shape& paddle);
        float getBallCenter();
        float getBallOffset(sf::Shape& paddle);
};

#endif // PLAYSTATE_HPP
