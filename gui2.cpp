#include "gui2.h"

#include "main.h"


DECLARE_APP(MainApp)

///////////////////////////////////////////////////////////////////////////
// ----------------------------------------------------------------------------
// constants
// ----------------------------------------------------------------------------

// IDs for the controls and the menu commands
enum
{
    // menu items
    ID_FORMAT_BOLD = 100,
    ID_FORMAT_ITALIC,
    ID_FORMAT_UNDERLINE,
    ID_FORMAT_STRIKETHROUGH,
    ID_FORMAT_SUPERSCRIPT,
    ID_FORMAT_SUBSCRIPT,
    ID_FORMAT_CONTENT,
    ID_FORMAT_FONT,
    ID_FORMAT_PARAGRAPH,
    ID_FORMAT_IMAGE,

    ID_RELOAD,
    ID_DELETE_DATE,

//    ID_UNDO,
//    ID_REDO,
    
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
    
    ID_HIERACHY,
    
    ID_FAVORITE_LIST,
    
    ID_FAVORITE_ADD,
    ID_FAVORITE_DELETE, 
    ID_FAVORITE_GO,
    ID_FAVORITE_MANAGE, 
    
    ID_STAY_ON_TOP,
    
    ID_FOCUS_FAVORITES,
};

// BEGIN EVENTS

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
    helpMenu->Append(wxID_ABOUT, _("&About\tF1"), _("Show about dialog")); 
    helpMenu->AppendSeparator();
    helpMenu->AppendCheckItem(ID_STAY_ON_TOP, _("&Stay on top\tF11"), _("Stay on top")); 
    helpMenu->Enable(ID_STAY_ON_TOP, false); //car non implementé
    helpMenu->Append(ID_FOCUS_FAVORITES, _("&Favorites List\tF5"), _("Focus to Favorites List")); 
//    helpMenu->AppendSeparator(); //todo à implémenter ?
//    helpMenu->AppendRadioItem(ID_LANG_FR, wxT("Français"), _("Set french language")); 
//    helpMenu->AppendRadioItem(ID_LANG_EN, wxT("English"), _("Set english language")); 
    
    fileMenu->Append(wxID_OPEN, _("&Open\tCtrl+O"), _("Open a file")); 
    fileMenu->Enable(wxID_OPEN, false);
    fileMenu->Append(wxID_SAVE, _("&Save\tCtrl+S"), _("Save the work")); 
    fileMenu->Append(wxID_SAVEAS, _("Save As...\tF12"), _("Save to a new file")); //
    
    fileMenu->AppendSeparator();
    fileMenu->AppendCheckItem(ID_HIERACHY, _("&Hierarchical Tree"), _("Toggle Simple/Hierarchical Tree"));
    fileMenu->Check(ID_HIERACHY, wxGetApp().IsHierarchicalTree());        
    fileMenu->AppendSeparator();
    fileMenu->Append(ID_RELOAD, _("&Reload\tF2"), _("Reload the file/tree"));
   // fileMenu->SetBitmap....
    fileMenu->AppendSeparator();
    fileMenu->Append(ID_PAGE_SETUP, _("Page Set&up..."), _("Page setup"));
#if USE_RICH_EDIT
    fileMenu->AppendSeparator();
    fileMenu->Append(ID_VIEW_HTML, _("View as HT&ML"), _("View HTML")); 
#endif // USE_RICH_EDIT 
    fileMenu->AppendSeparator();
    fileMenu->Append(wxID_EXIT, _("E&xit\tAlt+X"), _("Quit this program")); 

    wxMenu* editMenu = new wxMenu;
    editMenu->Append(ID_DELETE_DATE, _("&Delete date\tCtrl+D")); 
    editMenu->AppendSeparator();
    editMenu->Append(wxID_UNDO, _("&Undo\tCtrl+Z")); 
    editMenu->Append(wxID_REDO, _("&Redo\tCtrl+Y")); 
    editMenu->AppendSeparator();
    editMenu->Append(wxID_CUT, _("Cu&t\tCtrl+X")); 
    editMenu->Append(wxID_COPY, _("&Copy\tCtrl+C")); 
    editMenu->Append(wxID_PASTE, _("&Paste\tCtrl+V")); 

#if USE_RICH_EDIT
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
#endif // USE_RICH_EDIT

    wxMenu* favoriteMenu = new wxMenu;
    favoriteMenu->Append(ID_FAVORITE_GO, _("&Insert\tF6"), _("Insert selected favorite"));
    favoriteMenu->AppendSeparator();
    favoriteMenu->Append(ID_FAVORITE_ADD, _("&Add"), _("Add selected text to favorites"));
    favoriteMenu->Append(ID_FAVORITE_DELETE, _("&Delete"), _("Delete selected favorite"));
    favoriteMenu->Append(ID_FAVORITE_MANAGE, _("&Manage"), _("Manage favorites"));
    
    // now append the freshly created menu to the menu bar...
    m_menuBar = new wxMenuBar();
    m_menuBar->Append(fileMenu, _("&File")); 
    m_menuBar->Append(editMenu, _("&Edit")); 
#if USE_RICH_EDIT
    m_menuBar->Append(formatMenu, _("F&ormat")); 
    m_menuBar->Append(listsMenu, _("&Lists")); 
    m_menuBar->Append(tableMenu, _("&Tables")); 
    m_menuBar->Append(insertMenu, _("&Insert")); 
#endif // USE_RICH_EDIT
    m_menuBar->Append(favoriteMenu, _("Fa&vorites")); 
    m_menuBar->Append(helpMenu, _("&Help")); 

    // ... and attach this menu bar to the frame
    SetMenuBar(m_menuBar);

    // create a status bar just for fun (by default with 1 pane only)
    // but don't create it on limited screen space (WinCE)
    bool is_pda = wxSystemSettings::GetScreenType() <= wxSYS_SCREEN_PDA;

#if wxUSE_STATUSBAR
    if ( !is_pda )
    {
        m_statusBar = CreateStatusBar(1);
        SetStatusText(_("Welcome to Dailywork!")); 
    }
#endif

	wxBoxSizer* mainSizer;
	mainSizer = new wxBoxSizer( wxHORIZONTAL );
	
 	wxBoxSizer* datesSizer;
	datesSizer = new wxBoxSizer( wxVERTICAL );
	
	m_treeDates = new wxTreeCtrl( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTR_DEFAULT_STYLE );
	datesSizer->Add( m_treeDates, 1, wxALL|wxEXPAND, 2 );
	
	m_calendar = new wxCalendarCtrl( this, wxID_ANY, wxDefaultDateTime, wxDefaultPosition, wxDefaultSize, wxCAL_SHOW_HOLIDAYS );
	datesSizer->Add( m_calendar, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 2 );
	
	mainSizer->Add( datesSizer, 0, wxEXPAND, 2 );
    
	wxBoxSizer* editorSizer;
	editorSizer = new wxBoxSizer( wxVERTICAL );
	
	m_buttonGoNextAvailable = new wxButton( this, wxID_ANY, _("Go to the next available date"), wxDefaultPosition, wxDefaultSize, 0 );
	editorSizer->Add( m_buttonGoNextAvailable, 0, wxEXPAND | wxALL, 2 );
	
	m_buttonAddTomorrow = new wxButton( this, wxID_ANY, _("Add Tomorrow"), wxDefaultPosition, wxDefaultSize, 0 );
	editorSizer->Add( m_buttonAddTomorrow, 0, wxEXPAND | wxALL, 2 );

    CreateEditor();
    
    editorSizer->Add( m_editor, 1, wxEXPAND | wxALL, 2 );
        
	m_buttonAddYesterday = new wxButton( this, wxID_ANY, _("Add Yesterday"), wxDefaultPosition, wxDefaultSize, 0 );
	editorSizer->Add( m_buttonAddYesterday, 0, wxEXPAND | wxALL, 2 );
	
	m_buttonGoPrevAvailable = new wxButton( this, wxID_ANY, _("Go to the preivous available date"), wxDefaultPosition, wxDefaultSize, 0 );
	editorSizer->Add( m_buttonGoPrevAvailable, 0, wxEXPAND | wxALL, 2 );
    
		
	mainSizer->Add( editorSizer, 1, wxEXPAND, 2 );     //mainSizer->Add( m_editor, 1, wxEXPAND | wxALL, 5 );

	
	this->SetSizer( mainSizer );
	this->Layout();

	//m_statusBar = this->CreateStatusBar( 1, wxST_SIZEGRIP, wxID_ANY );
    // On Mac, don't create a 'native' wxToolBar because small bitmaps are not supported by native
    // toolbars. On Mac, a non-native, small-bitmap toolbar doesn't show unless it is explicitly
    // managed, hence the use of sizers. In a real application, use larger icons for the main
    // toolbar to avoid the need for this workaround. Or, use the toolbar in a container window
    // as part of a more complex hierarchy, and the toolbar will automatically be non-native.

    wxSystemOptions::SetOption(wxT("mac.toolbar.no-native"), 1);

 	m_mainToolBar = this->CreateToolBar( wxTB_HORIZONTAL, wxID_ANY ); 
  //  wxToolBar* m_mainToolBar = new wxToolBar(this, wxID_ANY, wxDefaultPosition, wxDefaultSize,
  //                                    wxNO_BORDER|wxTB_FLAT|wxTB_NODIVIDER|wxTB_NOALIGN);
  //  mainSizer->Add(m_mainToolBar, 0, wxEXPAND);

