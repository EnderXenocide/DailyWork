/////////////////////////////////////////////////////////////////////////////
// Name:        samples/richtext/richtext.cpp
// Purpose:     wxWidgets rich text editor sample
// Author:      Julian Smart
// Modified by:
// Created:     2005-10-02
// Copyright:   (c) Julian Smart
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

// ============================================================================
// declarations
// ============================================================================

// ----------------------------------------------------------------------------
// headers
// ----------------------------------------------------------------------------


// for all others, include the necessary headers (this file is usually all you
// need because it includes almost all "standard" wxWidgets headers)
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include "wx/fontdlg.h"
#include "wx/splitter.h"
#include "wx/sstream.h"
#include "wx/html/htmlwin.h"
#include "wx/stopwatch.h"
#include "wx/sysopt.h"

#if wxUSE_FILESYSTEM
#include "wx/filesys.h"
#include "wx/fs_mem.h"
#endif

#if wxUSE_HELP
#include "wx/cshelp.h"
#endif

#ifndef wxHAS_IMAGES_IN_RESOURCES
    #include "../sample.xpm"
#endif

#include "bitmaps/smiley.xpm"
// #include "bitmaps/idea.xpm"
#include "bitmaps/zebra.xpm"

#include "bitmaps/open.xpm"
#include "bitmaps/save.xpm"
#include "bitmaps/copy.xpm"
#include "bitmaps/cut.xpm"
#include "bitmaps/paste.xpm"
#include "bitmaps/undo.xpm"
#include "bitmaps/redo.xpm"
#include "bitmaps/bold.xpm"
#include "bitmaps/italic.xpm"
#include "bitmaps/underline.xpm"

#include "bitmaps/alignleft.xpm"
#include "bitmaps/alignright.xpm"
#include "bitmaps/centre.xpm"
#include "bitmaps/font.xpm"
#include "bitmaps/indentless.xpm"
#include "bitmaps/indentmore.xpm"

#include "wx/richtext/richtextctrl.h"
#include "wx/richtext/richtextstyles.h"
#include "wx/richtext/richtextxml.h"
#include "wx/richtext/richtexthtml.h"
#include "wx/richtext/richtextformatdlg.h"
#include "wx/richtext/richtextsymboldlg.h"
#include "wx/richtext/richtextstyledlg.h"
#include "wx/richtext/richtextprint.h"
#include "wx/richtext/richtextimagedlg.h"

// A custom field type
class wxRichTextFieldTypePropertiesTest: public wxRichTextFieldTypeStandard
{
public:
    wxRichTextFieldTypePropertiesTest(const wxString& name, const wxString& label, int displayStyle = wxRICHTEXT_FIELD_STYLE_RECTANGLE):
        wxRichTextFieldTypeStandard(name, label, displayStyle)
    {
    }
    wxRichTextFieldTypePropertiesTest(const wxString& name, const wxBitmap& bitmap, int displayStyle = wxRICHTEXT_FIELD_STYLE_RECTANGLE):
        wxRichTextFieldTypeStandard(name, bitmap, displayStyle)
    {
    }

    virtual bool CanEditProperties(wxRichTextField* WXUNUSED(obj)) const { return true; }
    virtual bool EditProperties(wxRichTextField* WXUNUSED(obj), wxWindow* WXUNUSED(parent), wxRichTextBuffer* WXUNUSED(buffer))
    {
        wxString label = GetLabel();
        wxMessageBox(wxString::Format(wxT("Editing %s"), label.c_str()));
        return true;
    }

    virtual wxString GetPropertiesMenuLabel(wxRichTextField* WXUNUSED(obj)) const
    {
        return GetLabel();
    }
};

// A custom composite field type
class wxRichTextFieldTypeCompositeTest: public wxRichTextFieldTypePropertiesTest
{
public:
    wxRichTextFieldTypeCompositeTest(const wxString& name, const wxString& label):
        wxRichTextFieldTypePropertiesTest(name, label, wxRICHTEXT_FIELD_STYLE_COMPOSITE)
    {
    }

    virtual bool UpdateField(wxRichTextBuffer* buffer, wxRichTextField* obj)
    {
        if (buffer)
        {
            wxRichTextAttr attr(buffer->GetAttributes());
            attr.GetTextBoxAttr().Reset();
            attr.SetParagraphSpacingAfter(0);
            attr.SetLineSpacing(10);
            obj->SetAttributes(attr);
        }
        obj->GetChildren().Clear();
        wxRichTextParagraph* para = new wxRichTextParagraph;
        wxRichTextPlainText* text = new wxRichTextPlainText(GetLabel());
        para->AppendChild(text);
        obj->AppendChild(para);
        return true;
   }
};

