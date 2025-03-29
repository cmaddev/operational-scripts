#ifndef common_hpp
#define common_hpp

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include <stdbool.h>
#ifdef __unix__
    #include<unistd.h>
    #define OS_TYPE LINUX
#elif defined(_WIN32) || defined(_WIN64)
    #include <windows.h>
    #include <direct.h>
    #define OS_TYPE WINDOWS
    extern wchar_t *wcmd;
    extern char* command;
    extern STARTUPINFOW si;             // Declarando extern
    extern PROCESS_INFORMATION pi;      // Declarando extern
    extern SECURITY_ATTRIBUTES sa;      // Declarando extern
    extern HANDLE hRead, hWrite;        // Declarando extern
    bool alloc_space(void);
    bool createPipeWin(void);
    bool writeCommand(const char* commandStr);
#endif

#define LINUX 10
#define WINDOWS 11

#define WIN_CMD_TEST1 "cmd.exe /c echo Hello, World!"
#define WIN_CMD_TEST2 "cmd.exe /c git"
#define WIN_CMD_TEST3 "cmd.exe /c echo Teste 3!"

#endif