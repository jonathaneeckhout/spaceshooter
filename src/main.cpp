#include <iostream>

#include <jengine/JEngine.hpp>

int main()
{
    std::cout << "Hello world" << std::endl;

    JEngine *engine = new JEngine();

    delete engine;

    return 0;
}