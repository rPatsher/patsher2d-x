/*
 * renderer.h
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
#ifndef RENDERER_H
#define RENDERER_H

#include <core/object/object_db.h>
#include <core/object/m_class.h>
#include <core/templates/local_vector>
#include <core/templates/vector.h>
#include <core/templates/hash_map.h>

// C Sources
#include <cstdlib>
#include <cstdio>


class Scene; 
class Event;
class Camera;

/**
 * @class Renderer
 */
class Renderer: public Object
	MCLASS(Renderer, Object);
{
	public:
		Renderer();
		virtual ~Renderer();
		static void bind_static_method();
	
	private:
		Vector<int> data;
		float distance;
		Ref<FILE> file;
		
	
	protected:
		
		
};

#endif /* RENDERER_H */ 
