// Granola - Granola - grlpch.h
// Created: 2023.05.19-6:41 PM
// Modified: 2023.05.19-6:41 PM
// 
// Copyright Michael Kowalski 2023

#pragma once

//---Standard C++ Library-------------
#include <algorithm>
#include <atomic>
#include <chrono>
#include <cstdio>
#include <functional>
#include <future>
#include <iomanip>
#include <iostream>
#include <memory>
#include <mutex>
#include <ranges>
#include <thread>
#include <utility>


#include <array>
#include <fstream>
#include <map>
#include <ranges>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
//------------------------------------


//---Granola Unchanged Headers--------
#include "Granola/Log.h"
//------------------------------------


//---Platform Specific----------------
#define GRL_PLATFORM_UNIX 0 // currently UNIX is not fully implemented

#ifdef GRL_PLATFORM_WINDOWS
#include <Windows.h>
#elif GRL_PLATFORM_UNIX
#include <unistd.h>
#include <signal.h>
#endif
//------------------------------------


//---Error Handling for external libs-
#ifdef HZ_PLATFORM_WINDOWS
#ifndef NOMINMAX
		// See github.com/skypjack/entt/wiki/Frequently-Asked-Questions#warning-c4003-the-min-the-max-and-the-macro
		#define NOMINMAX
#endif
#endif
//------------------------------------
