#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <time.h>

using namespace sf;

class Info {
public:
    int height = 50 , width = 30;
    int sizeOfTiles = 20;
    Texture tileTexture, snakeTexture, appleTexture, wallTexture;
    Sprite groundSprite, snakeSprite, appleSprite;

    Info() {
        tileTexture.loadFromFile("pictures/green2.jfif");
        snakeTexture.loadFromFile("pictures/red.jfif", sf::IntRect(1, 1, 20, 20));
        appleTexture.loadFromFile("pictures/apple.png", sf::IntRect(1, 1, 20, 20));
        groundSprite.setTexture(tileTexture);
        snakeSprite.setTexture(snakeTexture);
        appleSprite.setTexture(appleTexture);
    }
};

class Snake {
public:
    int len = 4;
    int x[100], y[100];
    std::string direction;
};

struct Apple {int x, y;} apple[2];

class Wall {
public:
    int x[3];
    int y[3];
};

void gameover(RenderWindow& window, Info& info) {
    Font font;
    font.loadFromFile("font/comic.ttf");
    Text text;
    text.setFont(font);
    text.setString("Game Over :)");
    text.setColor(Color::Black);
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
            if (Keyboard::isKeyPressed(Keyboard::Enter))
                window.close();
            if (Keyboard::isKeyPressed(Keyboard::Escape))
                window.close();
        }

        window.clear(Color::Red);
        window.draw(text);
        window.display();
    }
}

void updateSnake(Snake& snake) {
    for (int i = snake.len; i > 0; i--) {
        snake.x[i] = snake.x[i-1];
        snake.y[i] = snake.y[i-1];
    }

    if (snake.direction == "down")  {snake.y[0] += 1;}
    if (snake.direction == "left")  {snake.x[0] -= 1;}
    if (snake.direction == "right") {snake.x[0] += 1;}
    if (snake.direction == "up")    {snake.y[0] -= 1;}
}

void checkCollision(RenderWindow& window, Info& info, Snake& snake) {
    // check eating apples
    for (int i = 0; i <= 0; i++) { // TODO : should become i <= 1
        if ((snake.x[0] == apple[i].x) && (snake.y[0] == apple[i].y)) {
            snake.len++;
            apple[i].x = rand() % info.height;
            apple[i].y = rand() % info.width;
        }
    }

    // pass border of the window
    if (snake.x[0] > info.height) {snake.x[0] = 0 ;}
    if (snake.y[0] > info.width) {snake.y[0] = 0 ;}
    if (snake.x[0] < 0) {snake.x[0] = info.height ;}
    if (snake.y[0] < 0) {snake.y[0] = info.width ;}

    // check collision with itself
    for (int i = 4; i < snake.len; i++)
        if (snake.x[0] == snake.x[i] && snake.y[0] == snake.y[i])
            gameover(window, info);
}

void drawSnake(RenderWindow& window, Info& info, Snake& snake) {
    for (int i = 0; i < snake.len; i++) {
        info.snakeSprite.setPosition(snake.x[i] * info.sizeOfTiles,
                                     snake.y[i] * info.sizeOfTiles);
        window.draw(info.snakeSprite);
    }
}

void drawApple(RenderWindow& window, Info& info) {
    info.appleSprite.setPosition(apple[0].x * info.sizeOfTiles,
                                 apple[0].y * info.sizeOfTiles);
    window.draw(info.appleSprite);
}

void drawGroundTiles(RenderWindow& window, Info& info) {
    for (int i = 0; i < info.height; i++) {
        for (int j = 0; j < info.width; j++) {
                info.groundSprite.setPosition(i * info.sizeOfTiles,
                                              j * info.sizeOfTiles);
                window.draw(info.groundSprite);
        }
    }
}

RenderWindow* createWindow(Info info) {
    int height = info.height * info.sizeOfTiles;
    int width = info.width * info.sizeOfTiles;
    static RenderWindow window(VideoMode(height, width), "Snake Game :)");
    return &window;
}

void checkKeyboard1(Snake& snake) {
    if (Keyboard::isKeyPressed(Keyboard::Left) && snake.direction != "right")
        snake.direction = "left";
    if (Keyboard::isKeyPressed(Keyboard::Right) && snake.direction != "left")
        snake.direction = "right";
    if (Keyboard::isKeyPressed(Keyboard::Up) && snake.direction != "down")
        snake.direction = "up";
    if (Keyboard::isKeyPressed(Keyboard::Down) && snake.direction != "up") 
        snake.direction = "down";
}

void checkKeyboard2(Snake& snake) {
    if (Keyboard::isKeyPressed(Keyboard::A) && snake.direction != "right")
        snake.direction = "left";
    if (Keyboard::isKeyPressed(Keyboard::D) && snake.direction != "left")
        snake.direction = "right";
    if (Keyboard::isKeyPressed(Keyboard::W) && snake.direction != "down")
        snake.direction = "up";
    if (Keyboard::isKeyPressed(Keyboard::S) && snake.direction != "up") 
        snake.direction = "down";
}

int main() {
    Info* info = new Info();
    auto window = createWindow(*info);
    srand(time(0));    
    window->setFramerateLimit(15);
    Snake snake1, snake2;
    snake1.x[0] = 1; snake1.y[0] = 1;
    apple[0].x = 10; apple[0].y = 10;

    while (window->isOpen()) {
        Event event;
        while (window->pollEvent(event)) {
            if(event.type == Event::Closed)
                window->close();
        }
        checkKeyboard1(snake1);
        updateSnake(snake1);
        checkCollision(*window, *info, snake1);

        window->clear();
        drawGroundTiles(*window, *info);
        drawSnake(*window, *info, snake1);
        drawApple(*window, *info);
        window->display();
    }
    return 0;
}