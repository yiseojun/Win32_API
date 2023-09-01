#include <iostream>
#include <windows.h>

using namespace std;

BOOL ReadProcess(HANDLE hProcess, uintptr_t memoryAdress, int intPtrRead) {
   BOOL rpmReturn = ReadProcessMemory(hProcess, (LPCVOID)memoryAdress, &intPtrRead, sizeof(int*), NULL);
   if(rpmReturn == FALSE) {
      cout << "ReadProcessMemory(INT) Failed. Get Last Error: " << dec << GetLastError() << endl;
      system("pause");
      return EXIT_FAILURE;
   }
   return rpmReturn;
}

BOOL ReadProcess(HANDLE hProcess, uintptr_t memoryAdress, char charPtrRead[]) {
   BOOL rpmReturn = ReadProcessMemory(hProcess, (LPCVOID)memoryAdress, charPtrRead, 128, NULL);
   if(rpmReturn == FALSE) {
      cout << "ReadProcessMemory(STRING) Failed. Get Last Error: " << dec << GetLastError() << endl;
      system("pause");
      return EXIT_FAILURE;
   }
   return rpmReturn;
}

int main() {
   DWORD pid = 0;
   cout << "PID: ";
   cin >> dec >> pid;

   HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
   if(hProcess == NULL) {
      cout << "OpenProcess Failed. GetLastError: " << dec << GetLastError() << endl;
      system("pause");
      return EXIT_FAILURE;
   }

   uintptr_t memoryAdress = 0x0;
   cout << "Memory Adress of Integer to Read (in Hex): 0x";
   cin >> hex >> memoryAdress;
   cout << "Reading 0x" << hex << uppercase << memoryAdress << "..." << endl;

   char charPtrRead[128];
   ReadProcess(hProcess, memoryAdress, charPtrRead);

   cout << "intRead = " << charPtrRead << endl;

   cout << "Press ENTER to Quit." << endl;
   system("pause>nul");

   return EXIT_SUCCESS;
}