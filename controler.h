#ifndef CONTROLER_H
#define CONTROLER_H
#include <wx/string.h>
#include <wx/treectrl.h>

#include "dailyworkparser.h"
#include "currentdates.h"
#include "gui2.h"

class Controler
{
public:
    Controler();
    ~Controler();
    SetFrame(MainFrame* frame) {this->frame = frame;};
    void LoadFavoritesInComboBox();
    void LoadDailyWorkInTree();    
private
    MainFrame* frame;
    CurrentDates currentDates;
    DailyWorkParser dwparser; 
    ExcludedDays excludedDays;
    bool hierarchicalTree;
    int AddDateToTree(const wxDateTime& date, bool selectItem = false); // todo wxTreeCtrl& tree instead
    wxTreeItemId AddBranchHierarchy(wxTreeItemId rootId, wxDateTime date);
    wxTreeItemId AddBranchSimple(wxTreeItemId rootId, wxDateTime date);
    wxTreeItemId AddItem(wxTreeItemId parent, wxString text, wxDateTime date, bool setDataEmpty);
    wxTreeItemId AddItemData(wxTreeItemId itemId, wxDateTime date, bool setDataEmpty);
};

#endif // CONTROLER_H
