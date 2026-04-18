#pragma once
#include <client/feature/module/TextModule.h>

class ComboCounter : public TextModule {
public:
	ComboCounter();
	virtual ~ComboCounter() {}

	std::wstringstream text(bool isDefault, bool inEditor) override;

	void onAttack(Event& ev);
	void onPacketReceive(Event& ev);
	void onTick(Event& ev);
private:
	[[maybe_unused]] int combo = 0;
	std::chrono::system_clock::time_point lastHurt{};
	[[maybe_unused]] uint64_t lastRuntimeId = 0;
	[[maybe_unused]] bool hasHit = false;
};