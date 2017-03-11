#include <SFML/Graphics.hpp>
#include "constants.hpp"
#include "SplashState.hpp"
#include "PlayState.hpp"

SplashState::SplashState()
    : State()
    , font()
    , titleText()
    , playText()
{
    font.loadFromFile("PressStart2P.ttf");

    titleText.setFont(font);
    titleText.setCharacterSize(100);
    titleText.setString("P O N G");
    titleText.setOrigin(
            titleText.getLocalBounds().left + titleText.getLocalBounds().width/2,
            titleText.getLocalBounds().top + titleText.getLocalBounds().height/2
            );
    titleText.setPosition(WINDOW_WIDTH/2, WINDOW_HEIGHT/2 - SPACING * 4);

    playText.setFont(font);
    playText.setCharacterSize(30);
    playText.setString("Press spacebar to play");
    playText.setOrigin(
            playText.getLocalBounds().left + playText.getLocalBounds().width/2,
            playText.getLocalBounds().top + playText.getLocalBounds().height/2
            );
    playText.setPosition(WINDOW_WIDTH/2, WINDOW_HEIGHT/2 + SPACING * 4);
}

void SplashState::execute(sf::RenderWindow& window) {
    (void)window;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        setNextState(new PlayState());
    }
}

void SplashState::draw(sf::RenderWindow& window) {
    window.draw(titleText);
    window.draw(playText);
}
