#include "Entity.h"

Entity::Entity()
{
    velocity.x = velocity.y = 0.0f;
    position.x = position.y = 0.0f;
    vertex.color = sf::Color::White;
}

void Entity::ApplyForce(sf::Vector2f force, float deltaTime)
{
    velocity += force * deltaTime;
}

void Entity::ApplyGravity(float deltaTime)
{
    velocity.y -= 10 * deltaTime;
}

void Entity::ApplyVelocity(float deltaTime)
{
    position += velocity * deltaTime;
}

void Entity::ApplyDrag(float drag, float deltaTime)
{
    velocity -= velocity * drag * deltaTime;
}

sf::Vector2f Entity::GetPosition(bool inverse)
{
    sf::Vector2f result = position;
    if(inverse) result.y *= -1;
    return result;
}

sf::Vertex &Entity::GetVertex()
{
    vertex.position = GetPosition();
    return vertex;
}

void Entity::SetPosition(float x, float y, bool inverse)
{
    position.x = x;
    position.y = !inverse ? -y : y;
}

void Entity::SetVelocity(float x, float y, bool inverse)
{
    velocity.x = x;
    velocity.y = !inverse ? -y : y;
}

EntityPool::EntityPool()
{
    drag = -1;
    array.clear();
}

EntityPool::~EntityPool()
{
    array.clear();
}

void EntityPool::AddNewEntity(float x, float y, bool inverse)
{
    Entity newEntity;
    newEntity.SetPosition(x, inverse ? -y : y);
    array.push_back(newEntity);
}

void EntityPool::ForceToPoint(sf::Vector2f point, float force, float deltaTime, bool fixedForce, bool inverse)
{
    int i;
    float magnitude;
    sf::Vector2f direction;

    for (i = 0; i < array.size(); i++)
    {
        direction = point - array[i].GetPosition();
        magnitude = sqrt(direction.x * direction.x + direction.y * direction.y);
        direction /= magnitude;
        direction.y = inverse ? -direction.y : direction.y;
        if(!fixedForce) direction *= (float)(1.0 / sqrt(magnitude) + 0.1);
        array[i].ApplyForce(direction * force, deltaTime);
    }
}

void EntityPool::ForceFromPoint(sf::Vector2f point, float force, float deltaTime, bool fixedForce, bool inverse)
{
    int i;
    float magnitude;
    sf::Vector2f direction;

    for (i = 0; i < array.size(); i++)
    {
        direction = array[i].GetPosition() - point;
        magnitude = sqrt(direction.x * direction.x + direction.y * direction.y);
        direction /= magnitude;
        direction.y = inverse ? -direction.y : direction.y;
        if(!fixedForce) direction *= (float)(1.0 / sqrt(magnitude) + 0.1);
        array[i].ApplyForce(direction * force, deltaTime);
    }
}

void EntityPool::RemoveEntities(int count)
{
    int i;
    for (i = 0; i < count; i++)
        array.pop_back();
}

void EntityPool::Update(float deltaTime)
{
    int i;
    for (i = 0; i < array.size(); i++)
    {
        if(isGravityOn)
            array[i].ApplyGravity(deltaTime);
        if(drag > 0.0)
            array[i].ApplyDrag(drag, deltaTime);
        array[i].ApplyVelocity(deltaTime);
    }
}

void EntityPool::SetGravity(bool isActive)
{
    isGravityOn = isActive;
}

void EntityPool::SetDrag(float drag)
{
    this -> drag = drag;
}

float EntityPool::GetDrag()
{
    return drag;
}

Entity &EntityPool::operator[](int index)
{
    return array[index];
}

int EntityPool::Size()
{
    return array.size();
}
