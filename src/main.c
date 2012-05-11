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
#include "db.h"


static void
main_wm_initdialog(HWND win)
{
    /* Setup the treeview */
    {
        HWND tv_win;
        int i, j, k;
        const db_class_t* cls;
        const db_part_t* part;
        const db_state_t* state;
        TVINSERTSTRUCT tvis_class = {0};
        TVINSERTSTRUCT tvis_part = {0};
        TVINSERTSTRUCT tvis_state = {0};
        HTREEITEM handle_class;
        HTREEITEM handle_part;
        TCHAR buffer[128];
        
        tv_win = GetDlgItem(win, IDC_MAIN_TREEVIEW);
    
        tvis_class.hParent = NULL;
        tvis_class.hInsertAfter = TVI_LAST;
        tvis_class.item.mask = TVIF_PARAM | TVIF_TEXT;
        
        for(i = 0; i < db_n_classes; i++) {
            cls = &db_classes[i];
            db_class_display_name(cls, buffer, TE_ARRAY_SIZE(buffer));
    
            tvis_class.item.pszText = buffer;
            tvis_class.item.lParam = (LPARAM) cls;
            handle_class = (HTREEITEM) SendMessage(tv_win, TVM_INSERTITEM, 0, (LPARAM)&tvis_class);
            
    
            tvis_part.hParent = handle_class;
            tvis_part.hInsertAfter = TVI_LAST;
            tvis_part.item.mask = TVIF_PARAM | TVIF_TEXT;
            
            for(j = 0; j < cls->n_parts; j++) {
                part = &cls->parts[j];
    
                tvis_part.item.pszText = (TCHAR*) part->display_name;
                tvis_part.item.lParam = (LPARAM) part;
                handle_part = (HTREEITEM) SendMessage(tv_win, TVM_INSERTITEM, 0, (LPARAM)&tvis_part);
                
                
                tvis_state.hParent = handle_part;
                tvis_state.hInsertAfter = TVI_LAST;
                tvis_state.item.mask = TVIF_PARAM | TVIF_TEXT;
                
                for(k = 0; k < part->n_states; k++) {
                    state = &part->states[k];
                    
                    tvis_state.item.pszText = (TCHAR*) state->display_name;
                    tvis_state.item.lParam = (LPARAM) state;
                    SendMessage(tv_win, TVM_INSERTITEM, 0, (LPARAM)&tvis_state);
                }
            }
        }
    }
    
    /* Set font of the main labels */
    {
        HFONT font;
        LOGFONT lf;
        
        font = (HFONT) SendDlgItemMessage(win, IDC_MAIN_CLASS, WM_GETFONT, 0, 0);
        GetObject(font, sizeof(LOGFONT), &lf);
        
        lf.lfWeight+= 300;
        if(lf.lfWeight > 900)
            lf.lfWeight = 900;
        
        font = CreateFontIndirect(&lf);
        SendDlgItemMessage(win, IDC_MAIN_CLASS, WM_SETFONT, (WPARAM)font, TRUE);
        SendDlgItemMessage(win, IDC_MAIN_PART, WM_SETFONT, (WPARAM)font, TRUE);
        SendDlgItemMessage(win, IDC_MAIN_STATE, WM_SETFONT, (WPARAM)font, TRUE);
    }
    
    /* Setup list view */
    {
        RECT rect;
        LVCOLUMN col = { 0 };
        DWORD lvs_ex_style = LVS_EX_DOUBLEBUFFER | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES;
        
        GetClientRect(GetDlgItem(win, IDC_MAIN_PROPSLIST), &rect);
        
        col.mask = LVCF_TEXT | LVCF_SUBITEM | LVCF_WIDTH;
        col.pszText = _T("Type");
        col.iSubItem = 2;
        col.cx = rect.right * 10 / 100;
        SendDlgItemMessage(win, IDC_MAIN_PROPSLIST, LVM_INSERTCOLUMN, 0, (LPARAM)&col);
        col.pszText = _T("ID");
        col.iSubItem = 0;
        col.cx = rect.right * 10 / 100;
        SendDlgItemMessage(win, IDC_MAIN_PROPSLIST, LVM_INSERTCOLUMN, 1, (LPARAM)&col);
        col.pszText = _T("Property");
        col.iSubItem = 1;
        col.cx = rect.right * 30 / 100;
        SendDlgItemMessage(win, IDC_MAIN_PROPSLIST, LVM_INSERTCOLUMN, 2, (LPARAM)&col);
        col.pszText = _T("Value");
        col.iSubItem = 2;
        col.cx = rect.right * 40 / 100;
        SendDlgItemMessage(win, IDC_MAIN_PROPSLIST, LVM_INSERTCOLUMN, 3, (LPARAM)&col);
        col.pszText = _T("Origin");
        col.iSubItem = 3;
        col.cx = rect.right * 10 / 100;
        SendDlgItemMessage(win, IDC_MAIN_PROPSLIST, LVM_INSERTCOLUMN, 4, (LPARAM)&col);
        
        SendDlgItemMessage(win, IDC_MAIN_PROPSLIST, LVM_SETEXTENDEDLISTVIEWSTYLE,
                           lvs_ex_style, lvs_ex_style);
    }
}

