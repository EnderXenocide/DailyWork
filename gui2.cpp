#include "gui2.h"

DECLARE_APP(MainApp)

///////////////////////////////////////////////////////////////////////////
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
    ID_RICHTEXT_STYLE_COMBO, 
    
    ID_CALENDAR_SEL_CHANGED, 
    ID_TREE_SEL_CHANGED
};

// ----------------------------------------------------------------------------
// event tables and other macros for wxWidgets
// ----------------------------------------------------------------------------

// the event tables connect the wxWidgets events with the functions (event
// handlers) which process them. It can be also done at run-time, but for the
// simple menu events like this the static method is much simpler.
wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
    EVT_MENU(ID_Quit,  MainFrame::OnQuit)
    EVT_MENU(ID_About, MainFrame::OnAbout)

    EVT_MENU(wxID_OPEN,  MainFrame::OnOpen)
    EVT_MENU(wxID_SAVE,  MainFrame::OnSave)
    EVT_MENU(wxID_SAVEAS,  MainFrame::OnSaveAs)

    EVT_MENU(ID_FORMAT_BOLD,  MainFrame::OnBold)
    EVT_MENU(ID_FORMAT_ITALIC,  MainFrame::OnItalic)
    EVT_MENU(ID_FORMAT_UNDERLINE,  MainFrame::OnUnderline)

    EVT_MENU(ID_FORMAT_STRIKETHROUGH,  MainFrame::OnStrikethrough)
    EVT_MENU(ID_FORMAT_SUPERSCRIPT,  MainFrame::OnSuperscript)
    EVT_MENU(ID_FORMAT_SUBSCRIPT,  MainFrame::OnSubscript)

    EVT_UPDATE_UI(ID_FORMAT_BOLD,  MainFrame::OnUpdateBold)
    EVT_UPDATE_UI(ID_FORMAT_ITALIC,  MainFrame::OnUpdateItalic)
    EVT_UPDATE_UI(ID_FORMAT_UNDERLINE,  MainFrame::OnUpdateUnderline)

    EVT_UPDATE_UI(ID_FORMAT_STRIKETHROUGH,  MainFrame::OnUpdateStrikethrough)
    EVT_UPDATE_UI(ID_FORMAT_SUPERSCRIPT,  MainFrame::OnUpdateSuperscript)
    EVT_UPDATE_UI(ID_FORMAT_SUBSCRIPT,  MainFrame::OnUpdateSubscript)

    EVT_MENU(ID_FORMAT_ALIGN_LEFT,  MainFrame::OnAlignLeft)
    EVT_MENU(ID_FORMAT_ALIGN_CENTRE,  MainFrame::OnAlignCentre)
    EVT_MENU(ID_FORMAT_ALIGN_RIGHT,  MainFrame::OnAlignRight)

    EVT_UPDATE_UI(ID_FORMAT_ALIGN_LEFT,  MainFrame::OnUpdateAlignLeft)
    EVT_UPDATE_UI(ID_FORMAT_ALIGN_CENTRE,  MainFrame::OnUpdateAlignCentre)
    EVT_UPDATE_UI(ID_FORMAT_ALIGN_RIGHT,  MainFrame::OnUpdateAlignRight)

    EVT_MENU(ID_FORMAT_FONT,  MainFrame::OnFont)
    EVT_MENU(ID_FORMAT_IMAGE, MainFrame::OnImage)
    EVT_MENU(ID_FORMAT_PARAGRAPH,  MainFrame::OnParagraph)
    EVT_MENU(ID_FORMAT_CONTENT,  MainFrame::OnFormat)
    EVT_UPDATE_UI(ID_FORMAT_CONTENT,  MainFrame::OnUpdateFormat)
    EVT_UPDATE_UI(ID_FORMAT_FONT,  MainFrame::OnUpdateFormat)
    EVT_UPDATE_UI(ID_FORMAT_IMAGE, MainFrame::OnUpdateImage)
    EVT_UPDATE_UI(ID_FORMAT_PARAGRAPH,  MainFrame::OnUpdateFormat)
    EVT_MENU(ID_FORMAT_INDENT_MORE,  MainFrame::OnIndentMore)
    EVT_MENU(ID_FORMAT_INDENT_LESS,  MainFrame::OnIndentLess)

    EVT_MENU(ID_FORMAT_LINE_SPACING_HALF,  MainFrame::OnLineSpacingHalf)
    EVT_MENU(ID_FORMAT_LINE_SPACING_SINGLE,  MainFrame::OnLineSpacingSingle)
    EVT_MENU(ID_FORMAT_LINE_SPACING_DOUBLE,  MainFrame::OnLineSpacingDouble)

    EVT_MENU(ID_FORMAT_PARAGRAPH_SPACING_MORE,  MainFrame::OnParagraphSpacingMore)
    EVT_MENU(ID_FORMAT_PARAGRAPH_SPACING_LESS,  MainFrame::OnParagraphSpacingLess)

    EVT_MENU(ID_RELOAD,  MainFrame::OnReload)

    EVT_MENU(ID_INSERT_SYMBOL,  MainFrame::OnInsertSymbol)
    EVT_MENU(ID_INSERT_URL,  MainFrame::OnInsertURL)
    EVT_MENU(ID_INSERT_IMAGE, MainFrame::OnInsertImage)

    EVT_MENU(ID_FORMAT_NUMBER_LIST, MainFrame::OnNumberList)
    EVT_MENU(ID_FORMAT_BULLETS_AND_NUMBERING, MainFrame::OnBulletsAndNumbering)
    EVT_MENU(ID_FORMAT_ITEMIZE_LIST, MainFrame::OnItemizeList)
    EVT_MENU(ID_FORMAT_RENUMBER_LIST, MainFrame::OnRenumberList)
    EVT_MENU(ID_FORMAT_PROMOTE_LIST, MainFrame::OnPromoteList)
    EVT_MENU(ID_FORMAT_DEMOTE_LIST, MainFrame::OnDemoteList)
    EVT_MENU(ID_FORMAT_CLEAR_LIST, MainFrame::OnClearList)

    EVT_MENU(ID_TABLE_ADD_COLUMN, MainFrame::OnTableAddColumn)
    EVT_MENU(ID_TABLE_ADD_ROW, MainFrame::OnTableAddRow)
    EVT_MENU(ID_TABLE_DELETE_COLUMN, MainFrame::OnTableDeleteColumn)
    EVT_MENU(ID_TABLE_DELETE_ROW, MainFrame::OnTableDeleteRow)
    EVT_UPDATE_UI_RANGE(ID_TABLE_ADD_COLUMN, ID_TABLE_ADD_ROW, MainFrame::OnTableFocusedUpdateUI)
    EVT_UPDATE_UI_RANGE(ID_TABLE_DELETE_COLUMN, ID_TABLE_DELETE_ROW, MainFrame::OnTableHasCellsUpdateUI)

    EVT_MENU(ID_VIEW_HTML, MainFrame::OnViewHTML)
    EVT_MENU(ID_SWITCH_STYLE_SHEETS, MainFrame::OnSwitchStyleSheets)
    EVT_MENU(ID_MANAGE_STYLES, MainFrame::OnManageStyles)

#if wxUSE_PRINTING_ARCHITECTURE
    EVT_MENU(ID_PRINT, MainFrame::OnPrint)
    EVT_MENU(ID_PREVIEW, MainFrame::OnPreview)
#endif
    EVT_MENU(ID_PAGE_SETUP, MainFrame::OnPageSetup)

    EVT_TEXT_URL(wxID_ANY, MainFrame::OnURL)
    EVT_RICHTEXT_STYLESHEET_REPLACING(wxID_ANY, MainFrame::OnStyleSheetReplacing)

    EVT_MENU(ID_SET_FONT_SCALE, MainFrame::OnSetFontScale)
    EVT_MENU(ID_SET_DIMENSION_SCALE, MainFrame::OnSetDimensionScale)
    
    EVT_TREE_SEL_CHANGED(ID_TREE_SEL_CHANGED, MainFrame::OnTreeSelChanged)
    EVT_CALENDAR_SEL_CHANGED(ID_CALENDAR_SEL_CHANGED, MainFrame::OnCalendarSelChanged)

wxEND_EVENT_TABLE()


// BEGIN EVENTS

MainFrame::~MainFrame()
{
	// Disconnect Events
//	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( MainFrame::OnCloseFrame ) );
//	this->Disconnect( wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnExitClick ) );
	m_treeDates->Disconnect( wxEVT_COMMAND_TREE_SEL_CHANGED, wxTreeEventHandler( MainFrame::OnTreeSelChanged ), NULL, this );
	m_calendar->Disconnect( wxEVT_CALENDAR_SEL_CHANGED, wxCalendarEventHandler( MainFrame::OnCalendarSelChanged ), NULL, this );

}


