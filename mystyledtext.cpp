
//----------------------------------------------------------------------------
// informations
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
// headers
//----------------------------------------------------------------------------

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

// for all others, include the necessary headers (this file is usually all you
// need because it includes almost all 'standard' wxWidgets headers)
#ifndef WX_PRECOMP
    #include "wx/wx.h"
    #include "wx/textdlg.h"
#endif

//! wxWidgets headers
#include "wx/file.h"     // raw file io support
#include "wx/filename.h" // filename support

//! application headers
#include "defsext.h"     // additional definitions

#include "mystyledtext.h"

//----------------------------------------------------------------------------
// resources
//----------------------------------------------------------------------------


//============================================================================
// declarations
//============================================================================

// The (uniform) style used for the annotations.
const int ANNOTATION_STYLE = wxSTC_STYLE_LASTPREDEFINED + 1;

//============================================================================
// implementation
//============================================================================

//----------------------------------------------------------------------------
// MyStyledTextCtrl
//----------------------------------------------------------------------------

MyStyledTextCtrl::MyStyledTextCtrl (wxWindow *parent, wxWindowID id,
            const wxPoint &pos,
            const wxSize &size,
            long style)
    : wxStyledTextCtrl (parent, id, pos, size, style) {

    m_filename = wxEmptyString;

    m_LineNrID = 0;
    m_DividerID = 1;
    m_FoldingID = 2;

    // initialize language
    m_language = NULL;

    // Use all the bits in the style byte as styles, not indicators.
    SetStyleBits(8);
    
//    // default font for all styles
//    SetViewEOL (g_CommonPrefs.displayEOLEnable);
//    SetIndentationGuides (g_CommonPrefs.indentGuideEnable);
//    SetEdgeMode (g_CommonPrefs.longLineOnEnable?
//                 wxSTC_EDGE_LINE: wxSTC_EDGE_NONE);
//    SetViewWhiteSpace (g_CommonPrefs.whiteSpaceEnable?
//                       wxSTC_WS_VISIBLEALWAYS: wxSTC_WS_INVISIBLE);
//    SetOvertype (g_CommonPrefs.overTypeInitial);
//    SetReadOnly (g_CommonPrefs.readOnlyInitial);
//    SetWrapMode (g_CommonPrefs.wrapModeInitial?
//                 wxSTC_WRAP_WORD: wxSTC_WRAP_NONE);
//    wxFont font (10, wxMODERN, wxNORMAL, wxNORMAL);
//    StyleSetFont (wxSTC_STYLE_DEFAULT, font);
//    StyleSetForeground (wxSTC_STYLE_DEFAULT, *wxBLACK);
//    StyleSetBackground (wxSTC_STYLE_DEFAULT, *wxWHITE);
//    StyleSetForeground (wxSTC_STYLE_LINENUMBER, wxColour (wxT("DARK GREY")));
//    StyleSetBackground (wxSTC_STYLE_LINENUMBER, *wxWHITE);
//    StyleSetForeground(wxSTC_STYLE_INDENTGUIDE, wxColour (wxT("DARK GREY")));
//    InitializePrefs (DEFAULT_LANGUAGE);
//
//    // set visibility
//    SetVisiblePolicy (wxSTC_VISIBLE_STRICT|wxSTC_VISIBLE_SLOP, 1);
//    SetXCaretPolicy (wxSTC_CARET_EVEN|wxSTC_VISIBLE_STRICT|wxSTC_CARET_SLOP, 1);
//    SetYCaretPolicy (wxSTC_CARET_EVEN|wxSTC_VISIBLE_STRICT|wxSTC_CARET_SLOP, 1);
//
//    // markers
//    MarkerDefine (wxSTC_MARKNUM_FOLDER,        wxSTC_MARK_DOTDOTDOT, wxT("BLACK"), wxT("BLACK"));
//    MarkerDefine (wxSTC_MARKNUM_FOLDEROPEN,    wxSTC_MARK_ARROWDOWN, wxT("BLACK"), wxT("BLACK"));
//    MarkerDefine (wxSTC_MARKNUM_FOLDERSUB,     wxSTC_MARK_EMPTY,     wxT("BLACK"), wxT("BLACK"));
//    MarkerDefine (wxSTC_MARKNUM_FOLDEREND,     wxSTC_MARK_DOTDOTDOT, wxT("BLACK"), wxT("WHITE"));
//    MarkerDefine (wxSTC_MARKNUM_FOLDEROPENMID, wxSTC_MARK_ARROWDOWN, wxT("BLACK"), wxT("WHITE"));
//    MarkerDefine (wxSTC_MARKNUM_FOLDERMIDTAIL, wxSTC_MARK_EMPTY,     wxT("BLACK"), wxT("BLACK"));
//    MarkerDefine (wxSTC_MARKNUM_FOLDERTAIL,    wxSTC_MARK_EMPTY,     wxT("BLACK"), wxT("BLACK"));
//
//    // annotations
//    AnnotationSetVisible(wxSTC_ANNOTATION_BOXED);
//
//    // miscellaneous
//    m_LineNrMargin = TextWidth (wxSTC_STYLE_LINENUMBER, wxT("_999999"));
//    m_FoldingMargin = 16;
//    CmdKeyClear (wxSTC_KEY_TAB, 0); // this is done by the menu accelerator key
//    SetLayoutCache (wxSTC_CACHE_PAGE);

    SetWrapMode(true);
    wxFont font(11, wxROMAN, wxNORMAL, wxNORMAL);
    StyleSetFont(0, font); //utile ?
    SetLexer(wxSTC_LEX_HTML);
    StyleSetForeground (wxSTC_H_DOUBLESTRING,     wxColour(255,0,0));
    StyleSetForeground (wxSTC_H_SINGLESTRING,     wxColour(255,0,0));
    StyleSetForeground (wxSTC_H_ENTITY,           wxColour(255,0,0));
    StyleSetForeground (wxSTC_H_TAG,              wxColour(0,150,0));
    StyleSetForeground (wxSTC_H_TAGUNKNOWN,       wxColour(0,150,0));
    StyleSetForeground (wxSTC_H_ATTRIBUTE,        wxColour(0,0,150));
    StyleSetForeground (wxSTC_H_ATTRIBUTEUNKNOWN, wxColour(0,0,150));
    StyleSetForeground (wxSTC_H_COMMENT,          wxColour(150,150,150));   
    ConnectEvents();
}

