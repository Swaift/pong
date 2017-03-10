#include <SFML/Graphics.hpp>
#include "params.hpp"
#include "State.hpp"
#include "PlayState.hpp"
#include "Ball.hpp"
#include <cmath> // fabs()

PlayState::PlayState() 
    : divider({
            sf::Vertex(sf::Vector2f(WINDOW_WIDTH/2, 0)),
            sf::Vertex(sf::Vector2f(WINDOW_WIDTH/2, WINDOW_HEIGHT))
            })
    , topWall(sf::Vector2f(WINDOW_WIDTH, WALL_THICKNESS))
    , bottomWall(sf::Vector2f(WINDOW_WIDTH, WALL_THICKNESS))
    , leftWall(sf::Vector2f(WALL_THICKNESS, WINDOW_HEIGHT))
    , rightWall(sf::Vector2f(WALL_THICKNESS, WINDOW_HEIGHT))
    , lPaddle(sf::Vector2f(PADDLE_THICKNESS, PADDLE_LENGTH))
    , rPaddle(sf::Vector2f(PADDLE_THICKNESS, PADDLE_LENGTH))
    , ball(sf::Ball(BALL_RADIUS))
{
    topWall.setPosition(0, 0);
    bottomWall.setPosition(0, WINDOW_HEIGHT - WALL_THICKNESS);

    leftWall.setPosition(-WALL_THICKNESS, 0);
    rightWall.setPosition(WINDOW_WIDTH, 0);

    lPaddle.setPosition(PADDLE_SPACE, WINDOW_HEIGHT/2 - PADDLE_LENGTH/2);
    rPaddle.setPosition(WINDOW_WIDTH - PADDLE_THICKNESS - PADDLE_SPACE, WINDOW_HEIGHT/2 - PADDLE_LENGTH/2);
}

void PlayState::execute(sf::RenderWindow& window) {
    // rPaddle AI
    if (std::fabs(getBallOffset(rPaddle)) > PADDLE_LENGTH/2)
    {
        rPaddle.move(0, getBallOffset(rPaddle)/R_PADDLE_ACCEL);
    }

    // player paddle y-position same as mouse unless out of screen
    lPaddle.setPosition(lPaddle.getPosition().x, sf::Mouse::getPosition(window).y - PADDLE_LENGTH/2);
    if (lPaddle.getPosition().y < topWall.getPosition().y + WALL_THICKNESS) {
        lPaddle.setPosition(lPaddle.getPosition().x, topWall.getPosition().y + WALL_THICKNESS);
    } else if (lPaddle.getPosition().y + PADDLE_LENGTH > bottomWall.getPosition().y) {
        lPaddle.setPosition(lPaddle.getPosition().x, bottomWall.getPosition().y - PADDLE_LENGTH);
    }

    // bounce ball off walls
    if (ball.getGlobalBounds().intersects(topWall.getGlobalBounds())) {
        ball.setDy(std::fabs(ball.getDy()));
    } else if (ball.getGlobalBounds().intersects(bottomWall.getGlobalBounds())) {
        ball.setDy(-std::fabs(ball.getDy()));
    }
    // bounce ball off paddles
    if (ball.getGlobalBounds().intersects(lPaddle.getGlobalBounds())) {
        ball.setDy(getBallOffset(lPaddle)/MAX_BALL_OFFSET * BALL_STEP);
        ball.setDx(-ball.getDx());
    } else if (ball.getGlobalBounds().intersects(rPaddle.getGlobalBounds())) {
        ball.setDy(getBallOffset(rPaddle)/MAX_BALL_OFFSET * BALL_STEP);
        ball.setDx(-ball.getDx());
    }
    // check if ball hit either goal
    if (ball.getGlobalBounds().intersects(leftWall.getGlobalBounds())) {
        ball.reset();
    } else if (ball.getGlobalBounds().intersects(rightWall.getGlobalBounds())) {
        ball.reset();
    } else {
        ball.move(ball.getDx(), ball.getDy());
    }

    window.draw(topWall);
    window.draw(bottomWall);
    window.draw(divider, 2, sf::Lines);
    window.draw(lPaddle);
    window.draw(rPaddle);
    window.draw(ball);
}

inline float PlayState::getPaddleCenter(sf::Shape& paddle) {
    return paddle.getPosition().y + PADDLE_LENGTH/2;
}

inline float PlayState::getBallCenter() {
    return ball.getPosition().y + BALL_RADIUS;
}

inline float PlayState::getBallOffset(sf::Shape& paddle) {
    return getBallCenter() - getPaddleCenter(paddle);
}
