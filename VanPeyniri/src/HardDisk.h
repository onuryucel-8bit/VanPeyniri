#pragma once

#include <iostream>
#include <fstream>
#include <cstdint>

class HardDisk
{
public:
	HardDisk();
	~HardDisk();

	void run(std::unique_ptr<uint8_t[]>& ram);

	static constexpr uint16_t m_HADRES_INDEX_0 = 0x0A01;
	static constexpr uint16_t m_HADRES_INDEX_1 = 0x0A02;
	static constexpr uint16_t m_HADRES_INDEX_2 = 0x0A03;
	static constexpr uint16_t m_HADRES_INDEX_3 = 0x0A04;
	static constexpr uint16_t m_HSIZE_INDEX = 0x0A05;

	static constexpr uint16_t m_HCONTROL_INDEX = 0x0A06;
	static constexpr uint16_t m_HSTATUS_INDEX = 0x0A07;

	static constexpr uint16_t m_HRAM_INDEX_0 = 0x0A08;
	static constexpr uint16_t m_HRAM_INDEX_1 = 0x0A09;

	uint8_t m_regHadres0 = 0;
	uint8_t m_regHadres1 = 0;
	uint8_t m_regHadres2 = 0;
	uint8_t m_regHadres3 = 0;

	uint8_t m_regHSize = 0;

	uint8_t m_regHControl = 0;
	uint8_t m_regHStatus = 0;

	uint8_t m_regHRAMadres0 = 0;
	uint8_t m_regHRAMadres1 = 0;

private:
	void write(std::unique_ptr<uint8_t[]>& ram);
	void read(std::unique_ptr<uint8_t[]>& ram);

};

