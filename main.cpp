#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "include/menu.hpp"
#include "include/core.hpp"
#include <iostream>
using namespace sf;

int main() {
    RenderWindow window(VideoMode(850, 490), "Snake Game");
    window.setFramerateLimit(60);
    Music music;
    music.openFromFile("music/backgroundMusic.ogg");

    int speed;
    while (1) {
        music.play();
        showMenu(window, music, speed);
        showGame(window, speed);
    }
    return 0;
}