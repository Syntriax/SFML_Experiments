#include "SynGame.hpp"

sf::Font font;
sf::Color textColor = sf::Color(35, 35, 35);
sf::Color backColor = sf::Color(125, 162, 169);
sf::Color frontColor = sf::Color(247, 247, 247);

class GUIWindow;

#pragma region Text
    class SynText
    {
        protected:
            int x;
            int y;
            int offsetX;
            int offsetY;
            bool isCentered;
            sf::Text textDisplay;
        public:
            SynText(std::string = "", int = 0, int = 0, int = 0, int = 0, bool = false);
            virtual void SetText(std::string);
            virtual void SetOffset(int, int);
            virtual void SetPosition(int, int);
            virtual void SetCentered(bool);
            sf::Text GetText();
            ~SynText();
    };

    SynText::SynText(std::string text, int x, int y, int offsetX, int offsetY, bool isCentered)
    {    
        this -> isCentered = isCentered;
        textDisplay.setFont(font);
        textDisplay.setColor(textColor);
        SetText(text);
        SetOffset(offsetX, offsetX);
        SetPosition(x, y);
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

#pragma region InputField
    class SynInputField : public SynText
    {
        private:
            int width;
            int height;
            std::stringstream stream;
            sf::Vertex vertices[4];
            void CalculateVertices();
            int base;
            bool isFocused;
        public:
            SynInputField();
            void SetText(std::string);
            void SetArea(int, int);
            void SetOffset(int, int);
            void SetPosition(int, int);
            bool IsMouseOver(int, int);
            void AddToInput(char);
            void Click(bool);
            void SetBase(int);
            unsigned int GetValue();
            sf::Vertex *GetVertices();
            ~SynInputField();
    };
    
    SynInputField::SynInputField()
    {
        isFocused = false;
        stream.clear();
        SetOffset(7, 7);
        SetText(stream.str());

        for (int i = 0; i < 4; i++)
            vertices[i].color = frontColor;
    }

    void SynInputField::SetText(std::string newText)
    {
        SynText::SetText(newText);
        CalculateVertices();
    }
    
    void SynInputField::SetOffset(int x, int y)
    {
        SynText::SetOffset(x, y);
        CalculateVertices();
    }

    void SynInputField::SetPosition(int x, int y)
    {
        SynText::SetPosition(x, y);
        CalculateVertices();
    }

    void SynInputField::CalculateVertices()
    {
        float newWidth = width / 2;
        float newHeight = height / 2;

        vertices[0].position = sf::Vector2f(x, y);
        vertices[1].position = sf::Vector2f(x + newWidth, y);
        vertices[2].position = sf::Vector2f(x + newWidth, y + newHeight);
        vertices[3].position = sf::Vector2f(x, y + newHeight);
    }

    sf::Vertex *SynInputField::GetVertices()
    {
        return vertices;
    }

    unsigned int SynInputField::GetValue()
    {
        unsigned int value = 0;
        unsigned int calculatedValue = 0;
        char character;
        int counter = 0;
        std::stringstream temp;
        std::string tempString;
        temp << stream.str();
        
        if(base != 10)
            while (temp.str().length() > 0)
            {
                tempString = temp.str();
                character = tempString[tempString.length() - 1];
                tempString.pop_back();
                temp.str("");
                temp << tempString;

                if(character >= 'A')
                    calculatedValue = character - 'A' + 10;
                else
                    calculatedValue = character - '0';
                
                calculatedValue *= pow(base, counter++);
                value += calculatedValue;
            }
        else
            temp >> value;

        return value;
    }

    bool SynInputField::IsMouseOver(int mouseX, int mouseY)
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

    void SynInputField::Click(bool isFocused)
    {
        this -> isFocused = isFocused;
    }

    void SynInputField::SetBase(int base)
    {
        switch (base)
        {
            case 2:
            case 4:
            case 8:
            case 10:
            case 16:
                this -> base = base;
                stream.str("");
                SetText("");
                break;
            
            default:
                return;
        }
    }

    void SynInputField::AddToInput(char character)
    {
        if(!isFocused) return;

        if(character == 59 && stream.str().length() > 0) // Backspace
        {
            std::string temp = stream.str();
            temp.pop_back();
            stream.str("");
            stream << temp;
            SetText(stream.str());
            return;
        }
        
        if(character < 26 || character > 35) // 0 - 9 keys
        {
            if(base == 16)
            {
                if(character > 5)
                    return;
            }
            else
                return;
        }

        switch (base)
        {
            case 2:
                if(character < 26 || character > 27)
                    return;
                break;
            case 4:
                if(character < 26 || character > 29)
                    return;
                break;
            case 8:
                if(character < 26 || character > 33)
                    return;
                break;
        }

        if(stream.str().length() > 7)
            return;

        if(base == 16 && character < 6)
            stream << (char)(character + 65);
        else
            stream << character - 26;
        SetText(stream.str());
    }

    void SynInputField::SetArea(int width, int height)
    {
        this -> width = width;
        this -> height = height;
        SetPosition(x, y);
        CalculateVertices();
    }
    
    SynInputField::~SynInputField()
    {
    }
    
#pragma endregion

#pragma region Button
    class SynButton
    {
        private:
            SynText synText;
            GUIWindow *window;
            void (GUIWindow::*action)();
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
            void Bind(GUIWindow *, void (GUIWindow::*)());
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
        synText.SetOffset(0, -7);
        SetArea(width, height);
        SetPosition(x, y);
        CalculateVertices();
        
        for (int i = 0; i < 4; i++)
            vertices[i].color = frontColor;
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

    void SynButton::Bind(GUIWindow *window, void (GUIWindow::*action)())
    {
        this -> window = window;
        this -> action = action;
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
        ((window)->*(action))();
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
