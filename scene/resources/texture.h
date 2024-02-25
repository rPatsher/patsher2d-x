/*
 * texture.h
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


#ifndef TEXTURE_H
#define TEXTURE_H


#include "core/typedefs.h"
#include "core/object/ref_counted.h"
#include "core/object/m_object.h"

class Texture
{
	public:
		Texture();
		virtual ~Texture();
	public:
		void load(const char* file);
		void unload() const;
		
		void draw();
		void set_width(const int width);
		void set_height(const int height);
		
		int get_width() const;
		int get_height() const;
	
	private:
		Ref<Texture2D> texture;
};

#endif /* TEXTURE_H */ 
