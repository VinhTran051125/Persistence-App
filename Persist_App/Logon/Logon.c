#include <stdio.h>
#include <windows.h>
#include <shlobj.h>

int Reg_Run(){
	char path[MAX_PATH];
	char appName = "MyPersistenceApp";
	
	
	if(GetModuleFileNameA(NULL, path, MAX_PATH) == 0){
		printf("Loi, %lu\n", GetLastError());
		return 1;
	}
	
	HKEY key;
	const char* regPath = "Software\\Microsoft\\Windows\\CurrentVersion\\Run";
	
	LSTATUS status = RegOpenKeyExA(HKEY_CURRENT_USER, regPath, 0, KEY_WRITE, &key);
	
	if(status != ERROR_SUCCESS){
		printf("Loi: %ld\n", status);
		return 1;
	}
	
	status = RegSetValueExA(
		key,
		appName,
		0,
		REG_SZ,
		(const BYTE*)path,
		(DWORD)(strlen(path) + 1)
	);
	
	RegCloseKey(key);
	
	if(status != ERROR_SUCCESS){
		printf("Loi: %ld\n", status);
		return 1 ;
	}
	
	printf("Registry Run da duoc kich hoat\n");
    return 0;
}

int main(){
	printf("...");
    getchar();
    return 0;
}
