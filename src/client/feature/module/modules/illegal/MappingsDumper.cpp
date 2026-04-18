#include "pch.h"
#include "MappingsDumper.h"
#include "core/jvm_wrapper.h"
#include "client/Latite.h"

MappingsDumper::MappingsDumper() : Module("MappingsDumper", "Dumps Java classes/methods", Category::ILLEGAL) {}

void MappingsDumper::onEnable() {
    printf("[Ghost] --- Starting Full Class Dump ---\n");
    JvmWrapper::dumpAllClasses();
    printf("[Ghost] --- Dump Complete. Check console/logs ---\n");
    
    // Auto-disable
    setEnabled(false);
}
