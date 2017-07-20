//This is the header file for main.cpp (containing the main() function for the main Engine executable responsiblestarting the game)

//Include our CompilerCheck.h first in order to prevent shit from happen!
#include "Misc/CompilerCheck.h"

//Include then our ProgramInfo.h for the Version number to show
#include "ProgramInfo.h"

//Include Windows libraries and Headers
#ifdef _MSC_VER
# include <Windows.h>
# include <Windowsx.h>
# include <d3d9.h>
//DirectX12?
# pragma comment (lib, "d3d9.lib")
# include <Winsock2.h>
# pragma comment (lib, "WS2_32.lib")
# include <tchar.h>
# include <Imagehlp.h>
# pragma comment (lib, "Imagehlp.lib")
# include <Wincrypt.h>
# pragma comment (lib, "advapi32.lib")
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
