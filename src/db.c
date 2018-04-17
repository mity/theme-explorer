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


#include "db.h"


/* This database is an union from MS SDK 7.1 headers and following MSDN pages:
 *  - http://msdn.microsoft.com/en-us/library/windows/desktop/bb773210%28v=vs.85%29.aspx
 *  - http://msdn.microsoft.com/en-us/library/windows/desktop/ee453680%28v=vs.85%29.aspx
 *  - http://msdn.microsoft.com/en-us/library/windows/desktop/bb773218%28v=vs.85%29.aspx
 */


#define DB_DEFINE_CLASS(name, parts)                     { _T(#name), NULL, parts, TE_ARRAY_SIZE(parts) }
#define DB_DEFINE_SUBCLASS(name, subname, parts)         { _T(#name), _T(#subname), parts, TE_ARRAY_SIZE(parts) }
#define DB_DEFINE_PART(id, name, display_name, states)   { id, _T(#name), _T(#display_name), states, TE_ARRAY_SIZE(states) }
#define DB_DEFINE_PART_(id, name, display_name)          { id, _T(#name), _T(#display_name), NULL, 0 }
#define DB_DEFINE_STATE(id, name, display_name)          { id, _T(#name), _T(#display_name) }



/******************
 *** AdressBand ***
 ******************/

static const db_state_t db_states_ABBACKGROUND[] = {
    DB_DEFINE_STATE ( 1,  xxx_NORMAL,    Normal),
    DB_DEFINE_STATE ( 2,  xxx_HOT,       Hot),
    DB_DEFINE_STATE ( 3,  xxx_DISABLED,  Disabled),
    DB_DEFINE_STATE ( 4,  xxx_FOCUSED,   Focused)
};

static const db_part_t db_parts_ADDRESSBAND[] = {
    DB_DEFINE_PART  ( 1,  ABBACKGROUND,  Background,  db_states_ABBACKGROUND)
};


/******************
 *** AeroWizard ***
 ******************/

static const db_state_t db_states_AW_CONTENTAREA[] = {
    DB_DEFINE_STATE ( 1,  AW_S_CONTENTAREA_NOMARGIN,  NoMargin)
};

static const db_state_t db_states_AW_HEADERAREA[] = {
    DB_DEFINE_STATE ( 1,  AW_S_HEADERAREA_NOMARGIN,  NoMargin)
};

static const db_state_t db_states_AW_TITLEBAR[] = {
    DB_DEFINE_STATE ( 1,  AW_S_TITLEBAR_ACTIVE,    Active),
    DB_DEFINE_STATE ( 2,  AW_S_TITLEBAR_INACTIVE,  Inactive)
};

static const db_part_t db_parts_AEROWIZARD[] = {
    DB_DEFINE_PART  ( 1,  AW_TITLEBAR,     TitleBar,     db_states_AW_TITLEBAR),
    DB_DEFINE_PART  ( 2,  AW_HEADERAREA,   HeaderArea,   db_states_AW_HEADERAREA),
    DB_DEFINE_PART  ( 3,  AW_CONTENTAREA,  ContentArea,  db_states_AW_CONTENTAREA),
    DB_DEFINE_PART_ ( 4,  AW_COMMANDAREA,  CommandArea),
    DB_DEFINE_PART_ ( 5,  AW_BUTTON,       Button),  /* TODO: try like button */
};


/**************
 *** Button ***
 **************/

static const db_state_t db_states_BP_PUSHBUTTON[] = {
    DB_DEFINE_STATE ( 1,  PBS_NORMAL,               Normal),
    DB_DEFINE_STATE ( 2,  PBS_HOT,                  Hot),
    DB_DEFINE_STATE ( 3,  PBS_PRESSED,              Pressed),
    DB_DEFINE_STATE ( 4,  PBS_DISABLED,             Disabled),
    DB_DEFINE_STATE ( 5,  PBS_DEFAULTED,            Defaulted),
    DB_DEFINE_STATE ( 6,  PBS_DEFAULTED_ANIMATING,  DefaultedAnimating)
};

static const db_state_t db_states_BP_RADIOBUTTON[] = {
    DB_DEFINE_STATE ( 1,  RBS_UNCHECKEDNORMAL,    UncheckedNormal),
    DB_DEFINE_STATE ( 2,  RBS_UNCHECKEDHOT,       UncheckedHot),
    DB_DEFINE_STATE ( 3,  RBS_UNCHECKEDPRESSED,   UncheckedPressed),
    DB_DEFINE_STATE ( 4,  RBS_UNCHECKEDDISABLED,  UncheckedDisabled),
    DB_DEFINE_STATE ( 5,  RBS_CHECKEDNORMAL,      CheckedNormal),
    DB_DEFINE_STATE ( 6,  RBS_CHECKEDHOT,         CheckedHot),
    DB_DEFINE_STATE ( 7,  RBS_CHECKEDPRESSED,     CheckedPressed),
    DB_DEFINE_STATE ( 8,  RBS_CHECKEDDISABLED,    CheckedDisabled)
};

static const db_state_t db_states_BP_CHECKBOX[] = {
    DB_DEFINE_STATE ( 1,  CBS_UNCHECKEDNORMAL,    UncheckedNormal),
    DB_DEFINE_STATE ( 2,  CBS_UNCHECKEDHOT,       UncheckedHot),
    DB_DEFINE_STATE ( 3,  CBS_UNCHECKEDPRESSED,   UncheckedPressed),
    DB_DEFINE_STATE ( 4,  CBS_UNCHECKEDDISABLED,  UncheckedDisabled),
    DB_DEFINE_STATE ( 5,  CBS_CHECKEDNORMAL,      CheckedNormal),
    DB_DEFINE_STATE ( 6,  CBS_CHECKEDHOT,         CheckedHot),
    DB_DEFINE_STATE ( 7,  CBS_CHECKEDPRESSED,     CheckedPressed),
    DB_DEFINE_STATE ( 8,  CBS_CHECKEDDISABLED,    CheckedDisabled),
    DB_DEFINE_STATE ( 9,  CBS_MIXEDNORMAL,        MixedNormal),
    DB_DEFINE_STATE (10,  CBS_MIXEDHOT,           MixedHot),
    DB_DEFINE_STATE (11,  CBS_MIXEDPRESSED,       MixedPressed),
    DB_DEFINE_STATE (12,  CBS_MIXEDDISABLED,      MixedDisabled),
    DB_DEFINE_STATE (13,  CBS_IMPLICITNORMAL,     ImplicitNormal),
    DB_DEFINE_STATE (14,  CBS_IMPLICITHOT,        ImplicitHot),
    DB_DEFINE_STATE (15,  CBS_IMPLICITPRESSED,    ImplicitPressed),
    DB_DEFINE_STATE (16,  CBS_IMPLICITDISABLED,   ImplicitDisabled),
    DB_DEFINE_STATE (17,  CBS_EXCLUDEDNORMAL,     ExcludedNormal),
    DB_DEFINE_STATE (18,  CBS_EXCLUDEDHOT,        ExcludedHot),
    DB_DEFINE_STATE (19,  CBS_EXCLUDEDPRESSED,    ExcludedPressed),
    DB_DEFINE_STATE (20,  CBS_EXCLUDEDDISABLED,   ExcludedDisabled)
};

static const db_state_t db_states_BP_GROUPBOX[] = {
    DB_DEFINE_STATE ( 1,  GBS_NORMAL,    Normal),
    DB_DEFINE_STATE ( 2,  GBS_DISABLED,  Disabled)
};

static const db_state_t db_states_BP_COMMANDLINK[] = {
    DB_DEFINE_STATE ( 1,  CMDLS_NORMAL,               Normal),
    DB_DEFINE_STATE ( 2,  CMDLS_HOT,                  Hot),
    DB_DEFINE_STATE ( 3,  CMDLS_PRESSED,              Pressed),
    DB_DEFINE_STATE ( 4,  CMDLS_DISABLED,             Disabled),
    DB_DEFINE_STATE ( 5,  CMDLS_DEFAULTED,            Defaulted),
    DB_DEFINE_STATE ( 6,  CMDLS_DEFAULTED_ANIMATING,  DefaultedAnimating)
};

static const db_state_t db_states_BP_COMMANDLINKGLYPH[] = {
    DB_DEFINE_STATE ( 1,  CMDLGS_NORMAL,     Normal),
    DB_DEFINE_STATE ( 2,  CMDLGS_HOT,        Hot),
    DB_DEFINE_STATE ( 3,  CMDLGS_PRESSED,    Pressed),
    DB_DEFINE_STATE ( 4,  CMDLGS_DISABLED,   Disabled),
    DB_DEFINE_STATE ( 5,  CMDLGS_DEFAULTED,  Defaulted)
};

static const db_part_t db_parts_BUTTON[] = {
    DB_DEFINE_PART  ( 1,  BP_PUSHBUTTON,        PushButton,        db_states_BP_PUSHBUTTON),
    DB_DEFINE_PART  ( 2,  BP_RADIOBUTTON,       RadioButton,       db_states_BP_RADIOBUTTON),
    DB_DEFINE_PART  ( 3,  BP_CHECKBOX,          CheckBox,          db_states_BP_CHECKBOX),
    DB_DEFINE_PART  ( 4,  BP_GROUPBOX,          GroupBox,          db_states_BP_GROUPBOX),
    DB_DEFINE_PART_ ( 5,  BP_USERBUTTON,        UserButton),
    DB_DEFINE_PART  ( 6,  BP_COMMANDLINK,       CommandLink,       db_states_BP_COMMANDLINK),
    DB_DEFINE_PART  ( 7,  BP_COMMANDLINKGLYPH,  CommandLinkGlyph,  db_states_BP_COMMANDLINKGLYPH)
};


/*************
 *** Clock ***
 *************/

static const db_state_t db_states_CLP_TIME[] = {
    DB_DEFINE_STATE ( 1,  CLS_NORMAL,   Normal),
    DB_DEFINE_STATE ( 2,  CLS_HOT,      Hot),
    DB_DEFINE_STATE ( 3,  CLS_PRESSED,  Pressed)
};

static const db_part_t db_parts_CLOCK[] = {
    DB_DEFINE_PART  ( 1,  CLP_TIME,  Time,  db_states_CLP_TIME)
};


/****************
 *** ComboBox ***
 ****************/

static const db_state_t db_states_CP_DROPDOWNBUTTON[] = {
    DB_DEFINE_STATE ( 1,  CBXS_NORMAL,    Normal),
    DB_DEFINE_STATE ( 2,  CBXS_HOT,       Hot),
    DB_DEFINE_STATE ( 3,  CBXS_PRESSED,   Pressed),
    DB_DEFINE_STATE ( 4,  CBXS_DISABLED,  Disabled)
};

static const db_state_t db_states_CP_BORDER[] = {
    DB_DEFINE_STATE ( 1,  CBB_NORMAL,    Normal),
    DB_DEFINE_STATE ( 2,  CBB_HOT,       Hot),
    DB_DEFINE_STATE ( 3,  CBB_FOCUSED,   Focused),
    DB_DEFINE_STATE ( 4,  CBB_DISABLED,  Disabled)
};

static const db_state_t db_states_CP_READONLY[] = {
    DB_DEFINE_STATE ( 1,  CBRO_NORMAL,    Normal),
    DB_DEFINE_STATE ( 2,  CBRO_HOT,       Hot),
    DB_DEFINE_STATE ( 3,  CBRO_PRESSED,   Pressed),
    DB_DEFINE_STATE ( 4,  CBRO_DISABLED,  Disabled)
};

static const db_state_t db_states_CP_DROPDOWNBUTTONRIGHT[] = {
    DB_DEFINE_STATE ( 1,  CBXSR_NORMAL,    Normal),
    DB_DEFINE_STATE ( 2,  CBXSR_HOT,       Hot),
    DB_DEFINE_STATE ( 3,  CBXSR_PRESSED,   Pressed),
    DB_DEFINE_STATE ( 4,  CBXSR_DISABLED,  Disabled)
};

static const db_state_t db_states_CP_DROPDOWNBUTTONLEFT[] = {
    DB_DEFINE_STATE ( 1,  CBXSL_NORMAL,    Normal),
    DB_DEFINE_STATE ( 2,  CBXSL_HOT,       Hot),
    DB_DEFINE_STATE ( 3,  CBXSL_PRESSED,   Pressed),
    DB_DEFINE_STATE ( 4,  CBXSL_DISABLED,  Disabled)
};

static const db_state_t db_states_CP_CUEBANNER[] = {
    DB_DEFINE_STATE ( 1,  CBCB_NORMAL,    Normal),
    DB_DEFINE_STATE ( 2,  CBCB_HOT,       Hot),
    DB_DEFINE_STATE ( 3,  CBCB_PRESSED,   Pressed),
    DB_DEFINE_STATE ( 4,  CBCB_DISABLED,  Disabled)
};

static const db_part_t db_parts_COMBOBOX[] = {
    DB_DEFINE_PART  ( 1,  CP_DROPDOWNBUTTON,         DropDownButton,         db_states_CP_DROPDOWNBUTTON),
    DB_DEFINE_PART_ ( 2,  CP_BACKGROUND,             Background),
    DB_DEFINE_PART_ ( 3,  CP_TRANSPARENTBACKGROUND,  TransparentBackground),
    DB_DEFINE_PART  ( 4,  CP_BORDER,                 Border,                 db_states_CP_BORDER),
    DB_DEFINE_PART  ( 5,  CP_READONLY,               ReadOnly,               db_states_CP_READONLY),
    DB_DEFINE_PART  ( 6,  CP_DROPDOWNBUTTONRIGHT,    DropDownButtonRight,    db_states_CP_DROPDOWNBUTTONRIGHT),
    DB_DEFINE_PART  ( 7,  CP_DROPDOWNBUTTONLEFT,     DropDownButtonLeft,     db_states_CP_DROPDOWNBUTTONLEFT),
    DB_DEFINE_PART  ( 8,  CP_CUEBANNER,              CueBanner,              db_states_CP_CUEBANNER)
};


/**********************
 *** Communications ***
 **********************/

static const db_state_t db_states_CSST_TAB[] = {
    DB_DEFINE_STATE ( 1,  CSTB_NORMAL,    Normal),
    DB_DEFINE_STATE ( 2,  CSTB_HOT,       Hot),
    DB_DEFINE_STATE ( 3,  CSTB_SELECTED,  Selected)
};

static const db_part_t db_parts_COMMUNICATIONS[] = {
    DB_DEFINE_PART  ( 1,  CSST_TAB,  Tab,  db_states_CSST_TAB)
};

/********************
 *** ControlPanel ***
 ********************/

static const db_state_t db_states_CPANEL_HELPLINK[] = {
    DB_DEFINE_STATE ( 1,  CPHL_NORMAL,    Normal),
    DB_DEFINE_STATE ( 2,  CPHL_HOT,       Hot),
    DB_DEFINE_STATE ( 3,  CPHL_PRESSED,   Pressed),
    DB_DEFINE_STATE ( 4,  CPHL_DISABLED,  Disabled)
};

static const db_state_t db_states_CPANEL_TASKLINK[] = {
    DB_DEFINE_STATE ( 1,  CPTL_NORMAL,    Normal),
    DB_DEFINE_STATE ( 2,  CPTL_HOT,       Hot),
    DB_DEFINE_STATE ( 3,  CPTL_PRESSED,   Pressed),
    DB_DEFINE_STATE ( 4,  CPTL_DISABLED,  Disabled),
    DB_DEFINE_STATE ( 5,  CPTL_PAGE,      Page)
};

static const db_state_t db_states_CPANEL_CONTENTLINK[] = {
    DB_DEFINE_STATE ( 1,  CPCL_NORMAL,    Normal),
    DB_DEFINE_STATE ( 2,  CPCL_HOT,       Hot),
    DB_DEFINE_STATE ( 3,  CPCL_PRESSED,   Pressed),
    DB_DEFINE_STATE ( 4,  CPCL_DISABLED,  Disabled)
};

static const db_state_t db_states_CPANEL_SECTIONTITLELINK[] = {
    DB_DEFINE_STATE ( 1,  CPSTL_NORMAL,  Normal),
    DB_DEFINE_STATE ( 2,  CPSTL_HOT,     Hot)
};

static const db_part_t db_parts_CONTROLPANEL[] = {
    DB_DEFINE_PART_ ( 1, CPANEL_NAVIGATIONPANE,       NavigationPane),
    DB_DEFINE_PART_ ( 2, CPANEL_CONTENTPANE,          ContentPane),
    DB_DEFINE_PART_ ( 3, CPANEL_NAVIGATIONPANELABEL,  NavigationPaneLabel),
    DB_DEFINE_PART_ ( 4, CPANEL_CONTENTPANELABEL,     ContentPaneLabel),
    DB_DEFINE_PART_ ( 5, CPANEL_TITLE,                Title),
    DB_DEFINE_PART_ ( 6, CPANEL_BODYTEXT,             BodyText),
    DB_DEFINE_PART  ( 7, CPANEL_HELPLINK,             HelpLink,             db_states_CPANEL_HELPLINK),
    DB_DEFINE_PART  ( 8, CPANEL_TASKLINK,             TaskLink,             db_states_CPANEL_TASKLINK),
    DB_DEFINE_PART_ ( 9, CPANEL_GROUPTEXT,            GroupText),
    DB_DEFINE_PART  (10, CPANEL_CONTENTLINK,          ContentLink,          db_states_CPANEL_CONTENTLINK),
    DB_DEFINE_PART  (11, CPANEL_SECTIONTITLELINK,     SectionTitleLink,     db_states_CPANEL_SECTIONTITLELINK),
    DB_DEFINE_PART_ (12, CPANEL_LARGECOMMANDAREA,     LargeCommandArea),
    DB_DEFINE_PART_ (13, CPANEL_SMALLCOMMANDAREA,     SmallCommandArea),
    DB_DEFINE_PART_ (14, CPANEL_BUTTON,               Button),
    DB_DEFINE_PART_ (15, CPANEL_MESSAGETEXT,          MessageText),
    DB_DEFINE_PART_ (16, CPANEL_NAVIGATIONPANELINE,   NavigationPaneLine),
    DB_DEFINE_PART_ (17, CPANEL_CONTENTPANELINE,      ContentPaneline),
    DB_DEFINE_PART_ (18, CPANEL_BANNERAREA,           BannerArea),
    DB_DEFINE_PART_ (19, CPANEL_BODYTITLE,            BodyTitle)
};


/******************
 *** DatePicker ***
 ******************/

static const db_state_t db_states_DP_DATETEXT[] = {
    DB_DEFINE_STATE ( 1,  DPDT_NORMAL,    Normal),
    DB_DEFINE_STATE ( 2,  DPDT_DISABLED,  Disabled),
    DB_DEFINE_STATE ( 3,  DPDT_SELECTED,  Selected)
};

static const db_state_t db_states_DP_DATEBORDER[] = {
    DB_DEFINE_STATE ( 1,  DPDB_NORMAL,    Normal),
    DB_DEFINE_STATE ( 2,  DPDB_HOT,       Hot),
    DB_DEFINE_STATE ( 3,  DPDB_FOCUSED,   Focused),
    DB_DEFINE_STATE ( 4,  DPDB_DISABLED,  Disabled)
};

static const db_state_t db_states_DP_SHOWCALENDARBUTTONRIGHT[] = {
    DB_DEFINE_STATE ( 1,  DPSCBR_NORMAL,    Normal),
    DB_DEFINE_STATE ( 2,  DPSCBR_HOT,       Hot),
    DB_DEFINE_STATE ( 3,  DPSCBR_PRESSED,   Pressed),
    DB_DEFINE_STATE ( 4,  DPSCBR_DISABLED,  Disabled)
};

static const db_part_t db_parts_DATEPICKER[] = {
    DB_DEFINE_PART  ( 1,  DP_DATETEXT,                 DateText,                 db_states_DP_DATETEXT),
    DB_DEFINE_PART  ( 2,  DP_DATEBORDER,               DateBorder,               db_states_DP_DATEBORDER),
    DB_DEFINE_PART  ( 3,  DP_SHOWCALENDARBUTTONRIGHT,  ShowCalendarButtonRight,  db_states_DP_SHOWCALENDARBUTTONRIGHT)
};


/****************
 *** DragDrop ***
 ****************/

static const db_state_t db_states_DD_COPY[] = {
    DB_DEFINE_STATE ( 1,  DDCOPY_HIGHLIGHT,    Highlight),
    DB_DEFINE_STATE ( 2,  DDCOPY_NOHIGHLIGHT,  NonHighlight)
};

static const db_state_t db_states_DD_MOVE[] = {
    DB_DEFINE_STATE ( 1,  DDMOVE_HIGHLIGHT,    Highlight),
    DB_DEFINE_STATE ( 2,  DDMOVE_NOHIGHLIGHT,  NonHighlight)
};

static const db_state_t db_states_DD_UPDATEMETADATA[] = {
    DB_DEFINE_STATE ( 1,  DDUPDATEMETADATA_HIGHLIGHT,    Highlight),
    DB_DEFINE_STATE ( 2,  DDUPDATEMETADATA_NOHIGHLIGHT,  NonHighlight)
};

static const db_state_t db_states_DD_CREATELINK[] = {
    DB_DEFINE_STATE ( 1,  DDCREATELINK_HIGHLIGHT,    Highlight),
    DB_DEFINE_STATE ( 2,  DDCREATELINK_NOHIGHLIGHT,  NonHighlight)
};

static const db_state_t db_states_DD_WARNING[] = {
    DB_DEFINE_STATE ( 1,  DDWARNING_HIGHLIGHT,    Highlight),
    DB_DEFINE_STATE ( 2,  DDWARNING_NOHIGHLIGHT,  NonHighlight)
};

static const db_state_t db_states_DD_NONE[] = {
    DB_DEFINE_STATE ( 1,  DDNONE_HIGHLIGHT,    Highlight),
    DB_DEFINE_STATE ( 2,  DDNONE_NOHIGHLIGHT,  NonHighlight)
};

static const db_part_t db_parts_DRAGDROP[] = {
    DB_DEFINE_PART  ( 1,  DD_COPY,            Copy,            db_states_DD_COPY),
    DB_DEFINE_PART  ( 2,  DD_MOVE,            Move,            db_states_DD_MOVE),
    DB_DEFINE_PART  ( 3,  DD_UPDATEMETADATA,  UpdateMetaData,  db_states_DD_UPDATEMETADATA),
    DB_DEFINE_PART  ( 4,  DD_CREATELINK,      CreateLink,      db_states_DD_CREATELINK),
    DB_DEFINE_PART  ( 5,  DD_WARNING,         Warning,         db_states_DD_WARNING),
    DB_DEFINE_PART  ( 6,  DD_NONE,            None,            db_states_DD_NONE),
    DB_DEFINE_PART_ ( 7,  DD_IMAGEBG,         ImageBg),
    DB_DEFINE_PART_ ( 8,  DD_TEXTBG,          TextBg)
};


/************
 *** Edit ***
 ************/

