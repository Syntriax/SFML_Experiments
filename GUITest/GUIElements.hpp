#include "SynGame.hpp"

class SynButton
{
    private:
        sf::Text textDisplay;
        std::string text;
        static sf::Font font;
        int x;
        int y;
        int width;
        int height;
        void (*action)(int);
        int *value;
    public:
        SynButton(std::string, int, int, int, int);
        void Bind(void (*)(int), int *);
        bool IsMouseOver(int, int);
        void Click();
        ~SynButton();
};

SynButton::SynButton(std::string text, int x, int y, int width, int height)
{
    textDisplay.setFont(font);
    textDisplay.setString(text);
    this -> x = x;
    this -> y = y;
    this -> width = width;
    this -> height = height;
}

void SynButton::Bind(void (*action)(int), int *value)
{
    this -> action = action;
    this -> value = value;
}

bool SynButton::IsMouseOver(int mouseX, int mouseY)
{
    bool isOver;
    int halfWidth = width / 2;
    int halfHeight = height / 2;
    isOver = mouseX <= x + halfWidth && 
             mouseX >= x - halfWidth && 
             mouseY <= y + halfHeight && 
             mouseY >= y - halfHeight;
    return isOver;
}

void SynButton::Click()
{
    if(value)
        action(*value);
}

SynButton::~SynButton()
{
}
