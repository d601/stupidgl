#pragma once

#include <limits.h>

// This fails on systems where GLint is not a signed int, but I don't currently
// care about those.
#define GLINT_MAX INT_MAX