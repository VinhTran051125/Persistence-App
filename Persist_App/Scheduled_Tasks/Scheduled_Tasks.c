#include <stdio.h>
#include <windows.h>
#include <shlobj.h>

int ScheduledTasks(){
	char path[MAX_PATH];	
	
	if(GetModuleFileNameA(NULL, path, MAX_PATH) == 0){
		printf("Khong lay duoc duong dan, %lu\n", GetLastError());
		return 1;
	}
	
	char command[1024];
    snprintf(command, 
			sizeof(command), 
             "schtasks /create /tn \"MySystemUpdate\" /tr \"%s\" /sc onlogon /rl highest /f", 
             path
	);
             
    int result = system(command);

    if (result == 0) {
    	printf("1", result);
    } else {
        printf("That bai. Ma loi: %d\n", result);
    }
    return 0;
}

int main(){

	ScheduledTasks();
		
	printf("...");
    getchar();
    return 0;
}