// ----------------------------------------------------------------------------
// resources
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// private classes
// ----------------------------------------------------------------------------

// Define a new application type, each program should derive a class from wxApp
class MyRichTextCtrl: public wxRichTextCtrl
{
public:
    MyRichTextCtrl( wxWindow* parent, wxWindowID id = -1, const wxString& value = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize,
        long style = wxRE_MULTILINE, const wxValidator& validator = wxDefaultValidator, const wxString& name = wxTextCtrlNameStr):
      wxRichTextCtrl(parent, id, value, pos, size, style, validator, name)
    {
        m_lockId = 0;
        m_locked = false;
    }

    void SetLockId(long id) { m_lockId = id; }
    long GetLockId() const { return m_lockId; }

    void BeginLock() { m_lockId ++; m_locked = true; }
    void EndLock() { m_locked = false; }
    bool IsLocked() const { return m_locked; }

    static void SetEnhancedDrawingHandler();

    /**
        Prepares the content just before insertion (or after buffer reset). Called by the same function in wxRichTextBuffer.
        Currently is only called if undo mode is on.
    */
    virtual void PrepareContent(wxRichTextParagraphLayoutBox& container);

    /**
        Can we delete this range?
        Sends an event to the control.
    */
    virtual bool CanDeleteRange(wxRichTextParagraphLayoutBox& container, const wxRichTextRange& range) const;

    /**
        Can we insert content at this position?
        Sends an event to the control.
    */
    virtual bool CanInsertContent(wxRichTextParagraphLayoutBox& container, long pos) const;

    /**
        Finds a table,  either selected or near the cursor
    */
    wxRichTextTable* FindTable() const;

    /**
        Helper for FindTable()
    */
    wxRichTextObject* FindCurrentPosition() const;

    long    m_lockId;
    bool    m_locked;
};



// ----------------------------------------------------------------------------
// constants
// ----------------------------------------------------------------------------

// IDs for the controls and the menu commands
enum
{
    // menu items
    ID_Quit = wxID_EXIT,
    ID_About = wxID_ABOUT,

    ID_FORMAT_BOLD = 100,
    ID_FORMAT_ITALIC,
    ID_FORMAT_UNDERLINE,
    ID_FORMAT_STRIKETHROUGH,
    ID_FORMAT_SUPERSCRIPT,
    ID_FORMAT_SUBSCRIPT,
    ID_FORMAT_FONT,
    ID_FORMAT_IMAGE,
    ID_FORMAT_PARAGRAPH,
    ID_FORMAT_CONTENT,

    ID_RELOAD,

    ID_INSERT_SYMBOL,
    ID_INSERT_URL,
    ID_INSERT_IMAGE,

    ID_FORMAT_ALIGN_LEFT,
    ID_FORMAT_ALIGN_CENTRE,
    ID_FORMAT_ALIGN_RIGHT,

    ID_FORMAT_INDENT_MORE,
    ID_FORMAT_INDENT_LESS,

    ID_FORMAT_PARAGRAPH_SPACING_MORE,
    ID_FORMAT_PARAGRAPH_SPACING_LESS,

    ID_FORMAT_LINE_SPACING_HALF,
    ID_FORMAT_LINE_SPACING_DOUBLE,
    ID_FORMAT_LINE_SPACING_SINGLE,

    ID_FORMAT_NUMBER_LIST,
    ID_FORMAT_BULLETS_AND_NUMBERING,
    ID_FORMAT_ITEMIZE_LIST,
    ID_FORMAT_RENUMBER_LIST,
    ID_FORMAT_PROMOTE_LIST,
    ID_FORMAT_DEMOTE_LIST,
    ID_FORMAT_CLEAR_LIST,

    ID_TABLE_ADD_COLUMN,
    ID_TABLE_ADD_ROW,
    ID_TABLE_DELETE_COLUMN,
    ID_TABLE_DELETE_ROW,

    ID_SET_FONT_SCALE,
    ID_SET_DIMENSION_SCALE,

    ID_VIEW_HTML,
    ID_SWITCH_STYLE_SHEETS,
    ID_MANAGE_STYLES,

    ID_PRINT,
    ID_PREVIEW,
    ID_PAGE_SETUP,

    ID_RICHTEXT_CTRL,
    ID_RICHTEXT_STYLE_LIST,
    ID_RICHTEXT_STYLE_COMBO
};

// ============================================================================
// implementation
// ============================================================================

// ----------------------------------------------------------------------------
// the application class
// ----------------------------------------------------------------------------



// ----------------------------------------------------------------------------
// main frame
// ----------------------------------------------------------------------------



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
