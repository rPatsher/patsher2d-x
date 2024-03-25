/*
 * callback_signals.h
 * 
 * Copyright 2024 Patsher
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
 
#include "core/object/callback_func.h"
#include "core/object/ref_counted.h"

#include <cstdio>
#include <signal.h>
#include <functional>
#include <string>
#include <utility>


#ifndef CALLBACK_SIGNALS_H
#define CALLBACK_SIGNALS_H

template <typename T>
class CallBackSignals
{
	public:
		struct DataCall{
			T* obj;
			Ref<DataBack> data;
			DataCall() {}
			~DataCall() {}
		};
		
	public:

		CallBackSignals();
		virtual ~CallBackSignals();
	
	private:
		//
		
};

#endif /* CALLBACK_SIGNALS_H */ 
