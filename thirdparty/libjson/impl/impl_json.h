/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#ifndef json_impl_json_h
#define json_impl_json_h

#include "../json.h"
#include "impl_mem.h"

JSON_INLINE
json_doc_t*
json_parse(const char * __restrict contents, bool reverse) {
  json_doc_t *doc;
  json_t     *obj, *val, *parent;
  const char *key, *p, *end;
  json_t      tmproot;
  int         keysize;
  char        c, quote;
  bool        lookingForKey, foundQuote;

  if (!contents || (c = *contents) == '\0')
    return NULL;

  doc            = calloc(1, sizeof(*doc));
  doc->memroot   = calloc(1, sizeof(json_mem_t) + JSON_MEM_PAGE);
  p              = contents;

  memset(&tmproot, 0, sizeof(tmproot));
  tmproot.type   = JSON_OBJECT;

  key            = NULL;
  parent         = &tmproot;
  obj            = parent;
  keysize        = 0;
  lookingForKey  = false;

  ((json_mem_t *)doc->memroot)->capacity = JSON_MEM_PAGE;
  
  quote = '"';

  do {
  again:
    /* child */
    switch (c) {
      /* trim */
      case ' ':
      case '\r':
      case '\n':
      case '\t':
        break;
      case '{':
      case '[': {
        if (obj->type == JSON_ARRAY)
          ++((json_array_t *)obj)->count;

        /* switch parent */
        parent = obj;

        if (c == '{') {
          obj           = json__impl_calloc(doc, sizeof(json_t));
          obj->type     = JSON_OBJECT;
          lookingForKey = true;
        } else {
          obj       = json__impl_calloc(doc, sizeof(json_array_t));
          obj->type = JSON_ARRAY;
        }

        /* parent must not be NULL */

        if (!reverse) {
          if (!parent->next)
            parent->next = obj;
          else
            json_json(parent)->next = obj;
        } else {
          obj->next = parent->value;
        }

        parent->value = obj;
        obj->parent   = parent;

        if (key) {
          obj->key     = key;
          obj->keysize = keysize;
          key          = NULL;
        }

        break;
      }
      case '}':
      case ']':
        /* switch parent back */
        if (!parent)
          goto err;

        if (!reverse) {
          obj->value = obj->next;
          obj->next  = NULL;
        }

        obj           = parent;
        parent        = parent->parent;
        lookingForKey = obj->type == JSON_OBJECT;

        break;
      case ',': {
        lookingForKey = obj->type == JSON_OBJECT;
        break;
      }
      case ':': {
        /* c = *++p; */
        ++p;
        break;
      }
      default: {
        /* looking for key */
        if (lookingForKey) {
          if ((foundQuote = (c == '"' || c == '\'' || c == '`'))) {
            quote = c;
            c     = *++p;
          }
          
          key = end = p;

          if (foundQuote) {
            while (c != quote) {
              if (c == '\0')
                goto err;

              /* espace */
              if (c != '\\') {
                if (c != ' ' && c != '\r' && c != '\n' && c != '\t')
                  end = p + 1;
              } else {
                /* c = *++p; */
                ++p;
              }

              c = *++p;
            }

            /* skip trailing quote */
            /* c = *++p; */
            ++p;
          } else {
            while (c != ':') {
              if (c == '\0')
                goto err;
              
              if (c != ' ' && c != '\r'  && c != '\n' && c != '\t')
                end = p + 1;
              
              c = *++p;
            }
            
            /* skip trailing column */
            /* c = *++p; */
            ++p;
          }

          keysize = (int)(end - key);

          if (key == NULL || c  == '\0')
            goto err;

          lookingForKey = false;
        }

        /* looking for value */
        else {
          val       = json__impl_calloc(doc, sizeof(json_t));
          val->type = JSON_STRING;

          if (obj->type == JSON_ARRAY)
            ++((json_array_t *)obj)->count;

          /* parent must not be NULL */

          if (!reverse) {
            if (!obj->next)
              obj->next = val;
             else
              json_json(obj)->next = val;
          } else {
            val->next = obj->value;
          }

          obj->value  = val;
          val->parent = obj;

          if (key) {
            val->key     = key;
            val->keysize = keysize;
            key          = NULL;
          }
          
          if ((foundQuote = (c == '"' || c == '\'' || c == '`'))) {
            quote = c;
            c     = *++p;
          }

          end        = p;
          val->value = (void *)end;

          if (foundQuote) {
            while (c != quote) {
              if (c == '\0')
                goto err;

              /* espace */
              if (c != '\\') {
                if (c != ' ' && c != '\r' && c != '\n' && c != '\t')
                  end = p + 1;
              } else {
                /* c = *++p; */
                ++p;
              }

              c = *++p;
            }

            /* skip trailing quote */
            /* c = *++p; */
            ++p;
          } else {
            while (c != ',' && c != '{' && c != '}' && c != '[' && c != ']') {
              if (c == '\0')
                goto err;

              if (c != ' ' && c != '\r' && c != '\n' && c != '\t')
                end = p + 1;

              c = *++p;
            }
          }

          val->valsize = (int)(end - (char *)val->value);

          if (!foundQuote && val->valsize == 4) {
            char *n;

            /* check if it is null */
            n = val->value;

            if (n[0] == 'n' && n[1] == 'u' && n[2] == 'l' && n[3] == 'l') {
              val->value   = NULL;
              val->valsize = 0;
            }
          }
          
          c = *p;

          goto again;
        } /* if lookingForKey */
      } /* switch->default */
    } /* switch */
  } while ((c = *p) != '\0' && (c = *++p) != '\0');

err:
  if (tmproot.value) {
    ((json_t *)tmproot.value)->parent = NULL;
    ((json_t *)tmproot.value)->next   = NULL;
  }

  doc->root = tmproot.value;
  return doc;
}

