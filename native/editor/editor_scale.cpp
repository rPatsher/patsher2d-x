


#include "editor_scale.h"

float EditorScale::_scale = 1.0f;

void EditorScale::set_scale(float p_scale) {
	_scale = p_scale;
}

float EditorScale::get_scale() {
	return _scale;
}