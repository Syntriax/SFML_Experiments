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
        if(!isActive)
            return;

        if(IsLifeTimeOver())
            return;
            
        PhysicEntity::Update(deltaTime);
        
        ChangeColorOverLifeTime();
        remainingLifeTime -= deltaTime;
    }

    void Particle::ChangeColorOverLifeTime()
    {
        if(lifeTime < 0.0)
        {
            vertex.color.a = 0;
            return;
        }
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
            sf::Vector2f localVelo;
            float rotation;
            float speed;
            int particleSize;
            float particleLifeTime;
            float spawnRate;
            float spawnTimer;
        public:
            ParticleSystem();
            void SetSize(int);
            void SetSpeed(float);
            void SetRotation(float);
            void SetLocalVelocity(sf::Vector2f);
            void SetParticleLifeTime(float);
            void SetSpawnRate(int);
            void Update(float);
            void Play();
            Particle &operator[](int);
            int Size();
    };

    ParticleSystem::ParticleSystem()
    {
        particles.clear();
        color = sf::Color::White;
        particleSize = 0;
        particleLifeTime = 0.1;
        spawnRate = 10;
        spawnTimer = 0.0;
    }

    void ParticleSystem::Update(float deltaTime)
    {
        int i;
        Particle *particle;

        if(spawnTimer > 0.0)
            spawnTimer -= deltaTime;

        for (i = 0; i < particleSize; i++)
        {
            particle = &particles[i];
            particle -> Update(deltaTime);
        }
    }

    void ParticleSystem::Play()
    {
        int i;
        float spawnRotation;
        sf::Vector2f spawnVelocity;
        Particle *particle;

        if(spawnTimer > 0.0)
            return;

        for (i = 0; i < particleSize; i++)
        {
            particle = &particles[i];
            if(particle -> IsLifeTimeOver())
            {
                particle -> ResetRemainingLifeTime();
                particle -> SetPosition(position.x, position.y, false);
                spawnRotation = Random(-0.785, 0.785) - DegToRad * rotation; // 0.785 3.14(pi)/4
                spawnVelocity = sf::Vector2f(sin(spawnRotation), cos(spawnRotation)) * speed;
                particle -> SetVelocity(spawnVelocity + localVelo);
                spawnTimer = 1 / spawnRate;
                break;
            }
        }
    }

    void ParticleSystem::SetSpawnRate(int rate)
    {
        spawnRate = rate;
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

    void ParticleSystem::SetSpeed(float speed)
    {
        this -> speed = speed;
    }

    void ParticleSystem::SetRotation(float rotation)
    {
        this -> rotation = rotation;
    }

    void ParticleSystem::SetLocalVelocity(sf::Vector2f velo)
    {
        velo.y *= -1;
        localVelo = velo;
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
