#pragma once

#include <cstdint>
#include <algorithm>
#include <array>

#include "SDL3/SDL.h"


class GraphicsCard
{
public:
	GraphicsCard();
	~GraphicsCard();

	//Bellek adresleri
	static constexpr uint16_t m_POSX_INDEX = 0x1000;
	static constexpr uint16_t m_POSY_INDEX = 0x1001;
	static constexpr uint16_t m_COLOR_INDEX = 0x1002;
	static constexpr uint16_t m_COMMAND_INDEX = 0x1003;

	uint8_t m_regPosx = 0;
	uint8_t m_regPosy = 0;
	uint8_t m_regCommand = 0;
	uint8_t m_regColor = 0;

	void run();
	void draw(SDL_Renderer* renderer);

	void reset();

private:

	void clearBuffer();
	void drawPixel();
	
	static constexpr uint8_t m_WINDOW_WIDTH = 32;
	static constexpr uint8_t m_WINDOW_HEIGHT = 32;
	const uint8_t m_PIXEL_SIZE = 16;

	std::array<uint8_t, m_WINDOW_WIDTH* m_WINDOW_HEIGHT> m_vram = {};
};

