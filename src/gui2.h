#ifndef __GUI_H__
#define __GUI_H__

#define USE_RICH_EDIT false

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
//#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/treectrl.h>
#include <wx/calctrl.h>
#include <wx/sizer.h>
#include <wx/toolbar.h>
#include <wx/statusbr.h>
#include <wx/frame.h>
#include <wx/app.h>
#include <wx/combobox.h>
#include <wx/sysopt.h>
#include <wx/splitter.h>
#include <wx/checklst.h>
//#include <wx/srchctrl.h>
#include <wx/stattext.h>

#include "easylogging++.h"

#include "excludeddays.h"

#if USE_RICH_EDIT
#include <wx/richtext/richtextctrl.h>
#include "wx/richtext/richtextstyles.h"
#include "wx/richtext/richtextxml.h"
#include "wx/richtext/richtexthtml.h"
#include "wx/richtext/richtextformatdlg.h"
#include "wx/richtext/richtextsymboldlg.h"
#include "wx/richtext/richtextstyledlg.h"
#include "wx/richtext/richtextprint.h"
#include "wx/richtext/richtextimagedlg.h"
#include "myrichtext.h"
#else
#include "mystyledtext.h"
#endif // USE_RICH_EDIT

#ifndef wxHAS_IMAGES_IN_RESOURCES
    #include "../sample.xpm"
#endif

#if USE_RICH_EDIT
#include "bitmaps/smiley.xpm"
// #include "bitmaps/idea.xpm"
#include "bitmaps/zebra.xpm"
#endif  // USE_RICH_EDIT

#include "bitmaps/reload.xpm"
#include "bitmaps/delete.xpm"

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

#include "bitmaps/bookadd.xpm"
#include "bitmaps/bookdelete.xpm"
#include "bitmaps/bookedit.xpm"
#include "bitmaps/bookgo.xpm"


///////////////////////////////////////////////////////////////////////////
/// Class MainFrame
///////////////////////////////////////////////////////////////////////////////
class MainFrame : public wxFrame 
{
public:
    wxMenuBar* m_menuBar;
    wxTreeCtrl* m_treeDates;
    wxCalendarCtrl* m_calendar;
    wxStatusBar* m_statusBar;
    wxToolBar* m_mainToolBar;
    wxComboBox* m_comboBoxFavorite;
 
    wxMenu* m_editMenu;
    wxSplitterWindow *m_splitterEditorSearch;
    wxPanel *m_panelSearch, *m_panelEditor;
    
	wxStaticText* m_textCurDate;
    wxButton* m_buttonAddTomorrow;
    wxButton* m_buttonAddYesterday;
    wxButton* m_buttonGoNextAvailable;
    wxButton* m_buttonGoPrevAvailable;
    
    wxTextCtrl* m_textSearch; //wxSearchCtrl ? pb icon too big
    wxTreeCtrl* m_treeSearch;
 	wxStaticText* m_textSearchStat;
 
 #if USE_RICH_EDIT
    MyRichTextCtrl* m_editor;
#else
    MyStyledTextCtrl* m_editor;      
#endif
    
    MainFrame(const wxString& title, wxWindowID id, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_FRAME_STYLE);
   // MainFrame(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 699,413 ), long style = wxCLOSE_BOX|wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL);
    ~MainFrame();
 
    void OnStatusBarMessage(wxString msg);
    void OnDialogMessage(wxString msg);
    void EnableShowHirerarchicalTree(bool hiearchy);
    void SetText(wxString texte);    
    void ConnectSelectionEvents();
    void DisconnectSelectionEvents();
protected:  
    // event handlers (these functions should _not_ be virtual)
    void OnCloseFrame(wxCloseEvent& event);
    void OnTreeSelChanging(wxTreeEvent& event);
    void OnTreeSelChanged(wxTreeEvent& event);
    void OnTreeRightClick(wxTreeEvent& event);
    void OnCalendarSelChanged(wxCalendarEvent& event);
    void OnCalendarDblClick(wxCalendarEvent& event);
    void OnCalendarSetFocus(wxFocusEvent& event);
	void OnCalendarKillFocus(wxFocusEvent& event);
    
    void OnFocusComboFavorite(wxCommandEvent& event);
    //void OnComboFavoriteTextEnter(wxCommandEvent& event);
    //void OnComboFavoriteUpdate(wxCommandEvent& event);

    void OnShowHirerarchicalTree(wxCommandEvent& event);

	void OnDeleteDate(wxCommandEvent& event);
    void OnQuit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnStayOnTop(wxCommandEvent& event);

    void OnAddFavorite(wxCommandEvent& event);
    void OnGoFavorite(wxCommandEvent& event);
    void OnDeleteFavorite(wxCommandEvent& event);
    void OnManageFavorite(wxCommandEvent& event);
    void OnUpdateAddFavorite(wxUpdateUIEvent& event);
    void OnUpdateGoFavorite(wxUpdateUIEvent& event);
    void OnUpdateDeleteFavorite(wxUpdateUIEvent& event);

	void OnButtonGoNextAvailableClick(wxCommandEvent& event);
	void OnButtonGoPrevAvailableClick(wxCommandEvent& event);
	void OnButtonAddTomorrowClick(wxCommandEvent& event);
	void OnButtonAddYesterdayClick(wxCommandEvent& event);

    void OnOpen(wxCommandEvent& event);
    void OnSave(wxCommandEvent& event);
    void OnSaveAs(wxCommandEvent& event);
    
    void OnOptions(wxCommandEvent& event);
    
    void OnReload(wxCommandEvent& event);
    
    void OnTextSearchEnter(wxCommandEvent& event);  
    void OnTreeSearchSelChanged(wxTreeEvent& event);
 
    void OnShowPanelSearch(wxCommandEvent& event);
    void OnHidePanelSearch(wxSplitterEvent& event); 
  
 #if USE_RICH_EDIT
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

    void OnViewHTML(wxCommandEvent& event);

    void OnSwitchStyleSheets(wxCommandEvent& event);
    void OnManageStyles(wxCommandEvent& event);

    void OnInsertURL(wxCommandEvent& event);
    void OnURL(wxTextUrlEvent& event);
    void OnStyleSheetReplacing(wxRichTextEvent& event);
    
    void OnInsertImage(wxCommandEvent& event);
    
    void OnSetFontScale(wxCommandEvent& event);
    void OnSetDimensionScale(wxCommandEvent& event);    
 #else
    void OnUpdateUndo(wxUpdateUIEvent& event);
    void OnUpdateRedo(wxUpdateUIEvent& event);    
 #endif
     
private:
    const int sashPositionSearchEditor = -225; //todo save position before hide ?
    // Write text
#if USE_RICH_EDIT
    void WriteInitialText(); // ce n'est pas utile 
#endif   
    void ConnectEvents();
    void CreateEditor(wxWindow *parent);
    void CreateMenu();
    void CreateMainToolBar();    
};

///////////////////////////////////////////////////////////////////////////////
/// Class DlgOptions
///////////////////////////////////////////////////////////////////////////////
class DlgOptions : public wxDialog 
{
	private:

	protected:
		wxCheckListBox* m_checkListExcludeDays;
		wxButton* m_sdbSizerOK;
		wxButton* m_sdbSizerCancel;
	
	public:
		
        DlgOptions( wxWindow* parent, ExcludedDays ed); 
        //DlgOptions( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Préférences"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 420,309 ), long style = wxDEFAULT_DIALOG_STYLE 
		~DlgOptions();
        ExcludedDays GetExcludedDays();	
        void ExcludedDaysToIHM(ExcludedDays excludedDays);
};

#endif //__GUI_H__
