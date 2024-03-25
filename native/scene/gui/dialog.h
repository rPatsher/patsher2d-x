
/*
 * dialog.hpp
 * 
 * Copyright 2024 rPatsher 
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


#ifndef DIALOG_H
#define DIALOG_H


#include "core/object/m_object.h"
#include "core/object/ref_counted.h"
#include "core/templates/vector.h"
#include "core/string/ustring.h"
#include "scene/gui/control.h"
#include "scene/main/window.h"
#include "core/typedefs.h"

// C Libary

#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cctype>


/**
 * @class Dialog 
 */

class Dialog : public Control
	CLASS(Dialog , Control);
{
	public:
		enum Mode {
			
			
		};
		enum Flags {
			
			
		};
	
	public:
		Dialog();
		virtual ~Dialog();
	public:
		void create(); 
		bool init();
		
		void set_title(const char* title);
		String get_title() const;
		
		void set_size(const int width , const int height);
		int get_size() const;
		
		void set_pos(const int posx, const int posy);
		int get_pos() const;
		
		
		
	
	private:
		Ref<GtkWidget> p_dialog; // Create Dialog with using GtKWindow 
		Ref<Window> window; // Window Class for Dialog class
		bool initailize;
		bool visible;
		int width;
		int height;
	protected:
		static void bind_methods() {} 
		
};


class AcceptDialogs : public Dialog {
	CLASS(AcceptDialogs , Dialog);
};



class ConfirmeDialog : public Dialog {
	CLASS(ConfirmeDialog , Dialog); 
};
#endif /* DIALOG_H */ 
