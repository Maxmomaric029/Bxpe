#pragma once
#include "pch.h"
#include "core/jvm_wrapper.h"

class CItemStack {
public:
    explicit CItemStack(jobject obj) : m_obj(obj) {}
    CItemStack() : m_obj(nullptr) {}

    bool isValid() const { return m_obj != nullptr; }
    jobject getObject() const { return m_obj; }

    bool isEmpty() const;

    static bool initIDs();

private:
    jobject m_obj;
    static inline jclass    s_itemStackClass = nullptr;
    static inline jmethodID s_isEmpty        = nullptr;
};

class CPlayerInventory {
public:
    explicit CPlayerInventory(jobject obj) : m_obj(obj) {}
    CPlayerInventory() : m_obj(nullptr) {}

    bool isValid() const { return m_obj != nullptr; }
    jobject getObject() const { return m_obj; }

    CItemStack getArmorStack(int slot) const;

    static bool initIDs();

private:
    jobject m_obj;
    static inline jclass    s_inventoryClass = nullptr;
    static inline jmethodID s_getArmorStack  = nullptr;
};
