#include <SFML/Graphics.hpp>
#include "include/menu.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(850, 490), "Snake Game");
    window.setFramerateLimit(60);
    menu gameMenu;
    sf::Text* manualText = gameMenu.getManualText();
    sf::Sprite* BGImage = gameMenu.getBGImage();

    window.setKeyRepeatEnabled(false);
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            switch (event.type) {
                case sf::Event::KeyReleased:
                    if (event.key.code == sf::Keyboard::Escape)
                        window.close();
                    if (event.key.code == sf::Keyboard::Enter)
                        window.close(); // Should go to game
                    if (event.key.code == sf::Keyboard::Up)
                        gameMenu.turnMusicOn();
                    else if (event.key.code == sf::Keyboard::Down)
                        gameMenu.turnMusicOff();
                    else if (event.key.code == sf::Keyboard::Add)
                        gameMenu.increaseSpeed();
                    else if (event.key.code == sf::Keyboard::Subtract)
                        gameMenu.decreaseSpeed();
                    break;
                default:
                    break;
            }
        }
        window.clear(sf::Color::Black);
        window.draw(*BGImage);
        window.draw(*manualText);
        window.draw(*( gameMenu.getSpeedText() ));
        window.draw(*( gameMenu.getMusicText() ));
        window.display();
    }

    return 0;
}

/*#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}
*/