#ifndef DWITEMDATA_H
#define DWITEMDATA_H

#include <wx/treectrl.h>
#include <rapidjson/document.h>

class DWItemData : public wxTreeItemData
{
public:
    DWItemData (const wxDateTime& date, bool empty) : wxTreeItemData() 
    {
        m_date = date; 
        m_empty = empty;
    };
    ~DWItemData() {};
    wxDateTime GetDate() const { return m_date; };   
    bool IsEmpty() const { return m_empty; };   
private:
    wxDateTime m_date; 
    bool m_empty;
};

#endif // DWITEMDATA_H
