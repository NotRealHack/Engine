#pragma once

//This is the header file for main.cpp (containing gameloading routines)

//Are our compiler settings right?
#include "Misc\CompilerCheck.h"

//Add the version info
#include "ProgramInfo.h"

#ifdef _MSC_VER
# include <Windows.h>
# include <windowsx.h>
# include <d3d9.h>
# include <d3d12.h>
# pragma comment (lib,"d3d9.lib")
# pragma comment (lib,"d3d12.lib")
//# include <WinSock2.h>
# pragma comment (lib,"ws2_32.lib")
# include <tchar.h>
# include <ImageHlp.h>
# pragma comment (lib,"ImageHlp.lib")
# include <wincrypt.h>
# pragma comment (lib,"advapi32.lib")
# include <stdlib.h>
# include <malloc.h>
# include <new.h>
#elif __GNUC__
# include <iostream>
# include <sys/socket.h>
# include <linux/if_packet.h>
# include <net/ethernet.h>
# include <linux/types.h>
# include <istream>
# include <ostream>
# include <fstream>
# include <cstring>
# include <linux/audit.h>
# include <linux/crc32.h>
# include <linux/memory.h>
# include <linux/netfilter.h>
#endif