//    m_mainToolBar->AddTool(wxID_OPEN, wxEmptyString, wxBitmap(open_xpm), _("Open"));
    m_mainToolBar->AddTool(ID_RELOAD, wxEmptyString, wxBitmap(reload_xpm), _("Reload")); 
    
    m_mainToolBar->AddTool(wxID_SAVE, wxEmptyString, wxBitmap(save_xpm), _("Save")); 
    m_mainToolBar->AddSeparator();
    m_mainToolBar->AddTool(ID_DELETE_DATE, wxEmptyString, wxBitmap(delete_xpm), _("Delete date")); 
    m_mainToolBar->AddSeparator();
    m_mainToolBar->AddTool(wxID_CUT, wxEmptyString, wxBitmap(cut_xpm), _("Cut")); 
    m_mainToolBar->AddTool(wxID_COPY, wxEmptyString, wxBitmap(copy_xpm), _("Copy")); 
    m_mainToolBar->AddTool(wxID_PASTE, wxEmptyString, wxBitmap(paste_xpm), _("Paste")); 
    m_mainToolBar->AddSeparator();
    m_mainToolBar->AddTool(wxID_UNDO, wxEmptyString, wxBitmap(undo_xpm), _("Undo")); 
    m_mainToolBar->AddTool(wxID_REDO, wxEmptyString, wxBitmap(redo_xpm), _("Redo"));
#if USE_RICH_EDIT
    m_mainToolBar->AddSeparator();
    m_mainToolBar->AddCheckTool(ID_FORMAT_BOLD, wxEmptyString, wxBitmap(bold_xpm), wxNullBitmap, _("Bold")); 
    m_mainToolBar->AddCheckTool(ID_FORMAT_ITALIC, wxEmptyString, wxBitmap(italic_xpm), wxNullBitmap, _("Italic")); 
    m_mainToolBar->AddCheckTool(ID_FORMAT_UNDERLINE, wxEmptyString, wxBitmap(underline_xpm), wxNullBitmap, _("Underline")); 
    m_mainToolBar->AddSeparator();
    m_mainToolBar->AddCheckTool(ID_FORMAT_ALIGN_LEFT, wxEmptyString, wxBitmap(alignleft_xpm), wxNullBitmap, _("Align Left")); //Aligner à gauche
    m_mainToolBar->AddCheckTool(ID_FORMAT_ALIGN_CENTRE, wxEmptyString, wxBitmap(centre_xpm), wxNullBitmap, _("Centre")); //Centrer
    m_mainToolBar->AddCheckTool(ID_FORMAT_ALIGN_RIGHT, wxEmptyString, wxBitmap(alignright_xpm), wxNullBitmap, _("Align Right")); //Aligner à droite
    m_mainToolBar->AddSeparator();
    m_mainToolBar->AddTool(ID_FORMAT_INDENT_LESS, wxEmptyString, wxBitmap(indentless_xpm), _("Indent Less")); //Réduire le retrait
    m_mainToolBar->AddTool(ID_FORMAT_INDENT_MORE, wxEmptyString, wxBitmap(indentmore_xpm), _("Indent More")); //Augmenter le retrait
    m_mainToolBar->AddSeparator();
    m_mainToolBar->AddTool(ID_FORMAT_FONT, wxEmptyString, wxBitmap(font_xpm), _("Font")); //Police
#endif // USE_RICH_EDIT
    
    m_mainToolBar->AddSeparator();
    m_comboBoxFavorite = new wxComboBox(m_mainToolBar, ID_FAVORITE_LIST, wxEmptyString, wxDefaultPosition, wxSize(150,-1));
    m_comboBoxFavorite->SetHint(_("Favorites"));
    m_mainToolBar->AddControl(m_comboBoxFavorite);

    m_mainToolBar->AddTool(ID_FAVORITE_GO, wxEmptyString, wxBitmap(bookgo_xpm), _("Insert favorite")); //Inserer favoris
    m_mainToolBar->AddTool(ID_FAVORITE_MANAGE, wxEmptyString, wxBitmap(bookedit_xpm), _("Manage favorites")); //Gerer les favoris
    m_mainToolBar->AddTool(ID_FAVORITE_ADD, wxEmptyString, wxBitmap(bookadd_xpm), _("Add to favorites")); //Ajouter aux favoris
    m_mainToolBar->AddTool(ID_FAVORITE_DELETE, wxEmptyString, wxBitmap(bookdelete_xpm), _("Delete favorite")); //Supprimer favoris
    m_mainToolBar->Realize();

	this->Centre( wxBOTH );

    //WriteInitialText();
 
#if USE_RICH_EDIT
    // désactive les options de mise en forme du text parceque pas de lecture de fichier rtf...
    m_menuBar->EnableTop(2, false); //formatMenu
    m_menuBar->EnableTop(3, false); //listsMenu
    m_menuBar->EnableTop(4, false); //tableMenu
    m_menuBar->EnableTop(5, false); //insertMenu
    m_mainToolBar->EnableTool(ID_FORMAT_BOLD, false);
    m_mainToolBar->EnableTool(ID_FORMAT_ITALIC, false);
    m_mainToolBar->EnableTool(ID_FORMAT_UNDERLINE, false);
    m_mainToolBar->EnableTool(ID_FORMAT_ALIGN_LEFT, false);
    m_mainToolBar->EnableTool(ID_FORMAT_ALIGN_CENTRE, false);
    m_mainToolBar->EnableTool(ID_FORMAT_ALIGN_RIGHT, false);
    m_mainToolBar->EnableTool(ID_FORMAT_INDENT_LESS, false);
    m_mainToolBar->EnableTool(ID_FORMAT_INDENT_MORE, false);
    m_mainToolBar->EnableTool(ID_FORMAT_FONT, false);
    m_mainToolBar->EnableTool(ID_FORMAT_FONT, false); 
#endif // USE_RICH_EDIT

    ConnectEvents();
}   
 
MainFrame::~MainFrame()
{
    DisconnectEvents();	
}

void MainFrame::CreateEditor()
{    
#if USE_RICH_EDIT
    wxFont textFont = wxFont(12, wxROMAN, wxNORMAL, wxNORMAL);
    wxFont boldFont = wxFont(12, wxROMAN, wxNORMAL, wxBOLD);
    wxFont italicFont = wxFont(12, wxROMAN, wxITALIC, wxNORMAL);

    m_editor = new MyRichTextCtrl(this, ID_RICHTEXT_CTRL, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxVSCROLL|wxHSCROLL/*|wxWANTS_CHARS*/);
    wxASSERT(!m_editor->GetBuffer().GetAttributes().HasFontPixelSize());
    wxFont font(12, wxROMAN, wxNORMAL, wxNORMAL);
    m_editor->SetFont(font);
    wxASSERT(!m_editor->GetBuffer().GetAttributes().HasFontPixelSize());
    m_editor->SetStyleSheet(wxGetApp().GetStyleSheet()); 
#else
    //m_editor = new  wxTextCtrl(this, wxID_ANY, wxT(""), wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER | wxTE_MULTILINE);
    m_editor = new MyStyledTextCtrl(this);
#endif  // USE_RICH_EDIT
    m_editor->SetMargins(5, 5);
}

