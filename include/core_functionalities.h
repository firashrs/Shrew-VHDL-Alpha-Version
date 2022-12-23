#ifndef CORE_FUNCTIONALITIES_H
#define CORE_FUNCTIONALITIES_H


#include <iostream>
#include <vector>
#include "file_handler.h"

class core_functionalities
{
    public:
        core_functionalities();
        virtual ~core_functionalities();

        void compile(std::string wokring_file_path, std::string working_folder_path);

        //void simulate_1(std::string working_folder, std::string working_file);
        void simulate(std::string working_folder, std::string working_file, std::string chosen_entity_name="");
        std::vector<std::string> get_available_entities();


    protected:

    private:
        void show_error_log();
        void show_log();
};

#endif // CORE_FUNCTIONALITIES_H
