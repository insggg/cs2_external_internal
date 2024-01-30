﻿#include "os-imgui_base.h"
#include "../../hacks/features/menu/font/fontarray.h"
#include "../../hacks/features/menu/font/iconsfontwwesome5.h"
#include "../../framework/resources/weaponicon.h"

namespace OSImGui
{
    bool OSImGui_Base::InitImGui(ID3D11Device* device, ID3D11DeviceContext* device_context)
    {
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        io.Fonts->AddFontDefault();
        (void)io;

        ImFontAtlas* fontAtlas = new ImFontAtlas();
        ImFontConfig arialConfig;
        arialConfig.FontDataOwnedByAtlas = false;
        ImFont* arialFont = fontAtlas->AddFontFromFileTTF("C:\\Windows\\Fonts\\tahoma.ttf", 14.0f, &arialConfig, io.Fonts->GetGlyphRangesDefault());
        
        ImFontConfig iconConfig;
        static const ImWchar iconRanges[] = { ICON_MIN_FA, ICON_MAX_16_FA, 0 };
        iconConfig.MergeMode = true;
        iconConfig.PixelSnapH = true;
        iconConfig.OversampleH = 3;
        iconConfig.OversampleV = 3;
        iconConfig.GlyphRanges = iconRanges;
        iconConfig.FontDataOwnedByAtlas = false;
        ImFont* iconFont = fontAtlas->AddFontFromMemoryTTF((void*)faData, sizeof(faData), 15.f, &iconConfig, iconRanges);

        ImFont* WeaponIconFont = fontAtlas->AddFontFromMemoryTTF((void*)cs_icon, sizeof(cs_icon), 25.0f);

        io.Fonts = fontAtlas;

        ImGui::StyleColorsDark();
        io.LogFilename = nullptr;

        if (!ImGui_ImplWin32_Init(Window.hWnd))
            throw OSException("ImGui_ImplWin32_Init() call failed.");
        if (!ImGui_ImplDX11_Init(device, device_context))
            throw OSException("ImGui_ImplDX11_Init() call failed.");

        return true;
    }

    void OSImGui_Base::CleanImGui()
    {
        ImGui_ImplDX11_Shutdown();
        ImGui_ImplWin32_Shutdown();
        ImGui::DestroyContext();

        g_Device.CleanupDeviceD3D();
        DestroyWindow(Window.hWnd);
        UnregisterClassA(Window.ClassName.c_str(), Window.hInstance);
    }

    std::wstring OSImGui_Base::StringToWstring(std::string& str)
    {
        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
        return converter.from_bytes(str);
    }
}