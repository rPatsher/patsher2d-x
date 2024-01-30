/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#ifndef json_util_h
#define json_util_h

#include "common.h"
#include <stdlib.h>
#include <string.h>

/*!
 * @brief creates number (int32) from string value
 *
 * @param[in] object       json object
 * @param[in] defaultValue default value if operation fails
 * @return number
 */
JSON_INLINE
int32_t
json_int32(const json_t * __restrict object, int32_t defaultValue) {
  if (!object || object->type != JSON_STRING || !object->value)
    return defaultValue;

  return (int32_t)strtol(object->value, NULL, 10);
}

/*!
 * @brief creates number (uint32) from string value
 *
 * @param[in] object       json object
 * @param[in] defaultValue default value if operation fails
 * @return number
 */
JSON_INLINE
uint32_t
json_uint32(const json_t * __restrict object, uint32_t defaultValue) {
  if (!object || object->type != JSON_STRING || !object->value)
    return defaultValue;

  return (uint32_t)strtoul(object->value, NULL, 10);
}

/*!
 * @brief creates number (int64) from string value
 *
 * @param[in] object       json object
 * @param[in] defaultValue default value if operation fails
 * @return number
 */
JSON_INLINE
int64_t
json_int64(const json_t * __restrict object, int64_t defaultValue) {
  if (!object || object->type != JSON_STRING || !object->value)
    return defaultValue;

  return strtoll(object->value, NULL, 10);
}

/*!
 * @brief creates number (uint64) from string value
 *
 * @param[in] object       json object
 * @param[in] defaultValue default value if operation fails
 * @return number
 */
JSON_INLINE
uint64_t
json_uint64(const json_t * __restrict object, uint64_t defaultValue) {
  if (!object || object->type != JSON_STRING || !object->value)
    return defaultValue;

  return strtoull(object->value, NULL, 10);
}

/*!
 * @brief creates number (float) from string value
 *
 * @param[in] object       json object
 * @param[in] defaultValue default value if operation fails
 * @return number
 */
JSON_INLINE
float
json_float(const json_t * __restrict object, float defaultValue) {
  if (!object || object->type != JSON_STRING || !object->value)
    return defaultValue;

  return strtof(object->value, NULL);
}

/*!
 * @brief creates number (double) from string value
 *
 * @param[in] object       json object
 * @param[in] defaultValue default value if operation fails
 * @return number
 */
JSON_INLINE
double
json_double(const json_t * __restrict object, double defaultValue) {
  if (!object || object->type != JSON_STRING || !object->value)
    return defaultValue;

  return strtod(object->value, NULL);
}

/*!
 * @brief creates boolean from string value
 *
 * @param[in] object       json object
 * @param[in] defaultValue default value if operation fails
 * @return boolean values as integer: 1 true, 0 false, error: defaultValue
 */
JSON_INLINE
int
json_bool(const json_t * __restrict object, int defaultValue) {
  const char *boolString;
  char        first;

  if (!object || object->type != JSON_STRING || !(boolString = object->value))
    return defaultValue;

  first = boolString[0];

  if (first == 't' || first == '1') {
    return 1;
  } else if (first == 'n' || first == '0') {
    return 0;
  }

  return defaultValue;
}

/*!
 * @brief return non-NULL terminated string value
 *
 * you must use object->valSize to copy, compare ... string
 *
 * @param[in] object json object
 * @return non-NULL terminated string value (pointer only)
 */
JSON_INLINE
const char*
json_string(const json_t * __restrict object) {
  return (const char *)object->value;
}

/*!
 * @brief return json object from value
 */
JSON_INLINE
json_t*
json_json(const json_t * __restrict object) {
  return (json_t *)object->value;
}

/*!
 * @brief return NULL terminated duplicated string value
 *
 * value must be free-ed when no longer needed
 *
 * @param[in] object json object
 * @return NULL terminated duplicated string value
 */
JSON_INLINE
char*
json_string_dup(const json_t * __restrict object) {
  char *s;

  s = malloc(object->valsize + 1);
  memcpy(s, object->value, object->valsize);
  s[object->valsize] = '\0';

  return s;
}

/*!
 * @brief compares json key with a string
 *
 * @param[in] obj json object
 * @param[in] str string to compare (must be NULL terminated)
 * @return true if str is equals to json's key
 */
JSON_INLINE
bool
json_key_eq(const json_t * __restrict obj, const char * __restrict str) {
  size_t strsize;
    
  if ((strsize = strlen(str)) != (size_t)obj->keysize)
    return false;

  return strncmp(str, obj->key, strsize) == 0;
}

/*!
 * @brief compares json key with a string
 *
 * @param[in] obj     json object
 * @param[in] str     string to compare
 * @param[in] strsize size of string to compare
 * @return true if str is equals to json's key
 */
JSON_INLINE
bool
json_key_eqsz(const json_t * __restrict obj,
              const char   * __restrict str,
              size_t                    strsize) {
  if (strsize != (size_t)obj->keysize)
    return false;

  return strncmp(str, obj->key, strsize) == 0;
}

/*!
 * @brief compares json value with a string
 *
 * @param[in] obj json object
 * @param[in] str string to compare (must be NULL terminated)
 * @return true if str is equals to json's value
 */
JSON_INLINE
bool
json_val_eq(const json_t * __restrict obj, const char * __restrict str) {
  size_t strsize;
    
  if ((strsize = strlen(str)) != (size_t)obj->valsize)
    return false;

  return strncmp(str, obj->value, strsize) == 0;
}

/*!
 * @brief compares json value with a string
 *
 * @param[in] obj     json object
 * @param[in] str     string to compare
 * @param[in] strsize size of string to compare
 * @return true if str is equals to json's value
 */
JSON_INLINE
bool
json_val_eqsz(const json_t * __restrict obj,
              const char   * __restrict str,
              size_t                    strsize) {
  if (strsize != (size_t)obj->valsize)
    return false;

  return strncmp(str, obj->value, strsize) == 0;
}

/*!
 * @brief returns parent object if available
 *
 * @param[in] obj json object
 * @return returns parent object if available
 */
JSON_INLINE
json_t*
json_parent(const json_t * __restrict obj) {
  /*
  const json_t *prev;
  if (!obj)
    return NULL;

  do {
    prev = obj;
    obj  = obj->prev;
  } while (obj && obj->value != prev);

  return obj;*/

  return obj->parent;
}

#endif /* json_util_h */
