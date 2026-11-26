#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
    HMODULE dll = LoadLibraryA("C:\\SystemProgramming\\MyNewDll\x64\Debug\MyNewDll.dll");

    if (dll == NULL)
    {
        printf("Ошибка загрузки DLL: %lu\n", GetLastError());
        return 1;
    }

    typedef int (*ReadDataFunc)(void);
    ReadDataFunc ReadData =
        (ReadDataFunc)GetProcAddress(dll, "ReadData");

    typedef int (*ShowAllList)(void);
    ReadDataFunc ShowAllList =
        (ReadDataFunc)GetProcAddress(dll, "ShowAllList");

    ReadData;
    ShowAllList;
}
