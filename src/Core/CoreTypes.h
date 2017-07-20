#pragma once

#ifndef __CORE_CORETYPES_H__
#define __CORE_CORETYPES_H__

#include <Windows.h>
#include "../Misc/compiler.h"

enum {
	INDEX_NONE = -1
};

enum {
	UNICODE_BOM = 0xfeff
};

enum EForceInit {
	ForceInit,
	ForceInitToZero
};

typedef INT32 FPlatformUserID;
const FPlatformUserID PLATFORMUSERID_NONE = INDEX_NONE;

#endif