static const db_state_t db_states_EP_EDITTEXT[] = {
    DB_DEFINE_STATE ( 1,  ETS_NORMAL,     Normal),
    DB_DEFINE_STATE ( 2,  ETS_HOT,        Hot),
    DB_DEFINE_STATE ( 3,  ETS_SELECTED,   Selected),
    DB_DEFINE_STATE ( 3,  ETS_DISABLED,   Disabled),
    DB_DEFINE_STATE ( 4,  ETS_FOCUSED,    Focused),
    DB_DEFINE_STATE ( 5,  ETS_READONLY,   ReadOnly),
    DB_DEFINE_STATE ( 6,  ETS_ASSIST,     Assist),
    DB_DEFINE_STATE ( 7,  ETS_CUEBANNER,  CueBanner)
};

static const db_state_t db_states_EP_BACKGROUND[] = {
    DB_DEFINE_STATE ( 1,  EBS_NORMAL,    Normal),
    DB_DEFINE_STATE ( 2,  EBS_HOT,       Hot),
    DB_DEFINE_STATE ( 3,  EBS_DISABLED,  Disabled),
    DB_DEFINE_STATE ( 4,  EBS_FOCUSED,   Focused),
    DB_DEFINE_STATE ( 5,  EBS_READONLY,  ReadOnly),
    DB_DEFINE_STATE ( 6,  EBS_ASSIST,    Assist)
};

static const db_state_t db_states_EP_BACKGROUNDWITHBORDER[] = {
    DB_DEFINE_STATE ( 1,  EBWBS_NORMAL,    Normal),
    DB_DEFINE_STATE ( 2,  EBWBS_HOT,       Hot),
    DB_DEFINE_STATE ( 3,  EBWBS_DISABLED,  Disabled),
    DB_DEFINE_STATE ( 4,  EBWBS_FOCUSED,   Focused)
};

static const db_state_t db_states_EP_EDITBORDER_NOSCROLL[] = {
    DB_DEFINE_STATE ( 1,  EPSN_NORMAL,    Normal),
    DB_DEFINE_STATE ( 2,  EPSN_HOT,       Hot),
    DB_DEFINE_STATE ( 3,  EPSN_FOCUSED,   Focused),
    DB_DEFINE_STATE ( 4,  EPSN_DISABLED,  Disabled)
};

static const db_state_t db_states_EP_EDITBORDER_HSCROLL[] = {
    DB_DEFINE_STATE ( 1,  EPSH_NORMAL,    Normal),
    DB_DEFINE_STATE ( 2,  EPSH_HOT,       Hot),
    DB_DEFINE_STATE ( 3,  EPSH_FOCUSED,   Focused),
    DB_DEFINE_STATE ( 4,  EPSH_DISABLED,  Disabled)
};

static const db_state_t db_states_EP_EDITBORDER_VSCROLL[] = {
    DB_DEFINE_STATE ( 1,  EPSV_NORMAL,    Normal),
    DB_DEFINE_STATE ( 2,  EPSV_HOT,       Hot),
    DB_DEFINE_STATE ( 3,  EPSV_FOCUSED,   Focused),
    DB_DEFINE_STATE ( 4,  EPSV_DISABLED,  Disabled)
};

static const db_state_t db_states_EP_EDITBORDER_HVSCROLL[] = {
    DB_DEFINE_STATE ( 1,  EPSHV_NORMAL,    Normal),
    DB_DEFINE_STATE ( 2,  EPSHV_HOT,       Hot),
    DB_DEFINE_STATE ( 3,  EPSHV_FOCUSED,   Focused),
    DB_DEFINE_STATE ( 4,  EPSHV_DISABLED,  Disabled)
};

static const db_part_t db_parts_EDIT[] = {
    DB_DEFINE_PART  ( 1,  EP_EDITTEXT,              EditText,              db_states_EP_EDITTEXT),
    DB_DEFINE_PART_ ( 2,  EP_CARET,                 Caret),
    DB_DEFINE_PART  ( 3,  EP_BACKGROUND,            Background,            db_states_EP_BACKGROUND),
    DB_DEFINE_PART_ ( 4,  EP_PASSWORD,              Password),
    DB_DEFINE_PART  ( 5,  EP_BACKGROUNDWITHBORDER,  BackgroundWithBorder,  db_states_EP_BACKGROUNDWITHBORDER),
    DB_DEFINE_PART  ( 6,  EP_EDITBORDER_NOSCROLL,   EditBorder_NoScroll,   db_states_EP_EDITBORDER_NOSCROLL),
    DB_DEFINE_PART  ( 7,  EP_EDITBORDER_HSCROLL,    EditBorder_HScroll,    db_states_EP_EDITBORDER_HSCROLL),
    DB_DEFINE_PART  ( 8,  EP_EDITBORDER_VSCROLL,    EditBorder_VScroll,    db_states_EP_EDITBORDER_VSCROLL),
    DB_DEFINE_PART  ( 9,  EP_EDITBORDER_HVSCROLL,   EditBorder_HVScroll,   db_states_EP_EDITBORDER_HVSCROLL),
};


/*******************
 *** EmptyMarkup ***
 *******************/

static const db_state_t db_states_EMP_MARKUPTEXT[] = {
    DB_DEFINE_STATE ( 1,  EMT_NORMALTEXT,  NormalText),
    DB_DEFINE_STATE ( 2,  EMT_LINKTEXT,    LinkText)
};

static const db_part_t db_parts_EMPTYMARKUP[] = {
    DB_DEFINE_PART  ( 1,  EMP_MARKUPTEXT,  MarkupText,  db_states_EMP_MARKUPTEXT)
};


/*******************
 *** ExplorerBar ***
 *******************/

static const db_state_t db_states_EBP_HEADERCLOSE[] = {
    DB_DEFINE_STATE ( 1,  EBHC_NORMAL,   Normal),
    DB_DEFINE_STATE ( 2,  EBHC_HOT,      Hot),
    DB_DEFINE_STATE ( 3,  EBHC_PRESSED,  Pressed)
};

static const db_state_t db_states_EBP_HEADERPIN[] = {
    DB_DEFINE_STATE ( 1,  EBHP_NORMAL,           Normal),
    DB_DEFINE_STATE ( 2,  EBHP_HOT,              Hot),
    DB_DEFINE_STATE ( 3,  EBHP_PRESSED,          Pressed),
    DB_DEFINE_STATE ( 4,  EBHP_SELECTEDNORMAL,   SelectedNormal),
    DB_DEFINE_STATE ( 5,  EBHP_SELECTEDHOT,      SelectedHot),
    DB_DEFINE_STATE ( 6,  EBHP_SELECTEDPRESSED,  SelectedPressed)
};

static const db_state_t db_states_EBP_IEBARMENU[] = {
    DB_DEFINE_STATE ( 1,  EBM_NORMAL,   Normal),
    DB_DEFINE_STATE ( 2,  EBM_HOT,      Hot),
    DB_DEFINE_STATE ( 3,  EBM_PRESSED,  Pressed)
};

static const db_state_t db_states_EBP_NORMALGROUPCOLLAPSE[] = {
    DB_DEFINE_STATE ( 1,  EBNGC_NORMAL,   Normal),
    DB_DEFINE_STATE ( 2,  EBNGC_HOT,      Hot),
    DB_DEFINE_STATE ( 3,  EBNGC_PRESSED,  Pressed)
};

static const db_state_t db_states_EBP_NORMALGROUPEXPAND[] = {
    DB_DEFINE_STATE ( 1,  EBNGE_NORMAL,   Normal),
    DB_DEFINE_STATE ( 2,  EBNGE_HOT,      Hot),
    DB_DEFINE_STATE ( 3,  EBNGE_PRESSED,  Pressed)
};

static const db_state_t db_states_EBP_SPECIALGROUPCOLLAPSE[] = {
    DB_DEFINE_STATE ( 1,  EBSGC_NORMAL,   Normal),
    DB_DEFINE_STATE ( 2,  EBSGC_HOT,      Hot),
    DB_DEFINE_STATE ( 3,  EBSGC_PRESSED,  Pressed)
};

static const db_state_t db_states_EBP_SPECIALGROUPEXPAND[] = {
    DB_DEFINE_STATE ( 1,  EBSGE_NORMAL,   Normal),
    DB_DEFINE_STATE ( 2,  EBSGE_HOT,      Hot),
    DB_DEFINE_STATE ( 3,  EBSGE_PRESSED,  Pressed)
};

static const db_part_t db_parts_EXPLORERBAR[] = {
    DB_DEFINE_PART_ ( 1,  EBP_HEADERBACKGROUND,        HeaderBackground),
    DB_DEFINE_PART  ( 2,  EBP_HEADERCLOSE,             HeaderClose,             db_states_EBP_HEADERCLOSE),
    DB_DEFINE_PART  ( 3,  EBP_HEADERPIN,               HeaderPin,               db_states_EBP_HEADERPIN),
    DB_DEFINE_PART  ( 4,  EBP_IEBARMENU,               HeaderIEBarMenu,         db_states_EBP_IEBARMENU),
    DB_DEFINE_PART_ ( 5,  EBP_NORMALGROUPBACKGROUND,   NormalGroupBackground),
    DB_DEFINE_PART  ( 6,  EBP_NORMALGROUPCOLLAPSE,     NormalGroupCollapse,     db_states_EBP_NORMALGROUPCOLLAPSE),
    DB_DEFINE_PART  ( 7,  EBP_NORMALGROUPEXPAND,       NormalGroupExpand,       db_states_EBP_NORMALGROUPEXPAND),
    DB_DEFINE_PART_ ( 8,  EBP_NORMALGROUPHEAD,         NormalGroupHead),
    DB_DEFINE_PART_ ( 9,  EBP_SPECIALGROUPBACKGROUND,  SpecialGroupBackground),
    DB_DEFINE_PART  (10,  EBP_SPECIALGROUPCOLLAPSE,    SpecialGroupCollapse,    db_states_EBP_SPECIALGROUPCOLLAPSE),
    DB_DEFINE_PART  (11,  EBP_SPECIALGROUPEXPAND,      SpecialGroupExpand,      db_states_EBP_SPECIALGROUPEXPAND),
    DB_DEFINE_PART_ (12,  EBP_SPECIALGROUPHEAD,        SpecialGroupHead)
};


/**************
 *** Flyout ***
 **************/

static const db_state_t db_states_FLYOUT_BODY[] = {
    DB_DEFINE_STATE ( 1,  FBS_NORMAL,      Normal),
    DB_DEFINE_STATE ( 2,  FBS_EMPHASIZED,  Emphasized)
};

static const db_state_t db_states_FLYOUT_LABEL[] = {
    DB_DEFINE_STATE ( 1,  FLS_NORMAL,      Normal),
    DB_DEFINE_STATE ( 2,  FLS_SELECTED,    Selected),
    DB_DEFINE_STATE ( 3,  FLS_EMPHASIZED,  Emphasized),
    DB_DEFINE_STATE ( 4,  FLS_DISABLED,    Disabled)
};

static const db_state_t db_states_FLYOUT_LINK[] = {
    DB_DEFINE_STATE ( 1,  FLYOUTLINK_NORMAL,  Normal),
    DB_DEFINE_STATE ( 2,  FLYOUTLINK_HOVER,   Hover)
};

static const db_state_t db_states_FLYOUT_LINKHEADER[] = {
    DB_DEFINE_STATE ( 1,  FLH_NORMAL,  Normal),
    DB_DEFINE_STATE ( 2,  FLH_HOVER,   Hover)
};

static const db_part_t db_parts_FLYOUT[] = {
    DB_DEFINE_PART_ ( 1,  FLYOUT_HEADER,      Header),
    DB_DEFINE_PART  ( 2,  FLYOUT_BODY,        Body,        db_states_FLYOUT_BODY),
    DB_DEFINE_PART  ( 3,  FLYOUT_LABEL,       Label,       db_states_FLYOUT_LABEL),
    DB_DEFINE_PART  ( 4,  FLYOUT_LINK,        Link,        db_states_FLYOUT_LINK),
    DB_DEFINE_PART_ ( 5,  FLYOUT_DIVIDER,     Divider),
    DB_DEFINE_PART_ ( 6,  FLYOUT_WINDOW,      Window),
    DB_DEFINE_PART_ ( 7,  FLYOUT_LINKAREA,    LinkArea),
    DB_DEFINE_PART  ( 8,  FLYOUT_LINKHEADER,  LinkHeader,  db_states_FLYOUT_LINKHEADER),
};


/***************
 *** Globals ***
 ***************/

/* FIXME: Mostly just guessing, docs is incomplete and missing in SDK headers */

static const db_state_t db_states_GP_BORDER[] = {
    DB_DEFINE_STATE ( 1,  BSS_FLAT,    Flat),
    DB_DEFINE_STATE ( 2,  BSS_RAISED,  Raised),
    DB_DEFINE_STATE ( 3,  BSS_SUNKEN,  Sunken),
};

static const db_state_t db_states_GP_LINEHORZ[] = {
    DB_DEFINE_STATE ( 1,  LHS_FLAT,    Flat),
    DB_DEFINE_STATE ( 2,  LHS_RAISED,  Raised),
    DB_DEFINE_STATE ( 3,  LHS_SUNKEN,  Sunken),
};

static const db_state_t db_states_GP_LINEVERT[] = {
    DB_DEFINE_STATE ( 1,  LVS_FLAT,    Flat),
    DB_DEFINE_STATE ( 2,  LVS_RAISED,  Raised),
    DB_DEFINE_STATE ( 3,  LVS_SUNKEN,  Sunken),
};

static const db_part_t db_parts_GLOBALS[] = {
    DB_DEFINE_PART  ( 1,  GP_BORDER,    Border,    db_states_GP_BORDER),
    DB_DEFINE_PART  ( 2,  GP_LINEHORZ,  LineHorz,  db_states_GP_LINEHORZ),
    DB_DEFINE_PART  ( 3,  GP_LINEVERT,  LineVert,  db_states_GP_LINEVERT)
};


/**************
 *** Header ***
 **************/

static const db_state_t db_states_HP_HEADERITEM[] = {
    DB_DEFINE_STATE ( 1,  HIS_NORMAL,             Normal),
    DB_DEFINE_STATE ( 2,  HIS_HOT,                Hot),
    DB_DEFINE_STATE ( 3,  HIS_PRESSED,            Pressed),
    DB_DEFINE_STATE ( 4,  HIS_SORTEDNORMAL,       SortedNormal),
    DB_DEFINE_STATE ( 5,  HIS_SORTEDHOT,          SortedHot),
    DB_DEFINE_STATE ( 6,  HIS_SORTEDPRESSED,      SortedPressed),
    DB_DEFINE_STATE ( 7,  HIS_ICONNORMAL,         IconNormal),
    DB_DEFINE_STATE ( 8,  HIS_ICONHOT,            IconHot),
    DB_DEFINE_STATE ( 9,  HIS_ICONPRESSED,        IconPressed),
    DB_DEFINE_STATE (10,  HIS_ICONSORTEDNORMAL,   IconSortedNormal),
    DB_DEFINE_STATE (11,  HIS_ICONSORTEDHOT,      IconSortedHot),
    DB_DEFINE_STATE (12,  HIS_ICONSORTEDPRESSED,  IconSortedPressed)
};

static const db_state_t db_states_HP_HEADERITEMLEFT[] = {
    DB_DEFINE_STATE ( 1,  HILS_NORMAL,   Normal),
    DB_DEFINE_STATE ( 2,  HILS_HOT,      Hot),
    DB_DEFINE_STATE ( 3,  HILS_PRESSED,  Pressed)
};

static const db_state_t db_states_HP_HEADERITEMRIGHT[] = {
    DB_DEFINE_STATE ( 1,  HIRS_NORMAL,   Normal),
    DB_DEFINE_STATE ( 2,  HIRS_HOT,      Hot),
    DB_DEFINE_STATE ( 3,  HIRS_PRESSED,  Pressed)
};

static const db_state_t db_states_HP_HEADERSORTARROW[] = {
    DB_DEFINE_STATE ( 1,  HSAS_SORTEDUP,    SortedUp),
    DB_DEFINE_STATE ( 2,  HSAS_SORTEDDOWN,  SortedDown)
};

static const db_state_t db_states_HP_HEADERDROPDOWN[] = {
    DB_DEFINE_STATE ( 1,  HDDS_NORMAL,   Normal),
    DB_DEFINE_STATE ( 2,  HDDS_SOFTHOT,  SoftHot),
    DB_DEFINE_STATE ( 3,  HDDS_HOT,      Hot)
};

static const db_state_t db_states_HP_HEADERDROPDOWNFILTER[] = {
    DB_DEFINE_STATE ( 1,  HDDFS_NORMAL,   Normal),
    DB_DEFINE_STATE ( 2,  HDDFS_SOFTHOT,  SoftHot),
    DB_DEFINE_STATE ( 3,  HDDFS_HOT,      Hot)
};

static const db_state_t db_states_HP_HEADEROVERFLOW[] = {
    DB_DEFINE_STATE ( 1,  HOFS_NORMAL,   Normal),
    DB_DEFINE_STATE ( 2,  HOFS_HOT,      Hot)
};

static const db_part_t db_parts_HEADER[] = {
    DB_DEFINE_PART  ( 1,  HP_HEADERITEM,            HeaderItem,            db_states_HP_HEADERITEM),
    DB_DEFINE_PART  ( 2,  HP_HEADERITEMLEFT,        HeaderItemLeft,        db_states_HP_HEADERITEMLEFT),
    DB_DEFINE_PART  ( 3,  HP_HEADERITEMRIGHT,       HeaderItemRight,       db_states_HP_HEADERITEMRIGHT),
    DB_DEFINE_PART  ( 4,  HP_HEADERSORTARROW,       HeaderSortArrow,       db_states_HP_HEADERSORTARROW),
    DB_DEFINE_PART  ( 5,  HP_HEADERDROPDOWN,        HeaderDropDown,        db_states_HP_HEADERDROPDOWN),
    DB_DEFINE_PART  ( 6,  HP_HEADERDROPDOWNFILTER,  HeaderDropDownFilter,  db_states_HP_HEADERDROPDOWNFILTER),
    DB_DEFINE_PART  ( 7,  HP_HEADEROVERFLOW,        HeaderOverflow,        db_states_HP_HEADEROVERFLOW)
};


/************
 *** Link ***
 ************/

static const db_state_t db_states_LP_HYPERLINK[] = {
    DB_DEFINE_STATE ( 1,  HLS_NORMALTEXT,  NormalText),
    DB_DEFINE_STATE ( 2,  HLS_LINKTEXT,    LinkText)
};

static const db_part_t db_parts_LINK[] = {
    DB_DEFINE_PART  ( 1,  LP_HYPERLINK,  HyperLink,  db_states_LP_HYPERLINK)
};


/***************
 *** ListBox ***
 ***************/

static const db_state_t db_states_LBCP_BORDER_HSCROLL[] = {
    DB_DEFINE_STATE ( 1,  LBPSH_NORMAL,    Normal),
    DB_DEFINE_STATE ( 2,  LBPSH_FOCUSED,   Focused),
    DB_DEFINE_STATE ( 3,  LBPSH_HOT,       Hot),
    DB_DEFINE_STATE ( 4,  LBPSH_DISABLED,  Disabled)
};

static const db_state_t db_states_LBCP_BORDER_HVSCROLL[] = {
    DB_DEFINE_STATE ( 1,  LBPSHV_NORMAL,    Normal),
    DB_DEFINE_STATE ( 2,  LBPSHV_FOCUSED,   Focused),
    DB_DEFINE_STATE ( 3,  LBPSHV_HOT,       Hot),
    DB_DEFINE_STATE ( 4,  LBPSHV_DISABLED,  Disabled)
};

static const db_state_t db_states_LBCP_BORDER_NOSCROLL[] = {
    DB_DEFINE_STATE ( 1,  LBPSN_NORMAL,    Normal),
    DB_DEFINE_STATE ( 2,  LBPSN_FOCUSED,   Focused),
    DB_DEFINE_STATE ( 3,  LBPSN_HOT,       Hot),
    DB_DEFINE_STATE ( 4,  LBPSN_DISABLED,  Disabled)
};

static const db_state_t db_states_LBCP_BORDER_VSCROLL[] = {
    DB_DEFINE_STATE ( 1,  LBPSV_NORMAL,    Normal),
    DB_DEFINE_STATE ( 2,  LBPSV_FOCUSED,   Focused),
    DB_DEFINE_STATE ( 3,  LBPSV_HOT,       Hot),
    DB_DEFINE_STATE ( 4,  LBPSV_DISABLED,  Disabled)
};

static const db_state_t db_states_LBCP_ITEM[] = {
    DB_DEFINE_STATE ( 1,  LBPSI_HOT,               Hot),
    DB_DEFINE_STATE ( 2,  LBPSI_HOTSELECTED,       HotSelected),
    DB_DEFINE_STATE ( 3,  LBPSI_SELECTED,          Selected),
    DB_DEFINE_STATE ( 4,  LBPSI_SELECTEDNOTFOCUS,  SelectedNotFocus)
};

static const db_part_t db_parts_LISTBOX[] = {
    DB_DEFINE_PART  ( 1,  LBCP_BORDER_HSCROLL,   Border_HScroll,   db_states_LBCP_BORDER_HSCROLL),
    DB_DEFINE_PART  ( 2,  LBCP_BORDER_HVSCROLL,  Border_HVScroll,  db_states_LBCP_BORDER_HVSCROLL),
    DB_DEFINE_PART  ( 3,  LBCP_BORDER_NOSCROLL,  Border_NoScroll,  db_states_LBCP_BORDER_NOSCROLL),
    DB_DEFINE_PART  ( 4,  LBCP_BORDER_VSCROLL,   Border_VScroll,   db_states_LBCP_BORDER_VSCROLL),
    DB_DEFINE_PART  ( 5,  LBCP_ITEM,             Item,             db_states_LBCP_ITEM)
};


/****************
 *** ListView ***
 ****************/

static const db_state_t db_states_LVP_LISTITEM[] = {
    DB_DEFINE_STATE ( 1, LISS_NORMAL,            Normal),
    DB_DEFINE_STATE ( 2, LISS_HOT,               Hot),
    DB_DEFINE_STATE ( 3, LISS_SELECTED,          Selected),
    DB_DEFINE_STATE ( 4, LISS_DISABLED,          Disabled),
    DB_DEFINE_STATE ( 5, LISS_SELECTEDNOTFOCUS,  SelectedNotFocus),
    DB_DEFINE_STATE ( 6, LISS_HOTSELECTED,       HotSelected)
};

