#include "file_explorer_tree.h"

//std::vector<std::string> folder_trees_paths;
/*std::string log_file_path = "log.txt";
std::string error_file_path = "error_log.txt";*/

const long RIGHT_CLICK_MENU_COMMAND_OPEN = wxNewId();
const long RIGHT_CLICK_MENU_COMMAND_SELECT = wxNewId();
const long RIGHT_CLICK_MENU_COMMAND_COMPILE = wxNewId();
const long file_explorer_tree::ID_TREECTRL1 = wxNewId();


wxTreeCtrl* TreeCtrl1;

std::vector<wxTreeItemId> folders_expanded_already;
std::string tree_selected_element;
wxTreeItemId tree_selected_element_id;
wxTreeItemId tree_previous_selected_element_id;

std::vector<std::string> tree_folder_paths;

std::string tree_working_folder;
std::string tree_working_file;
wxButton* buttttonDialog;
wxFrame* parent_frame;

wxMenu menu;

file_explorer_tree* file_explorer;

/*
class fuckadjustFrame;

fuckadjustFrame* parent_frm;*/



BEGIN_EVENT_TABLE(file_explorer_tree,wxFrame)
    //(*EventTable(file_explorer_tree)
    //*)
END_EVENT_TABLE()


file_explorer_tree::file_explorer_tree(wxWindow* parent, wxWindowID id)
{

    //parent_frame = parent;
    TreeCtrl1 = new wxTreeCtrl(parent, ID_TREECTRL1, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE|wxTR_DEFAULT_STYLE, wxDefaultValidator, _T("ID_TREECTRL1"));

    window_parent = parent;


    core = new core_functionalities();

    /*parent_frm = (fuckadjustFrame*)window_parent;
    parent_frm->compile();*/

    //fuckadjustFrame::compile();

    menu.Append(RIGHT_CLICK_MENU_COMMAND_OPEN, "Open");
    menu.Append(RIGHT_CLICK_MENU_COMMAND_SELECT, "Select");
    menu.Append(RIGHT_CLICK_MENU_COMMAND_COMPILE, "Compile");
    menu.Bind(wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&file_explorer_tree::OnContextMenuSelected, this);

    TreeCtrl1->Bind(wxEVT_TREE_ITEM_EXPANDED, (wxObjectEventFunction)&file_explorer_tree::OnTreeCtrl1ItemExpanding, parent);
    TreeCtrl1->Bind(wxEVT_TREE_ITEM_ACTIVATED, (wxObjectEventFunction)&file_explorer_tree::OnTreeCtrl1ItemActivated, parent);
    TreeCtrl1->Bind(wxEVT_TREE_ITEM_RIGHT_CLICK, (wxObjectEventFunction)&file_explorer_tree::OnRightClickOnItem, parent);



    TreeCtrl1->AddRoot("Files");

}

wxTreeCtrl* file_explorer_tree::get_treectrl(){
    return TreeCtrl1;
}

file_explorer_tree::~file_explorer_tree()
{
    //dtor
}


std::string file_explorer_tree::full_path(wxTreeItemId id, std::string name){
    std::string path = name;
    wxTreeItemId last_id = id;
    std::string parent_name = "";

    if (id == (TreeCtrl1->GetRootItem()))
        return path;

    last_id = (wxTreeItemId)TreeCtrl1->GetItemParent(last_id);
    parent_name = (std::string)TreeCtrl1->GetItemText(last_id);

    while(last_id != (TreeCtrl1->GetRootItem())){
        path = parent_name+"\\"+path;
        last_id = (wxTreeItemId)TreeCtrl1->GetItemParent(last_id);
        parent_name = (std::string)TreeCtrl1->GetItemText(last_id);

    }
    return path;
}

/*
int file_explorer_tree::folder_exists(std::string folder_path){

    std::string log_file_path = "log.txt";
    std::string error_file_path = "error_log.txt";
    std::string first_command = " icacls "+folder_path+" > "+log_file_path+" 2> "+error_file_path;
    int exit_code = cmd_runner::run_command_inside_app(first_command, "YAAAYYYY IT EXISTS");


    std::ifstream error_file(error_file_path);
    std::string error_text;
    if (getline (error_file, error_text)){
        error_file.close();
        return 0;
    }

    error_file.close();
    return 1;


}*/

void file_explorer_tree::add_folder_tree(std::string folder_path){
    for (int i = 0; i < tree_folder_paths.size(); i++){
        if (tree_folder_paths[i] == folder_path)
            return;
    }
    tree_folder_paths.push_back(folder_path);
}





void file_explorer_tree::OnContextMenuSelected(wxCommandEvent& event)
{
        //const int select_command = RIGHT_CLICK_MENU_COMMAND_SELECT;


       /* TreeCtrl1->UnselectAll();
        TreeCtrl1->UnselectItem();

        TreeCtrl1->SelectItem(selected_element_id);*/

        //wxTextAttr ta;
       // ta.SetFontWeight(wxFONTWEIGHT_BOLD);
        //wxTreeItemId tmp = TreeCtrl1->AppendItem(parent, files[i]);




        if (event.GetId() == RIGHT_CLICK_MENU_COMMAND_SELECT){


            right_click_option_select();




        }else if (event.GetId() == RIGHT_CLICK_MENU_COMMAND_COMPILE){


            right_click_option_compile();
        }else if (event.GetId() == RIGHT_CLICK_MENU_COMMAND_OPEN){


            right_click_option_open();
        }


}

