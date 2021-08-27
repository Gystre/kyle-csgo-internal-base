// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef PCH_H
#define PCH_H

// add headers that you want to pre-compile here
#include "framework.h"

#include <minwindef.h>
#include <Windows.h>
#include <iostream>
#include <thread>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>
#include <memory>
#include <deque>
#include <algorithm>
#include <Psapi.h>
#include <array>
#include <filesystem>
#include <winerror.h>
#include <KnownFolders.h>
#include <ShlObj_core.h>
#include <xmmintrin.h>
#include <pmmintrin.h>

#endif //PCH_H
