#include "pch.h"
#include "ToggleSprintSneak.h"
#include "client/event/events/TickEvent.h"
#include "client/event/events/BeforeMoveEvent.h"
#include "client/event/events/AfterMoveEvent.h"
#include "mc/common/client/input/ClientInputHandler.h"

ToggleSprintSneak::ToggleSprintSneak() : TextModule("ToggleSprintSneak",
                                                    LocalizeString::get("client.textmodule.toggleSprintSneak.name"),
                                                    LocalizeString::get("client.textmodule.toggleSprintSneak.desc"),
                                                    GAMEHUD, 400.f, 0, true) {
    listen<TickEvent>(static_cast<EventListenerFunc>(&ToggleSprintSneak::onTick));
    listen<BeforeMoveEvent>(static_cast<EventListenerFunc>(&ToggleSprintSneak::beforeMove));
    listen<AfterMoveEvent>(static_cast<EventListenerFunc>(&ToggleSprintSneak::afterMove));
	listen<KeyUpdateEvent>(static_cast<EventListenerFunc>(&ToggleSprintSneak::onKey));

    addSetting("label", LocalizeString::get("client.textmodule.toggleSprintSneak.label.name"),
               LocalizeString::get("client.textmodule.toggleSprintSneak.label.desc"), label);
    addSetting("toggleSprint", LocalizeString::get("client.textmodule.toggleSprintSneak.toggleSprint.name"),
               LocalizeString::get("client.textmodule.toggleSprintSneak.toggleSprint.desc"), sprint);
    addSetting("alwaysSprint", LocalizeString::get("client.textmodule.toggleSprintSneak.alwaysSprint.name"),
               LocalizeString::get("client.textmodule.toggleSprintSneak.alwaysSprint.desc"), alwaysSprint,
               "toggleSprint"_istrue);


    //sprintMode.addEntry({ sprint_mode_normal, "Normal", "Lets the game handle the sprinting" });
    //sprintMode.addEntry({ sprint_mode_raw, "Raw", "Latite makes the player sprint" });
    //addEnumSetting("sprintMode", "Sprint Mode", "The method used by the client to sprint", sprintMode, "toggleSprint"_istrue);
    addSetting("toggleSneak", LocalizeString::get("client.textmodule.toggleSprintSneak.toggleSneak.name"),
               LocalizeString::get("client.textmodule.toggleSprintSneak.toggleSneak.desc"), sneak);
}


void ToggleSprintSneak::onTick(Event& evGeneric) {
}

void ToggleSprintSneak::beforeMove(Event& evGeneric) {
}

void ToggleSprintSneak::afterMove(Event& evGeneric) {
}

void ToggleSprintSneak::onKey(Event& evGeneric) {
}

std::wstringstream ToggleSprintSneak::text(bool isDefault, bool inEditor) {
	std::wstringstream wss;
	return wss;
}

bool ToggleSprintSneak::isActive() {
	return false;
}
