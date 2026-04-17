#pragma once
#include "pch.h"
#include "modules/module.h"

class ESP : public Module {
public:
    ESP();
    virtual void onUpdate(JNIEnv* env) override {}
    virtual void onRender(ImDrawList* drawList) override;
};
