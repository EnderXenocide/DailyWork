///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 17 2015)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

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
#include <wx/calctrl.h>
#include <wx/treectrl.h>
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/stattext.h>
#include <wx/richtext/richtextctrl.h>
#include <wx/statusbr.h>
#include <wx/toolbar.h>
#include <wx/frame.h>
#include <wx/checklst.h>
#include <wx/statbox.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class MainFrameBase
///////////////////////////////////////////////////////////////////////////////
class MainFrameBase : public wxFrame 
{
	private:
	
	protected:
		wxMenuBar* m_menuBar;
		wxMenu* m_menuFile;
		wxCalendarCtrl* m_calendar;
		wxTreeCtrl* m_treeDates;
		wxButton* m_buttonGoNextAvailable;
		wxButton* m_buttonGoTomorrow;
		wxStaticText* m_staticTextCurDate;
		wxRichTextCtrl* m_editor;
		wxButton* m_buttonYesterday;
		wxButton* m_buttonGoPrevAvailable;
		wxStatusBar* m_statusBar;
		wxToolBar* m_mainToolBar;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnCloseFrame( wxCloseEvent& event ) { event.Skip(); }
		virtual void OnExitClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnCalendarDblClick( wxCalendarEvent& event ) { event.Skip(); }
		virtual void OnCalendarKillFocus( wxFocusEvent& event ) { event.Skip(); }
		virtual void OnCalendarSetFocus( wxFocusEvent& event ) { event.Skip(); }
		virtual void OnTreeSelChanged( wxTreeEvent& event ) { event.Skip(); }
		virtual void OnButtonGoNextAvailableClick( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		MainFrameBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 699,413 ), long style = wxCLOSE_BOX|wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		
		~MainFrameBase();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class DlgPreference
///////////////////////////////////////////////////////////////////////////////
class DlgPreference : public wxDialog 
{
	private:
	
	protected:
		wxCheckListBox* m_checkListExcludeDays;
		wxStaticText* m_staticText2;
		wxStdDialogButtonSizer* m_sdbSizer1;
		wxButton* m_sdbSizer1OK;
		wxButton* m_sdbSizer1Cancel;
	
	public:
		
		DlgPreference( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Preferences"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 420,309 ), long style = wxDEFAULT_DIALOG_STYLE ); 
		~DlgPreference();
	
};

#endif //__GUI_H__
