#include "ui_drawer.h"

const long ui_drawer::ID_TOOL_NEW = wxNewId();
const long ui_drawer::ID_TOOL_IMPORT = wxNewId();
const long ui_drawer::ID_TOOL_OPEN = wxNewId();
const long ui_drawer::ID_TOOL_SAVE = wxNewId();
const long ui_drawer::ID_TOOL_COMPILE = wxNewId();
const long ui_drawer::ID_TOOL_SIMULATE = wxNewId();

static wxTextCtrl* LOG_FIELD;
static wxListCtrl* LIST_COMPILED;
static wxStaticText* TEXT_WORKINGFOLDERVAL;
static wxStaticText* TEXT_WORKINGFILEVAL;
static wxToolBar* TOOLBAR;
//wxNotebook* code_editor_notebook;
wxAuiNotebook* code_editor_notebook;
static core_functionalities * core_funcs;
static file_handler * file_hndlr;
static file_explorer_tree* file_explorer;
static wxSize* screen_size;
static wxWindow* parent;
static entity_select_form* entity_sel_form;

static std::string VHDL_HELLO_WORLD = "-- Simple Hello World Program\n"
                                        "\n"
                                        "library IEEE;\n"
                                        "use IEEE.std_logic_1164.all;\n"
                                        "\n"
                                        "entity T01_HelloWorldTb is\n"
                                        "port(\n"
                                        "  a: in std_logic;\n"
                                        "  b: in std_logic;\n"
                                        "  q: out std_logic);\n"
                                        "end entity;\n"
                                        "\n"
                                        "architecture sim of T01_HelloWorldTb is\n"
                                        "begin\n"
                                        "\n"
                                        "    process is\n"
                                        "    begin\n"
                                        "\n"
                                        "        report \"Hello World!\";\n"
                                        "        wait;\n"
                                        "\n"
                                        "    end process;\n"
                                        "\n"
                                        "end architecture;";
//
//struct  {
//    wxColour bg_color;
//    wxColour higher_bg_color;
//    wxColour highest_bg_color;
//    wxColour toolbar_color;
//    wxColour text_color;
//} colours;



//
//wxColour bg_color = wxColour(68,68,68);
//wxColour higher_bg_color = wxColour(89,89,89);
//wxColour highest_bg_color = wxColour(220,220,220);
//wxColour toolbar_color = wxColour(152,152,152);
//wxColour text_color = wxColour(255,255,255);
//
//wxColour bg_color = wxColour(230,230,230);
//wxColour higher_bg_color = wxColour(250,250,250);
//wxColour highest_bg_color = wxColour(255,255,255);
//wxColour text_color = wxColour(2,2,2);

ui_drawer::ui_drawer(wxWindow* parent, wxWindowID) {
    //TextCtrl3 = new wxTextCtrl(parent, ID_TEXTCTRL3, _("Results..."), wxPoint(72,200), wxSize(704,96), wxTE_MULTILINE, wxDefaultValidator, _T("ID_TEXTCTRL1"));

}



