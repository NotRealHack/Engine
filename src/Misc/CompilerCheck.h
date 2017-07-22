#pragma once

//This file MUST be included at least once

#ifdef _MSC_VER
# ifdef _KERNEL_MODE
#  error "What are you doing here? A kernel mode game? I don't believe that's neccesary lol"
# endif
# ifndef _CPPUNWIND
#  error
# endif
# ifdef _DLL
#  error
# endif
# ifndef __AVX2__
#  error
# endif
# ifndef _WIN64
#  error
# endif
#elif __GNUC__
# ifdef __ELF__
#  error
# endif
# ifdef __GNUC_GNU_INLINE__
#  warning
# endif
# ifndef __EXCEPTIONS
#  error
# endif
# ifndef __SSP__ || __SSP_ALL__ || __SSP_STRONG__ || __SSP_EXPLICIT__
#  error
# endif
#endif