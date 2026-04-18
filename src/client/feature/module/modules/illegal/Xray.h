#pragma once
#include "../../Module.h"

class Xray : public Module {
public:
	Xray();

    void onEnable() override;
    void onDisable() override;
};
