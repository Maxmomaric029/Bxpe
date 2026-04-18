#include "pch.h"
#include "MovableCoordinates.h"
#include <mc/common/client/gui/ScreenView.h>
#include <mc/common/client/gui/controls/VisualTree.h>
#include <mc/common/client/gui/controls/UIControl.h>

MovableCoordinates::MovableCoordinates() : HUDModule("MovableCoordinates",
                                                     LocalizeString::get("client.hudmodule.movableCoordinates.name"),
                                                     LocalizeString::get("client.hudmodule.movableCoordinates.desc"),
                                                     HUD, 0, false) {
    listen<RenderLayerEvent>(static_cast<EventListenerFunc>(&MovableCoordinates::onRenderLayer), true,
                             10 /*need to overpower the hud renderer*/);
    addSetting("hideVanillaCoordinates",
               LocalizeString::get("client.hudmodule.movableCoordinates.hideVanillaCoordinates.name"), L"",
               this->hideVanillaCoordinates);
}

void MovableCoordinates::render(DrawUtil& ctx, bool isDefault, bool inEditor) {
}

void MovableCoordinates::onRenderLayer(Event& evG) {
}

void MovableCoordinates::updatePos() {
    vanillaCoordinates->getDescendants([](std::shared_ptr<SDK::UIControl> control) {
        control->updatePos();
    });
}
