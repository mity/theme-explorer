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


#ifndef TE_MISC_H
#define TE_MISC_H

#include <malloc.h>
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


/* Some UXTHEME.DLL functions are only available since more recent Windows
 * versions. So we wrapper them to keep compatibility with Windows XP. */
HRESULT te_GetThemeBitmap(HTHEME hTheme, int iPartId, int iStateId, int iPropId, ULONG dwFlags, HBITMAP *phBitmap);
HRESULT te_GetThemeStream(HTHEME hTheme, int iPartId, int iStateId, int iPropId, void** ppvStream, DWORD *pcbStream, HINSTANCE hInst);

#define GetThemeBitmap      te_GetThemeBitmap
#define GetThemeStream      te_GetThemeStream


#endif  /* TE_MISC_H */