// frame constructor
MainFrame::MainFrame(const wxString& title, wxWindowID id, const wxPoint& pos,
        const wxSize& size, long style)
       : wxFrame(NULL, id, title, pos, size, style)
{
#ifdef __WXMAC__
    SetWindowVariant(wxWINDOW_VARIANT_SMALL);
#endif
    
    // set the frame icon
    SetIcon(wxICON(sample));

    // create a menu bar
    wxMenu *fileMenu = new wxMenu;

    // the "About" item should be in the help menu
    wxMenu *helpMenu = new wxMenu;
    helpMenu->Append(ID_About, wxT("&About\tF1"), wxT("Show about dialog"));

    fileMenu->Append(wxID_OPEN, wxT("&Open\tCtrl+O"), wxT("Open a file"));
    fileMenu->Append(wxID_SAVE, wxT("&Save\tCtrl+S"), wxT("Save a file"));
    fileMenu->Append(wxID_SAVEAS, wxT("&Save As...\tF12"), wxT("Save to a new file"));
    fileMenu->AppendSeparator();
    fileMenu->Append(ID_RELOAD, wxT("&Reload Text\tF2"), wxT("Reload the initial text"));
    fileMenu->AppendSeparator();
    fileMenu->Append(ID_PAGE_SETUP, wxT("Page Set&up..."), wxT("Page setup"));
#if wxUSE_PRINTING_ARCHITECTURE
    fileMenu->Append(ID_PRINT, wxT("&Print...\tCtrl+P"), wxT("Print"));
    fileMenu->Append(ID_PREVIEW, wxT("Print Pre&view"), wxT("Print preview"));
#endif
    fileMenu->AppendSeparator();
    fileMenu->Append(ID_VIEW_HTML, wxT("&View as HTML"), wxT("View HTML"));
    fileMenu->AppendSeparator();
    fileMenu->Append(ID_Quit, wxT("E&xit\tAlt+X"), wxT("Quit this program"));

    wxMenu* editMenu = new wxMenu;
    editMenu->Append(wxID_UNDO, _("&Undo\tCtrl+Z"));
    editMenu->Append(wxID_REDO, _("&Redo\tCtrl+Y"));
    editMenu->AppendSeparator();
    editMenu->Append(wxID_CUT, _("Cu&t\tCtrl+X"));
    editMenu->Append(wxID_COPY, _("&Copy\tCtrl+C"));
    editMenu->Append(wxID_PASTE, _("&Paste\tCtrl+V"));

    editMenu->AppendSeparator();
    editMenu->Append(wxID_SELECTALL, _("Select A&ll\tCtrl+A"));
    editMenu->AppendSeparator();
    editMenu->Append(ID_SET_FONT_SCALE, _("Set &Text Scale..."));
    editMenu->Append(ID_SET_DIMENSION_SCALE, _("Set &Dimension Scale..."));

    wxMenu* formatMenu = new wxMenu;
    formatMenu->AppendCheckItem(ID_FORMAT_BOLD, _("&Bold\tCtrl+B"));
    formatMenu->AppendCheckItem(ID_FORMAT_ITALIC, _("&Italic\tCtrl+I"));
    formatMenu->AppendCheckItem(ID_FORMAT_UNDERLINE, _("&Underline\tCtrl+U"));
    formatMenu->AppendSeparator();
    formatMenu->AppendCheckItem(ID_FORMAT_STRIKETHROUGH, _("Stri&kethrough"));
    formatMenu->AppendCheckItem(ID_FORMAT_SUPERSCRIPT, _("Superscrip&t"));
    formatMenu->AppendCheckItem(ID_FORMAT_SUBSCRIPT, _("Subscrip&t"));
    formatMenu->AppendSeparator();
    formatMenu->AppendCheckItem(ID_FORMAT_ALIGN_LEFT, _("L&eft Align"));
    formatMenu->AppendCheckItem(ID_FORMAT_ALIGN_RIGHT, _("&Right Align"));
    formatMenu->AppendCheckItem(ID_FORMAT_ALIGN_CENTRE, _("&Centre"));
    formatMenu->AppendSeparator();
    formatMenu->Append(ID_FORMAT_INDENT_MORE, _("Indent &More"));
    formatMenu->Append(ID_FORMAT_INDENT_LESS, _("Indent &Less"));
    formatMenu->AppendSeparator();
    formatMenu->Append(ID_FORMAT_PARAGRAPH_SPACING_MORE, _("Increase Paragraph &Spacing"));
    formatMenu->Append(ID_FORMAT_PARAGRAPH_SPACING_LESS, _("Decrease &Paragraph Spacing"));
    formatMenu->AppendSeparator();
    formatMenu->Append(ID_FORMAT_LINE_SPACING_SINGLE, _("Normal Line Spacing"));
    formatMenu->Append(ID_FORMAT_LINE_SPACING_HALF, _("1.5 Line Spacing"));
    formatMenu->Append(ID_FORMAT_LINE_SPACING_DOUBLE, _("Double Line Spacing"));
    formatMenu->AppendSeparator();
    formatMenu->Append(ID_FORMAT_FONT, _("&Font..."));
    formatMenu->Append(ID_FORMAT_IMAGE, _("Image Property"));
    formatMenu->Append(ID_FORMAT_PARAGRAPH, _("&Paragraph..."));
    formatMenu->Append(ID_FORMAT_CONTENT, _("Font and Pa&ragraph...\tShift+Ctrl+F"));
    formatMenu->AppendSeparator();
    formatMenu->Append(ID_SWITCH_STYLE_SHEETS, _("&Switch Style Sheets"));
    formatMenu->Append(ID_MANAGE_STYLES, _("&Manage Styles"));

    wxMenu* listsMenu = new wxMenu;
    listsMenu->Append(ID_FORMAT_BULLETS_AND_NUMBERING, _("Bullets and &Numbering..."));
    listsMenu->AppendSeparator();
    listsMenu->Append(ID_FORMAT_NUMBER_LIST, _("Number List"));
    listsMenu->Append(ID_FORMAT_ITEMIZE_LIST, _("Itemize List"));
    listsMenu->Append(ID_FORMAT_RENUMBER_LIST, _("Renumber List"));
    listsMenu->Append(ID_FORMAT_PROMOTE_LIST, _("Promote List Items"));
    listsMenu->Append(ID_FORMAT_DEMOTE_LIST, _("Demote List Items"));
    listsMenu->Append(ID_FORMAT_CLEAR_LIST, _("Clear List Formatting"));

    wxMenu* tableMenu = new wxMenu;
    tableMenu->Append(ID_TABLE_ADD_COLUMN, _("&Add Column"));
    tableMenu->Append(ID_TABLE_ADD_ROW, _("Add &Row"));
    tableMenu->Append(ID_TABLE_DELETE_COLUMN, _("Delete &Column"));
    tableMenu->Append(ID_TABLE_DELETE_ROW, _("&Delete Row"));

    wxMenu* insertMenu = new wxMenu;
    insertMenu->Append(ID_INSERT_SYMBOL, _("&Symbol...\tCtrl+I"));
    insertMenu->Append(ID_INSERT_URL, _("&URL..."));
    insertMenu->Append(ID_INSERT_IMAGE, _("&Image..."));

    // now append the freshly created menu to the menu bar...
    wxMenuBar *menuBar = new wxMenuBar();
    menuBar->Append(fileMenu, wxT("&File"));
    menuBar->Append(editMenu, wxT("&Edit"));
    menuBar->Append(formatMenu, wxT("F&ormat"));
    menuBar->Append(listsMenu, wxT("&Lists"));
    menuBar->Append(tableMenu, wxT("&Tables"));
    menuBar->Append(insertMenu, wxT("&Insert"));
    menuBar->Append(helpMenu, wxT("&Help"));

    // ... and attach this menu bar to the frame
    SetMenuBar(menuBar);

    // create a status bar just for fun (by default with 1 pane only)
    // but don't create it on limited screen space (WinCE)
    bool is_pda = wxSystemSettings::GetScreenType() <= wxSYS_SCREEN_PDA;

#if wxUSE_STATUSBAR
    if ( !is_pda )
    {
        m_statusBar = CreateStatusBar(2);
        SetStatusText(wxT("Welcome to wxRichTextCtrl!"));
    }
#endif

	wxBoxSizer* mainSizer;
	mainSizer = new wxBoxSizer( wxHORIZONTAL );
	
 	wxBoxSizer* datesSizer;
	datesSizer = new wxBoxSizer( wxVERTICAL );
	
	m_treeDates = new wxTreeCtrl( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTR_DEFAULT_STYLE );
	datesSizer->Add( m_treeDates, 1, wxALL|wxEXPAND, 5 );
	
	m_calendar = new wxCalendarCtrl( this, wxID_ANY, wxDefaultDateTime, wxDefaultPosition, wxDefaultSize, wxCAL_SHOW_HOLIDAYS );
	datesSizer->Add( m_calendar, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	mainSizer->Add( datesSizer, 0, wxEXPAND, 5 );
	 
    wxFont textFont = wxFont(12, wxROMAN, wxNORMAL, wxNORMAL);
    wxFont boldFont = wxFont(12, wxROMAN, wxNORMAL, wxBOLD);
    wxFont italicFont = wxFont(12, wxROMAN, wxITALIC, wxNORMAL);

    m_editor = new MyRichTextCtrl(this, ID_RICHTEXT_CTRL, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxVSCROLL|wxHSCROLL/*|wxWANTS_CHARS*/);
    wxASSERT(!m_editor->GetBuffer().GetAttributes().HasFontPixelSize());

    wxFont font(12, wxROMAN, wxNORMAL, wxNORMAL);

    m_editor->SetFont(font);

    wxASSERT(!m_editor->GetBuffer().GetAttributes().HasFontPixelSize());
 
    m_editor->SetMargins(10, 10);

    m_editor->SetStyleSheet(wxGetApp().GetStyleSheet());

	mainSizer->Add( m_editor, 1, wxEXPAND | wxALL, 5 );
	
	this->SetSizer( mainSizer );
	this->Layout();

	//m_statusBar = this->CreateStatusBar( 1, wxST_SIZEGRIP, wxID_ANY );
    // On Mac, don't create a 'native' wxToolBar because small bitmaps are not supported by native
    // toolbars. On Mac, a non-native, small-bitmap toolbar doesn't show unless it is explicitly
    // managed, hence the use of sizers. In a real application, use larger icons for the main
    // toolbar to avoid the need for this workaround. Or, use the toolbar in a container window
    // as part of a more complex hierarchy, and the toolbar will automatically be non-native.

    wxSystemOptions::SetOption(wxT("mac.toolbar.no-native"), 1);

 	wxToolBar* toolBar = this->CreateToolBar( wxTB_HORIZONTAL, wxID_ANY ); 
  //  wxToolBar* toolBar = new wxToolBar(this, wxID_ANY, wxDefaultPosition, wxDefaultSize,
  //                                    wxNO_BORDER|wxTB_FLAT|wxTB_NODIVIDER|wxTB_NOALIGN);
  //  mainSizer->Add(toolBar, 0, wxEXPAND);

    toolBar->AddTool(wxID_OPEN, wxEmptyString, wxBitmap(open_xpm), _("Open"));
    toolBar->AddTool(wxID_SAVEAS, wxEmptyString, wxBitmap(save_xpm), _("Save"));
    toolBar->AddSeparator();
    toolBar->AddTool(wxID_CUT, wxEmptyString, wxBitmap(cut_xpm), _("Cut"));
    toolBar->AddTool(wxID_COPY, wxEmptyString, wxBitmap(copy_xpm), _("Copy"));
    toolBar->AddTool(wxID_PASTE, wxEmptyString, wxBitmap(paste_xpm), _("Paste"));
    toolBar->AddSeparator();
    toolBar->AddTool(wxID_UNDO, wxEmptyString, wxBitmap(undo_xpm), _("Undo"));
    toolBar->AddTool(wxID_REDO, wxEmptyString, wxBitmap(redo_xpm), _("Redo"));
    toolBar->AddSeparator();
    toolBar->AddCheckTool(ID_FORMAT_BOLD, wxEmptyString, wxBitmap(bold_xpm), wxNullBitmap, _("Bold"));
    toolBar->AddCheckTool(ID_FORMAT_ITALIC, wxEmptyString, wxBitmap(italic_xpm), wxNullBitmap, _("Italic"));
    toolBar->AddCheckTool(ID_FORMAT_UNDERLINE, wxEmptyString, wxBitmap(underline_xpm), wxNullBitmap, _("Underline"));
    toolBar->AddSeparator();
    toolBar->AddCheckTool(ID_FORMAT_ALIGN_LEFT, wxEmptyString, wxBitmap(alignleft_xpm), wxNullBitmap, _("Align Left"));
    toolBar->AddCheckTool(ID_FORMAT_ALIGN_CENTRE, wxEmptyString, wxBitmap(centre_xpm), wxNullBitmap, _("Centre"));
    toolBar->AddCheckTool(ID_FORMAT_ALIGN_RIGHT, wxEmptyString, wxBitmap(alignright_xpm), wxNullBitmap, _("Align Right"));
    toolBar->AddSeparator();
    toolBar->AddTool(ID_FORMAT_INDENT_LESS, wxEmptyString, wxBitmap(indentless_xpm), _("Indent Less"));
    toolBar->AddTool(ID_FORMAT_INDENT_MORE, wxEmptyString, wxBitmap(indentmore_xpm), _("Indent More"));
    toolBar->AddSeparator();
    toolBar->AddTool(ID_FORMAT_FONT, wxEmptyString, wxBitmap(font_xpm), _("Font"));
    toolBar->AddSeparator();

    wxRichTextStyleComboCtrl* combo = new wxRichTextStyleComboCtrl(toolBar, ID_RICHTEXT_STYLE_COMBO, wxDefaultPosition, wxSize(160, -1), wxCB_READONLY);
    toolBar->AddControl(combo);
    
    combo->SetStyleSheet(wxGetApp().GetStyleSheet());
    combo->SetRichTextCtrl(m_editor);
    combo->UpdateStyles();
    
    toolBar->Realize();
    m_mainToolBar = toolBar;

	this->Centre( wxBOTH );

    WriteInitialText();
 //	// Connect Events
//	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( MainFrame::OnCloseFrame ) );
//	this->Connect( menuFileExit->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnExitClick ) );
	m_treeDates->Connect( wxEVT_TREE_SEL_CHANGED, wxTreeEventHandler( MainFrame::OnTreeSelChanged ), NULL, this );
	m_calendar->Connect( wxEVT_CALENDAR_SEL_CHANGED, wxCalendarEventHandler( MainFrame::OnCalendarSelChanged ), NULL, this );
}   

void MainFrame::OnCloseFrame(wxCloseEvent& event)
{
	Destroy();
}

void MainFrame::OnCalendarSelChanged(wxCalendarEvent& event) 
{ 
    wxTreeItemId ItemID=m_treeDates->GetSelection();
    wxString msg = m_treeDates->GetItemText(ItemID);
    OnStatusBarMessage(msg.ToStdString());
//    if (ItemID != NULL)
 //       m_treeDates->Delete(ItemID);
 //wxWindowBase child;
   // m_treeDates->AddChild()
}  

void MainFrame::OnTreeSelChanged( wxTreeEvent& event )
{
    wxString texte = wxGetApp().GetDWParser()->GetWorkFromTree(m_treeDates);
    m_editor->Clear();
    m_editor->WriteText(texte);
}

void MainFrame::OnStatusBarMessage(std::string msg)
{
	//std::cout << msg << std::endl;
    LOG(INFO) << msg ;
    m_statusBar->SetStatusText(wxString::FromUTF8(msg.c_str()));
}

// END EVENTS

// Write text
void MainFrame::WriteInitialText()
{
    MyRichTextCtrl& r = *m_editor;

    r.SetDefaultStyle(wxRichTextAttr());

    r.Freeze();

    r.BeginSuppressUndo();

    r.BeginParagraphSpacing(0, 20);

    r.BeginAlignment(wxTEXT_ALIGNMENT_CENTRE);
    r.BeginBold();

    r.BeginFontSize(14);

    wxString lineBreak = (wxChar) 29;

    r.WriteText(wxString(wxT("Welcome to wxRichTextCtrl, a wxWidgets control")) + lineBreak + wxT("for editing and presenting styled text and images\n"));
    r.EndFontSize();

    r.BeginItalic();
    r.WriteText(wxT("by Julian Smart"));
    r.EndItalic();

    r.EndBold();
    r.Newline();

    r.WriteImage(wxBitmap(zebra_xpm));

    r.Newline();
    r.Newline();

    r.EndAlignment();

#if 0
    r.BeginAlignment(wxTEXT_ALIGNMENT_CENTRE);
    r.WriteText(wxString(wxT("This is a simple test for a floating left image test. The zebra image should be placed at the left side of the current buffer and all the text should flow around it at the right side. This is a simple test for a floating left image test. The zebra image should be placed at the left side of the current buffer and all the text should flow around it at the right side. This is a simple test for a floating left image test. The zebra image should be placed at the left side of the current buffer and all the text should flow around it at the right side.")));
    r.Newline();
    r.EndAlignment();
#endif

    r.BeginAlignment(wxTEXT_ALIGNMENT_LEFT);
    wxRichTextAttr imageAttr;
    imageAttr.GetTextBoxAttr().SetFloatMode(wxTEXT_BOX_ATTR_FLOAT_LEFT);
    r.WriteText(wxString(wxT("This is a simple test for a floating left image test. The zebra image should be placed at the left side of the current buffer and all the text should flow around it at the right side. This is a simple test for a floating left image test. The zebra image should be placed at the left side of the current buffer and all the text should flow around it at the right side. This is a simple test for a floating left image test. The zebra image should be placed at the left side of the current buffer and all the text should flow around it at the right side.")));
    r.WriteImage(wxBitmap(zebra_xpm), wxBITMAP_TYPE_PNG, imageAttr);

    imageAttr.GetTextBoxAttr().GetTop().SetValue(200);
    imageAttr.GetTextBoxAttr().GetTop().SetUnits(wxTEXT_ATTR_UNITS_PIXELS);
    imageAttr.GetTextBoxAttr().SetFloatMode(wxTEXT_BOX_ATTR_FLOAT_RIGHT);
    r.WriteImage(wxBitmap(zebra_xpm), wxBITMAP_TYPE_PNG, imageAttr);
    r.WriteText(wxString(wxT("This is a simple test for a floating right image test. The zebra image should be placed at the right side of the current buffer and all the text should flow around it at the left side. This is a simple test for a floating left image test. The zebra image should be placed at the right side of the current buffer and all the text should flow around it at the left side. This is a simple test for a floating left image test. The zebra image should be placed at the right side of the current buffer and all the text should flow around it at the left side.")));
    r.EndAlignment();
    r.Newline();

    r.WriteText(wxT("What can you do with this thing? "));

    r.WriteImage(wxBitmap(smiley_xpm));
    r.WriteText(wxT(" Well, you can change text "));

    r.BeginTextColour(*wxRED);
    r.WriteText(wxT("colour, like this red bit."));
    r.EndTextColour();

    wxRichTextAttr backgroundColourAttr;
    backgroundColourAttr.SetBackgroundColour(*wxGREEN);
    backgroundColourAttr.SetTextColour(*wxBLUE);
    r.BeginStyle(backgroundColourAttr);
    r.WriteText(wxT(" And this blue on green bit."));
    r.EndStyle();

    r.WriteText(wxT(" Naturally you can make things "));
    r.BeginBold();
    r.WriteText(wxT("bold "));
    r.EndBold();
    r.BeginItalic();
    r.WriteText(wxT("or italic "));
    r.EndItalic();
    r.BeginUnderline();
    r.WriteText(wxT("or underlined."));
    r.EndUnderline();

    r.BeginFontSize(14);
    r.WriteText(wxT(" Different font sizes on the same line is allowed, too."));
    r.EndFontSize();

    r.WriteText(wxT(" Next we'll show an indented paragraph."));

    r.Newline();

    r.BeginLeftIndent(60);
    r.WriteText(wxT("It was in January, the most down-trodden month of an Edinburgh winter. An attractive woman came into the cafe, which is nothing remarkable."));
    r.Newline();

    r.EndLeftIndent();

    r.WriteText(wxT("Next, we'll show a first-line indent, achieved using BeginLeftIndent(100, -40)."));

    r.Newline();

    r.BeginLeftIndent(100, -40);

    r.WriteText(wxT("It was in January, the most down-trodden month of an Edinburgh winter. An attractive woman came into the cafe, which is nothing remarkable."));
    r.Newline();

    r.EndLeftIndent();

    r.WriteText(wxT("Numbered bullets are possible, again using subindents:"));
    r.Newline();

    r.BeginNumberedBullet(1, 100, 60);
    r.WriteText(wxT("This is my first item. Note that wxRichTextCtrl can apply numbering and bullets automatically based on list styles, but this list is formatted explicitly by setting indents."));
    r.Newline();
    r.EndNumberedBullet();

    r.BeginNumberedBullet(2, 100, 60);
    r.WriteText(wxT("This is my second item."));
    r.Newline();
    r.EndNumberedBullet();

    r.WriteText(wxT("The following paragraph is right-indented:"));
    r.Newline();

    r.BeginRightIndent(200);

    r.WriteText(wxT("It was in January, the most down-trodden month of an Edinburgh winter. An attractive woman came into the cafe, which is nothing remarkable."));
    r.Newline();

    r.EndRightIndent();

    r.WriteText(wxT("The following paragraph is right-aligned with 1.5 line spacing:"));
    r.Newline();

    r.BeginAlignment(wxTEXT_ALIGNMENT_RIGHT);
    r.BeginLineSpacing(wxTEXT_ATTR_LINE_SPACING_HALF);
    r.WriteText(wxT("It was in January, the most down-trodden month of an Edinburgh winter. An attractive woman came into the cafe, which is nothing remarkable."));
    r.Newline();
    r.EndLineSpacing();
    r.EndAlignment();

    wxArrayInt tabs;
    tabs.Add(400);
    tabs.Add(600);
    tabs.Add(800);
    tabs.Add(1000);
    wxRichTextAttr attr;
    attr.SetFlags(wxTEXT_ATTR_TABS);
    attr.SetTabs(tabs);
    r.SetDefaultStyle(attr);

    r.WriteText(wxT("This line contains tabs:\tFirst tab\tSecond tab\tThird tab"));
    r.Newline();

    r.WriteText(wxT("Other notable features of wxRichTextCtrl include:"));
    r.Newline();

    r.BeginSymbolBullet(wxT('*'), 100, 60);
    r.WriteText(wxT("Compatibility with wxTextCtrl API"));
    r.Newline();
    r.EndSymbolBullet();

    r.BeginSymbolBullet(wxT('*'), 100, 60);
    r.WriteText(wxT("Easy stack-based BeginXXX()...EndXXX() style setting in addition to SetStyle()"));
    r.Newline();
    r.EndSymbolBullet();

    r.BeginSymbolBullet(wxT('*'), 100, 60);
    r.WriteText(wxT("XML loading and saving"));
    r.Newline();
    r.EndSymbolBullet();

    r.BeginSymbolBullet(wxT('*'), 100, 60);
    r.WriteText(wxT("Undo/Redo, with batching option and Undo suppressing"));
    r.Newline();
    r.EndSymbolBullet();

    r.BeginSymbolBullet(wxT('*'), 100, 60);
    r.WriteText(wxT("Clipboard copy and paste"));
    r.Newline();
    r.EndSymbolBullet();

    r.BeginSymbolBullet(wxT('*'), 100, 60);
    r.WriteText(wxT("wxRichTextStyleSheet with named character and paragraph styles, and control for applying named styles"));
    r.Newline();
    r.EndSymbolBullet();

    r.BeginSymbolBullet(wxT('*'), 100, 60);
    r.WriteText(wxT("A design that can easily be extended to other content types, ultimately with text boxes, tables, controls, and so on"));
    r.Newline();
    r.EndSymbolBullet();

    // Make a style suitable for showing a URL
    wxRichTextAttr urlStyle;
    urlStyle.SetTextColour(*wxBLUE);
    urlStyle.SetFontUnderlined(true);

    r.WriteText(wxT("wxRichTextCtrl can also display URLs, such as this one: "));
    r.BeginStyle(urlStyle);
    r.BeginURL(wxT("http://www.wxwidgets.org"));
    r.WriteText(wxT("The wxWidgets Web Site"));
    r.EndURL();
    r.EndStyle();
    r.WriteText(wxT(". Click on the URL to generate an event."));

    r.Newline();

    r.WriteText(wxT("Note: this sample content was generated programmatically from within the MainFrame constructor in the demo. The images were loaded from inline XPMs. Enjoy wxRichTextCtrl!\n"));

    r.EndParagraphSpacing();

#if 1
    {
        // Add a text box

        r.Newline();

        wxRichTextAttr attr;
        attr.GetTextBoxAttr().GetMargins().GetLeft().SetValue(20, wxTEXT_ATTR_UNITS_PIXELS);
        attr.GetTextBoxAttr().GetMargins().GetTop().SetValue(20, wxTEXT_ATTR_UNITS_PIXELS);
        attr.GetTextBoxAttr().GetMargins().GetRight().SetValue(20, wxTEXT_ATTR_UNITS_PIXELS);
        attr.GetTextBoxAttr().GetMargins().GetBottom().SetValue(20, wxTEXT_ATTR_UNITS_PIXELS);

        attr.GetTextBoxAttr().GetBorder().SetColour(*wxBLACK);
        attr.GetTextBoxAttr().GetBorder().SetWidth(1, wxTEXT_ATTR_UNITS_PIXELS);
        attr.GetTextBoxAttr().GetBorder().SetStyle(wxTEXT_BOX_ATTR_BORDER_SOLID);

        wxRichTextBox* textBox = r.WriteTextBox(attr);
        r.SetFocusObject(textBox);

        r.WriteText(wxT("This is a text box. Just testing! Once more unto the breach, dear friends, once more..."));

        r.SetFocusObject(NULL); // Set the focus back to the main buffer
        r.SetInsertionPointEnd();
    }
#endif

#if 1
    {
        // Add a table

        r.Newline();

        wxRichTextAttr attr;
        attr.GetTextBoxAttr().GetMargins().GetLeft().SetValue(5, wxTEXT_ATTR_UNITS_PIXELS);
        attr.GetTextBoxAttr().GetMargins().GetTop().SetValue(5, wxTEXT_ATTR_UNITS_PIXELS);
        attr.GetTextBoxAttr().GetMargins().GetRight().SetValue(5, wxTEXT_ATTR_UNITS_PIXELS);
        attr.GetTextBoxAttr().GetMargins().GetBottom().SetValue(5, wxTEXT_ATTR_UNITS_PIXELS);
        attr.GetTextBoxAttr().GetPadding() = attr.GetTextBoxAttr().GetMargins();

        attr.GetTextBoxAttr().GetBorder().SetColour(*wxBLACK);
        attr.GetTextBoxAttr().GetBorder().SetWidth(1, wxTEXT_ATTR_UNITS_PIXELS);
        attr.GetTextBoxAttr().GetBorder().SetStyle(wxTEXT_BOX_ATTR_BORDER_SOLID);

        wxRichTextAttr cellAttr = attr;
        cellAttr.GetTextBoxAttr().GetWidth().SetValue(200, wxTEXT_ATTR_UNITS_PIXELS);
        cellAttr.GetTextBoxAttr().GetHeight().SetValue(150, wxTEXT_ATTR_UNITS_PIXELS);

        wxRichTextTable* table = r.WriteTable(6, 4, attr, cellAttr);

        int i, j;
        for (j = 0; j < table->GetRowCount(); j++)
        {
            for (i = 0; i < table->GetColumnCount(); i++)
            {
                wxString msg = wxString::Format(wxT("This is cell %d, %d"), (j+1), (i+1));
                r.SetFocusObject(table->GetCell(j, i));
                r.WriteText(msg);
            }
        }
        
        // Demonstrate colspan and rowspan
        wxRichTextCell* cell = table->GetCell(1, 0);
        cell->SetColSpan(2);
        r.SetFocusObject(cell);
        cell->Clear();
        r.WriteText("This cell spans 2 columns");
        
        cell = table->GetCell(1, 3);
        cell->SetRowSpan(2);
        r.SetFocusObject(cell);
        cell->Clear();
        r.WriteText("This cell spans 2 rows");

        cell = table->GetCell(2, 1);
        cell->SetColSpan(2);
        cell->SetRowSpan(3);
        r.SetFocusObject(cell);
        cell->Clear();
        r.WriteText("This cell spans 2 columns and 3 rows");

        r.SetFocusObject(NULL); // Set the focus back to the main buffer
        r.SetInsertionPointEnd();
    }
#endif

    r.Newline(); r.Newline();

    wxRichTextProperties properties;
    r.WriteText(wxT("This is a rectangle field: "));
    r.WriteField(wxT("rectangle"), properties);
    r.WriteText(wxT(" and a begin section field: "));
    r.WriteField(wxT("begin-section"), properties);
    r.WriteText(wxT("This is text between the two tags."));
    r.WriteField(wxT("end-section"), properties);
    r.WriteText(wxT(" Now a bitmap. "));
    r.WriteField(wxT("bitmap"), properties);
    r.WriteText(wxT(" Before we go, here's a composite field: ***"));
    wxRichTextField* field = r.WriteField(wxT("composite"), properties);
    field->UpdateField(& r.GetBuffer()); // Creates the composite value (sort of a text box)
    r.WriteText(wxT("*** End of composite field."));

    r.Newline();
    r.EndSuppressUndo();

    // Add some locked content first - needs Undo to be enabled
    {
        r.BeginLock();
        r.WriteText(wxString(wxT("This is a locked object.")));
        r.EndLock();

        r.WriteText(wxString(wxT(" This is unlocked text. ")));

        r.BeginLock();
        r.WriteText(wxString(wxT("More locked content.")));
        r.EndLock();
        r.Newline();

        // Flush the Undo buffer
        r.GetCommandProcessor()->ClearCommands();
    }

    r.Thaw();
}

// event handlers

void MainFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    // true is to force the frame to close
    Close(true);
}

void MainFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
    wxString msg;
    msg.Printf( wxT("This is a demo for wxRichTextCtrl, a control for editing styled text.\n(c) Julian Smart, 2005"));
    wxMessageBox(msg, wxT("About wxRichTextCtrl Sample"), wxOK | wxICON_INFORMATION, this);
}

// Forward command events to the current rich text control, if any
bool MainFrame::ProcessEvent(wxEvent& event)
{
    if (event.IsCommandEvent() && !event.IsKindOf(CLASSINFO(wxChildFocusEvent)))
    {
        // Problem: we can get infinite recursion because the events
        // climb back up to this frame, and repeat.
        // Assume that command events don't cause another command event
        // to be called, so we can rely on inCommand not being overwritten

        static int s_eventType = 0;
        static wxWindowID s_id = 0;

        if (s_id != event.GetId() && s_eventType != event.GetEventType())
        {
            s_eventType = event.GetEventType();
            s_id = event.GetId();

            wxWindow* focusWin = wxFindFocusDescendant(this);
            if (focusWin && focusWin->GetEventHandler()->ProcessEvent(event))
            {
                //s_command = NULL;
                s_eventType = 0;
                s_id = 0;
                return true;
            }

            s_eventType = 0;
            s_id = 0;
        }
        else
        {
            return false;
        }
    }

    return wxFrame::ProcessEvent(event);
}

