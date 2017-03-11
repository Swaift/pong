#include <SFML/Graphics.hpp>
#include "constants.hpp"
#include "GameOverState.hpp"
#include "PlayState.hpp"

GameOverState::GameOverState(bool win)
    : State()
    , font()
    , gameResultText()
    , playAgainText()
{
    font.loadFromFile("PressStart2P.ttf");

    gameResultText.setFont(font);
    gameResultText.setCharacterSize(50);
    if (win == true) {
        gameResultText.setString("You win!");
    } else {
        gameResultText.setString("You lose!");
    }
    gameResultText.setOrigin(
            gameResultText.getLocalBounds().left + gameResultText.getLocalBounds().width/2,
            gameResultText.getLocalBounds().top + gameResultText.getLocalBounds().height/2
            );
    gameResultText.setPosition(WINDOW_WIDTH/2, WINDOW_HEIGHT/2 - SPACING * 4);

    playAgainText.setFont(font);
    playAgainText.setCharacterSize(30);
    playAgainText.setString("Press spacebar to play again");
    playAgainText.setOrigin(
            playAgainText.getLocalBounds().left + playAgainText.getLocalBounds().width/2,
            playAgainText.getLocalBounds().top + playAgainText.getLocalBounds().height/2
            );
    playAgainText.setPosition(WINDOW_WIDTH/2, WINDOW_HEIGHT/2 + SPACING * 4);
}

void GameOverState::execute(sf::RenderWindow& window) {
    (void)window;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        setNextState(new PlayState());
    }
}

void GameOverState::draw(sf::RenderWindow& window) {
    window.draw(gameResultText);
    window.draw(playAgainText);
}
