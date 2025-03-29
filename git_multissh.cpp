#include "lib/common.hpp"

int main(int argc, char** argv)
{
    printf("Iniciando\n\n");
    
    if (!alloc_space()) {
        printf("Erro na alocação de memoria.\n");
        return -1;
    }
    
    if (!createPipeWin()) return -1;

    writeCommand("echo Hello, World!");
    writeCommand("git --version");

    CloseHandle(hWrite);

    char buffer[128];
    DWORD bytesRead;
    while(ReadFile(hRead, buffer, sizeof(buffer) - 1, &bytesRead, NULL) && bytesRead > 0)
    {
        buffer[bytesRead] = '\0';
        printf("%s", buffer);
        fflush(stdout);
    }

    DWORD lastError = GetLastError();
    if (lastError != ERROR_SUCCESS) { printf("Readfile errro code: $lu\n", lastError); }

    CloseHandle(hRead);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    printf("\n\nFinalizando o processo.\n\n");

    return 0;
}