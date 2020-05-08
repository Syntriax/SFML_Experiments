#include "SynGame.hpp"

class InverseKinematics
{
    private:
        Vector2 root;
        Vector2 *target;
        Vector2 *points;
        float *lengths;
        float totalLenght;
        unsigned int pointCount;
        unsigned int iterationCount;
        float distanceThreeshold; 
    public:
        InverseKinematics();
        void SetPoints(Vector2 *, unsigned int);
        void SetRoot(Vector2);
        void SetTarget(Vector2 *);
        void SetIterationCount(unsigned int);
        void Iterate();
        ~InverseKinematics();
};

InverseKinematics::InverseKinematics()
{
    points = NULL;
    lengths = NULL;
    pointCount = 0;
    iterationCount = 0;
    distanceThreeshold = 1;
}

void InverseKinematics::SetPoints(Vector2 *points, unsigned int count)
{
    int i;

    this -> points = points;
    this -> pointCount = count;
    this -> lengths = new float[count - 1];
    this -> totalLenght = 0.0;
    for (i = 0; i < count - 1; i++)
    {
        *(this -> lengths + i) = (*(points + i) - *(points + i + 1)).Magnitude();
        this -> totalLenght += *(this -> lengths + i);
    }
}

void InverseKinematics::SetIterationCount(unsigned int count)
{
    if(count == 0)  return;
    if(count > 100) return;

    this -> iterationCount = count;
}

void InverseKinematics::SetTarget(Vector2 *target)
{
    this -> target = target;
}

void InverseKinematics::SetRoot(Vector2 root)
{
    this -> root = root;
}

void InverseKinematics::Iterate()
{
    int i;
    Vector2 *point;
    Vector2 *nextPoint;
    float *length;
    int iterationCount = this -> iterationCount;
    int pointCount = this -> pointCount;
    
    // if the target is out of reach
    if(target->Distance(root) > this -> totalLenght)
    {
        Vector2 direction = (*target - root).Normalized();
        *(this -> points) = root;
        point = this -> points + 1;
        length = this -> lengths;

        for (i = 1; i < pointCount; i++)
        {
            *point = *(point - 1) + direction * *length;
            point++;
            length++;
        }
        
        return;
    }

    // if the target is in reachable distance
    for (i = 0; i < iterationCount; i++)
    {
        point = this -> points + pointCount - 1;
        if(point -> Distance(*target) < distanceThreeshold)
            return;
        length = this -> lengths + pointCount - 2;

        *point = *target;

        while (point != this -> points)
        {
            nextPoint = point - 1;
            *nextPoint = (*point) + (*nextPoint - *point).Normalized() * (*length);
            length--;
            point--;
        }

        *point = root;
        length = this -> lengths;

        while (point != this -> points + pointCount - 1)
        {
            nextPoint = point + 1;
            *nextPoint = (*point) + (*nextPoint - *point).Normalized() * (*length);
            length++;
            point++;
        }
    }
}

InverseKinematics::~InverseKinematics()
{
    if(lengths) delete lengths;
}
