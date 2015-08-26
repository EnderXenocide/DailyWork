#ifndef DWITEMDATA_H
#define DWITEMDATA_H

#include <wx/treectrl.h>

class DWItemData : public wxTreeItemData
{
public:
    DWItemData (const wxString desc ) : wxTreeItemData(), m_desc(desc) {};
    ~DWItemData() {};
    const wxString& GetDesc() const { return m_desc; };   
private:
    wxString m_desc;
};

#endif // DWITEMDATA_H
