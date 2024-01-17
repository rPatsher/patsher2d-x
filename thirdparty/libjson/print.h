/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#ifndef json_print_h
#define json_print_h

#include "common.h"
#include "json.h"
#include "util.h"
#include <stdio.h>

/*!
 * @brief print json with option
 *
 * @param[in] ostream stream to print
 * @param[in] json    json object
 * @param[in] opt     0: uglify, 1: pretty, 2: human
 */
JSON_INLINE
void
json_print_ex(FILE   * __restrict ostream,
              json_t * __restrict json,
              int                 opt) {
  const json_t *parent;
  int           pad, i;

  pad    = 0;
  parent = NULL;

  while (json) {
    if (opt > 0) {
      for (i = 0; i < pad; i++)
        fprintf(ostream, "\t");

      if (json->key)
        fprintf(ostream, "\"%.*s\": ", json->keysize, json->key);
    } else {
      if (json->key)
        fprintf(ostream, "\"%.*s\":", json->keysize, json->key);
    }

    switch (json->type) {
      case JSON_OBJECT:
        if (opt > 0)
          fprintf(ostream, "{\n");
        else
          fprintf(ostream, "{");

        if (json->value) {
          pad++;

          /* parent = json; */
          json = json->value;
          continue;
        } else {
          fprintf(ostream, "}");
        }
        break;

      case JSON_STRING:
        if (json->value)
          fprintf(ostream, "\"%.*s\"", json->valsize, json_string(json));
        else
          fprintf(ostream, "null");

        if (json->next)
          fprintf(ostream, ",");

        if (opt > 0)
          fprintf(ostream, "\n");
        break;

      case JSON_ARRAY:
        if (opt > 0) {
          if (opt > 1)
            fprintf(ostream, "(%d) [\n", json_count(json));
          else
            fprintf(ostream, "[\n");
        } else {
          fprintf(ostream, "[");
        }

        if (json->value) {
          pad++;

          /* parent = json; */
          json = json->value;
          continue;
        } else {
          fprintf(ostream, "]");
        }
        break;
      default:
        break;
    }

    if (json->next) {
      json = json->next;
    } else if ((parent = json->parent)) {
      do {
        --pad;

        if (opt > 0) {
          for (i = 0; i < pad; i++)
            fprintf(ostream, "\t");
        }

        if (parent->type == JSON_OBJECT)
          fprintf(ostream, "}");
        else if (parent->type == JSON_ARRAY)
          fprintf(ostream, "]");

        if (parent->next)
          fprintf(ostream, ",");

        if (opt > 0)
          fprintf(ostream, "\n");

        json   = parent->next;
        parent = parent->parent;
      } while (!json && parent);
    } else {
      break;
    }
  } /* while (json)  */
}

/*!
 * @brief print json
 *
 * @param[in] ostream stream to print
 * @param[in] json    json object
 */
JSON_INLINE
void
json_print_pretty(FILE   * __restrict ostream,
                  json_t * __restrict json) {
  json_print_ex(ostream, json, 1);
}

/*!
 * @brief print json for humans
 *
 * @param[in] ostream stream to print
 * @param[in] json    json object
 */
JSON_INLINE
void
json_print_human(FILE   * __restrict ostream,
                 json_t * __restrict json) {
  fprintf(ostream, "json ( %p ):\n", (void *)json);
  json_print_ex(ostream, json, 2);
  fprintf(ostream, "\n");
}

/*!
 * @brief print json
 *
 * @param[in] ostream stream to print
 * @param[in] json    json object
 */
JSON_INLINE
void
json_print_uglify(FILE   * __restrict ostream,
                  json_t * __restrict json) {
  json_print_ex(ostream, json, 0);
}

#endif /* json_print_h */