static const db_state_t db_states_LVP_GROUPHEADER[] = {
    DB_DEFINE_STATE ( 1,  LVGH_OPEN,                        Open),
    DB_DEFINE_STATE ( 2,  LVGH_OPENHOT,                     OpenHot),
    DB_DEFINE_STATE ( 3,  LVGH_OPENSELECTED,                OpenSelected),
    DB_DEFINE_STATE ( 4,  LVGH_OPENSELECTEDHOT,             OpenSelectedHot),
    DB_DEFINE_STATE ( 5,  LVGH_OPENSELECTEDNOTFOCUSED,      OpenSelectedNotFocused),
    DB_DEFINE_STATE ( 6,  LVGH_OPENSELECTEDNOTFOCUSEDHOT,   OpenSelectedNotFocusedHot),
    DB_DEFINE_STATE ( 7,  LVGH_OPENMIXEDSELECTION,          OpenMixedSelection),
    DB_DEFINE_STATE ( 8,  LVGH_OPENMIXEDSELECTIONHOT,       OpenMixedSelectionHot),
    DB_DEFINE_STATE ( 9,  LVGH_CLOSE,                       Close),
    DB_DEFINE_STATE (10,  LVGH_CLOSEHOT,                    CloseHot),
    DB_DEFINE_STATE (11,  LVGH_CLOSESELECTED,               CloseSelected),
    DB_DEFINE_STATE (12,  LVGH_CLOSESELECTEDHOT,            CloseSelectedHot),
    DB_DEFINE_STATE (13,  LVGH_CLOSESELECTEDNOTFOCUSED,     CloseSelectedNotFocused),
    DB_DEFINE_STATE (14,  LVGH_CLOSESELECTEDNOTFOCUSEDHOT,  CloseSelectedNotFocusedHot),
    DB_DEFINE_STATE (15,  LVGH_CLOSEMIXEDSELECTION,         CloseMixedSelection),
    DB_DEFINE_STATE (16,  LVGH_CLOSEMIXEDSELECTIONHOT,      CloseMixedSelectionHot)
};

static const db_state_t db_states_LVP_GROUPHEADERLINE[] = {
    DB_DEFINE_STATE ( 1,  LVGHL_OPEN,                        Open),
    DB_DEFINE_STATE ( 2,  LVGHL_OPENHOT,                     OpenHot),
    DB_DEFINE_STATE ( 3,  LVGHL_OPENSELECTED,                OpenSelected),
    DB_DEFINE_STATE ( 4,  LVGHL_OPENSELECTEDHOT,             OpenSelectedHot),
    DB_DEFINE_STATE ( 5,  LVGHL_OPENSELECTEDNOTFOCUSED,      OpenSelectedNotFocused),
    DB_DEFINE_STATE ( 6,  LVGHL_OPENSELECTEDNOTFOCUSEDHOT,   OpenSelectedNotFocusedHot),
    DB_DEFINE_STATE ( 7,  LVGHL_OPENMIXEDSELECTION,          OpenMixedSelection),
    DB_DEFINE_STATE ( 8,  LVGHL_OPENMIXEDSELECTIONHOT,       OpenMixedSelectionHot),
    DB_DEFINE_STATE ( 9,  LVGHL_CLOSE,                       Close),
    DB_DEFINE_STATE (10,  LVGHL_CLOSEHOT,                    CloseHot),
    DB_DEFINE_STATE (11,  LVGHL_CLOSESELECTED,               CloseSelected),
    DB_DEFINE_STATE (12,  LVGHL_CLOSESELECTEDHOT,            CloseSelectedHot),
    DB_DEFINE_STATE (13,  LVGHL_CLOSESELECTEDNOTFOCUSED,     CloseSelectedNotFocused),
    DB_DEFINE_STATE (14,  LVGHL_CLOSESELECTEDNOTFOCUSEDHOT,  CloseSelectedNotFocusedHot),
    DB_DEFINE_STATE (15,  LVGHL_CLOSEMIXEDSELECTION,         CloseMixedSelection),
    DB_DEFINE_STATE (16,  LVGHL_CLOSEMIXEDSELECTIONHOT,      CloseMixedSelectionHot)
};

static const db_state_t db_states_LVP_EXPANDBUTTON[] = {
    DB_DEFINE_STATE ( 1,  LVEB_NORMAL,  Normal),
    DB_DEFINE_STATE ( 2,  LVEB_HOVER,   Hover),
    DB_DEFINE_STATE ( 3,  LVEB_PUSHED,  Pushed)
};

static const db_state_t db_states_LVP_COLLAPSEBUTTON[] = {
    DB_DEFINE_STATE ( 1,  LVCB_NORMAL,  Normal),
    DB_DEFINE_STATE ( 2,  LVCB_HOVER,   Hover),
    DB_DEFINE_STATE ( 3,  LVCB_PUSHED,  Pushed)
};

static const db_part_t db_parts_LISTVIEW[] = {
    DB_DEFINE_PART  ( 1,  LVP_LISTITEM,          ListItem,          db_states_LVP_LISTITEM),
    DB_DEFINE_PART_ ( 2,  LVP_LISTGROUP,         ListGroup),
    DB_DEFINE_PART_ ( 3,  LVP_LISTDETAIL,        ListDetail),
    DB_DEFINE_PART_ ( 4,  LVP_LISTSORTEDDETAIL,  ListSortedDetail),
    DB_DEFINE_PART_ ( 5,  LVP_EMPTYTEXT,         EmptyText),
    DB_DEFINE_PART  ( 6,  LVP_GROUPHEADER,       GroupHeader,       db_states_LVP_GROUPHEADER),
    DB_DEFINE_PART  ( 7,  LVP_GROUPHEADERLINE,   GroupHeaderLine,   db_states_LVP_GROUPHEADERLINE),
    DB_DEFINE_PART  ( 8,  LVP_EXPANDBUTTON,      ExpandButton,      db_states_LVP_EXPANDBUTTON),
    DB_DEFINE_PART  ( 9,  LVP_COLLAPSEBUTTON,    CollapseButton,    db_states_LVP_COLLAPSEBUTTON),
    DB_DEFINE_PART_ (10,  LVP_COLUMNDETAIL,      ColumnDetail)
};


/************
 *** Menu ***
 ************/

static const db_state_t db_states_MENU_BARBACKGROUND[] = {
    DB_DEFINE_STATE ( 1,  MB_ACTIVE,    Active),
    DB_DEFINE_STATE ( 2,  MB_INACTIVE,  Inactive)
};

static const db_state_t db_states_MENU_BARITEM[] = {
    DB_DEFINE_STATE ( 1,  MBI_NORMAL,          Normal),
    DB_DEFINE_STATE ( 2,  MBI_HOT,             Hot),
    DB_DEFINE_STATE ( 3,  MBI_PUSHED,          Pushed),
    DB_DEFINE_STATE ( 4,  MBI_DISABLED,        Disabled),
    DB_DEFINE_STATE ( 5,  MBI_DISABLEDHOT,     DisabledHot),
    DB_DEFINE_STATE ( 6,  MBI_DISABLEDPUSHED,  DisabledPushed)
};

static const db_state_t db_states_MENU_POPUPCHECK[] = {
    DB_DEFINE_STATE ( 1,  MC_CHECKMARKNORMAL,    CheckMarkNormal),
    DB_DEFINE_STATE ( 2,  MC_CHECKMARKDISABLED,  CheckMarkDisabled),
    DB_DEFINE_STATE ( 3,  MC_BULLETNORMAL,       BulletNormal),
    DB_DEFINE_STATE ( 4,  MC_BULLETDISABLED,     BulletDisabled)
};

static const db_state_t db_states_MENU_POPUPCHECKBACKGROUND[] = {
    DB_DEFINE_STATE ( 1,  MCB_DISABLED,  Disabled),
    DB_DEFINE_STATE ( 2,  MCB_NORMAL,    Normal),
    DB_DEFINE_STATE ( 3,  MCB_BITMAP,    Bitmap)
};

static const db_state_t db_states_MENU_POPUPITEM[] = {
    DB_DEFINE_STATE ( 1,  MPI_NORMAL,       Normal),
    DB_DEFINE_STATE ( 2,  MPI_HOT,          Hot),
    DB_DEFINE_STATE ( 3,  MPI_DISABLED,     Disabled),
    DB_DEFINE_STATE ( 4,  MPI_DISABLEDHOT,  DisabledHot)
};

static const db_state_t db_states_MENU_POPUPSUBMENU[] = {
    DB_DEFINE_STATE ( 1,  MSM_NORMAL,    Normal),
    DB_DEFINE_STATE ( 2,  MSM_DISABLED,  Disabled)
};

static const db_state_t db_states_MENU_SYSTEMCLOSE[] = {
    DB_DEFINE_STATE ( 1,  MSYSC_NORMAL,    Normal),
    DB_DEFINE_STATE ( 2,  MSYSC_DISABLED,  Disabled)
};

static const db_state_t db_states_MENU_SYSTEMMAXIMIZE[] = {
    DB_DEFINE_STATE ( 1,  MSYSMX_NORMAL,    Normal),
    DB_DEFINE_STATE ( 2,  MSYSMX_DISABLED,  Disabled)
};

static const db_state_t db_states_MENU_SYSTEMMINIMIZE[] = {
    DB_DEFINE_STATE ( 1,  MSYSMN_NORMAL,    Normal),
    DB_DEFINE_STATE ( 2,  MSYSMN_DISABLED,  Disabled)
};

static const db_state_t db_states_MENU_SYSTEMRESTORE[] = {
    DB_DEFINE_STATE ( 1,  MSYSR_NORMAL,    Normal),
    DB_DEFINE_STATE ( 2,  MSYSR_DISABLED,  Disabled)
};

static const db_part_t db_parts_MENU[] = {
    DB_DEFINE_PART_ ( 1,  MENU_MENUITEM_TMSCHEMA,         MenuItem),
    DB_DEFINE_PART_ ( 2,  MENU_MENUDROPDOWN_TMSCHEMA,     MenuDropDown),
    DB_DEFINE_PART_ ( 3,  MENU_MENUBARITEM_TMSCHEMA,      MenuBarItem),
    DB_DEFINE_PART_ ( 4,  MENU_MENUBARDROPDOWN_TMSCHEMA,  MenuBarDropDown),
    DB_DEFINE_PART_ ( 5,  MENU_CHEVRON_TMSCHEMA,          Chevron),
    DB_DEFINE_PART_ ( 6,  MENU_SEPARATOR_TMSCHEMA,        Separator),
    DB_DEFINE_PART  ( 7,  MENU_BARBACKGROUND,             BarBackground,         db_states_MENU_BARBACKGROUND),
    DB_DEFINE_PART  ( 8,  MENU_BARITEM,                   BarItem,               db_states_MENU_BARITEM),
    DB_DEFINE_PART_ ( 9,  MENU_POPUPBACKGROUND,           PopupBackground),
    DB_DEFINE_PART_ (10,  MENU_POPUPBORDERS,              PopupBorders),
    DB_DEFINE_PART  (11,  MENU_POPUPCHECK,                PopupCheck,            db_states_MENU_POPUPCHECK),
    DB_DEFINE_PART  (12,  MENU_POPUPCHECKBACKGROUND,      PopupCheckBackground,  db_states_MENU_POPUPCHECKBACKGROUND),
    DB_DEFINE_PART_ (13,  MENU_POPUPGUTTER,               PopupGutter),
    DB_DEFINE_PART  (14,  MENU_POPUPITEM,                 PopupItem,             db_states_MENU_POPUPITEM),
    DB_DEFINE_PART_ (15,  MENU_POPUPSEPARATOR,            PopupSeparator),
    DB_DEFINE_PART  (16,  MENU_POPUPSUBMENU,              PopupSubMenu,          db_states_MENU_POPUPSUBMENU),
    DB_DEFINE_PART  (17,  MENU_SYSTEMCLOSE,               SystemClose,           db_states_MENU_SYSTEMCLOSE),
    DB_DEFINE_PART  (18,  MENU_SYSTEMMAXIMIZE,            SystemMaximize,        db_states_MENU_SYSTEMMAXIMIZE),
    DB_DEFINE_PART  (19,  MENU_SYSTEMMINIMIZE,            SystemMinimize,        db_states_MENU_SYSTEMMINIMIZE),
    DB_DEFINE_PART  (20,  MENU_SYSTEMRESTORE,             SystemRestore,         db_states_MENU_SYSTEMRESTORE)
};


/****************
 *** MenuBand ***
 ****************/

static const db_state_t db_states_MDP_NEWAPPBUTTON[] = {
    DB_DEFINE_STATE ( 1,  MDS_NORMAL,      Normal),
    DB_DEFINE_STATE ( 2,  MDS_HOT,         Hot),
    DB_DEFINE_STATE ( 3,  MDS_PRESSED,     Pressed),
    DB_DEFINE_STATE ( 4,  MDS_DISABLED,    Disabled),
    DB_DEFINE_STATE ( 5,  MDS_CHECKED,     Checked),
    DB_DEFINE_STATE ( 6,  MDS_HOTCHECKED,  HotChecked)
};

static const db_part_t db_parts_MENUBAND[] = {
    DB_DEFINE_PART  ( 1,  MDP_NEWAPPBUTTON,  NewAppButton,  db_states_MDP_NEWAPPBUTTON),
    DB_DEFINE_PART_ ( 2,  MDP_SEPERATOR,     Separator)
};


/****************
 *** MonthCal ***
 ****************/

static const db_state_t db_states_MC_GRIDCELLBACKGROUND[] = {
    DB_DEFINE_STATE ( 1,  MCGCB_SELECTED,            Selected),
    DB_DEFINE_STATE ( 2,  MCGCB_HOT,                 Hot),
    DB_DEFINE_STATE ( 3,  MCGCB_SELECTEDHOT,         SelectedHot),
    DB_DEFINE_STATE ( 4,  MCGCB_SELECTEDNOTFOCUSED,  SelectedNotFocused),
    DB_DEFINE_STATE ( 5,  MCGCB_TODAY,               Today)
};

static const db_state_t db_states_MC_GRIDCELL[] = {
    DB_DEFINE_STATE ( 1,  MCGC_HOT,          Hot),
    DB_DEFINE_STATE ( 2,  MCGC_HASSTATE,     HasState),
    DB_DEFINE_STATE ( 3,  MCGC_HASSTATEHOT,  HasStateHot),
    DB_DEFINE_STATE ( 4,  MCGC_TODAY,        Today)
};

static const db_state_t db_states_MC_GRIDCELLUPPER[] = {
    DB_DEFINE_STATE ( 1,  MCGCU_HOT,          Hot),
    DB_DEFINE_STATE ( 2,  MCGCU_HASSTATE,     HasState),
    DB_DEFINE_STATE ( 3,  MCGCU_HASSTATEHOT,  HasStateHot)
};

static const db_state_t db_states_MC_TRAILINGGRIDCELL[] = {
    DB_DEFINE_STATE ( 1,  MCTGC_HOT,          Hot),
    DB_DEFINE_STATE ( 2,  MCTGC_HASSTATE,     HasState),
    DB_DEFINE_STATE ( 3,  MCTGC_HASSTATEHOT,  HasStateHot),
    DB_DEFINE_STATE ( 4,  MCTGC_TODAY,        Today)
};

static const db_state_t db_states_MC_TRAILINGGRIDCELLUPPER[] = {
    DB_DEFINE_STATE ( 1,  MCTGCU_HOT,          Hot),
    DB_DEFINE_STATE ( 2,  MCTGCU_HASSTATE,     HasState),
    DB_DEFINE_STATE ( 3,  MCTGCU_HASSTATEHOT,  HasStateHot)
};

static const db_state_t db_states_MC_NAVNEXT[] = {
    DB_DEFINE_STATE ( 1,  MCNN_NORMAL,    Normal),
    DB_DEFINE_STATE ( 2,  MCNN_HOT,       Hot),
    DB_DEFINE_STATE ( 3,  MCNN_PRESSED,   Pressed),
    DB_DEFINE_STATE ( 4,  MCNN_DISABLED,  Disabled)
};

static const db_state_t db_states_MC_NAVPREV[] = {
    DB_DEFINE_STATE ( 1,  MCNP_NORMAL,    Normal),
    DB_DEFINE_STATE ( 2,  MCNP_HOT,       Hot),
    DB_DEFINE_STATE ( 3,  MCNP_PRESSED,   Pressed),
    DB_DEFINE_STATE ( 4,  MCNP_DISABLED,  Disabled)
};

static const db_part_t db_parts_MONTHCAL[] = {
    DB_DEFINE_PART_ ( 1,  MC_BACKGROUND,             Background),
    DB_DEFINE_PART_ ( 2,  MC_BORDERS,                Borders),
    DB_DEFINE_PART_ ( 3,  MC_GRIDBACKGROUND,         GridBackground),
    DB_DEFINE_PART_ ( 4,  MC_COLHEADERSPLITTER,      ColheaderSplitter),
    DB_DEFINE_PART  ( 5,  MC_GRIDCELLBACKGROUND,     GridCellBackground,     db_states_MC_GRIDCELLBACKGROUND),
    DB_DEFINE_PART  ( 6,  MC_GRIDCELL,               GridCell,               db_states_MC_GRIDCELL),
    DB_DEFINE_PART  ( 7,  MC_GRIDCELLUPPER,          GridCellUpper,          db_states_MC_GRIDCELLUPPER),
    DB_DEFINE_PART  ( 8,  MC_TRAILINGGRIDCELL,       TrailingGridCell,       db_states_MC_TRAILINGGRIDCELL),
    DB_DEFINE_PART  ( 9,  MC_TRAILINGGRIDCELLUPPER,  TrailingGridCellUpper,  db_states_MC_TRAILINGGRIDCELLUPPER),
    DB_DEFINE_PART  (10,  MC_NAVNEXT,                NavNext,                db_states_MC_NAVNEXT),
    DB_DEFINE_PART  (11,  MC_NAVPREV,                NavPrev,                db_states_MC_NAVPREV)
};


/******************
 *** Navigation ***
 ******************/

static const db_state_t db_states_NAV_BACKBUTTON[] = {
    DB_DEFINE_STATE ( 1,  NAV_BB_NORMAL,    Normal),
    DB_DEFINE_STATE ( 2,  NAV_BB_HOT,       Hot),
    DB_DEFINE_STATE ( 3,  NAV_BB_PRESSED,   Pressed),
    DB_DEFINE_STATE ( 4,  NAV_BB_DISABLED,  Disabled)
};

static const db_state_t db_states_NAV_FORWARDBUTTON[] = {
    DB_DEFINE_STATE ( 1,  NAV_FB_NORMAL,    Normal),
    DB_DEFINE_STATE ( 2,  NAV_FB_HOT,       Hot),
    DB_DEFINE_STATE ( 3,  NAV_FB_PRESSED,   Pressed),
    DB_DEFINE_STATE ( 4,  NAV_FB_DISABLED,  Disabled)
};

static const db_state_t db_states_NAV_MENUBUTTON[] = {
    DB_DEFINE_STATE ( 1,  NAV_MB_NORMAL,    Normal),
    DB_DEFINE_STATE ( 2,  NAV_MB_HOT,       Hot),
    DB_DEFINE_STATE ( 3,  NAV_MB_PRESSED,   Pressed),
    DB_DEFINE_STATE ( 4,  NAV_MB_DISABLED,  Disabled)
};

static const db_part_t db_parts_NAVIGATION[] = {
    DB_DEFINE_PART  ( 1,  NAV_BACKBUTTON,     BackButton,     db_states_NAV_BACKBUTTON),
    DB_DEFINE_PART  ( 2,  NAV_FORWARDBUTTON,  ForwardButton,  db_states_NAV_FORWARDBUTTON),
    DB_DEFINE_PART  ( 3,  NAV_MENUBUTTON,     MenuButton,     db_states_NAV_MENUBUTTON)
};


/************
 *** Page ***
 ************/

static const db_state_t db_states_PGRP_UP[] = {
    DB_DEFINE_STATE ( 1,  UPS_NORMAL,    Normal),
    DB_DEFINE_STATE ( 2,  UPS_HOT,       Hot),
    DB_DEFINE_STATE ( 3,  UPS_PRESSED,   Pressed),
    DB_DEFINE_STATE ( 4,  UPS_DISABLED,  Disabled)
};

static const db_state_t db_states_PGRP_DOWN[] = {
    DB_DEFINE_STATE ( 1,  DNS_NORMAL,    Normal),
    DB_DEFINE_STATE ( 2,  DNS_HOT,       Hot),
    DB_DEFINE_STATE ( 3,  DNS_PRESSED,   Pressed),
    DB_DEFINE_STATE ( 4,  DNS_DISABLED,  Disabled)
};

static const db_state_t db_states_PGRP_UPHORZ[] = {
    DB_DEFINE_STATE ( 1,  UPHZS_NORMAL,    Normal),
    DB_DEFINE_STATE ( 2,  UPHZS_HOT,       Hot),
    DB_DEFINE_STATE ( 3,  UPHZS_PRESSED,   Pressed),
    DB_DEFINE_STATE ( 4,  UPHZS_DISABLED,  Disabled)
};

static const db_state_t db_states_PGRP_DOWNHORZ[] = {
    DB_DEFINE_STATE ( 1,  DNHZS_NORMAL,    Normal),
    DB_DEFINE_STATE ( 2,  DNHZS_HOT,       Hot),
    DB_DEFINE_STATE ( 3,  DNHZS_PRESSED,   Pressed),
    DB_DEFINE_STATE ( 4,  DNHZS_DISABLED,  Disabled)
};

static const db_part_t db_parts_PAGE[] = {
    DB_DEFINE_PART  ( 1,  PGRP_UP,        Up,        db_states_PGRP_UP),
    DB_DEFINE_PART  ( 2,  PGRP_DOWN,      Down,      db_states_PGRP_DOWN),
    DB_DEFINE_PART  ( 3,  PGRP_UPHORZ,    UpHorz,    db_states_PGRP_UPHORZ),
    DB_DEFINE_PART  ( 4,  PGRP_DOWNHORZ,  DownHorz,  db_states_PGRP_DOWNHORZ)
};


/****************
 *** Progress ***
 ****************/

static const db_state_t db_states_PP_FILL[] = {
    DB_DEFINE_STATE ( 1,  PBFS_NORMAL,   Normal),
    DB_DEFINE_STATE ( 2,  PBFS_ERROR,    Error),
    DB_DEFINE_STATE ( 3,  PBFS_PAUSED,   Paused),
    DB_DEFINE_STATE ( 4,  PBFS_PARTIAL,  Partial)
};

static const db_state_t db_states_PP_FILLVERT[] = {
    DB_DEFINE_STATE ( 1,  PBFVS_NORMAL,   Normal),
    DB_DEFINE_STATE ( 2,  PBFVS_ERROR,    Error),
    DB_DEFINE_STATE ( 3,  PBFVS_PAUSED,   Paused),
    DB_DEFINE_STATE ( 4,  PBFVS_PARTIAL,  Partial)
};

static const db_state_t db_states_PP_TRANSPARENTBAR[] = {
    DB_DEFINE_STATE ( 1,  PBBS_NORMAL,   Normal),
    DB_DEFINE_STATE ( 2,  PBBS_PARTIAL,  Partial)
};

static const db_state_t db_states_PP_TRANSPARENTBARVERT[] = {
    DB_DEFINE_STATE ( 1,  PBBVS_NORMAL,   Normal),
    DB_DEFINE_STATE ( 2,  PBBVS_PARTIAL,  Partial)
};

