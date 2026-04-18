#include "pch.h"
#include <cmath>
#include "CustomCoordinates.h"

CustomCoordinates::CustomCoordinates() : TextModule("CustomCoordinates",
                                                    LocalizeString::get("client.textmodule.customCoordinates.name"),
                                                    LocalizeString::get("client.textmodule.customCoordinates.desc"),
                                                    HUD) {
    addSetting("showDimension", LocalizeString::get("client.textmodule.customCoordinates.showDimension.name"),
               LocalizeString::get("client.textmodule.customCoordinates.showDimension.desc"), this->showDimension);
}

std::wstringstream CustomCoordinates::text(bool isDefault, bool inEditor) {
    std::wstringstream wss;
    return wss;
}