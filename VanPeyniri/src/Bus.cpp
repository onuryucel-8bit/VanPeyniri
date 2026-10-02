#include "Bus.h"
#include "Bus.h"


Bus::Bus()
    :m_cpu
    (
        [this](uint16_t addr) 
        { return busRead(addr); },

        [this](uint16_t addr, uint8_t data) 
        { busWrite(addr, data); }
    )
{   
    m_cpu.Reset();
}

Bus::~Bus()
{
}

void Bus::busWrite(uint16_t address, uint8_t data)
{                     
    //TODO veri hatti - klavye bagli degil
    
    switch (address)    
    {
    
    //===================================//
    //Ekran karti adresleri
    case m_gpu.m_POSX_INDEX:
        m_gpu.m_regPosx = data;
        break;

    case m_gpu.m_POSY_INDEX:
        m_gpu.m_regPosy = data;
        break;

    case m_gpu.m_COLOR_INDEX:
        m_gpu.m_regColor = data;
        break;

    case m_gpu.m_COMMAND_INDEX:
        m_gpu.m_regCommand = data;
        break;
    //===================================//               
    }

    m_RAM[address] = data;
}

uint8_t Bus::busRead(uint16_t address)
{
    uint8_t retval = 0;

    switch (address)
    {
    case m_keyboard.m_KEY_INDEX:
        retval = m_RAM[address];
        m_cpu.IRQ(true);
        m_keyboard.m_regKey = 0;
        break;

    default:
        retval = m_RAM[address];
        break;
    }

    return retval;
}