static const db_part_t db_parts_PROGRESS[] = {
    DB_DEFINE_PART_ ( 1,  PP_BAR,                 Bar),
    DB_DEFINE_PART_ ( 2,  PP_BARVERT,             BarVert),
    DB_DEFINE_PART_ ( 3,  PP_CHUNK,               Chunk),
    DB_DEFINE_PART_ ( 4,  PP_CHUNKVERT,           ChunkVert),
    DB_DEFINE_PART  ( 5,  PP_FILL,                Fill,                db_states_PP_FILL),
    DB_DEFINE_PART  ( 6,  PP_FILLVERT,            FillVert,            db_states_PP_FILLVERT),
    DB_DEFINE_PART_ ( 7,  PP_PULSEOVERLAY,        PulseOverlay),
    DB_DEFINE_PART_ ( 8,  PP_MOVEOVERLAY,         MoveOverlay),
    DB_DEFINE_PART_ ( 9,  PP_PULSEOVERLAYVERT,    PulseOverlayVert),
    DB_DEFINE_PART_ (10,  PP_MOVEOVERLAYVERT,     MoveOverlayVert),
    DB_DEFINE_PART  (11,  PP_TRANSPARENTBAR,      TransparentBar,      db_states_PP_TRANSPARENTBAR),
    DB_DEFINE_PART  (12,  PP_TRANSPARENTBARVERT,  TransparentBarVert,  db_states_PP_TRANSPARENTBARVERT)
};


/*************
 *** Rebar ***
 *************/

static const db_state_t db_states_RP_CHEVRON[] = {
    DB_DEFINE_STATE ( 1,  CHEVS_NORMAL,   Normal),
    DB_DEFINE_STATE ( 2,  CHEVS_HOT,      Hot),
    DB_DEFINE_STATE ( 3,  CHEVS_PRESSED,  Pressed)
};

static const db_state_t db_states_RP_CHEVRONVERT[] = {
    DB_DEFINE_STATE ( 1,  CHEVSV_NORMAL,   Normal),
    DB_DEFINE_STATE ( 2,  CHEVSV_HOT,      Hot),
    DB_DEFINE_STATE ( 3,  CHEVSV_PRESSED,  Pressed)
};

static const db_state_t db_states_RP_SPLITTER[] = {
    DB_DEFINE_STATE ( 1,  SPLITS_NORMAL,   Normal),
    DB_DEFINE_STATE ( 2,  SPLITS_HOT,      Hot),
    DB_DEFINE_STATE ( 3,  SPLITS_PRESSED,  Pressed)
};

static const db_state_t db_states_RP_SPLITTERVERT[] = {
    DB_DEFINE_STATE ( 1,  SPLITSV_NORMAL,   Normal),
    DB_DEFINE_STATE ( 2,  SPLITSV_HOT,      Hot),
    DB_DEFINE_STATE ( 3,  SPLITSV_PRESSED,  Pressed)
};

static const db_part_t db_parts_REBAR[] = {
    DB_DEFINE_PART_ ( 1,  RP_GRIPPER,       Gripper),
    DB_DEFINE_PART_ ( 2,  RP_GRIPPERVERT,   GripperVert),
    DB_DEFINE_PART_ ( 3,  RP_BAND,          Band),
    DB_DEFINE_PART  ( 4,  RP_CHEVRON,       Chevron,       db_states_RP_CHEVRON),
    DB_DEFINE_PART  ( 5,  RP_CHEVRONVERT,   ChevronVert,   db_states_RP_CHEVRONVERT),
    DB_DEFINE_PART_ ( 6,  RP_BACKGROUND,    Background),
    DB_DEFINE_PART  ( 7,  RP_SPLITTER,      Splitter,      db_states_RP_SPLITTER),
    DB_DEFINE_PART  ( 8,  RP_SPLITTERVERT,  SplitterVert,  db_states_RP_SPLITTERVERT)
};


/*****************
 *** Scrollbar ***
 *****************/

static const db_state_t db_states_SBP_ARROWBTN[] = {
    DB_DEFINE_STATE ( 1,  ABS_UPNORMAL,       UpNormal),
    DB_DEFINE_STATE ( 2,  ABS_UPHOT,          UpHot),
    DB_DEFINE_STATE ( 3,  ABS_UPPRESSED,      UpPressed),
    DB_DEFINE_STATE ( 4,  ABS_UPDISABLED,     UpDisabled),
    DB_DEFINE_STATE ( 5,  ABS_DOWNNORMAL,     DownNormal),
    DB_DEFINE_STATE ( 6,  ABS_DOWNHOT,        DownHot),
    DB_DEFINE_STATE ( 7,  ABS_DOWNPRESSED,    DownPressed),
    DB_DEFINE_STATE ( 8,  ABS_DOWNDISABLED,   DownDisabled),
    DB_DEFINE_STATE ( 9,  ABS_LEFTNORMAL,     LeftNormal),
    DB_DEFINE_STATE (10,  ABS_LEFTHOT,        LeftHot),
    DB_DEFINE_STATE (11,  ABS_LEFTPRESSED,    LeftPressed),
    DB_DEFINE_STATE (12,  ABS_LEFTDISABLED,   LeftDisabled),
    DB_DEFINE_STATE (13,  ABS_RIGHTNORMAL,    RightNormal),
    DB_DEFINE_STATE (14,  ABS_RIGHTHOT,       RightHot),
    DB_DEFINE_STATE (15,  ABS_RIGHTPRESSED,   RightPressed),
    DB_DEFINE_STATE (16,  ABS_RIGHTDISABLED,  RightDisabled),
    DB_DEFINE_STATE (17,  ABS_UPHOVER,        UpHover),
    DB_DEFINE_STATE (18,  ABS_DOWNHOVER,      DownHover),
    DB_DEFINE_STATE (19,  ABS_LEFTHOVER,      LeftHover),
    DB_DEFINE_STATE (20,  ABS_RIGHTHOVER,     RightHover)
};

static const db_state_t db_states_SBP_shared[] = {
    DB_DEFINE_STATE ( 1,  SCRBS_NORMAL,    Normal),
    DB_DEFINE_STATE ( 2,  SCRBS_HOT,       Hot),
    DB_DEFINE_STATE ( 3,  SCRBS_PRESSED,   Pressed),
    DB_DEFINE_STATE ( 4,  SCRBS_DISABLED,  Disabled),
    DB_DEFINE_STATE ( 5,  SCRBS_HOVER,     Hover)
};

static const db_state_t db_states_SBP_SIZEBOX[] = {
    DB_DEFINE_STATE ( 1,  SZB_RIGHTALIGN,            RightAlign),
    DB_DEFINE_STATE ( 2,  SZB_LEFTALIGN,             LeftAlign),
    DB_DEFINE_STATE ( 3,  SZB_TOPRIGHTALIGN,         TopRightAlign),
    DB_DEFINE_STATE ( 4,  SZB_TOPLEFTALIGN,          TopLeftAlign),
    DB_DEFINE_STATE ( 5,  SZB_HALFBOTTOMRIGHTALIGN,  HalfBottomRightAlign),
    DB_DEFINE_STATE ( 6,  SZB_HALFBOTTOMLEFTALIGN,   HalfBottomLeftAlign),
    DB_DEFINE_STATE ( 7,  SZB_HALFTOPRIGHTALIGN,     HalfTopRightAlign),
    DB_DEFINE_STATE ( 8,  SZB_HALFTOPLEFTALIGN,      HalfTopLeftAlign)
};

static const db_part_t db_parts_SCROLLBAR[] = {
    DB_DEFINE_PART  ( 1,  SBP_ARROWBTN,        ArrowBtn,        db_states_SBP_ARROWBTN),
    DB_DEFINE_PART  ( 2,  SBP_THUMBBTNHORZ,    ThumbBtnHorz,    db_states_SBP_shared),
    DB_DEFINE_PART  ( 3,  SBP_THUMBBTNVERT,    ThumbBtnVert,    db_states_SBP_shared),
    DB_DEFINE_PART  ( 4,  SBP_LOWERTRACKHORZ,  LowerTrackHorz,  db_states_SBP_shared),
    DB_DEFINE_PART  ( 5,  SBP_UPPERTRACKHORZ,  UpperTrackHorz,  db_states_SBP_shared),
    DB_DEFINE_PART  ( 6,  SBP_LOWERTRACKVERT,  LowerTrackVert,  db_states_SBP_shared),
    DB_DEFINE_PART  ( 7,  SBP_UPPERTRACKVERT,  UpperTrackVert,  db_states_SBP_shared),
    DB_DEFINE_PART  ( 8,  SBP_GRIPPERHORZ,     GripperHorz,     db_states_SBP_shared),
    DB_DEFINE_PART  ( 9,  SBP_GRIPPERVERT,     GripperVert,     db_states_SBP_shared),
    DB_DEFINE_PART  (10,  SBP_SIZEBOX,         SizeBox,         db_states_SBP_SIZEBOX)
};


/*********************
 *** SearchEditBox ***
 *********************/

static const db_state_t db_states_SEBP_SEARCHEDITBOXTEXT[] = {
    DB_DEFINE_STATE ( 1,  SEBTS_FORMATTED,  Formatted)
};

static const db_part_t db_parts_SEARCHEDITBOX[] = {
    DB_DEFINE_PART  ( 1,  SEBP_SEARCHEDITBOXTEXT,  SearchEditBoxText,  db_states_SEBP_SEARCHEDITBOXTEXT)
};


/*****************
 *** SearchBox ***
 *****************/

static const db_state_t db_states_SBBACKGROUND[] = {
    DB_DEFINE_STATE ( 1,  xxx_NORMAL,    Normal),
    DB_DEFINE_STATE ( 2,  xxx_HOT,       Hot),
    DB_DEFINE_STATE ( 3,  xxx_DISABLED,  Disabled),
    DB_DEFINE_STATE ( 4,  xxx_FOCUSED,   Focused)
};

static const db_part_t db_parts_SEARCHBOX[] = {
    DB_DEFINE_PART  ( 1,  SBBACKGROUND,  Background,  db_states_SBBACKGROUND)
};


/************
 *** Spin ***
 ************/

static const db_state_t db_states_SPNP_UP[] = {
    DB_DEFINE_STATE ( 1,  UPS_NORMAL,    Normal),
    DB_DEFINE_STATE ( 2,  UPS_HOT,       Hot),
    DB_DEFINE_STATE ( 3,  UPS_PRESSED,   Pressed),
    DB_DEFINE_STATE ( 4,  UPS_DISABLED,  Disabled)
};

static const db_state_t db_states_SPNP_DOWN[] = {
    DB_DEFINE_STATE ( 1,  DNS_NORMAL,    Normal),
    DB_DEFINE_STATE ( 2,  DNS_HOT,       Hot),
    DB_DEFINE_STATE ( 3,  DNS_PRESSED,   Pressed),
    DB_DEFINE_STATE ( 4,  DNS_DISABLED,  Disabled)
};

static const db_state_t db_states_SPNP_UPHORZ[] = {
    DB_DEFINE_STATE ( 1,  UPHZS_NORMAL,    Normal),
    DB_DEFINE_STATE ( 2,  UPHZS_HOT,       Hot),
    DB_DEFINE_STATE ( 3,  UPHZS_PRESSED,   Pressed),
    DB_DEFINE_STATE ( 4,  UPHZS_DISABLED,  Disabled)
};

static const db_state_t db_states_SPNP_DOWNHORZ[] = {
    DB_DEFINE_STATE ( 1,  DNHZS_NORMAL,    Normal),
    DB_DEFINE_STATE ( 2,  DNHZS_HOT,       Hot),
    DB_DEFINE_STATE ( 3,  DNHZS_PRESSED,   Pressed),
    DB_DEFINE_STATE ( 4,  DNHZS_DISABLED,  Disabled)
};

static const db_part_t db_parts_SPIN[] = {
    DB_DEFINE_PART  ( 1,  SPNP_UP,        Up,        db_states_SPNP_UP),
    DB_DEFINE_PART  ( 2,  SPNP_DOWN,      Down,      db_states_SPNP_DOWN),
    DB_DEFINE_PART  ( 3,  SPNP_UPHORZ,    UpHorz,    db_states_SPNP_UPHORZ),
    DB_DEFINE_PART  ( 4,  SPNP_DOWNHORZ,  DownHorz,  db_states_SPNP_DOWNHORZ)
};


/******************
 *** StartPanel ***
 ******************/

static const db_state_t db_states_SPP_MOREPROGRAMSARROW[] = {
    DB_DEFINE_STATE ( 1,  SPS_NORMAL,    Normal),
    DB_DEFINE_STATE ( 2,  SPS_HOT,       Hot),
    DB_DEFINE_STATE ( 3,  SPS_PRESSED,   Pressed)
};

static const db_state_t db_states_SPP_LOGOFFBUTTONS[] = {
    DB_DEFINE_STATE ( 1,  SPLS_NORMAL,    Normal),
    DB_DEFINE_STATE ( 2,  SPLS_HOT,       Hot),
    DB_DEFINE_STATE ( 3,  SPLS_PRESSED,   Pressed)
};

static const db_state_t db_states_SPP_MOREPROGRAMSTAB[] = {
    DB_DEFINE_STATE ( 1,  SPMPT_NORMAL,    Normal),
    DB_DEFINE_STATE ( 2,  SPMPT_HOT,       Hot),
    DB_DEFINE_STATE ( 3,  SPMPT_SELECTED,  Selected),
    DB_DEFINE_STATE ( 4,  SPMPT_DISABLED,  Disabled),
    DB_DEFINE_STATE ( 5,  SPMPT_FOCUSED,   Focused)
};

static const db_state_t db_states_SPP_SOFTWAREEXPLORER[] = {
    DB_DEFINE_STATE ( 1,  SPSE_NORMAL,    Normal),
    DB_DEFINE_STATE ( 2,  SPSE_HOT,       Hot),
    DB_DEFINE_STATE ( 3,  SPSE_SELECTED,  Selected),
    DB_DEFINE_STATE ( 4,  SPSE_DISABLED,  Disabled),
    DB_DEFINE_STATE ( 5,  SPSE_FOCUSED,   Focused)
};

static const db_state_t db_states_SPP_OPENBOX[] = {
    DB_DEFINE_STATE ( 1,  SPOB_NORMAL,    Normal),
    DB_DEFINE_STATE ( 2,  SPOB_HOT,       Hot),
    DB_DEFINE_STATE ( 3,  SPOB_SELECTED,  Selected),
    DB_DEFINE_STATE ( 4,  SPOB_DISABLED,  Disabled),
    DB_DEFINE_STATE ( 5,  SPOB_FOCUSED,   Focused)
};

static const db_state_t db_states_SPP_MOREPROGRAMSARROWBACK[] = {
    DB_DEFINE_STATE ( 1,  SPSB_NORMAL,    Normal),
    DB_DEFINE_STATE ( 2,  SPSB_HOT,       Hot),
    DB_DEFINE_STATE ( 3,  SPSB_PRESSED,   Pressed)
};

static const db_part_t db_parts_STARTPANEL[] = {
    DB_DEFINE_PART_ ( 1,  SPP_USERPANE,                   UserPane),
    DB_DEFINE_PART_ ( 2,  SPP_MOREPROGRAMS,               MorePrograms),
    DB_DEFINE_PART  ( 3,  SPP_MOREPROGRAMSARROW,          MoreProgramsArrow,          db_states_SPP_MOREPROGRAMSARROW),
    DB_DEFINE_PART_ ( 4,  SPP_PROGLIST,                   ProgList),
    DB_DEFINE_PART_ ( 5,  SPP_PROGLISTSEPARATOR,          ProgListSeparator),
    DB_DEFINE_PART_ ( 6,  SPP_PLACESLIST,                 PlaceList),
    DB_DEFINE_PART_ ( 7,  SPP_PLACESLISTSEPARATOR,        PlaceListSeparator),
    DB_DEFINE_PART_ ( 8,  SPP_LOGOFF,                     LogOff),
    DB_DEFINE_PART  ( 9,  SPP_LOGOFFBUTTONS,              LogOffButtons,              db_states_SPP_LOGOFFBUTTONS),
    DB_DEFINE_PART_ (10,  SPP_USERPICTURE,                UserPicture),
    DB_DEFINE_PART_ (11,  SPP_PREVIEW,                    Preview),
    DB_DEFINE_PART  (12,  SPP_MOREPROGRAMSTAB,            MoreProgramsTab,            db_states_SPP_MOREPROGRAMSTAB),
    DB_DEFINE_PART_ (13,  SPP_NSCHOST,                    NscHost),
    DB_DEFINE_PART  (14,  SPP_SOFTWAREEXPLORER,           SoftwareExplorer,           db_states_SPP_SOFTWAREEXPLORER),
    DB_DEFINE_PART  (15,  SPP_OPENBOX,                    OpenBox,                    db_states_SPP_OPENBOX),
    DB_DEFINE_PART_ (16,  SPP_SEARCHVIEW,                 SearchView),
    DB_DEFINE_PART  (17,  SPP_MOREPROGRAMSARROWBACK,      MoreProgramsArrowBack,      db_states_SPP_MOREPROGRAMSARROWBACK),
    DB_DEFINE_PART_ (18,  SPP_TOPMATCH,                   TopMatch),
    DB_DEFINE_PART  (19,  SPP_LOGOFFSPLITBUTTONDROPDOWN,  LogOffSplitButtonDropDown,  db_states_SPP_LOGOFFBUTTONS)
};


/**************
 *** Static ***
 **************/

static const db_part_t db_parts_STATIC[] = {
    DB_DEFINE_PART_ ( 1,  STAT_TEXT,  Text)
};


/**************
 *** Status ***
 **************/

static const db_part_t db_parts_STATUS[] = {
    DB_DEFINE_PART_ ( 1,  SP_PANE,         Pane),
    DB_DEFINE_PART_ ( 2,  SP_GRIPPERPANE,  GripperPane),
    DB_DEFINE_PART_ ( 3,  SP_GRIPPER,      Gripper)
};


/***********
 *** Tab ***
 ***********/

static const db_state_t db_states_TABP_TABITEM[] = {
    DB_DEFINE_STATE ( 1,  TIS_NORMAL,    Normal),
    DB_DEFINE_STATE ( 2,  TIS_HOT,       Hot),
    DB_DEFINE_STATE ( 3,  TIS_SELECTED,  Selected),
    DB_DEFINE_STATE ( 4,  TIS_DISABLED,  Disabled),
    DB_DEFINE_STATE ( 5,  TIS_FOCUSED,   Focused)
};

static const db_state_t db_states_TABP_TABITEMLEFTEDGE[] = {
    DB_DEFINE_STATE ( 1,  TILES_NORMAL,    Normal),
    DB_DEFINE_STATE ( 2,  TILES_HOT,       Hot),
    DB_DEFINE_STATE ( 3,  TILES_SELECTED,  Selected),
    DB_DEFINE_STATE ( 4,  TILES_DISABLED,  Disabled),
    DB_DEFINE_STATE ( 5,  TILES_FOCUSED,   Focused)
};

static const db_state_t db_states_TABP_TABITEMRIGHTEDGE[] = {
    DB_DEFINE_STATE ( 1,  TIRES_NORMAL,    Normal),
    DB_DEFINE_STATE ( 2,  TIRES_HOT,       Hot),
    DB_DEFINE_STATE ( 3,  TIRES_SELECTED,  Selected),
    DB_DEFINE_STATE ( 4,  TIRES_DISABLED,  Disabled),
    DB_DEFINE_STATE ( 5,  TIRES_FOCUSED,   Focused)
};

static const db_state_t db_states_TABP_TABITEMBOTHEDGE[] = {
    DB_DEFINE_STATE ( 1,  TIBES_NORMAL,    Normal),
    DB_DEFINE_STATE ( 2,  TIBES_HOT,       Hot),
    DB_DEFINE_STATE ( 3,  TIBES_SELECTED,  Selected),
    DB_DEFINE_STATE ( 4,  TIBES_DISABLED,  Disabled),
    DB_DEFINE_STATE ( 5,  TIBES_FOCUSED,   Focused)
};

static const db_state_t db_states_TABP_TOPTABITEM[] = {
    DB_DEFINE_STATE ( 1,  TTIS_NORMAL,    Normal),
    DB_DEFINE_STATE ( 2,  TTIS_HOT,       Hot),
    DB_DEFINE_STATE ( 3,  TTIS_SELECTED,  Selected),
    DB_DEFINE_STATE ( 4,  TTIS_DISABLED,  Disabled),
    DB_DEFINE_STATE ( 5,  TTIS_FOCUSED,   Focused)
};

static const db_state_t db_states_TABP_TOPTABITEMLEFTEDGE[] = {
    DB_DEFINE_STATE ( 1,  TTILES_NORMAL,    Normal),
    DB_DEFINE_STATE ( 2,  TTILES_HOT,       Hot),
    DB_DEFINE_STATE ( 3,  TTILES_SELECTED,  Selected),
    DB_DEFINE_STATE ( 4,  TTILES_DISABLED,  Disabled),
    DB_DEFINE_STATE ( 5,  TTILES_FOCUSED,   Focused)
};

static const db_state_t db_states_TABP_TOPTABITEMRIGHTEDGE[] = {
    DB_DEFINE_STATE ( 1,  TTIRES_NORMAL,    Normal),
    DB_DEFINE_STATE ( 2,  TTIRES_HOT,       Hot),
    DB_DEFINE_STATE ( 3,  TTIRES_SELECTED,  Selected),
    DB_DEFINE_STATE ( 4,  TTIRES_DISABLED,  Disabled),
    DB_DEFINE_STATE ( 5,  TTIRES_FOCUSED,   Focused)
};

static const db_state_t db_states_TABP_TOPTABITEMBOTHEDGE[] = {
    DB_DEFINE_STATE ( 1,  TTIBES_NORMAL,    Normal),
    DB_DEFINE_STATE ( 2,  TTIBES_HOT,       Hot),
    DB_DEFINE_STATE ( 3,  TTIBES_SELECTED,  Selected),
    DB_DEFINE_STATE ( 4,  TTIBES_DISABLED,  Disabled),
    DB_DEFINE_STATE ( 5,  TTIBES_FOCUSED,   Focused)
};

static const db_part_t db_parts_TAB[] = {
    DB_DEFINE_PART  ( 1,  TABP_TABITEM,              TabItem,              db_states_TABP_TABITEM),
    DB_DEFINE_PART  ( 2,  TABP_TABITEMLEFTEDGE,      TabItemLeftEdge,      db_states_TABP_TABITEMLEFTEDGE),
    DB_DEFINE_PART  ( 3,  TABP_TABITEMRIGHTEDGE,     TabItemRightEdge,     db_states_TABP_TABITEMRIGHTEDGE),
    DB_DEFINE_PART  ( 4,  TABP_TABITEMBOTHEDGE,      TabItemBothEdge,      db_states_TABP_TABITEMBOTHEDGE),
    DB_DEFINE_PART  ( 5,  TABP_TOPTABITEM,           TopTabItem,           db_states_TABP_TOPTABITEM),
    DB_DEFINE_PART  ( 6,  TABP_TOPTABITEMLEFTEDGE,   TopTabItemLeftEdge,   db_states_TABP_TOPTABITEMLEFTEDGE),
    DB_DEFINE_PART  ( 7,  TABP_TOPTABITEMRIGHTEDGE,  TopTabItemRightEdge,  db_states_TABP_TOPTABITEMRIGHTEDGE),
    DB_DEFINE_PART  ( 8,  TABP_TOPTABITEMBOTHEDGE,   TopTabItemBothEdge,   db_states_TABP_TOPTABITEMBOTHEDGE),
    DB_DEFINE_PART_ ( 9,  TABP_PANE,                 Pane),
    DB_DEFINE_PART_ (10,  TABP_BODY,                 Body),
    DB_DEFINE_PART_ (11,  TABP_AEROWIZARDBODY,       AeroWizardBody)
};


