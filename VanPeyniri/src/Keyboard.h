#pragma once

#include <iostream>
#include <cstdint>

#include "SDL3/SDL.h"

class Keyboard
{
public:
	Keyboard();
	~Keyboard();

	static constexpr uint16_t m_KEY_INDEX = 0x0A00;

	uint8_t m_regKey = 0;

	bool run(SDL_Event& event);
private:

};
