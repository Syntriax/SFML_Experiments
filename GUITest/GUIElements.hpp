#include "SynGame.hpp"

sf::Font font;

#pragma region Text
    class SynText
    {
        private:
            int x;
            int y;
            int offsetX;
            int offsetY;
            bool isCentered;
            sf::Text textDisplay;
        public:
            SynText(std::string = "", int = 0, int = 0, int = 0, int = 0, bool = false);
            void SetText(std::string);
            void SetOffset(int, int);
            void SetPosition(int, int);
            void SetCentered(bool);
            sf::Text GetText();
            ~SynText();
    };

    SynText::SynText(std::string text, int x, int y, int offsetX, int offsetY, bool isCentered)
    {    
        this -> isCentered = isCentered;
        textDisplay.setFont(font);
        SetText(text);
        SetOffset(offsetX, offsetX);
        SetPosition(x, y);
        textDisplay.setColor(sf::Color::Red);
    }

    void SynText::SetText(std::string text)
    {
        textDisplay.setString(text);
        SetPosition(x, y);
    }

    void SynText::SetPosition(int x, int y)
    {
        this -> x = x;
        this -> y = y;
        x += offsetX;
        y += offsetY;

        if(isCentered)
            textDisplay.setOrigin((int)textDisplay.getLocalBounds().width / 2, (int)textDisplay.getLocalBounds().height / 2);
        
        textDisplay.setPosition(x, y);
    }

    void SynText::SetOffset(int offsetX, int offsetY)
    {
        this -> offsetX = offsetX;
        this -> offsetY = offsetY;
        SetPosition(x, y);
    }
    void SynText::SetCentered(bool isCentered)
    {
        this -> isCentered = isCentered;
    }

    sf::Text SynText::GetText()
    {
        return textDisplay;
    }

    SynText::~SynText()
    {
    }
#pragma endregion

#pragma region Button
    class SynButton
    {
        private:
            SynText synText;
            void (*action)(int);
            int *value;
            int x;
            int y;
            int width;
            int height;
            sf::Vertex vertices[4];
            void CalculateVertices();
        public:
            SynButton(std::string = "", int = 0, int = 0, int = 0, int = 0);
            void SetText(std::string);
            void SetPosition(int, int);
            void SetArea(int, int);
            void Bind(void (*)(int), int *);
            bool IsMouseOver(int, int);
            void Click();
            sf::Text GetText();
            sf::Vertex *GetVertices();
            ~SynButton();
    };

    void SynButton::CalculateVertices()
    {
        float newWidth = width / 2;
        float newHeight = height / 2;
        vertices[0].position = sf::Vector2f(x, y);
        vertices[1].position = sf::Vector2f(x + newWidth, y);
        vertices[2].position = sf::Vector2f(x + newWidth, y + newHeight);
        vertices[3].position = sf::Vector2f(x, y + newHeight);
    }

    SynButton::SynButton(std::string text, int x, int y, int width, int height)
    {
        synText.SetCentered(true);
        synText.SetOffset(0, -5);
        SetArea(width, height);
        SetPosition(x, y);
        CalculateVertices();
    }

    void SynButton::SetText(std::string text)
    {
        synText.SetText(text);
    }

    void SynButton::SetPosition(int x, int y)
    {
        this -> x = x;
        this -> y = y;
        synText.SetPosition(x + width / 4, y + height / 4);
        CalculateVertices();
    }

    void SynButton::SetArea(int width, int height)
    {
        this -> width = width;
        this -> height = height;
        synText.SetPosition(x + width / 4, y + height / 4);
        CalculateVertices();
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
                mouseX >= x && 
                mouseY <= y + halfHeight && 
                mouseY >= y;
        return isOver;
    }

    void SynButton::Click()
    {
        if(value)
            action(*value);
        else
            action(y);
    }
    sf::Text SynButton::GetText()
    {
        return synText.GetText();
    }
    sf::Vertex *SynButton::GetVertices()
    {
        return vertices;
    }

    SynButton::~SynButton()
    {
    }
#pragma endregion
