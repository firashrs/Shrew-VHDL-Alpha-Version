#ifndef UI_DRAWER_H
#define UI_DRAWER_H

#include <iostream>
#include <wx/frame.h>
#include <wx/textctrl.h>
#include <wx/button.h>
#include <wx/listctrl.h>
#include <wx/stattext.h>
#include <wx/stc/stc.h>
#include <wx/sashwin.h>
#include <wx/sizer.h>
#include <wx/gbsizer.h>
#include <wx/splitter.h>
#include <wx/notebook.h>
#include <wx/toolbar.h>
#include <wx/artprov.h>
#include <wx/filedlg.h>
#include <wx/wfstream.h>
#include <wx/log.h>
#include <wx/dirdlg.h>
#include <wx/aui/auibook.h>

#include <wx/artprov.h>
#include <wx/bitmap.h>
#include <wx/icon.h>
#include <wx/image.h>
#include <wx/intl.h>
#include <wx/string.h>
#include "core_functionalities.h"
#include "entity_select_form.h"
#include "file_explorer_tree.h"
#include "file_handler.h"

class ui_drawer: public wxFrame
{
    public:
        ui_drawer(wxWindow* parent, wxWindowID id = -1);
        static void draw_everything (wxWindow* parent, wxWindowID id, int window_x, int window_y, core_functionalities* core_funcs,  file_handler* main_file_handler);
        virtual ~ui_drawer();
        static void append_on_results(std::string words, bool is_error=false);
        static void pop_up(std::string message, std::string title);
        static void add_to_compiled_list(std::string file);


        static void change_working_folder(std::string folder);
        static void change_working_file(std::string file);
        static void close_entity_choosing_form(bool chosen, std::string entity_chosen);
        static void open_file(std::string file);
        static wxToolBar*  get_toolbar();

        static wxStyledTextCtrl* create_code_page(std::string content);



        static void OnSplitDpl(wxSplitterEvent& event);
        static void OnSplitChnging(wxSplitterEvent& event);

        static void tool_new();
        static void tool_import();
        static void tool_open();
        static void tool_save();
        static void tool_saveas(int page_number);
        static void tool_compile();
        static void tool_undo();
        static void tool_redo();
        static void tool_cut();
        static void tool_copy();
        static void tool_paste();
        static void tool_delete();
        static void tool_select_all();
        static void tool_simulate();

        //static wxTextCtrl* TextCtrl3;

    protected:

    private:
        static const long ID_TOOL_NEW;
        static const long ID_TOOL_IMPORT ;
        static const long ID_TOOL_OPEN ;
        static const long ID_TOOL_COMPILE;
        static const long ID_TOOL_SIMULATE;
        static const long ID_TOOL_SAVE;


};

#endif // UI_DRAWER_H
