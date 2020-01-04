#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

#define DegToRad 0.0174533 

class Rocket
{
    private:
        float thrustForce;
        float rotationForce;
        float rotation;
        float gravity;
        sf::Texture texture;
        sf::Sprite sprite;
        sf::Vector2f position;
        sf::Vector2f velocity;
        bool isActive;
        void ApplyGravity(float);
        void ApplyVelocity(float);
    public:
        Rocket();
        void Update(float);
        void Rotate(float, bool = true);
        void Thrust(float);
        void SetThrustForce(float);
        void SetRotationForce(float);
        void SetGravity(float);
        void SetPosition(float, float, bool = true);
        void SetTexture(sf::Texture, float = 1.0);
        void SetActive(bool = true);
        float GetSpeed();
        sf::Sprite GetSprite();
        sf::Vector2f GetPosition(bool = true);
        sf::Vector2f GetLandingPoint(bool = true);
};

Rocket::Rocket()
{
    velocity.x  = velocity.y    = 0.0f;
    position.x  = position.y    = 0.0f;
    thrustForce = rotationForce = rotation = 0.0f;
    gravity = 10;
    isActive = false;
}

void Rocket::Update(float deltaTime)
{
    if(!isActive) return;

    ApplyGravity(deltaTime);
    ApplyVelocity(deltaTime);
}

void Rocket::Rotate(float deltaTime, bool isRight)
{
    if(!isActive) return;

    rotation += (isRight ? rotationForce : -rotationForce) * deltaTime;
    sprite.setRotation(rotation);
}

void Rocket::Thrust(float deltaTime)
{
    if(!isActive) return;
    
    float force = thrustForce * deltaTime;
    velocity.x += sin(rotation * DegToRad) * force;
    velocity.y += cos(rotation * DegToRad) * force;
}

void Rocket::ApplyGravity(float deltaTime)
{
    velocity.y -= gravity * deltaTime;
}

void Rocket::ApplyVelocity(float deltaTime)
{
    position += velocity * deltaTime;
    sprite.setPosition(GetPosition());
}

void Rocket::SetPosition(float x, float y, bool inverse)
{
    position.x = x;
    position.y = !inverse ? -y : y;
    sprite.setPosition(position);
}

void Rocket::SetGravity(float gravity)
{
    this -> gravity = gravity;
}

void Rocket::SetThrustForce(float thrustForce)
{
    this -> thrustForce = thrustForce;
}

void Rocket::SetRotationForce(float rotationForce)
{
    this -> rotationForce = rotationForce;
}

void Rocket::SetTexture(sf::Texture texture, float size)
{
    this -> texture = texture;
    sprite = sf::Sprite(this -> texture);
    sprite.setScale(size, size);
    sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
}

void Rocket::SetActive(bool active)
{
    isActive = active;
}

float Rocket::GetSpeed()
{
    return sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
}

sf::Sprite Rocket::GetSprite()
{
    return sprite;
}

sf::Vector2f Rocket::GetPosition(bool inverse)
{
    sf::Vector2f result = position;
    if(inverse) result.y *= -1;
    return result;
}

sf::Vector2f Rocket::GetLandingPoint(bool inverse)
{
    sf::Vector2f result = position;
    result.x -= sin(rotation * DegToRad) * texture.getSize().y * sprite.getScale().y / 2;
    result.y -= cos(rotation * DegToRad) * texture.getSize().y * sprite.getScale().y / 2;
    if(inverse) result.y *= -1;
    return result;
}
