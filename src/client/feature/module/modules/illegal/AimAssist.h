#pragma once
#include "../../Module.h"
#include "client/event/events/UpdateEvent.h"

class AimAssist : public Module {
public:
	AimAssist();

	void onUpdate(Event& ev);
    void onEnable() override;
    void onDisable() override;

private:
	float getAngleDifference(float a, float b);
	float wrapAngleTo180(float angle);

	long long m_lastClickTime = 0;

    ValueType triggerbot = BoolValue(false);
    ValueType aim_assist = BoolValue(true);
    ValueType auto_clicker = BoolValue(false);

    ValueType target_range = FloatValue(4.0f);
    ValueType aim_fov = FloatValue(45.0f);
    ValueType aim_speed = FloatValue(2.0f);
    ValueType cps = FloatValue(12.0f);
};
