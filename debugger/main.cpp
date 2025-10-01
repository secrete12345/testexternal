#include <windows.h>
#include <iostream>
#include <vector>
#include <string>
#include <conio.h>
void positiontest(HANDLE hProv,float replaceVal){// DO NOT USE THIS FUNCTION YET
    SYSTEM_INFO sysInfo;
    GetSystemInfo(&sysInfo);
    LPCVOID start = sysInfo.lpMinimumApplicationAddress;
    LPCVOID end = sysInfo.lpMinimumApplicationAddress;
    MEMORY_BASIC_INFORMATION mbi;
    std::vector<BYTE> buffer;
    float val[mbi.RegionSize];
    float val2[mbi.RegionSize];
    std::vector<uint_ptr> mem_read;
    while(start < end){
        if(VirtualQueryEx(hProc,start,&mbi,sizeof(mbi)) && mbi.State == MEM_COMMIT && (mbi.Protect & PAGE_READWRITE)) {
            buffer.resize(mbi.RegionSize);
            SIZE_T bytesread;
            do {
                key_pressed = _getch();
            } while (key_pressed != 'k');

            if (GetAsyncKeyState(VK_K) & 0x8000) {
                if(ReadProcessMemory(hProc , start , buffer.data() , mbi.RegionSize , &bytesread)){
                     for (SIZE_T i = 0; i < bytesRead - sizeof(float); i++) {
                        
                        memcpy(&val[i], &buffer[i], sizeof(float));

                         
                     }
                }
            }
            Sleep(1);
            do {
                key_pressed = _getch();
            } while (key_pressed != 'k');
            if (GetAsyncKeyState(VK_K) & 0x8000) {
                if(ReadProcessMemory(hProc , start , buffer.data() , mbi.RegionSize , &bytesread)){
                     int count = 0;
                     for (SIZE_T i = 0; i < bytesRead - sizeof(float); i++) {
                        
                        memcpy(&val2, &buffer[i], sizeof(float));

                        if (val == val2) {
                            
                            uintptr_t addrToWrite = (uintptr_t)start + i;
                            std::cout << count << ": " << val << std::endl;
                            mem_read[count] = addrToWrite;                         
                            //WriteProcessMemory(hProc, (LPVOID)addrToWrite, &replaceVal, sizeof(int), nullptr);
                            //std::cout << "Replaced int at: " << (void*)addrToWrite << " (was " << val << ")\n";
                        }
                        count++;
                     }
                }
            }
            
            }          
            
        }
    }
    int option;
    std::cout << "Option 1: all address\n";
    std::cout << "       2: select index\n";
    std::cin >> option;
    if(option == 1){
        for(int i = 0; i <= mem_read.size(); i++){   
            WriteProcessMemory(hProc , (LPCVOID)mem_read[i],&replaceval,sizeof(float) , nullptr);
        }
    }
}
void integer(HANDLE hProc, int target, int replaceVal) {
    

    SYSTEM_INFO sysInfo;
    GetSystemInfo(&sysInfo);
    LPCVOID start = sysInfo.lpMinimumApplicationAddress;
    LPCVOID end = sysInfo.lpMaximumApplicationAddress;

    MEMORY_BASIC_INFORMATION mbi;
    std::vector<BYTE> buffer;
    //int test = 0; // for testing
    while (start < end) {
        //test += 1;
        if (VirtualQueryEx(hProc, start, &mbi, sizeof(mbi)) && mbi.State == MEM_COMMIT && (mbi.Protect & PAGE_READWRITE)) {

            buffer.resize(mbi.RegionSize);
            SIZE_T bytesRead;
            if (ReadProcessMemory(hProc, start, buffer.data(), mbi.RegionSize, &bytesRead)) {

                for (SIZE_T i = 0; i < bytesRead - sizeof(int); i++) {
                    int val;
                    memcpy(&val, &buffer[i], sizeof(int));

                    if (val == target) {

                        uintptr_t addrToWrite = (uintptr_t)start + i;
                        WriteProcessMemory(hProc, (LPVOID)addrToWrite, &replaceVal, sizeof(int), nullptr);
                        std::cout << "Replaced int at: " << (void*)addrToWrite << " (was " << val << ")\n";
                    }
                }
            }
        }
        start = (LPCVOID)((uintptr_t)start + mbi.RegionSize);
    }
}

