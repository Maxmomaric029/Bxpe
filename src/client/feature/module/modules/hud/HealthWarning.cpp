#include "pch.h"
#include "HealthWarning.h"
#include "client/event/events/RenderLayerEvent.h"
#include "mc/common/client/gui/controls/VisualTree.h"
#include "mc/common/client/gui/controls/UIControl.h"
#include "util/WorldToScreen.h"

HealthWarning::HealthWarning() : Module("HealthWarning", LocalizeString::get("client.hudmodule.healthWarning.name"), LocalizeString::get("client.hudmodule.healthWarning.desc"), HUD, nokeybind) {
	this->listen<RenderLayerEvent>(&HealthWarning::onRenderLayer);
	addSetting("vignetteColor", LocalizeString::get("client.hudmodule.healthWarning.vignetteColor.name"), L"", vignetteColor);
	addSliderSetting("healthPointThreshold", LocalizeString::get("client.hudmodule.healthWarning.healthPointThreshold.name"), L"", healthPointThreshold, FloatValue(1.f), FloatValue(19.f), FloatValue(.5f));
	addSliderSetting("vignetteFade", LocalizeString::get("client.hudmodule.healthWarning.vignetteFade.name"), L"", vignetteFade, FloatValue(0.f), FloatValue(1.f), FloatValue(.1f));
}


void HealthWarning::onRenderLayer(Event& evG) {
}
