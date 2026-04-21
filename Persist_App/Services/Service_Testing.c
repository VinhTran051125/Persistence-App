#include <windows.h>
#include <stdio.h>

SERVICE_STATUS serviceStatus;
SERVICE_STATUS_HANDLE hStatus;

void WriteLog(const char* msg) {
    FILE *f = fopen("C:\\temp\\myservice.log", "a+");
    if (f) {
        fprintf(f, "%s\n", msg);
        fclose(f);
    }
}

void WINAPI ServiceCtrlHandler(DWORD ctrlCode) {
    switch (ctrlCode) {
        case SERVICE_CONTROL_STOP:
            WriteLog("Service stopping...");

            serviceStatus.dwCurrentState = SERVICE_STOPPED;
            SetServiceStatus(hStatus, &serviceStatus);
            return;

        default:
            break;
    }

    SetServiceStatus(hStatus, &serviceStatus);
}

void WINAPI ServiceMain(DWORD argc, LPTSTR *argv) {
    serviceStatus.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
    serviceStatus.dwCurrentState = SERVICE_START_PENDING;
    serviceStatus.dwControlsAccepted = SERVICE_ACCEPT_STOP;

    hStatus = RegisterServiceCtrlHandler("MyPersistenceService", ServiceCtrlHandler);

    if (hStatus == (SERVICE_STATUS_HANDLE)0) {
        return;
    }

    serviceStatus.dwCurrentState = SERVICE_RUNNING;
    SetServiceStatus(hStatus, &serviceStatus);

    WriteLog("Service started...");

    while (serviceStatus.dwCurrentState == SERVICE_RUNNING) {
        WriteLog("Service is running...");
        Sleep(5000);
    }

    WriteLog("Service exited...");
}

int main() {
    SERVICE_TABLE_ENTRY ServiceTable[] = {
        {"MyPersistenceService", (LPSERVICE_MAIN_FUNCTION)ServiceMain},
        {NULL, NULL}
    };

    StartServiceCtrlDispatcher(ServiceTable);
    return 0;
}