MyStyledTextCtrl::~MyStyledTextCtrl () 
{ 
    DisconnectEvents();
}

void MyStyledTextCtrl::ConnectEvents()
{

    // common
    Connect(wxID_ANY, wxEVT_SIZE,  wxSizeEventHandler(MyStyledTextCtrl::OnSize));
    // edit
    Connect(wxID_CLEAR, wxEVT_COMMAND_MENU_SELECTED,  wxCommandEventHandler(MyStyledTextCtrl::OnEditClear));
    Connect(wxID_CUT, wxEVT_COMMAND_MENU_SELECTED,  wxCommandEventHandler(MyStyledTextCtrl::OnEditCut));
    Connect(wxID_COPY, wxEVT_COMMAND_MENU_SELECTED,  wxCommandEventHandler(MyStyledTextCtrl::OnEditCopy));
    Connect(wxID_PASTE, wxEVT_COMMAND_MENU_SELECTED,  wxCommandEventHandler(MyStyledTextCtrl::OnEditPaste));
    Connect(myID_INDENTINC, wxEVT_COMMAND_MENU_SELECTED,  wxCommandEventHandler(MyStyledTextCtrl::OnEditIndentInc));
    Connect(myID_INDENTRED, wxEVT_COMMAND_MENU_SELECTED,  wxCommandEventHandler(MyStyledTextCtrl::OnEditIndentRed));
    Connect(wxID_SELECTALL, wxEVT_COMMAND_MENU_SELECTED,  wxCommandEventHandler(MyStyledTextCtrl::OnEditSelectAll));
    Connect(myID_SELECTLINE, wxEVT_COMMAND_MENU_SELECTED,  wxCommandEventHandler(MyStyledTextCtrl::OnEditSelectLine));
    Connect(wxID_REDO, wxEVT_COMMAND_MENU_SELECTED,  wxCommandEventHandler(MyStyledTextCtrl::OnEditRedo));
    Connect(wxID_UNDO, wxEVT_COMMAND_MENU_SELECTED,  wxCommandEventHandler(MyStyledTextCtrl::OnEditUndo));
    // find
    Connect(wxID_FIND, wxEVT_COMMAND_MENU_SELECTED,  wxCommandEventHandler(MyStyledTextCtrl::OnFind));
    Connect(myID_FINDNEXT, wxEVT_COMMAND_MENU_SELECTED,  wxCommandEventHandler(MyStyledTextCtrl::OnFindNext));
    Connect(myID_REPLACE, wxEVT_COMMAND_MENU_SELECTED,  wxCommandEventHandler(MyStyledTextCtrl::OnReplace));
    Connect(myID_REPLACENEXT, wxEVT_COMMAND_MENU_SELECTED,  wxCommandEventHandler(MyStyledTextCtrl::OnReplaceNext));
    Connect(myID_BRACEMATCH, wxEVT_COMMAND_MENU_SELECTED,  wxCommandEventHandler(MyStyledTextCtrl::OnBraceMatch));
    Connect(myID_GOTO, wxEVT_COMMAND_MENU_SELECTED,  wxCommandEventHandler(MyStyledTextCtrl::OnGoto));
    // view
    Connect(myID_HILIGHTFIRST, wxEVT_COMMAND_MENU_SELECTED,  wxCommandEventHandler(MyStyledTextCtrl::OnHilightLang));
    Connect(myID_HILIGHTLAST, wxEVT_COMMAND_MENU_SELECTED,  wxCommandEventHandler(MyStyledTextCtrl::OnHilightLang));

    Connect(myID_DISPLAYEOL, wxEVT_COMMAND_MENU_SELECTED,  wxCommandEventHandler(MyStyledTextCtrl::OnDisplayEOL));
    Connect(myID_INDENTGUIDE, wxEVT_COMMAND_MENU_SELECTED,  wxCommandEventHandler(MyStyledTextCtrl::OnIndentGuide));
    Connect(myID_LINENUMBER, wxEVT_COMMAND_MENU_SELECTED,  wxCommandEventHandler(MyStyledTextCtrl::OnLineNumber));
    Connect(myID_LONGLINEON, wxEVT_COMMAND_MENU_SELECTED,  wxCommandEventHandler(MyStyledTextCtrl::OnLongLineOn));
    Connect(myID_WHITESPACE, wxEVT_COMMAND_MENU_SELECTED,  wxCommandEventHandler(MyStyledTextCtrl::OnWhiteSpace));
    Connect(myID_FOLDTOGGLE, wxEVT_COMMAND_MENU_SELECTED,  wxCommandEventHandler(MyStyledTextCtrl::OnFoldToggle));
    Connect(myID_OVERTYPE, wxEVT_COMMAND_MENU_SELECTED,  wxCommandEventHandler(MyStyledTextCtrl::OnSetOverType));
    Connect(myID_READONLY, wxEVT_COMMAND_MENU_SELECTED,  wxCommandEventHandler(MyStyledTextCtrl::OnSetReadOnly));
    Connect(myID_WRAPMODEON, wxEVT_COMMAND_MENU_SELECTED,  wxCommandEventHandler(MyStyledTextCtrl::OnWrapmodeOn));
    Connect(myID_CHARSETANSI, wxEVT_COMMAND_MENU_SELECTED,  wxCommandEventHandler(MyStyledTextCtrl::OnUseCharset));
    Connect(myID_CHARSETMAC, wxEVT_COMMAND_MENU_SELECTED,  wxCommandEventHandler(MyStyledTextCtrl::OnUseCharset));
    // annotations
    Connect(myID_ANNOTATION_ADD, wxEVT_COMMAND_MENU_SELECTED,  wxCommandEventHandler(MyStyledTextCtrl::OnAnnotationAdd));
    Connect(myID_ANNOTATION_REMOVE, wxEVT_COMMAND_MENU_SELECTED,  wxCommandEventHandler(MyStyledTextCtrl::OnAnnotationRemove));
    Connect(myID_ANNOTATION_CLEAR, wxEVT_COMMAND_MENU_SELECTED,  wxCommandEventHandler(MyStyledTextCtrl::OnAnnotationClear));
    Connect(myID_ANNOTATION_STYLE_HIDDEN, wxEVT_COMMAND_MENU_SELECTED,  wxCommandEventHandler(MyStyledTextCtrl::OnAnnotationStyle));
    Connect(myID_ANNOTATION_STYLE_STANDARD, wxEVT_COMMAND_MENU_SELECTED,  wxCommandEventHandler(MyStyledTextCtrl::OnAnnotationStyle));
    Connect(myID_ANNOTATION_STYLE_BOXED, wxEVT_COMMAND_MENU_SELECTED,  wxCommandEventHandler(MyStyledTextCtrl::OnAnnotationStyle));
    // extra
    Connect(myID_CHANGELOWER, wxEVT_COMMAND_MENU_SELECTED,  wxCommandEventHandler(MyStyledTextCtrl::OnChangeCase));
    Connect(myID_CHANGEUPPER, wxEVT_COMMAND_MENU_SELECTED,  wxCommandEventHandler(MyStyledTextCtrl::OnChangeCase));
    Connect(myID_CONVERTCR, wxEVT_COMMAND_MENU_SELECTED,  wxCommandEventHandler(MyStyledTextCtrl::OnConvertEOL));
    Connect(myID_CONVERTCRLF, wxEVT_COMMAND_MENU_SELECTED,  wxCommandEventHandler(MyStyledTextCtrl::OnConvertEOL));
    Connect(myID_CONVERTLF, wxEVT_COMMAND_MENU_SELECTED,  wxCommandEventHandler(MyStyledTextCtrl::OnConvertEOL));
    // stc
    Connect(wxID_ANY, wxEVT_STC_MARGINCLICK,  wxStyledTextEventHandler(MyStyledTextCtrl::OnMarginClick));
    Connect(wxID_ANY, wxEVT_STC_CHARADDED,  wxStyledTextEventHandler(MyStyledTextCtrl::OnCharAdded));
    Connect(wxID_ANY, wxEVT_STC_KEY,  wxStyledTextEventHandler(MyStyledTextCtrl::OnKey));

//    ( MyStyledTextCtrl:: )
    Connect(wxID_ANY, wxEVT_KEY_DOWN,  wxKeyEventHandler(MyStyledTextCtrl::OnKeyDown));
}

