#include "SynGame.hpp"

class GUIWindow : public Window
{
    private:
        SynButton *buttons;
        SynText output;
        SynInputField input;
        void BinaryButton();
        void QuaternaryButton();
        void OctalButton();
        void DecimalButton();
        void HexadecimalButton();
        void InputBinaryButton();
        void InputQuaternaryButton();
        void InputOctalButton();
        void InputDecimalButton();
        void InputHexadecimalButton();
        std::string GetBase(unsigned int, int);
    public:
        GUIWindow(unsigned int = 960, unsigned int = 540, std::string = "Window", sf::Uint32 = sf::Style::Titlebar | sf::Style::Close);
        void Update();
        void ButtonCheck(sf::Vector2i);
        void KeyHandle(char);
        ~GUIWindow();
};

void GUIWindow::BinaryButton()
{
    output.SetText(GetBase(input.GetValue(), 2));
}

void GUIWindow::QuaternaryButton()
{
    output.SetText(GetBase(input.GetValue(), 4));
}

void GUIWindow::OctalButton()
{
    output.SetText(GetBase(input.GetValue(), 8));
}

void GUIWindow::DecimalButton()
{
    output.SetText(GetBase(input.GetValue(), 10));
}

void GUIWindow::HexadecimalButton()
{
    output.SetText(GetBase(input.GetValue(), 16));
}

void GUIWindow::InputBinaryButton()
{
    input.SetBase(2);
}

void GUIWindow::InputQuaternaryButton()
{
    input.SetBase(4);
}

void GUIWindow::InputOctalButton()
{
    input.SetBase(8);
}

void GUIWindow::InputDecimalButton()
{
    input.SetBase(10);
}

void GUIWindow::InputHexadecimalButton()
{
    input.SetBase(16);
}


std::string GUIWindow::GetBase(unsigned int value, int base)
{
    std::stringstream stringStream;
    int counter = 0;

    while (value > 0)
    {
        if(base != 10)
            if(counter++ % 4 == 0)
                stringStream << ' ';

        if(base == 16)
            if((value % base) > 9)
                stringStream << (char)(((value % base) % 10) + 'A'); 
            else
                stringStream << (value % base);
        else
            stringStream << (value % base); 
        
        value = value / base;
    }

    if(base != 10)
        while (counter++ % 4 != 0)
            stringStream << '0';

    std::string displayValue = stringStream.str();

    char temp;
    int half = displayValue.length() / 2;
    int last = displayValue.length() - 1;

    for (int i = 0; i < half; i++)
    {
        temp = displayValue[i];
        displayValue[i] = displayValue[last];
        displayValue[last--] = temp;
    }
    
    displayValue.insert(0, "Sonuc: ");
    return displayValue;
}

GUIWindow::GUIWindow(unsigned int width, unsigned int height, std::string title, sf::Uint32 style) : Window(width, height, title, style)
{
    input.SetPosition(window.getSize().x / 2 - 120, 210);
    input.SetArea(400, 100);
    input.SetBase(10);
    output.SetText("");
    output.SetCentered(true);
    output.SetPosition(window.getSize().x / 2 - 20, 310);
    output.SetOffset(0, 0);
    buttons = new SynButton[10];

    (buttons + 0) -> SetText("Binary"); 
    (buttons + 1) -> SetText("Quaternary");
    (buttons + 2) -> SetText("Octal");
    (buttons + 3) -> SetText("Decimal");
    (buttons + 4) -> SetText("Hexadecimal");

    (buttons + 5) -> SetText("Binary"); 
    (buttons + 6) -> SetText("Quaternary");
    (buttons + 7) -> SetText("Octal");
    (buttons + 8) -> SetText("Decimal");
    (buttons + 9) -> SetText("Hexadecimal");
    
    (buttons + 0) -> SetArea(400, 100); (buttons + 0) -> SetPosition(650, 50);
    (buttons + 1) -> SetArea(400, 100); (buttons + 1) -> SetPosition(650, 150);
    (buttons + 2) -> SetArea(400, 100); (buttons + 2) -> SetPosition(650, 250);
    (buttons + 3) -> SetArea(400, 100); (buttons + 3) -> SetPosition(650, 350);
    (buttons + 4) -> SetArea(400, 100); (buttons + 4) -> SetPosition(650, 450);
    
    (buttons + 5) -> SetArea(400, 100); (buttons + 5) -> SetPosition(50, 50);
    (buttons + 6) -> SetArea(400, 100); (buttons + 6) -> SetPosition(50, 150);
    (buttons + 7) -> SetArea(400, 100); (buttons + 7) -> SetPosition(50, 250);
    (buttons + 8) -> SetArea(400, 100); (buttons + 8) -> SetPosition(50, 350);
    (buttons + 9) -> SetArea(400, 100); (buttons + 9) -> SetPosition(50, 450);

    (buttons + 0) -> Bind(this, &GUIWindow::BinaryButton);
    (buttons + 1) -> Bind(this, &GUIWindow::QuaternaryButton);
    (buttons + 2) -> Bind(this, &GUIWindow::OctalButton);
    (buttons + 3) -> Bind(this, &GUIWindow::DecimalButton);
    (buttons + 4) -> Bind(this, &GUIWindow::HexadecimalButton);

    (buttons + 5) -> Bind(this, &GUIWindow::InputBinaryButton);
    (buttons + 6) -> Bind(this, &GUIWindow::InputQuaternaryButton);
    (buttons + 7) -> Bind(this, &GUIWindow::InputOctalButton);
    (buttons + 8) -> Bind(this, &GUIWindow::InputDecimalButton);
    (buttons + 9) -> Bind(this, &GUIWindow::InputHexadecimalButton);
}

void GUIWindow::Update()
{
    
    int buttonCounter;

    Window::Update();

    if(!isFocused) 
        return;

    window.clear(backColor);

    for (buttonCounter = 0; buttonCounter < 10; buttonCounter++)
    {
        window.draw((buttons + buttonCounter) -> GetVertices(), 4, sf::PrimitiveType::Quads);
        window.draw((buttons + buttonCounter) -> GetText());
    }

    window.draw(output.GetText());
    window.draw(input.GetVertices(), 4, sf::PrimitiveType::Quads);
    window.draw(input.GetText());
    window.display();
}


void GUIWindow::ButtonCheck(sf::Vector2i mousePos)
{
    int i;
    SynButton *current;
    for (i = 0; i < 10; i++)
    {
        current = buttons + i;
        if(current -> IsMouseOver(mousePos.x, mousePos.y))
        {
            (buttons + i) -> Click();
            break;
        }
    }
    input.Click(input.IsMouseOver(mousePos.x, mousePos.y));
}

void GUIWindow::KeyHandle(char character)
{
    input.AddToInput(character);
}

GUIWindow::~GUIWindow()
{
    if(buttons) delete buttons;
}
