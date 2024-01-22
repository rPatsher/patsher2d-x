/*
 * editor_interface.h
 * 
 * Copyright 2024 rPatsher <>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */


#ifndef EDITOR_INTERFACE_H
#define EDITOR_INTERFACE_H

#include "scene/gui/control.h"
#include "scene/gui/panel.h"
#include "scene/gui/button.h"
#include "scene/gui/color_picker.h"
#include "scene/gui/box.h"
#include "scene/gui/hbox.h"
#include "scene/gui/vbox.h"
#include "scene/gui/window_box.h"

#include "scene/runtime/assets_manager.h"
#include "scene/main/node.h"
#include "scene/main/window.h"

#include "core/object/m_object.h"
#include "core/object/ref_counted.h"


#include "external/extensions/controls/control.h"
#include "external/extensions/controls/control_extension.h"
#include "external/extensions/controls/control_button.h"


class EditorInterface: public Control
{
	CLASS(EditorInterface , Control);
	public:
		enum Mode {
			
			
		};
	public:
		EditorInterface();
		virtual ~EditorInterface();
	
	private:
		
};

#endif /* EDITOR_INTERFACE_H */ 
