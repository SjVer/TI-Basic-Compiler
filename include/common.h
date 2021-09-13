#ifndef TI_COMMON_H
#define TI_COMMON_H

// global includes
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

#include "tools.h"

// OS name
#ifdef _WIN32
#define OS "Windows 32-bit"
#elif _WIN64
#define OS "Windows 64-bit"
#elif __APPLE__ || __MACH__
#define OS "Mac OSX"
#elif __linux__
#define OS "Linux"
#elif __FreeBSD__
#define OS "FreeBSD"
#elif __unix || __unix__
#define OS "Unix"
#else
#define OS "Other"
#endif

// email
#define EMAIL "sjoerd@marsenaar.com"

// compiled file extension
#define BINARY_EXTENSION "8xp"

#endif // !TI_COMMON_H