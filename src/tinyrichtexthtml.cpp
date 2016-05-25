/////////////////////////////////////////////////////////////////////////////
// Original  file
// Name:        src/richtext/richtexthtml.cpp
// Purpose:     HTML I/O for wxRichTextCtrl
// Author:      Julian Smart
// Modified by:
// Created:     2005-09-30
// Copyright:   (c) Julian Smart
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

// For compilers that support precompilation, includes "wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#if wxUSE_RICHTEXT

#include "tinyrichtexthtml.h"
#include "wx/richtext/richtextstyles.h"

#ifndef WX_PRECOMP
#endif

#include "wx/filename.h"
#include "wx/wfstream.h"
#include "wx/txtstrm.h"

#if wxUSE_FILESYSTEM
#include "wx/filesys.h"
#include "wx/fs_mem.h"
#endif

wxIMPLEMENT_DYNAMIC_CLASS(TinyRichTextHTMLHandler, wxRichTextFileHandler);


TinyRichTextHTMLHandler::TinyRichTextHTMLHandler(const wxString& name, const wxString& ext, int type)
    : wxRichTextFileHandler(name, ext, type), m_buffer(NULL), m_font(false), m_inTable(false)
{
    m_fontSizeMapping.Add(8);
    m_fontSizeMapping.Add(10);
    m_fontSizeMapping.Add(13);
    m_fontSizeMapping.Add(17);
    m_fontSizeMapping.Add(22);
    m_fontSizeMapping.Add(30);
    m_fontSizeMapping.Add(100);
}

/// Can we handle this filename (if using files)? By default, checks the extension.
bool TinyRichTextHTMLHandler::CanHandle(const wxString& filename) const
{
    wxString path, file, ext;
    wxFileName::SplitPath(filename, & path, & file, & ext);

    return (ext.Lower() == wxT("html") || ext.Lower() == wxT("htm"));
}


#if wxUSE_STREAMS
bool TinyRichTextHTMLHandler::DoLoadFile(wxRichTextBuffer *WXUNUSED(buffer), wxInputStream& WXUNUSED(stream))
{
    return true;
}
/*
 * We need to output only _changes_ in character formatting.
 */

bool TinyRichTextHTMLHandler::DoSaveFile(wxRichTextBuffer *buffer, wxOutputStream& stream)
{
    m_buffer = buffer;

    wxRichTextDrawingContext context(buffer);
    buffer->Defragment(context);

#if wxUSE_UNICODE
    wxCSConv* customEncoding = NULL;
    wxMBConv* conv = NULL;
    if (!GetEncoding().IsEmpty())
    {
        customEncoding = new wxCSConv(GetEncoding());
        if (!customEncoding->IsOk())
        {
            wxDELETE(customEncoding);
        }
    }
    if (customEncoding)
        conv = customEncoding;
    else
        conv = & wxConvUTF8;
#endif

    {
#if wxUSE_UNICODE
        wxTextOutputStream str(stream, wxEOL_NATIVE, *conv);
#else
        wxTextOutputStream str(stream, wxEOL_NATIVE);
#endif

        wxRichTextAttr currentParaStyle = buffer->GetAttributes();
        wxRichTextAttr currentCharStyle = buffer->GetAttributes();

        if ((GetFlags() & wxRICHTEXT_HANDLER_NO_HEADER_FOOTER) == 0)
            str << wxT("<html><head></head><body>\n");

        OutputFont(currentParaStyle, str);

        m_font = false;
        m_inTable = false;

        m_indents.Clear();
        m_listTypes.Clear();

        wxRichTextObjectList::compatibility_iterator node = buffer->GetChildren().GetFirst();
        while (node)
        {
            wxRichTextParagraph* para = wxDynamicCast(node->GetData(), wxRichTextParagraph);
            wxASSERT (para != NULL);

            if (para)
            {
                wxRichTextAttr paraStyle(para->GetCombinedAttributes());

                BeginParagraphFormatting(currentParaStyle, paraStyle, str);

                wxRichTextObjectList::compatibility_iterator node2 = para->GetChildren().GetFirst();
                while (node2)
                {
                    wxRichTextObject* obj = node2->GetData();
                    wxRichTextPlainText* textObj = wxDynamicCast(obj, wxRichTextPlainText);
                    if (textObj && !textObj->IsEmpty())
                    {
                        wxRichTextAttr charStyle(para->GetCombinedAttributes(obj->GetAttributes()));
                        BeginCharacterFormatting(currentCharStyle, charStyle, paraStyle, str);

                        wxString text = textObj->GetText();

                        if (charStyle.HasTextEffects() && (charStyle.GetTextEffects() & wxTEXT_ATTR_EFFECT_CAPITALS))
                            text.MakeUpper();

                        wxString toReplace = wxRichTextLineBreakChar;
                        text.Replace(toReplace, wxT("<br>"));

                        str << text;

                        EndCharacterFormatting(currentCharStyle, charStyle, paraStyle, str);
                    }

                    node2 = node2->GetNext();
                }

                EndParagraphFormatting(currentParaStyle, paraStyle, str);

                str << wxT("\n");
            }
            node = node->GetNext();
        }

        CloseLists(-1, str);

        str << wxT("</font>");

        if ((GetFlags() & wxRICHTEXT_HANDLER_NO_HEADER_FOOTER) == 0)
            str << wxT("</body></html>");

        str << wxT("\n");
    }

#if wxUSE_UNICODE
    if (customEncoding)
        delete customEncoding;
#endif

    m_buffer = NULL;

    return true;
}

