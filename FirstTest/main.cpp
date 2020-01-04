#include <SFML/Graphics.hpp>
#include <sstream>      // std::ostringstream
#include <vector>
#include <cmath>
#include "Player.hpp"

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
    float sinValue;
    float cosValue;
    float timePassed;
    float deltaTime;
    Player player;
    player.SetSpeed(1);
    player.SetPosition(500, -200);

    std::vector<sf::Vertex> vertices;
    if (!font.loadFromFile("../OpenSans-Bold.ttf"))
    {
        return -1;
    }
    text.setFont(font);
    // window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);

    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::LostFocus)
                continue;
        }
        
        deltaTime = clock.getElapsedTime().asSeconds() - timePassed;
        timePassed = clock.getElapsedTime().asSeconds();
        sinValue = sin(timePassed);
        cosValue = cos(timePassed);

        // player.MovePlayer();

        player.ApplyGravity(deltaTime);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            player.ApplyForce(sf::Vector2f(0, 20), deltaTime);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            player.ApplyForce(sf::Vector2f(5, 0), deltaTime);
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            player.ApplyForce(sf::Vector2f(-5, 0), deltaTime);
        player.ApplyVelocity(deltaTime);

        textToDisplay.str("");
        textToDisplay.clear();
        textToDisplay << "Sin: " << sinValue << 
        "\nCos: " << cosValue << 
        "\nFPS: " << (1.0 / deltaTime) <<
        "\nx, y: " << player.GetPosition().x << ", " << player.GetPosition().y;
        text.setString(textToDisplay.str());

        vertices.clear();
        vertices.push_back(CreateVertex(sinValue * 100 + 200, cosValue * 100 + 200));
        vertices.push_back(CreateVertex(cosValue * 100 + 300, cosValue * 100 + 300));
        vertices.push_back(CreateVertex(cosValue * 100 + 600, sinValue * 100 + 150));
        vertices.push_back(CreateVertex(sinValue * 100 + 200, cosValue * 100 + 200));

        vertices[0].color = vertices[3].color = sf::Color::Blue;
        vertices[1].color = sf::Color::Green;
        vertices[2].color = sf::Color::Red;
        
        window.clear();
        window.draw(&vertices[0], vertices.size(), sf::PrimitiveType::LinesStrip);
        window.draw(text);
        window.draw(&player.GetVertex(), 1, sf::PrimitiveType::Points);
        window.display();
    }

    return 0;
}

sf::Vertex CreateVertex(double x, double y)
{
    return sf::Vertex(sf::Vector2f(x, y));
}