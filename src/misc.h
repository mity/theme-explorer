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

#ifndef TE_MISC_H
#define TE_MISC_H

#include <tchar.h>
#include <windows.h>
#include <commctrl.h>
#include <uxtheme.h>


#include "resource.h"
#include "compat.h"
#include "themeview.h"


#define TE_ARRAY_SIZE(array)    (sizeof((array)) / sizeof((array)[0]))


extern HINSTANCE te_instance;
extern DWORD te_win_version;


/* Checking OS version (compare with normal operators: ==, <, <= etc.) */
#define TE_WIN_VER(platform, major, minor)                               \
    (((platform) << 16) | ((major) << 8) | ((minor) << 0))

#define TE_WIN_95          TE_WIN_VER(1, 4, 0)
#define TE_WIN_98          TE_WIN_VER(1, 4, 10)
#define TE_WIN_ME          TE_WIN_VER(1, 4, 90)
#define TE_WIN_NT4         TE_WIN_VER(2, 4, 0)
#define TE_WIN_2000        TE_WIN_VER(2, 5, 0)
#define TE_WIN_XP          TE_WIN_VER(2, 5, 1)
#define TE_WIN_S2003       TE_WIN_VER(2, 5, 2)
#define TE_WIN_VISTA       TE_WIN_VER(2, 6, 0)
#define TE_WIN_S2008       TE_WIN_VER(2, 6, 0)
#define TE_WIN_7           TE_WIN_VER(2, 6, 1)
#define TE_WIN_S2008R2     TE_WIN_VER(2, 6, 1)
#define TE_WIN_8           TE_WIN_VER(2, 6, 2)


void te_init(HINSTANCE instance);

INT_PTR te_dlgbox(const TCHAR* dlg_name, HWND parent, DLGPROC proc);




#endif  /* TE_MISC_H */
