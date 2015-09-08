#ifndef DWITEMDATA_H
#define DWITEMDATA_H

#include <wx/treectrl.h>
#include <rapidjson/document.h>

class DWItemData : public wxTreeItemData
{
public:
    DWItemData (const wxDateTime& date) : wxTreeItemData() {m_value = date;};
    ~DWItemData() {};
    wxDateTime GetValue() const { return m_value; };   
private:
    wxDateTime m_value; 
};

#endif // DWITEMDATA_H