void TinyRichTextHTMLHandler::BeginCharacterFormatting(const wxRichTextAttr& currentStyle, const wxRichTextAttr& thisStyle, const wxRichTextAttr& WXUNUSED(paraStyle), wxTextOutputStream& str)
{
    wxString style;

    // Is there any change in the font properties of the item?
    if (thisStyle.GetFontFaceName() != currentStyle.GetFontFaceName())
    {
        wxString faceName(thisStyle.GetFontFaceName());
        style += wxString::Format(wxT(" face=\"%s\""), faceName.c_str());
    }
    if (thisStyle.GetFontSize() != currentStyle.GetFontSize())
        style += wxString::Format(wxT(" size=\"%ld\""), PtToSize(thisStyle.GetFontSize()));

    bool bTextColourChanged = (thisStyle.GetTextColour() != currentStyle.GetTextColour());
    bool bBackgroundColourChanged = (thisStyle.GetBackgroundColour() != currentStyle.GetBackgroundColour());
    if (bTextColourChanged || bBackgroundColourChanged)
    {
        style += wxT(" style=\"");

        if (bTextColourChanged)
        {
            wxString color(thisStyle.GetTextColour().GetAsString(wxC2S_HTML_SYNTAX));
            style += wxString::Format(wxT("color: %s"), color.c_str());
        }
        if (bTextColourChanged && bBackgroundColourChanged)
            style += wxT(";");
        if (bBackgroundColourChanged)
        {
            wxString color(thisStyle.GetBackgroundColour().GetAsString(wxC2S_HTML_SYNTAX));
            style += wxString::Format(wxT("background-color: %s"), color.c_str());
        }

        style += wxT("\"");
    }

    if (style.size())
    {
        str << wxString::Format(wxT("<font %s >"), style.c_str());
        m_font = true;
    }

    if (thisStyle.GetFontWeight() == wxFONTWEIGHT_BOLD)
        str << wxT("<b>");
    if (thisStyle.GetFontStyle() == wxFONTSTYLE_ITALIC)
        str << wxT("<i>");
    if (thisStyle.GetFontUnderlined())
        str << wxT("<u>");

    if (thisStyle.HasURL())
        str << wxT("<a href=\"") << thisStyle.GetURL() << wxT("\">");

    if (thisStyle.HasTextEffects())
    {
        if (thisStyle.GetTextEffects() & wxTEXT_ATTR_EFFECT_STRIKETHROUGH)
            str << wxT("<del>");
        if (thisStyle.GetTextEffects() & wxTEXT_ATTR_EFFECT_SUPERSCRIPT)
            str << wxT("<sup>");
        if (thisStyle.GetTextEffects() & wxTEXT_ATTR_EFFECT_SUBSCRIPT)
            str << wxT("<sub>");
    }
}

void TinyRichTextHTMLHandler::EndCharacterFormatting(const wxRichTextAttr& WXUNUSED(currentStyle), const wxRichTextAttr& thisStyle, const wxRichTextAttr& WXUNUSED(paraStyle), wxTextOutputStream& stream)
{
    if (thisStyle.HasURL())
        stream << wxT("</a>");

    if (thisStyle.GetFontUnderlined())
        stream << wxT("</u>");
    if (thisStyle.GetFontStyle() == wxFONTSTYLE_ITALIC)
        stream << wxT("</i>");
    if (thisStyle.GetFontWeight() == wxFONTWEIGHT_BOLD)
        stream << wxT("</b>");

    if (thisStyle.HasTextEffects())
    {
        if (thisStyle.GetTextEffects() & wxTEXT_ATTR_EFFECT_STRIKETHROUGH)
            stream << wxT("</del>");
        if (thisStyle.GetTextEffects() & wxTEXT_ATTR_EFFECT_SUPERSCRIPT)
            stream << wxT("</sup>");
        if (thisStyle.GetTextEffects() & wxTEXT_ATTR_EFFECT_SUBSCRIPT)
            stream << wxT("</sub>");
    }

    if (m_font)
    {
        m_font = false;
        stream << wxT("</font>");
    }
}

