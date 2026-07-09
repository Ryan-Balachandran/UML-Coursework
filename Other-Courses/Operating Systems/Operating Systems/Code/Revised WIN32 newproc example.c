/**
 * This program creates a separate process using the CreateProcess() system call.
 *
 * Figure 3.10
 *
 * @author Gagne, Galvin, Silberschatz, Galvin, and Gagne
 * Operating System Concepts  - Tenth Edition
 * Copyright John Wiley & Sons - 2018
 */
 
 // Updated by T. Wilkes July 2020

#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include <stdio.h>

int main(VOID)
{
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    char text[] = "C:\\WINDOWS\\system32\\whoami.exe";
    wchar_t wtext[32];
    mbstowcs(wtext, text, strlen(text) + 1); //Plus null
    LPWSTR cl = wtext;
 
    // Start the child process.
    if (!CreateProcess(NULL,   // No module name (use command line).
        cl,               // Command line.
        NULL,             // Process handle not inheritable.
        NULL,             // Thread handle not inheritable.
        FALSE,            // Set handle inheritance to FALSE.
        0,                // No creation flags.
        NULL,             // Use parent's environment block.
        NULL,             // Use parent's starting directory.
        &si,              // Pointer to STARTUPINFO structure.
        &pi)             // Pointer to PROCESS_INFORMATION structure.
        )
    {
        printf("CreateProcess failed (%d).\n", GetLastError());
        return -1;
    }

    // Wait until child process exits.
    WaitForSingleObject(pi.hProcess, INFINITE);

    // Close process and thread handles.
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}
