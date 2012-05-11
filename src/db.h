/*
 * Copyright (c) 2012 Martin Mitas
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
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
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

const db_class_t* db_classes;
int db_n_classes;


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

const db_prop_t* db_props;
int db_n_props;


#endif  /* TE_DB_H */
