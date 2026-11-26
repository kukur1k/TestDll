#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


struct User {
    char* Surname;
    char* Name;
    char* Patronynic;
    int Age;
} typedef User;


User* userlist = NULL;
size_t userCount = 0;


BOOL WINAPI DllMain(HINSTANCE hlnstDll, DWORD dwReason, LPVOID IpReserved)
{
    MessageBoxA(NULL, "NEW DLL LOADED", "DEBUG", MB_OK);
    BOOL bAllWentWell = TRUE;
    switch (dwReason)
    {
    case DLL_PROCESS_ATTACH:
        break;
    case DLL_THREAD_ATTACH:
        break;
    case DLL_THREAD_DETACH:
        break;
    case DLL_PROCESS_DETACH:
        break;
    }
    if (bAllWentWell)

        return TRUE;
    else
        return FALSE;
}


BOOL AddUser(char* surname, char* name, char* patronymic, int age) {
    User* tmp = (User*)realloc(userlist, (userCount + 1) * sizeof(User));
    userlist = tmp;
    User* newU = &userlist[userCount];

    newU->Surname = _strdup(surname);
    newU->Name = _strdup(name);
    newU->Patronynic = _strdup(patronymic);

    if (!newU->Surname || !newU->Name || !newU->Patronynic)
    {
        free(newU->Surname);
        free(newU->Name);
        free(newU->Patronynic);
        return FALSE;
    }

    newU->Age = age;

    userCount++;
    return TRUE;
}

BOOL ParseUserLine(const char* line)
{
    char buf[256];
    strncpy_s(buf, sizeof(buf), line, _TRUNCATE);

    char* ctx = NULL;
    char* surname = strtok_s(buf, ";", &ctx);
    char* name = strtok_s(NULL, ";", &ctx);
    char* patronymic = strtok_s(NULL, ";", &ctx);
    char* ageStr = strtok_s(NULL, ";", &ctx);

    if (!surname || !name || !patronymic || !ageStr)
        return FALSE;

    printf("Surname: %s\n", surname);
    printf("Name: %s\n", name);
    printf("Patronymic: %s\n", patronymic);
    printf("Age string: %s\n", ageStr);

    int age = atoi(ageStr);


    AddUser(surname, name, patronymic, age);
    return TRUE;
}



extern "C" __declspec(dllexport)
int ReadData(LPWSTR str)
{
    MessageBoxA(NULL, "NEW DLL LOADED", "DEBUG", MB_OK);
    const char* path = "C:\\SystemProgramming\\MyNewDll\\x64\\Users.csv";

    FILE* file = fopen(path, "r");

    int added = 0;
    char line[256];

    while (fgets(line, sizeof(line), file))
    {

        size_t len = strlen(line);
        while (len && (line[len - 1] == '\n' || line[len - 1] == '\r'))
            line[--len] = '\0';

        if (len == 0) continue;
        if (ParseUserLine(line))
            added++;
    }

    fclose(file);
    return added;
}

extern "C" __declspec(dllexport)
void ShowAllList() {
    for (size_t i = 0; i < userCount; i++)
    {
        {
            printf("%s %s %s\n", userlist[i].Surname, userlist[i].Name, userlist[i].Patronynic);
        }
    }
}
