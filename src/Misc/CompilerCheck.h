#pragma once

//This file MUST be included at least once in order to check our compilation environment!

#ifdef _MSC_VER
# ifdef _KERNEL_MODE
#  error "What are you doing here? A kernel mode game? I don't believe you :)"
# endif
# ifndef _CPPUNWIND
#  error "Exception Handling? What is that? And why do I need it? Lol"
# endif
# ifdef _DLL
#  error "This won't be a dll!"
# endif
# ifndef _WIN64
#  error "This is an Win64 Program!"
# endif
#elif __GNUC__
# ifdef __ELF__
#  error "This shall not be an ELF program!"
# endif
# ifdef __GNUC_GNU_INLINE__
#  warning "Handling inline functions in GNU90 standard can be painful..."
# endif
# ifndef __EXCEPTIONS
#  error "Exception handling? In an program? Why? Lol"
# endif
# ifndef __SSP__ || __SSP_ALL__ || __SSP_STRONG__ || __SSP_EXPLICIT__
#  error "Stack protecting? Never heard of that^^ (I WANT IT)"
# endif
#endif