JSON_INLINE
void
json_free(json_doc_t * __restrict jsondoc) {
  json_mem_t *mem, *tofree;

  mem = jsondoc->memroot;
  while (mem) {
    tofree = mem;
    mem    = mem->next;
    free(tofree);
  }

  free(jsondoc);
}

JSON_INLINE
json_t*
json_get(const json_t * __restrict object, const char * __restrict key) {
  json_t *iter;
  size_t  keysize;
  
  if (!object || !key || !(iter = object->value))
    return NULL;
  
  keysize = strlen(key);
  while (iter && strncmp(iter->key, key, keysize) != 0)
    iter = iter->next;
  
  return iter;
}

JSON_INLINE
json_array_t*
json_array(const json_t * __restrict object) {
  if (!object || object->type != JSON_ARRAY)
    return NULL;
  
  return (void *)object;
}

JSON_INLINE
int
json_count(const json_t * __restrict object) {
  const json_array_t *arr;

  if ((arr = json_array(object)))
    return arr->count;

  return 0;
}

JSON_INLINE
bool
json_is_array(const json_t * __restrict object) {
  return object && object->type == JSON_ARRAY;
}

JSON_INLINE
void
json_array_float(float        * __restrict dest,
                 const json_t * __restrict object,
                 float                     defaultValue,
                 int                       desiredCount,
                 bool                      sourceIsReversed) {
  json_array_t *arr;
  json_t       *item;
  int           count, i;

  /* fill the array with default value if object is not an array */
  if (!(arr = json_array(object))) {
    for (i = 0; i < desiredCount; i++)
      dest[i] = defaultValue;
    return;
  }

  count = arr->count;
  item  = arr->base.value;
  
  if (desiredCount > 0 && count > desiredCount)
    count = desiredCount;

  if (sourceIsReversed) {
    if (desiredCount > count) {
      for (i = desiredCount - 1; i >= 0; i--)
        dest[i] = defaultValue;
    }

    while (item) {
      if (count <= 0)
        break;

      dest[--count] = json_float(item, defaultValue);
      item          = item->next;
    }
    
    while (count)
      dest[--count] = defaultValue;
  } else {
    i = 0;
    while (item) {
      if (i >= count)
        break;

      dest[i++] = json_float(item, defaultValue);
      item      = item->next;
    }
    
    if (i != desiredCount) {
      for (; i < desiredCount; i++)
        dest[i] = defaultValue;
    }
  }
}

#endif /* json_impl_json_h */
