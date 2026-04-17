#include "pch.h"
#include "modules/module_manager.h"
#include "modules/render/esp.h"
#include "modules/combat/aimassist.h"
#include "sdk/minecraft.h"
#include "sdk/entity.h"
#include "sdk/world.h"

// Note: Reach, Jesus and Xray are optional. We focus on Bape's core for now.

void ModuleManager::init() {
    // ── Init SDK IDs ────────────────────────────────────────────────
    if (!CMinecraft::initIDs()) {
        printf("[Bape] WARNING: Minecraft SDK init failed\n");
    }

    if (!CEntity::initIDs()) {
        printf("[Bape] WARNING: Entity SDK init failed\n");
    }

    if (!CWorld::initIDs()) {
        printf("[Bape] WARNING: World SDK init failed\n");
    }

    // ── Register modules ────────────────────────────────────────────
    auto reg = [&](std::unique_ptr<Module> mod) {
        s_modules.push_back(std::move(mod));
    };

    reg(std::make_unique<ESP>());
    reg(std::make_unique<AimAssist>());

    printf("[Bape] %zu modules registered successfully\n", s_modules.size());
}

void ModuleManager::shutdown() {
    for (auto& mod : s_modules) {
        if (mod->isEnabled()) {
            mod->setEnabled(false);
        }
    }
    s_modules.clear();
}

void ModuleManager::tickAll(JNIEnv* env) {
    for (auto& mod : s_modules) {
        if (mod->isEnabled()) {
            mod->onUpdate(env);
        }
    }
}

void ModuleManager::renderAll() {
    for (auto& mod : s_modules) {
        if (mod->isEnabled()) {
            mod->onRender(ImGui::GetBackgroundDrawList());
        }
    }
}

void ModuleManager::handleKey(int vk) {
    for (auto& mod : s_modules) {
        if (mod->getKeyBind() == vk) {
            mod->toggle();
        }
    }
}

Module* ModuleManager::getModule(const std::string& name) {
    for (auto& mod : s_modules) {
        if (mod->getName() == name) {
            return mod.get();
        }
    }
    return nullptr;
}
