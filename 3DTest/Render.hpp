#include "SynGame.hpp"

class RenderWindow : public Window
{
    private:
        sf::Vertex *vertices;
        unsigned int pixelSize;
        sf::Vertex *_CreateVertexBuffer();
        void ReloadScreenBuffer();
        void Render();
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
    Render();

    window.clear();
    window.draw(vertices, size.x * size.y, sf::Points);
    window.display();
}

void RenderWindow::Render()
{
    int y;
    int x;
    sf::Vertex *ptr = vertices;
    Sphere spheres[9];
    spheres[0].position = Vector3( 10, 0,  0); spheres[0].radius = 1.0;
    spheres[1].position = Vector3(-10, 0,  0); spheres[1].radius = 1.0;
    spheres[2].position = Vector3( 0, -10, 0); spheres[2].radius = 1.0;
    spheres[3].position = Vector3( 0,  10, 0); spheres[3].radius = 1.0;
    spheres[4].position = Vector3( 10, 10,  -10); spheres[4].radius = 1.0;
    spheres[5].position = Vector3(-10,-10,  -10); spheres[5].radius = 1.0;
    spheres[6].position = Vector3( 10, -10, -10); spheres[6].radius = 1.0;
    spheres[7].position = Vector3(-10,  10, -10); spheres[7].radius = 1.0;
    spheres[8].position = Vector3(0,  0, 10); spheres[8].radius = 5;
    RayMarch ray = RayMarch();
    Vector3 cameraPos(0, 0, -timer.GetTimePassed() * 2);
    Vector3 rayDirection;
    ray.SetRay(cameraPos, rayDirection, spheres, 9, 100);
    rayDirection = (0, 0, 0);
    for (y = 0; y < size.y; y++)
        for (x = 0; x < size.x; x++)
        {
            // Change this
            rayDirection.x = (float)x - (float)size.x / 2.0;
            rayDirection.y = (float)y - (float)size.y / 2.0;
            rayDirection.z = 1000.0;
            rayDirection = rayDirection.Normalized();
            
            ray.SetPosition(cameraPos, rayDirection);

            ptr -> color = ray.FireRay();
            ptr++;
        }
}

sf::Vertex *RenderWindow::_CreateVertexBuffer()
{
    int y;
    int x;
    sf::Vertex *newVertices = new sf::Vertex[size.x * size.y];
    sf::Vertex *ptr = newVertices;

    for (y = 0; y < size.y; y++)
        for (x = 0; x < size.x; x++)
        {
            ptr -> color = sf::Color::Black;
            ptr++ -> position = sf::Vector2f(x, y); 
        }

    return newVertices;    
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
