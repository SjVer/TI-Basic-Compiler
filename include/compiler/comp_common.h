#ifndef TI_COMP_COMMON_H
#define TI_COMP_COMMON_H

#include "common.h"
#include "chunk.h"
#include "scanner.h"

// name
#ifndef COMP_NAME
#define COMP_NAME "ticomp"
#endif

// version
#define COMP_VERSION "0.0.1"

// documentation
#define COMP_DOC COMP_NAME \
" -- A compiler for TI-Basic written by \
Sjoerd Vermeulen\v\
More info at https://github.com/SjVer/TI-Basic-Interpreter."

// 8xp format stuff
#define COMMENT (char [42]){"github.com/SjVer/TI-Basic-Interpreter"}
#define COMMENT_LEN 42

#endif // !TI_COMP_COMMON_H