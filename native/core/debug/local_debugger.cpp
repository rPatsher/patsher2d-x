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

#include "local_debugger.h"


#include "core/debug/engine_debugger.h"
#include "core/string/ustring.h"
#include "core/object/m_class.h"

virtual void LocalDebugger::initialize(const String &p_uri, bool p_skip_breakpoints, const Vector<String> &p_breakpoints, void (*p_allow_focus_steal_fn)()) const override {
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
	
	
	return p_uri;
	
}



virtual void LocalDebugger::register_profiler(const String &p_name, const Profiler &p_func) const override {
	profilers.insert(p_name, p_func);
}

virtual void LocalDebugger::unregister_profiler(const String &p_name) const override {
	Profiler &p = profilers[p_name];
	if (p.active && p.toggle) {
		p.toggle(p.data, false, Array());
		p.active = false;
	}
	profilers.erase(p_name);
}

virtual bool LocalDebugger::is_profiling(const String &p_name) const override {
	return profilers.has(p_name) && profilers[p_name].active;
}

virtual bool LocalDebugger::has_profiler(const String &p_name) const override {
	return profilers.has(p_name);
}

virtual bool LocalDebugger::has_capture(const String &p_name) const override {
	return captures.has(p_name);
}

void EngineDeubugger::_bind_methods() {
	Class::bind_method("initialize", &LocalDebugger::initialize);
	Class::bind_method("has_capture", &LocalDebugger::has_capture);
	Class::bind_method("has_profiler", &LocalDebugger::has_profiler);
	Class::bind_method("is_profiling", &LocalDebugger::has_capture);
	Class::bind_method("unregister_profiler", &LocalDebugger::unregister_profiler);
	Class::bind_method("register_profiler", &LocalDebugger::register_profiler);

}