void MainFrame::OnOpen(wxCommandEvent& WXUNUSED(event))
{
    wxString path;
    wxString filename;
    wxArrayInt fileTypes;

    wxString filter = wxRichTextBuffer::GetExtWildcard(false, false, & fileTypes);
    if (!filter.empty())
        filter += wxT("|");
    filter += wxT("All files (*.*)|*.*");

    wxFileDialog dialog(this,
        _("Choose a filename"),
        path,
        filename,
        filter,
        wxFD_OPEN);

    if (dialog.ShowModal() == wxID_OK)
    {
        wxString path = dialog.GetPath();

        if (!path.empty())
        {
            int filterIndex = dialog.GetFilterIndex();
            int fileType = (filterIndex < (int) fileTypes.GetCount())
                           ? fileTypes[filterIndex]
                           : wxRICHTEXT_TYPE_TEXT;
            m_editor->LoadFile(path, fileType);
        }
    }
}

void MainFrame::OnSave(wxCommandEvent& event)
{
    if (m_editor->GetFilename().empty())
    {
        OnSaveAs(event);
        return;
    }
    m_editor->SaveFile();
}

void MainFrame::OnSaveAs(wxCommandEvent& WXUNUSED(event))
{
    wxString filter = wxRichTextBuffer::GetExtWildcard(false, true);
    wxString path;
    wxString filename;

    wxFileDialog dialog(this,
        _("Choose a filename"),
        path,
        filename,
        filter,
        wxFD_SAVE);

    if (dialog.ShowModal() == wxID_OK)
    {
        wxString path = dialog.GetPath();

        if (!path.empty())
        {
            wxBusyCursor busy;
            wxStopWatch stopwatch;

            m_editor->SaveFile(path);

            long t = stopwatch.Time();
            wxLogDebug(wxT("Saving took %ldms"), t);
            wxMessageBox(wxString::Format(wxT("Saving took %ldms"), t));
        }
    }
}

