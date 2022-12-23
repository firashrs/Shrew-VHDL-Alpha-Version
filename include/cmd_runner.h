#ifndef CMD_RUNNER_H
#define CMD_RUNNER_H

#include <iostream>
#include <fstream>
#include <string>
#include <memory>

/*
#include <cstdarg>
#include <Windows.h>
#include <cstdio>
#include <windows.h>*/

class cmd_runner
{
    public:
        cmd_runner();
        virtual ~cmd_runner();
        static int run_command_inside_app(std::string command, std::string job, std::string* result=NULL, std::string* error=NULL);

    protected:

    private:
        static std::string exec(const char* cmd);
};

#endif // CMD_RUNNER_H
