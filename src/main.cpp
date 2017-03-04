#include <SFML/Graphics.hpp>
#include <ctime>
#include <cstdlib>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define PADDLE_WIDTH 20
#define PADDLE_HEIGHT 80
#define BALL_RADIUS 10

#define PADDLE_STEP 4
#define BALL_STEP 8
#define DOWN PADDLE_STEP
#define UP -PADDLE_STEP

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH,WINDOW_HEIGHT), "My window");
    srand((int) time(0));
    int gameOver = 0;

    // game over screen
    // TODO

    // calculate paddle coordinates based on top left corner
    sf::RectangleShape lPaddle(sf::Vector2f(PADDLE_WIDTH,PADDLE_HEIGHT));
    lPaddle.setPosition(20, WINDOW_HEIGHT/2 - PADDLE_HEIGHT/2);
    sf::RectangleShape rPaddle(sf::Vector2f(PADDLE_WIDTH,PADDLE_HEIGHT));
    rPaddle.setPosition(WINDOW_WIDTH - PADDLE_WIDTH - 20, WINDOW_HEIGHT/2 - PADDLE_HEIGHT/2);

    sf::CircleShape ball(BALL_RADIUS);
    int randomBallPos = (rand() % WINDOW_HEIGHT) + 1;
    int balldx, balldy;
    do {
        balldx = (rand() % BALL_STEP * 2) + 1 - BALL_STEP;
        balldy = (rand() % BALL_STEP * 2) + 1 - BALL_STEP;
    } while (abs(balldx) <= 1 || abs(balldy) <= 1);
    ball.setPosition(WINDOW_WIDTH/2 - BALL_RADIUS/2, randomBallPos);

    int rPaddleDir = DOWN;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        if (rPaddle.getGlobalBounds().top + PADDLE_HEIGHT/2 < ball.getGlobalBounds().top + BALL_RADIUS &&
                rPaddle.getGlobalBounds().top + PADDLE_HEIGHT < WINDOW_HEIGHT)
        {
            rPaddle.move(0, DOWN);
        } else if (rPaddle.getGlobalBounds().top + PADDLE_HEIGHT/2 > ball.getGlobalBounds().top + BALL_RADIUS &&
                rPaddle.getGlobalBounds().top > 0)
        {
            rPaddle.move(0, UP);
        }

        // player paddle controls
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) &&
                lPaddle.getGlobalBounds().top > 0)
        {
            lPaddle.move(0, UP);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) &&
                lPaddle.getGlobalBounds().top + PADDLE_HEIGHT < WINDOW_HEIGHT)
        {
            lPaddle.move(0, DOWN);
        }

        // move ball
        if ((ball.getGlobalBounds().top <= 0 && balldy < 0) ||
            (ball.getGlobalBounds().top + BALL_RADIUS * 2 >= WINDOW_HEIGHT && balldy > 0)) {
            balldy = -balldy;
        }
        if (ball.getGlobalBounds().intersects(lPaddle.getGlobalBounds()) ||
            ball.getGlobalBounds().intersects(rPaddle.getGlobalBounds())) {
            balldx = -balldx;
        }
        ball.move(balldx, balldy);

        window.clear(sf::Color::Black);
        if (!gameOver) {
            window.draw(lPaddle);
            window.draw(rPaddle);
            window.draw(ball);
        } else {
            //window.draw(scoreScreen);
        }
        window.display();
    }

    return 0;
}
