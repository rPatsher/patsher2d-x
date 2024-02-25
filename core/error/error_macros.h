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
#ifndef ERROR_MACROS_H
#define ERROR_MACROS_H


#include <cstdlib>
#include <cstdio>

#include "thirdparty/logger/src/logger.h"
#include "thirdparty/logger/src/loggerconf.h"
#include "thirdparty/log/log.h"
// Debug Log

#define LOG(...)       do {} while (0)
#define LOGINFO(...)   do {} while (0)
#define ERR_LOG_ERROR(...)  do {} while (0)
#define WAR_LOG_WARN(...)   do {} while (0)

// Args Templates
#define SAFE_DELETE(p)           do { delete (p); (p) = nullptr; } while(0)
#define SAFE_DELETE_ARRAY(p)     do { if(p) { delete[] (p); (p) = nullptr; } } while(0)
#define SAFE_FREE(p)             do { if(p) { free(p); (p) = nullptr; } } while(0)
#define SAFE_RELEASE(p)          do { if(p) { (p)->release(); } } while(0)
#define SAFE_RELEASE_NULL(p)     do { if(p) { (p)->release(); (p) = nullptr; } } while(0)
#define SAFE_RETAIN(p)           do { if(p) { (p)->retain(); } } while(0)
#define BREAK_IF(cond)           if(cond) break


