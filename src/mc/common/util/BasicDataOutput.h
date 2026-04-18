#pragma once
#define visual virtual

namespace SDK {
	// An implementation of Minecraft's IDataOutput.

	class BasicDataOutput {
	public:
		visual ~BasicDataOutput() {};
		std::string mStr;

		virtual void writeString([[maybe_unused]] void* gslStringSpan) {

		}
		virtual void writeLongString([[maybe_unused]] void* gslStringSpan) {

		}
		virtual void writeFloat([[maybe_unused]] float f) {

		}
		virtual void writeDouble([[maybe_unused]] long double d) {

		}
		virtual void writeByte([[maybe_unused]] char c) {

		}
		virtual void writeShort([[maybe_unused]] int16_t s) {

		}
		virtual void writeInt([[maybe_unused]] int i) {

		}
		virtual void writeLongLong([[maybe_unused]] int64_t o) {

		}
		virtual void writeBytes([[maybe_unused]] const void* bytes, [[maybe_unused]] uint64_t size) {

		}
		virtual bool isOk() {
			return true;
		}
	};
}