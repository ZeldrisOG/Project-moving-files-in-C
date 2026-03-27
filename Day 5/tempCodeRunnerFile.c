#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int main() {
        printf("Welcome to my project\n");
        // welcome message

       char* src = "C:\\Users\\Admin\\Placement\\test.txt";
       char* dst = "C:\\Users\\Admin\\Placement\\Day 5\\test.txt";
        // source and location i want to move the file to

        // move file Ex a powerful windows api method of moving files 
       if (MoveFileEx(src, dst, MOVEFILE_REPLACE_EXISTING)) {
        printf("Success! File moved and overwritten if it existed.\n");
    } else {
        printf("Failed. Error code: %lu\n", GetLastError());
    }
    return 0;
}
