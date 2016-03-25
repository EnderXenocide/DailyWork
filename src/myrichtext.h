/////////////////////////////////////////////////////////////////////////////
// Name:        richtext/richtext.h
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

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

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

#include "wx/richtext/richtextctrl.h"
#include "wx/richtext/richtextstyles.h"
#include "wx/richtext/richtextxml.h"
#include "wx/richtext/richtexthtml.h"
#include "wx/richtext/richtextformatdlg.h"
#include "wx/richtext/richtextsymboldlg.h"
#include "wx/richtext/richtextstyledlg.h"
#include "wx/richtext/richtextprint.h"


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
    
    bool ProcessEvent(wxEvent& event);

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
