/*
 * editor_node.h
 * 
 * Copyright 2024 Unknown <rPatsher@localhost>
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


#ifndef EDITOR_NODE_H
#define EDITOR_NODE_H

#include "core/object/ref_counted.h"
#include "core/object/m_class.h"
#include "core/object/m_object.h"
#include "core/templates/vector.h"
#include "core/templates/map.h"
#include "core/templates/hash_map.h"
#include "scene/main/node.h"
#include "scene/main/window.h"
#include "scene/gui/panel.h"
#include "scene/gui/texture_rect.h"
#include "scene/gui/box.h"
#include "scene/gui/container.h"
#include "scene/gui/button.h"
#include "scene/gui/control.h"
#include "scene/gui/input_box.h"
#include "scene/gui/label.h"
#include "scene/gui/label_atlas.h"
#include "scene/gui/window_box.h"
#include "scene/gui/progress_bar.h"
#include "scene/gui/scroll_bar.h"
#include "scene/runtime/asset_manager.h"
#include "scene/runtime/assets_manager_ex.h"
#include "scene/runtime/event_assets_manager_ex.h"
#include "scene/themes/default_theme.h"


class TabBar;
class AcceptDialogs;
class MenuBar;
class ListItem;
class TreeItem;
class Texture2D;




class EditorNode: public Node
	CLASS(EditorNode , Node);
{
	
	public:
		enum ModeMenuBar {
			MENU_SCENE,
			MENU_BAR_PROJECT,
			MENU_BAR_EDITOR,
			MENU_BAR_DEVELOPER
			
		};
		enum Mode {
			FLAGS_FULL_SCREEN = 0,
			FLAGS_RESIZE_WINDOW = 1
		};
	public:
		EditorNode();
		virtual ~EditorNode();
	
	private:
		Ref<Window> window;
		Ref<Node> node;
		
		
	
	
};

class EditorNodeDialogs : public AcceptDialogs {
	CLASS(EditorNodeDialogs , AcceptDialogs);
};
#endif /* EDITOR_NODE_H */ 
