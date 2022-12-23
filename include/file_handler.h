#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include "cmd_runner.h"

#include <vector>
#include <dirent.h>
#include <sys/stat.h>

class file_handler
{
    public:
        file_handler();
        virtual ~file_handler();
        static int folder_exists(std::string folder_path);
        static int folder_is_empty(std::string folder);
        static int is_vhdl_file(std::string file, std::string extension);
        static std::string get_parent_folder(std::string path);
        static std::vector<std::string> get_all_folders_names_within_folder(std::string folder);
        static std::vector<std::string> get_all_files_names_within_folder(std::string folder, std::string extension = "");
        static void clean_simulations();
        static void clean_cache();
        static std::vector<std::string> get_all_entities_of_file(std::string file);
        static std::string get_cf_file_name();
        static std::string get_file_content(std::string file_path);
        static void save_file(std::string file, std::string content);



    protected:

    private:
        static std::string remove_spaces(std::string word);
};

#endif // FILE_HANDLER_H