void MainFrame::OnBold(wxCommandEvent& WXUNUSED(event))
{
    m_editor->ApplyBoldToSelection();
}

void MainFrame::OnItalic(wxCommandEvent& WXUNUSED(event))
{
    m_editor->ApplyItalicToSelection();
}

void MainFrame::OnUnderline(wxCommandEvent& WXUNUSED(event))
{
    m_editor->ApplyUnderlineToSelection();
}

void MainFrame::OnStrikethrough(wxCommandEvent& WXUNUSED(event))
{
    m_editor->ApplyTextEffectToSelection(wxTEXT_ATTR_EFFECT_STRIKETHROUGH);
}

void MainFrame::OnSuperscript(wxCommandEvent& WXUNUSED(event))
{
    m_editor->ApplyTextEffectToSelection(wxTEXT_ATTR_EFFECT_SUPERSCRIPT);
}

void MainFrame::OnSubscript(wxCommandEvent& WXUNUSED(event))
{
    m_editor->ApplyTextEffectToSelection(wxTEXT_ATTR_EFFECT_SUBSCRIPT);
}


void MainFrame::OnUpdateBold(wxUpdateUIEvent& event)
{
    event.Check(m_editor->IsSelectionBold());
}

void MainFrame::OnUpdateItalic(wxUpdateUIEvent& event)
{
    event.Check(m_editor->IsSelectionItalics());
}

