/*
 * texture.cpp
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


#include "texture.h"


Texture::Texture()
{
	
}


Texture::~Texture()
{
	
}


void Texture::load(const char* file) {
	texture = LoadTexture(file);
}

void Texture::unload() const {
	UnLoadTexture(texture);
}

int Texture::get_width() const {
	return texture->width;
}

int Texture::get_height() const {
	return texture->height;
}

void Texture::set_width(const int width) {
	texture->width = width;
}

void Texture::set_height(const int height) {
	texture->height = height;
}

void Texture::set_mode(Alignment mode) const {
	switch (alignment) {
        case Alignment::TOP_CENTER:
            x -= texture.width / 2;
            break;
        case Alignment::TOP_RIGHT:
            x -= texture.width;
            break;
        case Alignment::MIDDLE_LEFT:
            y -= texture.height / 2;
            break;
        case Alignment::CENTER:
            x -= texture.width / 2;
            y -= texture.height / 2;
            break;
        case Alignment::MIDDLE_RIGHT:
            x -= texture.width;
            y -= texture.height / 2;
            break;
        case Alignment::BUTTOM_LEFT:
            y -= texture.height;
            break;
        case Alignment::BUTTOM_CENTER:
            x -= texture.width / 2;
            y -= texture.height;
            break;
        case Alignment::BUTTOM_RIGHT:
            x -= texture.width;
            y -= texture.height;
            break;
        // case Alignment::TopLeft:
        default:
            // Default is already top-left, no adjustments needed
            break;
    }

static void Texture::bind_methods() {
	Object::get_signelton()->bind_method("load" , &Texture::load);
	Object::get_signelton()->bind_method("create", &Texture::create);
	Object::get_signelton()->bind_method("unload" , &Texture::unload);
	Object::get_signelton()->bind_method("draw" , &Texture::draw);
	Object::get_signelton()->bind_method("set_width" , &Texture::set_width);
	Object::get_signelton()->bind_method("set_height", &Texture::set_height);
}