/****************
 *** TaskBand ***
 ****************/

static const db_part_t db_parts_TASKBAND[] = {
    DB_DEFINE_PART_ ( 1,  TDP_GROUPCOUNT,            GroupCount),
    DB_DEFINE_PART_ ( 2,  TDP_FLASHBUTTON,           FlashButton),
    DB_DEFINE_PART_ ( 3,  TDP_FLASHBUTTONGROUPMENU,  FlashButtonGroupMenu)
};


/***************
 *** TaskBar ***
 ***************/

static const db_part_t db_parts_TASKBAR[] = {
    DB_DEFINE_PART_ ( 1,  TBP_BACKGROUNDBOTTOM,  BackgroundBottom),
    DB_DEFINE_PART_ ( 2,  TBP_BACKGROUNDRIGHT,   BackgroundRight),
    DB_DEFINE_PART_ ( 3,  TBP_BACKGROUNDTOP,     BackgroundTop),
    DB_DEFINE_PART_ ( 4,  TBP_BACKGROUNDLEFT,    BackgroundLeft),
    DB_DEFINE_PART_ ( 5,  TBP_SIZINGBARBOTTOM,   SizingBarBottom),
    DB_DEFINE_PART_ ( 6,  TBP_SIZINGBARRIGHT,    SizingBarRight),
    DB_DEFINE_PART_ ( 7,  TBP_SIZINGBARTOP,      SizingBarTop),
    DB_DEFINE_PART_ ( 8,  TBP_SIZINGBARLEFT,     SizingBarLeft)
};


/******************
 *** TaskDialog ***
 ******************/

static const db_state_t db_states_TDLG_CONTENTPANE[] = {
    DB_DEFINE_STATE ( 1,  TDLGCPS_STANDALONE,  Standalone)
};

static const db_state_t db_states_TDLG_EXPANDOBUTTON[] = {
    DB_DEFINE_STATE ( 1,  TDLGEBS_NORMAL,           Normal),
    DB_DEFINE_STATE ( 2,  TDLGEBS_HOVER,            Hover),
    DB_DEFINE_STATE ( 3,  TDLGEBS_PRESSED,          Pressed),
    DB_DEFINE_STATE ( 4,  TDLGEBS_EXPANDEDNORMAL,   ExpandedNormal),
    DB_DEFINE_STATE ( 5,  TDLGEBS_EXPANDEDHOVER,    ExpandedHover),
    DB_DEFINE_STATE ( 6,  TDLGEBS_EXPANDEDPRESSED,  ExpandedPressed)
};

static const db_part_t db_parts_TASKDIALOG[] = {
    DB_DEFINE_PART_ ( 1,  TDLG_PRIMARYPANEL,         PrimaryPanel),
    DB_DEFINE_PART_ ( 2,  TDLG_MAININSTRUCTIONPANE,  MainInstructionPane),
    DB_DEFINE_PART_ ( 3,  TDLG_MAINICON,             MainIcon),
    DB_DEFINE_PART  ( 4,  TDLG_CONTENTPANE,          ContentPane,          db_states_TDLG_CONTENTPANE),
    DB_DEFINE_PART_ ( 5,  TDLG_CONTENTICON,          ContentIcon),
    DB_DEFINE_PART_ ( 6,  TDLG_EXPANDEDCONTENT,      ExpandedContent),
    DB_DEFINE_PART_ ( 7,  TDLG_COMMANDLINKPANE,      CommandLinkPane),
    DB_DEFINE_PART_ ( 8,  TDLG_SECONDARYPANEL,       SecondaryPanel),
    DB_DEFINE_PART_ ( 9,  TDLG_CONTROLPANE,          ControlPane),
    DB_DEFINE_PART_ (10,  TDLG_BUTTONSECTION,        ButtonSection),
    DB_DEFINE_PART_ (11,  TDLG_BUTTONWRAPPER,        ButtonWrapper),
    DB_DEFINE_PART_ (12,  TDLG_EXPANDOTEXT,          ExpandoText),
    DB_DEFINE_PART  (13,  TDLG_EXPANDOBUTTON,        ExpandoButton,        db_states_TDLG_EXPANDOBUTTON),
    DB_DEFINE_PART_ (14,  TDLG_VERIFICATIONTEXT,     VerificationText),
    DB_DEFINE_PART_ (15,  TDLG_FOOTNOTEPANE,         FootnotePane),
    DB_DEFINE_PART_ (16,  TDLG_FOOTNOTEAREA,         FootnoteArea),
    DB_DEFINE_PART_ (17,  TDLG_FOOTNOTESEPARATOR,    FootnoteSeparator),
    DB_DEFINE_PART_ (18,  TDLG_EXPANDEDFOOTERAREA,   ExpandedFootArea),
    DB_DEFINE_PART_ (19,  TDLG_PROGRESSBAR,          ProgressBar),
    DB_DEFINE_PART_ (20,  TDLG_IMAGEALIGNMENT,       ImageAlignement),
    DB_DEFINE_PART_ (21,  TDLG_RADIOBUTTONPANE,      RadioButtonPane)
};


/*****************
 *** TextStyle ***
 *****************/

static const db_state_t db_states_TEXT_HYPERLINKTEXT[] = {
    DB_DEFINE_STATE ( 1,  TS_HYPERLINK_NORMAL,    Normal),
    DB_DEFINE_STATE ( 2,  TS_HYPERLINK_HOT,       Hot),
    DB_DEFINE_STATE ( 3,  TS_HYPERLINK_PRESSED,   Pressed),
    DB_DEFINE_STATE ( 4,  TS_HYPERLINK_DISABLED,  Disabled)
};

static const db_state_t db_states_TEXT_CONTROLLABEL[] = {
    DB_DEFINE_STATE ( 1,  TS_CONTROLLABEL_NORMAL,    Normal),
    DB_DEFINE_STATE ( 2,  TS_CONTROLLABEL_DISABLED,  Disabled)
};

static const db_part_t db_parts_TEXTSTYLE[] = {
    DB_DEFINE_PART_ ( 1,  TEXT_MAININSTRUCTION,  MainInstruction),
    DB_DEFINE_PART_ ( 2,  TEXT_INSTRUCTION,      Instruction),
    DB_DEFINE_PART_ ( 3,  TEXT_BODYTITLE,        BodyTitle),
    DB_DEFINE_PART_ ( 4,  TEXT_BODYTEXT,         BodyText),
    DB_DEFINE_PART_ ( 5,  TEXT_SECONDARYTEXT,    SecondaryText),
    DB_DEFINE_PART  ( 6,  TEXT_HYPERLINKTEXT,    HyperLinkText,    db_states_TEXT_HYPERLINKTEXT),
    DB_DEFINE_PART_ ( 7,  TEXT_EXPANDED,         Expanded),
    DB_DEFINE_PART_ ( 8,  TEXT_LABEL,            Label),
    DB_DEFINE_PART  ( 9,  TEXT_CONTROLLABEL,     ControlLabel,     db_states_TEXT_CONTROLLABEL)
};


/***************
 *** Toolbar ***
 **************/

static const db_state_t db_states_TP_shared[] = {
    DB_DEFINE_STATE ( 1,  TS_NORMAL,        Normal),
    DB_DEFINE_STATE ( 2,  TS_HOT,           Hot),
    DB_DEFINE_STATE ( 3,  TS_PRESSED,       Pressed),
    DB_DEFINE_STATE ( 4,  TS_DISABLED,      Disabled),
    DB_DEFINE_STATE ( 5,  TS_CHECKED,       Checked),
    DB_DEFINE_STATE ( 6,  TS_HOTCHECKED,    HotChecked),
    DB_DEFINE_STATE ( 7,  TS_NEARHOT,       NearHot),
    DB_DEFINE_STATE ( 8,  TS_OTHERSIDEHOT,  OtherSideHot)
};

static const db_part_t db_parts_TOOLBAR[] = {
    DB_DEFINE_PART  ( 1,  TP_BUTTON,               Button,               db_states_TP_shared),
    DB_DEFINE_PART  ( 2,  TP_DROPDOWNBUTTON,       DropDownButton,       db_states_TP_shared),
    DB_DEFINE_PART  ( 3,  TP_SPLITBUTTON,          SplitButton,          db_states_TP_shared),
    DB_DEFINE_PART  ( 4,  TP_SPLITBUTTONDROPDOWN,  SplitButtonDropDown,  db_states_TP_shared),
    DB_DEFINE_PART  ( 5,  TP_SEPARATOR,            Separator,            db_states_TP_shared),
    DB_DEFINE_PART  ( 6,  TP_SEPARATORVERT,        SeparatorVert,        db_states_TP_shared),
    DB_DEFINE_PART  ( 7,  TP_DROPDOWNBUTTONGLYPH,  DropDownButtonGlyph,  db_states_TP_shared)
};


/***************
 *** Tooltip ***
 ***************/

static const db_state_t db_states_TTP_STANDARD[] = {
    DB_DEFINE_STATE ( 1,  TTSS_NORMAL,  Normal),
    DB_DEFINE_STATE ( 2,  TTSS_LINK,    Link)
};

static const db_state_t db_states_TTP_BALLOON[] = {
    DB_DEFINE_STATE ( 1,  TTBS_NORMAL,  Normal),
    DB_DEFINE_STATE ( 2,  TTBS_LINK,    Link)
};

static const db_state_t db_states_TTP_CLOSE[] = {
    DB_DEFINE_STATE ( 1,  TTCS_NORMAL,   Normal),
    DB_DEFINE_STATE ( 2,  TTCS_HOT,      Hot),
    DB_DEFINE_STATE ( 3,  TTCS_PRESSED,  Pressed)
};

static const db_state_t db_states_TTP_BALLOONSTEM[] = {
    DB_DEFINE_STATE ( 1,  TTBSS_POINTINGUPLEFTWALL,     PointingUpLeftWall),
    DB_DEFINE_STATE ( 2,  TTBSS_POINTINGUPCENTERED,     PointingUpCentered),
    DB_DEFINE_STATE ( 3,  TTBSS_POINTINGUPRIGHTWALL,    PointingUpRightWall),
    DB_DEFINE_STATE ( 4,  TTBSS_POINTINGDOWNRIGHTWALL,  PointingDownRightWall),
    DB_DEFINE_STATE ( 5,  TTBSS_POINTINGDOWNCENTERED,   PointingDownCentered),
    DB_DEFINE_STATE ( 6,  TTBSS_POINTINGDOWNLEFTWALL,   PointingDownLeftWall)
};

static const db_state_t db_states_TTP_WRENCH[] = {
    DB_DEFINE_STATE ( 1,  TTWS_NORMAL,   Normal),
    DB_DEFINE_STATE ( 2,  TTWS_HOT,      Hot),
    DB_DEFINE_STATE ( 3,  TTWS_PRESSED,  Pressed)
};

static const db_part_t db_parts_TOOLTIP[] = {
    DB_DEFINE_PART  ( 1,  TTP_STANDARD,       Standard,       db_states_TTP_STANDARD),
    DB_DEFINE_PART  ( 2,  TTP_STANDARDTITLE,  StandardTitle,  db_states_TTP_STANDARD),
    DB_DEFINE_PART  ( 3,  TTP_BALLOON,        Balloon,        db_states_TTP_BALLOON),
    DB_DEFINE_PART  ( 4,  TTP_BALLOONTITLE,   BalloonTitle,   db_states_TTP_BALLOON),
    DB_DEFINE_PART  ( 5,  TTP_CLOSE,          Close,          db_states_TTP_CLOSE),
    DB_DEFINE_PART  ( 6,  TTP_BALLOONSTEM,    BalloonStem,    db_states_TTP_BALLOONSTEM),
    DB_DEFINE_PART  ( 7,  TTP_WRENCH,         Wrench,         db_states_TTP_WRENCH)
};


/****************
 *** Trackbar ***
 ****************/

static const db_state_t db_states_TKP_TRACK[] = {
    DB_DEFINE_STATE ( 1,  TRS_NORMAL,   Normal)
};

static const db_state_t db_states_TKP_TRACKVERT[] = {
    DB_DEFINE_STATE ( 1,  TRVS_NORMAL,   Normal)
};

static const db_state_t db_states_TKP_THUMB[] = {
    DB_DEFINE_STATE ( 1,  TUS_NORMAL,    Normal),
    DB_DEFINE_STATE ( 2,  TUS_HOT,       Hot),
    DB_DEFINE_STATE ( 3,  TUS_PRESSED,   Pressed),
    DB_DEFINE_STATE ( 4,  TUS_FOCUSED,   Focused),
    DB_DEFINE_STATE ( 5,  TUS_DISABLED,  Disabled)
};

static const db_state_t db_states_TKP_THUMBBOTTOM[] = {
    DB_DEFINE_STATE ( 1,  TUBS_NORMAL,    Normal),
    DB_DEFINE_STATE ( 2,  TUBS_HOT,       Hot),
    DB_DEFINE_STATE ( 3,  TUBS_PRESSED,   Pressed),
    DB_DEFINE_STATE ( 4,  TUBS_FOCUSED,   Focused),
    DB_DEFINE_STATE ( 5,  TUBS_DISABLED,  Disabled)
};

static const db_state_t db_states_TKP_THUMBTOP[] = {
    DB_DEFINE_STATE ( 1,  TUTS_NORMAL,    Normal),
    DB_DEFINE_STATE ( 2,  TUTS_HOT,       Hot),
    DB_DEFINE_STATE ( 3,  TUTS_PRESSED,   Pressed),
    DB_DEFINE_STATE ( 4,  TUTS_FOCUSED,   Focused),
    DB_DEFINE_STATE ( 5,  TUTS_DISABLED,  Disabled)
};

static const db_state_t db_states_TKP_THUMBVERT[] = {
    DB_DEFINE_STATE ( 1,  TUVS_NORMAL,    Normal),
    DB_DEFINE_STATE ( 2,  TUVS_HOT,       Hot),
    DB_DEFINE_STATE ( 3,  TUVS_PRESSED,   Pressed),
    DB_DEFINE_STATE ( 4,  TUVS_FOCUSED,   Focused),
    DB_DEFINE_STATE ( 5,  TUVS_DISABLED,  Disabled)
};

static const db_state_t db_states_TKP_THUMBLEFT[] = {
    DB_DEFINE_STATE ( 1,  TUVLS_NORMAL,    Normal),
    DB_DEFINE_STATE ( 2,  TUVLS_HOT,       Hot),
    DB_DEFINE_STATE ( 3,  TUVLS_PRESSED,   Pressed),
    DB_DEFINE_STATE ( 4,  TUVLS_FOCUSED,   Focused),
    DB_DEFINE_STATE ( 5,  TUVLS_DISABLED,  Disabled)
};

static const db_state_t db_states_TKP_THUMBRIGHT[] = {
    DB_DEFINE_STATE ( 1,  TUVRS_NORMAL,    Normal),
    DB_DEFINE_STATE ( 2,  TUVRS_HOT,       Hot),
    DB_DEFINE_STATE ( 3,  TUVRS_PRESSED,   Pressed),
    DB_DEFINE_STATE ( 4,  TUVRS_FOCUSED,   Focused),
    DB_DEFINE_STATE ( 5,  TUVRS_DISABLED,  Disabled)
};

static const db_state_t db_states_TKP_TICS[] = {
    DB_DEFINE_STATE ( 1,  TSS_NORMAL,   Normal)
};

static const db_state_t db_states_TKP_TICSVERT[] = {
    DB_DEFINE_STATE ( 1,  TSVS_NORMAL,   Normal)
};

static const db_part_t db_parts_TRACKBAR[] = {
    DB_DEFINE_PART  ( 1,  TKP_TRACK,        Track,        db_states_TKP_TRACK),
    DB_DEFINE_PART  ( 2,  TKP_TRACKVERT,    TrackVert,    db_states_TKP_TRACKVERT),
    DB_DEFINE_PART  ( 3,  TKP_THUMB,        Thumb,        db_states_TKP_THUMB),
    DB_DEFINE_PART  ( 4,  TKP_THUMBBOTTOM,  ThumbBottom,  db_states_TKP_THUMBBOTTOM),
    DB_DEFINE_PART  ( 5,  TKP_THUMBTOP,     ThumbTop,     db_states_TKP_THUMBTOP),
    DB_DEFINE_PART  ( 6,  TKP_THUMBVERT,    ThumbVert,    db_states_TKP_THUMBVERT),
    DB_DEFINE_PART  ( 7,  TKP_THUMBLEFT,    ThumbLeft,    db_states_TKP_THUMBLEFT),
    DB_DEFINE_PART  ( 8,  TKP_THUMBRIGHT,   ThumbRight,   db_states_TKP_THUMBRIGHT),
    DB_DEFINE_PART  ( 9,  TKP_TICS,         Tics,         db_states_TKP_TICS),
    DB_DEFINE_PART  (10,  TKP_TICSVERT,     TicsVert,     db_states_TKP_TICSVERT)
};


/******************
 *** TrayNotify ***
 ******************/

static const db_part_t db_parts_TRAYNOTIFY[] = {
    DB_DEFINE_PART_ ( 1,  TNP_BACKGROUND,      Background),
    DB_DEFINE_PART_ ( 2,  TNP_ANIMBACKGROUND,  AnimBackground)
};


/****************
 *** TreeView ***
 ****************/

static const db_state_t db_states_TVP_TREEITEM[] = {
    DB_DEFINE_STATE ( 1,  TREIS_NORMAL,            Normal),
    DB_DEFINE_STATE ( 2,  TREIS_HOT,               Hot),
    DB_DEFINE_STATE ( 3,  TREIS_SELECTED,          Selected),
    DB_DEFINE_STATE ( 4,  TREIS_DISABLED,          Disabled),
    DB_DEFINE_STATE ( 5,  TREIS_SELECTEDNOTFOCUS,  SelectedNotFocus),
    DB_DEFINE_STATE ( 6,  TREIS_HOTSELECTED,       HotSelected)
};

static const db_state_t db_states_TVP_GLYPH[] = {
    DB_DEFINE_STATE ( 1,  GLPS_CLOSED,  Closed),
    DB_DEFINE_STATE ( 2,  GLPS_OPENED,  Opened)
};

static const db_state_t db_states_TVP_HOTGLYPH[] = {
    DB_DEFINE_STATE ( 1,  HGLPS_CLOSED,  Closed),
    DB_DEFINE_STATE ( 2,  HGLPS_OPENED,  Opened)
};

static const db_part_t db_parts_TREEVIEW[] = {
    DB_DEFINE_PART  ( 1,  TVP_TREEITEM,  TreeItem,  db_states_TVP_TREEITEM),
    DB_DEFINE_PART  ( 2,  TVP_GLYPH,     Glyph,     db_states_TVP_GLYPH),
    DB_DEFINE_PART_ ( 3,  TVP_BRANCH,    Branch),
    DB_DEFINE_PART  ( 4,  TVP_HOTGLYPH,  HotGlyph,  db_states_TVP_HOTGLYPH)
};


/**************
 *** Window ***
 **************/

static const db_state_t db_states_WP_CAPTION[] = {
    DB_DEFINE_STATE ( 1,  CS_ACTIVE,    Active),
    DB_DEFINE_STATE ( 2,  CS_INACTIVE,  Inactive),
    DB_DEFINE_STATE ( 3,  CS_DISABLED,  Disabled)
};

static const db_state_t db_states_WP_MINCAPTION[] = {
    DB_DEFINE_STATE ( 1,  MNCS_ACTIVE,    Active),
    DB_DEFINE_STATE ( 2,  MNCS_INACTIVE,  Inactive),
    DB_DEFINE_STATE ( 3,  MNCS_DISABLED,  Disabled)
};

static const db_state_t db_states_WP_MAXCAPTION[] = {
    DB_DEFINE_STATE ( 1,  MXCS_ACTIVE,    Active),
    DB_DEFINE_STATE ( 2,  MXCS_INACTIVE,  Inactive),
    DB_DEFINE_STATE ( 3,  MXCS_DISABLED,  Disabled)
};

static const db_state_t db_states_WP_SYSBUTTON[] = {
    DB_DEFINE_STATE ( 1,  SBS_NORMAL,    Normal),
    DB_DEFINE_STATE ( 2,  SBS_HOT,       Hot),
    DB_DEFINE_STATE ( 3,  SBS_PUSHED,    Pushed),
    DB_DEFINE_STATE ( 4,  SBS_DISABLED,  Disabled)
};

static const db_state_t db_states_WP_MINBUTTON[] = {
    DB_DEFINE_STATE ( 1,  MINBS_NORMAL,    Normal),
    DB_DEFINE_STATE ( 2,  MINBS_HOT,       Hot),
    DB_DEFINE_STATE ( 3,  MINBS_PUSHED,    Pushed),
    DB_DEFINE_STATE ( 4,  MINBS_DISABLED,  Disabled)
};

static const db_state_t db_states_WP_MAXBUTTON[] = {
    DB_DEFINE_STATE ( 1,  MAXBS_NORMAL,    Normal),
    DB_DEFINE_STATE ( 2,  MAXBS_HOT,       Hot),
    DB_DEFINE_STATE ( 3,  MAXBS_PUSHED,    Pushed),
    DB_DEFINE_STATE ( 4,  MAXBS_DISABLED,  Disabled)
};

static const db_state_t db_states_WP_CLOSEBUTTON[] = {
    DB_DEFINE_STATE ( 1,  CBS_NORMAL,    Normal),
    DB_DEFINE_STATE ( 2,  CBS_HOT,       Hot),
    DB_DEFINE_STATE ( 3,  CBS_PUSHED,    Pushed),
    DB_DEFINE_STATE ( 4,  CBS_DISABLED,  Disabled)
};

static const db_state_t db_states_WP_RESTOREBUTTON[] = {
    DB_DEFINE_STATE ( 1,  RBS_NORMAL,    Normal),
    DB_DEFINE_STATE ( 2,  RBS_HOT,       Hot),
    DB_DEFINE_STATE ( 3,  RBS_PUSHED,    Pushed),
    DB_DEFINE_STATE ( 4,  RBS_DISABLED,  Disabled)
};

static const db_state_t db_states_WP_HELPBUTTON[] = {
    DB_DEFINE_STATE ( 1,  HBS_NORMAL,    Normal),
    DB_DEFINE_STATE ( 2,  HBS_HOT,       Hot),
    DB_DEFINE_STATE ( 3,  HBS_PUSHED,    Pushed),
    DB_DEFINE_STATE ( 4,  HBS_DISABLED,  Disabled)
};

