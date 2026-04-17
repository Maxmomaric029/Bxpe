#include "pch.h"
#include "ui/menu.h"
#include "imgui/imgui.h"

int Menu::s_selectedTab = 0;
bool Menu::s_visible = true;

void Menu::render() {
    if (!s_visible) return;

    ImGui::SetNextWindowSize(ImVec2(550, 400), ImGuiCond_FirstUseEver);
    ImGui::Begin("Bape Internal", &s_visible, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);

    // Header con el nombre personalizado: B (Rojo) ape (Blanco)
    ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[0]); // Asumiendo fuente cargada
    ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "B");
    ImGui::SameLine(0, 0);
    ImGui::TextColored(ImVec4(1.0f, 1.0f, 1.0f, 1.0f), "ape");
    ImGui::SameLine();
    ImGui::TextDisabled(" | Internal Ghost Client");
    ImGui::Separator();

    // Tabs
    if (ImGui::Button("Combat", ImVec2(100, 30))) s_selectedTab = 0;
    ImGui::SameLine();
    if (ImGui::Button("Visuals", ImVec2(100, 30))) s_selectedTab = 1;
    ImGui::SameLine();
    if (ImGui::Button("Movement", ImVec2(100, 30))) s_selectedTab = 2;
    ImGui::SameLine();
    if (ImGui::Button("Misc", ImVec2(100, 30))) s_selectedTab = 3;

    ImGui::Separator();
    ImGui::BeginChild("Content", ImVec2(0, 0), true);

    if (s_selectedTab == 0) {
        ImGui::Text("Combat Modules");
        // Aquí irían los controles de AimAssist, etc.
    } else if (s_selectedTab == 1) {
        ImGui::Text("Visual Modules");
        // ESP, etc.
    }

    ImGui::EndChild();
    ImGui::End();
}
