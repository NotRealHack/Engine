#include "EngineLaunch.h"

FClassEngineLoop GClassEngineLoop;
bool IsConsoleExecutable = false;
#ifdef _MSC_VER
HANDLE NamedMutex = NULL;
#else
void* NamedMutex = NULL;
#endif
bool EnableInnerException = true;

FClassEngineLoop::FClassEngineLoop() {

}

int32_t EnginePreInit(const char* cmd) {
	int32_t eLevel = GClassEngineLoop.PreInit(cmd);
	return eLevel;
}

int32_t EngineInit() {
	int32_t eLevel = GClassEngineLoop.Init();
	return eLevel;
}

void EngineTick() {
	GClassEngineLoop.Tick();
}

void EngineExit() {
	IsRequestedExit = true;
	GClassEngineLoop.Exit();
}

void LaunchStaticShutdownAsErrorReaction() {
	//Nothing yet
}

#ifdef _MSC_VER
int32_t GuardedMain(char* cmd, HINSTANCE hInst, HINSTANCE hPrInst, int32_t nCmdShow)
#else
int32_t GuardedMain(const char* cmd)
#endif
{
	struct GEngineLoopCleanupGuard {
		~EngineLoopCleanupGuard() {
			EngineExit();
		}
	} CleanupGuard;

	char* dmp;
#ifdef _MSC_VER
	wsprintf(dmp, "minidump-e%i_%s.dmp", FClassEngineVersion::Current().GetChangelist(), FClassDateTime::Now().ToString());
#else
	swprinf(dmp, sizeof(dmp) / sizeof(*buf), "minidump-e%i_%s.dmp", FClassEngineVersion::Current().GetChangeList(), FClassDateTime::Now().ToString());
#endif
	strcpy(MinidumpFilename, dmp);
	const char* origCmd = cmd;
	cmd = FClassCommandLine::RemoveExeName(origCmd);
	const char* cmdOccurence = strstr(origCmd, "-cmd");
	IsConsoleExecutable = cmdOccurence != NULL && cmdOccurence < cmd;

	int32_t eLvl = EnginePreInit(cmd);
	if (eLvl != 0 || IsRequestedExit) {
		return eLvl;
	}
	if (IsEditor) {
		eLvl = EditorInit(GClassEngineLoop);
	}
	else {
		eLvl = EngineInit();
	}

	while (!IsRequestedExit) {
		EngineTick();
	}

	if (IsEditor) {
		EditorExit();
	}
	return eLvl;
}

//Linux code
void LaunchLinux_FClassEngineLoop_AppExit() {
	return FClassEngineLoop::AppExit();
}

void ReleaseNamedMutex() {
	if (NamedMutex) {
#ifdef _MSC_VER
		ReleaseMutex(NamedMutex);
#else
		pthread_mutex_unlock(&NamedMutex);
#endif
		NamedMutex = NULL;
	}
}

bool MakeNamedMutex(const char* cmd) {
	bool isFirstInstance = false;
	char MutexName[128] = "";
	strcpy(MutexName, "NRHackEngine");
#ifdef _MSC_VER
	NamedMutex = CreateMutex(NULL, true, MutexName);
	if (NamedMutex && GetLastError() != ERROR_ALREADY_EXISTS) {
#else
	if (!pthread_mutex_init(&NamedMutex, NULL)) {
#endif
		if (FParse::Param(cmd, "NEVERFIRST")) {
			ReleaseNamedMutex();
			isFirstInstance = false;
		}
		else {
			isFirstInstance = true;
		}
	}
	return isFirstInstance;
}

void InvalidParameterHandler(const char* expr, const char* func, const char* file, uint32_t line, uint64_t reserved) {
	//Nothing... for now
}

void SetupEnvironment() {
#ifdef _MSC_VER
	_set_invalid_parameter_handler((_invalid_parameter_handler)InvalidParameterHandler);
#ifdef _DEBUG
	_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_DEBUG);
	_CrtSetDebugFillThreshold(0);
#endif
#else
	//Setting up the linux env? Maybe?
#endif
}

#ifdef _MSC_VER
int32_t GuardedMainWrapper(char* cmd, HINSTANCE hInst, HINSTANCE hPrInst, int32_t nCmdShow)
#else
int32_t GuardedMainWrapper(const char* cmd)
#endif
{
	int32_t eLvl = 0;
#ifdef _MSC_VER
	eLvl = GuardedMain(cmd, hInst, hPrInst, nCmdShow);
#else
	eLvl = GuardedMain(cmd);
#endif
	return eLvl;
}