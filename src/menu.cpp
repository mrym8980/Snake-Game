#include "..\include\menu.hpp"
//#include <menu.hpp>
#include <string>

menu::menu() {
    this->speedText = "Speed : 2";
    this->speed = 2;
    this->musicOn = true;
    this->musicText = "Music : On";
}
sf::Text* menu::getManualText() {
    static sf::Font font;
    font.loadFromFile("font/comic.ttf");
    static sf::Text text;
    static std::string str("");
    str += "<Enter> : start\n";
    str += "<Esc>   : exit\n";
    str += "<+> : increase speed\n";
    str += "<-> : decrease speed\n";
    str += "<Arrow up>   : turn music on\n";
    str += "<Arrow down> : turn music off";
    text.setFont(font);
    text.setString(str);
    text.setFillColor(sf::Color::Yellow);
    text.setPosition(sf::Vector2f(10, 10));
    text.setCharacterSize(20);
    return &text;
}
sf::Sprite* menu::getBGImage() {
    static sf::Texture BGTexture;
    BGTexture.loadFromFile("pictures/snake.png");
    static sf::Sprite BGImage(BGTexture);
    return &BGImage;
}

sf::Text* menu::getSpeedText() {
    static sf::Font font;
    font.loadFromFile("font/comic.ttf");
    static sf::Text text;
    text.setFont(font);
    text.setString(this->speedText);
    text.setFillColor(sf::Color::Blue);
    text.setPosition(sf::Vector2f(10, 450));
    text.setCharacterSize(20);
    return &text;
}
void menu::increaseSpeed() {
    this->speed++;
    if (this->speed > 3)
        this->speed = 3;
    this->speedText = "Speed : " + std::to_string(this->speed);
}
void menu::decreaseSpeed() {
    this->speed--;
    if (this->speed < 1)
        this->speed = 1;
    this->speedText = "Speed : " + std::to_string(this->speed);
}
int menu::getSpeed() {
    return this->speed;
}

sf::Text* menu::getMusicText() {
    static sf::Font font;
    font.loadFromFile("font/comic.ttf");
    static sf::Text text;
    text.setFont(font);
    text.setString(this->musicText);
    text.setFillColor(sf::Color::Blue);
    text.setPosition(sf::Vector2f(730, 450));
    text.setCharacterSize(20);
    return &text;
}
void menu::turnMusicOn() {
    this->musicOn = true;
    this->musicText = "Music : On";
}
void menu::turnMusicOff() {
    this->musicOn = false;
    this->musicText = "Music : Off";
}
bool menu::isMusicOn() {
    return this->musicOn;
}