void MainFrame::OnUpdateUnderline(wxUpdateUIEvent& event)
{
    event.Check(m_editor->IsSelectionUnderlined());
}

void MainFrame::OnUpdateStrikethrough(wxUpdateUIEvent& event)
{
    event.Check(m_editor->DoesSelectionHaveTextEffectFlag(wxTEXT_ATTR_EFFECT_STRIKETHROUGH));
}

void MainFrame::OnUpdateSuperscript(wxUpdateUIEvent& event)
{
    event.Check(m_editor->DoesSelectionHaveTextEffectFlag(wxTEXT_ATTR_EFFECT_SUPERSCRIPT));
}

void MainFrame::OnUpdateSubscript(wxUpdateUIEvent& event)
{
    event.Check(m_editor->DoesSelectionHaveTextEffectFlag(wxTEXT_ATTR_EFFECT_SUBSCRIPT));
}

void MainFrame::OnAlignLeft(wxCommandEvent& WXUNUSED(event))
{
    m_editor->ApplyAlignmentToSelection(wxTEXT_ALIGNMENT_LEFT);
}

void MainFrame::OnAlignCentre(wxCommandEvent& WXUNUSED(event))
{
    m_editor->ApplyAlignmentToSelection(wxTEXT_ALIGNMENT_CENTRE);
}

void MainFrame::OnAlignRight(wxCommandEvent& WXUNUSED(event))
{
    m_editor->ApplyAlignmentToSelection(wxTEXT_ALIGNMENT_RIGHT);
}

void MainFrame::OnUpdateAlignLeft(wxUpdateUIEvent& event)
{
    event.Check(m_editor->IsSelectionAligned(wxTEXT_ALIGNMENT_LEFT));
}

void MainFrame::OnUpdateAlignCentre(wxUpdateUIEvent& event)
{
    event.Check(m_editor->IsSelectionAligned(wxTEXT_ALIGNMENT_CENTRE));
}

void MainFrame::OnUpdateAlignRight(wxUpdateUIEvent& event)
{
    event.Check(m_editor->IsSelectionAligned(wxTEXT_ALIGNMENT_RIGHT));
}

void MainFrame::OnFont(wxCommandEvent& WXUNUSED(event))
{
    wxRichTextRange range;
    if (m_editor->HasSelection())
        range = m_editor->GetSelectionRange();
    else
        range = wxRichTextRange(0, m_editor->GetLastPosition()+1);

    int pages = wxRICHTEXT_FORMAT_FONT;

    wxRichTextFormattingDialog formatDlg(pages, this);
    formatDlg.SetOptions(wxRichTextFormattingDialog::Option_AllowPixelFontSize);
    formatDlg.GetStyle(m_editor, range);

    if (formatDlg.ShowModal() == wxID_OK)
    {
        formatDlg.ApplyStyle(m_editor, range, wxRICHTEXT_SETSTYLE_WITH_UNDO|wxRICHTEXT_SETSTYLE_OPTIMIZE|wxRICHTEXT_SETSTYLE_CHARACTERS_ONLY);
    }
}

void MainFrame::OnImage(wxCommandEvent& WXUNUSED(event))
{
    wxRichTextRange range;
    wxASSERT(m_editor->HasSelection());

    range = m_editor->GetSelectionRange();
    wxASSERT(range.ToInternal().GetLength() == 1);

    wxRichTextImage* image = wxDynamicCast(m_editor->GetFocusObject()->GetLeafObjectAtPosition(range.GetStart()), wxRichTextImage);
    if (image)
    {
        wxRichTextObjectPropertiesDialog imageDlg(image, this);

        if (imageDlg.ShowModal() == wxID_OK)
        {
            imageDlg.ApplyStyle(m_editor);
        }
    }
}

void MainFrame::OnParagraph(wxCommandEvent& WXUNUSED(event))
{
    wxRichTextRange range;
    if (m_editor->HasSelection())
        range = m_editor->GetSelectionRange();
    else
        range = wxRichTextRange(0, m_editor->GetLastPosition()+1);

    int pages = wxRICHTEXT_FORMAT_INDENTS_SPACING|wxRICHTEXT_FORMAT_TABS|wxRICHTEXT_FORMAT_BULLETS;

    wxRichTextFormattingDialog formatDlg(pages, this);
    formatDlg.GetStyle(m_editor, range);

    if (formatDlg.ShowModal() == wxID_OK)
    {
        formatDlg.ApplyStyle(m_editor, range);
    }
}

void MainFrame::OnFormat(wxCommandEvent& WXUNUSED(event))
{
    wxRichTextRange range;
    if (m_editor->HasSelection())
        range = m_editor->GetSelectionRange();
    else
        range = wxRichTextRange(0, m_editor->GetLastPosition()+1);

    int pages = wxRICHTEXT_FORMAT_FONT|wxRICHTEXT_FORMAT_INDENTS_SPACING|wxRICHTEXT_FORMAT_TABS|wxRICHTEXT_FORMAT_BULLETS;

    wxRichTextFormattingDialog formatDlg(pages, this);
    formatDlg.GetStyle(m_editor, range);

    if (formatDlg.ShowModal() == wxID_OK)
    {
        formatDlg.ApplyStyle(m_editor, range);
    }
}

void MainFrame::OnUpdateFormat(wxUpdateUIEvent& event)
{
    event.Enable(m_editor->HasSelection());
}

void MainFrame::OnUpdateImage(wxUpdateUIEvent& event)
{
    wxRichTextRange range;
    wxRichTextObject *obj;

    range = m_editor->GetSelectionRange();
    if (range.ToInternal().GetLength() == 1)
    {
        obj = m_editor->GetFocusObject()->GetLeafObjectAtPosition(range.GetStart());
        if (obj && obj->IsKindOf(CLASSINFO(wxRichTextImage)))
        {
            event.Enable(true);
            return;
        }
    }

    event.Enable(false);
}

void MainFrame::OnIndentMore(wxCommandEvent& WXUNUSED(event))
{
    wxRichTextAttr attr;
    attr.SetFlags(wxTEXT_ATTR_LEFT_INDENT);

    if (m_editor->GetStyle(m_editor->GetInsertionPoint(), attr))
    {
        wxRichTextRange range(m_editor->GetInsertionPoint(), m_editor->GetInsertionPoint());
        if (m_editor->HasSelection())
            range = m_editor->GetSelectionRange();

        attr.SetLeftIndent(attr.GetLeftIndent() + 100);

        attr.SetFlags(wxTEXT_ATTR_LEFT_INDENT);
        m_editor->SetStyle(range, attr);
    }
}

void MainFrame::OnIndentLess(wxCommandEvent& WXUNUSED(event))
{
    wxRichTextAttr attr;
    attr.SetFlags(wxTEXT_ATTR_LEFT_INDENT);

    if (m_editor->GetStyle(m_editor->GetInsertionPoint(), attr))
    {
        wxRichTextRange range(m_editor->GetInsertionPoint(), m_editor->GetInsertionPoint());
        if (m_editor->HasSelection())
            range = m_editor->GetSelectionRange();

        if (attr.GetLeftIndent() > 0)
        {
            attr.SetLeftIndent(wxMax(0, attr.GetLeftIndent() - 100));

            m_editor->SetStyle(range, attr);
        }
    }
}

void MainFrame::OnLineSpacingHalf(wxCommandEvent& WXUNUSED(event))
{
    wxRichTextAttr attr;
    attr.SetFlags(wxTEXT_ATTR_LINE_SPACING);

    if (m_editor->GetStyle(m_editor->GetInsertionPoint(), attr))
    {
        wxRichTextRange range(m_editor->GetInsertionPoint(), m_editor->GetInsertionPoint());
        if (m_editor->HasSelection())
            range = m_editor->GetSelectionRange();

        attr.SetFlags(wxTEXT_ATTR_LINE_SPACING);
        attr.SetLineSpacing(15);

        m_editor->SetStyle(range, attr);
    }
}

void MainFrame::OnLineSpacingDouble(wxCommandEvent& WXUNUSED(event))
{
    wxRichTextAttr attr;
    attr.SetFlags(wxTEXT_ATTR_LINE_SPACING);

    if (m_editor->GetStyle(m_editor->GetInsertionPoint(), attr))
    {
        wxRichTextRange range(m_editor->GetInsertionPoint(), m_editor->GetInsertionPoint());
        if (m_editor->HasSelection())
            range = m_editor->GetSelectionRange();

        attr.SetFlags(wxTEXT_ATTR_LINE_SPACING);
        attr.SetLineSpacing(20);

        m_editor->SetStyle(range, attr);
    }
}

