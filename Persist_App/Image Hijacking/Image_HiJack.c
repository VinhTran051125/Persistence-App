#include <windows.h>
#include <stdio.h>
#include <process.h>

int main(int argc, char* argv[]) {

    printf("Image Hijacking!\n");

    Sleep(2000);

    if (argc > 1) {
        system(argv[1]); 
    } else {
        system("test.exe");
    }

    return 0;
}
