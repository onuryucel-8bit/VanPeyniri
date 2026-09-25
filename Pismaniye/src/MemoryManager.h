#pragma once

#include <iostream>
#include <optional>
#include <cstdint>
#include <unordered_map>

enum class VarSize
{
	Char,
	Short,
	Int
};

enum class Register
{
	None,
	A,
	X,
	Y
};

enum class StorageLocation
{
	ZeroPage,
	Stack,
	Register,
	DataSegment
};

struct VarInfo
{
	uint16_t m_address = 0;
	uint8_t m_value = 0;
	VarSize m_size = VarSize::Char;
	StorageLocation m_strorageLocation = StorageLocation::ZeroPage;
	Register m_reg = Register::None;
};

class MemoryManager
{
public:
	MemoryManager();
	~MemoryManager();

	uint16_t createVariable(std::string varname, VarSize var);

	std::optional<VarInfo> getVarInfo(std::string varname);
	std::optional<uint8_t> getValue(std::string varname);

	void setValue(std::string varname, uint8_t value);

	bool allocRegister(Register regname);
	void freeRegister(Register regname);

	void createCommand(uint8_t size);

private:


	//========================================//
	uint16_t STACK_START = 0x0100;
	uint16_t STACK_END = 0x01FF;
	
	uint16_t ZERO_PAGE_START = 0x0000;
	uint16_t ZERO_PAGE_END = 0x00FF;

	//TODO burayi derleyici - emu calismaya basladiginda degistir
	uint16_t DATA_SEGMENT_START = 0x0FFF;
	uint16_t DATA_SEGMENT_END = 0x1000;

	uint16_t TEXT_SEGMENT_START = 0x0100;
	//========================================//

	uint16_t m_textSegmentIndex = TEXT_SEGMENT_START;
	uint16_t m_dataSegmentIndex = DATA_SEGMENT_START;
	uint16_t m_zeroPageIndex = ZERO_PAGE_START;
	uint16_t m_stackPointer = STACK_START;

	bool f_usableRegisters[3] = {true, true, true};

	std::unordered_map<std::string, VarInfo> m_vartable;
	
};

