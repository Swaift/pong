#ifndef PLAY_HPP
#define PLAY_HPP

#include "SFML/Graphics.hpp"
#include "params.hpp"
#include <cstdlib>
#include <cmath>

namespace play {
    sf::Vertex divider[2];
    sf::RectangleShape topWall, bottomWall, leftWall, rightWall, lPaddle, rPaddle;
    sf::CircleShape ball;
    float ballDx, ballDy;
    int lScore, rScore;

    float getPaddleCenter(sf::Shape&);
    float getBallCenter(sf::Shape&);
    float getBallOffset(sf::Shape&, sf::Shape&);
    void initializePlay();
    void executePlay(sf::RenderWindow&);
    void resetBall();
}

float play::getPaddleCenter(sf::Shape& paddle) {
    return paddle.getPosition().y + PADDLE_LENGTH/2;
}

float play::getBallCenter(sf::Shape& ball) {
    return ball.getPosition().y + BALL_RADIUS;
}

float play::getBallOffset(sf::Shape& ball, sf::Shape& paddle) {
    return getBallCenter(ball) - getPaddleCenter(paddle);
}

void play::resetBall() {
    // place ball randomly along center axis
    ball.setPosition(WINDOW_WIDTH/2 - BALL_RADIUS/2, std::rand() % (WINDOW_HEIGHT - WALL_THICKNESS * 2 - BALL_RADIUS * 2) + WALL_THICKNESS);
    ballDx = -BALL_STEP;
    // ballDy goes either straight or at either angle toward the player
    ballDy = (std::rand() % 3 - 1) * BALL_STEP/2;
}

void play::initializePlay() {
    std::srand((int) std::time(NULL));

    // create line dividing play areas
    divider[0] = sf::Vertex(sf::Vector2f(WINDOW_WIDTH/2, 0));
    divider[1] = sf::Vertex(sf::Vector2f(WINDOW_WIDTH/2, WINDOW_HEIGHT));

    // create top and bottom walls
    topWall = sf::RectangleShape(sf::Vector2f(WINDOW_WIDTH, WALL_THICKNESS));
    bottomWall = sf::RectangleShape(sf::Vector2f(WINDOW_WIDTH, WALL_THICKNESS));
    topWall.setPosition(0, 0);
    bottomWall.setPosition(0, WINDOW_HEIGHT - WALL_THICKNESS);

    // create offscreen left and right walls
    leftWall = sf::RectangleShape(sf::Vector2f(WALL_THICKNESS, WINDOW_HEIGHT));
    rightWall = sf::RectangleShape(sf::Vector2f(WALL_THICKNESS, WINDOW_HEIGHT));
    leftWall.setPosition(-WALL_THICKNESS, 0);
    rightWall.setPosition(WINDOW_WIDTH, 0);

    // create paddles
    lPaddle = sf::RectangleShape(sf::Vector2f(PADDLE_THICKNESS, PADDLE_LENGTH));
    rPaddle = sf::RectangleShape(sf::Vector2f(PADDLE_THICKNESS, PADDLE_LENGTH));
    lPaddle.setPosition(PADDLE_SPACE, WINDOW_HEIGHT/2 - PADDLE_LENGTH/2);
    rPaddle.setPosition(WINDOW_WIDTH - PADDLE_THICKNESS - PADDLE_SPACE, WINDOW_HEIGHT/2 - PADDLE_LENGTH/2);

    // create ball
    ball = sf::CircleShape (BALL_RADIUS);
    resetBall();

    // reset scores
    lScore = 0;
    rScore = 0;
}

void play::executePlay(sf::RenderWindow& window)
{
    // rPaddle AI
    if (std::fabs(getBallOffset(ball, rPaddle)) > PADDLE_LENGTH/2)
    {
        rPaddle.move(0, getBallOffset(ball, rPaddle)/R_PADDLE_ACCEL);
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
        ballDy = std::fabs(ballDy);
    } else if (ball.getGlobalBounds().intersects(bottomWall.getGlobalBounds())) {
        ballDy = -std::fabs(ballDy);
    }
    // bounce ball off paddles
    if (ball.getGlobalBounds().intersects(lPaddle.getGlobalBounds())) {
        ballDy = getBallOffset(ball, lPaddle)/MAX_BALL_OFFSET * BALL_STEP;
        ballDx = -ballDx;
    } else if (ball.getGlobalBounds().intersects(rPaddle.getGlobalBounds())) {
        ballDy = getBallOffset(ball, rPaddle)/MAX_BALL_OFFSET * BALL_STEP;
        ballDx = -ballDx;
    }
    // check if ball hit either goal
    if (ball.getGlobalBounds().intersects(leftWall.getGlobalBounds())) {
        rScore++;
        resetBall();
    } else if (ball.getGlobalBounds().intersects(rightWall.getGlobalBounds())) {
        lScore++;
        resetBall();
    } else {
        ball.move(ballDx, ballDy);
    }

    window.draw(topWall);
    window.draw(bottomWall);
    window.draw(divider, 2, sf::Lines);
    window.draw(lPaddle);
    window.draw(rPaddle);
    window.draw(ball);
}

#endif // PLAY_HPP