void MainFrame::ConnectEvents()
{
    //todo prevenir wxEVT_TREE_SEL_CHANGING au demarage connection fait aprés chargement  dwparser 
	m_treeDates->Bind( wxEVT_TREE_SEL_CHANGED, &MainFrame::OnTreeSelChanged, this );
	m_treeDates->Bind( wxEVT_TREE_SEL_CHANGING, &MainFrame::OnTreeSelChanging, this );    
    m_treeDates->Bind( wxEVT_TREE_ITEM_RIGHT_CLICK, &MainFrame::OnTreeRightClick, this );
	m_calendar->Bind( wxEVT_CALENDAR_SEL_CHANGED, &MainFrame::OnCalendarSelChanged, this );
    m_calendar->Bind( wxEVT_KILL_FOCUS, &MainFrame::OnCalendarKillFocus, this );
	m_calendar->Bind( wxEVT_SET_FOCUS,  &MainFrame::OnCalendarSetFocus, this );
    m_calendar->Bind( wxEVT_CALENDAR_DOUBLECLICKED, &MainFrame::OnCalendarDblClick, this );
    m_buttonGoNextAvailable->Bind( wxEVT_COMMAND_BUTTON_CLICKED,  &MainFrame::OnButtonGoNextAvailableClick, this);
    m_buttonGoPrevAvailable->Bind( wxEVT_COMMAND_BUTTON_CLICKED,  &MainFrame::OnButtonGoPrevAvailableClick, this);
    m_buttonAddTomorrow->Bind( wxEVT_COMMAND_BUTTON_CLICKED,  &MainFrame::OnButtonAddTomorrowClick, this);
    m_buttonAddYesterday->Bind( wxEVT_COMMAND_BUTTON_CLICKED,  &MainFrame::OnButtonAddYesterdayClick, this);
    
    Bind(wxEVT_CLOSE_WINDOW, &MainFrame::OnCloseFrame, this);
    Bind(wxEVT_COMMAND_MENU_SELECTED,  &MainFrame::OnQuit, this, wxID_EXIT);
    Bind(wxEVT_COMMAND_MENU_SELECTED,  &MainFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_COMMAND_MENU_SELECTED,  &MainFrame::OnStayOnTop, this, ID_STAY_ON_TOP);

    Bind(wxEVT_COMMAND_MENU_SELECTED,  &MainFrame::OnOpen, this, wxID_OPEN);
    Bind(wxEVT_COMMAND_MENU_SELECTED,  &MainFrame::OnSave, this, wxID_SAVE);
    Bind(wxEVT_COMMAND_MENU_SELECTED,  &MainFrame::OnSaveAs, this, wxID_SAVEAS);
    
    Bind(wxEVT_COMMAND_MENU_SELECTED,  &MainFrame::OnShowHirerarchicalTree, this, ID_HIERACHY);
 
    Bind(wxEVT_COMMAND_MENU_SELECTED,  &MainFrame::OnReload, this, ID_RELOAD);
    Bind(wxEVT_COMMAND_MENU_SELECTED,  &MainFrame::OnDeleteDate, this, ID_DELETE_DATE);

#if USE_RICH_EDIT
    Bind(wxEVT_COMMAND_MENU_SELECTED,  &MainFrame::OnBold, this, ID_FORMAT_BOLD);
    Bind(wxEVT_COMMAND_MENU_SELECTED,  &MainFrame::OnItalic, this, ID_FORMAT_ITALIC);
    Bind(wxEVT_COMMAND_MENU_SELECTED,  &MainFrame::OnUnderline, this, ID_FORMAT_UNDERLINE);

    Bind(wxEVT_COMMAND_MENU_SELECTED,  &MainFrame::OnStrikethrough, this, ID_FORMAT_STRIKETHROUGH);
    Bind(wxEVT_COMMAND_MENU_SELECTED,  &MainFrame::OnSuperscript, this, ID_FORMAT_SUPERSCRIPT);
    Bind(wxEVT_COMMAND_MENU_SELECTED,  &MainFrame::OnSubscript, this, ID_FORMAT_SUBSCRIPT);

    Bind(wxEVT_UPDATE_UI,  &MainFrame::OnUpdateItalic, this, ID_FORMAT_ITALIC);
    Bind(wxEVT_UPDATE_UI,  &MainFrame::OnUpdateUnderline, this, ID_FORMAT_UNDERLINE);

    Bind(wxEVT_UPDATE_UI,  &MainFrame::OnUpdateStrikethrough, this, ID_FORMAT_STRIKETHROUGH);
    Bind(wxEVT_UPDATE_UI,  &MainFrame::OnUpdateSuperscript, this, ID_FORMAT_SUPERSCRIPT);
    Bind(wxEVT_UPDATE_UI,  &MainFrame::OnUpdateSubscript, this, ID_FORMAT_SUBSCRIPT);

    Bind(wxEVT_COMMAND_MENU_SELECTED,  &MainFrame::OnAlignLeft, this, ID_FORMAT_ALIGN_LEFT);
    Bind(wxEVT_COMMAND_MENU_SELECTED,  &MainFrame::OnAlignCentre, this, ID_FORMAT_ALIGN_CENTRE);
    Bind(wxEVT_COMMAND_MENU_SELECTED,  &MainFrame::OnAlignRight, this, ID_FORMAT_ALIGN_RIGHT);

    Bind(ID_FORMAT_ALIGN_LEFT, wxEVT_UPDATE_UI,  &MainFrame::OnUpdateAlignLeft, this, );
    Bind(ID_FORMAT_ALIGN_CENTRE, wxEVT_UPDATE_UI,  &MainFrame::OnUpdateAlignCentre, this, );
    Bind(ID_FORMAT_ALIGN_RIGHT, wxEVT_UPDATE_UI,  &MainFrame::OnUpdateAlignRight, this, );

    Bind(wxEVT_COMMAND_MENU_SELECTED,  &MainFrame::OnFont, this, ID_FORMAT_FONT);
    Bind(wxEVT_COMMAND_MENU_SELECTED,  &MainFrame::OnImage, this, ID_FORMAT_IMAGE);
    Bind(wxEVT_COMMAND_MENU_SELECTED,  &MainFrame::OnParagraph, this, ID_FORMAT_PARAGRAPH);
    Bind(wxEVT_COMMAND_MENU_SELECTED,  &MainFrame::OnFormat, this, ID_FORMAT_CONTENT);
    Bind(wxEVT_UPDATE_UI,  &MainFrame::OnUpdateFormat, this, ID_FORMAT_CONTENT, ID_FORMAT_PARAGRAPH);
    //Bind(wxEVT_UPDATE_UI,  wxUpdateUIEventHandler(MainFrame::OnUpdateFormat, this, ID_FORMAT_FONT);
    //Bind(wxEVT_UPDATE_UI,  wxUpdateUIEventHandler(MainFrame::OnUpdateFormat, this, ID_FORMAT_PARAGRAPH);
    Bind(wxEVT_UPDATE_UI,  &MainFrame::OnUpdateImage, this, ID_FORMAT_IMAGE);

    Bind(ID_FORMAT_INDENT_MORE, wxEVT_COMMAND_MENU_SELECTED,  &MainFrame::OnIndentMore, this, );
    Bind(ID_FORMAT_INDENT_LESS, wxEVT_COMMAND_MENU_SELECTED,  &MainFrame::OnIndentLess, this, );

    Bind(wxEVT_COMMAND_MENU_SELECTED,  &MainFrame::OnLineSpacingHalf, this, ID_FORMAT_LINE_SPACING_HALF);
    Bind(wxEVT_COMMAND_MENU_SELECTED,  &MainFrame::OnLineSpacingSingle, this, ID_FORMAT_LINE_SPACING_SINGLE);
    Bind(wxEVT_COMMAND_MENU_SELECTED,  &MainFrame::OnLineSpacingDouble, this, ID_FORMAT_LINE_SPACING_DOUBLE);

    Bind(wxEVT_COMMAND_MENU_SELECTED,  &MainFrame::OnParagraphSpacingMore, this, ID_FORMAT_PARAGRAPH_SPACING_MORE);
    Bind(wxEVT_COMMAND_MENU_SELECTED,  &MainFrame::OnParagraphSpacingLess, this, ID_FORMAT_PARAGRAPH_SPACING_LESS);

    Bind(wxEVT_COMMAND_MENU_SELECTED,  &MainFrame::OnInsertSymbol, this, ID_INSERT_SYMBOL);
    Bind(wxEVT_COMMAND_MENU_SELECTED,  &MainFrame::OnInsertURL, this, ID_INSERT_URL);
    Bind(wxEVT_COMMAND_MENU_SELECTED,  &MainFrame::OnInsertImage, this, ID_INSERT_IMAGE);

    Bind(wxEVT_COMMAND_MENU_SELECTED,  &MainFrame::OnNumberList, this, ID_FORMAT_NUMBER_LIST);
    Bind(wxEVT_COMMAND_MENU_SELECTED,  &MainFrame::OnBulletsAndNumbering, this, ID_FORMAT_BULLETS_AND_NUMBERING);
    Bind(wxEVT_COMMAND_MENU_SELECTED,  &MainFrame::OnItemizeList, this, ID_FORMAT_ITEMIZE_LIST);
    Bind(wxEVT_COMMAND_MENU_SELECTED,  &MainFrame::OnRenumberList, this, ID_FORMAT_RENUMBER_LIST);
    Bind(wxEVT_COMMAND_MENU_SELECTED,  &MainFrame::OnPromoteList, this, ID_FORMAT_PROMOTE_LIST);
    Bind(wxEVT_COMMAND_MENU_SELECTED,  &MainFrame::OnDemoteList, this, ID_FORMAT_DEMOTE_LIST);
    Bind(wxEVT_COMMAND_MENU_SELECTED,  &MainFrame::OnClearList, this, ID_FORMAT_CLEAR_LIST);
    Bind(wxEVT_COMMAND_MENU_SELECTED,  &MainFrame::OnTableAddColumn, this, ID_TABLE_ADD_COLUMN);
    Bind(wxEVT_COMMAND_MENU_SELECTED,  &MainFrame::OnTableAddRow, this, ID_TABLE_ADD_ROW);
    Bind(wxEVT_COMMAND_MENU_SELECTED,  &MainFrame::OnTableDeleteColumn, this, ID_TABLE_DELETE_COLUMN);
    Bind(wxEVT_COMMAND_MENU_SELECTED,  &MainFrame::OnTableDeleteRow, this, ID_TABLE_DELETE_ROW);

    Bind(wxEVT_UPDATE_UI,  &MainFrame::OnTableFocusedUpdateUI, this, ID_TABLE_ADD_COLUMN, ID_TABLE_ADD_ROW);
    Bind(wxEVT_UPDATE_UI,  &MainFrame::OnTableHasCellsUpdateUI, this, ID_TABLE_DELETE_COLUMN, ID_TABLE_DELETE_ROW);
//    Bind(wxEVT_UPDATE_UI,  &MainFrame::OnTableHasCellsUpdateUI, this, ID_TABLE_DELETE_ROW);

    Bind(wxEVT_COMMAND_MENU_SELECTED,  &MainFrame::OnViewHTML, this, ID_VIEW_HTML);
    Bind(wxEVT_COMMAND_MENU_SELECTED,  &MainFrame::OnSwitchStyleSheets, this, ID_SWITCH_STYLE_SHEETS);
    Bind(wxEVT_COMMAND_MENU_SELECTED,  &MainFrame::OnManageStyles, this, ID_MANAGE_STYLES);

    Bind(wxEVT_TEXT_URL,  &MainFrame::OnURL, this, wxID_ANY);
    Bind(wxEVT_RICHTEXT_STYLESHEET_REPLACING,  &MainFrame::OnStyleSheetReplacing, this, wxID_ANY);
    Bind(wxEVT_COMMAND_MENU_SELECTED,  &MainFrame::OnSetFontScale, this, ID_SET_FONT_SCALE);
    Bind(wxEVT_COMMAND_MENU_SELECTED,  &MainFrame::OnSetDimensionScale, this, ID_SET_DIMENSION_SCALE);
    
#else
    Bind(wxEVT_UPDATE_UI,  &MainFrame::OnUpdateUndo, this, wxID_UNDO);
    Bind(wxEVT_UPDATE_UI,  &MainFrame::OnUpdateRedo, this, wxID_REDO);
#endif

//    m_comboBoxFavorite->Connect(wxEVT_TEXT_ENTER, wxCommandEventHandler(MainFrame::OnComboFavoriteTextEnter));
//    Connect(wxID_ANY, wxEVT_TEXT, wxTextEventHandler(MainFrame::OnComboFavoriteUpdate));
//    Connect(wxID_ANY, wxEVT_TEXT_ENTER, wxTextEventHandler(MainFrame::OnComboFavoriteUpdate));
//    Connect(wxID_ANY, wxEVT_COMBOBOX, wxCommandEventHandler(MainFrame::OnComboFavoriteUpdate));

    Bind(wxEVT_COMMAND_MENU_SELECTED,  &MainFrame::OnAddFavorite, this, ID_FAVORITE_ADD);
    Bind(wxEVT_COMMAND_MENU_SELECTED,  &MainFrame::OnDeleteFavorite, this, ID_FAVORITE_DELETE);
    Bind(wxEVT_COMMAND_MENU_SELECTED,  &MainFrame::OnManageFavorite, this, ID_FAVORITE_MANAGE);
    Bind(wxEVT_COMMAND_MENU_SELECTED,  &MainFrame::OnGoFavorite, this, ID_FAVORITE_GO);
    Bind(wxEVT_UPDATE_UI,  &MainFrame::OnUpdateAddFavorite, this, ID_FAVORITE_ADD);
    Bind(wxEVT_UPDATE_UI,  &MainFrame::OnUpdateDeleteFavorite, this, ID_FAVORITE_DELETE);
    Bind(wxEVT_UPDATE_UI,  &MainFrame::OnUpdateGoFavorite, this, ID_FAVORITE_GO);
    
    Bind(wxEVT_COMMAND_MENU_SELECTED,  &MainFrame::OnFocusComboFavorite, this, ID_FOCUS_FAVORITES);   
 }

