

//#include "gpudata.h" disable
#include "XHASH_Module.hpp"
//typedef int int128_t __attribute__((mode(TI)));
//typedef unsigned int uint128_t __attribute__((mode(TI)));
std::string ConsolePut(std::string data) {
    std::cout << data << std::endl;
    return "";
}
bool LoadTextureFromFile(const char* filename, GLuint* out_texture, int* out_width, int* out_height, unsigned char* imgBuffer) {
    int image_width = 0;
    int image_height = 0;
    unsigned char* image_data = stbi_load(filename, &image_width, &image_height, NULL, 4);
    *imgBuffer = *image_data;
    if (image_data == NULL)
        return false;

    GLuint image_texture;
    glGenTextures(1, &image_texture);
    glBindTexture(GL_TEXTURE_2D, image_texture);

    // Setup filtering parameters for display
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Upload pixels into texture
#if defined(GL_UNPACK_ROW_LENGTH) && !defined(__EMSCRIPTEN__)
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
#endif
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
    stbi_image_free(image_data);

    *out_texture = image_texture;
    *out_width = image_width;
    *out_height = image_height;

    glBindTexture(GL_TEXTURE_2D, 0);

    return true;
}//
void ResetDeviceWGL();
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

#pragma comment (lib , "Urlmon.lib")

#pragma once
namespace ImGui {
    bool Spinner(const char* label, float radius, int thickness, const ImU32& color) {
        ImGuiWindow* window = GetCurrentWindow();
        if (window->SkipItems)
            return false;

        ImGuiContext& g = *GImGui;
        const ImGuiStyle& style = g.Style;
        const ImGuiID id = window->GetID(label);

        ImVec2 pos = window->DC.CursorPos;
        ImVec2 size((radius) * 2, (radius + style.FramePadding.y) * 2);

        const ImRect bb(pos, ImVec2(pos.x + size.x, pos.y + size.y));
        ItemSize(bb, style.FramePadding.y);
        if (!ItemAdd(bb, id))
            return false;

        // Render
        window->DrawList->PathClear();

        int num_segments = 30;
        int start = abs(ImSin(g.Time * 1.8f) * (num_segments - 5));

        const float a_min = IM_PI * 2.0f * ((float)start) / (float)num_segments;
        const float a_max = IM_PI * 2.0f * ((float)num_segments - 3) / (float)num_segments;

        const ImVec2 centre = ImVec2(pos.x + radius, pos.y + radius + style.FramePadding.y);

        for (int i = 0; i < num_segments; i++) {
            const float a = a_min + ((float)i / (float)num_segments) * (a_max - a_min);
            window->DrawList->PathLineTo(ImVec2(centre.x + ImCos(a + g.Time * 8) * radius,
                centre.y + ImSin(a + g.Time * 8) * radius));
        }

        window->DrawList->PathStroke(color, false, thickness);
    }
}

class cpudata {
public:
    int64_t fcpu_data = GetProcessorSpeed();
    std::nano cpu_load;
    std::string fNUMANodes = std::to_string(dDataCPU(1));
    std::string fPhysNumberPackages = std::to_string(dDataCPU(2));
    std::string fCPUCores = std::to_string(dDataCPU(3));
    std::string fCPULogicalCores = std::to_string(dDataCPU(4));
    std::string fL3CacheSize = std::to_string(dDataCPU(5));
    std::string fL2CacheSize = std::to_string(dDataCPU(6));
    std::string fL1CacheSize = std::to_string(dDataCPU(7));
    std::string fL4CacheSize = std::to_string(dDataCPU(8));
    std::string fCPULoadPercent;
    std::string fCPUSpeed = std::to_string(fcpu_data) + " Mhz";
};
struct MemoryData {
    int64_t dwLenA = (fMemStatus(0));
    int64_t dwMemoryLoad = (fMemStatus(1));
    int64_t ullAvailExtendedVirtual = (fMemStatus(2));
    int64_t ullAvailPageFile = (fMemStatus(3));
    int64_t ullAvailPhys = (fMemStatus(4)) ;
    int64_t ullAvailVirtual = (fMemStatus(5)) ;
    int64_t ullTotalPageFile = (fMemStatus(6));
    int64_t ullTotalPhys = (fMemStatus(7));
    int64_t ullTotalVirtual = fMemStatus(8);
};


MemoryData mInfo;

cpudata *CPU = new cpudata;
//
std::string strArray;

//fA_int2str(sInfo.CommitLimit,&strArray);
//
//..

