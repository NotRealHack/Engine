#pragma once

#ifndef __MISC_ENGINE_H__
#define __MISC_ENGINE_H__

#include "../Core/Core.h"

class IClassEngineLoop {
public:
	virtual uint64_t Init() = 0;
	virtual void Tick() = 0;

	//Cleanup
	virtual void ClearPendingGCObjects() = 0;
};

#endif