void MainFrame::DisconnectEvents()
{
	m_treeDates->Unbind( wxEVT_TREE_SEL_CHANGED, &MainFrame::OnTreeSelChanged, this );
	m_treeDates->Unbind( wxEVT_TREE_SEL_CHANGING, &MainFrame::OnTreeSelChanging, this );    
    m_treeDates->Unbind( wxEVT_TREE_ITEM_RIGHT_CLICK, &MainFrame::OnTreeRightClick, this );
	m_calendar->Unbind( wxEVT_CALENDAR_SEL_CHANGED, &MainFrame::OnCalendarSelChanged, this );
    m_calendar->Unbind( wxEVT_KILL_FOCUS, &MainFrame::OnCalendarKillFocus, this );
	m_calendar->Unbind( wxEVT_SET_FOCUS,  &MainFrame::OnCalendarSetFocus, this );
    m_calendar->Unbind( wxEVT_CALENDAR_DOUBLECLICKED, &MainFrame::OnCalendarDblClick, this );
    m_buttonGoNextAvailable->Unbind( wxEVT_COMMAND_BUTTON_CLICKED,  &MainFrame::OnButtonGoNextAvailableClick, this);
    m_buttonGoPrevAvailable->Unbind( wxEVT_COMMAND_BUTTON_CLICKED,  &MainFrame::OnButtonGoPrevAvailableClick, this);
    m_buttonAddTomorrow->Unbind( wxEVT_COMMAND_BUTTON_CLICKED,  &MainFrame::OnButtonAddTomorrowClick, this);
    m_buttonAddYesterday->Unbind( wxEVT_COMMAND_BUTTON_CLICKED,  &MainFrame::OnButtonAddYesterdayClick, this);
    
    Unbind(wxEVT_CLOSE_WINDOW, &MainFrame::OnCloseFrame, this);
    Unbind(wxEVT_COMMAND_MENU_SELECTED,  &MainFrame::OnQuit, this, wxID_EXIT);
    Unbind(wxEVT_COMMAND_MENU_SELECTED,  &MainFrame::OnAbout, this, wxID_ABOUT);
    Unbind(wxEVT_COMMAND_MENU_SELECTED,  &MainFrame::OnStayOnTop, this, ID_STAY_ON_TOP);

    Unbind(wxEVT_COMMAND_MENU_SELECTED,  &MainFrame::OnOpen, this, wxID_OPEN);
    Unbind(wxEVT_COMMAND_MENU_SELECTED,  &MainFrame::OnSave, this, wxID_SAVE);
    Unbind(wxEVT_COMMAND_MENU_SELECTED,  &MainFrame::OnSaveAs, this, wxID_SAVEAS);
    
    Unbind(wxEVT_COMMAND_MENU_SELECTED,  &MainFrame::OnShowHirerarchicalTree, this, ID_HIERACHY);
 
    Unbind(wxEVT_COMMAND_MENU_SELECTED,  &MainFrame::OnReload, this, ID_RELOAD);
    Unbind(wxEVT_COMMAND_MENU_SELECTED,  &MainFrame::OnDeleteDate, this, ID_DELETE_DATE);

#if USE_RICH_EDIT
    Unbind(wxEVT_COMMAND_MENU_SELECTED,  &MainFrame::OnBold, this, ID_FORMAT_BOLD);
    Unbind(wxEVT_COMMAND_MENU_SELECTED,  &MainFrame::OnItalic, this, ID_FORMAT_ITALIC);
    Unbind(wxEVT_COMMAND_MENU_SELECTED,  &MainFrame::OnUnderline, this, ID_FORMAT_UNDERLINE);

    Unbind(wxEVT_COMMAND_MENU_SELECTED,  &MainFrame::OnStrikethrough, this, ID_FORMAT_STRIKETHROUGH);
    Unbind(wxEVT_COMMAND_MENU_SELECTED,  &MainFrame::OnSuperscript, this, ID_FORMAT_SUPERSCRIPT);
    Unbind(wxEVT_COMMAND_MENU_SELECTED,  &MainFrame::OnSubscript, this, ID_FORMAT_SUBSCRIPT);

    Unbind(wxEVT_UPDATE_UI,  &MainFrame::OnUpdateItalic, this, ID_FORMAT_ITALIC);
    Unbind(wxEVT_UPDATE_UI,  &MainFrame::OnUpdateUnderline, this, ID_FORMAT_UNDERLINE);

    Unbind(wxEVT_UPDATE_UI,  &MainFrame::OnUpdateStrikethrough, this, ID_FORMAT_STRIKETHROUGH);
    Unbind(wxEVT_UPDATE_UI,  &MainFrame::OnUpdateSuperscript, this, ID_FORMAT_SUPERSCRIPT);
    Unbind(wxEVT_UPDATE_UI,  &MainFrame::OnUpdateSubscript, this, ID_FORMAT_SUBSCRIPT);

    Unbind(wxEVT_COMMAND_MENU_SELECTED,  &MainFrame::OnAlignLeft, this, ID_FORMAT_ALIGN_LEFT);
    Unbind(wxEVT_COMMAND_MENU_SELECTED,  &MainFrame::OnAlignCentre, this, ID_FORMAT_ALIGN_CENTRE);
    Unbind(wxEVT_COMMAND_MENU_SELECTED,  &MainFrame::OnAlignRight, this, ID_FORMAT_ALIGN_RIGHT);

    Unbind(ID_FORMAT_ALIGN_LEFT, wxEVT_UPDATE_UI,  &MainFrame::OnUpdateAlignLeft, this, );
    Unbind(ID_FORMAT_ALIGN_CENTRE, wxEVT_UPDATE_UI,  &MainFrame::OnUpdateAlignCentre, this, );
    Unbind(ID_FORMAT_ALIGN_RIGHT, wxEVT_UPDATE_UI,  &MainFrame::OnUpdateAlignRight, this, );

    Unbind(wxEVT_COMMAND_MENU_SELECTED,  &MainFrame::OnFont, this, ID_FORMAT_FONT);
    Unbind(wxEVT_COMMAND_MENU_SELECTED,  &MainFrame::OnImage, this, ID_FORMAT_IMAGE);
    Unbind(wxEVT_COMMAND_MENU_SELECTED,  &MainFrame::OnParagraph, this, ID_FORMAT_PARAGRAPH);
    Unbind(wxEVT_COMMAND_MENU_SELECTED,  &MainFrame::OnFormat, this, ID_FORMAT_CONTENT);
    Unbind(wxEVT_UPDATE_UI,  &MainFrame::OnUpdateFormat, this, ID_FORMAT_CONTENT, ID_FORMAT_PARAGRAPH);
    //Unbind(wxEVT_UPDATE_UI,  wxUpdateUIEventHandler(MainFrame::OnUpdateFormat, this, ID_FORMAT_FONT);
    //Unbind(wxEVT_UPDATE_UI,  wxUpdateUIEventHandler(MainFrame::OnUpdateFormat, this, ID_FORMAT_PARAGRAPH);
    Unbind(wxEVT_UPDATE_UI,  &MainFrame::OnUpdateImage, this, ID_FORMAT_IMAGE);

    Unbind(ID_FORMAT_INDENT_MORE, wxEVT_COMMAND_MENU_SELECTED,  &MainFrame::OnIndentMore, this, );
    Unbind(ID_FORMAT_INDENT_LESS, wxEVT_COMMAND_MENU_SELECTED,  &MainFrame::OnIndentLess, this, );

    Unbind(wxEVT_COMMAND_MENU_SELECTED,  &MainFrame::OnLineSpacingHalf, this, ID_FORMAT_LINE_SPACING_HALF);
    Unbind(wxEVT_COMMAND_MENU_SELECTED,  &MainFrame::OnLineSpacingSingle, this, ID_FORMAT_LINE_SPACING_SINGLE);
    Unbind(wxEVT_COMMAND_MENU_SELECTED,  &MainFrame::OnLineSpacingDouble, this, ID_FORMAT_LINE_SPACING_DOUBLE);

    Unbind(wxEVT_COMMAND_MENU_SELECTED,  &MainFrame::OnParagraphSpacingMore, this, ID_FORMAT_PARAGRAPH_SPACING_MORE);
    Unbind(wxEVT_COMMAND_MENU_SELECTED,  &MainFrame::OnParagraphSpacingLess, this, ID_FORMAT_PARAGRAPH_SPACING_LESS);

    Unbind(wxEVT_COMMAND_MENU_SELECTED,  &MainFrame::OnInsertSymbol, this, ID_INSERT_SYMBOL);
    Unbind(wxEVT_COMMAND_MENU_SELECTED,  &MainFrame::OnInsertURL, this, ID_INSERT_URL);
    Unbind(wxEVT_COMMAND_MENU_SELECTED,  &MainFrame::OnInsertImage, this, ID_INSERT_IMAGE);

    Unbind(wxEVT_COMMAND_MENU_SELECTED,  &MainFrame::OnNumberList, this, ID_FORMAT_NUMBER_LIST);
    Unbind(wxEVT_COMMAND_MENU_SELECTED,  &MainFrame::OnBulletsAndNumbering, this, ID_FORMAT_BULLETS_AND_NUMBERING);
    Unbind(wxEVT_COMMAND_MENU_SELECTED,  &MainFrame::OnItemizeList, this, ID_FORMAT_ITEMIZE_LIST);
    Unbind(wxEVT_COMMAND_MENU_SELECTED,  &MainFrame::OnRenumberList, this, ID_FORMAT_RENUMBER_LIST);
    Unbind(wxEVT_COMMAND_MENU_SELECTED,  &MainFrame::OnPromoteList, this, ID_FORMAT_PROMOTE_LIST);
    Unbind(wxEVT_COMMAND_MENU_SELECTED,  &MainFrame::OnDemoteList, this, ID_FORMAT_DEMOTE_LIST);
    Unbind(wxEVT_COMMAND_MENU_SELECTED,  &MainFrame::OnClearList, this, ID_FORMAT_CLEAR_LIST);
    Unbind(wxEVT_COMMAND_MENU_SELECTED,  &MainFrame::OnTableAddColumn, this, ID_TABLE_ADD_COLUMN);
    Unbind(wxEVT_COMMAND_MENU_SELECTED,  &MainFrame::OnTableAddRow, this, ID_TABLE_ADD_ROW);
    Unbind(wxEVT_COMMAND_MENU_SELECTED,  &MainFrame::OnTableDeleteColumn, this, ID_TABLE_DELETE_COLUMN);
    Unbind(wxEVT_COMMAND_MENU_SELECTED,  &MainFrame::OnTableDeleteRow, this, ID_TABLE_DELETE_ROW);

    Unbind(wxEVT_UPDATE_UI,  &MainFrame::OnTableFocusedUpdateUI, this, ID_TABLE_ADD_COLUMN, ID_TABLE_ADD_ROW);
    Unbind(wxEVT_UPDATE_UI,  &MainFrame::OnTableHasCellsUpdateUI, this, ID_TABLE_DELETE_COLUMN, ID_TABLE_DELETE_ROW);
//    Unbind(wxEVT_UPDATE_UI,  &MainFrame::OnTableHasCellsUpdateUI, this, ID_TABLE_DELETE_ROW);

    Unbind(wxEVT_COMMAND_MENU_SELECTED,  &MainFrame::OnViewHTML, this, ID_VIEW_HTML);
    Unbind(wxEVT_COMMAND_MENU_SELECTED,  &MainFrame::OnSwitchStyleSheets, this, ID_SWITCH_STYLE_SHEETS);
    Unbind(wxEVT_COMMAND_MENU_SELECTED,  &MainFrame::OnManageStyles, this, ID_MANAGE_STYLES);

    Unbind(wxEVT_TEXT_URL,  &MainFrame::OnURL, this, wxID_ANY);
    Unbind(wxEVT_RICHTEXT_STYLESHEET_REPLACING,  &MainFrame::OnStyleSheetReplacing, this, wxID_ANY);
    Unbind(wxEVT_COMMAND_MENU_SELECTED,  &MainFrame::OnSetFontScale, this, ID_SET_FONT_SCALE);
    Unbind(wxEVT_COMMAND_MENU_SELECTED,  &MainFrame::OnSetDimensionScale, this, ID_SET_DIMENSION_SCALE);
    
#else
    Unbind(wxEVT_UPDATE_UI,  &MainFrame::OnUpdateUndo, this, wxID_UNDO);
    Unbind(wxEVT_UPDATE_UI,  &MainFrame::OnUpdateRedo, this, wxID_REDO);
#endif

//    m_comboBoxFavorite->Connect(wxEVT_TEXT_ENTER, wxCommandEventHandler(MainFrame::OnComboFavoriteTextEnter));
//    Connect(wxID_ANY, wxEVT_TEXT, wxTextEventHandler(MainFrame::OnComboFavoriteUpdate));
//    Connect(wxID_ANY, wxEVT_TEXT_ENTER, wxTextEventHandler(MainFrame::OnComboFavoriteUpdate));
//    Connect(wxID_ANY, wxEVT_COMBOBOX, wxCommandEventHandler(MainFrame::OnComboFavoriteUpdate));

    Unbind(wxEVT_COMMAND_MENU_SELECTED,  &MainFrame::OnAddFavorite, this, ID_FAVORITE_ADD);
    Unbind(wxEVT_COMMAND_MENU_SELECTED,  &MainFrame::OnDeleteFavorite, this, ID_FAVORITE_DELETE);
    Unbind(wxEVT_COMMAND_MENU_SELECTED,  &MainFrame::OnManageFavorite, this, ID_FAVORITE_MANAGE);
    Unbind(wxEVT_COMMAND_MENU_SELECTED,  &MainFrame::OnGoFavorite, this, ID_FAVORITE_GO);
    Unbind(wxEVT_UPDATE_UI,  &MainFrame::OnUpdateAddFavorite, this, ID_FAVORITE_ADD);
    Unbind(wxEVT_UPDATE_UI,  &MainFrame::OnUpdateDeleteFavorite, this, ID_FAVORITE_DELETE);
    Unbind(wxEVT_UPDATE_UI,  &MainFrame::OnUpdateGoFavorite, this, ID_FAVORITE_GO);
    
    Unbind(wxEVT_COMMAND_MENU_SELECTED,  &MainFrame::OnFocusComboFavorite, this, ID_FOCUS_FAVORITES);  
}

