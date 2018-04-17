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


#include "misc.h"
#include "themeview.h"


static const TCHAR themeview_class[] = _T(THEMEVIEW_CLASS);


typedef struct themeview_tag themeview_t;
struct themeview_tag {
    HWND win;
    HFONT font;
    const TCHAR* cls_name;
    int part_id;
    int state_id;
};


void
themeview_setup(HWND win, const WCHAR* cls_name, const WCHAR* subcls_name, int part, int state)
{
    themeview_t* tv = (themeview_t*) GetWindowLongPtr(win, 0);
    
    tv->cls_name = cls_name;
    tv->part_id = part;
    tv->state_id = state;

    SetWindowTheme(win, subcls_name, NULL);
        
    InvalidateRect(win, NULL, TRUE);
}


static void
themeview_paint(themeview_t* tv, HDC dc)
{
    HTHEME theme;
    RECT rect;
    
    if(tv->cls_name == NULL)
        return;    
    theme = OpenThemeData(tv->win, tv->cls_name);
    if(theme == NULL)
        return;
        
    GetClientRect(tv->win, &rect);
    
    SelectObject(dc, tv->font);
    
    if(IsThemeBackgroundPartiallyTransparent(theme, tv->part_id, tv->state_id))
        DrawThemeParentBackground(tv->win, dc, &rect);
    DrawThemeBackground(theme, dc, tv->part_id, tv->state_id, &rect, &rect);
    
    if(GetWindowLong(tv->win, GWL_STYLE) & THEMEVIEW_STYLE_DRAWTEXT) {
        DrawThemeText(theme, dc, tv->part_id, tv->state_id, _T("Foo Bar"), -1,
                      DT_CENTER | DT_VCENTER | DT_SINGLELINE, 0, &rect);
    }
    
    CloseThemeData(theme);
}


static LRESULT CALLBACK
themeview_proc(HWND win, UINT msg, WPARAM wp, LPARAM lp)
{
    themeview_t* tv = (themeview_t*) GetWindowLongPtr(win, 0);

    switch(msg) {
        case WM_PAINT:
        case WM_PRINTCLIENT:
        {
            HDC dc = (HDC)wp;
            PAINTSTRUCT ps;

            if(wp == 0)
                dc = BeginPaint(win, &ps);
            themeview_paint(tv, dc);
            if(wp == 0)
                EndPaint(win, &ps);
            return 0;
        }
        
        case WM_SETFONT:
            tv->font = (HFONT) wp;
            if(LOWORD(lp))
                InvalidateRect(win, NULL, TRUE);
            break;
        
        case WM_NCCREATE:
            tv = (themeview_t*) malloc(sizeof(themeview_t));
            if(tv == NULL)
                return FALSE;
            memset(tv, 0, sizeof(themeview_t));
            tv->win = win;
            SetWindowLongPtr(win, 0, (LONG_PTR)tv);
            break;
        
        case WM_NCDESTROY:
            if(tv)
                free(tv);
            break;
    }
    
    return DefWindowProc(win, msg, wp, lp);
}


void
themeview_init(void)
{
    WNDCLASS wc = { 0 };
    
    wc.style = CS_GLOBALCLASS | CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = themeview_proc;
    wc.cbWndExtra = sizeof(themeview_t*);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.hInstance = te_instance;
    wc.lpszClassName = themeview_class;
    RegisterClass(&wc);
}

