#include "Application.h"

Application::Application()
    :cpu(Application::busRead, Application::busWrite)
{
    m_RAM[0] = 0xA9;
    m_RAM[1] = 0x05;
    m_RAM[2] = 0xA9;
    m_RAM[3] = 0x0F;
  
    cpu.Reset();
}

Application::~Application()
{
}

void Application::busWrite(uint16_t address, uint8_t data)
{
    m_RAM[address] = data;
}

uint8_t Application::busRead(uint16_t address)
{
    return m_RAM[address];
}

void Application::run()
{    
    initSDL();
    initImgui();

    uint64_t cycleCount = 10;

    //for (size_t i = 0; i < 20; i++)
    {
        cpu.Run(1, cycleCount);
    }

    while (f_running)
    {
        inputs();

        update();

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        drawImgui();
        draw();
        //swap buffers
        SDL_RenderPresent(renderer);

        
    }
}

void Application::update()
{

}


void Application::draw()
{
    SDL_FRect rect = { 100, 100, 32,32 };
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderFillRect(renderer, &rect);
}


void Application::drawImgui()
{
    ImGui_ImplSDLRenderer3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();
    //===================================================//
    //===================================================//
    //===================================================//

    ImGui::Begin("yazi");

    ImGui::Text("pc %x", cpu.GetPC());

    static ImGuiTableFlags flags = ImGuiTableFlags_SizingFixedFit
        | ImGuiTableFlags_RowBg
        | ImGuiTableFlags_Borders
        | ImGuiTableFlags_Resizable
        | ImGuiTableFlags_Reorderable
        | ImGuiTableFlags_Hideable;

    if (ImGui::BeginTable("table1", 3, flags))
    {
        //sutun isimleri
        ImGui::TableSetupColumn("Reg");
        ImGui::TableSetupColumn("Hex");
        ImGui::TableSetupColumn("Dec");

        //sonraki satira gec
        ImGui::TableHeadersRow();

        {
            //sonraki satira gec
            ImGui::TableNextRow();

            //sutun 0
            ImGui::TableSetColumnIndex(0);
            ImGui::Text("A");

            //sutun 1
            ImGui::TableSetColumnIndex(1);
            ImGui::Text("0x%02X", cpu.GetA());

            //sutun 2
            ImGui::TableSetColumnIndex(2);
            ImGui::Text("%u", cpu.GetA());
        }

        {
            //sonraki satira gec
            ImGui::TableNextRow();

            //sutun 0
            ImGui::TableSetColumnIndex(0);
            ImGui::Text("X");

            //sutun 1
            ImGui::TableSetColumnIndex(1);
            ImGui::Text("0x%02X", cpu.GetX());

            //sutun 2
            ImGui::TableSetColumnIndex(2);
            ImGui::Text("%u", cpu.GetX());
        }

        {
            //sonraki satira gec
            ImGui::TableNextRow();

            //sutun 0
            ImGui::TableSetColumnIndex(0);
            ImGui::Text("Y");

            //sutun 1
            ImGui::TableSetColumnIndex(1);
            ImGui::Text("0x%02X", cpu.GetY());

            //sutun 2
            ImGui::TableSetColumnIndex(2);
            ImGui::Text("%u", cpu.GetY());
        }

        ImGui::EndTable();
    }

    ImGui::End();


    //===================================================//
    //===================================================//
    //===================================================//

    ImGui::Render();
    ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), renderer);
}




void Application::inputs()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        ImGui_ImplSDL3_ProcessEvent(&event);

        if (event.type == SDL_EVENT_QUIT)
        {
            f_running = false;
        }

        switch (event.key.key)
        {
        case SDLK_ESCAPE:
            f_running = false;
            break;
        }
    }
}

void Application::initImgui()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    io = &ImGui::GetIO();

    // Enable Docking
    io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io->FontGlobalScale = 1;

    ImGui_ImplSDL3_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer3_Init(renderer);
}

void Application::initSDL()
{
    window = SDL_CreateWindow("TrabzonCaydanligi", WindowWidth, WindowHeight, NULL);

    if (window == nullptr)
    {
        std::cout << "HATA:: Pencere olusturulamadi\n";
        f_running = false;
    }

    renderer = SDL_CreateRenderer(window, NULL);

    if (renderer == nullptr)
    {
        std::cout << "HATA:: Renderer olusturulamadi\n";
        f_running = false;
    }

}