void MainFrame::SetText(wxString texte)
{
    LOG_IF(texte.IsEmpty(), DEBUG) << "No text to show in editor "; 
    LOG_IF(!texte.IsEmpty(), DEBUG) << "Text to show in editor <" << texte <<">";
/*#if USE_RICH_EDIT
    wxRichTextBuffer & rtb = m_editor->GetBuffer();
    m_editor->BeginSuppressUndo();
    rtb.ResetAndClearCommands();
    m_editor->Clear();
    m_editor->WriteText(wxString::FromUTF8(texte.c_str()));
    m_editor->EndSuppressUndo();
#else*/
    m_editor->SetValue(wxString::FromUTF8(texte.c_str()));
#if USE_RICH_EDIT == false
    m_editor->EmptyUndoBuffer();
#endif    
    m_editor->DiscardEdits();
    
//    bool retour = rtb.LoadFile(final); // == 0
//    //rtb.AddParagraph(wxT("Testeeds"));
//    rtb.UpdateRanges();
//    
////    bool retour = rtb.LoadFile(final, wxRICHTEXT_TYPE_RTF); 
////    rtb.UpdateRanges();
////    rtb.Invalidate(wxRICHTEXT_ALL);
////    m_editor->EndSuppressUndo();
////    m_editor->LayoutContent();
//// //   m_editor->Invalidate();
//    m_editor->Refresh(false); 
    //OnStatusBarMessage(texte.ToStdString());
}

