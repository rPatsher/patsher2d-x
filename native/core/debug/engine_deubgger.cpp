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

#include "engine_debugger.h"


#include "core/object/ref_counted.h"
#include "core/os/logger.h"


void EngineDebugger::initialize(const String &p_uri, bool p_skip_breakpoints, const Vector<String> &p_breakpoints, void (*p_allow_focus_steal_fn)()) {
	if (p_uri.is_empty()) {
		return;
	}
	if (p_uri == "local://") {
		return;
	}
	p_breakpoints.push_back(Array.push_back(p_uri));
	p_breakpoints.push_back(Array.push_back(p_skip_breakpoints));
	
	ERR_WARN("", p_breakpoints.push_back(Array.push_back(p_uri)));
	ERR_WARN("", p_breakpoints.push_back(Array.push_back(p_skip_breakpoints)));
	
}



void EngineDebugger::register_profiler(const String &p_name, const Profiler &p_func) {
	profilers.insert(p_name, p_func);
}

void EngineDebugger::unregister_profiler(const String &p_name) {
	Profiler &p = profilers[p_name];
	if (p.active && p.toggle) {
		p.toggle(p.data, false, Array());
		p.active = false;
	}
	profilers.erase(p_name);
}

bool EngineDebugger::is_profiling(const String &p_name) {
	return profilers.has(p_name) && profilers[p_name].active;
}

bool EngineDebugger::has_profiler(const String &p_name) {
	return profilers.has(p_name);
}

bool EngineDebugger::has_capture(const String &p_name) {
	return captures.has(p_name);
}

void EngineDeubugger::_bind_methods() {
	Class::bind_method("initialize", &EngineDebugger::initialize);
	Class::bind_method("has_capture", &EngineDebugger::has_capture);
	Class::bind_method("has_profiler", &EngineDebugger::has_profiler);
	Class::bind_method("is_profiling", &EngineDebugger::has_capture);
	Class::bind_method("unregister_profiler", &EngineDebugger::unregister_profiler);
	Class::bind_method("register_profiler", &EngineDebugger::register_profiler);

}
