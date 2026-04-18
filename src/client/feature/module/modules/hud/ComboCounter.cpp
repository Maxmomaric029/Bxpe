#include "pch.h"
#include "ComboCounter.h"
#include <mc/common/network/packet/ActorEventPacket.h>

ComboCounter::ComboCounter() : TextModule("ComboCounter", LocalizeString::get("client.textmodule.comboCounter.name"),
                                          LocalizeString::get("client.textmodule.comboCounter.desc"), HUD) {
    prefix = TextValue(LocalizeString::get("client.textmodule.comboCounter.count.name"));

    listen<AttackEvent>((EventListenerFunc)&ComboCounter::onAttack);
    listen<PacketReceiveEvent>((EventListenerFunc)&ComboCounter::onPacketReceive);
    listen<TickEvent>((EventListenerFunc)&ComboCounter::onTick);
}

std::wstringstream ComboCounter::text(bool isDefault, bool inEditor) {
    return std::wstringstream();
}

void ComboCounter::onAttack(Event& evG) {
}

void ComboCounter::onPacketReceive(Event& evG) {
}

void ComboCounter::onTick(Event&) {
}
