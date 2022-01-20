#include "..\include\menu.hpp"
#include <SFML/Audio.hpp>
#include <string>

using namespace sf;

Menu::Menu() {
    this->speedText = "Speed : 2";
    this->speed = 2;
    this->musicOn = true;
    this->musicText = "Music : On";
    this->isSetting = false;
    initManualText();
}
sf::Text* Menu::getManualText() {
    return manualText;
}
sf::Sprite* Menu::getBGImage() {
    static sf::Texture BGTexture;
    //BGTexture.loadFromFile("pictures/snake.png");
    BGTexture.loadFromFile("pictures/yellow-snake.jpg");
    static sf::Sprite BGImage(BGTexture);
    BGImage.setScale(0.55, 0.5);
    
    return &BGImage;
}

sf::Text* Menu::getSpeedText() {
    static sf::Font font;
    font.loadFromFile("font/comic.ttf");
    static sf::Text text;
    text.setFont(font);
    text.setString(this->speedText);
    text.setFillColor(sf::Color::Yellow);
    text.setPosition(sf::Vector2f(10, 450));
    text.setCharacterSize(20);
    return &text;
}
void Menu::increaseSpeed() {
    this->speed++;
    if (this->speed > 2)
        this->speed = 2;
    this->speedText = "Speed : " + std::to_string(this->speed);
}
void Menu::decreaseSpeed() {
    this->speed--;
    if (this->speed < 1)
        this->speed = 1;
    this->speedText = "Speed : " + std::to_string(this->speed);
}
int Menu::getSpeed() {
    return this->speed;
}

sf::Text* Menu::getMusicText() {
    static sf::Font font;
    font.loadFromFile("font/comic.ttf");
    static sf::Text text;
    text.setFont(font);
    text.setString(this->musicText);
    text.setFillColor(sf::Color::Green);
    text.setPosition(sf::Vector2f(730, 450));
    text.setCharacterSize(20);
    return &text;
}
void Menu::turnMusicOn(Music& music) {
    this->musicOn = true;
    this->musicText = "Music : On";
    music.play();
}
void Menu::turnMusicOff(Music& music) {
    this->musicOn = false;
    this->musicText = "Music : Off";
    music.pause();
}
bool Menu::isMusicOn() {
    return this->musicOn;
}

void Menu::handleSettingEvents(RenderWindow& window, Event& event, Music& music) {
    switch (event.type) {
        case sf::Event::KeyReleased:
            if (event.key.code == sf::Keyboard::Up)
                this->turnMusicOn(music);
            else if (event.key.code == sf::Keyboard::Down)
                this->turnMusicOff(music);
            else if (event.key.code == sf::Keyboard::Add)
                this->increaseSpeed();
            else if (event.key.code == sf::Keyboard::Subtract)
                this->decreaseSpeed();
            break;
        default:
            break;
    }
}
void Menu::checkButtonPressed(sf::RenderWindow& window, bool& isMenu) {
    if (Mouse::isButtonPressed(Mouse::Left))
        if (Mouse::getPosition(window).x >= 10 && Mouse::getPosition(window).x <= 160)
            if (Mouse::getPosition(window).y >= 10 && Mouse::getPosition(window).y <= 60)
                isMenu = false;

    if (Mouse::isButtonPressed(Mouse::Left))
        if (Mouse::getPosition(window).x >= 10 && Mouse::getPosition(window).x <= 160)
            if (Mouse::getPosition(window).y >= 70 && Mouse::getPosition(window).y <= 120)
                isSetting = true;
}
void Menu::drawSettingOptions(RenderWindow& window) {
    window.draw(*getManualText());
    window.draw(*getSpeedText());
    window.draw(*getMusicText()); 
}
void Menu::initManualText() {
    static sf::Font font;
    font.loadFromFile("font/comic.ttf");
    static sf::Text text;
    std::string str("");
    str += "<Esc>   : Back to menu\n";
    str += "<+> : increase speed\n";
    str += "<-> : decrease speed\n";
    str += "<Arrow up>   : turn music on\n";
    str += "<Arrow down> : turn music off\n";
    str += "More <Arrow up> : reset music";
    text.setFont(font);
    text.setString(str);
    text.setFillColor(sf::Color::Yellow);
    text.setPosition(sf::Vector2f(10, 10));
    text.setCharacterSize(20);
    this->manualText = &text;
}
void Menu::initButtons(sf::RenderWindow& window) {
    startButton.setSize(Vector2f(150.f, 50.f));
    startButton.setFillColor(Color::Black);
    startButton.setPosition(Vector2f(10.f, 10.f));
    startButton.setOutlineColor(Color::Yellow);
    startButton.setOutlineThickness(2.f);

    settingButton.setSize(Vector2f(150.f, 50.f));
    settingButton.setFillColor(Color::Black);
    settingButton.setPosition(Vector2f(10.f, 70.f));
    settingButton.setOutlineColor(Color::Yellow);
    settingButton.setOutlineThickness(2.f);

    static sf::Font font;
    font.loadFromFile("font/comic.ttf");
    startText.setFont(font);
    startText.setString("Start");
    startText.setFillColor(sf::Color::Yellow);
    startText.setPosition(sf::Vector2f(60, 22));
    startText.setCharacterSize(20);

    settingText.setFont(font);
    settingText.setString("Setting");
    settingText.setFillColor(sf::Color::Yellow);
    settingText.setPosition(sf::Vector2f(55, 80));
    settingText.setCharacterSize(20);
}
void Menu::drawButtons(sf::RenderWindow& window) {
    window.draw(startButton);
    window.draw(settingButton);
    window.draw(startText);
    window.draw(settingText);
}

void showMenu(sf::RenderWindow& window, Music& music, int& speed) {
    Menu menu;
    bool isMenu = true;
    Sprite* BGImage = menu.getBGImage();
    menu.initButtons(window);
    window.setSize(Vector2u(850, 490));
    sf::FloatRect view(0, 0, 850, 490);
    window.setView(sf::View(view));
    window.setKeyRepeatEnabled(false);
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case Event::Closed:
                    window.close();
                    music.stop();
                    exit(0);
                case sf::Event::KeyReleased:
                    if (event.key.code == sf::Keyboard::Escape && menu.isSetting == true)
                        menu.isSetting = false;
                    if (menu.isSetting == true)
                        menu.handleSettingEvents(window, event, music);
                    break;
                default:
                    break;
            }
        }
        window.clear(Color::Black);
        window.draw(*BGImage);
        menu.checkButtonPressed(window, isMenu);
        if (isMenu == false) {
            speed = menu.getSpeed();
            return;
        }
        if (menu.isSetting == false) menu.drawButtons(window);
        else menu.drawSettingOptions(window);
        window.display();
    }
}