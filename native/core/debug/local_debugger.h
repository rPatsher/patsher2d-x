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

#ifndef LOCAL_DEBUGGER_H
#define LOCAL_DEBUGGER_H


#include "core/error/error_macros.h"
#include "core/debug/engine_debugger.h"
#include "core/templates/hash_map.h"
#include "core/templates/vector.h"


class String;
class EngineDebugger;
class Profiler;
class Capture;

class LocalDebugger {
public:
	static virtual void initialize(const String &p_uri, bool p_skip_breakpoints, const Vector<String> &p_breakpoints, void (*p_allow_focus_steal_fn)()) const override;
	static virtual void deinitialize();
	static virtual void register_profiler(const String &p_name, const Profiler &p_profiler);
	static virtual void unregister_profiler(const String &p_name) const override;
	static virtual bool is_profiling(const String &p_name);
	static virtual bool has_profiler(const String &p_name);
	static virtual void profiler_add_frame_data(const String &p_name, const Array &p_data) const override;

protected:
	static HashMap<String, Profiler> profilers;
	static HashMap<String, Capture> captures;
	static HashMap<String, CreatePeerFunc> protocols;
	
public:
	virtual LocalDebugger();
	~LocalDebugger();
};



#endif // LOCAL_DEBUGGER_H