void MyStyledTextCtrl::DisconnectEvents()
{
}

//----------------------------------------------------------------------------
// common event handlers
void MyStyledTextCtrl::OnSize( wxSizeEvent& event ) {
    int x = GetClientSize().x +
            (g_CommonPrefs.lineNumberEnable? m_LineNrMargin: 0) +
            (g_CommonPrefs.foldEnable? m_FoldingMargin: 0);
    if (x > 0) SetScrollWidth (x);
    event.Skip();
}

// edit event handlers
void MyStyledTextCtrl::OnEditRedo (wxCommandEvent& event) {
    if (!CanRedo()) return;
    Redo ();
}

void MyStyledTextCtrl::OnEditUndo (wxCommandEvent& event) {
    if (!CanUndo()) return;
    Undo ();
}

void MyStyledTextCtrl::OnEditClear (wxCommandEvent& event) {
    if (GetReadOnly()) return;
    Clear ();
}

void MyStyledTextCtrl::OnKey (wxStyledTextEvent& event)
{
    wxMessageBox("OnKey");
}

void MyStyledTextCtrl::OnKeyDown (wxKeyEvent &event)
{
    if (CallTipActive())
        CallTipCancel();
    if (event.GetKeyCode() == WXK_SPACE && event.ControlDown() && event.ShiftDown())
    {
        int pos = GetCurrentPos();
        CallTipSetBackground(*wxYELLOW);
        CallTipShow(pos,
                    "This is a CallTip with multiple lines.\n"
                    "It is meant to be a context sensitive popup helper for the user.");
        return;
    }
    event.Skip();
}

