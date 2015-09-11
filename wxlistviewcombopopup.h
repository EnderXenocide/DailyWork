#include <wx/combo.h>
#include <wx/listctrl.h>

class wxListViewComboPopup : public wxListView, public wxComboPopup
{
public:
   // Initialize member variables
    virtual void Init()
    {
        m_value = -1;
        m_itemHere = -1; // hot item in list
    }

    // Create popup control
    virtual bool Create(wxWindow* parent)
    {
        return wxListView::Create(parent,1,
                                  wxPoint(0,0),wxDefaultSize,
                                  wxLC_LIST|wxLC_SINGLE_SEL|
                                  wxLC_SORT_ASCENDING|wxSIMPLE_BORDER);
    }

    // Return pointer to the created control
    virtual wxWindow *GetControl() { return this; }

    // Translate string into a list selection
    virtual void SetStringValue(const wxString& s)
    {
        int n = wxListView::FindItem(-1,s);
        if ( n >= 0 && n < wxListView::GetItemCount() )
            wxListView::Select(n);
    }

    // Get list selection as a string
    virtual wxString GetStringValue() const
    {
        if ( m_value >= 0 )
            return wxListView::GetItemText(m_value);
        return wxEmptyString;
    }

    // Do mouse hot-tracking (which is typical in list popups)
    void OnMouseMove(wxMouseEvent& event)
    {
        // Move selection to cursor if it is inside the popup
        int resFlags;
        int itemHere = HitTest(event.GetPosition(),resFlags);
        if ( itemHere >= 0 ) {
            wxListView::Select(itemHere,true);
            m_itemHere = itemHere;
        }
        event.Skip();
    }

    // On mouse left up, set the value and close the popup
    void OnMouseClick(wxMouseEvent& event)
    {
        m_value =  m_itemHere; //wxListView::GetFirstSelected(); //
        // TODO: Send event as well
        Dismiss();
    }

protected:
    int             m_itemHere; // hot item in popup
    int             m_value; // current item index
};

//        BEGIN_EVENT_TABLE(wxListViewComboPopup, wxListView)
//    EVT_MOTION(wxListViewComboPopup::OnMouseMove)
//    EVT_LEFT_UP(wxListViewComboPopup::OnMouseClick)
//END_EVENT_TABLE()