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
#ifndef ENGINE_H
#define ENGINE_H


#include "core/typedefs.h"
#include "core/templates/vector.h"
#include "core/error/error_macros.h"



class String;
class Object;


class Engine {
public:
	struct Signleton {
    	char* object;
    	int* count;
    	void* item;
    	String name;
    	Singleton(const String &p_name = String(), Object *p_ptr = nullptr, const String &p_class_name = String());
	};
	};

private:
    int fps;
    int p_target;
    bool hint;
    List<String>* p_list;
    double p_sec;
    double p_time;
    uint64_t frames_drawn = 0;
	uint32_t _frame_delay = 0;
	uint64_t _frame_ticks = 0;
	double _process_step = 0;

	int ips = 60;
	double physics_jitter_fix = 0.5;
	double _fps = 1;
	int _max_fps = 0;
	int _audio_output_latency = 0;
	double _time_scale = 1.0;
	uint64_t _physics_frames = 0;
	int max_physics_steps_per_frame = 8;
	double _physics_interpolation_fraction = 0.0f;
	bool abort_on_gpu_errors = false;
	bool use_validation_layers = false;
	bool generate_spirv_debug_info = false;
	int32_t gpu_idx = -1;

	uint64_t _process_frames = 0;
	bool _in_physics = false;

	List<Singleton> singletons;
	HashMap<String, Object *> singleton_ptrs;

	bool editor_hint = false;
	bool project_manager_hint = false;
	bool extension_reloading = false;

public:
    static Engine* get_signleton();
public:
    int get_engine_fps() const;
    int get_fps_targert() const;

    void set_fps_targert(int p_fps);
    double get_frame_time() const;

    bool is_editor_hint() const;
    bool is_hint() const;

    bool _is_class_enabled() const;
    

    void wiat_time(double seconds);
    void swap_screen_buffer();
    void set_randoom_seed(unsigned int seed);

    void set_randoom_value(int min , int max);
	
	uint64_t get_physics_frames() const { return _physics_frames; }
	uint64_t get_process_frames() const { return _process_frames; }
	bool is_in_physics_frame() const { return _in_physics; }
	uint64_t get_frame_ticks() const { return _frame_ticks; }
	double get_process_step() const { return _process_step; }
	double get_physics_interpolation_fraction() const { return _physics_interpolation_fraction; }

	void set_time_scale(double p_scale);
	double get_time_scale() const;

	void set_print_error_messages(bool p_enabled);
	bool is_printing_error_messages() const;

	void set_frame_delay(uint32_t p_msec);
	uint32_t get_frame_delay() const;

	void add_singleton(const Singleton &p_singleton);
	void get_singletons(List<Singleton> *p_singletons);
	bool has_singleton(const String &p_name) 


    void set_property_list(const List<String>* p_list) const;
    List<String> get_property_list() const;
protected:
    static void _bind_methods();
    friend class ProjectSettings;
    friend class Main;

public:
    Engine();
    ~Engine();

};



#endif // ENGINE_H