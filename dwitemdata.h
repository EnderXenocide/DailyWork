#ifndef DWITEMDATA_H
#define DWITEMDATA_H

#include <wx/treectrl.h>
#include <rapidjson/document.h>

class DWItemData : public wxTreeItemData
{
public:
    DWItemData (rapidjson::Value const & value) : wxTreeItemData() {m_value = (rapidjson::Value*) &value; };
    ~DWItemData() {};
    rapidjson::Value& GetValue() const { return *m_value; };   
private:
    rapidjson::Value* m_value; // pair date/texte
};

#endif // DWITEMDATA_H
