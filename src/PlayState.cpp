#include <SFML/Graphics.hpp>
#include "constants.hpp"
#include "State.hpp"
#include "PlayState.hpp"
#include "Ball.hpp"
#include "Score.hpp"
#include "GameOverState.hpp"
#include <cmath> // fabs()

PlayState::PlayState() 
    : State()
    , divider({
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
    , font()
    , lScore()
    , rScore()
    , wait(WAIT_TIME)
{
    topWall.setPosition(0, 0);
    bottomWall.setPosition(0, WINDOW_HEIGHT - WALL_THICKNESS);

    leftWall.setPosition(-WALL_THICKNESS, 0);
    rightWall.setPosition(WINDOW_WIDTH, 0);

    lPaddle.setPosition(SPACING, WINDOW_HEIGHT/2 - PADDLE_LENGTH/2);
    rPaddle.setPosition(WINDOW_WIDTH - PADDLE_THICKNESS - SPACING, WINDOW_HEIGHT/2 - PADDLE_LENGTH/2);

    font.loadFromFile("PressStart2P.ttf");

    lScore.setFont(font);
    lScore.setCharacterSize(100);
    lScore.setPosition(WINDOW_WIDTH/2 - lScore.getLocalBounds().width - 8, WALL_THICKNESS + SPACING);

    rScore.setFont(font);
    rScore.setCharacterSize(100);
    rScore.setPosition(WINDOW_WIDTH/2 + SPACING, WALL_THICKNESS + SPACING);

}

void PlayState::execute(sf::RenderWindow& window) {
    // rPaddle AI (do not move if pausing after point)
    if (std::fabs(getBallOffset(rPaddle)) > PADDLE_LENGTH/2 && wait == 0)
    {
        rPaddle.move(0, getBallOffset(rPaddle)/R_PADDLE_ACCEL);
    }
    restrictPaddle(rPaddle);

    // player paddle y-position same as mouse unless out of screen
    lPaddle.setPosition(lPaddle.getPosition().x, sf::Mouse::getPosition(window).y - PADDLE_LENGTH/2);
    restrictPaddle(lPaddle);

    // bounce ball off walls
    if (ball.getGlobalBounds().intersects(topWall.getGlobalBounds())) {
        ball.setDy(std::fabs(ball.getDy()));
    } else if (ball.getGlobalBounds().intersects(bottomWall.getGlobalBounds())) {
        ball.setDy(-std::fabs(ball.getDy()));
    }
    // bounce ball off paddles
    if (ball.getGlobalBounds().intersects(lPaddle.getGlobalBounds())) {
        ball.setDy(getBallOffset(lPaddle)/MAX_BALL_OFFSET * BALL_STEP);
        ball.setDx(std::fabs(ball.getDx()));
    } else if (ball.getGlobalBounds().intersects(rPaddle.getGlobalBounds())) {
        ball.setDy(getBallOffset(rPaddle)/MAX_BALL_OFFSET * BALL_STEP);
        ball.setDx(-std::fabs(ball.getDx()));
    }
    // reset ball and pause after each point
    if (ball.getGlobalBounds().intersects(leftWall.getGlobalBounds())) {
        rScore.setScore(rScore.getScore() + 1);
        wait = WAIT_TIME;
        ball.reset();
    } else if (ball.getGlobalBounds().intersects(rightWall.getGlobalBounds())) {
        lScore.setScore(lScore.getScore() + 1);
        wait = WAIT_TIME;
        ball.reset();
    } else if (wait > 0) {
        wait--;
    } else {
        ball.move(ball.getDx(), ball.getDy());
    }
    // check for win/lose (first to 5 points)
    if (lScore.getScore() >= 5) {
        setNextState(new GameOverState(true));
    } else if (rScore.getScore() >= 5) {
        setNextState(new GameOverState(false));
    }
}

void PlayState::draw(sf::RenderWindow& window) {
    window.draw(topWall);
    window.draw(bottomWall);
    window.draw(divider, 2, sf::Lines);
    window.draw(lPaddle);
    window.draw(rPaddle);
    window.draw(lScore);
    window.draw(rScore);
    if (wait == 0) {
        window.draw(ball);
    }
}

void PlayState::restrictPaddle(sf::Shape& paddle) {
    if (paddle.getPosition().y < topWall.getPosition().y + WALL_THICKNESS) {
        paddle.setPosition(paddle.getPosition().x, topWall.getPosition().y + WALL_THICKNESS);
    } else if (paddle.getPosition().y + PADDLE_LENGTH > bottomWall.getPosition().y) {
        paddle.setPosition(paddle.getPosition().x, bottomWall.getPosition().y - PADDLE_LENGTH);
    }
}

float PlayState::getBallOffset(sf::Shape& paddle) {
    return ball.getCenter() - (paddle.getPosition().y + PADDLE_LENGTH/2);
}
