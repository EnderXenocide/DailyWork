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
#include "gui2.h"

// main wxWidgets header file
#include <wx/wx.h>


#if wxUSE_HELP
#include "wx/cshelp.h"
#endif

#include "wx/richtext/richtextctrl.h"
#include "wx/richtext/richtextstyles.h"
#include "wx/richtext/richtextxml.h"
#include "wx/richtext/richtexthtml.h"
#include "wx/richtext/richtextformatdlg.h"
#include "wx/richtext/richtextsymboldlg.h"
#include "wx/richtext/richtextstyledlg.h"
#include "wx/richtext/richtextprint.h"
#include "wx/richtext/richtextimagedlg.h"
////////////////////////////////////////////////////////////////////////////////
// application class declaration 
////////////////////////////////////////////////////////////////////////////////

class MainApp : public wxApp
{
public:
     MainFrame* frame; 

    virtual bool OnInit();
    virtual int OnExit();
    void CreateStyles();
    void InitDailyWorkParser();
    void LoadDailyWorkInTree();
    MainApp& SetHierarchicalTree( bool hierarchy){this->hierarchicalTree = hierarchy; return *this; }
    bool IsHierarchicalTree() const{ return hierarchicalTree; }
    wxRichTextStyleSheet* GetStyleSheet() const { return m_styleSheet; } 
#if wxUSE_PRINTING_ARCHITECTURE
    wxRichTextPrinting* GetPrinting() const { return m_printing; }
#endif   
    int AddDateToTree(wxDateTime& date, bool selectItem = false); // todo wxTreeCtrl& tree instead
    wxTreeItemId AddItem(wxTreeItemId parent, wxString text);
    wxTreeItemId FindDateInTree(wxDateTime date);
    wxTreeItemId FindTextInTree(wxTreeItemId parent, wxString text);
    void SetWorkFromTreeSelection(wxString text);
    std::string GetWorkFromTreeSelection();
    void DeleteDateSelected();
    bool DeleteItemData(wxTreeItemId itemId);
    bool IsModified() const { return dwparser.IsModified(); }
    int Save() ;
    int SaveAs(wxString filename) ;
private:
    bool hierarchicalTree;
    wxRichTextStyleSheet*   m_styleSheet;
    DailyWorkParser dwparser; 
#if wxUSE_PRINTING_ARCHITECTURE
    wxRichTextPrinting*     m_printing;
#endif      
    void InitRichText(); 
    wxTreeItemId LoadBranchHierarchy(wxTreeItemId rootId, wxDateTime date);
    wxTreeItemId LoadBranchSimple(wxTreeItemId rootId, wxDateTime date);
};

// declare global static function wxGetApp()
DECLARE_APP(MainApp)

#endif //__main__
