#include "common.hpp"

wchar_t *wcmd;
char* command;

STARTUPINFOW si;
PROCESS_INFORMATION pi;
SECURITY_ATTRIBUTES sa;
HANDLE hRead, hWrite;

bool createPipeWin(void) 
{
    // Zera a memoria pra evitar lixo.
    ZeroMemory(&si, sizeof(STARTUPINFOW));
    ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));
    ZeroMemory(&sa, sizeof(SECURITY_ATTRIBUTES));

    sa.nLength = sizeof(SECURITY_ATTRIBUTES); // define o tamanho da estrutura SECURITY_ATTRIBUTES
    sa.bInheritHandle = TRUE; // permite que o process filho herde os ids do pipe
    sa.lpSecurityDescriptor = NULL; // usa as configs padroes

    if (!CreatePipe(&hRead, &hWrite, &sa, 0)) 
    { printf("Error creating pipe.\n"); return false; }

    // estrutura startup info
    si.cb = sizeof(si);
    si.dwFlags |= STARTF_USESTDHANDLES;
    si.hStdOutput = hWrite;
    si.hStdError = hWrite;
    si.hStdInput = hRead;

    wchar_t cmd[] = L"cmd.exe";

    // Usando CreateProcessW para lidar com wchar_t*
    if (!CreateProcessW(NULL, wcmd, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi))
    {
        DWORD errorCode = GetLastError();
        printf("Erro ao iniciar o terminal do Windows. Código de erro: %lu\n", errorCode);
        if (errorCode == (DWORD)2) { printf("error 2: FILE NOT FOUND\n"); }
        CloseHandle(hWrite);
        CloseHandle(hRead);
        return -1;
    }

    return true;
}

bool writeCommand(const char* commandStr) 
{
    
   DWORD bytesWritten;
   char formattedCommand[512];
   
   snprintf(formattedCommand, sizeof(formattedCommand), "%s\r\n", commandStr); // Adiciona quebra de linha

    if (!WriteFile(hWrite, formattedCommand, strlen(formattedCommand), &bytesWritten, NULL))
    {
        printf("Erro ao escrever comando no pipe.\n");
        return false;
    }

    return true;
}


bool alloc_space(void)
{
    wcmd = (wchar_t*)malloc(512 * sizeof(wchar_t));  // usando wchar_t* p strings unicode
    command = (char*)malloc(512 * sizeof(char));

    if (command == NULL || wcmd == NULL) return false;
    wcscpy(wcmd, L"cmd.exe");  // Definir cmd.exe corretamente
    return true;
}