static const db_state_t db_states_WP_HORZSCROLL[] = {
    DB_DEFINE_STATE ( 1,  HSS_NORMAL,    Normal),
    DB_DEFINE_STATE ( 2,  HSS_HOT,       Hot),
    DB_DEFINE_STATE ( 3,  HSS_PUSHED,    Pushed),
    DB_DEFINE_STATE ( 4,  HSS_DISABLED,  Disabled)
};

static const db_state_t db_states_WP_HORZTHUMB[] = {
    DB_DEFINE_STATE ( 1,  HTS_NORMAL,    Normal),
    DB_DEFINE_STATE ( 2,  HTS_HOT,       Hot),
    DB_DEFINE_STATE ( 3,  HTS_PUSHED,    Pushed),
    DB_DEFINE_STATE ( 4,  HTS_DISABLED,  Disabled)
};

static const db_state_t db_states_WP_VERTSCROLL[] = {
    DB_DEFINE_STATE ( 1,  VSS_NORMAL,    Normal),
    DB_DEFINE_STATE ( 2,  VSS_HOT,       Hot),
    DB_DEFINE_STATE ( 3,  VSS_PUSHED,    Pushed),
    DB_DEFINE_STATE ( 4,  VSS_DISABLED,  Disabled)
};

static const db_state_t db_states_WP_VERTTHUMB[] = {
    DB_DEFINE_STATE ( 1,  VTS_NORMAL,    Normal),
    DB_DEFINE_STATE ( 2,  VTS_HOT,       Hot),
    DB_DEFINE_STATE ( 3,  VTS_PUSHED,    Pushed),
    DB_DEFINE_STATE ( 4,  VTS_DISABLED,  Disabled)
};

static const db_state_t db_states_WP_FRAME[] = {
    DB_DEFINE_STATE ( 1,  FS_ACTIVE,    Active),
    DB_DEFINE_STATE ( 2,  FS_INACTIVE,  Inactive)
};

static const db_part_t db_parts_WINDOW[] = {
    DB_DEFINE_PART  ( 1,  WP_CAPTION,                         Caption,                        db_states_WP_CAPTION),
    DB_DEFINE_PART  ( 2,  WP_SMALLCAPTION,                    SmallCaption,                   db_states_WP_CAPTION),
    DB_DEFINE_PART  ( 3,  WP_MINCAPTION,                      MinCaption,                     db_states_WP_MINCAPTION),
    DB_DEFINE_PART  ( 4,  WP_SMALLMINCAPTION,                 SmallMinCaption,                db_states_WP_MINCAPTION),
    DB_DEFINE_PART  ( 5,  WP_MAXCAPTION,                      MaxCaption,                     db_states_WP_MAXCAPTION),
    DB_DEFINE_PART  ( 6,  WP_SMALLMAXCAPTION,                 SmallMaxCaption,                db_states_WP_MAXCAPTION),
    DB_DEFINE_PART_ ( 7,  WP_FRAMELEFT,                       FrameLeft),
    DB_DEFINE_PART_ ( 8,  WP_FRAMERIGHT,                      FrameRight),
    DB_DEFINE_PART_ ( 9,  WP_FRAMEBOTTOM,                     FrameBottom),
    DB_DEFINE_PART_ (10,  WP_SMALLFRAMELEFT,                  SmallFrameLeft),
    DB_DEFINE_PART_ (11,  WP_SMALLFRAMERIGHT,                 SmallFrameRight),
    DB_DEFINE_PART_ (12,  WP_SMALLFRAMEBOTTOM,                SmallFrameBottom),
    DB_DEFINE_PART  (13,  WP_SYSBUTTON,                       SysButton,                      db_states_WP_SYSBUTTON),
    DB_DEFINE_PART  (14,  WP_MDISYSBUTTON,                    MdiSysButton,                   db_states_WP_SYSBUTTON),
    DB_DEFINE_PART  (15,  WP_MINBUTTON,                       MinButton,                      db_states_WP_MINBUTTON),
    DB_DEFINE_PART  (16,  WP_MDIMINBUTTON,                    MdiMinButton,                   db_states_WP_MINBUTTON),
    DB_DEFINE_PART  (17,  WP_MAXBUTTON,                       MaxButton,                      db_states_WP_MAXBUTTON),
    DB_DEFINE_PART  (18,  WP_CLOSEBUTTON,                     CloseButton,                    db_states_WP_CLOSEBUTTON),
    DB_DEFINE_PART  (19,  WP_SMALLCLOSEBUTTON,                SmallCloseButton,               db_states_WP_CLOSEBUTTON),
    DB_DEFINE_PART  (20,  WP_MDICLOSEBUTTON,                  MdiCloseButton,                 db_states_WP_CLOSEBUTTON),
    DB_DEFINE_PART  (21,  WP_RESTOREBUTTON,                   RestoreButton,                  db_states_WP_RESTOREBUTTON),
    DB_DEFINE_PART  (22,  WP_MDIRESTOREBUTTON,                MdiRestoreButton,               db_states_WP_RESTOREBUTTON),
    DB_DEFINE_PART  (23,  WP_HELPBUTTON,                      HelpButton,                     db_states_WP_HELPBUTTON),
    DB_DEFINE_PART  (24,  WP_MDIHELPBUTTON,                   MdiHelpButton,                  db_states_WP_HELPBUTTON),
    DB_DEFINE_PART  (25,  WP_HORZSCROLL,                      HorzScroll,                     db_states_WP_HORZSCROLL),
    DB_DEFINE_PART  (26,  WP_HORZTHUMB,                       HorzThumb,                      db_states_WP_HORZTHUMB),
    DB_DEFINE_PART  (27,  WP_VERTSCROLL,                      VertScroll,                     db_states_WP_VERTSCROLL),
    DB_DEFINE_PART  (28,  WP_VERTTHUMB,                       VertThumb,                      db_states_WP_VERTTHUMB),
    DB_DEFINE_PART_ (29,  WP_DIALOG,                          Dialog),
    DB_DEFINE_PART_ (30,  WP_CAPTIONSIZINGTEMPLATE,           CaptionSizingTemplate),
    DB_DEFINE_PART_ (31,  WP_SMALLCAPTIONSIZINGTEMPLATE,      SmallCaptionSizingTemplate),
    DB_DEFINE_PART_ (32,  WP_FRAMELEFTSIZINGTEMPLATE,         FrameLeftSizingTemplate),
    DB_DEFINE_PART_ (33,  WP_SMALLFRAMELEFTSIZINGTEMPLATE,    SmallFrameLeftSizingTemplate),
    DB_DEFINE_PART_ (34,  WP_FRAMERIGHTSIZINGTEMPLATE,        FrameRightSizingTemplate),
    DB_DEFINE_PART_ (35,  WP_SMALLFRAMERIGHTSIZINGTEMPLATE,   SmallFrameRightSizingTemplate),
    DB_DEFINE_PART_ (36,  WP_FRAMEBOTTOMSIZINGTEMPLATE,       FrameBottomSizingTemplate),
    DB_DEFINE_PART_ (37,  WP_SMALLFRAMEBOTTOMSIZINGTEMPLATE,  SmallFrameRightSizingTemplate),
    DB_DEFINE_PART  (38,  WP_FRAME,                           Frame,                          db_states_WP_FRAME)
};


/******************************
 *** Classes and Subclasses ***
 ******************************/

static const db_class_t db_classes_helper[] = {
    DB_DEFINE_CLASS(AddressBand,                                       db_parts_ADDRESSBAND),
        DB_DEFINE_SUBCLASS(AddressBand, AB,                            db_parts_ADDRESSBAND),
        DB_DEFINE_SUBCLASS(AddressBand, ABComposited,                  db_parts_ADDRESSBAND),
        DB_DEFINE_SUBCLASS(AddressBand, ABGreen,                       db_parts_ADDRESSBAND),
        DB_DEFINE_SUBCLASS(AddressBand, ABGreenComposited,             db_parts_ADDRESSBAND),
        DB_DEFINE_SUBCLASS(AddressBand, ABRed,                         db_parts_ADDRESSBAND),
        DB_DEFINE_SUBCLASS(AddressBand, ABRedComposited,               db_parts_ADDRESSBAND),
        DB_DEFINE_SUBCLASS(AddressBand, ABYellow,                      db_parts_ADDRESSBAND),
        DB_DEFINE_SUBCLASS(AddressBand, ABYellowComposited,            db_parts_ADDRESSBAND),
    DB_DEFINE_CLASS(AeroWizard,                                        db_parts_AEROWIZARD),
    DB_DEFINE_CLASS(Button,                                            db_parts_BUTTON),
        DB_DEFINE_SUBCLASS(Button, InfoPaneButton,                     db_parts_BUTTON),
        DB_DEFINE_SUBCLASS(Button, InfoPaneStatic,                     db_parts_BUTTON),
        DB_DEFINE_SUBCLASS(Button, ShowDesktop,                        db_parts_BUTTON),
        DB_DEFINE_SUBCLASS(Button, VerticalShowDesktop,                db_parts_BUTTON),
        DB_DEFINE_SUBCLASS(Button, Start,                              db_parts_BUTTON),
        DB_DEFINE_SUBCLASS(Button, TrayNotifyHoriz,                    db_parts_BUTTON),
        DB_DEFINE_SUBCLASS(Button, TrayNotifyHorizComposited,          db_parts_BUTTON),
        DB_DEFINE_SUBCLASS(Button, TrayNotifyHorizOpen,                db_parts_BUTTON),
        DB_DEFINE_SUBCLASS(Button, TrayNotifyHorizOpenComposited,      db_parts_BUTTON),
        DB_DEFINE_SUBCLASS(Button, TrayNotifyVert,                     db_parts_BUTTON),
        DB_DEFINE_SUBCLASS(Button, TrayNotifyVertComposited,           db_parts_BUTTON),
        DB_DEFINE_SUBCLASS(Button, TrayNotifyVertOpen,                 db_parts_BUTTON),
        DB_DEFINE_SUBCLASS(Button, TrayNotifyVertOpenComposited,       db_parts_BUTTON),
    DB_DEFINE_CLASS(Clock,                                             db_parts_CLOCK),
        DB_DEFINE_SUBCLASS(Clock, TrayNotify,                          db_parts_CLOCK),
        DB_DEFINE_SUBCLASS(Clock, TrayNotifyComposited,                db_parts_CLOCK),
    DB_DEFINE_CLASS(Combobox,                                          db_parts_COMBOBOX),
        DB_DEFINE_SUBCLASS(Combobox, Address,                          db_parts_COMBOBOX),
        DB_DEFINE_SUBCLASS(Combobox, AddressComposited,                db_parts_COMBOBOX),
        DB_DEFINE_SUBCLASS(Combobox, Communications,                   db_parts_COMBOBOX),
        DB_DEFINE_SUBCLASS(Combobox, InactiveAddress,                  db_parts_COMBOBOX),
        DB_DEFINE_SUBCLASS(Combobox, InactiveAddressComposited,        db_parts_COMBOBOX),
        DB_DEFINE_SUBCLASS(Combobox, MaxAddress,                       db_parts_COMBOBOX),
        DB_DEFINE_SUBCLASS(Combobox, MaxAddressComposited,             db_parts_COMBOBOX),
        DB_DEFINE_SUBCLASS(Combobox, MaxInactiveAddress,               db_parts_COMBOBOX),
        DB_DEFINE_SUBCLASS(Combobox, MaxInactiveAddressComposited,     db_parts_COMBOBOX),
        DB_DEFINE_SUBCLASS(Combobox, TaskbarComposited,                db_parts_COMBOBOX),
    DB_DEFINE_CLASS(Communications,                                    db_parts_COMMUNICATIONS),
    DB_DEFINE_CLASS(ControlPanel,                                      db_parts_CONTROLPANEL),
    DB_DEFINE_CLASS(DatePicker,                                        db_parts_DATEPICKER),
    DB_DEFINE_CLASS(DragDrop,                                          db_parts_DRAGDROP),
    DB_DEFINE_CLASS(Edit,                                              db_parts_EDIT),
        DB_DEFINE_SUBCLASS(Edit, Address,                              db_parts_EDIT),
        DB_DEFINE_SUBCLASS(Edit, AddressComposited,                    db_parts_EDIT),
        DB_DEFINE_SUBCLASS(Edit, CommonItemDialogPreviewPaneControl,   db_parts_EDIT),
        DB_DEFINE_SUBCLASS(Edit, DocumentsPreviewPaneControl,          db_parts_EDIT),
        DB_DEFINE_SUBCLASS(Edit, EditComposited,                       db_parts_EDIT),
        DB_DEFINE_SUBCLASS(Edit, Explorer,                             db_parts_EDIT),
        DB_DEFINE_SUBCLASS(Edit, GenericPreviewPaneControl,            db_parts_EDIT),
        DB_DEFINE_SUBCLASS(Edit, Help,                                 db_parts_EDIT),
        DB_DEFINE_SUBCLASS(Edit, InactiveAddress,                      db_parts_EDIT),
        DB_DEFINE_SUBCLASS(Edit, InactiveAddressComposited,            db_parts_EDIT),
        DB_DEFINE_SUBCLASS(Edit, InactiveSearchBoxEdit,                db_parts_EDIT),
        DB_DEFINE_SUBCLASS(Edit, InactiveSearchBoxEditComposited,      db_parts_EDIT),
        DB_DEFINE_SUBCLASS(Edit, MaxAddress,                           db_parts_EDIT),
        DB_DEFINE_SUBCLASS(Edit, MaxAddressComposited,                 db_parts_EDIT),
        DB_DEFINE_SUBCLASS(Edit, MaxInactiveAddress,                   db_parts_EDIT),
        DB_DEFINE_SUBCLASS(Edit, MaxInactiveAddressComposited,         db_parts_EDIT),
        DB_DEFINE_SUBCLASS(Edit, MaxInactiveSearchBoxEdit,             db_parts_EDIT),
        DB_DEFINE_SUBCLASS(Edit, MaxInactiveSearchBoxEditComposited,   db_parts_EDIT),
        DB_DEFINE_SUBCLASS(Edit, MaxSearchBoxEdit,                     db_parts_EDIT),
        DB_DEFINE_SUBCLASS(Edit, MaxSearchBoxEditComposited,           db_parts_EDIT),
        DB_DEFINE_SUBCLASS(Edit, MusicPreviewPaneControl,              db_parts_EDIT),
        DB_DEFINE_SUBCLASS(Edit, PhotoPreviewPaneControl,              db_parts_EDIT),
        DB_DEFINE_SUBCLASS(Edit, SearchBoxEdit,                        db_parts_EDIT),
        DB_DEFINE_SUBCLASS(Edit, SearchBoxEditComposited,              db_parts_EDIT),
        DB_DEFINE_SUBCLASS(Edit, TaskBarComposited,                    db_parts_EDIT),
    DB_DEFINE_CLASS(EmptyMarkup,                                       db_parts_EMPTYMARKUP),
        DB_DEFINE_SUBCLASS(EmptyMarkup, StartMenuComposited,           db_parts_EMPTYMARKUP),
    DB_DEFINE_CLASS(ExplorerBar,                                       db_parts_EXPLORERBAR),
    DB_DEFINE_CLASS(Flyout,                                            db_parts_FLYOUT),
    DB_DEFINE_CLASS(Globals,                                           db_parts_GLOBALS),
    DB_DEFINE_CLASS(Header,                                            db_parts_HEADER),
        DB_DEFINE_SUBCLASS(Header, ItemsView,                          db_parts_HEADER),
    DB_DEFINE_CLASS(Link,                                              db_parts_LINK),
        DB_DEFINE_SUBCLASS(Link, StartMenuComposited,                  db_parts_LINK),
    DB_DEFINE_CLASS(ListBox,                                           db_parts_LISTBOX),
    DB_DEFINE_CLASS(ListView,                                          db_parts_LISTVIEW),
        DB_DEFINE_SUBCLASS(ListView, Explorer,                         db_parts_LISTVIEW),
        DB_DEFINE_SUBCLASS(ListView, ItemsView,                        db_parts_LISTVIEW),
        DB_DEFINE_SUBCLASS(ListView, StartMenu,                        db_parts_LISTVIEW),
        DB_DEFINE_SUBCLASS(ListView, StartMenuComposited,              db_parts_LISTVIEW),
        DB_DEFINE_SUBCLASS(ListView, StartMenuCompositedMFU,           db_parts_LISTVIEW),
        DB_DEFINE_SUBCLASS(ListView, StartMenuPlaceListComposited,     db_parts_LISTVIEW),
        DB_DEFINE_SUBCLASS(ListView, TopMatch,                         db_parts_LISTVIEW),
        DB_DEFINE_SUBCLASS(ListView, TopMatchComposited,               db_parts_LISTVIEW),
    DB_DEFINE_CLASS(Menu,                                              db_parts_MENU),
        DB_DEFINE_SUBCLASS(Menu, Communications,                       db_parts_MENU),
        DB_DEFINE_SUBCLASS(Menu, Media,                                db_parts_MENU),
    DB_DEFINE_CLASS(MenuBand,                                          db_parts_MENUBAND),
        DB_DEFINE_SUBCLASS(MenuBand, ExplorerMenu,                     db_parts_MENUBAND),
        DB_DEFINE_SUBCLASS(MenuBand, StartMenu,                        db_parts_MENUBAND),
    DB_DEFINE_CLASS(MonthCal,                                          db_parts_MONTHCAL),
    DB_DEFINE_CLASS(Navigation,                                        db_parts_NAVIGATION),
    DB_DEFINE_CLASS(Page,                                              db_parts_PAGE),
    DB_DEFINE_CLASS(Progress,                                          db_parts_PROGRESS),
        DB_DEFINE_SUBCLASS(Progress, Indeterminate,                    db_parts_PROGRESS),
    DB_DEFINE_CLASS(Rebar,                                             db_parts_REBAR),
        DB_DEFINE_SUBCLASS(Rebar, AlternateRebar,                      db_parts_REBAR),
        DB_DEFINE_SUBCLASS(Rebar, BrowserTabBar,                       db_parts_REBAR),
        DB_DEFINE_SUBCLASS(Rebar, Communications,                      db_parts_REBAR),
        DB_DEFINE_SUBCLASS(Rebar, Default,                             db_parts_REBAR),
        DB_DEFINE_SUBCLASS(Rebar, ExplorerBar,                         db_parts_REBAR),
        DB_DEFINE_SUBCLASS(Rebar, Help,                                db_parts_REBAR),
        DB_DEFINE_SUBCLASS(Rebar, InactiveNavbar,                      db_parts_REBAR),
        DB_DEFINE_SUBCLASS(Rebar, InactiveNavbarComposited,            db_parts_REBAR),
        DB_DEFINE_SUBCLASS(Rebar, ITBarBase,                           db_parts_REBAR),
        DB_DEFINE_SUBCLASS(Rebar, MaxInactiveNavbar,                   db_parts_REBAR),
        DB_DEFINE_SUBCLASS(Rebar, MaxInactiveNavbarComposited,         db_parts_REBAR),
        DB_DEFINE_SUBCLASS(Rebar, MaxNavbar,                           db_parts_REBAR),
        DB_DEFINE_SUBCLASS(Rebar, MaxNavbarComposited,                 db_parts_REBAR),
        DB_DEFINE_SUBCLASS(Rebar, Media,                               db_parts_REBAR),
        DB_DEFINE_SUBCLASS(Rebar, Navbar,                              db_parts_REBAR),
        DB_DEFINE_SUBCLASS(Rebar, NavbarBase,                          db_parts_REBAR),
        DB_DEFINE_SUBCLASS(Rebar, NavbarComposited,                    db_parts_REBAR),
        DB_DEFINE_SUBCLASS(Rebar, NavbarNonTopmost,                    db_parts_REBAR),
        DB_DEFINE_SUBCLASS(Rebar, TaskBar,                             db_parts_REBAR),
        DB_DEFINE_SUBCLASS(Rebar, TaskBarComposited,                   db_parts_REBAR),
    DB_DEFINE_CLASS(Scrollbar,                                         db_parts_SCROLLBAR),
        DB_DEFINE_SUBCLASS(ScrollBar, TaskBand2,                       db_parts_SCROLLBAR),
        DB_DEFINE_SUBCLASS(ScrollBar, TaskBand2Composited,             db_parts_SCROLLBAR),
    DB_DEFINE_CLASS(SearchEditBox,                                     db_parts_SEARCHEDITBOX),
    DB_DEFINE_CLASS(SearchBox,                                         db_parts_SEARCHBOX),
        DB_DEFINE_SUBCLASS(SearchBox, InactiveSearchBox,               db_parts_SEARCHBOX),
        DB_DEFINE_SUBCLASS(SearchBox, InactiveSearchBoxComposited,     db_parts_SEARCHBOX),
        DB_DEFINE_SUBCLASS(SearchBox, MaxInactiveSearchBox,            db_parts_SEARCHBOX),
        DB_DEFINE_SUBCLASS(SearchBox, MaxInactiveSearchBoxComposited,  db_parts_SEARCHBOX),
        DB_DEFINE_SUBCLASS(SearchBox, MaxSearchBox,                    db_parts_SEARCHBOX),
        DB_DEFINE_SUBCLASS(SearchBox, MaxSearchBoxComposited,          db_parts_SEARCHBOX),
        DB_DEFINE_SUBCLASS(SearchBox, SearchBoxComposited,             db_parts_SEARCHBOX),
    DB_DEFINE_CLASS(Spin,                                              db_parts_SPIN),
    DB_DEFINE_CLASS(StartPanel,                                        db_parts_STARTPANEL),
    DB_DEFINE_CLASS(StartPanelPriv,                                    db_parts_STARTPANEL),
        DB_DEFINE_SUBCLASS(StartPanelPriv, StartPanelComposited,       db_parts_STARTPANEL),
        DB_DEFINE_SUBCLASS(StartPanelPriv, StartPanelCompositedBottom, db_parts_STARTPANEL),
    DB_DEFINE_CLASS(Static,                                            db_parts_STATIC),
    DB_DEFINE_CLASS(Status,                                            db_parts_STATUS),
    DB_DEFINE_CLASS(Tab,                                               db_parts_TAB),
        DB_DEFINE_SUBCLASS(Tab, BrowserTab,                            db_parts_TAB),
    DB_DEFINE_CLASS(TaskBand,                                          db_parts_TASKBAND),
    DB_DEFINE_CLASS(TaskBar,                                           db_parts_TASKBAR),
        DB_DEFINE_SUBCLASS(TaskBar, TaskBarComposited,                 db_parts_TASKBAR),
        DB_DEFINE_SUBCLASS(TaskBar, TaskBar2,                          db_parts_TASKBAR),
        DB_DEFINE_SUBCLASS(TaskBar, TaskBar2Composited,                db_parts_TASKBAR),
    DB_DEFINE_CLASS(TaskDialog,                                        db_parts_TASKDIALOG),
    DB_DEFINE_CLASS(TextStyle,                                         db_parts_TEXTSTYLE),
    DB_DEFINE_CLASS(Toolbar,                                           db_parts_TOOLBAR),
        DB_DEFINE_SUBCLASS(Toolbar, Alternate,                         db_parts_TOOLBAR),
        DB_DEFINE_SUBCLASS(Toolbar, BB,                                db_parts_TOOLBAR),
        DB_DEFINE_SUBCLASS(Toolbar, BBComposited,                      db_parts_TOOLBAR),
        DB_DEFINE_SUBCLASS(Toolbar, Communications,                    db_parts_TOOLBAR),
        DB_DEFINE_SUBCLASS(Toolbar, ExplorerBar,                       db_parts_TOOLBAR),
        DB_DEFINE_SUBCLASS(Toolbar, ExplorerMenu,                      db_parts_TOOLBAR),
        DB_DEFINE_SUBCLASS(Toolbar, Go,                                db_parts_TOOLBAR),
        DB_DEFINE_SUBCLASS(Toolbar, GoComposited,                      db_parts_TOOLBAR),
        DB_DEFINE_SUBCLASS(Toolbar, InactiveBB,                        db_parts_TOOLBAR),
        DB_DEFINE_SUBCLASS(Toolbar, InactiveBBComposited,              db_parts_TOOLBAR),
        DB_DEFINE_SUBCLASS(Toolbar, InactiveGo,                        db_parts_TOOLBAR),
        DB_DEFINE_SUBCLASS(Toolbar, InactiveGoComposited,              db_parts_TOOLBAR),
        DB_DEFINE_SUBCLASS(Toolbar, InfoPaneToolbar,                   db_parts_TOOLBAR),
        DB_DEFINE_SUBCLASS(Toolbar, LVPopup,                           db_parts_TOOLBAR),
        DB_DEFINE_SUBCLASS(Toolbar, LVPopupBottom,                     db_parts_TOOLBAR),
        DB_DEFINE_SUBCLASS(Toolbar, MaxBB,                             db_parts_TOOLBAR),
        DB_DEFINE_SUBCLASS(Toolbar, MaxBBComposited,                   db_parts_TOOLBAR),
        DB_DEFINE_SUBCLASS(Toolbar, MaxGo,                             db_parts_TOOLBAR),
        DB_DEFINE_SUBCLASS(Toolbar, MaxGoComposited,                   db_parts_TOOLBAR),
        DB_DEFINE_SUBCLASS(Toolbar, MaxInactiveGo,                     db_parts_TOOLBAR),
        DB_DEFINE_SUBCLASS(Toolbar, MaxInactiveGoComposited,           db_parts_TOOLBAR),
        DB_DEFINE_SUBCLASS(Toolbar, Media,                             db_parts_TOOLBAR),
        DB_DEFINE_SUBCLASS(Toolbar, Placesbar,                         db_parts_TOOLBAR),
        DB_DEFINE_SUBCLASS(Toolbar, SearchButton,                      db_parts_TOOLBAR),
        DB_DEFINE_SUBCLASS(Toolbar, SearchButtonComposited,            db_parts_TOOLBAR),
        DB_DEFINE_SUBCLASS(Toolbar, StartMenu,                         db_parts_TOOLBAR),
        DB_DEFINE_SUBCLASS(Toolbar, TaskBar,                           db_parts_TOOLBAR),
        DB_DEFINE_SUBCLASS(Toolbar, TaskBarComposited,                 db_parts_TOOLBAR),
        DB_DEFINE_SUBCLASS(Toolbar, TaskBarVert,                       db_parts_TOOLBAR),
        DB_DEFINE_SUBCLASS(Toolbar, TaskBarVertComposited,             db_parts_TOOLBAR),
        DB_DEFINE_SUBCLASS(Toolbar, Travel,                            db_parts_TOOLBAR),
        DB_DEFINE_SUBCLASS(Toolbar, TravelComposited,                  db_parts_TOOLBAR),
        DB_DEFINE_SUBCLASS(Toolbar, TrayNotify,                        db_parts_TOOLBAR),
        DB_DEFINE_SUBCLASS(Toolbar, TrayNotifyComposited,              db_parts_TOOLBAR),
    DB_DEFINE_CLASS(Tooltip,                                           db_parts_TOOLTIP),
    DB_DEFINE_CLASS(TrackBar,                                          db_parts_TRACKBAR),
    DB_DEFINE_CLASS(TrayNotify,                                        db_parts_TRAYNOTIFY),
        DB_DEFINE_SUBCLASS(TrayNotify, TrayNotifyHoriz,                db_parts_TRAYNOTIFY),
        DB_DEFINE_SUBCLASS(TrayNotify, TrayNotifyHorizComposited,      db_parts_TRAYNOTIFY),
        DB_DEFINE_SUBCLASS(TrayNotify, TrayNotifyVert,                 db_parts_TRAYNOTIFY),
        DB_DEFINE_SUBCLASS(TrayNotify, TrayNotifyVertComposited,       db_parts_TRAYNOTIFY),
    DB_DEFINE_CLASS(TreeView,                                          db_parts_TREEVIEW),
        DB_DEFINE_SUBCLASS(TreeView, Explorer,                         db_parts_TREEVIEW),
        DB_DEFINE_SUBCLASS(TreeView, StartMenuKeyBoard,                db_parts_TREEVIEW),
        DB_DEFINE_SUBCLASS(TreeView, StartMenuKeyBoardComposited,      db_parts_TREEVIEW),
        DB_DEFINE_SUBCLASS(TreeView, StartMenuHover,                   db_parts_TREEVIEW),
        DB_DEFINE_SUBCLASS(TreeView, StartMenuHoverComposited,         db_parts_TREEVIEW),
    DB_DEFINE_CLASS(Window,                                            db_parts_WINDOW),
        DB_DEFINE_SUBCLASS(Window, CompositedWindow,                   db_parts_WINDOW)
};