//
//
//
//static std::string fTime = (std::to_string(tInfo.Hour) + ":" + std::to_string(tInfo.Min) + ":" + std::to_string(tInfo.Sec));
// Data stored per platform window
struct WGL_WindowData { HDC hDC; };

// Data
static HGLRC            g_hRC;
static WGL_WindowData   g_MainWindow;
static int              g_Width;
static int              g_Height;
ImVec4 clear_color = ImVec4(0.01f, 0.01f, 0.02f, 0.80f);

// Forward declarations of helper functions
bool CreateDeviceWGL(HWND hWnd, WGL_WindowData* data);
void CleanupDeviceWGL(HWND hWnd, WGL_WindowData* data);

//
void ResetDeviceWGL();
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

int main(int, char** argv)
{
  

    ImGui_ImplWin32_EnableDpiAwareness();
    WNDCLASSEXW wc = { sizeof(wc), CS_OWNDC, WndProc, 0L, 0L, GetModuleHandle(nullptr), nullptr, nullptr, nullptr, nullptr, L"XHASH 0.5 OpenGL3.3", nullptr };
    ::RegisterClassExW(&wc);
    HWND hwnd = ::CreateWindowW(wc.lpszClassName, L"XHASH 0.5 OpenGL3.3", WS_OVERLAPPEDWINDOW | WS_EX_TOOLWINDOW | WS_EX_NOPARENTNOTIFY, 100, 80, 500, 300, nullptr, nullptr, wc.hInstance, nullptr);
    ::SetWindowLongA(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE) & ~WS_SIZEBOX);
    // Initialize OpenGL
   // AGPU->hwnd = hwnd;
    if (!CreateDeviceWGL(hwnd, &g_MainWindow))
    {
        CleanupDeviceWGL(hwnd, &g_MainWindow);
        ::DestroyWindow(hwnd);
        ::UnregisterClassW(wc.lpszClassName, wc.hInstance);
        return 1;
    }
    wglMakeCurrent(g_MainWindow.hDC, g_hRC);

    // Show the window
   // ::ShowWindow(hwnd, SW_SHOWDEFAULT);
    ::AnimateWindow(hwnd, 100, AW_BLEND);
    ::ShowWindow(GetConsoleWindow(), 2);
    ::UpdateWindow(hwnd);
    std::string fStrParam;
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;   // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;    // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    ImGui_ImplWin32_InitForOpenGL(hwnd);
    ImGui_ImplOpenGL3_Init();
    io.Fonts->AddFontFromFileTTF(".\\Bounded-Regular.ttf", 20.0f);//
    ImFont* font15 = io.Fonts->AddFontFromFileTTF(".\\Bounded-Regular.ttf", 15.0f);
    ImFont* font40 = io.Fonts->AddFontFromFileTTF(".\\Bounded-Regular.ttf", 40.0f);
    ImFont* font60 = io.Fonts->AddFontFromFileTTF(".\\Bounded-Regular.ttf", 60.0f);
    int CPUInfo[4] = { -1 };
    unsigned   nExIds, i = 0;
    char CPUBrandString[0x40];
    // Get the information associated with each extended ID.
    __cpuid(CPUInfo, 0x80000000);
    nExIds = CPUInfo[0];
    for (i = 0x80000000; i <= nExIds; ++i)
    {
        __cpuid(CPUInfo, i);
        // Interpret CPU brand string
        if (i == 0x80000002)
            memcpy(CPUBrandString, CPUInfo, sizeof(CPUInfo));
        else if (i == 0x80000003)
            memcpy(CPUBrandString + 16, CPUInfo, sizeof(CPUInfo));
        else if (i == 0x80000004)
            memcpy(CPUBrandString + 32, CPUInfo, sizeof(CPUInfo));
    }
    std::string dCPUBrandString = CPUBrandString;
    // Main loop
    bool main_logo = true;
    bool done = false;
    ImDrawListSplitter JEApp;
    while (!done)
    {
        // Poll and handle messages (inputs, window resize, etc.)
        // See the WndProc() function below for our to dispatch events to the Win32 backend.
        MSG msg;
        bool fB_loadFrame = false;
        while (::PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
        {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
            if (msg.message == WM_QUIT)
                exit(0);
            //  done = true;
            if (msg.message == WM_DESTROY)
                exit(0);
        }

        if (done)
            break;
        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        bool fJEFrame = true;
        char intBuffer;
        int64_t a = 555;
        intBuffer = (char)a;
        // std::cout << "[JE_ENGINE] Frame Cra" << std::endl;
        std::exception* d;

        //  std::cout << "ADDR:" << &d << "->" << d << std::endl;
        //  ImGui::Begin("\tJE x64_OpenGL3_SSE4.2 C++20",&fJEFrame, ImGuiWindowFlags_NoCollapse + ImGuiWindowFlags_NoTitleBar);  
              // Create a window called "Hello, world!" and append into it.
        //ImGui::SetWindowPos(ImVec2(6.0f, 19.0f));
        ImGui::SetWindowSize(ImVec2(500.0f, 300.0f));
        JEApp.ClearFreeMemory();
        ImGuiStyle& style = ImGui::GetStyle();
        style.Colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
        style.Colors[ImGuiCol_WindowBg] = ImVec4(0.01f, 0.01f, 0.02f, 0.80f);
        style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
        style.Colors[ImGuiCol_PopupBg] = ImVec4(0.05f, 0.05f, 0.10f, 0.85f);
        style.Colors[ImGuiCol_Border] = ImVec4(0.70f, 0.70f, 0.70f, 0.65f);
        style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        style.Colors[ImGuiCol_FrameBg] = ImVec4(0.00f, 0.00f, 0.01f, 1.00f);
        style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.90f, 0.80f, 0.80f, 0.40f);
        style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.90f, 0.65f, 0.65f, 0.45f);
        style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.08f, 0.08f, 0.08f, 0.80f);
        style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.01f, 0.01f, 0.02f, 0.80f);
        style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.20f, 0.25f, 0.30f, 0.60f);
        style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.55f, 0.53f, 0.55f, 0.51f);
        style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.56f, 0.56f, 0.56f, 1.00f);
        style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.56f, 0.56f, 0.56f, 0.91f);
        style.Colors[ImGuiCol_CheckMark] = ImVec4(0.90f, 0.90f, 0.90f, 0.83f);
        style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.70f, 0.70f, 0.70f, 0.62f);
        style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.30f, 0.30f, 0.30f, 0.84f);
        style.Colors[ImGuiCol_Button] = ImVec4(0.30f, 0.30f, 0.30f, 0.80f);
        style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.50f, 0.69f, 0.99f, 0.68f);
        style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.80f, 0.50f, 0.50f, 1.00f);
        style.Colors[ImGuiCol_Header] = ImVec4(0.30f, 0.69f, 1.00f, 0.53f);
        style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.44f, 0.61f, 0.86f, 1.00f);
        style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.38f, 0.62f, 0.83f, 1.00f);
        style.Colors[ImGuiCol_ResizeGrip] = ImVec4(1.00f, 1.00f, 1.00f, 0.85f);
        style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(1.00f, 1.00f, 1.00f, 0.60f);
        style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(1.00f, 1.00f, 1.00f, 0.90f);
        style.Colors[ImGuiCol_PlotLines] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
        style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
        style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
        style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
        style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.00f, 0.00f, 1.00f, 0.35f);
        style.WindowBorderSize = 1.0f;
        style.FrameBorderSize = 1.0f;
        ImGuiButtonFlags btn_flags = ImGuiButtonFlags_MouseButtonMask_;



        JEApp.ClearFreeMemory();
        if (XHASHA->b_vsync) {
            Sleep(13);
            // WriteConfigJE << "fJEVsync=true;" << std::endl;
        }
        else {
            Sleep(0);
            // WriteConfigJE << "fJEVsync=false;" << std::endl;

        }
        ImGui::Begin("XHASH", &XHASHA->fXHMainMenuBool, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
        XHASHA->XHASHWindowSize(490, 290);
        XHASHA->XHASHWindowPos(0, 0);
        if (XHASHA->fXHGenerateWindowBool) {
            XHASHA->XHASHCursorPos(220, 10);
           // ImGui::Spinner("load", 20, 2, ImGui::GetColorU32(ImVec4(ImVec4(0.40f, 0, 1.0f, 1.0f))));
            if (XHASHA->MethodHash == "sha256") {
                XHASHA->XHASHSha256Gen(XHASHA->fXHChars, &XHASHA->fXHASHOutGen);
            }
            else if (XHASHA->MethodHash == "xhash") {
                XHASHA->generate(XHASHA->fXMaxHashSize, &XHASHA->fXHGenerateWindowBool, &XHASHA->fXHASHOutGen);
            }
        }
        if (XHASHA->fXHASHAbout) {
            //https://github.com/System-Glitch/SHA256
            ImGui::Begin("XHASH::ABOUT", &XHASHA->fXHASHAbout);
            ImGui::PushFont(font15);//11ffdf
            ImGui::TextColored(XHASHA->RGBA2IV4(255, 0, 50, 255), "THANKS!!");
            ImGui::TextColored(XHASHA->RGBA2IV4(0, 255, 50, 255), "SHA - 256: https://github.com/System-Glitch/SHA256");
            ImGui::TextColored(XHASHA->RGBA2IV4(11, 255, 140, 255), "XHASH 0.5 (C++20)_windows_amd64 by HCPP");
            ImGui::PopFont();
            ImGui::End();
        }
        if (XHASHA->fXHSaveFileWindowBool) {
            ImGui::Begin("Save File", &XHASHA->fXHSaveFileWindowBool);
            ImGui::InputText("file", &XHASHA->strFileName); ImGui::SameLine(); if (ImGui::Button("OK")) {
                XHASHA->SaveFile(XHASHA->strFileName);
                XHASHA->fXHSaveFileWindowBool = false;
            }
            ImGui::End();
        }
        ImGui::Text(("XHASH:" + std::to_string(XHASHA->fXHASHOutGen.size())+"/"+std::to_string(XHASHA->fXMaxHashSize)).c_str());
        XHASHA->XHASHCursorPos(40, 30);
        ImGui::TextColored(XHASHA->RGBA2IV4(140,0,255,255), "XHASH - POWERFUL HASH GENERATOR");
        if (ImGui::Button("sha256")) {       
            XHASHA->MethodHash = "sha256";
        }
        ImGui::SameLine();
        if (ImGui::Button("Rand Hash")) {
            XHASHA->MethodHash = "xhash";
        }
        ImGui::PushItemWidth(200.0f);
        if (XHASHA->MethodHash != "sha256") {
            ImGui::Text("SYMBOLS TO GEN");
        }
        else {
            ImGui::Text("TEXT");
        }
        ImGui::InputText("c", &XHASHA->fXHChars, ImGuiInputTextFlags_CharsUppercase);
        ImGui::PopItemWidth();
            ImGui::PushItemWidth(130.0f);
            if (XHASHA->MethodHash != "sha256") {
            ImGui::Text("SIZE HASH");
            ImGui::InputInt("size", &XHASHA->fXMaxHashSize, 0);
        }  XHASHA->XHASHButton("GENERATE", &XHASHA->fXHGenerateWindowBool); ImGui::SameLine();
        ImGui::PopItemWidth();
        XHASHA->XHASHButton("SAVE .txt", &XHASHA->fXHSaveFileWindowBool); ImGui::SameLine(); if (ImGui::Button("ABOUT")) { XHASHA->fXHASHAbout = true; } ImGui::SameLine(); if (ImGui::Button("EXIT")) { exit(0); }
        ImGui::Text((XHASHA->strData).c_str());
         ImGui::End();
// Rendering
        ImGui::Render();
        glViewport(0, 0, 400, 800);
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Present
        ::SwapBuffers(g_MainWindow.hDC);

    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    CleanupDeviceWGL(hwnd, &g_MainWindow);
    wglDeleteContext(g_hRC);
    ::DestroyWindow(hwnd);
    ::UnregisterClassW(wc.lpszClassName, wc.hInstance);

    return 0;
}

