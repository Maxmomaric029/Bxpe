#include "pch.h"
#include "MovableBossbar.h"

#include <mc/common/client/gui/ScreenView.h>
#include <mc/common/client/gui/controls/VisualTree.h>
#include <mc/common/client/gui/controls/UIControl.h>


MovableBossbar::MovableBossbar() : HUDModule("MovableBossbar",
                                             LocalizeString::get("client.hudmodule.movableBossbar.name"),
                                             LocalizeString::get("client.hudmodule.movableBossbar.desc"), HUD, 0,
                                             false) {
	listen<RenderLayerEvent>((EventListenerFunc)&MovableBossbar::onRenderLayer, true, 10 /*need to overpower the hud renderer*/);
	addSetting("hideBossbar", LocalizeString::get("client.hudmodule.movableBossbar.hideBossbar.name"), L"",
               this->hideBossbar);
}

void MovableBossbar::render([[maybe_unused]] DrawUtil& ctx, [[maybe_unused]] bool isDefault, [[maybe_unused]] bool inEditor) {
}

void MovableBossbar::onRenderLayer([[maybe_unused]] Event& evG) {
}

void MovableBossbar::updatePos() {
	bossHealthGrid->getDescendants([](std::shared_ptr<SDK::UIControl> control) {
		control->updatePos();
		});
}
