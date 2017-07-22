#pragma once

#ifndef __ENGINELAUNCH_ENGINELAUNCH_H__
#define __ENGINELAUNCH_ENGINELAUNCH_H__

#include "../Core/Core.h"
#include "../Misc/Engine.h"

class EngineService;
class PendingCleanupObjects;
class IClassSessionService;

class FClassEngineLoop : public IClassEngineLoop {
public:
	FClassEngineLoop();

public:
	int32_t PreInit(int32_t argc, char* argv[], const char* addCmd = NULL);
	int32_t PreInit(const char* cmd);

	//TODO: In order to uncomment this, implement module manager
	//void LoadPreInitModules();
	//bool LoadCoreModules();
	//bool LoadStartupCoreModules();
	//bool LoadStartupModules();

	virtual uint64_t Init() override;
	void InitTimer();
	void StopEngine(); //Do a shutdown
	bool ShouldUseIdleMode() const;
	virtual void Tick() override;
	virtual void ClearPendingGCObjects() override;
	static bool AppInit();
	static void AppPreExit();
	static void AppExit();

protected:
	
};

#endif