void MyStyledTextCtrl::OnEditCut (wxCommandEvent& event) {
    if (GetReadOnly() || (GetSelectionEnd()-GetSelectionStart() <= 0)) return;
    Cut ();
}

void MyStyledTextCtrl::OnEditCopy (wxCommandEvent& event) {
    if (GetSelectionEnd()-GetSelectionStart() <= 0) return;
    Copy ();
}

void MyStyledTextCtrl::OnEditPaste (wxCommandEvent& event) {
    if (!CanPaste()) return;
    Paste ();
}

void MyStyledTextCtrl::OnFind (wxCommandEvent& event) {
}

void MyStyledTextCtrl::OnFindNext (wxCommandEvent& event) {
}

void MyStyledTextCtrl::OnReplace (wxCommandEvent& event) {
}

void MyStyledTextCtrl::OnReplaceNext (wxCommandEvent& event) {
}

void MyStyledTextCtrl::OnBraceMatch (wxCommandEvent& event) {
    int min = GetCurrentPos ();
    int max = BraceMatch (min);
    if (max > (min+1)) {
        BraceHighlight (min+1, max);
        SetSelection (min+1, max);
    }else{
        BraceBadLight (min);
    }
}

void MyStyledTextCtrl::OnGoto (wxCommandEvent& event) {
}

void MyStyledTextCtrl::OnEditIndentInc (wxCommandEvent& event) {
    CmdKeyExecute (wxSTC_CMD_TAB);
}

void MyStyledTextCtrl::OnEditIndentRed (wxCommandEvent& event) {
    CmdKeyExecute (wxSTC_CMD_DELETEBACK);
}

void MyStyledTextCtrl::OnEditSelectAll (wxCommandEvent& event) {
    SetSelection (0, GetTextLength ());
}

void MyStyledTextCtrl::OnEditSelectLine (wxCommandEvent& event) {
    int lineStart = PositionFromLine (GetCurrentLine());
    int lineEnd = PositionFromLine (GetCurrentLine() + 1);
    SetSelection (lineStart, lineEnd);
}

void MyStyledTextCtrl::OnHilightLang (wxCommandEvent &event) {
    InitializePrefs (g_LanguagePrefs [event.GetId() - myID_HILIGHTFIRST].name);
}

void MyStyledTextCtrl::OnDisplayEOL (wxCommandEvent& event) {
    SetViewEOL (!GetViewEOL());
}

void MyStyledTextCtrl::OnIndentGuide (wxCommandEvent& event) {
    SetIndentationGuides (!GetIndentationGuides());
}

void MyStyledTextCtrl::OnLineNumber (wxCommandEvent& event) {
    SetMarginWidth (m_LineNrID,
                    GetMarginWidth (m_LineNrID) == 0? m_LineNrMargin: 0);
}

void MyStyledTextCtrl::OnLongLineOn (wxCommandEvent& event) {
    SetEdgeMode (GetEdgeMode() == 0? wxSTC_EDGE_LINE: wxSTC_EDGE_NONE);
}

void MyStyledTextCtrl::OnWhiteSpace (wxCommandEvent& event) {
    SetViewWhiteSpace (GetViewWhiteSpace() == 0?
                       wxSTC_WS_VISIBLEALWAYS: wxSTC_WS_INVISIBLE);
}

void MyStyledTextCtrl::OnFoldToggle (wxCommandEvent& event) {
    ToggleFold (GetFoldParent(GetCurrentLine()));
}

void MyStyledTextCtrl::OnSetOverType (wxCommandEvent& event) {
    SetOvertype (!GetOvertype());
}

void MyStyledTextCtrl::OnSetReadOnly (wxCommandEvent& event) {
    SetReadOnly (!GetReadOnly());
}

