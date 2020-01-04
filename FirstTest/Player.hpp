#include <SFML/Graphics.hpp>

class Player
{
    private:
        sf::Vertex vertex;
        sf::Vector2f position;
        float movementSpeed;
        sf::Vector2f velocity;
    public:
        Player();
        void MovePlayer();
        void ApplyForce(sf::Vector2f, float);
        void ApplyGravity(float);
        void ApplyVelocity(float);
        void SetSpeed(float);
        void SetPosition(float, float);
        sf::Vertex &GetVertex();
        sf::Vector2f GetPosition();
};

Player::Player()
{
    velocity.x = velocity.y = 0.0f;
    movementSpeed = 0.0f;
    position.x = position.y = 0.0f;
    vertex.color = sf::Color::White;
}

void Player::ApplyForce(sf::Vector2f force, float deltaTime)
{
    velocity += force * deltaTime;
}

void Player::MovePlayer()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        velocity.x = movementSpeed;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        velocity.x = -movementSpeed;
    else
        velocity.x = 0;
    

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        velocity.y = movementSpeed;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        velocity.y = -movementSpeed;
    else
        velocity.y = 0;
}

void Player::ApplyGravity(float deltaTime)
{
    velocity.y -= 10 * deltaTime;
}

void Player::ApplyVelocity(float deltaTime)
{
    position += velocity * deltaTime;
}

sf::Vector2f Player::GetPosition()
{
    sf::Vector2f result = position;
    result.y *= -1;
    return result;
}

sf::Vertex &Player::GetVertex()
{
    vertex.position = GetPosition();
    return vertex;
}

void Player::SetSpeed(float speed)
{
    movementSpeed = speed;
}

void Player::SetPosition(float x, float y)
{
    position.x = x;
    position.y = y;
}