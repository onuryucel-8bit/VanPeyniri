#include "Application.h"

Application::Application()
{  
    loadAsmFile();

    //islemci isaretcisini yolla
    m_mem_edit.UserData = &m_bus.m_cpu;

    //program sayacinin rengi
    m_mem_edit.HighlightColor = IM_COL32(100, 100, 0, 255);

    //mem_edit\e arka plan rengini ayarlayacak callback fonksiyonunu yolluyoruz 
    m_mem_edit.HighlightFn = [](const ImU8* data, size_t off, void* user_data) -> bool
    {
        mos6502* cpu = static_cast<mos6502*>(user_data);
        return (off == cpu->GetPC());
    };

    m_disassemblyTable[0xA5] = "LDA zero page";
    m_disassemblyTable[0xA9] = "LDA imm";
    m_disassemblyTable[0x8D] = "STA";
    m_disassemblyTable[0x4C] = "JMP";
    m_disassemblyTable[0xE6] = "INC zero page";
    m_disassemblyTable[0x40] = "RTI";

}   

Application::~Application()
{
    
}

void Application::drawRegisterRow(const char* name, uint8_t value)
{
    ImGui::TableNextRow();

    ImGui::TableSetColumnIndex(0);
    ImGui::Text("%s", name);

    ImGui::TableSetColumnIndex(1);
    ImGui::Text("0x%X", value);

    ImGui::TableSetColumnIndex(2);
    ImGui::Text("%u", value);
}

void Application::callAssembler()
{
    reproc::process process;

    std::array<std::string, 2> args;
    args[0] = "make";
    args[1] = "run";

    reproc::options options;
    options.working_directory = cmake_PROJECT_RES;

    reproc::arguments arguments(args);


    std::error_code err = process.start(arguments, options);

    if (err)
    {
        std::cout << "err.message()" << err.message() << "\n";
    }

    //TODO neden 5 saniye?
    using namespace std::chrono_literals;
    std::pair<int, std::error_code> status = process.wait(5s);
}

void Application::loadAsmFile()
{
    std::ifstream file(cmake_PROJECT_RES "output.bin", std::ios::binary);

    if (!file.is_open())
    {
        std::cout << "HATA:: Dosyanin konumu veya ismi yanlis...\n" << cmake_PROJECT_RES "output.bin" << "\n";
    }

    // get its size:
    std::streampos fileSize;

    file.seekg(0, std::ios::end);
    fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    file.read((char*)m_bus.m_RAM.get(), fileSize);    
}

void Application::run()
{     
    initSDL();
    initImgui();

    uint64_t cycleCount = 10;
    
    while (f_running)
    {
        inputs();

        update();

        //=============================================//
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        m_bus.m_gpu.run();
        m_bus.m_gpu.draw(renderer);

        drawImgui();
        draw();
        
        //swap buffers
        SDL_RenderPresent(renderer);
        //=============================================//

        if (f_runCpu || f_runCpuStep)
        {
            m_bus.m_cpu.Run(1, cycleCount);
            f_runCpuStep = false;
        }

       
    }
}

void Application::update()
{

}

void Application::draw()
{
    
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

    auto it = m_disassemblyTable.find(m_bus.m_RAM[m_bus.m_cpu.GetPC()]);

    //tabloda bu degisken kayitlimi?
    if (it != m_disassemblyTable.end())
    {
        ImGui::Text("pc => %s [%04X]", it->second.c_str(), m_bus.m_cpu.GetPC());
    }
    else
    {
        ImGui::Text("tanimsiz komut");
    }

    if (ImGui::Button("Derle DASM"))
    {
        callAssembler();
        loadAsmFile();
    }

    if (ImGui::Button("Sifirla"))
    {
        m_bus.m_cpu.Reset();
        m_bus.m_gpu.reset();
    }

    if (ImGui::Button("Durdur"))
    {
        f_runCpu = !f_runCpu;
    }

    if (ImGui::Button("Adim"))
    {
        f_runCpuStep = !f_runCpuStep;
        f_runCpu = false;
    }

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

        drawRegisterRow("PC", m_bus.m_cpu.GetPC());
        drawRegisterRow("flag", m_bus.m_cpu.GetP());
        drawRegisterRow("Sp", m_bus.m_cpu.GetS());

        drawRegisterRow("A", m_bus.m_cpu.GetA());
        drawRegisterRow("X", m_bus.m_cpu.GetX());
        drawRegisterRow("Y", m_bus.m_cpu.GetY());

        drawRegisterRow("IRQ", m_bus.m_cpu.getIRQ());

        //e(ekran) k(karti) 
        drawRegisterRow("ekx", m_bus.m_gpu.m_regPosx);
        drawRegisterRow("eky", m_bus.m_gpu.m_regPosy);
        drawRegisterRow("ekc", m_bus.m_gpu.m_regCommand);


        ImGui::EndTable();
    }
            
    //TODO DIKKAT lan bu sey hata vermiyor bos... isaretci gosteriyor 
    //eger boyle yazarsam (m_RAM.get()) m_RAM suan bus icinde
    m_mem_edit.DrawWindow("Memory Editor", m_bus.m_RAM.get(), 0xFFFF);

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

        if (event.type == SDL_EVENT_KEY_DOWN ||
            event.type == SDL_EVENT_KEY_UP)
        {        
            if (m_bus.m_keyboard.run(event))
            {                
                m_bus.m_cpu.IRQ(false);
            }
        }
    }
}

void Application::initImgui()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO* io = &ImGui::GetIO();

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