void ui_drawer::draw_everything(wxWindow* imported_parent, wxWindowID, int window_x,int  window_y, core_functionalities* main_core_funcs, file_handler* main_file_handler) {
    core_funcs = main_core_funcs;
    file_hndlr = main_file_handler;
    parent = imported_parent;

    screen_size = new wxSize(window_x, window_y);


    TOOLBAR = new wxToolBar(parent, wxID_NEW, wxDefaultPosition, wxDefaultSize, wxTB_HORIZONTAL, _T("ID_TOOLBAR1"));
//     wxImage print (wxT ("icons\\v3.ico"), wxBITMAP_TYPE_PNG);
//    wxIcon newIcon;
//    newIcon.CopyFromBitmap(wxBitmap(wxImage(_T("icons\\v3.ico"))));

    TOOLBAR->AddTool(ID_TOOL_NEW, _("New File"), wxBitmap(wxImage("icons\\tools_icons\\new.png")), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_WARNING")),wxART_TOOLBAR), wxITEM_NORMAL,  _("New File"),  _("New File"));
    //TOOLBAR->AddTool(ID_TOOL_NEW, _("New File"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_NORMAL_FILE")),wxART_TOOLBAR), wxNullBitmap, wxITEM_NORMAL,  _("New File"),  _("New File"));
    TOOLBAR->AddTool(ID_TOOL_IMPORT, _("Import"), wxBitmap(wxImage("icons\\tools_icons\\import.png")), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_WARNING")),wxART_TOOLBAR), wxITEM_NORMAL, _("Import"), _("Import"));
    TOOLBAR->AddTool(ID_TOOL_OPEN, _("Open"), wxBitmap(wxImage("icons\\tools_icons\\open.png")), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_WARNING")),wxART_TOOLBAR), wxITEM_NORMAL, _("Open"), _("Open"));

    TOOLBAR->AddTool(ID_TOOL_SAVE, _("Save"), wxBitmap(wxImage("icons\\tools_icons\\save.png")), wxNullBitmap, wxITEM_NORMAL, _("Save"), _("Save"));
    TOOLBAR->InsertSeparator(4);
    TOOLBAR->AddTool(ID_TOOL_COMPILE, _("Compile"), wxBitmap(wxImage("icons\\tools_icons\\compile.png")), wxNullBitmap, wxITEM_NORMAL, _("Compile"), _("Compile"));
    TOOLBAR->AddTool(ID_TOOL_SIMULATE, _("Simulate"), wxBitmap(wxImage("icons\\tools_icons\\simulate.png")), wxNullBitmap, wxITEM_NORMAL, _("Simulate"), _("Simulate"));

    TOOLBAR->SetBackgroundColour(color_palette::toolbar_color);


    TOOLBAR->Bind(wxEVT_COMMAND_TOOL_CLICKED, [&](wxCommandEvent& e) {
        int id= e.GetId();
        if (id == ID_TOOL_NEW) {
            tool_new();

        } else if(id == ID_TOOL_IMPORT) {


            tool_import();
        } else if(id == ID_TOOL_OPEN) {

            tool_open();
        } else if(id == ID_TOOL_SAVE) {

            tool_save();
        } else if(id == ID_TOOL_COMPILE) {
            tool_compile();

        } else if(id == ID_TOOL_SIMULATE) {
            tool_simulate();
        }
    });


    wxSplitterWindow* SplitterWindow2 = new wxSplitterWindow(parent, wxID_ANY, wxDefaultPosition, wxSize(window_x,window_y*0.8), wxSP_LIVE_UPDATE);

    wxPanel* explorer = new wxPanel(SplitterWindow2, wxID_ANY, wxDefaultPosition, wxSize(window_x*0.15,window_y*0.8));
    explorer->SetBackgroundColour(color_palette::bg_color);
    explorer->SetForegroundColour( color_palette::text_color );
    wxBoxSizer *vbox_explorer = new wxBoxSizer(wxVERTICAL);
    wxStaticText* title1 = new wxStaticText(explorer,wxID_ANY,"\nFile Explorer");
    file_explorer = new file_explorer_tree(explorer);
    file_explorer->get_treectrl()->SetBackgroundColour(color_palette::higher_bg_color);
    wxStaticText* title2 = new wxStaticText(explorer,wxID_ANY,"\nCompiled Files");
    LIST_COMPILED = new wxListCtrl(explorer, wxID_ANY, wxPoint(0,220), wxSize(250,120), wxBORDER_NONE|wxLC_LIST, wxDefaultValidator, _T("ID_COMPILED_LIST"));


    wxStaticText* TEXT_WORKINGFOLDER = new wxStaticText(explorer, wxID_ANY, _("Working Folder: "), wxDefaultPosition, wxDefaultSize, 0, _T("ID_TEXTFOLDER"));
    TEXT_WORKINGFOLDERVAL = new wxStaticText(explorer, wxID_ANY, _(""), wxDefaultPosition, wxDefaultSize, 0, _T("ID_TEXTFOLDER"));
    wxStaticText* TEXT_WORKINGFILE = new wxStaticText(explorer, wxID_ANY, _("Working File: "), wxDefaultPosition, wxDefaultSize, 0, _T("ID_TEXTFILE"));
    TEXT_WORKINGFILEVAL = new wxStaticText(explorer, wxID_ANY, _(""), wxDefaultPosition, wxDefaultSize, 0, _T("ID_TEXTFILE"));

    LIST_COMPILED->SetBackgroundColour(color_palette::higher_bg_color);
    LIST_COMPILED->SetForegroundColour( color_palette::text_color );
    LIST_COMPILED->AppendColumn("Compiled Files", wxLIST_FORMAT_LEFT, 100);
    vbox_explorer->Add(title1, 0);
    vbox_explorer->Add(file_explorer->get_treectrl(), 1, wxEXPAND);
    vbox_explorer->Add(TEXT_WORKINGFOLDER, 0);
    vbox_explorer->Add(TEXT_WORKINGFOLDERVAL, 0);
    vbox_explorer->Add(TEXT_WORKINGFILE, 0);
    vbox_explorer->Add(TEXT_WORKINGFILEVAL, 0);
    vbox_explorer->Add(title2, 0);
    vbox_explorer->Add(LIST_COMPILED, 1, wxEXPAND);
    explorer->SetSizer( vbox_explorer );


    wxSplitterWindow* SplitterWindow3 = new wxSplitterWindow(SplitterWindow2, wxID_ANY, wxDefaultPosition, wxSize(window_x*0.7,window_y*0.8), wxSP_LIVE_UPDATE);



    SplitterWindow2->SplitVertically(explorer, SplitterWindow3);
    SplitterWindow2->SetSashGravity(0.15);
    SplitterWindow2->SetSashPosition(4);


    wxPanel* scene = new wxPanel(SplitterWindow3, wxID_ANY, wxDefaultPosition, wxSize(window_x*0.7,window_y*0.4), wxBORDER_NONE);
    scene->SetBackgroundColour(color_palette::bg_color);
    wxBoxSizer *vbox_scene = new wxBoxSizer(wxVERTICAL);
//    vbox_scene->set
    code_editor_notebook = new wxAuiNotebook(scene, wxID_ANY,wxDefaultPosition, wxDefaultSize );
    vbox_scene->Add(code_editor_notebook,  1, wxEXPAND);
    scene->SetSizer( vbox_scene );






    wxPanel* log = new wxPanel(SplitterWindow3, wxID_ANY, wxDefaultPosition, wxSize(window_x*0.7,window_y*0.15));
    log->SetBackgroundColour(color_palette::bg_color);

    wxBoxSizer *vbox_log = new wxBoxSizer(wxVERTICAL);
    LOG_FIELD = new wxTextCtrl(log, wxID_ANY, _("Results..."), wxDefaultPosition, wxDefaultSize, wxBORDER_NONE|wxTE_MULTILINE, wxDefaultValidator, _T("ID_TEXTCTRL1"));
    LOG_FIELD->SetBackgroundColour(color_palette::bg_color);
    LOG_FIELD->SetForegroundColour(color_palette::text_color );
    vbox_log->Add(LOG_FIELD, 1, wxEXPAND);
    log->SetSizer( vbox_log );


    SplitterWindow3->SplitHorizontally(scene, log);
    SplitterWindow3->SetSashGravity(0.8);
    SplitterWindow3->SetSashPosition(1000000);




//
//    code_editor_notebook->Bind(wxEVT_AUINOTEBOOK_PAGE_CLOSED, [&](wxAuiNotebookEvent& e) {
//        int tmp = e.GetSelection();
//        std::cout<<tmp<<std::endl;
//        std::string stmp = std::string(code_editor_notebook->GetPageText(0).mb_str());
//        std::cout<<stmp<<std::endl;
//
//    });

    SplitterWindow2->Bind(wxEVT_SPLITTER_DOUBLECLICKED, [&](wxSplitterEvent& e) {

        e.Veto();

    });

    SplitterWindow2->Bind(wxEVT_SPLITTER_SASH_POS_CHANGING, [&](wxSplitterEvent& e) {

        int i_value = e.GetSashPosition();
        wxSplitterWindow* stmp = (wxSplitterWindow*) e.GetEventObject();
        int i = stmp->GetSashPosition();

        if (i_value < 4)
            e.Veto();

        if ( abs(i_value-i) > 100) {
            e.Veto();
        }

    });


}

wxToolBar* ui_drawer::get_toolbar() {
    return TOOLBAR;
}

void ui_drawer::OnSplitChnging(wxSplitterEvent& event) {
    int i_value = event.GetSashPosition();
    wxSplitterWindow* stmp = (wxSplitterWindow*) event.GetEventObject();
    int i = stmp->GetSashPosition();

    if (i_value < 4)
        event.Veto();

    if ( abs(i_value-i) > 100) {
        event.Veto();
    }
}
void ui_drawer::OnSplitDpl(wxSplitterEvent& event) {

    event.Veto();
}

ui_drawer::~ui_drawer() {
    //dtor
}

wxStyledTextCtrl* ui_drawer::create_code_page(std::string content){

    wxStyledTextCtrl* code_editor = new wxStyledTextCtrl( code_editor_notebook, wxID_NEW, wxPoint(260,60), wxSize(750,250), wxBORDER_NONE );



    enum {MARGIN_LINE_NUMBERS};
    code_editor->SetMarginWidth (MARGIN_LINE_NUMBERS, 50);
    code_editor->StyleSetForeground (wxSTC_STYLE_LINENUMBER, wxColour (75, 75, 75) );
    code_editor->StyleSetBackground (wxSTC_STYLE_LINENUMBER, wxColour (220, 220, 220));
    code_editor->SetMarginType (MARGIN_LINE_NUMBERS, wxSTC_MARGIN_NUMBER);

    code_editor->SetWrapMode (wxSTC_WRAP_WORD);
    //text->SetText("CODE");
    code_editor->StyleClearAll();
    code_editor->SetLexer(wxSTC_LEX_VHDL);

    code_editor->StyleSetForeground (wxSTC_VHDL_STRING, wxColour(150,0,0));
    code_editor->StyleSetForeground (wxSTC_VHDL_STRINGEOL, wxColour(150,0,0));
    code_editor->StyleSetForeground (wxSTC_VHDL_OPERATOR, wxColour(165,105,0));
    code_editor->StyleSetForeground (wxSTC_VHDL_IDENTIFIER, wxColour(40,0,60));
    code_editor->StyleSetForeground (wxSTC_VHDL_NUMBER, wxColour(0,150,0));
    code_editor->StyleSetForeground (wxSTC_VHDL_KEYWORD, wxColour(0,0,150));
    code_editor->StyleSetForeground (wxSTC_VHDL_USERWORD, wxColour(0,150,0));
    code_editor->StyleSetForeground (wxSTC_VHDL_COMMENT, wxColour(150,150,150));
    code_editor->StyleSetForeground (wxSTC_VHDL_COMMENTLINEBANG, wxColour(150,150,150));
    code_editor->StyleSetForeground (wxSTC_VHDL_STDOPERATOR, wxColour(165,105,50));
    code_editor->StyleSetForeground (wxSTC_VHDL_ATTRIBUTE, wxColour(165,105,10));
    code_editor->StyleSetForeground (wxSTC_VHDL_STDFUNCTION, wxColour(165,105,150));
    code_editor->StyleSetForeground (wxSTC_VHDL_STDPACKAGE, wxColour(165,105,200));
    code_editor->StyleSetForeground (wxSTC_VHDL_STDTYPE, wxColour(165,105,250));

    code_editor->SetBackgroundColour(color_palette::bg_color);
    code_editor->SetForegroundColour(color_palette::text_color );


    code_editor->SetText(content);
    return code_editor;

}

void ui_drawer::open_file(std::string file) {

    int exists_already = -1;

    for (int i = 0; i < code_editor_notebook->GetPageCount(); i++){
        std::string tmp_name = std::string(code_editor_notebook->GetPageText(i).mb_str());
        if (tmp_name == file){
            exists_already = i;
            break;
        }
    }


    std::string file_content = file_hndlr->get_file_content(file);


    if ( exists_already == -1 ){
        wxStyledTextCtrl* code_editor = create_code_page(file_content);
        code_editor_notebook->AddPage(code_editor, file);
        code_editor_notebook->SetSelection(code_editor_notebook->GetPageCount()-1);
    }else{
        wxStyledTextCtrl* code_editor = (wxStyledTextCtrl*)code_editor_notebook->GetPage(exists_already);
        code_editor->SetText(file_content);
        code_editor_notebook->SetSelection(exists_already);
    }




    //TEXT_EDITORTITLE->SetLabel(file);
//    if (code_editor->IsFrozen())
//        code_editor->Thaw();
}


void ui_drawer::add_to_compiled_list(std::string file) {
    if ( LIST_COMPILED->FindItem(0, file) == -1 )
        LIST_COMPILED->InsertItem(0, file);
}

void ui_drawer::change_working_folder(std::string folder) {
    TEXT_WORKINGFOLDERVAL->SetLabel(folder);
}
void ui_drawer::change_working_file(std::string file) {
    TEXT_WORKINGFILEVAL->SetLabel(file);

}


void ui_drawer::close_entity_choosing_form(bool chosen, std::string entity_chosen) {
    parent->Thaw();
    entity_sel_form->Hide();
    if (chosen == false){


        return;
    }

    ui_drawer::append_on_results("CHOSEN ENTITY: "+entity_chosen);

    std::string selected_file = file_explorer->get_file_path();
    std::string selected_folder = file_explorer->get_folder_path();
    core_funcs->simulate(selected_folder, selected_file, entity_chosen);
}


void ui_drawer::pop_up(std::string message, std::string title) {
    wxMessageBox(message, _(title));
}

void ui_drawer::append_on_results(std::string words, bool is_error) {
    if (is_error){

//        LOG_FIELD->SetDefaultStyle(wxTextAttr(*wxRED));
//        LOG_FIELD->SetDefaultStyle(wxTextAttr(wxNullColour, *wxRED));
        //self.text.SetDefaultStyle(wx.TextAttr(wx.BLUE))
        LOG_FIELD->AppendText("\n");
        LOG_FIELD->AppendText(words);
        LOG_FIELD->AppendText("\n");
       // LOG_FIELD->SetDefaultStyle(wxTextAttr(*wxBLACK));
    }else{
        LOG_FIELD->AppendText("\n");
        LOG_FIELD->AppendText(words);
        LOG_FIELD->AppendText("\n");

    }
}


void ui_drawer::tool_new() {

    wxStyledTextCtrl* code_editor = create_code_page(VHDL_HELLO_WORLD);
    code_editor_notebook->AddPage(code_editor, "New");
    code_editor_notebook->SetSelection(code_editor_notebook->GetPageCount()-1);
}
void ui_drawer::tool_saveas(int page_number) {
    wxFileDialog   saveFileDialog(parent, _("Save VHDL file"), "", "",
                                           "VHDL files (*.vhd)|*.vhd", wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
    if (saveFileDialog.ShowModal() == wxID_CANCEL)
        return;     // the user changed idea...

    // save the current contents in the file;
    // this can be done with e.g. wxWidgets output streams:
    wxFileOutputStream output_stream(saveFileDialog.GetPath());
    if (!output_stream.IsOk())
    {
        wxLogError("Cannot save current contents in file '%s'.", saveFileDialog.GetPath());
        return;
    }
    std::string file_path = std::string(saveFileDialog.GetPath().mb_str());

    //wxStyledTextCtrl* code_editor = (wxStyledTextCtrl*) code_editor_notebook->GetPage(page_number);
    code_editor_notebook->SetPageText(page_number, file_path);
    tool_save();
}


void ui_drawer::tool_save() {
    int current_i = code_editor_notebook->GetSelection();

    if (current_i == -1)
        return;

    std::string tmp_name = std::string(code_editor_notebook->GetPageText(current_i).mb_str());

    if (file_hndlr->folder_exists(tmp_name)){

        wxStyledTextCtrl* tmp_codeeditor;
        tmp_codeeditor = (wxStyledTextCtrl*) code_editor_notebook->GetPage(current_i);
        //std::string tmp_content = std::string(code_editor_notebook->GetPage(current_i).mb_str());
        std::string tmp_content = std::string(tmp_codeeditor->GetText().mb_str());

        file_hndlr->save_file(tmp_name, tmp_content);
    }else{
        tool_saveas( current_i);
    }
}

void ui_drawer::tool_import() {
    wxFileDialog openFileDialog(parent, _("Open VHD file"), "", "",
                   "VHDL files (*.vhdl;*.vhd)|*.vhdl;*.vhd", wxFD_OPEN|wxFD_FILE_MUST_EXIST);
    if (openFileDialog.ShowModal() == wxID_CANCEL)
        return;     // the user changed idea...

    // proceed loading the file chosen by the user;
    // this can be done with e.g. wxWidgets input streams:
    wxFileInputStream input_stream(openFileDialog.GetPath());
    if (!input_stream.IsOk()) {
        wxLogError("Cannot open file '%s'.", openFileDialog.GetPath());
        return;
    }
    std::string folder_path = std::string(openFileDialog.GetPath().mb_str());

    std::cout<<folder_path<<std::endl;
    file_explorer->import_folder(folder_path);
}

void ui_drawer::tool_open() {
    wxDirDialog* dirDialog = new wxDirDialog(parent);

    // Display the dialog and transfer the contents to
    // the wxTextCtrl on the main frame if the user
    // doesn't cancel
    if (dirDialog->ShowModal() != wxID_OK)
        return ;



    std::string folder_path = std::string(dirDialog->GetPath().mb_str());

    std::cout<<folder_path<<std::endl;

    dirDialog->Destroy();
    file_explorer->import_folder(folder_path);
}


void ui_drawer::tool_compile() {
    std::string selected_file = file_explorer->get_file_path();
    std::string selected_folder = file_explorer->get_folder_path();
    core_funcs->compile(selected_file, selected_folder);
}

void ui_drawer::tool_undo() {
    int current_page = code_editor_notebook->GetSelection();
    wxStyledTextCtrl* code_editor = (wxStyledTextCtrl*)code_editor_notebook->GetPage(current_page);
    code_editor->Undo();
}
void ui_drawer::tool_redo() {
    int current_page = code_editor_notebook->GetSelection();
    wxStyledTextCtrl* code_editor = (wxStyledTextCtrl*)code_editor_notebook->GetPage(current_page);
    code_editor->Redo();
}
void ui_drawer::tool_cut() {
    int current_page = code_editor_notebook->GetSelection();
    wxStyledTextCtrl* code_editor = (wxStyledTextCtrl*)code_editor_notebook->GetPage(current_page);
    code_editor->Cut();
}
void ui_drawer::tool_copy() {
    int current_page = code_editor_notebook->GetSelection();
    wxStyledTextCtrl* code_editor = (wxStyledTextCtrl*)code_editor_notebook->GetPage(current_page);
    code_editor->Copy();
}

void ui_drawer::tool_paste() {
    int current_page = code_editor_notebook->GetSelection();
    wxStyledTextCtrl* code_editor = (wxStyledTextCtrl*)code_editor_notebook->GetPage(current_page);
    code_editor->Paste();
}
void ui_drawer::tool_delete() {
    int current_page = code_editor_notebook->GetSelection();
    wxStyledTextCtrl* code_editor = (wxStyledTextCtrl*)code_editor_notebook->GetPage(current_page);
    code_editor->DeleteBack();
}
void ui_drawer::tool_select_all() {
    int current_page = code_editor_notebook->GetSelection();
    wxStyledTextCtrl* code_editor = (wxStyledTextCtrl*)code_editor_notebook->GetPage(current_page);
    code_editor->SelectAll();
}


void ui_drawer::tool_simulate() {

        file_hndlr->clean_simulations();
        std::vector<std::string> entities = core_funcs->get_available_entities();
        if (entities.size() > 0){
            wxSize* form_size = new wxSize(screen_size->GetWidth()*0.2, screen_size->GetHeight()*0.3);
            wxSize* form_position = new wxSize( (screen_size->GetWidth()/2)-(form_size->GetWidth()/2),
                                                       (screen_size->GetHeight()/2)-(form_size->GetHeight()/2));
            entity_sel_form = new entity_select_form(entities, form_position, form_size);


            entity_sel_form->Show();
            parent->Freeze();
        }
}
