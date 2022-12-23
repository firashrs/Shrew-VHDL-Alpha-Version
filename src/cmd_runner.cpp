#include "cmd_runner.h"


cmd_runner::cmd_runner()
{
    //ctor
}

cmd_runner::~cmd_runner()
{
    //dtor
}



int cmd_runner::run_command_inside_app(std::string command, std::string job, std::string* result , std::string* error){

    std::string log_file_path = "log.txt";
    std::string error_file_path = "error_log.txt";

    exec(command.c_str());



    int exit_code_var = 0;


    std::ifstream log_file(log_file_path);
    std::string log_text;
    while (getline (log_file, log_text)) {
        std::cout<<log_text<<std::endl;
       // ui_drawer::append_on_results(log_text);
    }
    log_file.close();


    std::ifstream error_file(error_file_path);
    std::string error_text;
    while (getline (error_file, error_text)) {
        exit_code_var = 1;
        std::cout<<error_text<<std::endl;
        //ui_drawer::append_on_results(error_text);
    }
    error_file.close();

    if (exit_code_var == 0){

        std::cout<<job<<std::endl;
       // ui_drawer::append_on_results(job);

    }

    return exit_code_var;
}

//std::string cmd_runner::exec(const char* cmd) {
//    std::array<char, 128> buffer;
//    std::string result;
//    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
//    if (!pipe) {
//        throw std::runtime_error("popen() failed!");
//    }
//    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
//        result += buffer.data();
//    }
//    return result;
//}

std::string cmd_runner::exec(const char* cmd) {
    system(cmd);

    return "";
}

