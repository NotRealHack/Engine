#pragma once

#ifndef __CORE_COREDEFINES_H__
#define __CORE_COREDEFINES_H__

#define STUBBED(x)																				\
	do {																						\
		static bool WeHaveAlreadySeenThisStubbedSection = false;								\
		if (!WeHaveAlreadySeenThisStubbedSection) {												\
			WeHaveAlreadySeenThisStubbedSection = true;											\
			fprintf(stderr, "STUB: %s at %s:%d (%s)\n", x, __FILE__, __LINE__, __FUNCTION__);	\
		}																						\
	}

#define STANDALONE_SEEKFREE_SUFFIX TEXT("_SF")

#endif