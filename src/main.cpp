#include <SFML/Graphics.hpp>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define PADDLE_WIDTH 20
#define PADDLE_HEIGHT 80
#define BALL_RADIUS 10

#define PADDLE_STEP 4
#define DOWN PADDLE_STEP
#define UP -PADDLE_STEP

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH,WINDOW_HEIGHT), "My window");

    sf::Clock clock;

    // calculate paddle coordinates based on top left corner
    sf::RectangleShape lPaddle(sf::Vector2f(PADDLE_WIDTH,PADDLE_HEIGHT));
    lPaddle.setPosition(20, WINDOW_HEIGHT/2 - PADDLE_HEIGHT/2);
    sf::RectangleShape rPaddle(sf::Vector2f(PADDLE_WIDTH,PADDLE_HEIGHT));
    rPaddle.setPosition(WINDOW_WIDTH - PADDLE_WIDTH - 20, WINDOW_HEIGHT/2 - PADDLE_HEIGHT/2);

    sf::CircleShape ball(BALL_RADIUS);
    ball.setPosition(WINDOW_WIDTH/2 - BALL_RADIUS/2, WINDOW_HEIGHT/2 - BALL_RADIUS/2);

    int rPaddleDir = DOWN;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // 60 fps is approximately 0.16 seconds per frame
        if (clock.getElapsedTime().asSeconds() > 0.016f) {
            // AI for rPaddle
            if (rPaddle.getGlobalBounds().top + PADDLE_HEIGHT == WINDOW_HEIGHT) {
                rPaddleDir = UP;
            } else if (rPaddle.getGlobalBounds().top == 0) {
                rPaddleDir = DOWN;
            }
            rPaddle.move(0, rPaddleDir);

            // player paddle controls
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) &&
                    lPaddle.getGlobalBounds().top != 0) {
                lPaddle.move(0, UP);
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) &&
                    lPaddle.getGlobalBounds().top + PADDLE_HEIGHT != WINDOW_HEIGHT) {
                lPaddle.move(0, DOWN);
            }
        }

        window.clear(sf::Color::Black);
        window.draw(lPaddle);
        window.draw(rPaddle);
        window.draw(ball);
        window.display();
    }

    return 0;
}
