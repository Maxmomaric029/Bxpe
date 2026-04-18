#include "pch.h"
#include "sdk/options.h"
#include "config/mappings.h"

bool CKeyBinding::initIDs() {
    JNIEnv* env = JvmWrapper::getEnv();
    s_kbClass = JvmWrapper::findClass(Mappings::KeyBinding_Class);
    if (!s_kbClass) return false;

    s_isPressed = JvmWrapper::getMethodID(s_kbClass, Mappings::KB_isPressed, Mappings::KB_isPressed_Sig);
    return s_isPressed != nullptr;
}

bool CKeyBinding::isPressed() const {
    if (!m_obj || !s_isPressed) return false;
    return JvmWrapper::getEnv()->CallBooleanMethod(m_obj, s_isPressed) == JNI_TRUE;
}

bool CGameOptions::initIDs() {
    JNIEnv* env = JvmWrapper::getEnv();
    s_optionsClass = JvmWrapper::findClass(Mappings::Options_Class);
    if (!s_optionsClass) return false;

    s_keyForward = JvmWrapper::getFieldID(s_optionsClass, Mappings::Options_keyForward, Mappings::Options_KeySig);
    s_keyBack    = JvmWrapper::getFieldID(s_optionsClass, Mappings::Options_keyBack, Mappings::Options_KeySig);
    s_keyLeft    = JvmWrapper::getFieldID(s_optionsClass, Mappings::Options_keyLeft, Mappings::Options_KeySig);
    s_keyRight   = JvmWrapper::getFieldID(s_optionsClass, Mappings::Options_keyRight, Mappings::Options_KeySig);
    s_keyJump    = JvmWrapper::getFieldID(s_optionsClass, Mappings::Options_keyJump, Mappings::Options_KeySig);
    s_keySneak   = JvmWrapper::getFieldID(s_optionsClass, Mappings::Options_keySneak, Mappings::Options_KeySig);

    return s_keyForward && s_keyBack && s_keyLeft && s_keyRight && s_keyJump && s_keySneak;
}

CKeyBinding CGameOptions::getKeyForward() const {
    if (!m_obj || !s_keyForward) return CKeyBinding(nullptr);
    return CKeyBinding(JvmWrapper::getEnv()->GetObjectField(m_obj, s_keyForward));
}

CKeyBinding CGameOptions::getKeyBack() const {
    if (!m_obj || !s_keyBack) return CKeyBinding(nullptr);
    return CKeyBinding(JvmWrapper::getEnv()->GetObjectField(m_obj, s_keyBack));
}

CKeyBinding CGameOptions::getKeyLeft() const {
    if (!m_obj || !s_keyLeft) return CKeyBinding(nullptr);
    return CKeyBinding(JvmWrapper::getEnv()->GetObjectField(m_obj, s_keyLeft));
}

CKeyBinding CGameOptions::getKeyRight() const {
    if (!m_obj || !s_keyRight) return CKeyBinding(nullptr);
    return CKeyBinding(JvmWrapper::getEnv()->GetObjectField(m_obj, s_keyRight));
}

CKeyBinding CGameOptions::getKeyJump() const {
    if (!m_obj || !s_keyJump) return CKeyBinding(nullptr);
    return CKeyBinding(JvmWrapper::getEnv()->GetObjectField(m_obj, s_keyJump));
}

CKeyBinding CGameOptions::getKeySneak() const {
    if (!m_obj || !s_keySneak) return CKeyBinding(nullptr);
    return CKeyBinding(JvmWrapper::getEnv()->GetObjectField(m_obj, s_keySneak));
}
