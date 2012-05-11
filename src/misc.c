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

#include "misc.h"


HINSTANCE te_instance;
DWORD te_win_version;


void
te_init(HINSTANCE instance)
{
    OSVERSIONINFOEX ver;
    
    te_instance = instance;
    
    ver.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
    GetVersionEx((OSVERSIONINFO*) &ver);
    te_win_version = TE_WIN_VER(ver.dwPlatformId, ver.dwMajorVersion, ver.dwMinorVersion);
    
    InitCommonControls();
    
    themeview_init();
}



INT_PTR
te_dlgbox(const TCHAR* dlg_name, HWND parent, DLGPROC proc)
{
    HRSRC res;
    HGLOBAL glob;
    BYTE* data;
    BYTE* tmp;
    DWORD size;
    LRESULT ret;
    LOGFONTW lf = {0};
    DWORD lf_facesize;
    BYTE charset;
    
    /* Get the dialog template resource data */
    res = FindResource(te_instance, dlg_name, (const TCHAR*) RT_DIALOG);
    if(res == NULL)
        goto err;
    glob = LoadResource(te_instance, res);
    if(glob == NULL)
        goto err;
    size = SizeofResource(te_instance, res);
    data = (BYTE*) LockResource(glob);
    if(data == NULL || size <= 2)
        goto err;

    /* Determine the appropriate font */
    //GetThemeSysFont(NULL, TMT_MSGBOXFONT, &lf);
    if(te_win_version < TE_WIN_VISTA) {
        lf.lfHeight = 8;
        wcscpy(lf.lfFaceName, L"MS Shell Dlg");
    } else {
        lf.lfHeight = 9;
        wcscpy(lf.lfFaceName, L"Segoe UI");
    }
    lf_facesize = (wcslen(lf.lfFaceName) + 1) * sizeof(WCHAR);

    /* Create a temporary template with the proper font */
#define DATA_WORD(offset)    *((WORD*)(data + (offset)))
#define DATA_DWORD(offset)   *((DWORD*)(data + (offset)))
#define DATA_STRING(offset)  ((WCHAR*)(data + (offset)))
    if(size >= 26  &&  DATA_WORD(0) == 0x0001  &&  DATA_WORD(2) == 0xffff) {
        /* DLGTEMPLATEEX (see http://blogs.msdn.com/b/oldnewthing/archive/2004/06/23/163596.aspx) */
        DWORD style = DATA_DWORD(12);
        DWORD n = 26;
        DWORD skip = 0;
        
        //n += (DATA_WORD(n) == 0xffff) ? 4 : (wcslen(DATA_STRING(n)) + 1) * sizeof(WCHAR);   /* dialog menu */
        if(DATA_WORD(n) == 0xffff)
            n += 4;
        else
            n += (wcslen(DATA_STRING(n)) + 1) * sizeof(WCHAR);
        n += (wcslen(DATA_STRING(n)) + 1) * sizeof(WCHAR);                                  /* dialog class */
        n += (wcslen(DATA_STRING(n)) + 1) * sizeof(WCHAR);                                  /* dialog caption */
        
        if(style & (DS_SHELLFONT | DS_SETFONT))
            skip += 6 + (wcslen(DATA_STRING(n+6)) + 1) * sizeof(WCHAR);
        style |= DS_SHELLFONT;
        
        tmp = _malloca(size - skip + 32);
        if(tmp == NULL)
            goto err;
        
        memcpy(tmp, data, n);
        memcpy(tmp + 12, &style, 4);
        memcpy(tmp + n, (WORD*) &lf.lfHeight, 2);
        memcpy(tmp + n + 2, (WORD*) &lf.lfWeight, 2);
        memcpy(tmp + n + 4, &lf.lfItalic, 1);
        charset = 1;
        memcpy(tmp + n + 5, &charset, 1);
        memcpy(tmp + n + 6, lf.lfFaceName, lf_facesize);
        
        memcpy(tmp + n + 6 + lf_facesize, data + n + skip, size - skip - n);
    } else if(size >= 18) {
        /* DLGTEMPLATE (see http://blogs.msdn.com/b/oldnewthing/archive/2004/06/23/163596.aspx) */
        // TODO
        goto err;
    } else {
        goto err;
    }
    
    ret = DialogBoxIndirect(te_instance, (DLGTEMPLATE*)tmp, parent, proc);
    _freea(tmp);
    
    return ret;

err:
    return DialogBox(te_instance, dlg_name, parent, proc);
}
