#pragma once
#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_win32.h"
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#include <tchar.h>
#include <string>
//#include "JoyStick.h"
#include <iostream>
#include <conio.h>
#include <fstream>
#include <Psapi.h>
#include <urlmon.h>
#include "dSys.h"
#include <clocale>
#include <thread>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "cpudata.h"
#include "imgui_internal.h"
#include <gl/GL.h>
#include <stdint.h>
#include "imgui_stdlib.h"
#include <cstdlib>
#include <ctime>

// data

class XHASH {
public:
	bool  b_vsync = true;
    uint64_t generate(uint64_t fXHSize, bool* stopGen, std::string* outHasBuf);
    uint64_t XHASHWindowSize(uint64_t x, uint64_t y);
    uint64_t XHASHWindowPos(uint64_t x, uint64_t y);
    uint64_t XHASHCursorPos(uint64_t x, uint64_t y);
    int fXMaxHashSize = 0;
    std::string strData;
    std::string fXHASHOutGen;
    std::string strFileName;
    std::string fXHChars;
    bool XHASHButton(const char* name, bool* state);
    ImVec4 RGBA2IV4(float rx, float gx, float bx, float ax);
    bool SaveFile(std::string filename);
    bool log(std::string data);
	//
	bool  fXHMainMenuBool = true;
	bool  fXHGenerateWindowBool = false;
    bool  fXHSaveFileWindowBool = false;

};
bool XHASH::SaveFile(std::string filename) {
    std::ofstream filetxt((filename).c_str());
    filetxt.is_open();
    filetxt << XHASH::fXHASHOutGen << std::endl;
    filetxt.close();
    return 1;
    XHASH::log(filename + ": Saved!");
}
bool  XHASH::log(std::string data) {
    XHASH::strData = data;
}
uint64_t XHASH::generate(uint64_t fXHSize, bool* stopGen, std::string *outHasBuf) {
  //  XHASH::b_vsync = false;
    std::srand(std::time(0));
    uint64_t fXHMaxLen = fXHSize;
    uint64_t fXHStrSizeOffset = 0;
    uint64_t section = 0;
    uint64_t strSizeBuffer = XHASH::fXHChars.size();
    uint64_t xrandOffset = 0;
    std::string fXHstrBufferIn;
    std::string fXHStrOut;
    if (XHASH::fXHChars.size() < 1) {
        XHASH::log("Error: Chars not Setup");
        XHASH::fXHGenerateWindowBool = false;
    }
    else {
        for (uint64_t ds0 = 0; ds0 < fXHMaxLen; ds0++) {
            fXHstrBufferIn += XHASH::fXHChars[rand() % XHASH::fXHChars.size()];
            std::cout << "seed" << time(NULL) << "->" << rand() % XHASH::fXHChars.size() << std::endl;
            if (ds0 >= fXHSize) {
                break;
                //XHASH::b_vsync = true;
            }
        }
        *outHasBuf = fXHstrBufferIn;
        XHASH::fXHGenerateWindowBool = false;
    }
    return 1;
}
ImVec4 XHASH::RGBA2IV4(float rx, float gx, float bx, float ax) {
    float r_ = rx / 255;
    float g_ = gx / 255;
    float b_ = bx / 255;
    float a_ = ax / 255;
    return ImVec4(r_, g_, b_, a_);
}
uint64_t XHASH::XHASHWindowSize(uint64_t x, uint64_t y) {
    ImGui::SetWindowSize(ImVec2(x, y));
    return 0;
}
uint64_t XHASH::XHASHWindowPos(uint64_t x, uint64_t y) {
    ImGui::SetWindowPos(ImVec2(x, y));
    return 0;
}
uint64_t XHASH::XHASHCursorPos(uint64_t x, uint64_t y) {
    ImGui::SetCursorPos(ImVec2(x, y));
    return 0;
}
bool XHASH::XHASHButton(const char* name, bool *stateA) {
    if (ImGui::Button(name)) {
        *stateA = true;
    }
    //*stateA = fXb;
    return 0;
}
XHASH* XHASHA = new XHASH();
