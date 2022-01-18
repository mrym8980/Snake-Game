#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <time.h>

using namespace sf;

class Info {
public:
    int height = 25 , width = 15;
    int sizeOfTiles = 45;
    Texture tileTexture, snakeTexture, appleTexture, wallTexture;
    Sprite groundSprite, appleSprite, wallSprite;
    CircleShape snakeSprite;

    Info() {
        CircleShape newSnakeSprite(sizeOfTiles/2, 8);

        tileTexture.loadFromFile("pictures/blue2.jpg");
        snakeTexture.loadFromFile("pictures/sname.jpg",IntRect(1, 1, 45, 45));
        appleTexture.loadFromFile("pictures/Untitled-1.psd");
        wallTexture.loadFromFile("pictures/stone.jpg");

        groundSprite.setTexture(tileTexture);
        newSnakeSprite.setTexture(&snakeTexture);
        snakeSprite = newSnakeSprite; 
        appleSprite.setTexture(appleTexture);
        wallSprite.setTexture(wallTexture);
    }
};

class Snake {
public:
    int len = 4;
    int x[100], y[100];
    std::string direction;
};

struct Apple {int x, y;} apple[2];
struct Wall {int x[3], y[3];} wall[2];

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

void checkCollision(RenderWindow& window, Info& info, Snake& snake1, Snake& snake2) {
    // check eating apples
    bool flag = false;
    for (int i = 0; i <= 1; i++) {
        if ((snake1.x[0] == apple[i].x) && (snake1.y[0] == apple[i].y)) {
            snake1.len++;
            while (!flag)
            {
                flag = true;
                apple[i].x = rand() % info.height;
                apple[i].y = rand() % info.width;

                for (int j = 0; j < 3; j++){
                    if (apple[i].x == wall[0].x[j] && apple[i].y == wall[0].y[j]){flag = false ; break ;}
                    if (apple[i].x == wall[1].x[j] && apple[i].y == wall[1].y[j]){flag = false ; break ;}
                }
            }
        }
    }

    // check collision with the wall
    for (int i = 0; i <= 1; i++)
        for (int j = 0; j <= 2; j++)
            if ((snake1.x[0] == wall[i].x[j]) && (snake1.y[0] == wall[i].y[j]))
                gameover(window, info);

    // pass border of the window
    if (snake1.x[0] > info.height) {snake1.x[0] = 0;}
    if (snake1.y[0] > info.width) {snake1.y[0] = 0;}
    if (snake1.x[0] < 0) {snake1.x[0] = info.height;}
    if (snake1.y[0] < 0) {snake1.y[0] = info.width;}

    // check collision with itself
    for (int i = 4; i < snake1.len; i++)
        if (snake1.x[0] == snake1.x[i] && snake1.y[0] == snake1.y[i])
            gameover(window, info);

    // check collision with snake2
    for (int i = 0; i < snake2.len; i++)
        if (snake1.x[0] == snake2.x[i] && snake1.y[0] == snake2.y[i])
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
    for (int i = 0; i <= 1; i++) {
        info.appleSprite.setPosition(apple[i].x * info.sizeOfTiles,
                                     apple[i].y * info.sizeOfTiles);
        window.draw(info.appleSprite);
    }
}

void drawWall(RenderWindow& window, Info& info) {
    for (int i = 0; i <= 1; i++) {
        for(int j = 0; j <= 2; j++) {
            info.wallSprite.setPosition(wall[i].x[j] * info.sizeOfTiles,
                                        wall[i].y[j] * info.sizeOfTiles);
            window.draw(info.wallSprite);
        }
    }        
}