/// Begin paragraph formatting
void TinyRichTextHTMLHandler::BeginParagraphFormatting(const wxRichTextAttr& WXUNUSED(currentStyle), const wxRichTextAttr& thisStyle, wxTextOutputStream& str)
{
    if (thisStyle.HasPageBreak())
    {
        str << wxT("<div style=\"page-break-after:always\"></div>\n");
    }

    if (thisStyle.HasLeftIndent() && thisStyle.GetLeftIndent() != 0)
    {
        if (thisStyle.HasBulletStyle())
        {
            int indent = thisStyle.GetLeftIndent();

            // Close levels high than this
            CloseLists(indent, str);

            if (m_indents.GetCount() > 0 && indent == m_indents.Last())
            {
                // Same level, no need to start a new list
            }
            else if (m_indents.GetCount() == 0 || indent > m_indents.Last())
            {
                m_indents.Add(indent);

                wxString tag;
                int listType = TypeOfList(thisStyle, tag);
                m_listTypes.Add(listType);

                // wxHTML needs an extra <p> before a list when using <p> ... </p> in previous paragraphs.
                // TODO: pass a flag that indicates we're using wxHTML.
                str << wxT("<p>\n");

                str << tag;
            }

            str << wxT("<li> ");
        }
        else
        {
            CloseLists(-1, str);

            wxString align = GetAlignment(thisStyle);
            str << wxString::Format(wxT("<p align=\"%s\""), align.c_str());

            wxString styleStr;

            if ((GetFlags() & wxRICHTEXT_HANDLER_USE_CSS) && thisStyle.HasParagraphSpacingBefore())
            {
                float spacingBeforeMM = thisStyle.GetParagraphSpacingBefore() / 10.0f;

                styleStr += wxString::Format(wxT("margin-top: %.2fmm; "), spacingBeforeMM);
            }
            if ((GetFlags() & wxRICHTEXT_HANDLER_USE_CSS) && thisStyle.HasParagraphSpacingAfter())
            {
                float spacingAfterMM = thisStyle.GetParagraphSpacingAfter() / 10.0f;

                styleStr += wxString::Format(wxT("margin-bottom: %.2fmm; "), spacingAfterMM);
            }

            float indentLeftMM = (thisStyle.GetLeftIndent() + thisStyle.GetLeftSubIndent())/10.0f;
            if ((GetFlags() & wxRICHTEXT_HANDLER_USE_CSS) && (indentLeftMM > 0.0))
            {
                styleStr += wxString::Format(wxT("margin-left: %.2fmm; "), indentLeftMM);
            }
            float indentRightMM = thisStyle.GetRightIndent()/10.0f;
            if ((GetFlags() & wxRICHTEXT_HANDLER_USE_CSS) && thisStyle.HasRightIndent() && (indentRightMM > 0.0))
            {
                styleStr += wxString::Format(wxT("margin-right: %.2fmm; "), indentRightMM);
            }
            // First line indentation
            float firstLineIndentMM = - thisStyle.GetLeftSubIndent() / 10.0f;
            if ((GetFlags() & wxRICHTEXT_HANDLER_USE_CSS) && (firstLineIndentMM > 0.0))
            {
                styleStr += wxString::Format(wxT("text-indent: %.2fmm; "), firstLineIndentMM);
            }

            if (!styleStr.IsEmpty())
                str << wxT(" style=\"") << styleStr << wxT("\"");

            str << wxT(">");

            // TODO: convert to pixels
            int indentPixels = static_cast<int>(indentLeftMM*10/4);

            if ((GetFlags() & wxRICHTEXT_HANDLER_USE_CSS) == 0)
            {
                // Use a table to do indenting if we don't have CSS
                str << wxString::Format(wxT("<table border=0 cellpadding=0 cellspacing=0><tr><td width=\"%d\"></td><td>"), indentPixels);
                m_inTable = true;
            }

            if (((GetFlags() & wxRICHTEXT_HANDLER_USE_CSS) == 0) && (thisStyle.GetLeftSubIndent() < 0))
            {
                str << SymbolicIndent( - thisStyle.GetLeftSubIndent());
            }
        }
    }
    else
    {
        CloseLists(-1, str);

        wxString align = GetAlignment(thisStyle);
        str << wxString::Format(wxT("<p align=\"%s\""), align.c_str());

        wxString styleStr;

        if ((GetFlags() & wxRICHTEXT_HANDLER_USE_CSS) && thisStyle.HasParagraphSpacingBefore())
        {
            float spacingBeforeMM = thisStyle.GetParagraphSpacingBefore() / 10.0f;

            styleStr += wxString::Format(wxT("margin-top: %.2fmm; "), spacingBeforeMM);
        }
        if ((GetFlags() & wxRICHTEXT_HANDLER_USE_CSS) && thisStyle.HasParagraphSpacingAfter())
        {
            float spacingAfterMM = thisStyle.GetParagraphSpacingAfter() / 10.0f;

            styleStr += wxString::Format(wxT("margin-bottom: %.2fmm; "), spacingAfterMM);
        }

        if (!styleStr.IsEmpty())
            str << wxT(" style=\"") << styleStr << wxT("\"");

        str << wxT(">");
    }
    OutputFont(thisStyle, str);
}

