/*********************************************************************
 * Name:      	main.h
 * Purpose:   	Declares simple wxWidgets application with GUI
 * 				created using wxFormBuilder.
 * Author:    
 * Created:   
 * Copyright: 
 * License:   	wxWidgets license (www.wxwidgets.org)
 * 
 * Notes:		Note that all GUI creation code is declared in
 * 				gui.h source file which is generated by wxFormBuilder.
 *********************************************************************/

#ifndef __main__
#define __main__


#include "dailyworkparser.h"
#include "currentdates.h"
#include "gui2.h"

// main wxWidgets header file
#include <wx/wx.h>
#include <wx/string.h>
#include <wx/treectrl.h>
#include <wx/msgdlg.h>

#if wxUSE_HELP
#include <wx/cshelp.h>
#endif

#if USE_RICH_EDIT
#include <wx/richtext/richtextctrl.h>
#include <wx/richtext/richtextstyles.h>
#include <wx/richtext/richtextxml.h>
#include <wx/richtext/richtexthtml.h>
#include <wx/richtext/richtextformatdlg.h>
#include <wx/richtext/richtextsymboldlg.h>
#include <wx/richtext/richtextstyledlg.h>
#include <wx/richtext/richtextprint.h>
#include <wx/richtext/richtextimagedlg.h>
#endif

////////////////////////////////////////////////////////////////////////////////
// application class declaration 
////////////////////////////////////////////////////////////////////////////////

class MainApp : public wxApp
{
public:
     MainFrame* frame; 
     
     MainApp() { m_language = wxLANGUAGE_UNKNOWN; };

    virtual bool OnInit();
    virtual int OnExit();
    
    void CreateStyles();
    void InitDailyWorkParser();
    void LoadFavoritesInComboBox();
    void LoadDailyWorkInTree();
    MainApp& SetHierarchicalTree( bool hierarchy){this->hierarchicalTree = hierarchy; return *this; }
    bool IsHierarchicalTree() const{ return hierarchicalTree; }
#if USE_RICH_EDIT
    wxRichTextStyleSheet* GetStyleSheet() const { return m_styleSheet; } 
#endif    
    int AddDateToTree(const wxDateTime& date, bool selectItem = false); // todo wxTreeCtrl& tree instead
    wxTreeItemId AddItem(wxTreeItemId parent, wxString text, wxDateTime date, bool setDataEmpty);
    void SetCurrentDate(const wxDateTime &date);
    void SetCurrentDateFromTreeDatesSelection();
    void SetCurrentDateFromTreeSearchSelection();  
    void SetPrevDateAsCurrentDate();
    void SetNextDateAsCurrentDate();  
    void AddTomorrowToTree();
    void AddYesterdayToTree();    
    wxDateTime GetDateFromTreeDatesSelection();
    wxString GetCurrentDateWork();
    void DeleteDateSelected();
    bool DeleteItemData(wxTreeItemId itemId);
    bool IsModified() const { return dwparser.IsModified(); }
    int Save() ;
    int SaveAs(wxString filename) ;
    int AddToFavorites(wxString text);
    int DeleteSelectedFavorite();
    void UpdateCurrentWork();
    int CountDates();
    int SearchInDates(wxString text);
    void SelectFirstTreeDatesItem();
private:
    wxDateTime GetDateFromTreeSelection(wxTreeCtrl* tree);
    wxDateTime GetDateFromItem(wxTreeCtrl* tree, wxTreeItemId itemId);
    void DeleteDate(wxDateTime date);
    CurrentDates currentDates;
    bool hierarchicalTree;
    wxLanguage m_language;  // language specified by user
    wxLocale* m_locale;  // locale we'll be using
    DailyWorkParser dwparser; 
    ExcludedDays excludedDays;
    void InitLanguageSupport();
     wxTreeItemId AddItemData(wxTreeItemId itemId, wxDateTime date, bool setDataEmpty);
    void SelectDateInTree(const wxDateTime &date);
    wxTreeItemId SelectDateInChild(wxTreeItemId parent, wxDateTime date);
    wxTreeItemId AddBranchHierarchy(wxTreeItemId rootId, wxDateTime date);
    wxTreeItemId AddBranchSimple(wxTreeItemId rootId, wxDateTime date);
    void GetDatesAround(const wxDateTime &date, wxDateTime &prevDate, wxDateTime &nextDate);
    void SetButtonsState();
 
 #if USE_RICH_EDIT   
    wxRichTextStyleSheet*   m_styleSheet;
    void InitRichText(); 
#endif 

};

// declare global static function wxGetApp()
DECLARE_APP(MainApp)

#endif //__main__
