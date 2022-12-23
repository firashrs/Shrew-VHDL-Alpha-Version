

#include "file_handler.h"

file_handler::file_handler()
{
}

file_handler::~file_handler()
{
    //dtor
}




std::string file_handler::get_cf_file_name(){
    std::string log_file_path = "log.txt";
    std::string error_file_path = "error_log.txt";
    std::string first_command = " dir /b *cf > "+log_file_path+" 2> "+error_file_path;
    int exit_code = cmd_runner::run_command_inside_app(first_command, "");



    std::ifstream log_file(log_file_path);
    std::string log_text;
    getline (log_file, log_text);
    log_file.close();

    return log_text;
}

void file_handler::clean_cache(){

    std::string log_file_path = "log.txt";
    std::string error_file_path = "error_log.txt";
    std::string command = "del *.cf > "+log_file_path+" 2> "+error_file_path;

    cmd_runner::run_command_inside_app(command, "\n\n Cleaned \n\n");
}

std::string file_handler::remove_spaces(std::string word){
    while (word[0] == ' '){
        word = word.substr(1, word.size()-1);
    }
    while (word[word.size()-1] == ' '){
        word = word.substr(0, word.size()-1);
    }

    return word;
}

std::vector<std::string> file_handler::get_all_entities_of_file(std::string file){

    std::vector<std::string> entities;

    std::ifstream vhd_file(file);
    std::string vhd_file_text;
    while (getline (vhd_file, vhd_file_text)) {
           // if (file.find(extension) != std::string::npos)
        std::string capt_vhd_file_text = vhd_file_text;
        for (auto & c: capt_vhd_file_text) c = toupper(c);

        int entity_pos = capt_vhd_file_text.find("ENTITY ");
        int at_pos = capt_vhd_file_text.find(" AT");
        int name_length = at_pos - entity_pos;


        if ( (entity_pos != -1) && (at_pos != -1) && (name_length > 0) ){
            std::string entity_name = vhd_file_text.substr(entity_pos+7, name_length-7);
            std::string no_space_entity_name = remove_spaces(entity_name);

            entities.push_back(no_space_entity_name);
        }


    }
    vhd_file.close();

    return entities;
}


//void file_handler::clean_simulations(std::string recent_vcd_path){
//
//
//    std::string log_file_path = "log.txt";
//    std::string error_file_path = "error_log.txt";
//    std::string command = "del "+recent_vcd_path+" > "+log_file_path+" 2> "+error_file_path;
//
//    cmd_runner::run_command_inside_app(command, "\n\n Cleaned Simulations \n\n");
//}

void file_handler::clean_simulations(){


    std::string log_file_path = "log.txt";
    std::string error_file_path = "error_log.txt";
    std::string command = "del *.vcd > "+log_file_path+" 2> "+error_file_path;

    cmd_runner::run_command_inside_app(command, "\n\n Cleaned Simulations \n\n");
}


std::string file_handler::get_parent_folder(std::string path){
    std::string directory_of = "\"Directory of \"";

    std::string log_file_path = "log.txt";
    std::string error_file_path = "error_log.txt";

    std::string first_command = " dir "+path+" | findstr "+directory_of+" > "+log_file_path+" 2> "+error_file_path;
    int exit_code = cmd_runner::run_command_inside_app(first_command, "");



    std::ifstream log_file(log_file_path);
    std::string log_text;
    getline (log_file, log_text);
    log_file.close();

    log_text = log_text.substr(directory_of.size()-1, log_text.size()-directory_of.size()+2);
    std::cout<<"("+log_text+")"<<std::endl;

    return log_text;



}

std::string file_handler::get_file_content(std::string file_path){
    std::ifstream file(file_path);
    std::string text;
    std::string content;

    //text = text.substr(directory_of.size()-1, text.size()-directory_of.size()+2);
    while (getline (file, text)) {
        if (content != ""){
            content = content+'\n';

        }
        content = content+text;
    }

    file.close();
    return content;
}

std::vector<std::string> file_handler::get_all_folders_names_within_folder(std::string folder)
{
    struct stat st;
    std::vector<std::string> folders;

    DIR *dir = opendir(folder.c_str());

    struct dirent *entry = readdir(dir);

    while (entry != NULL)
    {

       std::string s_dname = entry->d_name;
       std::string full_path = folder+"\\"+s_dname;

       if ( stat( full_path.c_str(), &st ) == 0 ){

            if (st.st_mode & S_IFDIR  ){
                if ( (s_dname != ".") && (s_dname != "..")){
                    folders.push_back(s_dname);
                    std::cout<<s_dname<<std::endl;
                }
            }
       }
        entry = readdir(dir);
    }

    closedir(dir);

    return folders;


}


void file_handler::save_file(std::string file, std::string content){
    std::ofstream myfile;
    myfile.open (file);
    myfile << content;
    myfile.close();
}


int file_handler::is_vhdl_file(std::string file, std::string extension){
    if (file.find(extension) != std::string::npos)
        return 1;
    return 0;
}



std::vector<std::string> file_handler::get_all_files_names_within_folder(std::string folder, std::string extension)
{
    struct stat st;
    std::vector<std::string> files;

    DIR *dir = opendir(folder.c_str());

    struct dirent *entry = readdir(dir);

    while (entry != NULL)
    {
       // if (entry->d_type == DT_DIR)

       std::string s_dname = entry->d_name;
       std::string full_path = folder+"\\"+s_dname;

       if ( stat( full_path.c_str(), &st ) == 0 ){

            if (st.st_mode & S_IFREG   ) {
                if (extension != ""){
                    if (is_vhdl_file(s_dname, extension)) {
                        files.push_back(s_dname);
                        std::cout<<s_dname<<std::endl;
                    }
                }else{
                    files.push_back(s_dname);
                    std::cout<<s_dname<<std::endl;

                }
            }
       }
        entry = readdir(dir);
    }

    closedir(dir);

    return files;


}

int file_handler::folder_is_empty(std::string folder)
{

    struct stat st;
    std::vector<std::string> folders;

    DIR *dir = opendir(folder.c_str());

    struct dirent *entry = readdir(dir);

    while (entry != NULL)
    {
       // if (entry->d_type == DT_DIR)

       std::string s_dname = entry->d_name;
       std::string full_path = folder+"\\"+s_dname;

       if ( stat( full_path.c_str(), &st ) == 0 ){

            if ( (s_dname != ".") && (s_dname != "..")){
                return 0;
            }

       }
        entry = readdir(dir);
    }

    closedir(dir);

    return 1;


}

int file_handler::folder_exists(std::string folder_path){

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


}
