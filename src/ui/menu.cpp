#include "pch.h"
#include "ui/menu.h"
#include "modules/module_manager.h"
#include "core/jvm_wrapper.h"
#include "config/mappings.h"

void Menu::TabItem(const char* label, int id) {
    bool selected = (s_selectedTab == id);
    ImVec2 size = ImVec2(100, 35);
    
    // Transparent background for tabs, only highlight text and underline
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1, 1, 1, 0.05f));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(1, 1, 1, 0.1f));
    
    if (s_boldFont) ImGui::PushFont(s_boldFont);
    if (ImGui::Button(label, size)) {
        s_selectedTab = id;
    }
    if (s_boldFont) ImGui::PopFont();
    
    if (selected) {
        ImVec2 pMin = ImGui::GetItemRectMin();
        ImVec2 pMax = ImGui::GetItemRectMax();
        // Modern accent underline
        ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(pMin.x + 10, pMax.y), ImVec2(pMax.x - 10, pMax.y + 2), IM_COL32(230, 230, 230, 255), 2.0f);
    }

    ImGui::PopStyleColor(3);
}

void Menu::CustomToggle(const char* label, bool* v) {
    if (s_boldFont) ImGui::PushFont(s_boldFont);
    ImGui::Text(label);
    if (s_boldFont) ImGui::PopFont();
    
    ImGui::SameLine(ImGui::GetWindowWidth() - 50);
    
    ImVec2 p = ImGui::GetCursorScreenPos();
    ImDrawList* draw_list = ImGui::GetWindowDrawList();

    float height = 20.0f;
    float width = 38.0f;
    float radius = height * 0.50f;

    if (ImGui::InvisibleButton(label, ImVec2(width, height)))
        *v = !*v;

    ImU32 col_bg;
    if (ImGui::IsItemHovered())
        col_bg = *v ? IM_COL32(110, 110, 110, 255) : IM_COL32(60, 60, 60, 255);
    else
        col_bg = *v ? IM_COL32(90, 90, 90, 255) : IM_COL32(40, 40, 40, 255);

    draw_list->AddRectFilled(p, ImVec2(p.x + width, p.y + height), col_bg, radius);
    draw_list->AddCircleFilled(ImVec2(p.x + radius + (*v ? (width - radius * 2.0f) : 0), p.y + radius), radius - 1.5f, IM_COL32(230, 230, 230, 255));
}

void Menu::CustomSlider(const char* label, float* v, float min, float max, const char* format) {
    if (s_boldFont) ImGui::PushFont(s_boldFont);
    ImGui::Text(label);
    if (s_boldFont) ImGui::PopFont();
    
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(4, 2));
    ImGui::SliderFloat((std::string("##") + label).c_str(), v, min, max, format);
    ImGui::PopStyleVar();
}