#define TMT_DIBDATA	2
#define TMT_GLYPHDIBDATA	8
#define GBF_DIRECT      0x00000001
#define GBF_COPY        0x00000002
static HRESULT (WINAPI* fn_GetThemeBitmap)(HTHEME, int, int, int, ULONG, HBITMAP*);

static void
main_reset(HWND win, const db_class_t* cls, const db_part_t* part, const db_state_t* state)
{
    HTHEME theme;
    
    theme = OpenThemeData(win, cls->name);
    
    /* Reset titles */
    {
        TCHAR buffer[128];

        SendDlgItemMessage(win, IDC_MAIN_CLASS, WM_SETTEXT, 0, (LPARAM) cls->name);

        _sntprintf(buffer, TE_ARRAY_SIZE(buffer), _T("[%d] %s"), part->id, part->name ? part->name : _T(""));
        SendDlgItemMessage(win, IDC_MAIN_PART, WM_SETTEXT, 0, (LPARAM) buffer);

        _sntprintf(buffer, TE_ARRAY_SIZE(buffer), _T("[%d] %s"), state->id, state->name ? state->name : _T(""));
        SendDlgItemMessage(win, IDC_MAIN_STATE, WM_SETTEXT, 0, (LPARAM) buffer);
    }

    /* Reset theme preview */
    {
        HBITMAP bmp;
        int i;
        
        for(i = IDC_MAIN_THEMEVIEW_FIRST; i <= IDC_MAIN_THEMEVIEW_LAST; i++)
            themeview_setup(GetDlgItem(win, i), cls->name, part->id, state->id);

        bmp = NULL;
        if(theme  &&  fn_GetThemeBitmap)
            fn_GetThemeBitmap(theme, part->id, state->id, TMT_DIBDATA, GBF_DIRECT, &bmp);            
        SendDlgItemMessage(win, IDC_MAIN_BITMAP_BKG, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp);

        bmp = NULL;
        if(theme  &&  fn_GetThemeBitmap)
            fn_GetThemeBitmap(theme, part->id, state->id, TMT_GLYPHDIBDATA, GBF_DIRECT, &bmp);
        SendDlgItemMessage(win, IDC_MAIN_BITMAP_GLYPH, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp);
    }
    
    /* Reset properties */
    {
        int i;
        HWND lv;

        lv = GetDlgItem(win, IDC_MAIN_PROPSLIST);
        
        SendMessage(lv, WM_SETREDRAW, 0, 0);
        
        SendMessage(lv, LVM_DELETEALLITEMS, 0, 0);
    
        if(theme) {
            LVITEM item = {0};
            SendMessage(lv, LVM_SETITEMCOUNT, db_n_props, 0);
            for(i = 0; i < db_n_props; i++) {
                const db_prop_t* prop = &db_props[i];
                PROPERTYORIGIN origin;
                TCHAR buffer[256];
                
                OutputDebugString(prop->name);
                
                if(prop->id == TS_MIN  ||   prop->id == TS_TRUE  ||  prop->id == TS_DRAW) {
                    if(part->id != 0)
                        origin = PO_PART;
                    else
                        origin = PO_NOTFOUND;
                } else {
                    if(GetThemePropertyOrigin(theme, part->id, state->id, prop->id, &origin) != S_OK)
                        continue;
                }
                    
                if(origin == PO_NOTFOUND)
                    continue;

                item.iSubItem = 0;
                item.mask = LVIF_TEXT;
                item.pszText = (TCHAR*) prop->type->display_name;
                SendMessage(lv, LVM_INSERTITEM, 0, (LPARAM) &item);
                
                item.iSubItem = 1;
                item.mask = LVIF_TEXT;
                item.pszText = buffer;
                _sntprintf(buffer, TE_ARRAY_SIZE(buffer), _T("%d"), prop->id);
                SendMessage(lv, LVM_SETITEM, 0, (LPARAM) &item);
                
                item.iSubItem = 2;
                item.pszText = (TCHAR*) prop->name;
                SendMessage(lv, LVM_SETITEM, 0, (LPARAM) &item);
                
                item.iSubItem = 3;
                item.pszText = buffer;
                prop->type->to_string(theme, part->id, state->id, prop->id,
                                      buffer, TE_ARRAY_SIZE(buffer));
                SendMessage(lv, LVM_SETITEM, 0, (LPARAM) &item);

                item.iSubItem = 4;
                switch((int)origin) {
                    case PO_STATE:   item.pszText = _T("state"); break;
                    case PO_PART:    item.pszText = _T("part"); break;
                    case PO_CLASS:   item.pszText = _T("class"); break;
                    case PO_GLOBAL:  item.pszText = _T("global"); break;
                    default:         item.pszText = _T("?"); break;
                }
                SendMessage(lv, LVM_SETITEM, 0, (LPARAM) &item);
                
                item.iItem++;
            }
        }
        
        SendMessage(lv, WM_SETREDRAW, 1, 0);
        InvalidateRect(lv, NULL, TRUE);
    }
    
    CloseThemeData(theme);
}