// Helper functions
bool CreateDeviceWGL(HWND hWnd, WGL_WindowData* data)
{
    HDC hDc = ::GetDC(hWnd);
    PIXELFORMATDESCRIPTOR pfd = { 0 };
    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 32;

    const int pf = ::ChoosePixelFormat(hDc, &pfd);
    if (pf == 0)
        return false;
    if (::SetPixelFormat(hDc, pf, &pfd) == FALSE)
        return false;
    ::ReleaseDC(hWnd, hDc);

    data->hDC = ::GetDC(hWnd);
    if (!g_hRC)
        g_hRC = wglCreateContext(data->hDC);
    return true;
}

void CleanupDeviceWGL(HWND hWnd, WGL_WindowData* data)
{
    wglMakeCurrent(nullptr, nullptr);
    ::ReleaseDC(hWnd, data->hDC);
}

// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Win32 message handler
// You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
// - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
// - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
// Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg)
    {
    case WM_SIZE:
        if (wParam != SIZE_MINIMIZED)
        {
            g_Width = LOWORD(lParam);
            g_Height = HIWORD(lParam);
        }
        return 0;
    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
            return 0;
        break;
    case WM_DESTROY:
        exit(0);
        return 0;
    }
    return ::DefWindowProcW(hWnd, msg, wParam, lParam);
}
