/*
 * Theme Explorer
 * Copyright (c) 2012 Martin Mitas
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */


#ifndef TE_DB_H
#define TE_DB_H

#include "misc.h"


/******************************
 *** Classes, parts, states ***
 ******************************/
 
typedef struct db_class_tag db_class_t;
typedef struct db_part_tag db_part_t;
typedef struct db_state_tag db_state_t;

struct db_class_tag {
    const TCHAR* name;
    const TCHAR* subclass;
    const db_part_t* parts;
    int n_parts;
};

struct db_part_tag {
    int id;
    const TCHAR* name;
    const TCHAR* display_name;
    const db_state_t* states;
    int n_states;
};

struct db_state_tag {
    int id;
    const TCHAR* name;
    const TCHAR* display_name;
};

extern const db_class_t* db_classes;
extern int db_n_classes;


void db_class_display_name(const db_class_t* cls, TCHAR* buffer, UINT bufsize);


/******************
 *** Properties ***
 ******************/

typedef struct db_type_tag db_type_t;
typedef struct db_prop_tag db_prop_t;

struct db_type_tag {
    int id;
    const TCHAR* name;
    const TCHAR* display_name;
    
    void (*to_string)(HTHEME /*theme*/, int /*part*/, int /*state*/, int /*prop*/,
                      TCHAR* /*buffer*/, DWORD /*bufsize*/);
};

struct db_prop_tag {
    const db_type_t* type;
    int id;
    const TCHAR* name;
    const TCHAR* display_name;    
};

extern const db_prop_t* db_props;
extern int db_n_props;


#endif  /* TE_DB_H */
