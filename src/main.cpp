#include "SFML/Graphics.hpp"
#include "game/Object/CollisionBox.hpp"
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor({255, 0, 0});

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        

        window.clear();
        window.draw(shape);
        window.display();
    }


    CollisionBox A, B;
    A.x = 32;
    A.y = 32;
    std::cout << A.CheckIfCollidesWith(B);
    return 0;
}