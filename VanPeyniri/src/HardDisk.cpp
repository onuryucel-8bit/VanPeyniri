#include "HardDisk.h"

HardDisk::HardDisk()
{
}

HardDisk::~HardDisk()
{
}

void HardDisk::run(std::unique_ptr<uint8_t[]>& ram)
{
    if (m_regHControl == 0)
    {
        return;
    }

    switch (m_regHControl)
    {    
    //r
    case 1:
        read(ram);
        break;
    //w
    case 2:
        write(ram);
        break;
    }

    m_regHControl = 0;
}

void HardDisk::write(std::unique_ptr<uint8_t[]>& ram)
{
    std::fstream file(cmake_PROJECT_RES "hdd0.bin", std::ios::in | std::ios::out | std::ios::binary);

    if (!file.is_open())
    {
        std::cout << "HATA:: Dosyanin konumu veya ismi yanlis...\n" << cmake_PROJECT_RES "hdd0.bin" << "\n";
    }

    //nereye yazilacak
    uint32_t hdd_adr =
        (m_regHadres3 << 24)
        | (m_regHadres2 << 16)
        | (m_regHadres1 << 8)
        | (m_regHadres0);

    //verinin baslangic adresi
    uint16_t ram_adr =
        (m_regHRAMadres1 << 8)
        | m_regHRAMadres0;

    //imleci kaydir
    file.seekp(hdd_adr, std::ios::beg);

    //reghsize veri boyutu ram[ram_adr] => hdd[hdd_adr]
    file.write(reinterpret_cast<const char*>(&ram[ram_adr]), m_regHSize);

    file.close();
}

void HardDisk::read(std::unique_ptr<uint8_t[]>& ram)
{
    std::fstream file(cmake_PROJECT_RES "hdd0.bin", std::ios::in | std::ios::out | std::ios::binary);

    if (!file.is_open())
    {
        std::cout << "HATA:: Dosyanin konumu veya ismi yanlis...\n" << cmake_PROJECT_RES "hdd0.bin" << "\n";
    }

    //nereden okunacak
    uint32_t hdd_adr =
        (m_regHadres3 << 24)
        | (m_regHadres2 << 16)
        | (m_regHadres1 << 8)
        | (m_regHadres0);

    //verinin koyulacagi yer
    uint16_t ram_adr =
        (m_regHRAMadres1 << 8)
        | m_regHRAMadres0;

    //imleci kaydir
    file.seekp(hdd_adr, std::ios::beg);

    //reghsize veri boyutu hdd[hdd_adr] => ram[ram_adr]    
    file.read(reinterpret_cast<char*>(&ram[ram_adr]), m_regHSize);

    file.close();
}
