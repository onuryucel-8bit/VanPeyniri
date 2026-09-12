#include <iostream>
#include <memory>

#include "SDL3/SDL.h"

#include "imgui.h"
#include "backends/imgui_impl_sdl3.h"
#include "backends/imgui_impl_sdlrenderer3.h"

#include "mos6502/mos6502.h"

class Application
{
public:
	Application();
	~Application();

	void run();
	
private:

	void initSDL();
	void initImgui();

	void update();
	void inputs();
	void draw();
	void drawImgui();


	static void busWrite(uint16_t address, uint8_t data);
	static uint8_t busRead(uint16_t address);

	const int WindowWidth = 800;
	const int WindowHeight = 600;
	SDL_Window* window = nullptr;

	SDL_Renderer* renderer = nullptr;
	bool f_running = true;

	ImGuiIO* io;

	mos6502 cpu;
	
	inline static std::unique_ptr<uint8_t[]> m_RAM = std::make_unique<uint8_t[]>(0x10000);;
};

