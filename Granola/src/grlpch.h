// Granola - Granola - grlpch.h
// Created: 2023.05.19-6:41 PM
// Modified: 2023.05.19-6:41 PM
// 
// Copyright Michael Kowalski 2023

#pragma once

//---Standard C++ Library-------------
#include <algorithm>
#include <chrono>
#include <cstdio>
#include <functional>
#include <iostream>
#include <memory>
#include <utility>

#include <array>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
//------------------------------------


//---Platform Specific----------------
#define GRL_PLATFORM_UNIX 0 // currently UNIX is not fully implemented

#ifdef GRL_PLATFORM_WINDOWS
#include <Windows.h>
#elif GRL_PLATFORM_UNIX
#include <unistd.h>
#endif
//------------------------------------
