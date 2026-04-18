#include "pch.h"
#include <iomanip>
#include <cmath>
#include "CustomCoordinates.h"
#include "sdk/minecraft.h"

CustomCoordinates::CustomCoordinates() : TextModule("CustomCoordinates",
                                                    LocalizeString::get("client.textmodule.customCoordinates.name"),
                                                    LocalizeString::get("client.textmodule.customCoordinates.desc"),
                                                    HUD) {
    addSetting("showDimension", LocalizeString::get("client.textmodule.customCoordinates.showDimension.name"),
               LocalizeString::get("client.textmodule.customCoordinates.showDimension.desc"), this->showDimension);
}

std::wstringstream CustomCoordinates::text(bool isDefault, bool inEditor) {
    std::wstringstream wss;
    if (inEditor) {
        wss << L"0, 0, 0";
        return wss;
    }

    CLocalPlayer lp = CMinecraft::getLocalPlayer();
    if (lp.isValid()) {
        wss << std::fixed << std::setprecision(1) 
            << lp.getX() << L", " << lp.getY() << L", " << lp.getZ();
    } else {
        wss << L"N/A";
    }

    return wss;
}