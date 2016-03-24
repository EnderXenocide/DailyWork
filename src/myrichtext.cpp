/////////////////////////////////////////////////////////////////////////////
// Name:        richtext.h
// Purpose:     wxWidgets rich text editor sample
// Author:      Julian Smart
// Modified by:
// Created:     2005-10-02
// Copyright:   (c) Julian Smart
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#include "myrichtext.h"

// Forward command events to the current rich text control, if any
bool MyRichTextCtrl::ProcessEvent(wxEvent& event)
{
    static wxEvent* s_lastEvent = NULL;
   
    //prevent infinite recursion
    if (&event == s_lastEvent )
        return false;
        
    if ( event.IsCommandEvent() && 
        !event.IsKindOf(CLASSINFO(wxChildFocusEvent)) &&
        !event.IsKindOf(CLASSINFO(wxContextMenuEvent))  )
    {
       s_lastEvent = & event;

        wxWindow* focusWin = wxFindFocusDescendant(this);
        bool success = false;
        if (focusWin)
            success = focusWin->GetEventHandler()->ProcessEvent(event);
        
        if (!success)
            success = wxRichTextCtrl::ProcessEvent(event);
        
        s_lastEvent = NULL;    

        return success;
    }   
    else {
        return wxRichTextCtrl::ProcessEvent(event);
    }
}

void MyRichTextCtrl::PrepareContent(wxRichTextParagraphLayoutBox& container)
{
    if (IsLocked())
    {
        // Lock all content that's about to be added to the control
        wxRichTextObjectList::compatibility_iterator node = container.GetChildren().GetFirst();
        while (node)
        {
            wxRichTextParagraph* para = wxDynamicCast(node->GetData(), wxRichTextParagraph);
            if (para)
            {
                wxRichTextObjectList::compatibility_iterator childNode = para->GetChildren().GetFirst();
                while (childNode)
                {
                    wxRichTextObject* obj = childNode->GetData();
                    obj->GetProperties().SetProperty(wxT("Lock"), m_lockId);

                    childNode = childNode->GetNext();
                }
            }
            node = node->GetNext();
        }
    }
}

bool MyRichTextCtrl::CanDeleteRange(wxRichTextParagraphLayoutBox& container, const wxRichTextRange& range) const
{
    long i;
    for (i = range.GetStart(); i < range.GetEnd(); i++)
    {
        wxRichTextObject* obj = container.GetLeafObjectAtPosition(i);
        if (obj && obj->GetProperties().HasProperty(wxT("Lock")))
        {
            return false;
        }
    }
    return true;
}

bool MyRichTextCtrl::CanInsertContent(wxRichTextParagraphLayoutBox& container, long pos) const
{
    wxRichTextObject* child1 = container.GetLeafObjectAtPosition(pos);
    wxRichTextObject* child2 = container.GetLeafObjectAtPosition(pos-1);

    long lock1 = -1, lock2 = -1;

    if (child1 && child1->GetProperties().HasProperty(wxT("Lock")))
        lock1 = child1->GetProperties().GetPropertyLong(wxT("Lock"));
    if (child2 && child2->GetProperties().HasProperty(wxT("Lock")))
        lock2 = child2->GetProperties().GetPropertyLong(wxT("Lock"));

    if (lock1 != -1 && lock1 == lock2)
        return false;

    // Don't allow insertion before a locked object if it's at the beginning of the buffer.
    if (pos == 0 && lock1 != -1)
        return false;

    return true;
}


class wxRichTextEnhancedDrawingHandler: public wxRichTextDrawingHandler
{
public:
    wxRichTextEnhancedDrawingHandler()
    {
        SetName(wxT("enhanceddrawing"));
        m_lockBackgroundColour = wxColour(220, 220, 220);
    }

    /**
        Returns @true if this object has virtual attributes that we can provide.
    */
    virtual bool HasVirtualAttributes(wxRichTextObject* obj) const;

    /**
        Provides virtual attributes that we can provide.
    */
    virtual bool GetVirtualAttributes(wxRichTextAttr& attr, wxRichTextObject* obj) const;

    /**
        Gets the count for mixed virtual attributes for individual positions within the object.
        For example, individual characters within a text object may require special highlighting.
    */
    virtual int GetVirtualSubobjectAttributesCount(wxRichTextObject* WXUNUSED(obj)) const { return 0; }

    /**
        Gets the mixed virtual attributes for individual positions within the object.
        For example, individual characters within a text object may require special highlighting.
        Returns the number of virtual attributes found.
    */
    virtual int GetVirtualSubobjectAttributes(wxRichTextObject* WXUNUSED(obj), wxArrayInt& WXUNUSED(positions), wxRichTextAttrArray& WXUNUSED(attributes)) const  { return 0; }

    /**
        Do we have virtual text for this object? Virtual text allows an application
        to replace characters in an object for editing and display purposes, for example
        for highlighting special characters.
    */
    virtual bool HasVirtualText(const wxRichTextPlainText* WXUNUSED(obj)) const { return false; }

    /**
        Gets the virtual text for this object.
    */
    virtual bool GetVirtualText(const wxRichTextPlainText* WXUNUSED(obj), wxString& WXUNUSED(text)) const { return false; }

    wxColour    m_lockBackgroundColour;
};

bool wxRichTextEnhancedDrawingHandler::HasVirtualAttributes(wxRichTextObject* obj) const
{
    return obj->GetProperties().HasProperty(wxT("Lock"));
}

bool wxRichTextEnhancedDrawingHandler::GetVirtualAttributes(wxRichTextAttr& attr, wxRichTextObject* obj) const
{
    if (obj->GetProperties().HasProperty(wxT("Lock")))
    {
        attr.SetBackgroundColour(m_lockBackgroundColour);
        return true;
    }
    return false;
}

void MyRichTextCtrl::SetEnhancedDrawingHandler()
{
    wxRichTextBuffer::AddDrawingHandler(new wxRichTextEnhancedDrawingHandler);
}

wxRichTextObject* MyRichTextCtrl::FindCurrentPosition() const
{
    long position = -1;

    if (HasSelection())  // First see if there's a selection
    {
        wxRichTextRange range = GetSelectionRange();
        if (range.ToInternal().GetLength() == 1)
        {
            position = range.GetStart();
        }
    }
    if (position == -1)  // Failing that, near cursor
    {
        position = GetAdjustedCaretPosition(GetCaretPosition());
    }


    wxRichTextObject* obj = GetFocusObject()->GetLeafObjectAtPosition(position);

    return obj;
}

wxRichTextTable* MyRichTextCtrl::FindTable() const
{
    wxRichTextObject* obj = FindCurrentPosition();

    // It could be a table or a cell (or neither)
    wxRichTextTable* table = wxDynamicCast(obj, wxRichTextTable);
    if (table)
    {
        return table;
    }

    while (obj)
    {
        obj = obj->GetParent();
        wxRichTextTable* table = wxDynamicCast(obj, wxRichTextTable);
        if (table)
        {
            return table;
        }
    }

    return NULL;
}
