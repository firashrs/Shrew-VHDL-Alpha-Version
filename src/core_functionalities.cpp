#include "core_functionalities.h"
#include "ui_drawer.h"


std::string ghdl_path = "GHDL\\0.37-mingw32-mcode\\bin\\ghdl.exe";
std::string gtkwave_path = "gtkwave\\bin\\gtkwave.exe";

std::string log_file_path = "log.txt";
std::string error_file_path = "error_log.txt";


core_functionalities::core_functionalities()
{
    //ctor
}

core_functionalities::~core_functionalities()
{
    //dtor
}

void core_functionalities::compile(std::string wokring_file_path, std::string working_folder_path){

    if (wokring_file_path != "")
        ui_drawer::append_on_results("--COMPILING FILE : "+wokring_file_path);
    else
        ui_drawer::append_on_results("--COMPILING ALL FOLDER : "+working_folder_path);


    std::vector<std::string> all_files;
    std::vector<std::string> all_folders ;


//    std::vector<std::string> compiled_files;


    if (wokring_file_path != ""){
        all_files.push_back(wokring_file_path);

    }else if (working_folder_path != ""){
        std::string hirarchy = working_folder_path;
        all_folders.push_back(working_folder_path);
        for (int k = 0; k < all_folders.size(); k++){

            std::vector<std::string> tmp_files = file_handler::get_all_files_names_within_folder(all_folders[k], ".vhd");
            for (int i = 0; i < tmp_files.size(); i++){
                tmp_files[i] = all_folders[k]+"\\"+tmp_files[i];
            }
            all_files.insert(all_files.end(), tmp_files.begin(), tmp_files.end());


            std::vector<std::string> tmp_folders = file_handler::get_all_folders_names_within_folder(all_folders[k]);
            for (int i = 0; i < tmp_folders.size(); i++){
                tmp_folders[i] = all_folders[k]+"\\"+tmp_folders[i];
            }
            all_folders.insert(all_folders.end(), tmp_folders.begin(), tmp_folders.end());
        }


    }else{

        ui_drawer::append_on_results("Select A Folder or A File !");
        ui_drawer::pop_up("Select A Folder or A File !", "Alert !");
       // wxMessageBox("Select A Folder or A File!", _("Alert !"));
        //TextCtrl3->AppendText("\n");
        //TextCtrl3->AppendText("Select A Folder or A File !");
        return;
    }



    if (all_files.size() < 1){
       // TextCtrl3->AppendText("\n");
        //TextCtrl3->AppendText("No VHD Files in "+working_folder_path);
       // wxMessageBox("No files found!", _("Alert !"));

        ui_drawer::append_on_results("No VHD Files in "+working_folder_path);
        ui_drawer::pop_up("No files found!", "Alert !");
    }else{
        ui_drawer::append_on_results("--FOUND FILES LIST");
//        TextCtrl3->AppendText("\nSTART FOUND FILES LIST\n");
        for (int i = 0; i < all_files.size(); i++){
            ui_drawer::append_on_results("----"+std::to_string(i+1)+": "+all_files[i]);
          //  TextCtrl3->AppendText("\n");
           // TextCtrl3->AppendText(all_files[i]);

        }
        //TextCtrl3->AppendText("\n\nEND FOUND FILES LIST\n");

    }
    ui_drawer::append_on_results("------------------");

    for (int i =0; i<all_files.size(); i++){
        std::string vhd_file_path = all_files[i];

        ui_drawer::append_on_results("--COMPILING : "+std::to_string(i+1)+": "+vhd_file_path);

        std::string first_command = ghdl_path +" -s "+vhd_file_path+" > "+log_file_path+" 2> "+error_file_path;
        std::string second_command = ghdl_path +" -a "+vhd_file_path+" > "+log_file_path+" 2> "+error_file_path;


        //exec(first_command.c_str());

        int exit_code = cmd_runner::run_command_inside_app(first_command, "----"+all_files[i]+" : Syntax Verified");
        if (exit_code){

           // TextCtrl3->AppendText("\n\nCOMPILATION STOPPED: SYNTAX ERROR\n");
            ui_drawer::append_on_results("----COMPILATION STOPPED: SYNTAX ERROR");

            show_error_log();
        }else{
            show_log();
            exit_code = cmd_runner::run_command_inside_app(second_command, "----"+all_files[i]+" : Compiled");
            if (exit_code) {
             //   TextCtrl3->AppendText("\n\nCOMPILATION STOPPED: COMPILATION ERROR\n");
                ui_drawer::append_on_results("----COMPILATION STOPPED: COMPILATION ERROR");

                show_error_log();
            }else{
                show_log();
//                    compiled_files.push_back(all_files[i]);
//                if ( done_compiled_list->FindItem(0, all_files[i]) == -1 ){
//                    done_compiled_list->InsertItem(0, all_files[i]);
//                }
                ui_drawer::add_to_compiled_list(all_files[i]);
            }
        }


    }
}


