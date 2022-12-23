/***************************************************************
 * Name:      ShrewVHDLMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Firas Hares (firas.hrs@gmail.com)
 * Created:   2022-12-11
 * Copyright: Firas Hares (https://github.com/firashrs/)
 * License:
 **************************************************************/

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include "ShrewVHDLMain.h"

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__WXMAC__)
        wxbuild << _T("-Mac");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}


const long ShrewVHDLFrame::idMenuQuit = wxNewId();
const long ShrewVHDLFrame::idMenuAbout = wxNewId();
const long ShrewVHDLFrame::idMenuNew = wxNewId();
const long ShrewVHDLFrame::idMenuImport = wxNewId();
const long ShrewVHDLFrame::idMenuOpen = wxNewId();
const long ShrewVHDLFrame::idMenuSave = wxNewId();
const long ShrewVHDLFrame::idMenuCompile = wxNewId();
const long ShrewVHDLFrame::idMenuSimulate = wxNewId();
const long ShrewVHDLFrame::idMenuUndo = wxNewId();
const long ShrewVHDLFrame::idMenuRedo = wxNewId();
const long ShrewVHDLFrame::idMenuCut= wxNewId();
const long ShrewVHDLFrame::idMenuCopy = wxNewId();
const long ShrewVHDLFrame::idMenuPaste = wxNewId();
const long ShrewVHDLFrame::idMenuDelete = wxNewId();
const long ShrewVHDLFrame::idMenuSelectall = wxNewId();
const long ShrewVHDLFrame::ID_STATUSBAR1 = wxNewId();



BEGIN_EVENT_TABLE(ShrewVHDLFrame, wxFrame)
END_EVENT_TABLE()