void MyStyledTextCtrl::OnWrapmodeOn (wxCommandEvent& event) {
    SetWrapMode (GetWrapMode() == 0? wxSTC_WRAP_WORD: wxSTC_WRAP_NONE);
}

void MyStyledTextCtrl::OnUseCharset (wxCommandEvent &event) {
    int Nr;
    int charset = GetCodePage();
    switch (event.GetId()) {
        case myID_CHARSETANSI: {charset = wxSTC_CHARSET_ANSI; break;}
        case myID_CHARSETMAC: {charset = wxSTC_CHARSET_ANSI; break;}
    }
    for (Nr = 0; Nr < wxSTC_STYLE_LASTPREDEFINED; Nr++) {
        StyleSetCharacterSet (Nr, charset);
    }
    SetCodePage (charset);
}

void MyStyledTextCtrl::OnAnnotationAdd(wxCommandEvent& WXUNUSED(event))
{
    const int line = GetCurrentLine();

    wxString ann = AnnotationGetText(line);
    ann = wxGetTextFromUser
          (
            wxString::Format("Enter annotation for the line %d", line),
            "Edit annotation",
            ann,
            this
          );
    if ( ann.empty() )
        return;

    AnnotationSetText(line, ann);
    AnnotationSetStyle(line, ANNOTATION_STYLE);

    // Scintilla doesn't update the scroll width for annotations, even with
    // scroll width tracking on, so do it manually.
    const int width = GetScrollWidth();

    // NB: The following adjustments are only needed when using
    //     wxSTC_ANNOTATION_BOXED annotations style, but we apply them always
    //     in order to make things simpler and not have to redo the width
    //     calculations when the annotations visibility changes. In a real
    //     program you'd either just stick to a fixed annotations visibility or
    //     update the width when it changes.

    // Take into account the fact that the annotation is shown indented, with
    // the same indent as the line it's attached to.
    int indent = GetLineIndentation(line);

    // This is just a hack to account for the width of the box, there doesn't
    // seem to be any way to get it directly from Scintilla.
    indent += 3;

    const int widthAnn = TextWidth(ANNOTATION_STYLE, ann + wxString(indent, ' '));

    if (widthAnn > width)
        SetScrollWidth(widthAnn);
}

void MyStyledTextCtrl::OnAnnotationRemove(wxCommandEvent& WXUNUSED(event))
{
    AnnotationSetText(GetCurrentLine(), wxString());
}

void MyStyledTextCtrl::OnAnnotationClear(wxCommandEvent& WXUNUSED(event))
{
    AnnotationClearAll();
}

void MyStyledTextCtrl::OnAnnotationStyle(wxCommandEvent& event)
{
    int style = 0;
    switch (event.GetId()) {
        case myID_ANNOTATION_STYLE_HIDDEN:
            style = wxSTC_ANNOTATION_HIDDEN;
            break;

        case myID_ANNOTATION_STYLE_STANDARD:
            style = wxSTC_ANNOTATION_STANDARD;
            break;

        case myID_ANNOTATION_STYLE_BOXED:
            style = wxSTC_ANNOTATION_BOXED;
            break;
    }

    AnnotationSetVisible(style);
}

void MyStyledTextCtrl::OnChangeCase (wxCommandEvent &event) {
    switch (event.GetId()) {
        case myID_CHANGELOWER: {
            CmdKeyExecute (wxSTC_CMD_LOWERCASE);
            break;
        }
        case myID_CHANGEUPPER: {
            CmdKeyExecute (wxSTC_CMD_UPPERCASE);
            break;
        }
    }
}

void MyStyledTextCtrl::OnConvertEOL (wxCommandEvent &event) {
    int eolMode = GetEOLMode();
    switch (event.GetId()) {
        case myID_CONVERTCR: { eolMode = wxSTC_EOL_CR; break;}
        case myID_CONVERTCRLF: { eolMode = wxSTC_EOL_CRLF; break;}
        case myID_CONVERTLF: { eolMode = wxSTC_EOL_LF; break;}
    }
    ConvertEOLs (eolMode);
    SetEOLMode (eolMode);
}

//! misc
void MyStyledTextCtrl::OnMarginClick (wxStyledTextEvent &event) {
    if (event.GetMargin() == 2) {
        int lineClick = LineFromPosition (event.GetPosition());
        int levelClick = GetFoldLevel (lineClick);
        if ((levelClick & wxSTC_FOLDLEVELHEADERFLAG) > 0) {
            ToggleFold (lineClick);
        }
    }
}

void MyStyledTextCtrl::OnCharAdded (wxStyledTextEvent &event) {
    char chr = (char)event.GetKey();
    int currentLine = GetCurrentLine();
    // Change this if support for mac files with \r is needed
    if (chr == '\n') {
        int lineInd = 0;
        if (currentLine > 0) {
            lineInd = GetLineIndentation(currentLine - 1);
        }
        if (lineInd == 0) return;
        SetLineIndentation (currentLine, lineInd);
        GotoPos(PositionFromLine (currentLine) + lineInd);
    }
}


