#include "SynGame.hpp"

class PhysicEntity : public Entity
{
    private:
        void ApplyGravity(float);
        void ApplyVelocity(float);
    protected:
        sf::Vector2f velocity;
        float gravity;
        bool isActive;
    public:
        PhysicEntity();
        void Update(float);
        void SetVelocity(sf::Vector2f);
        void SetGravity(float = 10);
        void SetActive(bool = true);
        float GetSpeed();
};

PhysicEntity::PhysicEntity() : Entity()
{
    velocity = sf::Vector2f(0.0, 0.0);
    gravity = 0.0;
    isActive = true;
}

void PhysicEntity::Update(float deltaTime)
{
    if(!isActive) return;

    ApplyGravity(deltaTime);
    ApplyVelocity(deltaTime);
}

void PhysicEntity::ApplyGravity(float deltaTime)
{
    velocity.y -= gravity * deltaTime;
}

void PhysicEntity::ApplyVelocity(float deltaTime)
{
    position += velocity * deltaTime;
}

void PhysicEntity::SetVelocity(sf::Vector2f velocity)
{
    this -> velocity = velocity;
}

void PhysicEntity::SetGravity(float gravity)
{
    this -> gravity = gravity;
}

void PhysicEntity::SetActive(bool active)
{
    isActive = active;
}

float PhysicEntity::GetSpeed()
{
    return sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
}