ShrewVHDLFrame::ShrewVHDLFrame(wxFrame *frame, const wxString& title)
    : wxFrame(frame, -1, title)
{
//#if wxUSE_MENUS
//    // create a menu bar
//    wxMenuBar* mbar = new wxMenuBar();
//    wxMenu* fileMenu = new wxMenu(_T(""));
//    fileMenu->Append(idMenuQuit, _("&Quit\tAlt-F4"), _("Quit the application"));
//    mbar->Append(fileMenu, _("&File"));
//
//    wxMenu* helpMenu = new wxMenu(_T(""));
//    helpMenu->Append(idMenuAbout, _("&About\tF1"), _("Show info about this application"));
//    mbar->Append(helpMenu, _("&Help"));
//
//    SetMenuBar(mbar);
//#endif // wxUSE_MENUS
//
//#if wxUSE_STATUSBAR
//    // create a status bar with some information about the used wxWidgets version
//    CreateStatusBar(2);
//    SetStatusText(_("Hello Code::Blocks user!"),0);
//    SetStatusText(wxbuildinfo(short_f), 1);
//#endif // wxUSE_STATUSBAR
    RECT rc ;
    GetWindowRect(GetDesktopWindow(), &rc);
    int screen_x = rc.right;
    int screen_y = rc.bottom;
    SetClientSize(wxSize(screen_x,screen_y));


    core_functionalities* core_funcs = new core_functionalities();

    file_handler* fhandler = new file_handler();
    fhandler->clean_cache();
    fhandler->clean_simulations();


    int window_x = 0;
    int window_y = 0;
    GetClientSize(&window_x, &window_y);

    this->SetMinSize(wxSize(window_x*0.4, window_y*0.4));
    this->Maximize (true);


    ui_drawer::draw_everything(this, -1,window_x, window_y ,core_funcs, fhandler);
    wxToolBar* toolbar = ui_drawer::get_toolbar();
    toolbar->Realize();
    SetToolBar(toolbar);


    wxMenuBar* MenuBar = new wxMenuBar();

    wxMenu* Menu_File = new wxMenu();

    wxMenuItem* MenuItem_new = new wxMenuItem(Menu_File, idMenuNew, _("New File"), _("New File"), wxITEM_NORMAL);
    wxMenuItem* MenuItem_import = new wxMenuItem(Menu_File, idMenuImport, _("Import"), _("Import a single file"), wxITEM_NORMAL);
    wxMenuItem* MenuItem_open = new wxMenuItem(Menu_File, idMenuOpen, _("Open"), _("Open a whole folder"), wxITEM_NORMAL);
    wxMenuItem* MenuItem_save = new wxMenuItem(Menu_File, idMenuSave, _("Save"), _("Save current file"), wxITEM_NORMAL);
    wxMenuItem* MenuItem_close = new wxMenuItem(Menu_File, idMenuQuit, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    Menu_File->Append(MenuItem_new);
    Menu_File->Append(MenuItem_import);
    Menu_File->Append(MenuItem_open);
    Menu_File->Append(MenuItem_save);
    Menu_File->AppendSeparator();
    Menu_File->Append(MenuItem_close);
    MenuBar->Append(Menu_File, _("&File"));


    wxMenu* Menu_Edit = new wxMenu();
    wxMenuItem* MenuItem_undo = new wxMenuItem(Menu_Edit, idMenuUndo, _("Undo"), _("Undo"), wxITEM_NORMAL);
    wxMenuItem* MenuItem_redo = new wxMenuItem(Menu_Edit, idMenuRedo, _("Redo"), _("Redo"), wxITEM_NORMAL);
    wxMenuItem* MenuItem_cut = new wxMenuItem(Menu_Edit, idMenuCut, _("Cut"), _("Cut"), wxITEM_NORMAL);
    wxMenuItem* MenuItem_copy = new wxMenuItem(Menu_Edit, idMenuCopy, _("Copy"), _("Copy"), wxITEM_NORMAL);
    wxMenuItem* MenuItem_paste = new wxMenuItem(Menu_Edit, idMenuPaste, _("Paste"), _("Paste"), wxITEM_NORMAL);
    wxMenuItem* MenuItem_delete = new wxMenuItem(Menu_Edit, idMenuDelete, _("Delete"), _("Delete"), wxITEM_NORMAL);
    wxMenuItem* MenuItem_selectall = new wxMenuItem(Menu_Edit, idMenuSelectall, _("Select All"), _("Select All"), wxITEM_NORMAL);
    Menu_Edit->Append(MenuItem_undo);
    Menu_Edit->Append(MenuItem_redo);
    Menu_Edit->AppendSeparator();
    Menu_Edit->Append(MenuItem_cut);
    Menu_Edit->Append(MenuItem_copy);
    Menu_Edit->Append(MenuItem_paste);
    Menu_Edit->Append(MenuItem_delete);
    Menu_Edit->AppendSeparator();
    Menu_Edit->Append(MenuItem_selectall);
    MenuBar->Append(Menu_Edit, _("&Edit"));


    wxMenu* Menu_run = new wxMenu();
    wxMenuItem* MenuItem_compile = new wxMenuItem(Menu_run, idMenuCompile, _("Compile"), _("Compile selected File or Folder"), wxITEM_NORMAL);
    wxMenuItem* MenuItem_simulate = new wxMenuItem(Menu_run, idMenuSimulate, _("Simulate"), _("Simulate the compiled files"), wxITEM_NORMAL);
    Menu_run->Append(MenuItem_compile);
    Menu_run->Append(MenuItem_simulate);
    MenuBar->Append(Menu_run, _("Run"));

    wxMenu* Menu_help = new wxMenu();
    wxMenuItem* MenuItem_about = new wxMenuItem(Menu_help, idMenuAbout, _("About\tF1"), _("Show info about this application"), wxITEM_NORMAL);
    Menu_help->Append(MenuItem_about);
    MenuBar->Append(Menu_help, _("Help"));


    SetMenuBar(MenuBar);
    wxStatusBar* StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    StatusBar1->SetFieldsCount(1,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);


    Menu_File->Bind(wxEVT_COMMAND_MENU_SELECTED, [&](wxCommandEvent& e) {
        int id =  (int)e.GetId();
        if (id == idMenuNew){
            ui_drawer::tool_new();
        }else if (id == idMenuImport){
            ui_drawer::tool_import();
        }else if (id == idMenuOpen){
            ui_drawer::tool_open();
        }else if (id == idMenuSave){
            ui_drawer::tool_save();
        }
    });


    Menu_Edit->Bind(wxEVT_COMMAND_MENU_SELECTED, [&](wxCommandEvent& e) {
        int id =  (int)e.GetId();
        if (id == idMenuUndo){
            ui_drawer::tool_undo();
        }else if (id == idMenuRedo){
            ui_drawer::tool_redo();
        }else if (id == idMenuCut){
            ui_drawer::tool_cut();
        }else if (id == idMenuCopy){
            ui_drawer::tool_copy();
        }else if (id == idMenuPaste){
            ui_drawer::tool_paste();
        }else if (id == idMenuDelete){
            ui_drawer::tool_delete();
        }else if (id == idMenuSelectall){
            ui_drawer::tool_select_all();
        }
    });

    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&ShrewVHDLFrame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&ShrewVHDLFrame::OnAbout);

}


ShrewVHDLFrame::~ShrewVHDLFrame()
{
}

void ShrewVHDLFrame::OnClose(wxCloseEvent &event)
{
    Destroy();
}

void ShrewVHDLFrame::OnQuit(wxCommandEvent &event)
{
    Destroy();
}

void ShrewVHDLFrame::OnAbout(wxCommandEvent &event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(_("* Name:      Shrew VHDL\n"
 "* Purpose:   Free VHDL compiler and Simulator\n"
 "* Author:    Firas Hares (firas.hrs@gmail.com)\n"
 "* Created:   2022\n"
 "* Copyright: Firas Hares (https://github.com/firashrs/)"), "Shrew VHDL - About");
}
