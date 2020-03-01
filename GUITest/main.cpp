#include "SynGame.hpp"

int main()
{
    font.loadFromFile("../OpenSans-Bold.ttf");
    GUIWindow window(960, 540, "GUI Test");

    while (window.IsOpen())
        window.Update();
    
    return 0;
}