void MainFrame::EnableShowHirerarchicalTree(bool hiearchy)
{
     m_menuBar->Enable(ID_HIERACHY, hiearchy);
}

// BEGIN  MY EVENTS

void MainFrame::OnFocusComboFavorite(wxCommandEvent& event)
{
	m_comboBoxFavorite->SetFocus();
}
  
void MainFrame::OnCloseFrame(wxCloseEvent& event)
{
    bool exit = true;
    wxGetApp().UpdateCurrentWork();
    if (wxGetApp().IsModified()) {
        wxMessageDialog dial(this, _("This document was modified, would you like to save ?"), _("Warning"), wxYES_NO|wxCANCEL|wxCENTER_FRAME);
        int retour = dial.ShowModal();
        if (retour==wxID_YES)
            wxGetApp().Save();
        else if (retour==wxID_CANCEL)
            exit = false;///todo ne pas fermer
    }  
    if (exit)
        Destroy();
}

void MainFrame::OnCalendarDblClick(wxCalendarEvent& event)
{
    //chercher date dans tree
    wxDateTime selDate = m_calendar->GetDate();
    wxGetApp().AddDateToTree(selDate, true);
    m_editor->SetFocus(); //todo correction 1re ligne vide
}

void MainFrame::OnCalendarSetFocus( wxFocusEvent& event )
{
    OnStatusBarMessage(_("Double-clicking on a date to add it on the tree")); 
}

