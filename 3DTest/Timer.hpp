#include "SynGame.hpp"

class Timer
{
    private:
        sf::Clock clock;
        float deltaTime;
        float timePassed;
    public:
        Timer();
        void ResetTimer();
        void UpdateTime();
        float GetDeltaTime();
        float GetTimePassed();
};

Timer::Timer()
{
    clock.restart();
    timePassed = 0.0;
    deltaTime = 0.0;
}

void Timer::ResetTimer()
{
    clock.restart();
    timePassed = 0.0;
    deltaTime = 0.0;
}

void Timer::UpdateTime()
{
    float newTimePassed = clock.getElapsedTime().asSeconds();

    deltaTime = newTimePassed - timePassed;
    timePassed = newTimePassed;
}

float Timer::GetDeltaTime()
{
    return deltaTime;
}

float Timer::GetTimePassed()
{
    return timePassed;
}
