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

#include <functional> // for std::function


#include "core/string/ustring.h" // for String class
#include "core/object/ref_counted.h" // for RefCounted class
#include "core/error/error_list.h" // for Error enum 
#include "core/object/m_object.h" // for CLASS() macro to registeration class 


/**
 * @class FileAccess
 * @brief FileAccess class 
 * provides basic functionality for opening, writing to, and reading from a file. 
 * The constructor takes a filename, and the member functions handle file operations.
 * 
 */

class FileAccess : public RefCounted {
	CLASS(FileAccess , RefCounted);	

public:
	enum ModeFlags {
		WRITE,
		READ,
		WRITE_READ,
		READ_WRITE
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

	bool open_compressed(const String& path, ModeFlags mode);
	bool open_encrypted(const String& path, ModeFlags mode);

	bool write_line_to_file(const String& line);
	bool write_pascal_string_to_file(const String& p_pascal);
 
	bool write_var_to_file(const void* variable, size_t size);
  bool write_16_to_file(uint16_t value);
  
	bool read(const String& data);
  	bool get_line_from_file(const String& line);
    
	bool store_string(const String& data);
  	bool get_var_from_file(void* variable, size_t size);
  
	bool get_hidden_attribute();

	uint16_t get16();
  
	String get_file_path() const;
  	String get_open_error() const;
  
	Vector<uint8_t> get_file_as_Bytes() const; 
	String get_error() const;
  
	Vector<String> get_csv_Line(char delimiter = ',');
  
	void close();
  	void flush();
  
	bool get8(uint8_t& value);
  	uint16_t get16();
  
	String get_as_text();
	String get_file_as_string();

	std::function<void()> get_create_func();


	std::chrono::system_clock::time_point get_modified_time() const;
	bool set_modified_time(const std::chrono::system_clock::time_point& newTime);
	
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
	static void _bind_methods() {} 


private:
    String filename;
    std::fstream file;
    ModeFlags mode;
    String lastError;
    

};


#endif // FILE_ACCESS_H