/// End paragraph formatting
void TinyRichTextHTMLHandler::EndParagraphFormatting(const wxRichTextAttr& WXUNUSED(currentStyle), const wxRichTextAttr& thisStyle, wxTextOutputStream& stream)
{
    if (thisStyle.HasFont())
        stream << wxT("</font>");

    if (m_inTable)
    {
        stream << wxT("</td></tr></table></p>\n");
        m_inTable = false;
    }
    else if (!thisStyle.HasBulletStyle())
        stream << wxT("</p>\n");
}

/// Closes lists to level (-1 means close all)
void TinyRichTextHTMLHandler::CloseLists(int level, wxTextOutputStream& str)
{
    // Close levels high than this
    int i = m_indents.GetCount()-1;
    while (i >= 0)
    {
        int l = m_indents[i];
        if (l > level)
        {
            if (m_listTypes[i] == 0)
                str << wxT("</ol>");
            else
                str << wxT("</ul>");
            m_indents.RemoveAt(i);
            m_listTypes.RemoveAt(i);
        }
        else
            break;
        i --;
     }
}

/// Output font tag
void TinyRichTextHTMLHandler::OutputFont(const wxRichTextAttr& style, wxTextOutputStream& stream)
{
    if (style.HasFont())
    {
        stream << wxString::Format(wxT("<font face=\"%s\" size=\"%ld\""), style.GetFontFaceName().c_str(), PtToSize(style.GetFontSize()));
        if (style.HasTextColour())
            stream << wxString::Format(wxT(" color=\"%s\""), style.GetTextColour().GetAsString(wxC2S_HTML_SYNTAX).c_str());
        stream << wxT(" >");
    }
}

int TinyRichTextHTMLHandler::TypeOfList( const wxRichTextAttr& thisStyle, wxString& tag )
{
    // We can use number attribute of li tag but not all the browsers support it.
    // also wxHtmlWindow doesn't support type attribute.

    bool m_is_ul = false;
    if (thisStyle.GetBulletStyle() == (wxTEXT_ATTR_BULLET_STYLE_ARABIC|wxTEXT_ATTR_BULLET_STYLE_PERIOD))
        tag = wxT("<ol type=\"1\">");
    else if (thisStyle.GetBulletStyle() == wxTEXT_ATTR_BULLET_STYLE_LETTERS_UPPER)
        tag = wxT("<ol type=\"A\">");
    else if (thisStyle.GetBulletStyle() == wxTEXT_ATTR_BULLET_STYLE_LETTERS_LOWER)
        tag = wxT("<ol type=\"a\">");
    else if (thisStyle.GetBulletStyle() == wxTEXT_ATTR_BULLET_STYLE_ROMAN_UPPER)
        tag = wxT("<ol type=\"I\">");
    else if (thisStyle.GetBulletStyle() == wxTEXT_ATTR_BULLET_STYLE_ROMAN_LOWER)
        tag = wxT("<ol type=\"i\">");
    else
    {
        tag = wxT("<ul>");
        m_is_ul = true;
    }

    if (m_is_ul)
        return 1;
    else
        return 0;
}

wxString TinyRichTextHTMLHandler::GetAlignment( const wxRichTextAttr& thisStyle )
{
    switch( thisStyle.GetAlignment() )
    {
    case wxTEXT_ALIGNMENT_LEFT:
        return  wxT("left");
    case wxTEXT_ALIGNMENT_RIGHT:
        return wxT("right");
    case wxTEXT_ALIGNMENT_CENTER:
        return wxT("center");
    case wxTEXT_ALIGNMENT_JUSTIFIED:
        return wxT("justify");
    default:
        return wxT("left");
    }
}

long TinyRichTextHTMLHandler::PtToSize(long size)
{
    int i;
    int len = m_fontSizeMapping.GetCount();
    for (i = 0; i < len; i++)
        if (size <= m_fontSizeMapping[i])
            return i+1;
    return 7;
}

wxString TinyRichTextHTMLHandler::SymbolicIndent(long indent)
{
    wxString in;
    for(;indent > 0; indent -= 20)
        in.Append( wxT("&nbsp;") );
    return in;
}

#endif
// wxUSE_STREAMS


#endif
// wxUSE_RICHTEXT

