#pragma once
#include "../../Module.h"
#include "client/event/events/RenderOverlayEvent.h"

class ESP : public Module {
public:
	ESP();

	void onRender(Event& ev);

private:
    ValueType draw_boxes = BoolValue(true);
    ValueType draw_names = BoolValue(true);
    ValueType draw_health = BoolValue(true);
    ValueType draw_distance = BoolValue(true);
    ValueType draw_animals = BoolValue(false);
    ValueType draw_chests = BoolValue(false);
    ValueType chams = BoolValue(false);
    ValueType max_distance = FloatValue(200.0f);
};
