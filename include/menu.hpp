#ifndef MENU_HPP
#define MENU_HPP
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;

class Menu {
private:
    std::string speedText;
    std::string musicText;
    int speed;
    bool musicOn;
    sf::Text* manualText;
    sf::RectangleShape startButton;
    sf::RectangleShape settingButton;
    sf::Text startText;
    sf::Text settingText;
public:
    Menu();
    bool isSetting;
    sf::Sprite* getBGImage(); // Get background image
    sf::Text* getManualText();
    sf::Text* getSpeedText();
    void increaseSpeed();
    void decreaseSpeed();
    int getSpeed();
    sf::Text* getMusicText();
    void turnMusicOn(Music& music);
    void turnMusicOff(Music& music);
    bool isMusicOn();
    void handleSettingEvents(RenderWindow& window, Event& event, Music& music);
    void checkButtonPressed(sf::RenderWindow& window, bool& isMenu);
    void drawSettingOptions(sf::RenderWindow& window);
    void initManualText();
    void initButtons(sf::RenderWindow& window);
    void drawButtons(sf::RenderWindow& window);
};

void showMenu(sf::RenderWindow& window, Music& music, int& speed);

#endif // MENU_HPP_INCLUDED