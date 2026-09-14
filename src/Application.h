#include <iostream>
#include <memory>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <chrono>
#include <array>

#include "SDL3/SDL.h"

#include "imgui.h"
#include "backends/imgui_impl_sdl3.h"
#include "backends/imgui_impl_sdlrenderer3.h"

#include "imgui_memory_editor.h"

#include "reproc++/reproc.hpp"

#include "mos6502/mos6502.h"

/*

sp = sp + 0x100


------------------ 0
	Zero Page
------------------ 0xFF

------------------ 0x100
	Yigin
------------------ 0x1FF


*/


class Application
{
public:
	Application();
	~Application();

	void run();
	
private:

	void initSDL();
	void initImgui();

	//========================================//
	void update();
	void inputs();
	void draw();
	void drawImgui();
	//========================================//

	void drawRegisterRow(const char* name, uint8_t value);

	static void busWrite(uint16_t address, uint8_t data);
	static uint8_t busRead(uint16_t address);

	void callAssembler();
	void loadAsmFile();

	//========================================//
	const int WindowWidth = 800;
	const int WindowHeight = 600;
	SDL_Window* window = nullptr;

	SDL_Renderer* renderer = nullptr;
	bool f_running = true;
	bool f_runCpu = true;

	mos6502 cpu;
	
	inline static std::unique_ptr<uint8_t[]> m_RAM = std::make_unique<uint8_t[]>(0x10000);;
};