void initWalls(Info& info) {
    //Vertical wall
    bool flag = true;
    do{
        flag = true;
        wall[0].x[0] = rand() % info.height ; wall[0].y[0] = rand() % info.width;

        if (wall[0].x[0] == 1 && wall[0].y[0] == 1)flag = false;//check Collision with snake 
        if (wall[0].x[0] == 10 && wall[0].y[0] == 10)flag = false;

        if (wall[0].x[0] == 5 && wall[0].y[0] == 7)flag = false;//check Collision with fish
        if (wall[0].x[0] == 1 && wall[0].y[0] == 9)flag = false;

        for (int i = 1; i <= 2; i++) {
            wall[0].x[i] = wall[0].x[0];
            wall[0].y[i] = wall[0].y[i - 1] + 1;

            //std::cout << "wall vertical [0] [1] [2]" << std::endl;
            //std::cout << wall[0].x[0] << "\t" << wall[0].x[1] << "\t" << wall[0].x[2] << std::endl;
            //std::cout << wall[0].y[0] << "\t" << wall[0].y[1] << "\t" << wall[0].y[2] << std::endl;

            if (wall[0].x[i] == 1 && wall[0].y[i] == 1){flag = false;break;}
            else if (wall[0].x[i] == 10 && wall[0].y[i] == 10){flag = false;break;}
        }
    }while(wall[0].y[0] > info.width - 3 || !flag);


    //Horizontal wall
    
    do {
        flag = true;
        wall[1].x[0] = rand() % info.height; wall[1].y[0] = rand() % info.width;

        if (wall[1].x[0] == 1 && wall[1].y[0] == 1)flag = false;//check Collision with snake
        if (wall[1].x[0] == 10 && wall[1].y[0] == 10)flag = false;

        if (wall[1].x[0] == 5 && wall[1].y[0] == 7)flag = false;//check Collision with fish
        if (wall[1].x[0] == 1 && wall[1].y[0] == 9)flag = false;

        else if (abs (wall[1].x[0] - wall[0].x[1]) <= 3)flag = false;//distance between walls
        else if (abs (wall[1].y[0] - wall[0].y[1]) <= 4)flag = false;//distance between walls

        for (int i = 1; i <= 2; i++) {
            wall[1].x[i] = wall[1].x[i - 1] + 1;
            wall[1].y[i] = wall[1].y[0];

            //std::cout << "wall h [0] [1] [2]" << std::endl;
            //std::cout << wall[1].x[0] << "\t" << wall[1].x[1] << "\t" << wall[1].x[2] << std::endl;
            //std::cout << wall[1].y[0] << "\t" << wall[1].y[1] << "\t" << wall[1].y[2] << std::endl;

            if (wall[1].x[i] == 1 && wall[1].y[i] == 1){flag = false;break;}
            else if (wall[1].x[i] == 10 && wall[1].y[i] == 10){flag = false;break;}

        }
    }while (wall[1].x[0] > info.height - 3 || !flag);

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

void checkKeyboard(Snake& snake1, Snake& snake2) {
    // check keyboards for snake1
    if (Keyboard::isKeyPressed(Keyboard::Left) && snake1.direction != "right")
        snake1.direction = "left";
    if (Keyboard::isKeyPressed(Keyboard::Right) && snake1.direction != "left")
        snake1.direction = "right";
    if (Keyboard::isKeyPressed(Keyboard::Up) && snake1.direction != "down")
        snake1.direction = "up";
    if (Keyboard::isKeyPressed(Keyboard::Down) && snake1.direction != "up") 
        snake1.direction = "down";

    // check keyboards for snake2
    if (Keyboard::isKeyPressed(Keyboard::A) && snake2.direction != "right")
        snake2.direction = "left";
    if (Keyboard::isKeyPressed(Keyboard::D) && snake2.direction != "left")
        snake2.direction = "right";
    if (Keyboard::isKeyPressed(Keyboard::W) && snake2.direction != "down")
        snake2.direction = "up";
    if (Keyboard::isKeyPressed(Keyboard::S) && snake2.direction != "up") 
        snake2.direction = "down";
}

int main() {
    Info* info = new Info();
    auto window = createWindow(*info);
    srand(time(0));
    window->setFramerateLimit(15);
    Snake snake1, snake2; 
    snake1.x[0] = 1; snake1.y[0] = 1;
    snake2.x[0] = 10; snake2.y[0] = 10;

    apple[0].x = 5; apple[0].y = 7;
    apple[1].x = 9; apple[1].y = 1;
    initWalls(*info);
    
    while (window->isOpen()) {
        Event event;
        while (window->pollEvent(event)) {
            if(event.type == Event::Closed)
                window->close();
        }
        checkKeyboard(snake1, snake2);
        updateSnake(snake1);
        updateSnake(snake2);
        checkCollision(*window, *info, snake1, snake2);
        checkCollision(*window, *info, snake2, snake1);

        window->clear();
        drawGroundTiles(*window, *info);
        drawSnake(*window, *info, snake1);
        drawSnake(*window, *info, snake2);
        drawApple(*window, *info);
        drawWall(*window, *info);
        window->display();
    }
    return 0;
}