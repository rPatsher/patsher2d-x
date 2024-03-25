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
#ifndef RESOURCE_H
#define RESOURCE_H

#include "core/error/error_macros.h"
#include "core/error/error_list.h"
#include "core/object/m_class.h"
#include "core/object/ref_counted.h"
#include "core/templates/safe_list.h"
#include "core/templates/safe_refcounted.h"



class String;
class Node;
class Variant;
class ResourceID;


class Resource : public RefCounted {
	CLASS(Resource, RefCounted);


public:
	static void register_custom_data_to_otdb() { Class::add_resource_base_extension("res", get_class_static()); }
	virtual String get_base_extension() const { return "res"; }

private:
        friend class ResourceCache;
        friend class ResourceID;

        String name;
        String path_cache;
        String scene_unique_id;
        
        bool local_to_scene = false;
        Node *local_scene = nullptr;

        SelfList<Resource> remapped_list;
        
public:
        virtual void reset_state();
        virtual Error copy_from(const Ref<Resource> &p_resource);
        virtual void reload_from_file();
        
        void set_name(const String &p_name);
        String get_name() const;

        virtual void set_path(const String &p_path, bool p_take_over = false);
        String get_path() const;
        
        virtual ResourceID get_id() const;
        
        virtual void duplicate(bool p_duplicate);
    	virtual void clear();
        
        bool set_local_to_scene(bool p_enable);
        bool is_local_to_scene(); 
        static void get_cached_resources(List<Resource>* p_resources);
        
        void update_configuration_warning() ;
        void reload_editor_from_file();
        
        virtual void set_scene_unique_id(const String &p_id);
        virtual void set_id_for_path(const String& path, const String& id);
        String generate_datetime_unique_id();
        String generate_datetime();
        
private:
	Map<String, String> properties;
    bool is_dup; // flag to track duplication status
    std::unordered_map<std::string, std::string> pathToId; // map to store ID associated with a path
    
};

class ResourceCache {
        friend class Resource;
        friend class ResourceLoader;
        static HashMap<String, Resource *> resources;
        static HashMap<String, HashMap<String, String>> res_path;
        friend void unregister_core_types();
        static void clear();
        friend void register_core_types();

public:
        static bool has(const String &p_path);
        static Ref<Resource> get_ref(const String &p_path);
        static void get_cached_resources(List<Ref<Resource>> *p_resources);
        static int get_cached_resource_count();
};





#endif // RESOURCE_H