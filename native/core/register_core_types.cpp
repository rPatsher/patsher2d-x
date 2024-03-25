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
#include "register_core_types.h"
#include "core/config/engine.h"
#include "core/config/project_settings.h"
#include "core/debug/engine_debugger.h"
#include "core/debug/local_debugger.h"
#include "core/extension/extension.h"
#include "core/extension/extension_manager.h"
#include "core/input/input.h"
#include "core/input/input_map.h"
#include "core/input/input_event.h"
#include "core/object/m_object.h"
#include "core/object/ref_counted.h"
#include "core/object/undo_redo.h"
#include "core/object/script.h"
#include "core/object/script_instance.h"
#include "core/io/config_file.h"




#include "m_class.h"



void register_core_utils() {
	// Config
	DBREGISTER_CLASS(Engine); 
	DBREGISTER_CLASS(ProjectSettings);
	// Debugger 
	DBREGISTER_CLASS(EngineDebugger);
	DBREGISTER_CLASS(LocalDebugger);
	// Extensions
	DBREGISTER_CLASS(Extension);
	DBREGISTER_CLASS(ExtensionManager);
	// Input
	DBREGISTER_CLASS(Input);
	DBREGISTER_CLASS(InputEvent);
	DBREGISTER_CLASS(InputMap);
	DBREGISTER_CLASS(InputMouse);
	DBREGISTER_CLASS(InputMouseButton);
	DBREGISTER_CLASS(InputMouseMotion);
	DBREGISTER_CLASS(InputEventScreenDrag);
	DBREGISTER_CLASS(InputEventScreenTouch);
	// IO
	DBREGISTER_CLASS(ConfigFile);
	DBREGISTER_CLASS(FileSystem);
	DBREGISTER_CLASS(FileAccess);
	DBREGISTER_CLASS(DirAccess);
	DBREGISTER_CLASS(ZipUtils);
	DBREGISTER_CLASS(FileSystemZip);
	DBREGISTER_CLASS(FileSystemMemory);
	DBREGISTER_CLASS(HttpClient);
	DBREGISTER_CLASS(HttpServer);
	DBREGISTER_CLASS(JsonUtils);
	DBREGISTER_CLASS(Resource);
	
	
	
	
}