static void
main_treeview_wm_notify(HWND win, NMHDR* hdr)
{
    static const db_class_t cls_null = {0};
    static const db_part_t part_null = {0};
    static const db_state_t state_null = {0};
    
    if(hdr->code == TVN_SELCHANGED) {
        int n = 0;
        NM_TREEVIEW* nm = (NM_TREEVIEW*) hdr;
        HTREEITEM h;
        void* ptr[3];
        const db_class_t* cls;
        const db_part_t* part;
        const db_state_t* state;
        
        for(h = nm->itemNew.hItem;
            h != NULL && n < 3;
            h = (HTREEITEM) SendDlgItemMessage(win, IDC_MAIN_TREEVIEW, TVM_GETNEXTITEM, TVGN_PARENT, (LPARAM)h))
        {
            TVITEM item;
            item.mask = TVIF_HANDLE | TVIF_PARAM;
            item.hItem = h;
            
            SendDlgItemMessage(win, IDC_MAIN_TREEVIEW, TVM_GETITEM, 0, (LPARAM)&item);
            ptr[n] = (void*)item.lParam;
            n++;
        }
        
        cls = (n >= 1  ?  (const db_class_t*)ptr[n - 1]  :  &cls_null);
        part = (n >= 2  ?  (const db_part_t*)ptr[n - 2]  :  &part_null);
        state = (n >= 3  ?  (const db_state_t*)ptr[n - 3] :  &state_null);
        
        main_reset(win, cls, part, state);
    }
}


static void
main_wm_command(HWND win, UINT ctl_id)
{
    switch(ctl_id) {
        case IDM_FILE_EXIT:
            EndDialog(win, 0);
            break;
    }
}


static WORD old_w = 0;
static WORD old_h = 0;

static INT_PTR CALLBACK
main_proc(HWND win, UINT msg, WPARAM wp, LPARAM lp)
{
    switch(msg) {
        case WM_NOTIFY:
            switch(wp) {
                case IDC_MAIN_TREEVIEW:
                    main_treeview_wm_notify(win, (NMHDR*) lp);
                    break;
            }
            break;
        
        case WM_SIZE:
            if(wp == SIZE_MAXIMIZED || wp == SIZE_RESTORED) {
                WORD w = LOWORD(lp);
                WORD h = HIWORD(lp);
                
                if(old_w != 0 && old_h != 0) {
                    RECT rect;
                    
                    GetWindowRect(GetDlgItem(win, IDC_MAIN_TREEVIEW), &rect);
                    MapWindowPoints(NULL, win, (POINT*)&rect, 2);
                    SetWindowPos(GetDlgItem(win, IDC_MAIN_TREEVIEW), NULL,
                                 rect.left, rect.top, rect.right - rect.left,
                                 rect.bottom - rect.top + h - old_h,
                                 SWP_NOZORDER);

                    GetWindowRect(GetDlgItem(win, IDC_MAIN_PROPSLIST), &rect);
                    MapWindowPoints(NULL, win, (POINT*)&rect, 2);
                    SetWindowPos(GetDlgItem(win, IDC_MAIN_PROPSLIST), NULL,
                                 rect.left, rect.top,
                                 rect.right - rect.left + w - old_w,
                                 rect.bottom - rect.top + h - old_h,
                                 SWP_NOZORDER | SWP_NOMOVE);
                }
                
                old_w = w;
                old_h = h;
            }
            break;
        
        case WM_COMMAND:
            main_wm_command(win, LOWORD(wp));
            break;
        
        case WM_INITDIALOG:
            main_wm_initdialog(win);
            return TRUE;

        case WM_CLOSE:
            EndDialog(win, 0);
            break;
            
        default:
            return FALSE;
    }
    
    return TRUE;
}


int APIENTRY
WinMain(HINSTANCE instance, HINSTANCE instance_prev, LPSTR cmd_line, int cmd_show)
{
    HMODULE dll;
    
    dll = GetModuleHandle(_T("uxtheme.dll"));
    if(dll)
        fn_GetThemeBitmap = (HRESULT(WINAPI *)(HTHEME, int, int, int, ULONG, HBITMAP*))
                                    GetProcAddress(dll, "GetThemeBitmap");
    else
        fn_GetThemeBitmap = NULL;

    te_init(instance);
    
    //DialogBox(te_instance, MAKEINTRESOURCE(IDD_MAIN), NULL, main_proc);
    te_dlgbox(MAKEINTRESOURCE(IDD_MAIN), NULL, main_proc);
    
    return 0;
}