void MainFrame::OnCalendarKillFocus( wxFocusEvent& event )
{
    OnStatusBarMessage("");
}

void MainFrame::OnCalendarSelChanged(wxCalendarEvent& event) 
{ 
    //todo find date in tree ??
 //   wxGetApp().SetCurrentDate(m_calendar->GetDate());  
  
//    wxTreeItemId itemId = wxGetApp().FindDateInTree(m_calendar->GetDate());
//    if (itemId.IsOk()) {
//        m_treeDates->SelectItem(itemId, true);
//    }
}  

void MainFrame::OnTreeSelChanging( wxTreeEvent& event )
{
    wxGetApp().UpdateCurrentWork();
}

void MainFrame::OnTreeSelChanged( wxTreeEvent& event )
{
    wxGetApp().SetCurrentDateFromTreeSelection();   
}

void MainFrame::OnTreeRightClick(wxTreeEvent& event)
{
    wxDateTime date = wxGetApp().GetDateFromTreeSelection();   
    if (date.IsValid())
        m_calendar->SetDate(date);
}

void MainFrame::OnStatusBarMessage(wxString msg)
{
	//std::cout << msg << std::endl;
    //LOG(INFO) << msg ;
//    m_statusBar->SetStatusText(wxString::FromUTF8(msg.c_str()));
    m_statusBar->SetStatusText(msg);
}

void MainFrame::OnShowHirerarchicalTree(wxCommandEvent& event)
{
    bool c = m_menuBar->IsChecked(ID_HIERACHY);
    wxGetApp().SetHierarchicalTree(c); 
    wxGetApp().LoadDailyWorkInTree();  
}

/*
void MainFrame::OnComboFavoriteTextEnter(wxCommandEvent& event)
{
   OnGoFavorite(event);
}
    
void MainFrame::OnComboFavoriteUpdate(wxCommandEvent& event)
{
    // Don't show messages for the log output window (it'll crash)
    if ( !event.GetEventObject()->IsKindOf(CLASSINFO(wxComboCtrl)) )
        return;

    if ( event.GetEventType() == wxEVT_COMBOBOX )
    {
        LOG(DEBUG) << wxT("EVT_COMBOBOX(id=%i,selection=%i)"),event.GetId(),event.GetSelection();
    }
    else if ( event.GetEventType() == wxEVT_TEXT )
    {
        LOG(DEBUG) << wxT("EVT_TEXT(id=%i,string=\"%s\")"),event.GetId(),event.GetString().c_str();
    }
    else if ( event.GetEventType() == wxEVT_TEXT_ENTER )
    {
        LOG(DEBUG) << wxT(("EVT_TEXT_ENTER(id=%i,string=\"%s\")",              event.GetId(), event.GetString().c_str());
    }
}*/

void MainFrame::OnAddFavorite(wxCommandEvent& event)
{
        //m_editor->Copy();
//       wxRichTextSelection rtselection = m_editor->GetSelection(); 
//       m_editor->Copy();
//       wxString  selection = rtselection.GetContainer()->GetText();
       wxString  selection = m_editor->GetStringSelection(); 
       wxGetApp().AddToFavorites(selection);  
}

void MainFrame::OnDeleteFavorite(wxCommandEvent& event)
{
       wxGetApp().DeleteSelectedFavorite();     
}

void MainFrame::OnManageFavorite(wxCommandEvent& event)
{
    //todo faire fonction avec listbox et ...
    wxMessageDialog(this, _("Not yet implemented..."), _("Information"), wxOK|wxCENTER_FRAME).ShowModal();
    
}    

void MainFrame::OnGoFavorite(wxCommandEvent& event)
{
    m_editor->SetFocus();
    wxString s = m_comboBoxFavorite->GetStringSelection(); 
    m_editor->WriteText(s);
}
    
void MainFrame::OnUpdateAddFavorite(wxUpdateUIEvent& event)
{
    event.Enable(m_editor->CanCopy()); //todo voir s'il n'y a pas une fonction plus appropriée
}

void MainFrame::OnUpdateDeleteFavorite(wxUpdateUIEvent& event)
{
    event.Enable(m_comboBoxFavorite->GetSelection() != wxNOT_FOUND); // (m_comboBoxFavorite->GetCount()==0) &&
}

void MainFrame::OnUpdateGoFavorite(wxUpdateUIEvent& event)
{
    event.Enable(m_comboBoxFavorite->GetStringSelection() != ""); // (m_comboBoxFavorite->GetCount()==0) &&
}

void MainFrame::OnButtonGoNextAvailableClick(wxCommandEvent& event)
{
    wxGetApp().SetNextDateAsCurrentDate();    
}

void MainFrame::OnButtonGoPrevAvailableClick(wxCommandEvent& event)
{
   wxGetApp().SetPrevDateAsCurrentDate();   
}

void MainFrame::OnButtonAddTomorrowClick(wxCommandEvent& event)
{
   wxGetApp().AddTomorrowToTree();  
}

void MainFrame::OnButtonAddYesterdayClick(wxCommandEvent& event)
{
   wxGetApp().AddYesterdayToTree();      
}    
 
void MainFrame::OnReload(wxCommandEvent& event)
{
    LOG(INFO) << "Ouverture du fichier json " ;
    wxGetApp().InitDailyWorkParser();
}

void MainFrame::OnDeleteDate(wxCommandEvent& event)
{
    wxGetApp().DeleteDateSelected();
}

//void MainFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
void MainFrame::OnQuit(wxCommandEvent& event)
{
    // true is to force the frame to close
    Close();
}

void MainFrame::OnAbout(wxCommandEvent& event)
{
 #if USE_RICH_EDIT
    wxString msg = _("This is a daily notepad.\n(c) Laurent Silvestre\nThanks to Julian Smart and his wxRichTextCtrl demo (currently unused), 2005");
#else
    wxString msg = _("This is a daily notepad.\n(c) Laurent Silvestre\nThanks to Wyo and his STC test module, 2015");
#endif
    wxMessageBox(msg, _("About Dailywork"), wxOK | wxICON_INFORMATION, this);
}

void MainFrame::OnStayOnTop(wxCommandEvent& event)
{
   //todo possible ?
}

void MainFrame::OnSave(wxCommandEvent& event)
{
   wxGetApp().UpdateCurrentWork(); // met à jour/ou pas le texte ecrit dans le richedit dans DWparser
    wxGetApp().Save();    
//    wxDateTime d; 
//    for(auto i = wxGetApp().currentDates.dates.begin(); i != wxGetApp().currentDates.dates.end(); ++i) {
//        d = *i;
//        LOG(INFO) <<d.Format().ToStdString();        
//    }    
}

void MainFrame::OnSaveAs(wxCommandEvent& event)
{    
    wxString filter = "*.json"; //wxRichTextBuffer::GetExtWildcard(false, true);
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
            wxGetApp().UpdateCurrentWork(); // met à jour/ou pas le texte ecrit dans le richedit dans DWparser
            wxGetApp().SaveAs(path);
            wxString s = wxString::Format(_("Save as <%s>"), path); 
            OnStatusBarMessage(s.ToStdString());
             //wxBusyCursor busy;
            //wxStopWatch stopwatch;
           // m_editor->SaveFile(path);
            //long t = stopwatch.Time();
            //wxLogDebug(wxT("Saving took %ldms"), t);
            //wxMessageBox(wxString::Format(_("Saving took %ldms"), t));
        }
    }
}

// END MY EVENTS

// event handlers

void MainFrame::OnOpen(wxCommandEvent&event)
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
            #if USE_RICH_EDIT
            int filterIndex = dialog.GetFilterIndex();
            int fileType = (filterIndex < (int) fileTypes.GetCount())
                           ? fileTypes[filterIndex]
                           : wxRICHTEXT_TYPE_TEXT;
            m_editor->LoadFile(path, fileType);
            #else
            m_editor->LoadFile(path);
            #endif
        }
    }
}

#if USE_RICH_EDIT == false
void MainFrame::OnUpdateUndo(wxUpdateUIEvent& event)
{
    event.Enable(m_editor->CanUndo());   
}

