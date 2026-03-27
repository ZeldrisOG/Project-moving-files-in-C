#include <windows.h>
#include <string.h>
#include <ctype.h>

// This function handles the "Notepad Check"
BOOL IsNotepad() {
    char processName[MAX_PATH];
    // Get the name of the .exe that just loaded this DLL
    GetModuleFileNameA(NULL, processName, MAX_PATH);
    
    // Convert to lowercase and check if "notepad.exe" is in the string
    // strstr looks for a substring within a string
    if (strstr(processName, "notepad.exe") != NULL) {
        return TRUE;
    }
    return FALSE;
}

// 1. DLL Entry Point
BOOL APIENTRY DllMain(HMODULE hModule, DWORD nReason, LPVOID lpReserved) {
    if (nReason == DLL_PROCESS_ATTACH) {
        // Only run the setup if we are inside Notepad
        if (IsNotepad()) {
            // We don't show the message here anymore; 
            // we wait for the Insert key in the Hook procedure.
        }
    }
    return TRUE;
}

// 2. The Hook Procedure (The Gatekeeper for the INS key)
__declspec(dllexport) LRESULT CALLBACK MyHook(int nCode, WPARAM wParam, LPARAM lParam) {
    // Only process if it's a valid hook code and we are in Notepad
    if (nCode >= 0 && IsNotepad()) {
        
        // Check if a key was pressed (WM_KEYDOWN)
        // Note: For WH_GETMESSAGE hooks, the message is in the MSG struct
        PMSG pMsg = (PMSG)lParam;
        
        if (pMsg->message == WM_KEYDOWN) {
            // Check if the key is the INSERT key (VK_INSERT)
            if (pMsg->wParam == VK_INSERT) {
                MessageBoxA(NULL, "Injected", "Injector created by Zeldris", MB_OK);
            }
        }
    }
    
    // Always pass the message to the next hook in the chain
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}