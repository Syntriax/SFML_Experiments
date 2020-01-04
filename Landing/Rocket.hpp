// #include <SFML/Graphics.hpp>
// #include <cmath>
#include "SynGame.hpp"
// #include "Particles.hpp"
// #include "PhysicEntity.hpp"

#define DegToRad 0.0174533 
#define RotationLimit 45.0 

class Rocket : public PhysicEntity
{
    private:
        float thrustForce;
        float rotationForce;
        float rotation;
        sf::Texture texture;
        sf::Sprite sprite;
    public:
        ParticleSystem particleSystem;
        Rocket();
        void Rotate(float, bool = true);
        void Thrust(float);
        void Update(float);
        void SetThrustForce(float);
        void SetRotationForce(float);
        void SetTexture(sf::Texture, float = 1.0);
        sf::Sprite GetSprite();
        sf::Vector2f GetLandingPoint(bool = true);
        void SetPosition(float, float, bool = true);
};

Rocket::Rocket() : PhysicEntity()
{
    thrustForce = rotationForce = rotation = 0.0f;
    SetGravity();
}

void Rocket::Rotate(float deltaTime, bool isRight)
{
    if(!isActive) return;

    rotation += (isRight ? rotationForce : -rotationForce) * deltaTime;
    
    if(rotation > RotationLimit)
        rotation = RotationLimit;
    else if(rotation < -RotationLimit)
        rotation = -RotationLimit;
    
    sprite.setRotation(rotation);
}

void Rocket::Thrust(float deltaTime)
{
    if(!isActive) return;
    
    float force = thrustForce * deltaTime;
    velocity.x += sin(rotation * DegToRad) * force;
    velocity.y += cos(rotation * DegToRad) * force;
    
    particleSystem.SetPosition(position);
    particleSystem.Update(deltaTime);
}

void Rocket::Update(float deltaTime)
{
    PhysicEntity::Update(deltaTime);
    particleSystem.Update(deltaTime);
    sprite.setPosition(GetPosition());
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

void Rocket::SetPosition(float x, float y, bool inverse)
{
    Entity::SetPosition(x, y, inverse);
    sprite.setPosition(position);
}

sf::Sprite Rocket::GetSprite()
{
    return sprite;
}

sf::Vector2f Rocket::GetLandingPoint(bool inverse)
{
    sf::Vector2f result = position;
    result.x -= sin(rotation * DegToRad) * texture.getSize().y * sprite.getScale().y / 2;
    result.y -= cos(rotation * DegToRad) * texture.getSize().y * sprite.getScale().y / 2;
    if(inverse) result.y *= -1;
    return result;
}
