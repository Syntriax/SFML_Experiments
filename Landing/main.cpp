#include <SFML/Graphics.hpp>
#include <sstream>
#include <cmath>
#include "SynGame.hpp"

#define WindowSize  sf::VideoMode(960, 540)
#define WindowStyle sf::Style::Titlebar | sf::Style::Close
#define WindowTitle "Test Window Syntriax"

#define SizeMultiplier 5
#define WinThreshold 2.0

sf::Vertex CreateVertex(double, double);

float Terrain(float x, float divider)
{
    return sin(x / divider);
}

int main()
{
    std::ostringstream textToDisplay;
    sf::RenderWindow window(WindowSize, WindowTitle, WindowStyle);
    sf::Event event;
    sf::Clock clock;
    sf::Text text;
    sf::Font font;
    sf::Texture playerTexture;
    Rocket player;
    sf::Vertex terrain[320];
    float timePassed;
    float deltaTime;
    bool isFocused = true;

    for (int i = 0; i < 320; i++)
    {
        terrain[i].position.x = i * 3;
        terrain[i].position.y = Terrain(i * 3, SizeMultiplier * 25) * SizeMultiplier * 25 + 400;
    }

    if (!playerTexture.loadFromFile("Rocket.png"))
        return -1;
    if (!font.loadFromFile("../OpenSans-Bold.ttf"))
        return -1;

    player.SetTexture(playerTexture, SizeMultiplier);
    player.SetRotationForce(45);
    player.SetThrustForce(25 * SizeMultiplier);
    player.SetGravity(10 * SizeMultiplier);
    player.SetPosition(480, -50);
    player.SetActive(true);
    player.particleSystem.SetParticleLifeTime(2);
    player.particleSystem.SetSpawnRate(25);
    player.particleSystem.SetSize(50);
    player.particleSystem.SetSpeed(10 * SizeMultiplier);

    text.setFont(font);
    window.setVerticalSyncEnabled(true);

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
        }
        if(!isFocused)
        {
            timePassed = clock.getElapsedTime().asSeconds();
            continue;
        }
        
        deltaTime = clock.getElapsedTime().asSeconds() - timePassed;
        timePassed = clock.getElapsedTime().asSeconds();
        
        textToDisplay.str("");
        textToDisplay.clear();

        //Collision
        if(terrain[(int)player.GetLandingPoint().x / 3].position.y - player.GetLandingPoint().y < 0.0)
        {
            player.SetActive(false);
            textToDisplay << (player.GetSpeed() / SizeMultiplier < WinThreshold ? "Win" : "Loose");
            textToDisplay << "\nCollided";
            textToDisplay << "\nSpeed: " << player.GetSpeed() / SizeMultiplier;
            textToDisplay << "\nWin Speed: " << WinThreshold;
        }

        text.setString(textToDisplay.str());

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            player.Thrust(deltaTime);

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            player.Rotate(deltaTime, true);
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            player.Rotate(deltaTime, false);

        player.Update(deltaTime);

        window.clear();
        window.draw(text);
        window.draw(&terrain[0], 320, sf::PrimitiveType::LinesStrip);
        for (int i = 0; i < player.particleSystem.Size(); i++)
            window.draw(&player.particleSystem[i].GetVertex(), 1, sf::PrimitiveType::Points);
        window.draw(player.GetSprite());
        window.display();
    }

    return 0;
}

sf::Vertex CreateVertex(double x, double y)
{
    return sf::Vertex(sf::Vector2f(x, y));
}