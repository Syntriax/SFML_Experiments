#include "SynGame.hpp"

class Window
{
    private:
        sf::RenderWindow window;
        sf::Event event;
        sf::Vector2u size;
        std::string title;
        sf::Uint32 style;
        Timer timer; 
        bool isFocused;
    public:
        Window(unsigned int = 960, unsigned int = 540, std::string = "Window", sf::Uint32 = 7U);
        void CreateWindow();
        void CloseWindow();
        void Update();
        void SetFrameRate(int = 0);
        void SetTitle(std::string);
        void SetSize(unsigned int, unsigned int);
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
    isFocused = true;
    SetFrameRate();
    CreateWindow();
}

void Window::CreateWindow()
{
    if(window.isOpen())
        return;

    sf::VideoMode videoMode(size.x, size.y);
    window.create(videoMode, title, style);
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
    window.setSize(size);
}

bool Window::IsOpen()
{
    return window.isOpen();
}
