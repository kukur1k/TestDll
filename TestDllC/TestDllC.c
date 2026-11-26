#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
    HMODULE dll = LoadLibraryA("MyNewDll.dll");
    system("chcp 1251");

    if (dll == NULL)
    {
        printf("Ошибка загрузки DLL: %lu\n", GetLastError());
        return 1;
    }


    struct User {
        char* Surname;
        char* Name;
        char* Patronynic;
        int Age;
    } typedef User;

    typedef int (*ReadDataFunc)(void);
    ReadDataFunc ReadData = (ReadDataFunc)GetProcAddress(dll, "ReadData");

    typedef int (*ShowAllListFunc)(void);
    ShowAllListFunc ShowAllList = (ShowAllListFunc)GetProcAddress(dll, "ShowAllList");

    typedef int (*SearchByStrFunc)(char*);
    SearchByStrFunc SearchByStr = (SearchByStrFunc)GetProcAddress(dll, "SearchBySurname");

    int countAddUsers = ReadData();
    printf("\ncount users was readed: %d\n", countAddUsers);

    ShowAllList();

  /*  printf("\nВведите строку для поиска по фамилии:\n");
    char* searchStr = calloc(100, sizeof(char));
    gets(searchStr);
    int searchResCount = SearchByStr(searchStr);
    printf("\ncount users was search: %d\n", searchResCount);*/


    User testUsers[5] = {
    { "Иванов",  "Иван",  "Иванович",  30 },
    { "Петров",  "Пётр",  "Петрович",  25 },
    { "Сидоров", "Сидор", "Сидорович", 40 },
    { "Кузнецов","Кузьма","Кузьмич",   35 },
    { "Смирнов", "Семён", "Семёнович", 28 }
    };

    typedef int (*WriteDataFunc)(const char*, User*, int);
    WriteDataFunc WriteData = (WriteDataFunc)GetProcAddress(dll, "WriteData");

    int written = WriteData("D:\\SystemProgramming\\TestDll\\UsersOut.csv", testUsers , 5);
    printf("\ncount users was written: %d\n", written);


    typedef double (*AvgAgeFunc)(User*, int);
    AvgAgeFunc AvgAge = (AvgAgeFunc)GetProcAddress(dll, "AvgAge");

    int avgAge = AvgAge(testUsers, 5);
    printf("\navg age = %d\n", avgAge);



}
