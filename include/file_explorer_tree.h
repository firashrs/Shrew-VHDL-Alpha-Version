#ifndef FILE_EXPLORER_TREE_H
#define FILE_EXPLORER_TREE_H

#include <wx/treectrl.h>
#include <wx/frame.h>
#include <vector>
#include <iostream>
#include <string>
#include <wx/menu.h>
#include <wx/msgdlg.h>

#include "cmd_runner.h"
#include "file_handler.h"

#include "ui_drawer.h"
#include "core_functionalities.h"
class file_explorer_tree : public wxFrame
{
    public:
        file_explorer_tree(wxWindow* parent, wxWindowID id = -1);
        virtual ~file_explorer_tree();
        std::string get_file_path();
        std::string get_folder_path();

        wxTreeCtrl* get_treectrl();
        void import_folder(std::string folder_path);


        void OnContextMenuSelected(wxCommandEvent& event);



    protected:

    private:

        wxWindow* window_parent;
        static const long ID_TREECTRL1;
        core_functionalities* core;
        void OnTreeCtrl1ItemExpanding(wxTreeEvent& event);
        void OnTreeCtrl1ItemActivated(wxTreeEvent& event);


        void OnRightClickOnItem(wxTreeEvent& event);
        std::string full_path(wxTreeItemId id, std::string name);
        void add_folder_tree(std::string folder_path);
        void folder_parsing(std::string folder_path, wxTreeItemId parent);


        void right_click_option_open();
        int right_click_option_select();
        void right_click_option_compile();

        int check_path(std::string path);

        DECLARE_EVENT_TABLE()

};

#endif // FILE_EXPLORER_TREE_H
