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

#ifndef ENGINE_DEBUGGER_H
#define ENGINE_DEBUGGER_H

#include "core/templates/vector.h"
#include "core/templates/hash_map.h"
#include "core/string/ustring.h"
#include "core/variant/array.h"
#include "core/error/error_list.h"
#include "core/error/error_macros.h"



class RefCounted; 
class ScriptDebugger;


class EngineDeubgger {
public:
	typedef void (*ProfilingToggle)(void *p_user, bool p_enable, const Array &p_opts);
	typedef void (*ProfilingTick)(void *p_user, double p_frame_time, double p_process_time, double p_physics_time, double p_physics_frame_time);
	typedef void (*ProfilingAdd)(void *p_user, const Array &p_arr);

	typedef Error (*CaptureFunc)(void *p_user, const String &p_msg, const Array &p_args, bool &r_captured);
public:
	class Profiler {
		friend class EngineDebugger;

		ProfilingToggle toggle = nullptr;
		ProfilingAdd add = nullptr;
		ProfilingTick tick = nullptr;
		void *data = nullptr;
		bool active = false;

	public:
		Profiler() {}
		Profiler(void *p_data, ProfilingToggle p_toggle, ProfilingAdd p_add, ProfilingTick p_tick) {
			data = p_data;
			toggle = p_toggle;
			add = p_add;
			tick = p_tick;
		}
	};
	class Capture {
		friend class EngineDebugger;

		CaptureFunc capture = nullptr;
		void *data = nullptr;

	public:
		Capture() {}
		Capture(void *p_data, CaptureFunc p_capture) {
			data = p_data;
			capture = p_capture;
		}
	};
	
protected:
	private:
	double frame_time = 0.0;
	double process_time = 0.0;
	double physics_time = 0.0;
	double physics_frame_time = 0.0;

	uint32_t poll_every = 0;
	public:
	void _bind_methods() {}

protected:
	static EngineDebugger *singleton;
	static ScriptDebugger *script_debugger;

	static HashMap<String, Profiler> profilers;
	static HashMap<String, Capture> captures;
	static HashMap<String, CreatePeerFunc> protocols;
public:
static void initialize(const String &p_uri, bool p_skip_breakpoints, const Vector<String> &p_breakpoints, void (*p_allow_focus_steal_fn)());
	static void deinitialize();
	static void register_profiler(const String &p_name, const Profiler &p_profiler);
	static void unregister_profiler(const String &p_name);
	static bool is_profiling(const String &p_name);
	static bool has_profiler(const String &p_name);
	static void profiler_add_frame_data(const String &p_name, const Array &p_data);

	virtual EngineDebugger();
	~EngineDebugger()

};




#endif // ENGINE_DEBUGGER_H