#include "SynGame.hpp"

#pragma region Timer
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
#pragma endregion

#pragma region Window
    class Window
    {
        protected:
            sf::RenderWindow window;
            sf::Event event;
            sf::Vector2u size;
            sf::Vector2u windowedSize;
            std::string title;
            sf::Uint32 style;
            Timer timer; 
            bool isFocused;
            bool fullscreen;
            virtual void Update();
        public:
            Window(unsigned int = 960, unsigned int = 540, std::string = "Window", sf::Uint32 = sf::Style::Titlebar | sf::Style::Close);
            virtual void CreateWindow();
            virtual void CloseWindow();
            void SetFrameRate(int = 0);
            void SetTitle(std::string);
            virtual void SetSize(unsigned int, unsigned int);
            bool IsOpen();
    };

    void Window::Update()
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                CloseWindow();
            else if (event.type == sf::Event::LostFocus)
                isFocused = false;
            else if (event.type == sf::Event::GainedFocus)
                isFocused = true;
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::F))
            {
                fullscreen = !fullscreen;
                CloseWindow();
                CreateWindow();
            }
        }

        if(!isFocused)
            return;
        
        timer.UpdateTime();
    }

    Window::Window(unsigned int width, unsigned int height, std::string title, sf::Uint32 style)
    {
        this -> size.x = width;
        this -> size.y = height;
        this -> title  = title;
        this -> style  = style;

        windowedSize.x = width;
        windowedSize.y = height;
        
        isFocused = true;
        fullscreen = false;
        SetFrameRate();
        CreateWindow();
    }

    void Window::CreateWindow()
    {
        if(window.isOpen())
            return;

        if(!fullscreen)
        {
            size = windowedSize;
            sf::VideoMode videoMode(windowedSize.x, windowedSize.y);
            window.create(videoMode, title, style);
        }
        else
        {
            sf::VideoMode videoMode(sf::VideoMode::getDesktopMode());
            size.x = videoMode.width;
            size.y = videoMode.height;
            window.create(videoMode, title, sf::Style::Fullscreen);
        }

        timer.ResetTimer();
    }

    void Window::CloseWindow()
    {
        if(!window.isOpen())
            return;

        window.close();
    }

    void Window::SetFrameRate(int rate)
    {
        if(rate == 0)
        {
            window.setVerticalSyncEnabled(true);
            return;
        }
        
        if(rate < 0)
            window.setFramerateLimit(10000);
        else
            window.setFramerateLimit(rate);

        window.setVerticalSyncEnabled(false);
    }

    void Window::SetTitle(std::string title)
    {
        this -> title = title;
        window.setTitle(title);
    }

    void Window::SetSize(unsigned int width, unsigned int height)
    {
        size = sf::Vector2u(width, height);
        sf::Vector2i pos = window.getPosition();
        CloseWindow();
        window.setSize(size);
        CreateWindow();
        window.setPosition(pos);
    }

    bool Window::IsOpen()
    {
        return window.isOpen();
    }
#pragma endregion
