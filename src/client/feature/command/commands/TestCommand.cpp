#include "pch.h"
#include "TestCommand.h"
#include "client/Latite.h"
#include "mc/common/client/gui/controls/UIControl.h"
#include "mc/common/client/gui/controls/VisualTree.h"
#include <mc/common/nbt/CompoundTag.h>

// static SDK::UIControl* bossbar = nullptr;

TestCommand::TestCommand() : Command("test", L"A command for testing", "$ [...]", {"tc"}) {
	Eventing::get().listen<RenderLayerEvent>(this, (EventListenerFunc)&TestCommand::onRenderLayer);
}

bool TestCommand::execute([[maybe_unused]] std::string const label, [[maybe_unused]] std::vector<std::string> args) {
#if 0
	auto lp = SDK::ClientInstance::get()->getLocalPlayer();
	if (!lp) return true;
	auto selec = lp->supplies->inventory->getItem(lp->supplies->selectedSlot);

	if (selec && selec->tag) {
		SDK::BasicPrintStream ps{};
		SDK::BasicDataOutput psx{};
		selec->tag->print("prefix", ps);
		selec->tag->write(psx);

		message(ps.mStr);
	}
#endif
	return true;
}

void TestCommand::onRenderLayer([[maybe_unused]] Event& evG) {
	//auto& ev = reinterpret_cast<RenderLayerEvent&>(evG);
	//if (!bossbar) bossbar = ev.getScreenView()->visualTree->rootControl->findFirstDescendantWithName("boss_health_grid");
}
