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

    //PRINT
    case 3:
        print();
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
				color = { 100,100,100,255 };
				break;

			case 1:
				color = { 200,200,200,255 };
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

void GraphicsCard::drawPixel(uint8_t x, uint8_t y, uint8_t color)
{
    m_vram[y * m_WINDOW_WIDTH + x] = color;
}

void GraphicsCard::print()
{
    //Bazlama yiyen deniz anasi

    if (vgay >= m_WINDOW_HEIGHT)
    {
        vgay = 0;
    }

    if (vgax > m_WINDOW_WIDTH)
    {
        vgax = 0;
    }

    switch (m_regChar)
    {
    case '\n':
        vgay += 8;
        vgax = 0;

        return;

    case '\t':
        vgax += 16;
        return;

    default:
        break;
    }

    uint16_t start_x = vgax;
    uint16_t start_y = vgay;

    for (uint8_t row = 0; row < 8; row++)
    {
        uint8_t line = font8x8[m_regChar][row];
        uint8_t mask = 1;

        //TODO neden int8_t ?
        for (int8_t col = 0; col < 8; col++)
        {
            uint8_t bit = (line & mask) >> col;
            mask <<= 1;

            if (bit == 1)
            {
                //fg                
                drawPixel(start_x, start_y, m_regColor);
            }
            else
            {
                //bg
                drawPixel(start_x, start_y, m_regBgColor);
            }

            start_x++;
        }

        start_x = vgax;
        start_y++;
    }

    vgax += 8;

    if (vgax >= m_WINDOW_WIDTH)
    {
        vgax = 0;
        vgay += 8;
    }
}