void Menu::applyTheme() {
    auto& io = ImGui::GetIO();
    if (s_boldFont == nullptr) {
        // Load system bold font
        s_boldFont = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\arialbd.ttf", 16.0f);
        if (s_boldFont == nullptr) {
             // Fallback to standard arial if bold isn't found for some reason
             s_boldFont = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\arial.ttf", 16.0f);
        }
    }

    auto& style = ImGui::GetStyle();
    
    // Rounded corners & padding
    style.WindowRounding    = 8.0f;
    style.FrameRounding     = 4.0f;
    style.PopupRounding     = 4.0f;
    style.ScrollbarRounding = 12.0f;
    style.GrabRounding      = 4.0f;
    style.TabRounding       = 4.0f;
    style.WindowBorderSize  = 1.0f;
    style.FrameBorderSize   = 1.0f;

    style.WindowPadding     = ImVec2(10, 10);
    style.FramePadding      = ImVec2(6, 4);
    style.ItemSpacing       = ImVec2(8, 8);

    ImVec4* colors = style.Colors;

    // Premium Silver / Black / Slate Palette
    colors[ImGuiCol_Text]                   = ImVec4(0.95f, 0.95f, 0.95f, 1.00f);
    colors[ImGuiCol_TextDisabled]           = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
    colors[ImGuiCol_WindowBg]               = ImVec4(0.06f, 0.06f, 0.06f, 1.00f);
    colors[ImGuiCol_ChildBg]                = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_PopupBg]                = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
    colors[ImGuiCol_Border]                 = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
    colors[ImGuiCol_BorderShadow]           = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);

    colors[ImGuiCol_FrameBg]                = ImVec4(0.12f, 0.12f, 0.12f, 1.00f);
    colors[ImGuiCol_FrameBgHovered]         = ImVec4(0.18f, 0.18f, 0.18f, 1.00f);
    colors[ImGuiCol_FrameBgActive]          = ImVec4(0.24f, 0.24f, 0.24f, 1.00f);

    colors[ImGuiCol_TitleBg]                = ImVec4(0.04f, 0.04f, 0.04f, 1.00f);
    colors[ImGuiCol_TitleBgActive]          = ImVec4(0.04f, 0.04f, 0.04f, 1.00f);
    colors[ImGuiCol_TitleBgCollapsed]       = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);

    colors[ImGuiCol_MenuBarBg]               = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
    colors[ImGuiCol_ScrollbarBg]            = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
    colors[ImGuiCol_ScrollbarGrab]          = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabHovered]   = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabActive]    = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);

    colors[ImGuiCol_CheckMark]              = ImVec4(0.80f, 0.80f, 0.80f, 1.00f);
    colors[ImGuiCol_SliderGrab]             = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
    colors[ImGuiCol_SliderGrabActive]       = ImVec4(0.80f, 0.80f, 0.80f, 1.00f);

    colors[ImGuiCol_Button]                 = ImVec4(0.15f, 0.15f, 0.15f, 1.00f);
    colors[ImGuiCol_ButtonHovered]          = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
    colors[ImGuiCol_ButtonActive]           = ImVec4(0.35f, 0.35f, 0.35f, 1.00f);

    colors[ImGuiCol_Header]                 = ImVec4(0.15f, 0.15f, 0.15f, 1.00f);
    colors[ImGuiCol_HeaderHovered]          = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
    colors[ImGuiCol_HeaderActive]           = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);

    colors[ImGuiCol_Separator]              = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
    colors[ImGuiCol_SeparatorHovered]       = ImVec4(0.30f, 0.30f, 0.30f, 0.78f);
    colors[ImGuiCol_SeparatorActive]        = ImVec4(0.40f, 0.40f, 0.40f, 1.00f);

    colors[ImGuiCol_ResizeGrip]             = ImVec4(0.26f, 0.59f, 0.98f, 0.00f);
    colors[ImGuiCol_ResizeGripHovered]      = ImVec4(0.26f, 0.59f, 0.98f, 0.00f);
    colors[ImGuiCol_ResizeGripActive]       = ImVec4(0.26f, 0.59f, 0.98f, 0.00f);

    colors[ImGuiCol_Tab]                    = ImVec4(0.08f, 0.08f, 0.08f, 1.00f);
    colors[ImGuiCol_TabHovered]             = ImVec4(0.18f, 0.18f, 0.18f, 1.00f);
    colors[ImGuiCol_TabActive]              = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
    colors[ImGuiCol_TabUnfocused]           = ImVec4(0.07f, 0.10f, 0.15f, 0.97f);
    colors[ImGuiCol_TabUnfocusedActive]     = ImVec4(0.14f, 0.26f, 0.42f, 1.00f);

    colors[ImGuiCol_PlotLines]              = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
    colors[ImGuiCol_PlotLinesHovered]       = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
    colors[ImGuiCol_PlotHistogram]          = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
    colors[ImGuiCol_PlotHistogramHovered]   = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
    colors[ImGuiCol_TextSelectedBg]         = ImVec4(0.40f, 0.40f, 0.40f, 0.35f);
    colors[ImGuiCol_DragDropTarget]         = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
    colors[ImGuiCol_NavHighlight]           = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    colors[ImGuiCol_NavWindowingHighlight]  = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
    colors[ImGuiCol_NavWindowingDimBg]      = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
    colors[ImGuiCol_ModalWindowDimBg]       = ImVec4(0.00f, 0.00f, 0.00f, 0.60f);
}

