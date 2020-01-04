#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

class Entity;

class EntityPool
{
    private:
        std::vector<Entity> array;
        bool isGravityOn;
        float drag;
    public:
        EntityPool();
        ~EntityPool();
        void AddNewEntity(float, float, bool = true);
        void ForceToPoint(sf::Vector2f, float, float, bool = true, bool = true);
        void ForceFromPoint(sf::Vector2f, float, float, bool = true, bool = true);
        void RemoveEntities(int);
        void Update(float);
        void SetGravity(bool);
        void SetDrag(float);
        float GetDrag();
        Entity &operator[](int);
        int Size();
};

class Entity
{
    private:
        sf::Vertex vertex;
        sf::Vector2f position;
        sf::Vector2f velocity;
    public:
        Entity();
        void ApplyForce(sf::Vector2f, float);
        void ApplyDrag(float, float);
        void ApplyGravity(float);
        void ApplyVelocity(float);
        void SetPosition(float, float, bool = true);
        void SetVelocity(float, float, bool = true);
        sf::Vertex &GetVertex();
        sf::Vector2f GetPosition(bool = true);
};