#define ERR_PRINT(fmt, ...) \ 
      log_error("ERROR: " fmt, ##__VA_ARGS__);


#define ERR_WARN(fmt , ...) \ 
      log_warn("WARN: " fmt , ##__VA_ARGS__);


#define ERR_INFO(fmt , ...)  \ 
      log_info("INFO: " fmt, ##__VA_ARGS__);


/**
	*@brief ErrorMacros for logger class on c++ 
	*/
	
enum ErrorHandlerType {
	ERR_HANDLER_ERROR,
	ERR_HANDLER_WARNING,
	ERR_HANDLER_SCRIPT,
	ERR_HANDLER_SHADER,
};

typedef void (*ErrorHandlerFunc)(void *, const char *, const char *, int p_line, const char *, const char *, bool p_editor_notify, ErrorHandlerType p_type);

struct ErrorHandlerList {
	ErrorHandlerFunc errfunc = nullptr;
	void *userdata = nullptr;

	ErrorHandlerList *next = nullptr;

	ErrorHandlerList() {}
};

void add_error_handler(ErrorHandlerList *p_handler);
void remove_error_handler(const ErrorHandlerList *p_handler);

// functions used by the error macros 
void _err_print_error(const char *p_function, const char *p_file, int p_line, const char *p_error, bool p_editor_notify = false, ErrorHandlerType p_type = ERR_HANDLER_ERROR);
void _err_print_error(const char *p_function, const char *p_file, int p_line, const String &p_error, bool p_editor_notify = false, ErrorHandlerType p_type = ERR_HANDLER_ERROR);
void _err_print_error(const char *p_function, const char *p_file, int p_line, const char *p_error, const char *p_message, bool p_editor_notify = false, ErrorHandlerType p_type = ERR_HANDLER_ERROR);
void _err_print_error(const char *p_function, const char *p_file, int p_line, const String &p_error, const char *p_message, bool p_editor_notify = false, ErrorHandlerType p_type = ERR_HANDLER_ERROR);
void _err_print_error(const char *p_function, const char *p_file, int p_line, const char *p_error, const String &p_message, bool p_editor_notify = false, ErrorHandlerType p_type = ERR_HANDLER_ERROR);
void _err_print_error(const char *p_function, const char *p_file, int p_line, const String &p_error, const String &p_message, bool p_editor_notify = false, ErrorHandlerType p_type = ERR_HANDLER_ERROR);
void _err_print_index_error(const char *p_function, const char *p_file, int p_line, int64_t p_index, int64_t p_size, const char *p_index_str, const char *p_size_str, const char *p_message = "", bool p_editor_notify = false, bool fatal = false);
void _err_print_index_error(const char *p_function, const char *p_file, int p_line, int64_t p_index, int64_t p_size, const char *p_index_str, const char *p_size_str, const String &p_message, bool p_editor_notify = false, bool fatal = false);
void _err_flush_stdout();

#ifdef __GNUC__
//#define FUNCTION_STR __PRETTY_FUNCTION__ - too annoying
#define FUNCTION_STR __FUNCTION__
#else
#define FUNCTION_STR __FUNCTION__
#endif

#ifdef _MSC_VER
/**
 * Don't use GENERATE_TRAP() directly, should only be used be the macros below.
 */
#define GENERATE_TRAP() __debugbreak()
#else
/**
 * Don't use GENERATE_TRAP() directly, should only be used be the macros below.
 */
#define GENERATE_TRAP() __builtin_trap()
#endif



#define ERR_FAIL_INDEX_V(m_index, m_size, m_retval)                                                             \
	if (unlikely((m_index) < 0 || (m_index) >= (m_size))) {                                                     \
		_err_print_index_error(FUNCTION_STR, __FILE__, __LINE__, m_index, m_size, _STR(m_index), _STR(m_size)); \
		return m_retval;                                                                                        \
	} else                                                                                                      \
		((void)0)

#define ERR_FAIL_INDEX_V_MSG(m_index, m_size, m_retval, m_msg)                                                         \
	if (unlikely((m_index) < 0 || (m_index) >= (m_size))) {                                                            \
		_err_print_index_error(FUNCTION_STR, __FILE__, __LINE__, m_index, m_size, _STR(m_index), _STR(m_size), m_msg); \
		return m_retval;                                                                                               \
	} else                                                                                                             \
		((void)0)

/**
 * Same as `ERR_FAIL_INDEX_V_MSG` but also notifies the editor.
 */
#define ERR_FAIL_INDEX_V_EDMSG(m_index, m_size, m_retval, m_msg)                                                             \
	if (unlikely((m_index) < 0 || (m_index) >= (m_size))) {                                                                  \
		_err_print_index_error(FUNCTION_STR, __FILE__, __LINE__, m_index, m_size, _STR(m_index), _STR(m_size), m_msg, true); \
		return m_retval;                                                                                                     \
	} else                                                                                                                   \
		((void)0)


// Unsigned integer index out of bounds error macros.

#define ERR_FAIL_UNSIGNED_INDEX(m_index, m_size)                                                                \
	if (unlikely((m_index) >= (m_size))) {                                                                      \
		_err_print_index_error(FUNCTION_STR, __FILE__, __LINE__, m_index, m_size, _STR(m_index), _STR(m_size)); \
		return;                                                                                                 \
	} else                                                                                                      \
		((void)0)


#define ERR_FAIL_UNSIGNED_INDEX_MSG(m_index, m_size, m_msg)                                                            \
	if (unlikely((m_index) >= (m_size))) {                                                                             \
		_err_print_index_error(FUNCTION_STR, __FILE__, __LINE__, m_index, m_size, _STR(m_index), _STR(m_size), m_msg); \
		return;                                                                                                        \
	} else                                                                                                             \
		((void)0)

/**
 * Same as `ERR_FAIL_UNSIGNED_INDEX_MSG` but also notifies the editor.
 */
#define ERR_FAIL_UNSIGNED_INDEX_EDMSG(m_index, m_size, m_msg)                                                                \
	if (unlikely((m_index) >= (m_size))) {                                                                                   \
		_err_print_index_error(FUNCTION_STR, __FILE__, __LINE__, m_index, m_size, _STR(m_index), _STR(m_size), m_msg, true); \
		return;                                                                                                              \
	} else                                                                                                                   \
		((void)0)

/**
 * Try using `ERR_FAIL_UNSIGNED_INDEX_V_MSG`.
 * Only use this macro if there is no sensible error message.
 *
 * Ensures an unsigned integer index `m_index` is less than `m_size`.
 * If not, the current function returns `m_retval`.
 */
#define ERR_FAIL_UNSIGNED_INDEX_V(m_index, m_size, m_retval)                                                    \
	if (unlikely((m_index) >= (m_size))) {                                                                      \
		_err_print_index_error(FUNCTION_STR, __FILE__, __LINE__, m_index, m_size, _STR(m_index), _STR(m_size)); \
		return m_retval;                                                                                        \
	} else                                                                                                      \
		((void)0)
		
	




#endif // ERROR_MACROS_H
