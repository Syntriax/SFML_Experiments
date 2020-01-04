#include "SynGame.hpp"

class Entity
{
    protected:
        sf::Vector2f position;
    public:
        Entity();
        void SetPosition(float, float, bool = true);
        void SetPosition(sf::Vector2f, bool = true);
        sf::Vector2f GetPosition(bool = true);
};

Entity::Entity()
{
    position = sf::Vector2f(0.0, 0.0);
}

void Entity::SetPosition(float x, float y, bool inverse)
{
    position.x = x;
    position.y = !inverse ? -y : y;
}

void Entity::SetPosition(sf::Vector2f position, bool inverse)
{
    this -> position = position;
    this -> position.y = !inverse ? -this -> position.y : this -> position.y;
}

sf::Vector2f Entity::GetPosition(bool inverse)
{
    sf::Vector2f result = position;
    if(inverse) result.y *= -1;
    return result;
}