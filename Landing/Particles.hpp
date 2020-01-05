#include "SynGame.hpp"

#pragma region Particle
    class Particle : public PhysicEntity
    {
        private:
            sf::Vertex vertex;
            float lifeTime;
            float remainingLifeTime;
            void ChangeColorOverLifeTime();
        public:
            Particle();
            Particle(sf::Color);
            void Update(float);
            void ResetRemainingLifeTime();
            void SetLifeTime(float);
            bool IsLifeTimeOver();
            sf::Vertex &GetVertex();
    };

    Particle::Particle() : PhysicEntity()
    {
        vertex.color = sf::Color::White;
        lifeTime = remainingLifeTime = 0.0;
    }

    Particle::Particle(sf::Color color) : PhysicEntity()
    {
        vertex.color = color;
        lifeTime = remainingLifeTime = 0.0;
    }

    void Particle::Update(float deltaTime)
    {
        PhysicEntity::Update(deltaTime);
        
        if(!isActive)
            return;

        remainingLifeTime -= deltaTime;
        ChangeColorOverLifeTime();
    }

    void Particle::ChangeColorOverLifeTime()
    {
        int value = 255 * (remainingLifeTime / lifeTime);
        vertex.color.a = value;
    }

    void Particle::ResetRemainingLifeTime()
    {
        remainingLifeTime = lifeTime;
    }

    void Particle::SetLifeTime(float time)
    {
        remainingLifeTime = lifeTime = time;
    }

    bool Particle::IsLifeTimeOver()
    {
        return remainingLifeTime <= 0.0;
    }

    sf::Vertex &Particle::GetVertex()
    {
        vertex.position = position;
        return vertex;
    }
#pragma endregion
#pragma region Particle System
    class ParticleSystem : public Entity
    {
        private:
            std::vector<Particle> particles;
            sf::Color color;
            int particleSize;
            float particleLifeTime;
        public:
            ParticleSystem();
            void SetSize(int);
            void SetParticleLifeTime(float);
            void Update(float);
            Particle &operator[](int);
            int Size();
    };

    ParticleSystem::ParticleSystem()
    {
        particles.clear();
        color = sf::Color::White;
        particleSize = 0;
        particleLifeTime = 0.1;
    }

    void ParticleSystem::Update(float deltaTime)
    {
        int i;
        Particle *particle;

        for (i = 0; i < particleSize; i++)
        {
            particle = &particles[i];
            particle -> Update(deltaTime);
            if(particle -> IsLifeTimeOver())
            {
                particle -> ResetRemainingLifeTime();
                particle -> SetPosition(position.x, position.y, false);
                particle -> SetVelocity(sf::Vector2f(Random(-10.0, 10.0), Random(-10.0, 10.0)));
            }
        }
    }

    void ParticleSystem::SetSize(int size)
    {
        while(particleSize != size)
            if(particleSize > size)
            {
                delete &particles[--particleSize];
                particles.pop_back();
            }
            else
            {
                Particle newParticle = Particle(color);
                newParticle.SetLifeTime(particleLifeTime);
                particles.push_back(newParticle);
                particleSize++;
            }
    }

    void ParticleSystem::SetParticleLifeTime(float lifeTime)
    {
        if(lifeTime < 0.1)
            return;

        int i;
        particleLifeTime = lifeTime;
        for (i = 0; i < particleSize; i++)
            particles[i].SetLifeTime(lifeTime);
    }

    Particle &ParticleSystem::operator[](int index)
    {
        return particles[index];
    }

    int ParticleSystem::Size()
    {
        return particles.size();
    }
#pragma endregion
