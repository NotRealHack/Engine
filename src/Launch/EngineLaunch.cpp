#include "EngineLaunch.h"

FClassEngineLoop GClassEngineLoop;
bool IsConsoleExecutable = false;

int stubbed_main(int argc, char** argv) {
	return 0;
}

int32_t EnginePreInit(const char* cmd) {
	int32_t eLevel = GClassEngineLoop.PreInit(cmd);
	return eLevel;
}