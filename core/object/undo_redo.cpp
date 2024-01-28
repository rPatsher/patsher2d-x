#include "undo_redo.h"










void UndoRedo::_bind_methods() {
  Object::bind_method("add_action", &UndoRedo::add_action);
  Object::bind_method("undo", &UndoRedo::undo);
}





