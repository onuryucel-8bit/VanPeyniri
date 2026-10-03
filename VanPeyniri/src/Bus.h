#pragma once

#include <cstdint>
#include <memory>

#include "emu_mos6502/mos6502.h"
#include "GraphicsCard.h"
#include "Keyboard.h"
#include "HardDisk.h"

class Bus
{
public:
	Bus();
	~Bus();
	
	void busWrite(uint16_t address, uint8_t data);
	uint8_t busRead(uint16_t address);

	std::unique_ptr<uint8_t[]> m_RAM = std::make_unique<uint8_t[]>(0x10000);

	mos6502 m_cpu;
	GraphicsCard m_gpu;
	Keyboard m_keyboard;
	HardDisk m_hdd;

private:

};
