#pragma once

#ifndef __CORE_CORETYPES_H__
#define __CORE_CORETYPES_H__

#ifdef _MSC_VER
#include <Windows.h>
typedef UINT32 uint32_t;
typedef  INT32  int32_t;
typedef UINT64 uint64_t;
typedef  INT64  int64_t;
#elif __GNUC__
#include <linux/types.h>
#endif

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

typedef int32_t PUserID;

#endif