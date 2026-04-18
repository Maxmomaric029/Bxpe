#pragma once
#include "pch.h"
#include "core/jvm_wrapper.h"

class CKeyBinding {
public:
    explicit CKeyBinding(jobject obj) : m_obj(obj) {}
    CKeyBinding() : m_obj(nullptr) {}

    bool isValid() const { return m_obj != nullptr; }
    jobject getObject() const { return m_obj; }

    bool isPressed() const;

    static bool initIDs();

private:
    jobject m_obj;
    static inline jclass    s_kbClass     = nullptr;
    static inline jmethodID s_isPressed   = nullptr;
};

class CGameOptions {
public:
    explicit CGameOptions(jobject obj) : m_obj(obj) {}
    CGameOptions() : m_obj(nullptr) {}

    bool isValid() const { return m_obj != nullptr; }
    jobject getObject() const { return m_obj; }

    CKeyBinding getKeyForward() const;
    CKeyBinding getKeyBack() const;
    CKeyBinding getKeyLeft() const;
    CKeyBinding getKeyRight() const;
    CKeyBinding getKeyJump() const;
    CKeyBinding getKeySneak() const;

    static bool initIDs();

private:
    jobject m_obj;
    static inline jclass    s_optionsClass = nullptr;
    static inline jfieldID  s_keyForward   = nullptr;
    static inline jfieldID  s_keyBack      = nullptr;
    static inline jfieldID  s_keyLeft      = nullptr;
    static inline jfieldID  s_keyRight     = nullptr;
    static inline jfieldID  s_keyJump      = nullptr;
    static inline jfieldID  s_keySneak     = nullptr;
};