//----------------------------------------------------------------------------
// private functions
wxString MyStyledTextCtrl::DeterminePrefs (const wxString &filename) {

    LanguageInfo const* curInfo;

    // determine language from filepatterns
    int languageNr;
    for (languageNr = 0; languageNr < g_LanguagePrefsSize; languageNr++) {
        curInfo = &g_LanguagePrefs [languageNr];
        wxString filepattern = curInfo->filepattern;
        filepattern.Lower();
        while (!filepattern.empty()) {
            wxString cur = filepattern.BeforeFirst (';');
            if ((cur == filename) ||
                (cur == (filename.BeforeLast ('.') + wxT(".*"))) ||
                (cur == (wxT("*.") + filename.AfterLast ('.')))) {
                return curInfo->name;
            }
            filepattern = filepattern.AfterFirst (';');
        }
    }
    return wxEmptyString;

}

bool MyStyledTextCtrl::InitializePrefs (const wxString &name) {

    // initialize styles
    StyleClearAll();
    LanguageInfo const* curInfo = NULL;

    // determine language
    bool found = false;
    int languageNr;
    for (languageNr = 0; languageNr < g_LanguagePrefsSize; languageNr++) {
        curInfo = &g_LanguagePrefs [languageNr];
        if (curInfo->name == name) {
            found = true;
            break;
        }
    }
    if (!found) return false;

    // set lexer and language
    SetLexer (curInfo->lexer);
    m_language = curInfo;

    // set margin for line numbers
    SetMarginType (m_LineNrID, wxSTC_MARGIN_NUMBER);
    StyleSetForeground (wxSTC_STYLE_LINENUMBER, wxColour (wxT("DARK GREY")));
    StyleSetBackground (wxSTC_STYLE_LINENUMBER, *wxWHITE);
    SetMarginWidth (m_LineNrID, 0); // start out not visible

    // annotations style
    StyleSetBackground(ANNOTATION_STYLE, wxColour(244, 220, 220));
    StyleSetForeground(ANNOTATION_STYLE, *wxBLACK);
    StyleSetSizeFractional(ANNOTATION_STYLE,
            (StyleGetSizeFractional(wxSTC_STYLE_DEFAULT)*4)/5);

    // default fonts for all styles!
    int Nr;
    for (Nr = 0; Nr < wxSTC_STYLE_LASTPREDEFINED; Nr++) {
        wxFont font (10, wxMODERN, wxNORMAL, wxNORMAL);
        StyleSetFont (Nr, font);
    }

    // set common styles
    StyleSetForeground (wxSTC_STYLE_DEFAULT, wxColour (wxT("DARK GREY")));
    StyleSetForeground (wxSTC_STYLE_INDENTGUIDE, wxColour (wxT("DARK GREY")));

    // initialize settings
    if (g_CommonPrefs.syntaxEnable) {
        int keywordnr = 0;
        for (Nr = 0; Nr < STYLE_TYPES_COUNT; Nr++) {
            if (curInfo->styles[Nr].type == -1) continue;
            const StyleInfo &curType = g_StylePrefs [curInfo->styles[Nr].type];
            wxFont font (curType.fontsize, wxMODERN, wxNORMAL, wxNORMAL, false,
                         curType.fontname);
            StyleSetFont (Nr, font);
            if (curType.foreground) {
                StyleSetForeground (Nr, wxColour (curType.foreground));
            }
            if (curType.background) {
                StyleSetBackground (Nr, wxColour (curType.background));
            }
            StyleSetBold (Nr, (curType.fontstyle & mySTC_STYLE_BOLD) > 0);
            StyleSetItalic (Nr, (curType.fontstyle & mySTC_STYLE_ITALIC) > 0);
            StyleSetUnderline (Nr, (curType.fontstyle & mySTC_STYLE_UNDERL) > 0);
            StyleSetVisible (Nr, (curType.fontstyle & mySTC_STYLE_HIDDEN) == 0);
            StyleSetCase (Nr, curType.lettercase);
            const char *pwords = curInfo->styles[Nr].words;
            if (pwords) {
                SetKeyWords (keywordnr, pwords);
                keywordnr += 1;
            }
        }
    }

    // set margin as unused
    SetMarginType (m_DividerID, wxSTC_MARGIN_SYMBOL);
    SetMarginWidth (m_DividerID, 0);
    SetMarginSensitive (m_DividerID, false);

    // folding
    SetMarginType (m_FoldingID, wxSTC_MARGIN_SYMBOL);
    SetMarginMask (m_FoldingID, wxSTC_MASK_FOLDERS);
    StyleSetBackground (m_FoldingID, *wxWHITE);
    SetMarginWidth (m_FoldingID, 0);
    SetMarginSensitive (m_FoldingID, false);
    if (g_CommonPrefs.foldEnable) {
        SetMarginWidth (m_FoldingID, curInfo->folds != 0? m_FoldingMargin: 0);
        SetMarginSensitive (m_FoldingID, curInfo->folds != 0);
        SetProperty (wxT("fold"), curInfo->folds != 0? wxT("1"): wxT("0"));
        SetProperty (wxT("fold.comment"),
                     (curInfo->folds & mySTC_FOLD_COMMENT) > 0? wxT("1"): wxT("0"));
        SetProperty (wxT("fold.compact"),
                     (curInfo->folds & mySTC_FOLD_COMPACT) > 0? wxT("1"): wxT("0"));
        SetProperty (wxT("fold.preprocessor"),
                     (curInfo->folds & mySTC_FOLD_PREPROC) > 0? wxT("1"): wxT("0"));
        SetProperty (wxT("fold.html"),
                     (curInfo->folds & mySTC_FOLD_HTML) > 0? wxT("1"): wxT("0"));
        SetProperty (wxT("fold.html.preprocessor"),
                     (curInfo->folds & mySTC_FOLD_HTMLPREP) > 0? wxT("1"): wxT("0"));
        SetProperty (wxT("fold.comment.python"),
                     (curInfo->folds & mySTC_FOLD_COMMENTPY) > 0? wxT("1"): wxT("0"));
        SetProperty (wxT("fold.quotes.python"),
                     (curInfo->folds & mySTC_FOLD_QUOTESPY) > 0? wxT("1"): wxT("0"));
    }
    SetFoldFlags (wxSTC_FOLDFLAG_LINEBEFORE_CONTRACTED |
                  wxSTC_FOLDFLAG_LINEAFTER_CONTRACTED);

    // set spaces and indention
    SetTabWidth (4);
    SetUseTabs (false);
    SetTabIndents (true);
    SetBackSpaceUnIndents (true);
    SetIndent (g_CommonPrefs.indentEnable? 4: 0);

    // others
    SetViewEOL (g_CommonPrefs.displayEOLEnable);
    SetIndentationGuides (g_CommonPrefs.indentGuideEnable);
    SetEdgeColumn (80);
    SetEdgeMode (g_CommonPrefs.longLineOnEnable? wxSTC_EDGE_LINE: wxSTC_EDGE_NONE);
    SetViewWhiteSpace (g_CommonPrefs.whiteSpaceEnable?
                       wxSTC_WS_VISIBLEALWAYS: wxSTC_WS_INVISIBLE);
    SetOvertype (g_CommonPrefs.overTypeInitial);
    SetReadOnly (g_CommonPrefs.readOnlyInitial);
    SetWrapMode (g_CommonPrefs.wrapModeInitial?
                 wxSTC_WRAP_WORD: wxSTC_WRAP_NONE);

    return true;
}

