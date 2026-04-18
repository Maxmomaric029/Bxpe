#include "pch.h"
#include "ESP.h"
#include "client/event/events/RenderOverlayEvent.h"
#include "render_jni/esp_renderer.h"
#include "sdk/minecraft.h"
#include "sdk/world.h"
#include "client/Latite.h"

ESP::ESP() : Module("ESP", L"ESP", L"Extra Sensory Perception", Category::ILLEGAL) {
    addSetting("drawBoxes", L"Draw Boxes", L"Draw 2D boxes around entities", draw_boxes);
    addSetting("drawNames", L"Draw Names", L"Draw names above entities", draw_names);
    addSetting("drawHealth", L"Draw Health", L"Draw health bars", draw_health);
    addSetting("drawDistance", L"Draw Distance", L"Draw distance to entities", draw_distance);
    addSetting("drawAnimals", L"Draw Animals", L"Show non-player entities", draw_animals);
    addSetting("maxDistance", L"Max Distance", L"Maximum distance to show ESP", max_distance);
    
    listen<RenderOverlayEvent>(&ESP::onRender);
}

void ESP::onRender([[maybe_unused]] Event& ev) {
}