void file_explorer_tree::folder_parsing(std::string folder_path, wxTreeItemId parent){

    if (parent != (TreeCtrl1->GetRootItem()))
        TreeCtrl1->DeleteChildren(parent);

    std::vector<std::string> files = file_handler::get_all_files_names_within_folder(folder_path);
    for (int i = 0; i < files.size(); i++){

        wxTreeItemId tmp = TreeCtrl1->AppendItem(parent, files[i]);
    }

    std::cout<<"-----------------------"<<std::endl;
    std::vector<std::string> folders = file_handler::get_all_folders_names_within_folder(folder_path);

    for (int i = 0; i < folders.size(); i++){
        wxTreeItemId child2Id = TreeCtrl1->AppendItem(parent, folders[i]);

        if (!file_handler::folder_is_empty(full_path(child2Id, folders[i]))){
            TreeCtrl1->AppendItem(child2Id, "tmp");
        }

    }


}

void file_explorer_tree::import_folder(std::string folder_path){

    if ( ! file_handler::folder_exists(folder_path) )
        return;



    add_folder_tree(folder_path);


    TreeCtrl1->DeleteChildren(TreeCtrl1->GetRootItem());

    for (int i = 0; i < tree_folder_paths.size(); i++ ){


        //std::cout<<tree_folder_paths[i]<<std::endl;
        wxTreeItemId child2Id = TreeCtrl1->AppendItem((TreeCtrl1->GetRootItem()), tree_folder_paths[i]);
        if (!file_handler::folder_is_empty(tree_folder_paths[i])){
            TreeCtrl1->AppendItem(child2Id, "tmp");
        }
        folder_parsing(tree_folder_paths[i], child2Id);
        TreeCtrl1->Expand((TreeCtrl1->GetRootItem()));

        tree_selected_element = tree_folder_paths[i];
        tree_selected_element_id = child2Id;
        right_click_option_select();
    }
}


void file_explorer_tree::OnRightClickOnItem(wxTreeEvent& event){

    wxTreeItemId id =  event.GetItem();
    if (!id.IsOk())
        return;

    std::string text =  (std::string)TreeCtrl1->GetItemText(id);




    TreeCtrl1->SelectItem(id);
    tree_selected_element = full_path(id, text);
    tree_selected_element_id = id;

    //TreeCtrl1->get
    //wxTreeItemId itt = TreeCtrl1->GetSelection();

    PopupMenu(&menu);
  //  menu.Bind(wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&file_explorer_tree::OnContextMenuSelected, this);

}



int file_explorer_tree::check_path(std::string path){
    if (file_handler::folder_exists(tree_selected_element)){
        tree_working_folder = file_handler::get_parent_folder(tree_selected_element);

        //StaticText1->SetLabel(working_folder);
        ui_drawer::change_working_folder(tree_working_folder);

        if (file_handler::is_vhdl_file(tree_selected_element, ".vhd")){
            //StaticText2->SetLabel(selected_element);
            ui_drawer::change_working_file(tree_selected_element);
            tree_working_file = tree_selected_element;

            ui_drawer::append_on_results("SELECTED FILE: "+tree_selected_element);
        }else{
            ui_drawer::change_working_file("");
            tree_working_file = "";

            ui_drawer::append_on_results("SELECTED FOLDER: "+tree_working_folder);
        }

        return 1;

    }else{
        return 0;
    }
}

int file_explorer_tree::right_click_option_select(){

    int show_popup = 0;
    wxString str;
    if (tree_selected_element == "")
        return 0;

    if (check_path(tree_selected_element)){
        if (tree_previous_selected_element_id.IsOk()){
            TreeCtrl1->SetItemBold(tree_previous_selected_element_id, 0);
        }

        TreeCtrl1->SetItemBold(tree_selected_element_id, 1);


        tree_previous_selected_element_id = tree_selected_element_id;

        if (show_popup){
            str = tree_selected_element;
            wxMessageBox(str);
        }

        return 1;

    }
    return 0;

    //parent_frm->compile();
}


std::string file_explorer_tree::get_file_path(){
    return tree_working_file;
}
std::string file_explorer_tree::get_folder_path(){
    return tree_working_folder;
}

void file_explorer_tree::right_click_option_open(){

    if (right_click_option_select()){
        if (tree_working_file != "")
            ui_drawer::open_file(tree_working_file);

    }
}


void file_explorer_tree::right_click_option_compile(){

    if (right_click_option_select())
        core->compile(tree_working_file, tree_working_folder);
}

void file_explorer_tree::OnTreeCtrl1ItemActivated(wxTreeEvent& event){
    OnTreeCtrl1ItemExpanding(event);

    wxTreeItemId id =  event.GetItem();
    if (!id.IsOk())
        return;

    std::string text =  (std::string)TreeCtrl1->GetItemText(id);




    TreeCtrl1->SelectItem(id);
    tree_selected_element = full_path(id, text);
    tree_selected_element_id = id;


    right_click_option_open();

}


void file_explorer_tree::OnTreeCtrl1ItemExpanding(wxTreeEvent& event)
{
    wxTreeItemId id =  (wxTreeItemId)event.GetItem();
    std::string text =  (std::string)TreeCtrl1->GetItemText(event.GetItem());

    for (int i =0; i < folders_expanded_already.size(); i++){
        if (folders_expanded_already[i] == id ){
            return;
        }
    }
    folders_expanded_already.push_back(id);
    std::cout<<("----"+full_path(id, text))<<std::endl;
    folder_parsing (full_path(id, text), id);


    //right_click_option_select();
}