void ScanAndReplaceFloat(HANDLE hProc, float targetMin, float targetMax, float replaceVal) {
    const float epsilon = 0.001f; // for inaccuracy of float

    SYSTEM_INFO sysInfo;
    GetSystemInfo(&sysInfo);
    LPCVOID start = sysInfo.lpMinimumApplicationAddress;
    LPCVOID end = sysInfo.lpMaximumApplicationAddress;

    MEMORY_BASIC_INFORMATION mbi;
    std::vector<BYTE> buffer;
    //int test = 0; // for testing
    while (start < end) {
        //test += 1;
        if (VirtualQueryEx(hProc, start, &mbi, sizeof(mbi)) && mbi.State == MEM_COMMIT && (mbi.Protect & PAGE_READWRITE)) {
            
            buffer.resize(mbi.RegionSize);
            SIZE_T bytesRead;
            if (ReadProcessMemory(hProc, start, buffer.data(), mbi.RegionSize, &bytesRead)) {
                
                for (SIZE_T i = 0; i < bytesRead - sizeof(float); i++) {
                    float val;
                    memcpy(&val, &buffer[i], sizeof(float));

                    if (val >= (targetMin - epsilon) && val <= (targetMax + epsilon)) {
                        
                        uintptr_t addrToWrite = (uintptr_t)start + i;
                        WriteProcessMemory(hProc, (LPVOID)addrToWrite, &replaceVal, sizeof(float), nullptr);
                        std::cout << "Replaced float at: " << (void*)addrToWrite << " (was " << val << ")\n";
                    }
                }
            }
        }
        start = (LPCVOID)((uintptr_t)start + mbi.RegionSize);
    }
}


void ScanAndReplaceString(HANDLE hProc, const std::string& target, const std::string& replacement) {
    if (replacement.size() > target.size()) {
        std::cerr << "Replacement string must not be longer than target string.\n";
        return;
    }

    SYSTEM_INFO sysInfo;
    GetSystemInfo(&sysInfo);
    LPCVOID start = sysInfo.lpMinimumApplicationAddress;
    LPCVOID end = sysInfo.lpMaximumApplicationAddress;

    MEMORY_BASIC_INFORMATION mbi;
    std::vector<BYTE> buffer;

    while (start < end) {
        if (VirtualQueryEx(hProc, start, &mbi, sizeof(mbi)) && mbi.State == MEM_COMMIT && (mbi.Protect & PAGE_READWRITE)) {
            buffer.resize(mbi.RegionSize);
            SIZE_T bytesRead;
            if (ReadProcessMemory(hProc, start, buffer.data(), mbi.RegionSize, &bytesRead)) {
                for (SIZE_T i = 0; i < bytesRead - target.size(); i++) {
                    if (memcmp(&buffer[i], target.c_str(), target.size()) == 0) {
                        uintptr_t addrToWrite = (uintptr_t)start + i;
                        WriteProcessMemory(hProc, (LPVOID)addrToWrite, replacement.c_str(), replacement.size(), nullptr);
                        std::cout << "Replaced string at: " << (void*)addrToWrite << "\n";
                    }
                }
            }
        }
        start = (LPCVOID)((uintptr_t)start + mbi.RegionSize);
    }
}

int main() {
    DWORD pid;
    std::cout << "Enter PID of target process: ";
    std::cin >> pid;

    HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);//hproc
    if (!hProc) {
        std::cerr << "Failed to open process.\n";
        return 1;
    }

    while (true) {
        std::cout << "\nMenu:\n";
        std::cout << "1. Scan for integer\n";
        std::cout << "2. Scan for float range and replace\n";
        std::cout << "3. Scan for string and replace\n";
        std::cout << "4. Exit\n";
        std::cout << "Choice: ";

        int choice;
        std::cin >> choice;

        if (choice == 1) { //updated haven't check yet 30/9/25
            int val , replacetar;
            std::cout << "Enter integer to scan for: ";
            std::cin >> val;
            std::cout << "Enter interger to replace: ";
            std::cin >> replacetar;
            integer(hProc , val , replacetar);
        }
        else if (choice == 2) {
            float minVal, maxVal, replaceVal;
            std::cout << "Enter min float value: ";
            std::cin >> minVal;
            std::cout << "Enter max float value: ";
            std::cin >> maxVal;
            std::cout << "Enter replacement float value: ";
            std::cin >> replaceVal;
            ScanAndReplaceFloat(hProc, minVal, maxVal, replaceVal);

        }
        else if (choice == 3) {
            std::string target, replacement;
            std::cout << "Enter target string: ";
            std::cin >> target;
            std::cout << "Enter replacement string (must be same or smaller length): ";
            std::cin >> replacement;
            ScanAndReplaceString(hProc, target, replacement);

        }
        else if (choice == 4) {
            break;
        }
    }

    CloseHandle(hProc);
    return 0;
}



