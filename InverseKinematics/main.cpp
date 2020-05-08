#include "SynGame.hpp"

int main()
{
    TestWindow window(1600, 900, "Inverse Kinematics Test Syntriax");
    window.SetFrameRate(60);
    
    while (window.IsOpen())
        window.Update();

    return 0;
}
