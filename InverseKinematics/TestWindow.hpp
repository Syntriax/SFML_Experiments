#include "SynGame.hpp"

class TestWindow : public Window
{
    protected:
        InverseKinematics kinematics;
        Vector2 target;
        Vector2 *points;
        unsigned int pointCount;
    public:
        TestWindow(unsigned int = 960, unsigned int = 540, std::string = "Window", sf::Uint32 = sf::Style::Titlebar | sf::Style::Close);
        void Update();
};

void TestWindow::Update()
{
    int i;
    Window::Update();
    
    if(!isFocused)
        return;

    target = Vector2(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
    kinematics.Iterate();
    sf::Vertex *array = new sf::Vertex[this -> pointCount];
    
    for (i = 0; i < this -> pointCount; i++)
        *(array + i) = sf::Vertex(sf::Vector2f((points + i) -> x, (points + i) -> y), sf::Color::White);

    window.clear(sf::Color::Black);
    window.draw(array, this -> pointCount, sf::PrimitiveType::LinesStrip);
    window.display();
    delete array;
}

TestWindow::TestWindow(unsigned int width, unsigned int height, std::string title, sf::Uint32 style) : Window(width, height, title, style) 
{
    pointCount = 5;
    points = new Vector2[pointCount];

    for (int i = 0; i < pointCount; i++)
        *(points + i) = Vector2(500 + i * 75, 500 + i * 75);

    kinematics.SetPoints(points, pointCount);
    kinematics.SetRoot(*(points + 0));
    kinematics.SetIterationCount(10);
    kinematics.SetTarget(&target);
}
