/***************************************************************
 * Name:      ShrewVHDLMain.h
 * Purpose:   Defines Application Frame
 * Author:    Firas Hares (firas.hrs@gmail.com)
 * Created:   2022-12-11
 * Copyright: Firas Hares (https://github.com/firashrs/)
 * License:
 **************************************************************/

#ifndef SHREWVHDLMAIN_H
#define SHREWVHDLMAIN_H

#include "file_explorer_tree.h"
#include "cmd_runner.h"
#include "core_functionalities.h"
#include "file_handler.h"
#include "ui_drawer.h"

#include "ShrewVHDLApp.h"

class ShrewVHDLFrame: public wxFrame
{
    public:
        ShrewVHDLFrame(wxFrame *frame, const wxString& title);
        ~ShrewVHDLFrame();
        core_functionalities* core_funcs;
        void chosen_entity(std::string entity_selected);
    private:
        void OnClose(wxCloseEvent& event);
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        static const long idMenuQuit;
        static const long idMenuNew;
        static const long idMenuImport;
        static const long idMenuOpen;
        static const long idMenuSave;
        static const long idMenuAbout;
        static const long idMenuCompile;
        static const long idMenuSimulate;
        static const long idMenuUndo;
        static const long idMenuRedo;
        static const long idMenuCut;
        static const long idMenuCopy;
        static const long idMenuPaste;
        static const long idMenuDelete;
        static const long idMenuSelectall;
        static const long ID_STATUSBAR1;
        DECLARE_EVENT_TABLE()
};


#endif // ShrewVHDLMAIN_H
