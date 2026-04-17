#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <iostream>
#include <vector>
#include <string>
#include <atomic>
#include <thread>
#include <chrono>
#include <algorithm>

// JNI
#include <jni.h>
#include <jvmti.h>

// MinHook
#include "MinHook.h"

// ImGui
#include "imgui.h"
#include "backends/imgui_impl_win32.h"
#include "backends/imgui_impl_opengl3.h"

// Bape Config
#include "config/mappings.h"
