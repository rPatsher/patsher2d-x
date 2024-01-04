/**
 * MIT License

Copyright (c) 2024/2025 rPatsher

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#ifndef TYPEDEFS_H
#define TYPEDEFS_H

#include <raygui.h>
#include <rlgl.h>

#include <raylib.h>
#include <raymath.h>

class ClassDB;

// Macro to begin a namespace block
#define RPT_NAMESPACE_BEGIN namespace {
// Macro to end a namespace block
#define RPT_NAMESPACE_BEGIN }

/**
 * The `RPTAPI` macro is a platform-dependent conditional declaration in C++.
 * Its purpose is to facilitate the creation of code that behaves differently
 * based on the target platform during compilation. It allows developers to
 * define functions, variables, or symbols with specific linkage or behavior
 * depending on the operating system or platform being compiled for.
 * 
 * By utilizing conditional compilation directives (`#ifdef`, `#elif`, etc.),
 * `RPTAPI` enables developers to create code that seamlessly adapts to various
 * platforms such as Windows, Linux, web (Emscripten), or Android. This macro
 * serves as a switch, enabling the appropriate linkage specifications or
 * platform-specific definitions based on the environment in which the code is
 * being compiled.
 * 
 * For instance, it can be configured to handle exporting or importing symbols
 * in DLLs for Windows, use default external linkage for object files on Linux,
 * and exclude definitions for Android and web platforms. The macro allows for
 * a modular and adaptable codebase, ensuring proper functionality across diverse
 * platforms without needing separate codebases for each environment.
 * 
 * Developers can define and use `RPTAPI` in header files to declare functions,
 * variables, or symbols, and then provide platform-specific implementations in
 * separate files, tailored to each platform's requirements. This approach enables
 * the creation of platform-agnostic code while accommodating platform-specific
 * functionality when necessary.
 */

#include <csignal>
#include <string>
#include <vector>
#include <map>

#if defined(_WIN32)
  #ifdef RPTAPI_EXPORTS
    #define RPTAPI extern "C" __declspec(dllexport)
  #else
    #define RPTAPI extern "C" __declspec(dllimport)
  #endif
#elif defined(__linux__)
  #define RPTAPI extern "C"
#elif defined(__EMSCRIPTEN__)
  #define RPTAPI extern "C"
  #define WEB_PLATFORM_AVAILABLE
#elif defined(__ANDROID__)
  #define RPTAPI extern "C"
  #define ANDROID_PLATFORM_AVAILABLE
#else
  #error Unsupported platform
#endif





#include <glfw/include/GLFW/glfw3.h>
#include <glfw/include/GLFW/glfw3native.h>

 

#endif //