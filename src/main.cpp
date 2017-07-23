#include "main.h"
#include "Launch\EngineLaunch.h"

bool ShouldPauseBeforeExit;

int32_t main(int argc, char* argv[]) {
	return CommonMain(argc, argv, &GuardedMain);
}

#ifdef _MSC_VER
int32_t __stdcall WinMain(_In_ HINSTANCE hInInstance, _In_opt_ HINSTANCE hPrInstance, _In_ char*, _In_ int32_t nCmdShow)
#else
int32_t WinMain()
#endif
{
#ifndef _MSC_VER
	return 0;
#else
	SetupEnvironment();
	int32_t eLvl = 0;
	hInstance = hInInstance;
	const char* cmd = ::GetCommandLine();
#ifdef _DEBUG
	if (true && !AlwaysReportCrash)
#else
	if (IsDebuggerPresent() && !AlwaysReportCrash)
#endif
	{
		eLvl = GuardedMain((char*)cmd, hInInstance, hPrInstance, nCmdShow);
	}
	else {
		IsGuarded = 1;
		eLvl = GuardedMainWrapper((char*)cmd, hInInstance, hPrInstance, nCmdShow);
		IsGuarded = 0;
	}
	FClassEngineLoop::AppExit();

	if (ShouldPauseBeforeExit) {
		Sleep(INFINITE);
	}
	return eLvl;
}