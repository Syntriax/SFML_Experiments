#include "SynGame.hpp"

class RayMarch
{
    private:
        Sphere *spheres;
        Sphere *closest;
        Vector3 direction;
        Vector3 position;
        int sphereSize;
        int stepLimit;
        int stepCounter;
        float minDistance;
        float maxDistance;
        float GetClosestDistance();
        Sphere *GetClosestSphere();
    public:
        RayMarch();
        RayMarch(Vector3, Vector3, Sphere *, int = 0);
        void SetRay(Vector3, Vector3, Sphere *, int = 0, int = 100, float = 0.01);
        void SetPosition(Vector3, Vector3);
        int GetStepCount();
        sf::Color FireRay();
};

RayMarch::RayMarch()
{
    this -> position = (0.0, 0.0);
    this -> direction = (0.0, 0.0);
    this -> spheres = NULL;
    stepCounter = 0;
    sphereSize = 0;
    minDistance = 0.01;
    stepLimit = 100;
    maxDistance = 100.0;
}

RayMarch::RayMarch(Vector3 position, Vector3 direction, Sphere *spheres, int size)
{
    this -> position = position;
    this -> direction = direction;
    this -> spheres = spheres;
    sphereSize = size;
    stepCounter = 0;
    minDistance = 0.01;
    stepLimit = 100;
    maxDistance = 100.0;
}

void RayMarch::SetRay(Vector3 position, Vector3 direction, Sphere *spheres, int size, int stepLimit, float minDistance)
{
    this -> position = position;
    this -> direction = direction;
    this -> spheres = spheres;
    this -> sphereSize = size;
    this -> stepLimit = stepLimit;
    this -> minDistance = minDistance;
    stepCounter = 0;
}

void RayMarch::SetPosition(Vector3 position, Vector3 direction)
{
    this -> position = position;
    this -> direction = direction;
    stepCounter = 0;

}

Sphere *RayMarch::GetClosestSphere()
{
    int i;
    Sphere *ptr = spheres;
    Sphere *closestSphere = NULL;
    float closestDistance;
    float distance;

    if(!ptr) return NULL;

    closestDistance = position.Distance((*ptr).position) - (*ptr).radius;
    for (i = 0; i < sphereSize; i++)
    {
        distance = position.Distance((*ptr).position) - (*ptr).radius;
        if(distance < closestDistance)
        {
            closestDistance = distance;
            closestSphere = ptr;
        }
        ptr++;
    }
    
    return closestSphere;
}

float RayMarch::GetClosestDistance()
{
    int i;
    Sphere *ptr = spheres;
    float closestDistance;
    float distance;

    if(!ptr) return 0.0;
    closestDistance = position.Distance((*ptr).position) - (*ptr).radius;
    for (i = 0; i < sphereSize; i++)
    {
        distance = position.Distance((*ptr).position) - (*ptr).radius;
        if(distance < closestDistance)
        {
            closestDistance = distance;
            closest = ptr;
        }
        ptr++;
    }
    
    return closestDistance;
}

int RayMarch::GetStepCount() { return stepCounter; }

sf::Color RayMarch::FireRay()
{
    float distance;
    stepCounter = 0;

    if(!spheres) return sf::Color::Black;

    for (stepCounter = 0; stepCounter < stepLimit; stepCounter++)
    {
        distance = GetClosestDistance();
        
        if(distance <= minDistance)
            return closest -> color;

        if(distance >= maxDistance)
        {
            sf::Uint8 val = 256 * stepCounter / stepLimit;
            return sf::Color(val, val, val);
        }

        position += direction * distance;
    }

    return sf::Color::Black;
}
