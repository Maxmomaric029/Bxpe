#include "pch.h"
#include "SpeedDisplay.h"
#include "sdk/minecraft.h"
#include "client/event/Eventing.h"
#include "client/event/events/TickEvent.h"

SpeedDisplay::SpeedDisplay() : TextModule("SpeedDisplay", LocalizeString::get("client.textmodule.speedDisplay.name"),
                                          LocalizeString::get("client.textmodule.speedDisplay.desc"), HUD) {
    addSliderSetting("decimals", LocalizeString::get("client.textmodule.speedDisplay.decimals.name"),
                     LocalizeString::get("client.textmodule.speedDisplay.decimals.desc"), decimals, FloatValue(0.f),
                     FloatValue(10.f), FloatValue(1.f));
    addSetting("includeY", LocalizeString::get("client.textmodule.speedDisplay.includeY.name"),
               LocalizeString::get("client.textmodule.speedDisplay.includeY.desc"), includeY);

    this->suffix = TextValue(L" m/s");

    listen<TickEvent>(static_cast<EventListenerFunc>(&SpeedDisplay::onTick));
}

void SpeedDisplay::onTick(Event& evGeneric) {
	CLocalPlayer plr = CMinecraft::getLocalPlayer();
	if (!plr.isValid()) return;

	double x = plr.getX();
	double y = plr.getY();
	double z = plr.getZ();

	double px = plr.getPrevX();
	double py = plr.getPrevY();
	double pz = plr.getPrevZ();

	double dx = x - px;
	double dy = y - py;
	double dz = z - pz;

	if (!std::get<BoolValue>(this->includeY)) {
		dy = 0;
	}

	speed = std::sqrt(dx * dx + dy * dy + dz * dz) * 20.0;
}

std::wstringstream SpeedDisplay::text(bool isDefault, bool inEditor) {
	std::wstringstream wss;
	wss << std::fixed << std::setprecision(static_cast<std::streamsize>(std::get<FloatValue>(decimals))) << speed;
	return wss;
}
