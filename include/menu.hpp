#ifndef MENU_HPP
#define MENU_HPP
#include <SFML/Graphics.hpp>

class menu {
private:
    std::string speedText;
    std::string musicText;
    int speed;
    bool musicOn;
public:
    menu();
    sf::Sprite* getBGImage(); // Get background image
    sf::Text* getManualText();
    sf::Text* getSpeedText();
    void increaseSpeed();
    void decreaseSpeed();
    int getSpeed();

    sf::Text* getMusicText();
    void turnMusicOn();
    void turnMusicOff();
    bool isMusicOn();
};

#endif // MENU_HPP_INCLUDED
