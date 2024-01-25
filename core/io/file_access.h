/**
 * MIT License

Copyright (c) 2024/2025 rPatsher

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#ifndef FILE_ACCESS_H
#define FILE_ACCESS_H


#include <filesystem>
#include <new>
#include <cstdio>
#include <cstdlib>

#include <functional>


#include "core/string/ustring.h"
#include "core/templates/hash_map.h"
#include "core/templates/list.h"
#include "core/templates/vector.h"
#include "core/object/ref_counted.h"
#include "core/error/error_list.h"

#include "core/object/m_object.h"


/**
 * @class FileAccess
 * @brief This simple FileAccess class 
 * provides basic functionality for opening, writing to, and reading from a file. 
 * The constructor takes a filename, and the member functions handle file operations.
 * 
 */

class FileAccess : public RefCounted {
	CLASS(FileAccess , RefCounted);	
	
public:
	enum ModeFlags {
		WRITE,
		READ
	};
public:
	FileAccess();
	virtual ~FileAccess();
		
public:
	/**
	 * open the file
	 * check if file is open !! 
	 */
	bool open(const String& path, ModeFlags mode);
	bool is_open() const;
	
	bool file_exists(const String& path) const;
	bool write(const String& data);
	
	/**
     *  Creates binary data from a file.
     *  @return A data object.
     */
	
	virtual void get_data_from_file(const String& file) const;


	/**
     *  Gets string from a file.
     */
     
     virtual void get_string_from_file(const String& file) const;
     
     
	/**
     * Gets string from a file, async off the main patsher thread
     *
     * @param path filepath for the string to be read. Can be relative or absolute path
     * @param callback Function that will be called when file is read. Will be called 
     * on the main patsher thread.
     */
     
	virtual void get_string_from_file(const String& path , std::function<void(String)> callback) const;
	
	
protected:
	static void bind_methods() {} 
};



#endif // FILE_ACCESS_H
