#ifndef CORE_HPP
#define CORE_HPP

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <cmath>

using namespace sf;

class Info {
public:
    int height, width;
    bool restart;
    int sizeOfTiles;
    Texture tileTexture, snakeTexture, appleTexture, wallTexture;
    Sprite groundSprite, appleSprite, wallSprite;
    CircleShape snakeSprite;
    Info();
};

class Snake {
public:
    Snake();
    int len;
    int x[100], y[100];
    std::string direction;
};

struct Apple {int x, y;}; // apple[2];
struct Wall {int x[3], y[3];}; // wall[2];

void gameover(RenderWindow& window, Info& info);

void updateSnake(Snake& snake);

void checkCollision(RenderWindow& window, Info& info, Snake& snake1, Snake& snake2);

void drawSnake(RenderWindow& window, Info& info, Snake& snake);

void drawApple(RenderWindow& window, Info& info);

void drawWall(RenderWindow& window, Info& info);

void initWalls(Info& info);

void drawGroundTiles(RenderWindow& window, Info& info);

void resizeWindow(Info info, RenderWindow& window);

void checkKeyboard(Snake& snake1, Snake& snake2);

void checkCollisionWithApples(Snake& snake1, Info& info, bool& flag);

void handleSpeed(Snake& snake1, Snake& snake2, Clock& clock, int speed);

void initAllThings(Snake& snake1, Snake& snake2, Info& info);

void showGame(RenderWindow& window, int speed);

#endif // CORE_HPP_INCLUDED