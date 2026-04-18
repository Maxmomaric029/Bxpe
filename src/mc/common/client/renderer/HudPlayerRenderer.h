#pragma once
namespace SDK {
	class HudPlayerRenderer {
		[[maybe_unused]] char pad_0000[16]; //0x0000
	public:
		float timeToClose; //0x0010
		float tick; //0x0014
	};
}