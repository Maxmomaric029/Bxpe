#include "pch.h"
#include "MovablePaperdoll.h"
#include <mc/common/client/gui/ScreenView.h>
#include <mc/common/client/gui/controls/VisualTree.h>
#include <mc/common/client/gui/controls/UIControl.h>
#include <mc/common/client/renderer/HudPlayerRenderer.h>

MovablePaperdoll::MovablePaperdoll() : HUDModule("Paperdoll",
                                                 LocalizeString::get("client.hudmodule.movablePaperdoll.name"),
                                                 LocalizeString::get("client.hudmodule.movablePaperdoll.desc"), HUD) {
    addSetting("alwaysShow", LocalizeString::get("client.hudmodule.movablePaperdoll.alwaysShow.name"),
               LocalizeString::get("client.hudmodule.movablePaperdoll.alwaysShow.desc"), alwaysShow);

    listen<RenderLayerEvent>(static_cast<EventListenerFunc>(&MovablePaperdoll::onRenderLayer), true,
                             10 /*need to overpower the hud renderer*/);
}

void MovablePaperdoll::render([[maybe_unused]] DrawUtil& ctx, [[maybe_unused]] bool isDefault, [[maybe_unused]] bool inEditor) {
}

void MovablePaperdoll::onRenderLayer([[maybe_unused]] Event& evG) {
}