void core_functionalities::simulate(std::string working_folder, std::string working_file, std::string chosen_entity_name){
    //std::string folder_path = selected_element;

    //std::string ghdl_path = "GHDL\\0.37-mingw32-mcode\\bin\\ghdl.exe";
    //std::string gtkwave_path = "gtkwave\\bin\\gtkwave.exe";

    std::string vcd_file_path = working_folder+"\\hi.vcd";

    //std::string log_file_path = "log.txt";
    //std::string error_file_path = "error_log.txt";

    if (chosen_entity_name == "")
        return ;


    std::string first_command = ghdl_path +" -r "+chosen_entity_name+" -s 0 -e 1000 --vcd="+vcd_file_path+" > "+log_file_path+" 2> "+error_file_path;
    std::string second_command = gtkwave_path +" "+ vcd_file_path+" > "+log_file_path+" 2> "+error_file_path;



    int exit_code = cmd_runner::run_command_inside_app(first_command, "--Simulated");

    if (exit_code){
      //  TextCtrl3->AppendText("\n\nSIMULATION STOPPED: SIMULATION ERROR\n");
        std::cout<<"SIMULATION STOPPED: SIMULATION ERROR"<<std::endl;

        show_error_log();
    }else{

        exit_code = cmd_runner::run_command_inside_app(second_command, "--Run Signal Viewer");
        std::cout<<"Run Signal Viewer"<<std::endl;
        if (exit_code){
           // TextCtrl3->AppendText("\n\nSIMULATION STOPPED: RUUNING ERROR\n");
            std::cout<<"SIMULATION STOPPED: RUUNING ERROR"<<std::endl;

            show_error_log();
        }else{
            show_log();
        }
    }
}

std::vector<std::string> core_functionalities::get_available_entities(){

    std::string cf_file = file_handler::get_cf_file_name();
    std::vector<std::string> entities = file_handler::get_all_entities_of_file(cf_file);

    ui_drawer::append_on_results("--ENTITIES LIST: ");
    for (int i = 0; i < entities.size(); i++)
        ui_drawer::append_on_results("----"+std::to_string(i+1)+": "+entities[i]);

    return entities;
}

//void core_functionalities::simulate_1(std::string working_folder, std::string working_file){
//
//    //std::string folder_path = selected_element;
//    //std::string main_entity_name = std::string(TextCtrl2->GetValue().mb_str());
//
//    //std::string ghdl_path = "GHDL\\0.37-mingw32-mcode\\bin\\ghdl.exe";
//    //std::string gtkwave_path = "gtkwave\\bin\\gtkwave.exe";
//
//    std::string vcd_file_path = working_folder+"\\hi.vcd";
//
//    //std::string log_file_path = "log.txt";
//    //std::string error_file_path = "error_log.txt";
//
//
//    file_handler::clean_simulations(vcd_file_path);
//
//
//
//    //TextCtrl3->AppendText("\n\n");
//   // TextCtrl3->AppendText("START READING ENITIES INSIDE "+cf_file+"\n\n");
////    for (int i = 0; i < entities.size(); i++){
//       // TextCtrl3->AppendText("\n"+entities[i]);
//    //}
//   // TextCtrl3->AppendText("\n\n");
//   // TextCtrl3->AppendText("END READING ENITIES\n\n");
//
//
//
//    //chosen_entity_name = ""
//    //this->Freeze();
//
//}

void core_functionalities::show_error_log(){
    std::ifstream error_file(error_file_path);
    std::string error_text;
    while (getline (error_file, error_text)) {
        ui_drawer::append_on_results(error_text, true);
    }
    error_file.close();
}


void core_functionalities::show_log(){

    std::ifstream log_file(log_file_path);
    std::string log_text;
    while (getline (log_file, log_text)) {
        ui_drawer::append_on_results(log_text);
    }
    log_file.close();
}