void Menu::render() {
    if (!s_visible) return;

    static bool themeApplied = false;
    if (!themeApplied) {
        applyTheme();
        themeApplied = true;
    }

    // Slightly wider window for horizontal layout
    ImGui::SetNextWindowSize(ImVec2(500, 450), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowPos(ImVec2(100, 100), ImGuiCond_FirstUseEver);

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(15, 10));
    ImGui::Begin("Bape Internal // Forge 1.21.1", &s_visible,
        ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar);
    ImGui::PopStyleVar();

    ImVec2 winPos = ImGui::GetWindowPos();
    ImVec2 winSize = ImGui::GetWindowSize();
    ImDrawList* drawList = ImGui::GetWindowDrawList();

    // ── Header/Title ──
    if (s_boldFont) ImGui::PushFont(s_boldFont);
    ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "B");
    ImGui::SameLine(0, 0);
    ImGui::TextColored(ImVec4(1.0f, 1.0f, 1.0f, 1.0f), "ape");
    ImGui::SameLine(0, 5);
    ImGui::TextDisabled("| Internal Ghost Client");
    if (s_boldFont) ImGui::PopFont();
    
    ImGui::SameLine(ImGui::GetWindowWidth() - 100);
    ImGui::TextDisabled("v2.6 PREM");
    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    // ── Navigation (Top Tabs) ──
    ImGui::BeginGroup();
    TabItem("COMBAT", 0); ImGui::SameLine();
    TabItem("MOVEMENT", 1); ImGui::SameLine();
    TabItem("VISUALS", 2); ImGui::SameLine();
    TabItem("UTILITY", 3);
    ImGui::EndGroup();
    
    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    // ── Content Area ──
    ImGui::BeginChild("ContentScroll", ImVec2(0, winSize.y - 120), false, ImGuiWindowFlags_NoScrollbar);
    
    auto editColor = [](const char* label, ImU32& color) {
        float col[4] = {
            (float)((color >> 0) & 0xFF) / 255.0f,
            (float)((color >> 8) & 0xFF) / 255.0f,
            (float)((color >> 16) & 0xFF) / 255.0f,
            (float)((color >> 24) & 0xFF) / 255.0f
        };
        ImGui::PushID(label);
        ImGui::Text(label);
        ImGui::SameLine(ImGui::GetWindowWidth() - 40);
        if (ImGui::ColorEdit4("##col", col, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoLabel)) {
            color = IM_COL32((int)(col[0] * 255.0f), (int)(col[1] * 255.0f), (int)(col[2] * 255.0f), (int)(col[3] * 255.0f));
        }
        ImGui::PopID();
    };

    if (s_selectedTab == 0) { // COMBAT
        if (s_boldFont) ImGui::PushFont(s_boldFont);
        ImGui::TextDisabled("COMBAT MODULES");
        if (s_boldFont) ImGui::PopFont();
        ImGui::Spacing();

        auto* reach = ModuleManager::getModule("Reach");
        if (reach) {
            bool enabled = reach->isEnabled();
            CustomToggle("Reach Extension", &enabled);
            reach->setEnabled(enabled);
            if (enabled) {
                ImGui::Indent();
                CustomSlider("Max Shot Distance", &reach->getFloatSetting("reach_distance"), 3.0f, 10.0f, "%.1f");
                ImGui::Unindent();
            }
        }

        ImGui::Spacing();
        auto* aim = ModuleManager::getModule("Aim Assist");
        if (aim) {
            bool enabled = aim->isEnabled();
            CustomToggle("Aimbot Assist", &enabled);
            aim->setEnabled(enabled);
            if (enabled) {
                ImGui::Indent();
                CustomToggle("Interpolation", &aim->getBoolSetting("aim_assist"));
                CustomSlider("FOV Radius", &aim->getFloatSetting("aim_fov"), 10.0f, 180.0f, "%.0f");
                CustomSlider("Smoothness", &aim->getFloatSetting("aim_speed"), 0.1f, 5.0f, "%.1f");
                ImGui::Spacing();
                CustomToggle("Triggerbot", &aim->getBoolSetting("triggerbot"));
                CustomToggle("AutoClicker", &aim->getBoolSetting("auto_clicker"));
                CustomSlider("CPS Max", &aim->getFloatSetting("cps"), 1.0f, 20.0f, "%.0f");
                ImGui::Unindent();
            }
        }
    }
    else if (s_selectedTab == 1) { // MOVEMENT
        if (s_boldFont) ImGui::PushFont(s_boldFont);
        ImGui::TextDisabled("PHYSICS MODULES");
        if (s_boldFont) ImGui::PopFont();
        ImGui::Spacing();

        auto* jesus = ModuleManager::getModule("Jesus");
        if (jesus) {
            bool enabled = jesus->isEnabled();
            CustomToggle("Water Walking", &enabled);
            jesus->setEnabled(enabled);
            if (enabled) {
                ImGui::Indent();
                CustomToggle("Solid Collision", &jesus->getBoolSetting("solid"));
                CustomSlider("Surface Bounce", &jesus->getFloatSetting("bounce"), 0.0f, 0.4f, "%.2f");
                ImGui::Unindent();
            }
        }
    }
    else if (s_selectedTab == 2) { // VISUALS
        if (s_boldFont) ImGui::PushFont(s_boldFont);
        ImGui::TextDisabled("VISUAL OVERLAYS");
        if (s_boldFont) ImGui::PopFont();
        ImGui::Spacing();

        auto* esp = ModuleManager::getModule("ESP");
        if (esp) {
            bool enabled = esp->isEnabled();
            CustomToggle("Master Overlay", &enabled);
            esp->setEnabled(enabled);
            if (enabled) {
                ImGui::Indent();
                CustomToggle("2D Bounding Boxes", &esp->getBoolSetting("draw_boxes"));
                CustomToggle("Render Names", &esp->getBoolSetting("draw_names"));
                CustomToggle("Health Bars", &esp->getBoolSetting("draw_health"));
                CustomToggle("Distance Info", &esp->getBoolSetting("draw_distance"));
                CustomToggle("Skeleton Chams", &esp->getBoolSetting("chams"));
                CustomToggle("Render Animals", &esp->getBoolSetting("draw_animals"));
                CustomToggle("Dropped Items", &esp->getBoolSetting("draw_items"));
                CustomToggle("Other Objects", &esp->getBoolSetting("draw_objects"));
                CustomSlider("Visual Range", &esp->getFloatSetting("max_distance"), 10.0f, 500.0f, "%.0fm");
                
                ImGui::Spacing();
                ImGui::Separator();
                ImGui::TextDisabled("Color Settings");
                editColor("Enemy Box Color", esp->getColorSetting("box_visible"));
                editColor("Label Text Color", esp->getColorSetting("text_color"));
                ImGui::Unindent();
            }
        }
    }
    else if (s_selectedTab == 3) { // UTILITY
        if (s_boldFont) ImGui::PushFont(s_boldFont);
        ImGui::TextDisabled("UTILITY TOOLS");
        if (s_boldFont) ImGui::PopFont();
        ImGui::Spacing();

        auto* xray = ModuleManager::getModule("X-Ray");
        if (xray) {
            bool enabled = xray->isEnabled();
            CustomToggle("X-Ray Scanner", &enabled);
            xray->setEnabled(enabled);
            if (enabled) {
                ImGui::Indent();
                ImGui::Columns(2, "XraySub", false);
                CustomToggle("Diamond", &xray->getBoolSetting("diamond"));
                CustomToggle("Iron", &xray->getBoolSetting("iron"));
                CustomToggle("Gold", &xray->getBoolSetting("gold"));
                CustomToggle("Emerald", &xray->getBoolSetting("emerald"));
                ImGui::NextColumn();
                CustomToggle("Coal", &xray->getBoolSetting("coal"));
                CustomToggle("Lapis", &xray->getBoolSetting("lapis"));
                CustomToggle("Redstone", &xray->getBoolSetting("redstone"));
                CustomToggle("Spawners", &xray->getBoolSetting("spawner"));
                ImGui::Columns(1);
                
                ImGui::Spacing();
                CustomSlider("Search Radius", &xray->getFloatSetting("radius"), 10.0f, 100.0f, "%.0f");
                CustomSlider("Tracer Thickness", &xray->getFloatSetting("thickness"), 1.0f, 5.0f, "%.1f");
                ImGui::Unindent();
            }
        }
    }

    ImGui::EndChild();

    // ── Footer ──
    ImGui::Separator();
    ImGui::Spacing();
    ImGui::TextColored(ImVec4(0.4f, 0.4f, 0.4f, 1.0f), "Build: Forge 1.21.1 | Developed by Antigravity");

    ImGui::End();
}