void MainFrame::OnLineSpacingSingle(wxCommandEvent& WXUNUSED(event))
{
    wxRichTextAttr attr;
    attr.SetFlags(wxTEXT_ATTR_LINE_SPACING);

    if (m_editor->GetStyle(m_editor->GetInsertionPoint(), attr))
    {
        wxRichTextRange range(m_editor->GetInsertionPoint(), m_editor->GetInsertionPoint());
        if (m_editor->HasSelection())
            range = m_editor->GetSelectionRange();

        attr.SetFlags(wxTEXT_ATTR_LINE_SPACING);
        attr.SetLineSpacing(0); // Can also use 10

        m_editor->SetStyle(range, attr);
    }
}

void MainFrame::OnParagraphSpacingMore(wxCommandEvent& WXUNUSED(event))
{
    wxRichTextAttr attr;
    attr.SetFlags(wxTEXT_ATTR_PARA_SPACING_AFTER);

    if (m_editor->GetStyle(m_editor->GetInsertionPoint(), attr))
    {
        wxRichTextRange range(m_editor->GetInsertionPoint(), m_editor->GetInsertionPoint());
        if (m_editor->HasSelection())
            range = m_editor->GetSelectionRange();

        attr.SetParagraphSpacingAfter(attr.GetParagraphSpacingAfter() + 20);

        attr.SetFlags(wxTEXT_ATTR_PARA_SPACING_AFTER);
        m_editor->SetStyle(range, attr);
    }
}

void MainFrame::OnParagraphSpacingLess(wxCommandEvent& WXUNUSED(event))
{
    wxRichTextAttr attr;
    attr.SetFlags(wxTEXT_ATTR_PARA_SPACING_AFTER);

    if (m_editor->GetStyle(m_editor->GetInsertionPoint(), attr))
    {
        wxRichTextRange range(m_editor->GetInsertionPoint(), m_editor->GetInsertionPoint());
        if (m_editor->HasSelection())
            range = m_editor->GetSelectionRange();

        if (attr.GetParagraphSpacingAfter() >= 20)
        {
            attr.SetParagraphSpacingAfter(attr.GetParagraphSpacingAfter() - 20);

            attr.SetFlags(wxTEXT_ATTR_PARA_SPACING_AFTER);
            m_editor->SetStyle(range, attr);
        }
    }
}

void MainFrame::OnReload(wxCommandEvent& WXUNUSED(event))
{
    m_editor->Clear();
    WriteInitialText();
}

void MainFrame::OnViewHTML(wxCommandEvent& WXUNUSED(event))
{
    wxDialog dialog(this, wxID_ANY, _("HTML"), wxDefaultPosition, wxSize(500, 400), wxDEFAULT_DIALOG_STYLE);

    wxBoxSizer* boxSizer = new wxBoxSizer(wxVERTICAL);
    dialog.SetSizer(boxSizer);

    wxHtmlWindow* win = new wxHtmlWindow(& dialog, wxID_ANY, wxDefaultPosition, wxSize(500, 400), wxSUNKEN_BORDER);
    boxSizer->Add(win, 1, wxALL, 5);

    wxButton* cancelButton = new wxButton(& dialog, wxID_CANCEL, wxT("&Close"));
    boxSizer->Add(cancelButton, 0, wxALL|wxCENTRE, 5);

    wxString text;
    wxStringOutputStream strStream(& text);

    wxRichTextHTMLHandler htmlHandler;
    htmlHandler.SetFlags(wxRICHTEXT_HANDLER_SAVE_IMAGES_TO_MEMORY);

    wxArrayInt fontSizeMapping;
    fontSizeMapping.Add(7);
    fontSizeMapping.Add(9);
    fontSizeMapping.Add(11);
    fontSizeMapping.Add(12);
    fontSizeMapping.Add(14);
    fontSizeMapping.Add(22);
    fontSizeMapping.Add(100);

    htmlHandler.SetFontSizeMapping(fontSizeMapping);

    if (htmlHandler.SaveFile(& m_editor->GetBuffer(), strStream))
    {
        win->SetPage(text);
    }

    boxSizer->Fit(& dialog);

    dialog.ShowModal();

    // Now delete the temporary in-memory images
    htmlHandler.DeleteTemporaryImages();
}

// Demonstrates how you can change the style sheets and have the changes
// reflected in the control content without wiping out character formatting.

void MainFrame::OnSwitchStyleSheets(wxCommandEvent& WXUNUSED(event))
{
    static wxRichTextStyleSheet* gs_AlternateStyleSheet = NULL;

    wxRichTextStyleListCtrl *styleList = (wxRichTextStyleListCtrl*) FindWindow(ID_RICHTEXT_STYLE_LIST);
    wxRichTextStyleComboCtrl* styleCombo = (wxRichTextStyleComboCtrl*) FindWindow(ID_RICHTEXT_STYLE_COMBO);

    wxRichTextStyleSheet* sheet = m_editor->GetStyleSheet();

    // One-time creation of an alternate style sheet
    if (!gs_AlternateStyleSheet)
    {
        gs_AlternateStyleSheet = new wxRichTextStyleSheet(*sheet);

        // Make some modifications
        for (int i = 0; i < (int) gs_AlternateStyleSheet->GetParagraphStyleCount(); i++)
        {
            wxRichTextParagraphStyleDefinition* def = gs_AlternateStyleSheet->GetParagraphStyle(i);

            if (def->GetStyle().HasTextColour())
                def->GetStyle().SetTextColour(*wxBLUE);

            if (def->GetStyle().HasAlignment())
            {
                if (def->GetStyle().GetAlignment() == wxTEXT_ALIGNMENT_CENTRE)
                    def->GetStyle().SetAlignment(wxTEXT_ALIGNMENT_RIGHT);
                else if (def->GetStyle().GetAlignment() == wxTEXT_ALIGNMENT_LEFT)
                    def->GetStyle().SetAlignment(wxTEXT_ALIGNMENT_CENTRE);
            }
            if (def->GetStyle().HasLeftIndent())
            {
                def->GetStyle().SetLeftIndent(def->GetStyle().GetLeftIndent() * 2);
            }
        }
    }

    // Switch sheets
    wxRichTextStyleSheet* tmp = gs_AlternateStyleSheet;
    gs_AlternateStyleSheet = sheet;
    sheet = tmp;

    m_editor->SetStyleSheet(sheet);
    m_editor->ApplyStyleSheet(sheet); // Makes the control reflect the new style definitions

    styleList->SetStyleSheet(sheet);
    styleList->UpdateStyles();

    styleCombo->SetStyleSheet(sheet);
    styleCombo->UpdateStyles();
}

void MainFrame::OnManageStyles(wxCommandEvent& WXUNUSED(event))
{
    wxRichTextStyleSheet* sheet = m_editor->GetStyleSheet();

    int flags = wxRICHTEXT_ORGANISER_CREATE_STYLES|wxRICHTEXT_ORGANISER_EDIT_STYLES;

    wxRichTextStyleOrganiserDialog dlg(flags, sheet, NULL, this, wxID_ANY, _("Style Manager"));
    dlg.ShowModal();
}

void MainFrame::OnInsertSymbol(wxCommandEvent& WXUNUSED(event))
{
    wxRichTextAttr attr;
    attr.SetFlags(wxTEXT_ATTR_FONT);
    m_editor->GetStyle(m_editor->GetInsertionPoint(), attr);

    wxString currentFontName;
    if (attr.HasFont() && attr.GetFont().IsOk())
        currentFontName = attr.GetFont().GetFaceName();

    // Don't set the initial font in the dialog (so the user is choosing
    // 'normal text', i.e. the current font) but do tell the dialog
    // what 'normal text' is.

    wxSymbolPickerDialog dlg(wxT("*"), wxEmptyString, currentFontName, this);

    if (dlg.ShowModal() == wxID_OK)
    {
        if (dlg.HasSelection())
        {
            long insertionPoint = m_editor->GetInsertionPoint();

            m_editor->WriteText(dlg.GetSymbol());

            if (!dlg.UseNormalFont())
            {
                wxFont font(attr.GetFont());
                font.SetFaceName(dlg.GetFontName());
                attr.SetFont(font);
                m_editor->SetStyle(insertionPoint, insertionPoint+1, attr);
            }
        }
    }
}

void MainFrame::OnNumberList(wxCommandEvent& WXUNUSED(event))
{
    if (m_editor->HasSelection())
    {
        wxRichTextRange range = m_editor->GetSelectionRange();
        m_editor->SetListStyle(range, wxT("Numbered List 1"), wxRICHTEXT_SETSTYLE_WITH_UNDO|wxRICHTEXT_SETSTYLE_RENUMBER);
    }
}

