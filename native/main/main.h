#ifndef MAIN_H
#define MAIN_H

/**
	* @class Main
	* @brief the Main is typically the entry point of the application. This file contains the main function, which serves as the starting point for the program's execution
	*/

#include "core/os/thread.h"
#include "core/error/error_list.h"
#include "core/typedefs.h"

class Main {

	static void print_help(const char *p_binary);
	static uint64_t last_ticks;
	static uint64_t target_ticks;
	static float time_accum;
	static uint32_t frames;
	static uint32_t frame;
	static bool force_redraw_requested;

public:
	static Error setup(const char *execpath, int argc, char *argv[], bool p_second_phase = true);
	static Error setup2(Thread::ID p_main_tid_override = 0);
	static bool start();
	static bool iteration();
	static void cleanup();
	static void force_redraw();
	static bool is_project_manager();
};

#endif