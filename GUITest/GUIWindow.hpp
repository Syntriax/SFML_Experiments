#include "SynGame.hpp"

class GUIWindow : public Window
{
    private:
    public:
        GUIWindow(unsigned int = 960, unsigned int = 540, std::string = "Window", sf::Uint32 = sf::Style::Titlebar | sf::Style::Close);
        void Update();
        ~GUIWindow();
};

GUIWindow::GUIWindow(unsigned int width, unsigned int height, std::string title, sf::Uint32 style) : Window(width, height, title, style)
{

}

void GUIWindow::Update()
{
    if(!isFocused) 
        return;

    Window::Update();
}

GUIWindow::~GUIWindow()
{
}
