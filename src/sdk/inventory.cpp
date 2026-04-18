#include "pch.h"
#include "sdk/inventory.h"
#include "config/mappings.h"

bool CItemStack::initIDs() {
    JNIEnv* env = JvmWrapper::getEnv();
    s_itemStackClass = JvmWrapper::findClass(Mappings::ItemStack_Class);
    if (!s_itemStackClass) return false;

    s_isEmpty = JvmWrapper::getMethodID(s_itemStackClass, Mappings::ItemStack_isEmpty, Mappings::ItemStack_isEmpty_Sig);
    return s_isEmpty != nullptr;
}

bool CItemStack::isEmpty() const {
    if (!m_obj || !s_isEmpty) return true;
    return JvmWrapper::getEnv()->CallBooleanMethod(m_obj, s_isEmpty) == JNI_TRUE;
}

bool CPlayerInventory::initIDs() {
    JNIEnv* env = JvmWrapper::getEnv();
    s_inventoryClass = JvmWrapper::findClass(Mappings::PlayerInventory_Class);
    if (!s_inventoryClass) return false;

    s_getArmorStack = JvmWrapper::getMethodID(s_inventoryClass, Mappings::PlayerInventory_getArmorStack, Mappings::PlayerInventory_getArmorStack_Sig);
    return s_getArmorStack != nullptr;
}

CItemStack CPlayerInventory::getArmorStack(int slot) const {
    if (!m_obj || !s_getArmorStack) return CItemStack(nullptr);
    jobject stack = JvmWrapper::getEnv()->CallObjectMethod(m_obj, s_getArmorStack, slot);
    return CItemStack(stack);
}
