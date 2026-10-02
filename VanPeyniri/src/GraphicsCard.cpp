#include "GraphicsCard.h"

GraphicsCard::GraphicsCard()
{
}

GraphicsCard::~GraphicsCard()
{
}

void GraphicsCard::run()
{	
	switch (m_regCommand)
	{
	case 0:
		break;

	//DRAW_PIXEL
	case 1:
		drawPixel();
		break;

	//CLEAR_ALL
	case 2:
		clearBuffer();
		break;

	}

	m_regCommand = 0;
}

void GraphicsCard::reset()
{
	std::fill(m_vram.begin(), m_vram.end(), 0);
	m_regColor = 0;
	m_regCommand = 0;
	m_regPosx = 0;
	m_regPosy = 0;
}

void GraphicsCard::draw(SDL_Renderer* renderer)
{
	for (size_t x = 0; x < m_WINDOW_WIDTH; x++)
	{
		for (size_t y = 0; y < m_WINDOW_HEIGHT; y++)
		{
			SDL_Color color = { 0,0,0,255 };
			
			switch (m_vram[y * m_WINDOW_WIDTH + x])
			{
			case 0:
				color = { 0,0,255,255 };
				break;

			case 1:
				color = { 0,255,0,255 };
				break;
			}

			SDL_FRect rect = { x * (m_PIXEL_SIZE + 1) , y * (m_PIXEL_SIZE + 1) , m_PIXEL_SIZE, m_PIXEL_SIZE };

			SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
			SDL_RenderFillRect(renderer, &rect);
		}		
	}
}

void GraphicsCard::clearBuffer()
{
	std::fill(m_vram.begin(), m_vram.end(), m_regColor);
}

void GraphicsCard::drawPixel()
{
	m_vram[m_regPosy * m_WINDOW_WIDTH + m_regPosx] = m_regColor;
}
