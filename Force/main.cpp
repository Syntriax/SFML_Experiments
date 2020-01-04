#include <SFML/Graphics.hpp>
#include <sstream>
#include <math.h>
#include "Entity.h"

#define WindowSize  sf::VideoMode(960, 540)
#define WindowStyle sf::Style::Titlebar | sf::Style::Close
#define WindowTitle "Test Window Syntriax"

sf::Vertex CreateVertex(double, double);

int main()
{
    std::ostringstream textToDisplay;
    sf::RenderWindow window(WindowSize, WindowTitle, WindowStyle);
    sf::Event event;
    sf::Clock clock;
    sf::Text text;
    sf::Font font;
    sf::Vector2f vector;
    float radiantValue;
    float timePassed;
    float deltaTime;
    float force = 1000;
    EntityPool pool;
    bool isFocused = true;
    bool isFixedForce = true;
    pool.SetGravity(false);
    pool.SetDrag(0.0);

    if (!font.loadFromFile("../OpenSans-Bold.ttf"))
        return -1;

    text.setFont(font);
    window.setVerticalSyncEnabled(true);
    // window.setFramerateLimit(140);

    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::LostFocus)
                isFocused = false;
            else if (event.type == sf::Event::GainedFocus)
                isFocused = true;
            else if (event.type == sf::Event::KeyPressed)
            {
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::R))
                    pool.RemoveEntities(pool.Size());
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                    pool.SetDrag(2);
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                    pool.SetDrag(1);
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                    pool.SetDrag(0.5);
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::F))
                    pool.SetDrag(0.25);
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::G))
                    pool.SetDrag(0.1);
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::H))
                    pool.SetDrag(0.0);
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
                    force = 100;
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::X))
                    force = 500;
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::C))
                    force = 1000;
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::V))
                    force = 2500;
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::B))
                    force = 10000;
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::L))
                    isFixedForce = !isFixedForce;
            }
        }
        if(!isFocused)
        {
            timePassed = clock.getElapsedTime().asSeconds();
            continue;
        }
        
        deltaTime = clock.getElapsedTime().asSeconds() - timePassed;
        timePassed = clock.getElapsedTime().asSeconds();
        
        pool.Update(deltaTime);

        textToDisplay.str("");
        textToDisplay.clear();
        textToDisplay << "Entity Count: " << pool.Size() << 
                         "\nDrag: " << pool.GetDrag() <<
                         "\nForce: " << force <<
                         "\nForce Mode: " << (isFixedForce ? "Fixed" : "Distance") <<
                         "\nFPS: " << (1.0 / deltaTime);
        text.setString(textToDisplay.str());

        
        if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
        {
            vector = (sf::Vector2f) sf::Mouse::getPosition(window);
            for (int i = 0; i < 18; i++)
            {
                radiantValue = ((float)i / 18.0 * 7.28) + timePassed;
                pool.AddNewEntity(vector.x + sin(radiantValue) * 100.0, vector.y + cos(radiantValue) * 100.0);
            }
        }
        if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
            pool.ForceToPoint((sf::Vector2f) sf::Mouse::getPosition(window), force, deltaTime, isFixedForce);
        if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Middle))
            pool.ForceFromPoint((sf::Vector2f) sf::Mouse::getPosition(window), force, deltaTime, isFixedForce);
        
        window.clear();
        for (int i = 0; i < pool.Size(); i++)
            window.draw(&pool[i].GetVertex(), 1, sf::PrimitiveType::Points);
        window.draw(text);
        // window.draw(&player.GetVertex(), 1, sf::PrimitiveType::Points);
        window.display();
    }

    return 0;
}

sf::Vertex CreateVertex(double x, double y)
{
    return sf::Vertex(sf::Vector2f(x, y));
}