void MainFrame::OnUpdateRedo(wxUpdateUIEvent& event)
{
    event.Enable(m_editor->CanRedo()); 
}
#endif

// Forward command events to the current rich text control, if any
bool MainFrame::ProcessEvent(wxEvent& event)
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
            success = wxFrame::ProcessEvent(event);
        
        s_lastEvent = NULL;    

        return success;
    }   
    else {
        return wxFrame::ProcessEvent(event);
    }
}

#if USE_RICH_EDIT

void MainFrame::OnBold(wxCommandEvent& event)
{
    m_editor->ApplyBoldToSelection();
}

void MainFrame::OnItalic(wxCommandEvent& event)
{
    m_editor->ApplyItalicToSelection();
}

void MainFrame::OnUnderline(wxCommandEvent& event)
{
    m_editor->ApplyUnderlineToSelection();
}

void MainFrame::OnStrikethrough(wxCommandEvent& event)
{
    m_editor->ApplyTextEffectToSelection(wxTEXT_ATTR_EFFECT_STRIKETHROUGH);
}

void MainFrame::OnSuperscript(wxCommandEvent& event)
{
    m_editor->ApplyTextEffectToSelection(wxTEXT_ATTR_EFFECT_SUPERSCRIPT);
}

void MainFrame::OnSubscript(wxCommandEvent& event)
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

void MainFrame::OnAlignLeft(wxCommandEvent& event)
{
    m_editor->ApplyAlignmentToSelection(wxTEXT_ALIGNMENT_LEFT);
}

void MainFrame::OnAlignCentre(wxCommandEvent& event)
{
    m_editor->ApplyAlignmentToSelection(wxTEXT_ALIGNMENT_CENTRE);
}

void MainFrame::OnAlignRight(wxCommandEvent& event)
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

void MainFrame::OnFont(wxCommandEvent& event)
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

void MainFrame::OnImage(wxCommandEvent& event)
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

void MainFrame::OnParagraph(wxCommandEvent& event)
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

void MainFrame::OnFormat(wxCommandEvent& event)
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

void MainFrame::OnIndentMore(wxCommandEvent& event)
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

void MainFrame::OnIndentLess(wxCommandEvent& event)
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

void MainFrame::OnLineSpacingHalf(wxCommandEvent& event)
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

void MainFrame::OnLineSpacingDouble(wxCommandEvent& event)
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

void MainFrame::OnLineSpacingSingle(wxCommandEvent& event)
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

void MainFrame::OnParagraphSpacingMore(wxCommandEvent& event)
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

void MainFrame::OnParagraphSpacingLess(wxCommandEvent& event)
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

void MainFrame::OnViewHTML(wxCommandEvent& event)
{
    wxDialog dialog(this, wxID_ANY, _("HTML"), wxDefaultPosition, wxSize(500, 400), wxDEFAULT_DIALOG_STYLE);

    wxBoxSizer* boxSizer = new wxBoxSizer(wxVERTICAL);
    dialog.SetSizer(boxSizer);

    wxHtmlWindow* win = new wxHtmlWindow(& dialog, wxID_ANY, wxDefaultPosition, wxSize(500, 400), wxSUNKEN_BORDER);
    boxSizer->Add(win, 1, wxALL, 5);

    wxButton* cancelButton = new wxButton(& dialog, wxID_CANCEL, _("&Close"));
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

void MainFrame::OnSwitchStyleSheets(wxCommandEvent& event)
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

void MainFrame::OnManageStyles(wxCommandEvent& event)
{
    wxRichTextStyleSheet* sheet = m_editor->GetStyleSheet();

    int flags = wxRICHTEXT_ORGANISER_CREATE_STYLES|wxRICHTEXT_ORGANISER_EDIT_STYLES;

    wxRichTextStyleOrganiserDialog dlg(flags, sheet, NULL, this, wxID_ANY, _("Style Manager"));
    dlg.ShowModal();
}

void MainFrame::OnInsertSymbol(wxCommandEvent& event)
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

void MainFrame::OnNumberList(wxCommandEvent& event)
{
    if (m_editor->HasSelection())
    {
        wxRichTextRange range = m_editor->GetSelectionRange();
        m_editor->SetListStyle(range, _("Numbered List 1"), wxRICHTEXT_SETSTYLE_WITH_UNDO|wxRICHTEXT_SETSTYLE_RENUMBER);
    }
}

void MainFrame::OnBulletsAndNumbering(wxCommandEvent& event)
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

void MainFrame::OnItemizeList(wxCommandEvent& event)
{
    if (m_editor->HasSelection())
    {
        wxRichTextRange range = m_editor->GetSelectionRange();
        m_editor->SetListStyle(range, _("Bullet List 1"));
    }
}

void MainFrame::OnRenumberList(wxCommandEvent& event)
{
    if (m_editor->HasSelection())
    {
        wxRichTextRange range = m_editor->GetSelectionRange();
        m_editor->NumberList(range, NULL, wxRICHTEXT_SETSTYLE_WITH_UNDO|wxRICHTEXT_SETSTYLE_RENUMBER);
    }
}

void MainFrame::OnPromoteList(wxCommandEvent& event)
{
    if (m_editor->HasSelection())
    {
        wxRichTextRange range = m_editor->GetSelectionRange();
        m_editor->PromoteList(1, range, NULL);
    }
}

void MainFrame::OnDemoteList(wxCommandEvent& event)
{
    if (m_editor->HasSelection())
    {
        wxRichTextRange range = m_editor->GetSelectionRange();
        m_editor->PromoteList(-1, range, NULL);
    }
}

void MainFrame::OnClearList(wxCommandEvent& event)
{
    if (m_editor->HasSelection())
    {
        wxRichTextRange range = m_editor->GetSelectionRange();
        m_editor->ClearListStyle(range);
    }
}

void MainFrame::OnTableAddColumn(wxCommandEvent& event)
{
    wxRichTextTable* table = wxDynamicCast(m_editor->FindTable(), wxRichTextTable);
    if (table)
    {
        wxRichTextAttr cellAttr = table->GetCell(0, 0)->GetAttributes();
        table->AddColumns(table->GetColumnCount(), 1, cellAttr);
    }
}

void MainFrame::OnTableAddRow(wxCommandEvent& event)
{
    wxRichTextTable* table = wxDynamicCast(m_editor->FindTable(), wxRichTextTable);
    if (table)
    {
        wxRichTextAttr cellAttr = table->GetCell(0, 0)->GetAttributes();
        table->AddRows(table->GetRowCount(), 1, cellAttr);
    }
}

void MainFrame::OnTableDeleteColumn(wxCommandEvent& event)
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

void MainFrame::OnTableDeleteRow(wxCommandEvent& event)
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

void MainFrame::OnInsertURL(wxCommandEvent& event)
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

void MainFrame::OnInsertImage(wxCommandEvent& event)
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

void MainFrame::OnSetFontScale(wxCommandEvent& event)
{
    wxString value = wxString::Format(wxT("%g"), m_editor->GetFontScale());
    wxString text = wxGetTextFromUser(_("Enter a text scale factor:"), _("Text Scale Factor"), value, wxGetTopLevelParent(this));
    if (!text.IsEmpty() && value != text)
    {
        double scale = 1.0;
        wxSscanf(text, wxT("%lf"), & scale);
        m_editor->SetFontScale(scale, true);
    }
}

void MainFrame::OnSetDimensionScale(wxCommandEvent& event)
{
    wxString value = wxString::Format(wxT("%g"), m_editor->GetDimensionScale());
    wxString text = wxGetTextFromUser(_("Enter a dimension scale factor:"), _("Dimension Scale Factor"), value, wxGetTopLevelParent(this));
    if (!text.IsEmpty() && value != text)
    {
        double scale = 1.0;
        wxSscanf(text, wxT("%lf"), & scale);
        m_editor->SetDimensionScale(scale, true);
    }
}


void MainFrame::WriteInitialText()
{
// Write text
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
#endif //USE_RICH_EDIT