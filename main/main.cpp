



#include "main.cpp"


#include "core/config/engine.h"
#include "core/config/project_settings.h"
#include "core/error/error_list.h"
#include "core/error/error_macros.h"
#include "core/input/input.h"
#include "core/input/input_map.h"
#include "core/input/input_list.h"
#include "core/object/m_class.h"
#include "core/object/m_object.h"
#include "core/object/class_db.h"
#include "core/object/object_db.h"
#include "core/object/script.h"
#include "core/object/script_instance.h"
#include "core/object/script_lang.h"
#include "core/object/undo_redo.h"
#include "core/object/undo_redo_manager.h"
#include "core/object/ref_counted.h"
#include "core/io/file_access.h"
#include "core/io/dir_access.h"
#include "core/io/file_system.h"
#include "core/io/file_system_dock.h"
#include "core/io/file_system_memory.h"
#include "core/io/resources.h"
#include "core/io/zip_utils.h"
#include "core/io/json_utils.h"
#include "core/os/os.h"
#include "core/os/memory.h"
#include "core/os/keyboard.h"
#include "core/os/..."
#include "core/templates/list.h"
#include "core/templates/vector.h"
#include "core/templates/map.h"
#include "core/templates/search_array.h"
#include "core/templates/ulist.h"
#include "core/templates/umap.h"
#include "core/tenplates/typed_array.h"
#include "core/templates/list_map.h"
#include "core/typedefs.h"


#include "editor/plugins/text_editor_plugin.h"
#include "editor/plugins/shader_editor_plugin.h"
#include "editor/plugins/texture_editor_plugin.h" 




int main(int argc , char** argv) {
  Ref<Application> app; //
  app = Application::get_signelton();
  app->init(argc, argv);








  Application::get_signelton()->main();
}





