#include "MemoryManager.h"
#include "MemoryManager.h"
#include "MemoryManager.h"

MemoryManager::MemoryManager()
{
}

MemoryManager::~MemoryManager()
{
}

uint16_t MemoryManager::createVariable(std::string varname, VarSize var)
{
	auto it = m_vartable.find(varname);

	//tabloda verilen degisken varmi?
	if (it != m_vartable.end())
	{
		//var
		//TODO
		//print error
		//return
	}

	std::cout << ".org " << m_dataSegmentIndex << "\n";

	m_vartable[varname].m_address = m_dataSegmentIndex;
	m_vartable[varname].m_value = 0;
	m_vartable[varname].m_reg = Register::None;
	m_vartable[varname].m_size = VarSize::Char;
	m_vartable[varname].m_strorageLocation = StorageLocation::DataSegment;

	return m_dataSegmentIndex++;
}

std::optional<VarInfo> MemoryManager::getVarInfo(std::string varname)
{
	auto it = m_vartable.find(varname);

	//tabloda bu degisken kayitlimi?
	if (it != m_vartable.end())
	{
		//varsa [key,value] degeri yolla
		return it->second;
	}

	//yoksa bos optional gonder
	return std::nullopt;
}

std::optional<uint8_t> MemoryManager::getValue(std::string varname)
{
	auto it = m_vartable.find(varname);

	//tabloda bu degisken kayitlimi?
	if (it != m_vartable.end())
	{
		return it->second.m_value;
	}

	return std::nullopt;
}

void MemoryManager::setValue(std::string varname, uint8_t value)
{
	m_vartable[varname].m_value = value;
}

bool MemoryManager::allocRegister(Register regname)
{
	f_usableRegisters[static_cast<int>(regname)] = false;

	return false;
}

void MemoryManager::freeRegister(Register regname)
{
	f_usableRegisters[static_cast<int>(regname)] = true;
}

void MemoryManager::createCommand(uint8_t size)
{
	m_textSegmentIndex += size;
}
