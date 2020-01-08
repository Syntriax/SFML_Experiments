#include "SynGame.hpp"

class RenderWindow : public Window
{
    private:
        sf::Vertex *vertices;
        unsigned int pixelSize;
        sf::Vertex *_CreateVertexBuffer();
        void ReloadScreenBuffer();
    public:
        RenderWindow(unsigned int = 960, unsigned int = 540, std::string = "Window", sf::Uint32 = sf::Style::Titlebar | sf::Style::Close);
        ~RenderWindow();
        void Update();
        void CreateWindow();
        void CloseWindow();
        void SetSize(unsigned int, unsigned int);
};

void RenderWindow::Update()
{
    if(!isFocused) 
        return;

    Window::Update();
    window.clear();
    window.draw(vertices, size.x * size.y, sf::Points);
    window.display();
}

sf::Vertex *RenderWindow::_CreateVertexBuffer()
{
    int y;
    int x;
    sf::Vertex *newBuffer = new sf::Vertex[size.x * size.y];
    sf::Vertex *ptr = newBuffer;

    for (y = 0; y < size.y; y++)
        for (x = 0; x < size.x; x++)
        {
            ptr -> color = sf::Color::Black;
            ptr++ -> position = sf::Vector2f(x, y); 
        }

    return newBuffer;    
}

void RenderWindow::ReloadScreenBuffer()
{
    if(vertices)
        delete[] vertices;

    vertices = _CreateVertexBuffer();
}

void RenderWindow::CreateWindow()
{
    if(window.isOpen())
        return;
    
    Window::CreateWindow();
    ReloadScreenBuffer();
}

void RenderWindow::CloseWindow()
{
    if(!window.isOpen())
        return;

    Window::CloseWindow();
    
    if(vertices)
        delete[] vertices;

    vertices = NULL;
}

void RenderWindow::SetSize(unsigned int width, unsigned int height)
{
    Window::SetSize(width, height);
    ReloadScreenBuffer();
}

RenderWindow::RenderWindow(unsigned int width, unsigned int height, std::string title, sf::Uint32 style) : Window(width, height, title, style)
{
    ReloadScreenBuffer();
}

RenderWindow::~RenderWindow()
{
    if(vertices)
        delete[] vertices;
}
