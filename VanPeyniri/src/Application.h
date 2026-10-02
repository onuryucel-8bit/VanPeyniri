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


#include "Bus.h"

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

	void callAssembler();
	void loadAsmFile();

	//========================================//
	const int WindowWidth = 800;
	const int WindowHeight = 600;
	SDL_Window* window = nullptr;

	SDL_Renderer* renderer = nullptr;
	bool f_running = true;
	bool f_runCpu = true;
	bool f_runCpuStep = false;

	Bus m_bus;
	MemoryEditor m_mem_edit;
	
	std::unordered_map<uint8_t, std::string> m_disassemblyTable;
};

