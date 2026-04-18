#pragma once
#include "../../Module.h"
#include "client/event/events/UpdateEvent.h"

class Reach : public Module {
public:
	Reach();

	void onUpdate(Event& ev);
    void onDisable() override;

private:
    ValueType reach_distance = FloatValue(3.5f);
};
