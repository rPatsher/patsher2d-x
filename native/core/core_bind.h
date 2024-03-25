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
#ifndef CORE_BIND_H
#define CORE_BIND_H


#include <core/templates/map.h>
#include <core/typedefs.h>
#include <core/version.gen.h>
#include <core/object/m_class.h>
#include <core/object/ref_counted.h>
#include <core/string/string.h>
#include <core/error/error_list.h>




#include <filesystem/filesystem.h>
#include <filesystem>
#include <thread>

class Resource;


class ResourceLoader : public RefCounted {
    MCLASS(ResourceLoader , RefCounted);

protected:
	static void _bind_methods();
	static ResourceLoader *singleton;
public:
	enum ThreadLoadStatus {
		THREAD_LOAD_INVALID_RESOURCE,
		THREAD_LOAD_IN_PROGRESS,
		THREAD_LOAD_FAILED,
		THREAD_LOAD_LOADED
	};

    enum CacheMode {
		CACHE_MODE_IGNORE, // Resource and subresources do not use path cache, no path is set into resource.
		CACHE_MODE_REUSE, // Resource and subresources use patch cache, reuse existing loaded resources instead of loading from disk when available.
		CACHE_MODE_REPLACE, // Resource and subresource use path cache, but replace existing loaded resources when available with information from disk.
	};

    static ResourceLoader *get_singleton() { return singleton; }

    Error load_threaded_request(const String &p_path, const String &p_type_hint = "", bool p_use_sub_threads = false, CacheMode p_cache_mode = CACHE_MODE_REUSE);
    Ref<Resource> load(const String &p_path, const String &p_type_hint = "", CacheMode p_cache_mode = CACHE_MODE_REUSE);


    ResourceLoader() { singleton = this; }

};


class ResourceSaver : public RefCounted {


    
};




#endif 
