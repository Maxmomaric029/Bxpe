#pragma once
#include "../../Module.h"
#include "client/event/events/UpdateEvent.h"

class Jesus : public Module {
public:
	Jesus();

	void onUpdate(Event& ev);
};
