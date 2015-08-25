#ifndef __GUI_H__
#define __GUI_H__


#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/intl.h>
#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/treectrl.h>
#include <wx/calctrl.h>
#include <wx/sizer.h>
#include <wx/toolbar.h>
#include <wx/richtext/richtextctrl.h>
#include <wx/statusbr.h>
#include <wx/frame.h>
#include <wx/app.h> 

#include "wx/richtext/richtextctrl.h"
#include "wx/richtext/richtextstyles.h"
#include "wx/richtext/richtextxml.h"
#include "wx/richtext/richtexthtml.h"
#include "wx/richtext/richtextformatdlg.h"
#include "wx/richtext/richtextsymboldlg.h"
#include "wx/richtext/richtextstyledlg.h"
#include "wx/richtext/richtextprint.h"
#include "wx/richtext/richtextimagedlg.h"

#include "myrichtext.h"
#include "easylogging++.h"


#ifndef wxHAS_IMAGES_IN_RESOURCES
    #include "../sample.xpm"
#endif

#include "bitmaps/smiley.xpm"
// #include "bitmaps/idea.xpm"
#include "bitmaps/zebra.xpm"

#include "bitmaps/open.xpm"
#include "bitmaps/save.xpm"
#include "bitmaps/copy.xpm"
#include "bitmaps/cut.xpm"
#include "bitmaps/paste.xpm"
#include "bitmaps/undo.xpm"
#include "bitmaps/redo.xpm"
#include "bitmaps/bold.xpm"
#include "bitmaps/italic.xpm"
#include "bitmaps/underline.xpm"

#include "bitmaps/alignleft.xpm"
#include "bitmaps/alignright.xpm"
#include "bitmaps/centre.xpm"
#include "bitmaps/font.xpm"
#include "bitmaps/indentless.xpm"
#include "bitmaps/indentmore.xpm"

///////////////////////////////////////////////////////////////////////////
/// Class MainFrame
///////////////////////////////////////////////////////////////////////////////
class MainFrame : public wxFrame 
{
public:
    wxMenuBar* m_menuBar;
    wxMenu* m_menuFile;
    wxTreeCtrl* m_treeDates;
    wxCalendarCtrl* m_calendar;
    wxToolBar* m_richTextToolBar;
    wxStatusBar* m_statusBar;
    wxToolBar* m_mainToolBar;
 
    MyRichTextCtrl* m_editor;
    
    MainFrame(const wxString& title, wxWindowID id, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_FRAME_STYLE);
    MainFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 699,413 ), long style = wxCLOSE_BOX|wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
    ~MainFrame();
 
   void OnStatusBarMessage(std::string msg);
 
protected:  
    // Virtual event handlers, overide them in your derived class
    void OnCloseFrame( wxCloseEvent& event );
    void OnTreeSelChanged( wxTreeEvent& event );
    void OnCalendarSelChanged( wxCalendarEvent& event );

    // event handlers (these functions should _not_ be virtual)
    void OnQuit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);

    void OnOpen(wxCommandEvent& event);
    void OnSave(wxCommandEvent& event);
    void OnSaveAs(wxCommandEvent& event);

    void OnBold(wxCommandEvent& event);
    void OnItalic(wxCommandEvent& event);
    void OnUnderline(wxCommandEvent& event);

    void OnStrikethrough(wxCommandEvent& event);
    void OnSuperscript(wxCommandEvent& event);
    void OnSubscript(wxCommandEvent& event);

    void OnUpdateBold(wxUpdateUIEvent& event);
    void OnUpdateItalic(wxUpdateUIEvent& event);
    void OnUpdateUnderline(wxUpdateUIEvent& event);
    void OnUpdateStrikethrough(wxUpdateUIEvent& event);
    void OnUpdateSuperscript(wxUpdateUIEvent& event);
    void OnUpdateSubscript(wxUpdateUIEvent& event);

    void OnAlignLeft(wxCommandEvent& event);
    void OnAlignCentre(wxCommandEvent& event);
    void OnAlignRight(wxCommandEvent& event);

    void OnUpdateAlignLeft(wxUpdateUIEvent& event);
    void OnUpdateAlignCentre(wxUpdateUIEvent& event);
    void OnUpdateAlignRight(wxUpdateUIEvent& event);

    void OnIndentMore(wxCommandEvent& event);
    void OnIndentLess(wxCommandEvent& event);

    void OnFont(wxCommandEvent& event);
    void OnImage(wxCommandEvent& event);
    void OnUpdateImage(wxUpdateUIEvent& event);
    void OnParagraph(wxCommandEvent& event);
    void OnFormat(wxCommandEvent& event);
    void OnUpdateFormat(wxUpdateUIEvent& event);

    void OnInsertSymbol(wxCommandEvent& event);

    void OnLineSpacingHalf(wxCommandEvent& event);
    void OnLineSpacingDouble(wxCommandEvent& event);
    void OnLineSpacingSingle(wxCommandEvent& event);

    void OnParagraphSpacingMore(wxCommandEvent& event);
    void OnParagraphSpacingLess(wxCommandEvent& event);

    void OnNumberList(wxCommandEvent& event);
    void OnBulletsAndNumbering(wxCommandEvent& event);
    void OnItemizeList(wxCommandEvent& event);
    void OnRenumberList(wxCommandEvent& event);
    void OnPromoteList(wxCommandEvent& event);
    void OnDemoteList(wxCommandEvent& event);
    void OnClearList(wxCommandEvent& event);

    void OnTableAddColumn(wxCommandEvent& event);
    void OnTableAddRow(wxCommandEvent& event);
    void OnTableDeleteColumn(wxCommandEvent& event);
    void OnTableDeleteRow(wxCommandEvent& event);
    void OnTableFocusedUpdateUI(wxUpdateUIEvent& event);
    void OnTableHasCellsUpdateUI(wxUpdateUIEvent& event);

    void OnReload(wxCommandEvent& event);

    void OnViewHTML(wxCommandEvent& event);

    void OnSwitchStyleSheets(wxCommandEvent& event);
    void OnManageStyles(wxCommandEvent& event);

    void OnInsertURL(wxCommandEvent& event);
    void OnURL(wxTextUrlEvent& event);
    void OnStyleSheetReplacing(wxRichTextEvent& event);

#if wxUSE_PRINTING_ARCHITECTURE
    void OnPrint(wxCommandEvent& event);
    void OnPreview(wxCommandEvent& event);
#endif
    void OnPageSetup(wxCommandEvent& event);

    void OnInsertImage(wxCommandEvent& event);

    void OnSetFontScale(wxCommandEvent& event);
    void OnSetDimensionScale(wxCommandEvent& event);

    // Forward command events to the current rich text control, if any
    bool ProcessEvent(wxEvent& event);

    // Write text
    void WriteInitialText();

private:
    // any class wishing to process wxWidgets events must use this macro
    wxDECLARE_EVENT_TABLE();
};

#endif //__GUI_H__