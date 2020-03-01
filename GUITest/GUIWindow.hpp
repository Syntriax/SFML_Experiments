#include "SynGame.hpp"
#include <iostream>

class GUIWindow : public Window
{
    private:
        SynButton *buttons;
        SynText output;
        void BinaryButton();
        void QuaternaryButton();
        void OctalButton();
        void HexadecimalButton();
    public:
        GUIWindow(unsigned int = 960, unsigned int = 540, std::string = "Window", sf::Uint32 = sf::Style::Titlebar | sf::Style::Close);
        void Update();
        void ButtonCheck(sf::Vector2i);
        ~GUIWindow();
};

void GUIWindow::BinaryButton()
{
    output.SetText("Output: Binary");
}

void GUIWindow::QuaternaryButton()
{
    output.SetText("Output: Quaternary");
}

void GUIWindow::OctalButton()
{
    output.SetText("Output: Octal");
}

void GUIWindow::HexadecimalButton()
{
    output.SetText("Output: Hexadecimal");
}

GUIWindow::GUIWindow(unsigned int width, unsigned int height, std::string title, sf::Uint32 style) : Window(width, height, title, style)
{
    output.SetText("Output: ");
    output.SetCentered(true);
    output.SetPosition(window.getSize().x / 2, window.getSize().y / 2);
    output.SetOffset(0, 0);
    buttons = new SynButton[4];

    (buttons + 0) -> SetText("Binary"); 
    (buttons + 1) -> SetText("Quaternary");
    (buttons + 2) -> SetText("Octal");
    (buttons + 3) -> SetText("Hexadecimal");
    
    (buttons + 0) -> SetArea(400, 100); (buttons + 0) -> SetPosition(650, 100);
    (buttons + 1) -> SetArea(400, 100); (buttons + 1) -> SetPosition(650, 200);
    (buttons + 2) -> SetArea(400, 100); (buttons + 2) -> SetPosition(650, 300);
    (buttons + 3) -> SetArea(400, 100); (buttons + 3) -> SetPosition(650, 400);

    (buttons + 0) -> Bind((void (*)(int))&BinaryButton, NULL);
    (buttons + 1) -> Bind((void (*)(int))&QuaternaryButton, NULL);
    (buttons + 2) -> Bind((void (*)(int))&OctalButton, NULL);
    (buttons + 3) -> Bind((void (*)(int))&HexadecimalButton, NULL);
}

void GUIWindow::Update()
{
    
    int buttonCounter;

    Window::Update();

    if(!isFocused) 
        return;

    window.clear(sf::Color::Black);

    for (buttonCounter = 0; buttonCounter < 4; buttonCounter++)
    {
        window.draw((buttons + buttonCounter) -> GetVertices(), 4, sf::PrimitiveType::Quads);
        window.draw((buttons + buttonCounter) -> GetText());
    }

    window.draw(output.GetText());
    window.display();
}


void GUIWindow::ButtonCheck(sf::Vector2i mousePos)
{
    int i;
    SynButton *current;
    for (i = 0; i < 4; i++)
    {
        current = buttons + i;
        if(current -> IsMouseOver(mousePos.x, mousePos.y))
        {
            (buttons + i) -> Click();
            break;
        }
    }
    
}

GUIWindow::~GUIWindow()
{
    if(buttons) delete buttons;
}