bool MyStyledTextCtrl::LoadFile ()
{
#if wxUSE_FILEDLG
    // get filname
    if (!m_filename) {
        wxFileDialog dlg (this, wxT("Open file"), wxEmptyString, wxEmptyString,
                          wxT("Any file (*)|*"), wxFD_OPEN | wxFD_FILE_MUST_EXIST | wxFD_CHANGE_DIR);
        if (dlg.ShowModal() != wxID_OK) return false;
        m_filename = dlg.GetPath();
    }

    // load file
    return LoadFile (m_filename);
#else
    return false;
#endif // wxUSE_FILEDLG
}

bool MyStyledTextCtrl::LoadFile (const wxString &filename) {

    // load file in edit and clear undo
    if (!filename.empty()) m_filename = filename;

    wxStyledTextCtrl::LoadFile(m_filename);

    EmptyUndoBuffer();

    // determine lexer language
    wxFileName fname (m_filename);
    InitializePrefs (DeterminePrefs (fname.GetFullName()));

    return true;
}

bool MyStyledTextCtrl::SaveFile ()
{
#if wxUSE_FILEDLG
    // return if no change
    if (!Modified()) return true;

    // get filname
    if (!m_filename) {
        wxFileDialog dlg (this, wxT("Save file"), wxEmptyString, wxEmptyString, wxT("Any file (*)|*"),
                          wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
        if (dlg.ShowModal() != wxID_OK) return false;
        m_filename = dlg.GetPath();
    }

    // save file
    return SaveFile (m_filename);
#else
    return false;
#endif // wxUSE_FILEDLG
}

bool MyStyledTextCtrl::SaveFile (const wxString &filename) {

    // return if no change
    if (!Modified()) return true;

//     // save edit in file and clear undo
//     if (!filename.empty()) m_filename = filename;
//     wxFile file (m_filename, wxFile::write);
//     if (!file.IsOpened()) return false;
//     wxString buf = GetText();
//     bool okay = file.Write (buf);
//     file.Close();
//     if (!okay) return false;
//     EmptyUndoBuffer();
//     SetSavePoint();

//     return true;

    return wxStyledTextCtrl::SaveFile(filename);

}

bool MyStyledTextCtrl::Modified () {

    // return modified state
    return (GetModify() && !GetReadOnly());
}


//----------------------------------------------------------------------------
// EditProperties
//----------------------------------------------------------------------------

EditProperties::EditProperties (MyStyledTextCtrl *edit,
                                long style)
        : wxDialog (edit, wxID_ANY, wxEmptyString,
                    wxDefaultPosition, wxDefaultSize,
                    style | wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER) {

    // sets the application title
    SetTitle (_("Properties"));
    wxString text;

    // fullname
    wxBoxSizer *fullname = new wxBoxSizer (wxHORIZONTAL);
    fullname->Add (10, 0);
    fullname->Add (new wxStaticText (this, wxID_ANY, _("Full filename"),
                                     wxDefaultPosition, wxSize(80, wxDefaultCoord)),
                   0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL);
    fullname->Add (new wxStaticText (this, wxID_ANY, edit->GetFilename()),
                   0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL);

    // text info
    wxGridSizer *textinfo = new wxGridSizer (4, 0, 2);
    textinfo->Add (new wxStaticText (this, wxID_ANY, _("Language"),
                                     wxDefaultPosition, wxSize(80, wxDefaultCoord)),
                   0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxLEFT, 4);
    textinfo->Add (new wxStaticText (this, wxID_ANY, edit->m_language->name),
                   0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxRIGHT, 4);
    textinfo->Add (new wxStaticText (this, wxID_ANY, _("Lexer-ID: "),
                                     wxDefaultPosition, wxSize(80, wxDefaultCoord)),
                   0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxLEFT, 4);
    text = wxString::Format (wxT("%d"), edit->GetLexer());
    textinfo->Add (new wxStaticText (this, wxID_ANY, text),
                   0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxRIGHT, 4);
    wxString EOLtype = wxEmptyString;
    switch (edit->GetEOLMode()) {
        case wxSTC_EOL_CR: {EOLtype = wxT("CR (Unix)"); break; }
        case wxSTC_EOL_CRLF: {EOLtype = wxT("CRLF (Windows)"); break; }
        case wxSTC_EOL_LF: {EOLtype = wxT("CR (Macintosh)"); break; }
    }
    textinfo->Add (new wxStaticText (this, wxID_ANY, _("Line endings"),
                                     wxDefaultPosition, wxSize(80, wxDefaultCoord)),
                   0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxLEFT, 4);
    textinfo->Add (new wxStaticText (this, wxID_ANY, EOLtype),
                   0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxRIGHT, 4);

    // text info box
    wxStaticBoxSizer *textinfos = new wxStaticBoxSizer (
                     new wxStaticBox (this, wxID_ANY, _("Informations")),
                     wxVERTICAL);
    textinfos->Add (textinfo, 0, wxEXPAND);
    textinfos->Add (0, 6);

    // statistic
    wxGridSizer *statistic = new wxGridSizer (4, 0, 2);
    statistic->Add (new wxStaticText (this, wxID_ANY, _("Total lines"),
                                     wxDefaultPosition, wxSize(80, wxDefaultCoord)),
                    0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxLEFT, 4);
    text = wxString::Format (wxT("%d"), edit->GetLineCount());
    statistic->Add (new wxStaticText (this, wxID_ANY, text),
                    0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxRIGHT, 4);
    statistic->Add (new wxStaticText (this, wxID_ANY, _("Total chars"),
                                     wxDefaultPosition, wxSize(80, wxDefaultCoord)),
                    0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxLEFT, 4);
    text = wxString::Format (wxT("%d"), edit->GetTextLength());
    statistic->Add (new wxStaticText (this, wxID_ANY, text),
                    0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxRIGHT, 4);
    statistic->Add (new wxStaticText (this, wxID_ANY, _("Current line"),
                                     wxDefaultPosition, wxSize(80, wxDefaultCoord)),
                    0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxLEFT, 4);
    text = wxString::Format (wxT("%d"), edit->GetCurrentLine());
    statistic->Add (new wxStaticText (this, wxID_ANY, text),
                    0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxRIGHT, 4);
    statistic->Add (new wxStaticText (this, wxID_ANY, _("Current pos"),
                                     wxDefaultPosition, wxSize(80, wxDefaultCoord)),
                    0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxLEFT, 4);
    text = wxString::Format (wxT("%d"), edit->GetCurrentPos());
    statistic->Add (new wxStaticText (this, wxID_ANY, text),
                    0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxRIGHT, 4);

    // char/line statistics
    wxStaticBoxSizer *statistics = new wxStaticBoxSizer (
                     new wxStaticBox (this, wxID_ANY, _("Statistics")),
                     wxVERTICAL);
    statistics->Add (statistic, 0, wxEXPAND);
    statistics->Add (0, 6);

    // total pane
    wxBoxSizer *totalpane = new wxBoxSizer (wxVERTICAL);
    totalpane->Add (fullname, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10);
    totalpane->Add (0, 6);
    totalpane->Add (textinfos, 0, wxEXPAND | wxLEFT | wxRIGHT, 10);
    totalpane->Add (0, 10);
    totalpane->Add (statistics, 0, wxEXPAND | wxLEFT | wxRIGHT, 10);
    totalpane->Add (0, 6);
    wxButton *okButton = new wxButton (this, wxID_OK, _("OK"));
    okButton->SetDefault();
    totalpane->Add (okButton, 0, wxALIGN_CENTER | wxALL, 10);

    SetSizerAndFit (totalpane);

    ShowModal();
}
