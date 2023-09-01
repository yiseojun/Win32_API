#include <iostream>
#include <windows.h>

using namespace std;

// Class that access to other process
class ProcessAccess {
public :
   int mode;
   DWORD pid;
   BOOL flag = true;
   HANDLE hProcess;
   uintptr_t adress;

   ProcessAccess(DWORD pid) : pid(pid) {
      GetProcessHandle();

      while(flag) {
         cout << "SELECT MODE(Read = 0, Write = 1, EXIT = 2): ";
         cin >> mode;

         int IntRead;
         int IntWrite;

         switch(mode) {
            case 0 :
               IntRead = 0;
               cout << "Memory Address of the Integer to Read (in Hexadecimal): 0x";
               cin >> hex >> adress;

               ReadMemory(adress, &IntRead);

               break;
            case 1 :
               cout << "Memory Address of the Integer to Write (in Hexadecimal): 0x";
               cin >> hex >> adress;

               cout << "ENTER the Value to Overwrite: ";
               cin >> dec >> IntWrite;

               WriteMemory(adress, &IntWrite);

               break;
            case 2 :
               flag = false;

               break;
            default :
               flag = false;
         }
      }

      CloseHandle(hProcess);
      cout << "Press ENTER to Quit." << endl;
      system("pause > nul");
   }

   // Function to get a handle
   BOOL GetProcessHandle() {
      hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
      if(hProcess == NULL) {
         cout << "Failed to GetProcessHandle. GetLastError = " << GetLastError() << endl;
         system("pause");
         return EXIT_FAILURE;
      }
      return 0;
   }

   // Function to read content of memory
   BOOL ReadMemory(uintptr_t adress, int *IntRead) {
      BOOL RPMReturn = ReadProcessMemory(hProcess, (LPCVOID)adress, IntRead, sizeof(int), NULL);
      if(RPMReturn == FALSE) {
         cout << "Failed to ReadProcessMemory. GetLastError = " << GetLastError() << endl;
         cout << "\n---------------------------------------\n" << endl;
         system("pause");
         return EXIT_FAILURE;
      }

      PrintResult(*IntRead);
      return 0;
   }

   BOOL WriteMemory(uintptr_t adress, int *IntWrite) {
      BOOL WPMReturn = WriteProcessMemory(hProcess, (LPVOID)adress, IntWrite, sizeof(int), NULL);
      if(WPMReturn == FALSE) {
         cout << "Failed to WriteProcessMemory. GetLastError = " << GetLastError() << endl;
         cout << "\n---------------------------------------\n" << endl;
         system("pause");
         return EXIT_FAILURE;
      }
      else {
         cout << "The Request has been Successfully Processed." << endl;
         cout << "\n---------------------------------------\n" << endl;
      }

      return 0;
   }

   void PrintResult(int result) {
      cout << "\nResult = " << result << endl;
      cout << "\n---------------------------------------\n" << endl;
   }
};

int main() {
   DWORD pid;
   cout << "PID: ";
   cin >> pid;
   cout << endl;

   ProcessAccess Process(pid);
}