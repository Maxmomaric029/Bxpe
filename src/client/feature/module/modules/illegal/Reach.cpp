#include "pch.h"
#include "Reach.h"
#include "sdk/minecraft.h"
#include "client/Latite.h"

Reach::Reach() : Module("Reach", "Increase attack distance", Category::ILLEGAL) {
    addSetting("Distance", &reach_distance);
    listen<UpdateEvent>(&Reach::onUpdate);
}

void Reach::onUpdate(Event& ev) {
    if (!isEnabled()) return;
    if (ev.getHash() != UpdateEvent::hash) return;

    // Reach in Java internal often involves hooking the entity interaction logic.
    // For now, this is a placeholder for the logic to be injected via dump.
}

void Reach::onDisable() {
}
