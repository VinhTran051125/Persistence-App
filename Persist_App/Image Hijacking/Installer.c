#include <windows.h>
#include <stdio.h>

int main() {

    const char* debuggerPath = "D:\\2.Subject_Document\\21.RE\\Image Hijacking\\IH.exe";
    const char* subkey = "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\test.exe";

    HKEY hKey;
    LONG lResult;

    lResult = RegCreateKeyExA(
        HKEY_LOCAL_MACHINE, 
        subkey, 
        0, 
        NULL, 
        REG_OPTION_NON_VOLATILE, 
        KEY_WRITE, 
        NULL, 
        &hKey, 
        NULL
    );

    if (lResult != ERROR_SUCCESS) {
        printf("Khong the mo/tao Key Registry. Ma loi: %ld\n", lResult);
        return 1;
    }

    lResult = RegSetValueExA(
        hKey, 
        "Debugger", 
        0, 
        REG_SZ, 
        (const BYTE*)debuggerPath, 
        (DWORD)(strlen(debuggerPath) + 1)
    );

    RegCloseKey(hKey);

    printf("...");
    getchar();
    return 0;
}
