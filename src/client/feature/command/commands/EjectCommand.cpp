#include "pch.h"
#include "EjectCommand.h"
#include "client/Latite.h"
#include "client/misc/ClientMessageQueue.h"

EjectCommand::EjectCommand() : Command("eject", LocalizeString::get("client.commands.eject.desc"), "{0}") {
}

bool EjectCommand::execute([[maybe_unused]] std::string const label, [[maybe_unused]] std::vector<std::string> args) {
	message(LocalizeString::get("client.commands.eject.ejectMsg.name"));
	Latite::get().queueEject();
	return true;
}
