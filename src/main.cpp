#include <SFML/Graphics.hpp>
#include <ctime>
#include <cstdlib>
#include <cmath>

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 800

#define PADDLE_THICKNESS 20
#define PADDLE_LENGTH 80
#define BALL_RADIUS 10
#define WALL_THICKNESS 20
#define PADDLE_SPACE 20

#define MAX_BALL_OFFSET (PADDLE_LENGTH/2 + BALL_RADIUS)
#define R_PADDLE_ACCEL 7 // lower is more acceleration
#define BALL_STEP 10

float getPaddleCenter(sf::Shape& paddle) {
    return paddle.getPosition().y + PADDLE_LENGTH/2;
}

float getBallCenter(sf::Shape& ball) {
    return ball.getPosition().y + BALL_RADIUS;
}

float getBallOffset(sf::Shape& ball, sf::Shape& paddle) {
    return getBallCenter(ball) - getPaddleCenter(paddle);
}

void processPlay(sf::RenderWindow& window,
                 sf::Shape& topWall,
                 sf::Shape& bottomWall,
                 sf::Shape& lPaddle,
                 sf::Shape& rPaddle,
                 sf::Shape& ball,
                 float& ballDx,
                 float& ballDy)
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
    ball.move(ballDx, ballDy);

    window.draw(topWall);
    window.draw(bottomWall);
    window.draw(lPaddle);
    window.draw(rPaddle);
    window.draw(ball);
}

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH,WINDOW_HEIGHT), "My window");

    // initialize state machine
    enum class State {
        SPLASH,
        PLAY,
        GAMEOVER
    };
    State currentState = State::PLAY;
    State nextState = State::PLAY;
    
    // create top and bottom walls
    sf::RectangleShape topWall(sf::Vector2f(WINDOW_WIDTH, WALL_THICKNESS));
    sf::RectangleShape bottomWall(sf::Vector2f(WINDOW_WIDTH, WALL_THICKNESS));
    topWall.setPosition(0, 0);
    bottomWall.setPosition(0, WINDOW_HEIGHT - WALL_THICKNESS);

    // create paddles
    sf::RectangleShape lPaddle(sf::Vector2f(PADDLE_THICKNESS, PADDLE_LENGTH));
    sf::RectangleShape rPaddle(sf::Vector2f(PADDLE_THICKNESS, PADDLE_LENGTH));
    lPaddle.setPosition(PADDLE_SPACE, WINDOW_HEIGHT/2 - PADDLE_LENGTH/2);
    rPaddle.setPosition(WINDOW_WIDTH - PADDLE_THICKNESS - PADDLE_SPACE, WINDOW_HEIGHT/2 - PADDLE_LENGTH/2);

    // place ball randomly along center axis
    srand((int) time(NULL));
    sf::CircleShape ball(BALL_RADIUS);
    ball.setPosition(WINDOW_WIDTH/2 - BALL_RADIUS/2, rand() % (WINDOW_HEIGHT - WALL_THICKNESS * 2 - BALL_RADIUS * 2) + WALL_THICKNESS);
    float ballDx = -BALL_STEP;
    // ballDy can either be -BALL_STEP/2, 0, or BALL_STEP/2
    float ballDy = (rand() % 3 - 1) * BALL_STEP/2;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        window.clear(sf::Color::Black);

        currentState = nextState;
        switch (currentState) {
            case State::SPLASH:
                // TODO
                nextState = State::SPLASH;
                break;
            case State::PLAY:
                processPlay(window,
                            topWall,
                            bottomWall,
                            lPaddle,
                            rPaddle,
                            ball,
                            ballDx,
                            ballDy);
                nextState = State::PLAY;
                break;
            case State::GAMEOVER:
                // TODO
                nextState = State::GAMEOVER;
                break;
        }

        window.display();
    }

    return 0;
}
