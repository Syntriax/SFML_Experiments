#include "SynGame.hpp"

class Sphere
{
    public:
        Vector3 position;
        float radius;
        sf::Color color;
        Sphere(Vector3 = (0,0,0), float = 1.0, sf::Color = sf::Color::White);
};

Sphere::Sphere(Vector3 position, float radius, sf::Color color)
{
    this -> position = position;
    this -> radius = radius;
    this -> color = color;
}