const db_class_t* db_classes = db_classes_helper;
int db_n_classes = TE_ARRAY_SIZE(db_classes_helper);


void
db_class_display_name(const db_class_t* cls, TCHAR* buffer, UINT bufsize)
{
    if(cls->subclass != NULL)
        _sntprintf(buffer, bufsize, _T("%s [%s]"), cls->name, cls->subclass);
    else
        _sntprintf(buffer, bufsize, _T("%s"), cls->name);
    buffer[bufsize - 1] = _T('\0');
}


/******************
 *** Properties ***
 ******************/

static void
db_to_string_TMT_ENUM(HTHEME theme, int part, int state, int prop, TCHAR* buffer, DWORD bufsize)
{
    const TCHAR* str = NULL;
    int val;

    if(GetThemeInt(theme, part, state, prop, &val) != S_OK) {
        buffer[0] = _T('\0');
        return;
    }

    switch(prop) {
        case 4001:
            switch(val) {
                case 0:  str = _T("BT_IMAGEFILE"); break;
                case 1:  str = _T("BT_BORDERFILL"); break;
                case 2:  str = _T("BT_NONE"); break;
            }
            break;

        case 4002:
            switch(val) {
                case 0:  str = _T("BT_RECT"); break;
                case 1:  str = _T("BT_ROUNDRECT"); break;
                case 2:  str = _T("BT_ELLIPSE"); break;
            }
            break;

        case 4003:
            switch(val) {
                case 0:  str = _T("FT_SOLID"); break;
                case 1:  str = _T("FT_VERTGRADIENT"); break;
                case 2:  str = _T("FT_HORZGRADIENT"); break;
                case 3:  str = _T("FT_RADIALGRADIENT"); break;
                case 4:  str = _T("FT_TILEIMAGE"); break;
            }
            break;

        case 4004:
            switch(val) {
                case 0:  str = _T("ST_TRUESIZE"); break;
                case 1:  str = _T("ST_STRETCH"); break;
                case 2:  str = _T("ST_TILE"); break;
            }
            break;

        case 4005:
            switch(val) {
                case 0:  str = _T("HA_LEFT"); break;
                case 1:  str = _T("HA_CENTER"); break;
                case 2:  str = _T("HA_RIGHT"); break;
            }
            break;

        case 4006:
            switch(val) {
                case 0:  str = _T("CA_LEFT"); break;
                case 1:  str = _T("CA_CENTER"); break;
                case 2:  str = _T("CA_RIGHT"); break;
            }
            break;

        case 4007:
            switch(val) {
                case 0:  str = _T("VA_LEFT"); break;
                case 1:  str = _T("VA_CENTER"); break;
                case 2:  str = _T("VA_RIGHT"); break;
            }
            break;

        case 4008:
            switch(val) {
                case  0:  str = _T("OT_TOPLEFT"); break;
                case  1:  str = _T("OT_TOPRIGHT"); break;
                case  2:  str = _T("OT_TOPMIDDLE"); break;
                case  3:  str = _T("OT_BOTTOMLEFT"); break;
                case  4:  str = _T("OT_BOTTOMRIGHT"); break;
                case  5:  str = _T("OT_BOTTOMMIDDLE"); break;
                case  6:  str = _T("OT_MIDDLELEFT"); break;
                case  7:  str = _T("OT_MIDDLERIGHT"); break;
                case  8:  str = _T("OT_LEFTOFCAPTION"); break;
                case  9:  str = _T("OT_RIGHTOFCAPTION"); break;
                case 10:  str = _T("OT_LEFTOFLASTBUTTON"); break;
                case 11:  str = _T("OT_RIGHTOFLASTBUTTON"); break;
                case 12:  str = _T("OT_ABOVELASTBUTTON"); break;
                case 13:  str = _T("OT_BELOWLASTBUTTON"); break;
            }
            break;

        case 4009:
            switch(val) {
                case 0:  str = _T("ICE_NONE"); break;
                case 1:  str = _T("ICE_GLOW"); break;
                case 2:  str = _T("ICE_SHADOW"); break;
                case 3:  str = _T("ICE_PULSE"); break;
                case 4:  str = _T("ICE_ALPHA"); break;
            }
            break;

        case 4010:
            switch(val) {
                case 0:  str = _T("TST_NONE"); break;
                case 1:  str = _T("TST_SINGLE"); break;
                case 2:  str = _T("TST_CONTINUOUS"); break;
            }
            break;

        case 4011:
            switch(val) {
                case 0:  str = _T("IL_VERTICAL"); break;
                case 1:  str = _T("IL_HORIZONTAL"); break;
            }
            break;

        case 4012:
            switch(val) {
                case 0:  str = _T("GT_NONE"); break;
                case 1:  str = _T("GT_IMAGEGLYPH"); break;
                case 2:  str = _T("GT_FONTGLYPH"); break;
            }
            break;

        case 4013:
            switch(val) {
                case 0:  str = _T("IST_NONE"); break;
                case 1:  str = _T("IST_SIZE"); break;
                case 2:  str = _T("IST_DPI"); break;
            }
            break;

        case 4014:
            switch(val) {
                case 0:  str = _T("GFST_NONE"); break;
                case 1:  str = _T("GFST_SIZE"); break;
                case 2:  str = _T("GFST_DPI"); break;
            }
            break;

        case 4015:
            switch(val) {
                case 0:  str = _T("TSST_NONE"); break;
                case 1:  str = _T("TSST_SIZE"); break;
                case 2:  str = _T("TSST_DPI"); break;
            }
            break;
    }

    if(str)
        _sntprintf(buffer, bufsize, _T("%d (%s)"), val, str);
    else
        _sntprintf(buffer, bufsize, _T("%d"), val);
}

static void
db_to_string_TMT_STRING(HTHEME theme, int part, int state, int prop, TCHAR* buffer, DWORD bufsize)
{
    if(GetThemeString(theme, part, state, prop, buffer, bufsize) != S_OK)
        buffer[0] = _T('\0');
}

static void
db_to_string_TMT_INT(HTHEME theme, int part, int state, int prop, TCHAR* buffer, DWORD bufsize)
{
    int val;

    if(GetThemeInt(theme, part, state, prop, &val) != S_OK) {
        if(GetThemeMetric(theme, GetDC(NULL), part, state, prop, &val) != S_OK) {
            buffer[0] = _T('\0');
            return;
        }
    }

    _sntprintf(buffer, bufsize, _T("%d (0x%x)"), val, (unsigned)val);
}

static void
db_to_string_TMT_BOOL(HTHEME theme, int part, int state, int prop, TCHAR* buffer, DWORD bufsize)
{
    BOOL val;

    if(GetThemeBool(theme, part, state, prop, &val) != S_OK) {
        buffer[0] = _T('\0');
        return;
    }

    _sntprintf(buffer, bufsize, _T("%s"), (val ? _T("True") : _T("False")));
}

static void
db_to_string_TMT_COLOR(HTHEME theme, int part, int state, int prop, TCHAR* buffer, DWORD bufsize)
{
    COLORREF rgb;

    if(GetThemeColor(theme, part, state, prop, &rgb) != S_OK) {
        buffer[0] = _T('\0');
        return;
    }

    _sntprintf(buffer, bufsize, _T("%d,%d,%d (#%06x)"),
               (int)GetRValue(rgb), (int)GetGValue(rgb), (int)GetBValue(rgb),
               (unsigned)(rgb & 0xffffff));
}

static void
db_to_string_TMT_MARGINS(HTHEME theme, int part, int state, int prop, TCHAR* buffer, DWORD bufsize)
{
    MARGINS margins;

    if(GetThemeMargins(theme, GetDC(NULL), part, state, prop, NULL, &margins) != S_OK) {
        buffer[0] = _T('\0');
        return;
    }

    _sntprintf(buffer, bufsize, _T("%d,%d (horz), %d,%d (vert)"),
               margins.cxLeftWidth, margins.cxRightWidth,
               margins.cyTopHeight, margins.cyBottomHeight);
}

static void
db_to_string_TMT_FILENAME(HTHEME theme, int part, int state, int prop, TCHAR* buffer, DWORD bufsize)
{
    if(GetThemeFilename(theme, part, state, prop, buffer, bufsize) != S_OK)
        buffer[0] = _T('\0');
}

static void
db_to_string_TMT_SIZE(HTHEME theme, int part, int state, int prop, TCHAR* buffer, DWORD bufsize)
{
    SIZE size;

    if(GetThemePartSize(theme, GetDC(NULL), part, state, NULL, prop, &size) != S_OK) {
        buffer[0] = _T('\0');
        return;
    }

    _sntprintf(buffer, bufsize, _T("%dx%d"), (int)size.cx, (int)size.cy);
}

static void
db_to_string_TMT_POSITION(HTHEME theme, int part, int state, int prop, TCHAR* buffer, DWORD bufsize)
{
    POINT pos;

    if(GetThemePosition(theme, part, state, prop, &pos) != S_OK) {
        buffer[0] = _T('\0');
        return;
    }

    _sntprintf(buffer, bufsize, _T("%d,%d"), pos.x, pos.y);
}

static void
db_to_string_TMT_RECT(HTHEME theme, int part, int state, int prop, TCHAR* buffer, DWORD bufsize)
{
    RECT rect;

    if(GetThemeRect(theme, part, state, prop, &rect) != S_OK) {
        buffer[0] = _T('\0');
        return;
    }

    _sntprintf(buffer, bufsize, _T("%d,%d - %d,%d (%dx%d)"),
               rect.left, rect.top, rect.right, rect.bottom,
               rect.right - rect.left, rect.bottom - rect.top);
}

static void
db_to_string_TMT_FONT(HTHEME theme, int part, int state, int prop, TCHAR* buffer, DWORD bufsize)
{
    const TCHAR* weight = _T("");
    LOGFONT lf;

    if(GetThemeFont(theme, GetDC(NULL), part, state, prop, &lf) != S_OK) {
        buffer[0] = _T('\0');
        return;
    }

    switch(((lf.lfWeight + 50) / 100) * 100) {
        case 0:              weight = _T(""); break;
        case FW_THIN:        weight = _T(" thin"); break;
        case FW_EXTRALIGHT:  weight = _T(" extralight"); break;
        case FW_LIGHT:       weight = _T(" light"); break;
        case FW_REGULAR:     weight = _T(" regular"); break;
        case FW_MEDIUM:      weight = _T(" medium"); break;
        case FW_SEMIBOLD:    weight = _T(" semibold"); break;
        case FW_BOLD:        weight = _T(" bold"); break;
        case FW_EXTRABOLD:   weight = _T(" extrabold"); break;
        case FW_HEAVY:       weight = _T(" heavy"); break;
        default:             weight = _T(" ??"); break;
    }

    _sntprintf(buffer, bufsize, _T("%s,%d%s%s%s"),
               lf.lfFaceName, lf.lfHeight, weight,
               lf.lfUnderline ? _T(" underlined") : _T(""),
               lf.lfItalic ? _T(" italic") : _T(""));
}

static void
db_to_string_TMT_INTLIST(HTHEME theme, int part, int state, int prop, TCHAR* buffer, DWORD bufsize)
{
    BYTE mem[410 * sizeof(int)];
    INTLIST* list = (INTLIST*) mem;  /* workaround of mingw-w64 bug #3524667 */
    int i;
    size_t n;

    if(GetThemeIntList(theme, part, state, prop, list) != S_OK) {
        buffer[0] = _T('\0');
        return;
    }

    for(i = 0; i < list->iValueCount; i++) {
        n = _sntprintf(buffer, bufsize, (i > 0 ? _T(",%d") : _T("%d")), list->iValues[i]);
        if(n <= 0)
            break;
        buffer += n;
        bufsize -= n;
    }
}

static void
db_to_string_TMT_DISKSTREAM(HTHEME theme, int part, int state, int prop, TCHAR* buffer, DWORD bufsize)
{
    TCHAR theme_path[MAX_PATH];
    HANDLE theme_instance;
    void* stream;
    DWORD stream_len;

    buffer[0] = _T('\0');
    if(FAILED(GetCurrentThemeName(theme_path, TE_ARRAY_SIZE(theme_path), NULL, 0, NULL, 0)))
        return;

    theme_instance = LoadLibraryEx(theme_path, 0, LOAD_LIBRARY_AS_DATAFILE);
    if(!theme_instance)
        return;

    if(SUCCEEDED(GetThemeStream(theme, part, state, prop, &stream, &stream_len, theme_instance)))
        _sntprintf(buffer, bufsize, _T("<diskstream %u bytes>"), (unsigned)stream_len);

    FreeLibrary(theme_instance);
}

static void
db_to_string_TMT_STREAM(HTHEME theme, int part, int state, int prop, TCHAR* buffer, DWORD bufsize)
{
    void* stream;
    DWORD stream_len;

    buffer[0] = _T('\0');
    if(SUCCEEDED(GetThemeStream(theme, part, state, prop, &stream, &stream_len, NULL)))
        _sntprintf(buffer, bufsize, _T("<stream %u bytes>"), (unsigned)stream_len);
}


static const db_type_t db_type_TMT_ENUM =       { 200,  _T("TMT_ENUM"),        _T("Enum"),        db_to_string_TMT_ENUM };
static const db_type_t db_type_TMT_STRING =     { 201,  _T("TMT_STRING"),      _T("String"),      db_to_string_TMT_STRING };
static const db_type_t db_type_TMT_INT =        { 202,  _T("TMT_INT"),         _T("Int"),         db_to_string_TMT_INT };
static const db_type_t db_type_TMT_BOOL =       { 203,  _T("TMT_BOOL"),        _T("Bool"),        db_to_string_TMT_BOOL };
static const db_type_t db_type_TMT_COLOR =      { 204,  _T("TMT_COLOR"),       _T("Color"),       db_to_string_TMT_COLOR };
static const db_type_t db_type_TMT_MARGINS =    { 205,  _T("TMT_MARGINS"),     _T("Margins"),     db_to_string_TMT_MARGINS };
static const db_type_t db_type_TMT_FILENAME =   { 206,  _T("TMT_FILENAME"),    _T("Filename"),    db_to_string_TMT_FILENAME };
static const db_type_t db_type_TMT_SIZE =       { 207,  _T("TMT_SIZE"),        _T("Size"),        db_to_string_TMT_SIZE };
static const db_type_t db_type_TMT_POSITION =   { 208,  _T("TMT_POSITION"),    _T("Positon"),     db_to_string_TMT_POSITION };
static const db_type_t db_type_TMT_RECT =       { 209,  _T("TMT_RECT"),        _T("Rect"),        db_to_string_TMT_RECT };
static const db_type_t db_type_TMT_FONT =       { 210,  _T("TMT_FONT"),        _T("Font"),        db_to_string_TMT_FONT };
static const db_type_t db_type_TMT_INTLIST =    { 211,  _T("TMT_INTLIST"),     _T("IntList"),     db_to_string_TMT_INTLIST };
static const db_type_t db_type_TMT_DISKSTREAM = { 213,  _T("TMT_DISKSTREAM"),  _T("DiskStream"),  db_to_string_TMT_DISKSTREAM };
static const db_type_t db_type_TMT_STREAM =     { 214,  _T("TMT_STREAM"),      _T("Stream"),      db_to_string_TMT_STREAM };

#define DB_DEFINE_ENUM(id, name, display_name)       { &db_type_TMT_ENUM,       id, _T(#name), _T(#display_name) }
#define DB_DEFINE_STRING(id, name, display_name)     { &db_type_TMT_STRING,     id, _T(#name), _T(#display_name) }
#define DB_DEFINE_INT(id, name, display_name)        { &db_type_TMT_INT,        id, _T(#name), _T(#display_name) }
#define DB_DEFINE_BOOL(id, name, display_name)       { &db_type_TMT_BOOL,       id, _T(#name), _T(#display_name) }
#define DB_DEFINE_COLOR(id, name, display_name)      { &db_type_TMT_COLOR,      id, _T(#name), _T(#display_name) }
#define DB_DEFINE_MARGINS(id, name, display_name)    { &db_type_TMT_MARGINS,    id, _T(#name), _T(#display_name) }
#define DB_DEFINE_FILENAME(id, name, display_name)   { &db_type_TMT_FILENAME,   id, _T(#name), _T(#display_name) }
#define DB_DEFINE_SIZE(id, name, display_name)       { &db_type_TMT_SIZE,       id, _T(#name), _T(#display_name) }
#define DB_DEFINE_POSITION(id, name, display_name)   { &db_type_TMT_POSITION,   id, _T(#name), _T(#display_name) }
#define DB_DEFINE_RECT(id, name, display_name)       { &db_type_TMT_RECT,       id, _T(#name), _T(#display_name) }
#define DB_DEFINE_FONT(id, name, display_name)       { &db_type_TMT_FONT,       id, _T(#name), _T(#display_name) }
#define DB_DEFINE_INTLIST(id, name, display_name)    { &db_type_TMT_INTLIST,    id, _T(#name), _T(#display_name) }
#define DB_DEFINE_DISKSTREAM(id, name, display_name) { &db_type_TMT_DISKSTREAM, id, _T(#name), _T(#display_name) }
#define DB_DEFINE_STREAM(id, name, display_name)     { &db_type_TMT_STREAM,     id, _T(#name), _T(#display_name) }

