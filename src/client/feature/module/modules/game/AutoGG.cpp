#include "pch.h"
#include "AutoGG.h"
#include <mc/common/network/packet/CommandRequestPacket.h>
#include "mc/common/network/MinecraftPackets.h"

AutoGG::AutoGG() : Module("AutoGG", LocalizeString::get("client.module.autoGG.name"),
                          LocalizeString::get("client.module.autoGG.desc"), GAME, nokeybind) {
    addSetting("useCustomMessage", LocalizeString::get("client.module.autoGG.useCustomMessage.name"),
               LocalizeString::get("client.module.autoGG.useCustomMessage.desc"), useCustomMessage);
    addSetting("customMessage", LocalizeString::get("client.module.autoGG.customMessage.name"),
               LocalizeString::get("client.module.autoGG.customMessage.desc"), customMessage, "useCustomMessage"_istrue);
    listen<ChatMessageEvent>(static_cast<EventListenerFunc>(&AutoGG::onText));
}

void AutoGG::onText(Event& evG) {
    ChatMessageEvent& ev = reinterpret_cast<ChatMessageEvent&>(evG);

    std::wstring chatMessage = util::StrToWStr(ev.getMessage());
    std::wstring hiveDetectMessage = L"\u00a7r\u00a7c\u00a7lGame OVER!";
    
    if (chatMessage.find(hiveDetectMessage) != std::string::npos) {
        std::string msg = "gg";
        if (std::get<BoolValue>(useCustomMessage)) {
            msg = util::WStrToStr(std::get<TextValue>(customMessage).str);
        }
        
        CLocalPlayer::sendMessage(msg);
    }
}
