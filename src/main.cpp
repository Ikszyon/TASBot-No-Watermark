#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <algorithm>


static char* TASBotBase = reinterpret_cast<char*>(GetModuleHandle("tBot.dll"));


size_t GetOffset(const char* Buffer, size_t Length, const char* String) {
    return std::search(Buffer, Buffer + Length, String, String + strlen(String)) - Buffer;
}

void TerminateString(void* Address) {
    DWORD Old;
    VirtualProtect(Address, 1, PAGE_EXECUTE_READWRITE, &Old);
    memcpy(Address, "\0", 1);
    VirtualProtect(Address, 1, Old, &Old);
}


DWORD APIENTRY MainThread(LPVOID lpParam) {

    TerminateString(TASBotBase + GetOffset(TASBotBase, 5000000, "Replay by TASBOT"));
    TerminateString(TASBotBase + GetOffset(TASBotBase, 5000000, "Replay by TASBOT"));

    return S_OK;
}

DWORD WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved) {
    switch(dwReason) {
        case DLL_PROCESS_ATTACH:
            CreateThread(NULL, 0x10000, reinterpret_cast<LPTHREAD_START_ROUTINE>(&MainThread), NULL, 0, NULL);
            break;

        default:
            break;
    }

    return TRUE;
}