#include <stdio.h>
#include <windows.h>

int main() {
        int varInt = 123456;
        char varChar[128] = "Long char array right there ->";
        int *ptr2int = &varInt;
        int **ptr2ptr = &ptr2int;
        int ***ptr2ptr2 = &ptr2ptr;
        
    do {
        printf("Process ID : %d\n\n", GetCurrentProcessId());
        printf("varInt       (0x%p) = %d\n", &varInt, varInt);
        printf("varChar[128] (0x%p) = %s\n\n", &varChar, varChar);

        printf("ptr2int      (0x%p) = 0x%p\n", &ptr2int, ptr2int);
        printf("ptr2ptr      (0x%p) = 0x%p\n", &ptr2ptr, ptr2ptr);
        printf("ptr2ptr2     (0x%p) = 0x%p\n\n", &ptr2ptr2, ptr2ptr2);

        printf("Press ENTER to print again.\n\n\n");
        getchar();

        printf("----------------------------------------------------------------------\n\n");
    }   while(1);
}