void MainFrame::OnBulletsAndNumbering(wxCommandEvent& WXUNUSED(event))
{
    wxRichTextStyleSheet* sheet = m_editor->GetStyleSheet();

    int flags = wxRICHTEXT_ORGANISER_BROWSE_NUMBERING;

    wxRichTextStyleOrganiserDialog dlg(flags, sheet, m_editor, this, wxID_ANY, _("Bullets and Numbering"));
    if (dlg.ShowModal() == wxID_OK)
    {
        if (dlg.GetSelectedStyleDefinition())
            dlg.ApplyStyle();
    }
}

void MainFrame::OnItemizeList(wxCommandEvent& WXUNUSED(event))
{
    if (m_editor->HasSelection())
    {
        wxRichTextRange range = m_editor->GetSelectionRange();
        m_editor->SetListStyle(range, wxT("Bullet List 1"));
    }
}

void MainFrame::OnRenumberList(wxCommandEvent& WXUNUSED(event))
{
    if (m_editor->HasSelection())
    {
        wxRichTextRange range = m_editor->GetSelectionRange();
        m_editor->NumberList(range, NULL, wxRICHTEXT_SETSTYLE_WITH_UNDO|wxRICHTEXT_SETSTYLE_RENUMBER);
    }
}

void MainFrame::OnPromoteList(wxCommandEvent& WXUNUSED(event))
{
    if (m_editor->HasSelection())
    {
        wxRichTextRange range = m_editor->GetSelectionRange();
        m_editor->PromoteList(1, range, NULL);
    }
}

void MainFrame::OnDemoteList(wxCommandEvent& WXUNUSED(event))
{
    if (m_editor->HasSelection())
    {
        wxRichTextRange range = m_editor->GetSelectionRange();
        m_editor->PromoteList(-1, range, NULL);
    }
}

void MainFrame::OnClearList(wxCommandEvent& WXUNUSED(event))
{
    if (m_editor->HasSelection())
    {
        wxRichTextRange range = m_editor->GetSelectionRange();
        m_editor->ClearListStyle(range);
    }
}

void MainFrame::OnTableAddColumn(wxCommandEvent& WXUNUSED(event))
{
    wxRichTextTable* table = wxDynamicCast(m_editor->FindTable(), wxRichTextTable);
    if (table)
    {
        wxRichTextAttr cellAttr = table->GetCell(0, 0)->GetAttributes();
        table->AddColumns(table->GetColumnCount(), 1, cellAttr);
    }
}

void MainFrame::OnTableAddRow(wxCommandEvent& WXUNUSED(event))
{
    wxRichTextTable* table = wxDynamicCast(m_editor->FindTable(), wxRichTextTable);
    if (table)
    {
        wxRichTextAttr cellAttr = table->GetCell(0, 0)->GetAttributes();
        table->AddRows(table->GetRowCount(), 1, cellAttr);
    }
}

void MainFrame::OnTableDeleteColumn(wxCommandEvent& WXUNUSED(event))
{
    wxRichTextTable* table = wxDynamicCast(m_editor->FindTable(), wxRichTextTable);
    if (table)
    {
        int col = table->GetFocusedCell().GetCol();
        if (col == -1)
        {
            col = table->GetColumnCount() - 1;
        }
            
        table->DeleteColumns(col, 1);
    }
}

void MainFrame::OnTableDeleteRow(wxCommandEvent& WXUNUSED(event))
{
    wxRichTextTable* table = wxDynamicCast(m_editor->FindTable(), wxRichTextTable);
    if (table)
    {
        int row = table->GetFocusedCell().GetRow();
        if (row == -1)
        {
            row = table->GetRowCount() - 1;
        }
            
        table->DeleteRows(row, 1);
    }
}

void MainFrame::OnTableFocusedUpdateUI(wxUpdateUIEvent& event)
{
    event.Enable(m_editor->FindTable() != NULL);
}

void MainFrame::OnTableHasCellsUpdateUI(wxUpdateUIEvent& event)
{
    bool enable(false);
    wxRichTextTable* table = wxDynamicCast(m_editor->FindTable(), wxRichTextTable);
    if (table)
    {
        if (event.GetId() == ID_TABLE_DELETE_COLUMN)
        {
            enable = table->GetColumnCount() > 1;
        }
        else
        {
            enable = table->GetRowCount() > 1;
        }
    }

    event.Enable(enable);
}

void MainFrame::OnInsertURL(wxCommandEvent& WXUNUSED(event))
{
    wxString url = wxGetTextFromUser(_("URL:"), _("Insert URL"));
    if (!url.IsEmpty())
    {
        // Make a style suitable for showing a URL
        wxRichTextAttr urlStyle;
        urlStyle.SetTextColour(*wxBLUE);
        urlStyle.SetFontUnderlined(true);

        m_editor->BeginStyle(urlStyle);
        m_editor->BeginURL(url);
        m_editor->WriteText(url);
        m_editor->EndURL();
        m_editor->EndStyle();
    }
}

void MainFrame::OnInsertImage(wxCommandEvent& WXUNUSED(event))
{
    wxFileDialog dialog(this, _("Choose an image"), "", "", "BMP and GIF files (*.bmp;*.gif)|*.bmp;*.gif|PNG files (*.png)|*.png|JPEG files (*.jpg;*.jpeg)|*.jpg;*.jpeg");
    if (dialog.ShowModal() == wxID_OK)
    {
        wxString path = dialog.GetPath();
        wxImage image;
        if (image.LoadFile(path) && image.GetType() != wxBITMAP_TYPE_INVALID)
            m_editor->WriteImage(path, image.GetType());
    }
}

void MainFrame::OnURL(wxTextUrlEvent& event)
{
    wxMessageBox(event.GetString());
}

// Veto style sheet replace events when loading from XML, since we want
// to keep the original style sheet.
void MainFrame::OnStyleSheetReplacing(wxRichTextEvent& event)
{
    event.Veto();
}

#if wxUSE_PRINTING_ARCHITECTURE
void MainFrame::OnPrint(wxCommandEvent& WXUNUSED(event))
{
    wxGetApp().GetPrinting()->PrintBuffer(m_editor->GetBuffer());
}

void MainFrame::OnPreview(wxCommandEvent& WXUNUSED(event))
{
    wxGetApp().GetPrinting()->PreviewBuffer(m_editor->GetBuffer());
}
#endif

void MainFrame::OnPageSetup(wxCommandEvent& WXUNUSED(event))
{
    wxDialog dialog(this, wxID_ANY, wxT("Testing"), wxPoint(10, 10), wxSize(400, 300), wxDEFAULT_DIALOG_STYLE);

    wxNotebook* nb = new wxNotebook(& dialog, wxID_ANY, wxPoint(5, 5), wxSize(300, 250));
    wxPanel* panel = new wxPanel(nb, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    wxPanel* panel2 = new wxPanel(nb, wxID_ANY, wxDefaultPosition, wxDefaultSize);

    new wxRichTextCtrl(panel, wxID_ANY, wxEmptyString, wxPoint(5, 5), wxSize(200, 150), wxVSCROLL|wxTE_READONLY);
    nb->AddPage(panel, wxT("Page 1"));

    new wxRichTextCtrl(panel2, wxID_ANY, wxEmptyString, wxPoint(5, 5), wxSize(200, 150), wxVSCROLL|wxTE_READONLY);
    nb->AddPage(panel2, wxT("Page 2"));

    new wxButton(& dialog, wxID_OK, wxT("OK"), wxPoint(5, 180));

    dialog.ShowModal();

//    wxGetApp().GetPrinting()->PageSetup();
}

void MainFrame::OnSetFontScale(wxCommandEvent& WXUNUSED(event))
{
    wxString value = wxString::Format(wxT("%g"), m_editor->GetFontScale());
    wxString text = wxGetTextFromUser(wxT("Enter a text scale factor:"), wxT("Text Scale Factor"), value, wxGetTopLevelParent(this));
    if (!text.IsEmpty() && value != text)
    {
        double scale = 1.0;
        wxSscanf(text, wxT("%lf"), & scale);
        m_editor->SetFontScale(scale, true);
    }
}

void MainFrame::OnSetDimensionScale(wxCommandEvent& WXUNUSED(event))
{
    wxString value = wxString::Format(wxT("%g"), m_editor->GetDimensionScale());
    wxString text = wxGetTextFromUser(wxT("Enter a dimension scale factor:"), wxT("Dimension Scale Factor"), value, wxGetTopLevelParent(this));
    if (!text.IsEmpty() && value != text)
    {
        double scale = 1.0;
        wxSscanf(text, wxT("%lf"), & scale);
        m_editor->SetDimensionScale(scale, true);
    }
}
