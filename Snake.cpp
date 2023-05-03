#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>

#pragma warning(disable : 4244);
#pragma warning(disable : 4305);
#pragma warning(disable : 4081);
#pragma warning(disable : 26812);

using namespace sf;

const unsigned int max_size = 2000;

struct snake {
    int x, y;
}s[max_size];

struct fruit {
    int x, y;
}f;

enum Direction {
    left,
    right,
    down,
    up
};

int main()
{
    Clock clock;
    Direction direction = right;

    int W(50), H(30);
    int size(20);
    int length(10);

    int width = size * W;
    int height = size * H;

    f.x = 10, f.y = 10;

    int r(255), g(0), b(0);

    RectangleShape apple(Vector2f(size, size));
    apple.setFillColor(Color::Red);

    RectangleShape* rect = new RectangleShape[max_size];

    for (int k(0); k < length; k++)
    {
        int h = rand() % 255;
        rect[k].setFillColor(Color(r, g, b));
        rect[k].setPosition(s[k].x, s[k].y);    
    }

    RenderWindow window(VideoMode(width, height), "Snake");

    float timer(0), delay(0.03);
    while (window.isOpen())
    {
        srand(time(0));
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;
       
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        if (Keyboard::isKeyPressed(Keyboard::Up) && direction != down)direction = up;
        if (Keyboard::isKeyPressed(Keyboard::Down) && direction != up)direction = down;
        if (Keyboard::isKeyPressed(Keyboard::Left) && direction != right)direction = left;
        if (Keyboard::isKeyPressed(Keyboard::Right) && direction != left)direction = right;
        if (Keyboard::isKeyPressed(Keyboard::D))delay = 0.01;
        if (!(Keyboard::isKeyPressed(Keyboard::D)))delay = 0.03;


        if (timer > delay)
        {
            timer = 0;

            for (int k(length); k > 0; --k)
            {
                s[k].x = s[k - 1].x;
                s[k].y = s[k - 1].y;
            }

            if (direction == right)s[0].x += 1;
            if (direction == left)s[0].x -= 1;
            if (direction == up)s[0].y -= 1;
            if (direction == down)s[0].y += 1;

            if (s[0].x > W)s[0].x = 0;
            if (s[0].x < 0)s[0].x = W;

            if (s[0].y > H)s[0].y = 0;
            if (s[0].y < 0)s[0].y = H;

            if (s[0].x == f.x && s[0].y == f.y)
            {
                length++;
                
                r = rand() % 255;
                g = rand() % 255;
                b = rand() % 255;

              
                f.x = rand() % W;
                f.y = rand() % H;
            }

            for (int k(1); k < length; k++)
            {
                if (s[k].x == s[0].x && s[k].y == s[0].y) {
                    length = 4;
                }
            }

        }

        window.clear();

        for (int k(0); k < length; k++)
        {
            
            rect[k].setSize(Vector2f(size, size));
            rect[k].setFillColor(Color(r, g, b));
            rect[k].setPosition(s[k].x*size, s[k].y*size);
            window.draw(rect[k]);
        }

        apple.setPosition(f.x*size, f.y*size);
        window.draw(apple);

        window.display();
    }


    delete[] rect;
    return 0;
}