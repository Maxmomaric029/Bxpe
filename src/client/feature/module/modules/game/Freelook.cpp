#include "pch.h"
#include "Freelook.h"

Freelook::Freelook() : Module("Freelook", LocalizeString::get("client.module.freelook.name"), LocalizeString::get("client.module.freelook.desc"), GAME, 'F') {
	listen<UpdatePlayerCameraEvent>((EventListenerFunc)&Freelook::onCameraUpdate);
	listen<PerspectiveEvent>((EventListenerFunc)&Freelook::onPerspective);
}

void Freelook::onCameraUpdate(Event& evG) {
	auto& ev = reinterpret_cast<UpdatePlayerCameraEvent&>(evG);

	ev.setViewAngles(lastRot);
}

void Freelook::onPerspective(Event& evG) {
	auto& ev = reinterpret_cast<PerspectiveEvent&>(evG);
	ev.getView() = 1;
}

void Freelook::onEnable() {
	CLocalPlayer lp = CMinecraft::getLocalPlayer();
	if (lp.isValid()) {
		lastRot = { lp.getYaw(), lp.getPitch() };
	}
}

void Freelook::onDisable() {
}
