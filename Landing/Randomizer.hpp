#include <time.h>
#include <iostream>

template <typename T> 
T Random(T min, T max)
{
    T result;
    long int value;
    static unsigned long int counter = time(0);
    srand(time(0) * counter++);
    value = ((rand() * counter) % (int)((max - min) * 100000000.0));
    result = value / 100000000.0 + min;
    return result;
}