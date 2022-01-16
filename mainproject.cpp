#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <time.h>

using namespace sf;

int N = 50 , M = 30;
int size = 20;
int w = size * N;
int h = size * M;

int dir,num = 4;

struct snake
{int x,y;} s[100];

struct Fruct
{int x,y;} f;

struct Stone
{int x,y;} st[3];

void Gameover()
{
    RenderWindow window(VideoMode(w,h) , "Snake Game :)");
    while (window.isOpen())
    {
        Event e;
        while(window.pollEvent(e))
        {
            if(e.type == Event::Closed)
                window.close();
            if(Keyboard::isKeyPressed(Keyboard::Enter))
                window.close();
        }

        window.clear(Color::Black);

        window.display();
    }
    
}


void Tick(){
    for(int i = num ; i > 0 ; i--)
    {
        s[i].x = s[i-1].x;
        s[i].y = s[i-1].y;
    }
    
    //f.x += 1;

    if(dir == 0){s[0].y += 1;}
    if(dir == 1){s[0].x -= 1;}
    if(dir == 2){s[0].x += 1;}
    if(dir == 3){s[0].y -= 1;}

    if ((s[0].x == f.x) && (s[0].y == f.y))
    {
        num++;
        f.x = rand() % N;
        f.y = rand() % M;
    }
    /*for(int i = 0; i < 3; i++)
        if ((s[0].x == st[i].x) && (s[0].y == st[i].y))
            Gameover();*/

    if(s[0].x > N){s[0].x = 0 ;}
    else if(s[0].y > M){s[0].y = 0 ;}
    else if(s[0].x < 0){s[0].x = N ;}
    else if(s[0].y < 0){s[0].y = M ;}

    for(int i = 1; i < num ; i++)
        if(s[0].x == s[i].x && s[0].y == s[i].y){num = i;}
}


int main()
{
    srand(time(0));

    RenderWindow window(VideoMode(w,h) , "Snake Game :)");

    Texture t1 , t2 , t3 , t4;
    t1.loadFromFile("pictures/green2.jfif");
    t2.loadFromFile("pictures/red.jfif", sf::IntRect(1, 1, 20, 20));
    t3.loadFromFile("pictures/apple.png");
    //t4.loadFromFile("stone.jpg");

    Sprite sprite1(t1);
    Sprite sprite2(t2);
    Sprite sprite3(t3);
    //Sprite sprite4(t4);
    
    Clock clock;
    //float timer = 0 , delay = 5;

    f.x = 10; f.y = 10;
    st[0].x = rand() % N; st[0].y = rand() % M;
    for(int i = 1; i <3; i++)
    {
        st[i].x = st[0].x;
        st[i].y = st[i-1].y + 1;
    }
    window.setFramerateLimit(30);

    while (window.isOpen())
    {
        //float time = clock.getElapsedTime().asSeconds();
        //timer += time;
        

        Event e;
        while(window.pollEvent(e))
        {
            if(e.type == Event::Closed)
                window.close();
        }

        if(Keyboard::isKeyPressed(Keyboard::Left)){dir = 1;}
        if(Keyboard::isKeyPressed(Keyboard::Right)){dir = 2;}
        if(Keyboard::isKeyPressed(Keyboard::Up)){dir = 3;}
        if(Keyboard::isKeyPressed(Keyboard::Down)){dir = 0;}


        //if(timer > delay){timer = 0 ; Tick();}

        Tick();


        window.clear();
        ///draw///
        for(int i = 0 ; i < N ; i++)
            for(int j = 0 ; j < M ; j++)
                {
                    sprite1.setPosition(i * size , j * size);
                    window.draw(sprite1);
                }
        
        for(int i = 0 ; i < num ;i++)//for snake
            { sprite2.setPosition(s[i].x*size , s[i].y*size) ; window.draw(sprite2); }

        sprite3.setPosition(f.x*size , f.y*size);//for apple
        window.draw(sprite3);

        //for(int i = 0 ; i < 3 ;i++)//for snake
        //    { sprite4.setPosition(st[i].x , st[i].y) ; window.draw(sprite4); }

        window.display();
    }
    
    return 0;

}