static const db_prop_t db_props_helper[] = {
    DB_DEFINE_ENUM(4001,  TMT_BGTYPE,               BgType),
    DB_DEFINE_ENUM(4002,  TMT_BORDERTYPE,           BorderType),
    DB_DEFINE_ENUM(4003,  TMT_FILLTYPE,             FillType),
    DB_DEFINE_ENUM(4004,  TMT_SIZINGTYPE,           SizingType),
    DB_DEFINE_ENUM(4005,  TMT_HALIGN,               HAlign),
    DB_DEFINE_ENUM(4006,  TMT_CONTENTALIGNMENT,     ContentAlignement),
    DB_DEFINE_ENUM(4007,  TMT_VALIGN,               VAlign),
    DB_DEFINE_ENUM(4008,  TMT_OFFSETTYPE,           OffsetType),
    DB_DEFINE_ENUM(4009,  TMT_ICONEFFECT,           IconEffect),
    DB_DEFINE_ENUM(4010,  TMT_TEXTSHADOWTYPE,       TextShadowType),
    DB_DEFINE_ENUM(4011,  TMT_IMAGELAYOUT,          ImageLayout),
    DB_DEFINE_ENUM(4012,  TMT_GLYPHTYPE,            GlyphType),
    DB_DEFINE_ENUM(4013,  TMT_IMAGESELECTTYPE,      ImageSelectType),
    DB_DEFINE_ENUM(4014,  TMT_GLYPHFONTSIZINGTYPE,  GlyphFontSizingType),
    DB_DEFINE_ENUM(4015,  TMT_TRUESIZESCALINGTYPE,  TrueSizeScalingType),

    DB_DEFINE_STRING( 201,  TMT_STRING,           String),
    DB_DEFINE_STRING( 401,  TMT_COLORSCHEMES,     ColorSchemes),
    DB_DEFINE_STRING( 402,  TMT_SIZES,            Sizes),
    DB_DEFINE_STRING( 600,  TMT_NAME,             Name),
    DB_DEFINE_STRING( 601,  TMT_DISPLAYNAME,      DisplayName),
    DB_DEFINE_STRING( 602,  TMT_TOOLTIP,          Tooltip),
    DB_DEFINE_STRING( 603,  TMT_COMPANY,          Company),
    DB_DEFINE_STRING( 605,  TMT_COPYRIGHT,        Copyright),
    DB_DEFINE_STRING( 604,  TMT_AUTHOR,           Author),
    DB_DEFINE_STRING( 606,  TMT_URL,              Url),
    DB_DEFINE_STRING( 607,  TMT_VERSION,          Version),
    DB_DEFINE_STRING( 608,  TMT_DESCRIPTION,      Description),
    DB_DEFINE_STRING(1401,  TMT_CSSNAME,          CssName),
    DB_DEFINE_STRING(1402,  TMT_XMLNAME,          XmlName),
    DB_DEFINE_STRING(1403,  TMT_LASTUPDATED,      LastUpdated),
    DB_DEFINE_STRING(1404,  TMT_ALIAS,            Alias),
    DB_DEFINE_STRING(3201,  TMT_TEXT,             Text),
    DB_DEFINE_STRING(3202,  TMT_CLASSICVALUE,     ClassicValue),
    DB_DEFINE_STRING(8001,  TMT_ATLASINPUTIMAGE,  AtlasInputImage),

    DB_DEFINE_INT( 403,  TMT_CHARSET,              Charset),
    DB_DEFINE_INT(1301,  TMT_MINCOLORDEPTH,        MinColorDepth),
    DB_DEFINE_INT(1801,  TMT_FROMHUE1,             FromHuw1),
    DB_DEFINE_INT(1802,  TMT_FROMHUE2,             FromHuw2),
    DB_DEFINE_INT(1803,  TMT_FROMHUE3,             FromHuw3),
    DB_DEFINE_INT(1804,  TMT_FROMHUE4,             FromHuw4),
    DB_DEFINE_INT(1805,  TMT_FROMHUE5,             FromHuw5),
    DB_DEFINE_INT(1806,  TMT_TOHUE1,               ToHue1),
    DB_DEFINE_INT(1807,  TMT_TOHUE2,               ToHue2),
    DB_DEFINE_INT(1808,  TMT_TOHUE3,               ToHue3),
    DB_DEFINE_INT(1809,  TMT_TOHUE4,               ToHue4),
    DB_DEFINE_INT(1810,  TMT_TOHUE5,               ToHue5),
    DB_DEFINE_INT(2006,  TMT_TOCOLOR1,             ToColor1),
    DB_DEFINE_INT(2007,  TMT_TOCOLOR2,             ToColor2),
    DB_DEFINE_INT(2008,  TMT_TOCOLOR3,             ToColor3),
    DB_DEFINE_INT(2009,  TMT_TOCOLOR4,             ToColor4),
    DB_DEFINE_INT(2010,  TMT_TOCOLOR5,             ToColor5),
    DB_DEFINE_INT(2401,  TMT_IMAGECOUNT,           ImageCount),
    DB_DEFINE_INT(2402,  TMT_ALPHALEVEL,           AlphaLevel),
    DB_DEFINE_INT(2403,  TMT_BORDERSIZE,           BorderSize),
    DB_DEFINE_INT(2404,  TMT_ROUNDCORNERWIDTH,     RoundCornerWidth),
    DB_DEFINE_INT(2405,  TMT_ROUNDCORNERHEIGHT,    RoundCornerHeight),
    DB_DEFINE_INT(2406,  TMT_GRADIENTRATIO1,       GradientRatio1),
    DB_DEFINE_INT(2407,  TMT_GRADIENTRATIO2,       GradientRatio2),
    DB_DEFINE_INT(2408,  TMT_GRADIENTRATIO3,       GradientRatio3),
    DB_DEFINE_INT(2409,  TMT_GRADIENTRATIO4,       GradientRatio4),
    DB_DEFINE_INT(2410,  TMT_GRADIENTRATIO5,       GradientRatio5),
    DB_DEFINE_INT(2411,  TMT_PROGRESSCHUNKSIZE,    ProgressChunkSize),
    DB_DEFINE_INT(2412,  TMT_PROGRESSSPACESIZE,    ProgressSpaceSize),
    DB_DEFINE_INT(2413,  TMT_SATURATION,           Saturation),
    DB_DEFINE_INT(2414,  TMT_TEXTBORDERSIZE,       TextBorderSize),
    DB_DEFINE_INT(2415,  TMT_ALPHATHRESHOLD,       AlphaThreshold),
    DB_DEFINE_INT(2416,  TMT_WIDTH,                Width),
    DB_DEFINE_INT(2417,  TMT_HEIGHT,               Height),
    DB_DEFINE_INT(2418,  TMT_GLYPHINDEX,           FlyphIndex),
    DB_DEFINE_INT(2419,  TMT_TRUESIZESTRETCHMARK,  TrueSizeStretchMark),
    DB_DEFINE_INT(2420,  TMT_MINDPI1,              MinDpi1),
    DB_DEFINE_INT(2421,  TMT_MINDPI2,              MinDpi2),
    DB_DEFINE_INT(2422,  TMT_MINDPI3,              MinDpi3),
    DB_DEFINE_INT(2423,  TMT_MINDPI4,              MinDpi4),
    DB_DEFINE_INT(2424,  TMT_MINDPI5,              MinDpi5),
    DB_DEFINE_INT(2425,  TMT_TEXTGLOWSIZE,         TextGlowSize),
    DB_DEFINE_INT(2426,  TMT_FRAMESPERSECOND,      FramesPerSecond),
    DB_DEFINE_INT(2427,  TMT_PIXELSPERFRAME,       PixelsPerFrame),
    DB_DEFINE_INT(2428,  TMT_ANIMATIONDELAY,       AnimationDelay),
    DB_DEFINE_INT(2429,  TMT_GLOWINTENSITY,        GlowIntensity),
    DB_DEFINE_INT(2430,  TMT_OPACITY,              Opacity),
    DB_DEFINE_INT(2431,  TMT_COLORIZATIONCOLOR,    ColorizationColor),
    DB_DEFINE_INT(2432,  TMT_COLORIZATIONOPACITY,  ColorizationOpacity),
    DB_DEFINE_INT(5006,  TMT_ANIMATIONDURATION,    AnimationDuration),

    /* These are documented by MSDN as TMT_SIZE, but they are actually TMT_INT too. */
    DB_DEFINE_INT(1201,  TMT_SIZINGBORDERWIDTH,    SizingBorderWidth),
    DB_DEFINE_INT(1202,  TMT_SCROLLBARWIDTH,       ScrollBarWidth),
    DB_DEFINE_INT(1203,  TMT_SCROLLBARHEIGHT,      ScrollBarHeight),
    DB_DEFINE_INT(1204,  TMT_CAPTIONBARWIDTH,      CaptionBarWidth),
    DB_DEFINE_INT(1205,  TMT_CAPTIONBARHEIGHT,     CaptionBarHeight),
    DB_DEFINE_INT(1206,  TMT_SMCAPTIONBARWIDTH,    SmCaptionBarWidth),
    DB_DEFINE_INT(1207,  TMT_SMCAPTIONBARHEIGHT,   SmCaptionBarHeight),
    DB_DEFINE_INT(1208,  TMT_MENUBARWIDTH,         MenuBarWidth),
    DB_DEFINE_INT(1209,  TMT_MENUBARHEIGHT,        MenuBarHeight),
    DB_DEFINE_INT(1210,  TMT_PADDEDBORDERWIDTH,    PaddedBorderWidth),

    DB_DEFINE_BOOL(1001,  TMT_FLATMENUS,             FlatMenus),
    DB_DEFINE_BOOL(2201,  TMT_TRANSPARENT,           Transparent),
    DB_DEFINE_BOOL(2202,  TMT_AUTOSIZE,              AutoSize),
    DB_DEFINE_BOOL(2203,  TMT_BORDERONLY,            BorderOnly),
    DB_DEFINE_BOOL(2204,  TMT_COMPOSITED,            Composited),
    DB_DEFINE_BOOL(2205,  TMT_BGFILL,                BgFill),
    DB_DEFINE_BOOL(2206,  TMT_GLYPHTRANSPARENT,      GlyphTransparent),
    DB_DEFINE_BOOL(2207,  TMT_GLYPHONLY,             GlyphOnly),
    DB_DEFINE_BOOL(2208,  TMT_ALWAYSSHOWSIZINGBAR,   AlwaysShowSizingBar),
    DB_DEFINE_BOOL(2209,  TMT_MIRRORIMAGE,           MirrorImage),
    DB_DEFINE_BOOL(2210,  TMT_UNIFORMSIZING,         UniformSizing),
    DB_DEFINE_BOOL(2211,  TMT_INTEGRALSIZING,        IntegralSizing),
    DB_DEFINE_BOOL(2212,  TMT_SOURCEGROW,            SourceGrow),
    DB_DEFINE_BOOL(2213,  TMT_SOURCESHRINK,          SourceShrink),
    DB_DEFINE_BOOL(2214,  TMT_DRAWBORDERS,           DrawBorders),
    DB_DEFINE_BOOL(2215,  TMT_NOETCHEDEFFECT,        NoEtchedEffect),
    DB_DEFINE_BOOL(2216,  TMT_TEXTAPPLYOVERLAY,      TextApplyOverlay),
    DB_DEFINE_BOOL(2217,  TMT_TEXTGLOW,              TextGlow),
    DB_DEFINE_BOOL(2218,  TMT_TEXTITALIC,            TextItalic),
    DB_DEFINE_BOOL(2219,  TMT_COMPOSITEDOPAQUE,      CompositedOpaque),
    DB_DEFINE_BOOL(2220,  TMT_LOCALIZEDMIRRORIMAGE,  LocalizedMirrorImage),
    DB_DEFINE_BOOL(5001,  TMT_USERPICTURE,           UserPicture),
    DB_DEFINE_BOOL(7001,  TMT_SCALEDBACKGROUND,      ScaledBackground),

    DB_DEFINE_COLOR( 204,  TMT_COLOR,                    Color),
    DB_DEFINE_COLOR(1601,  TMT_SCROLLBAR,                ScrollBar),
    DB_DEFINE_COLOR(1602,  TMT_BACKGROUND,               Background),
    DB_DEFINE_COLOR(1603,  TMT_ACTIVECAPTION,            ActiveCaption),
    DB_DEFINE_COLOR(1604,  TMT_INACTIVECAPTION,          InactiveCaption),
    DB_DEFINE_COLOR(1605,  TMT_MENU,                     Menu),
    DB_DEFINE_COLOR(1606,  TMT_WINDOW,                   Window),
    DB_DEFINE_COLOR(1607,  TMT_WINDOWFRAME,              WindowFrame),
    DB_DEFINE_COLOR(1608,  TMT_MENUTEXT,                 MenuText),
    DB_DEFINE_COLOR(1609,  TMT_WINDOWTEXT,               WindowText),
    DB_DEFINE_COLOR(1610,  TMT_CAPTIONTEXT,              CaptionText),
    DB_DEFINE_COLOR(1611,  TMT_ACTIVEBORDER,             ActiveBorder),
    DB_DEFINE_COLOR(1612,  TMT_INACTIVEBORDER,           InactiveBorder),
    DB_DEFINE_COLOR(1613,  TMT_APPWORKSPACE,             AppWorkspace),
    DB_DEFINE_COLOR(1614,  TMT_HIGHLIGHT,                Highlight),
    DB_DEFINE_COLOR(1615,  TMT_HIGHLIGHTTEXT,            HighlightText),
    DB_DEFINE_COLOR(1616,  TMT_BTNFACE,                  BtnFace),
    DB_DEFINE_COLOR(1617,  TMT_BTNSHADOW,                BtnShadow),
    DB_DEFINE_COLOR(1618,  TMT_GRAYTEXT,                 GrayText),
    DB_DEFINE_COLOR(1619,  TMT_BTNTEXT,                  BtnText),
    DB_DEFINE_COLOR(1620,  TMT_INACTIVECAPTIONTEXT,      InactiveCaptionText),
    DB_DEFINE_COLOR(1621,  TMT_BTNHIGHLIGHT,             BtnHighlight),
    DB_DEFINE_COLOR(1622,  TMT_DKSHADOW3D,               DkShadow3D),
    DB_DEFINE_COLOR(1623,  TMT_LIGHT3D,                  Light3D),
    DB_DEFINE_COLOR(1624,  TMT_INFOTEXT,                 InfoText),
    DB_DEFINE_COLOR(1625,  TMT_INFOBK,                   InfoBk),
    DB_DEFINE_COLOR(1626,  TMT_BUTTONALTERNATEFACE,      ButtonAlternateFace),
    DB_DEFINE_COLOR(1627,  TMT_HOTTRACKING,              HotTracking),
    DB_DEFINE_COLOR(1628,  TMT_GRADIENTACTIVECAPTION,    GradientActiveCaption),
    DB_DEFINE_COLOR(1629,  TMT_GRADIENTINACTIVECAPTION,  GradientInactiveCaption),
    DB_DEFINE_COLOR(1630,  TMT_MENUHILIGHT,              MenuHilight),
    DB_DEFINE_COLOR(1631,  TMT_MENUBAR,                  MenuBar),
    DB_DEFINE_COLOR(2001,  TMT_FROMCOLOR1,               FromColor1),
    DB_DEFINE_COLOR(2002,  TMT_FROMCOLOR2,               FromColor2),
    DB_DEFINE_COLOR(2003,  TMT_FROMCOLOR3,               FromColor3),
    DB_DEFINE_COLOR(2004,  TMT_FROMCOLOR4,               FromColor4),
    DB_DEFINE_COLOR(2005,  TMT_FROMCOLOR5,               FromColor5),
    DB_DEFINE_COLOR(3801,  TMT_BORDERCOLOR,              BorderColor),
    DB_DEFINE_COLOR(3802,  TMT_FILLCOLOR,                FillColor),
    DB_DEFINE_COLOR(3803,  TMT_TEXTCOLOR,                TextColor),
    DB_DEFINE_COLOR(3804,  TMT_EDGELIGHTCOLOR,           EdgeLightColor),
    DB_DEFINE_COLOR(3805,  TMT_EDGEHIGHLIGHTCOLOR,       EdgeHighlightColor),
    DB_DEFINE_COLOR(3806,  TMT_EDGESHADOWCOLOR,          EdgeShadowColor),
    DB_DEFINE_COLOR(3807,  TMT_EDGEDKSHADOWCOLOR,        EdgeDkShadowColor),
    DB_DEFINE_COLOR(3808,  TMT_EDGEFILLCOLOR,            EdgeFillColor),
    DB_DEFINE_COLOR(3809,  TMT_TRANSPARENTCOLOR,         TrnasparentColor),
    DB_DEFINE_COLOR(3810,  TMT_GRADIENTCOLOR1,           GradientColor1),
    DB_DEFINE_COLOR(3811,  TMT_GRADIENTCOLOR2,           GradientColor2),
    DB_DEFINE_COLOR(3812,  TMT_GRADIENTCOLOR3,           GradientColor3),
    DB_DEFINE_COLOR(3813,  TMT_GRADIENTCOLOR4,           GradientColor4),
    DB_DEFINE_COLOR(3814,  TMT_GRADIENTCOLOR5,           GradientColor5),
    DB_DEFINE_COLOR(3815,  TMT_SHADOWCOLOR,              ShadowColor),
    DB_DEFINE_COLOR(3816,  TMT_GLOWCOLOR,                GlowColor),
    DB_DEFINE_COLOR(3817,  TMT_TEXTBORDERCOLOR,          TextBorderColor),
    DB_DEFINE_COLOR(3818,  TMT_TEXTSHADOWCOLOR,          TextShadowColor),
    DB_DEFINE_COLOR(3819,  TMT_GLYPHTEXTCOLOR,           GlyphTextColor),
    DB_DEFINE_COLOR(3820,  TMT_GLYPHTRANSPARENTCOLOR,    GlyphTransparentColor),
    DB_DEFINE_COLOR(3821,  TMT_FILLCOLORHINT,            FillColorHint),
    DB_DEFINE_COLOR(3822,  TMT_BORDERCOLORHINT,          BorderColorHint),
    DB_DEFINE_COLOR(3823,  TMT_ACCENTCOLORHINT,          AccentColorHint),
    DB_DEFINE_COLOR(3824,  TMT_TEXTCOLORHINT,            TextColorHint),
    DB_DEFINE_COLOR(3825,  TMT_HEADING1TEXTCOLOR,        Heading1TextColor),
    DB_DEFINE_COLOR(3826,  TMT_HEADING2TEXTCOLOR,        Heading2TextColor),
    DB_DEFINE_COLOR(3827,  TMT_BODYTEXTCOLOR,            BodyTextColor),
    DB_DEFINE_COLOR(5003,  TMT_BLENDCOLOR,               BlendColor),

    DB_DEFINE_MARGINS( 205,  TMT_MARGINS,         Margins),
    DB_DEFINE_MARGINS(3601,  TMT_SIZINGMARGINS,   SizingMargins),
    DB_DEFINE_MARGINS(3602,  TMT_CONTENTMARGINS,  ContentMargins),
    DB_DEFINE_MARGINS(3603,  TMT_CAPTIONMARGINS,  CaptionMargins),

    DB_DEFINE_FILENAME( 206,  TMT_FILENAME,          FileName),
    DB_DEFINE_FILENAME(3001,  TMT_IMAGEFILE,         ImageFile),
    DB_DEFINE_FILENAME(3002,  TMT_IMAGEFILE1,        ImageFile1),
    DB_DEFINE_FILENAME(3003,  TMT_IMAGEFILE2,        ImageFile2),
    DB_DEFINE_FILENAME(3004,  TMT_IMAGEFILE3,        ImageFile3),
    DB_DEFINE_FILENAME(3005,  TMT_IMAGEFILE4,        ImageFile4),
    DB_DEFINE_FILENAME(3006,  TMT_IMAGEFILE5,        ImageFile5),
    DB_DEFINE_FILENAME(3008,  TMT_GLYPHIMAGEFILE,    GlyphImageFile),

    DB_DEFINE_SIZE(207,       TMT_SIZE, Size),
    DB_DEFINE_SIZE(TS_MIN,    TS_MIN,   MinSize),
    DB_DEFINE_SIZE(TS_TRUE,   TS_TRUE,  TrueSize),
    DB_DEFINE_SIZE(TS_DRAW,   TS_DRAW,  DrawSize),

    DB_DEFINE_POSITION( 208,  TMT_POSITION,          Position),
    DB_DEFINE_POSITION(3401,  TMT_OFFSET,            Offset),
    DB_DEFINE_POSITION(3402,  TMT_TEXTSHADOWOFFSET,  TextShadowOffset),
    DB_DEFINE_POSITION(3403,  TMT_MINSIZE,           MinSize),
    DB_DEFINE_POSITION(3404,  TMT_MINSIZE1,          MinSize1),
    DB_DEFINE_POSITION(3405,  TMT_MINSIZE2,          MinSize2),
    DB_DEFINE_POSITION(3406,  TMT_MINSIZE3,          MinSize3),
    DB_DEFINE_POSITION(3407,  TMT_MINSIZE4,          MinSize4),
    DB_DEFINE_POSITION(3408,  TMT_MINSIZE5,          MinSize5),
    DB_DEFINE_POSITION(3409,  TMT_NORMALSIZE,        NormalSize),

    DB_DEFINE_RECT( 209,  TMT_RECT,                 Rect),
    DB_DEFINE_RECT(5002,  TMT_DEFAULTPANESIZE,      DefaultPaneSize),
    DB_DEFINE_RECT(5004,  TMT_CUSTOMSPLITRECT,      CustomSplitRect),
    DB_DEFINE_RECT(5005,  TMT_ANIMATIONBUTTONRECT,  AnimationButtonRect),
    DB_DEFINE_RECT(8002,  TMT_ATLASRECT,            AtlasRect),


    DB_DEFINE_FONT( 210,  TMT_FONT,              Font),
    DB_DEFINE_FONT( 801,  TMT_CAPTIONFONT,       CaptionFont),
    DB_DEFINE_FONT( 802,  TMT_SMALLCAPTIONFONT,  SmallCaptionFont),
    DB_DEFINE_FONT( 803,  TMT_MENUFONT,          MenuFont),
    DB_DEFINE_FONT( 804,  TMT_STATUSFONT,        StatusFont),
    DB_DEFINE_FONT( 805,  TMT_MSGBOXFONT,        MsgBoxFont),
    DB_DEFINE_FONT( 806,  TMT_ICONTITLEFONT,     IconTitleFont),
    DB_DEFINE_FONT( 807,  TMT_HEADING1FONT,      Heading1Font),
    DB_DEFINE_FONT( 808,  TMT_HEADING2FONT,      Heading2Font),
    DB_DEFINE_FONT( 809,  TMT_BODYFONT,          BodyFont),
    DB_DEFINE_FONT(2601,  TMT_GLYPHFONT,         GlyphFont),

    DB_DEFINE_INTLIST(6000, TMT_TRANSITIONDURATIONS, TransitionDuration),

    DB_DEFINE_DISKSTREAM(213, TMT_DISKSTREAM, DiskStream),

    DB_DEFINE_STREAM(214, TMT_STREAM, Stream)
};


const db_prop_t* db_props = db_props_helper;
int db_n_props = TE_ARRAY_SIZE(db_props_helper);
