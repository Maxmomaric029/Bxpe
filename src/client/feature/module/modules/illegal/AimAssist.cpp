#include "pch.h"
#include "AimAssist.h"
#include "sdk/minecraft.h"
#include "sdk/world.h"
#include "client/Latite.h"

AimAssist::AimAssist() : Module("AimAssist", L"Aim Assist", L"Smoothly aims at players", Category::ILLEGAL) {
    addSetting("aimAssist", L"Aim Assist", L"Enable smooth aiming", aim_assist);
    addSetting("targetRange", L"Target Range", L"Maximum distance for target", target_range);
    addSetting("aimFov", L"Aim FOV", L"Maximum FOV for target", aim_fov);
    addSetting("aimSpeed", L"Aim Speed", L"Speed of aiming", aim_speed);
    
    listen<UpdateEvent>(&AimAssist::onUpdate);
    listen<RenderOverlayEvent>(&AimAssist::onRender);
}

float AimAssist::wrapAngleTo180(float angle) {
    return 0.f;
}

float AimAssist::getAngleDifference(float a, float b) {
    return 0.f;
}

void AimAssist::onUpdate(Event& ev) {
}

void AimAssist::onRender(Event& ev) {
}

void AimAssist::onEnable() {}
void AimAssist::onDisable() {}
