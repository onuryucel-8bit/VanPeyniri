#include "Keyboard.h"

Keyboard::Keyboard()
{
}

Keyboard::~Keyboard()
{
}

bool Keyboard::run(SDL_Event& event)
{
    std::cout << std::hex <<  event.key.key << "\n";
    m_regKey = event.key.key;

    return m_regKey != 0;

    /*switch (event.key.key)
    {
    case SDLK_A:
        std::cout << "aaaa\n";
        break;
    }*/
}
