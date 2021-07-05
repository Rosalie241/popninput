//
// popninput - https://github.com/Rosalie241/popninput
//  Copyright (C) 2021 Rosalie Wanders <rosalie@mailbox.org>
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License version 3.
//  You should have received a copy of the GNU General Public License
//  along with this program. If not, see <https://www.gnu.org/licenses/>.
//

//
// Includes
// 

#include <windows.h>
#include <stdio.h>
#include <stdbool.h>

//
// Global variables
//

static int g_ButtonState = 0;
static int g_ButtonKeybindings[9];
static struct
{
    char name[20];
    int keyCode;
} g_ButtonConfigMapping[] = 
{
    /* numbers */
    { "0", 0x30 }, { "1", 0x31 },
    { "2", 0x32 }, { "3", 0x33 },
    { "4", 0x34 }, { "5", 0x35 },
    { "6", 0x36 }, { "7", 0x37 },
    { "8", 0x38 }, { "9", 0x39 },
    /* numpad numbers */
    { "NUMPAD_0", 0x60 }, { "NUMPAD_1", 0x61 },
    { "NUMPAD_2", 0x62 }, { "NUMPAD_3", 0x63 },
    { "NUMPAD_4", 0x64 }, { "NUMPAD_5", 0x65 },
    { "NUMPAD_6", 0x66 }, { "NUMPAD_7", 0x67 },
    { "NUMPAD_8", 0x68 }, { "NUMPAD_9", 0x69 },
    /* letters */
    { "A", 0x41 }, { "B", 0x42 },
    { "C", 0x43 }, { "D", 0x44 },
    { "E", 0x45 }, { "F", 0x46 },
    { "G", 0x47 }, { "H", 0x48 },
    { "I", 0x49 }, { "J", 0x4A },
    { "K", 0x4B }, { "L", 0x4C },
    { "M", 0x4D }, { "N", 0x4E },
    { "O", 0x4F }, { "P", 0x50 },
    { "Q", 0x51 }, { "R", 0x52 },
    { "S", 0x53 }, { "T", 0x54 },
    { "U", 0x55 }, { "V", 0x56 },
    { "W", 0x57 }, { "X", 0x58 },
    { "Y", 0x59 }, { "Z", 0x5A },
};
static char g_DefaultConfigFile[] = ";\n"
                                    "; popninput - https://github.com/Rosalie241/popninput\n"
                                    ";  Copyright (C) 2021 Rosalie Wanders <rosalie@mailbox.org>\n"
                                    ";  This program is free software: you can redistribute it and/or modify\n"
                                    ";  it under the terms of the GNU General Public License version 3.\n"
                                    ";  You should have received a copy of the GNU General Public License\n"
                                    ";  along with this program. If not, see <https://www.gnu.org/licenses/>.\n"
                                    ";\n"
                                    "; button layout:\n"
                                    ";      {BUTTON_1} {BUTTON_3} {BUTTON_5} {BUTTON_7}\n"
                                    "; {BUTTON_0} {BUTTON_2} {BUTTON_4} {BUTTON_6} {BUTTON_8}\n"
                                    ";\n"
                                    "[popninput]\n"
                                    "BUTTON_0=A\n"
                                    "BUTTON_1=W\n"
                                    "BUTTON_2=S\n"
                                    "BUTTON_3=E\n"
                                    "BUTTON_4=D\n"
                                    "BUTTON_5=R\n"
                                    "BUTTON_6=F\n"
                                    "BUTTON_7=T\n"
                                    "BUTTON_8=G\n";

//
// Helper functions
//

static void DisplayError(const char* fmt, ...)
{
    char buf[MAX_PATH];

    va_list args;
    va_start(args, fmt);
    vsprintf(buf, fmt, args);
    va_end(args);

    MessageBoxA(NULL, buf, "popninput", MB_OK | MB_ICONERROR);
}

//
// Library functions
//

/// <summary>
///     Initializes Input
/// </summary>
bool pdiInitialize(HINSTANCE hinst, void* param2)
{
    char configFileName[] = "popninput.ini";
    char configFilePath[MAX_PATH];

    /* turn relative configFileName into absolute path,
     *  needed for GetPrivateProfileStringA()
     */
    GetFullPathNameA(configFileName, MAX_PATH, configFilePath, NULL);

    /* if the config file doesn't exist, create a default one */
    if (GetFileAttributesA(configFileName) == INVALID_FILE_ATTRIBUTES)
    {
        FILE* file = fopen(configFileName, "wb+");
        if (file == NULL)
        {
            DisplayError("Cannot create \"%s\": %li!", configFileName, GetLastError());
            return false;
        }

        /* write default contents to config file */
        fwrite(g_DefaultConfigFile, strlen(g_DefaultConfigFile), 1, file);
        fclose(file);

        DisplayError("Default config file created, see \"%s\"", configFileName);
    }

    /* read config file */
    char keyName[11];
    char value[20];
    bool foundMapping;

    /* loop over each BUTTON_ key,
     *  and attempt to retrieve the value,
     *  if it doesn't exist or is invalid,
     *  error out
     */
    for (int i = 0; i < 9; i++)
    {
        foundMapping = false;

        sprintf(keyName, "BUTTON_%i", i);

        GetPrivateProfileStringA("popninput", keyName, "", value, 20, configFilePath);

        /* make sure the key is set */
        if (strcmp(value, "") == 0)
        {
            DisplayError("\"%s\" is unset!", keyName);
            return false;
        }

        /* loop over each mapping and try to find a mapping */
        for (int y = 0; y < ARRAYSIZE(g_ButtonConfigMapping); y++)
        {
            if (strcmpi(g_ButtonConfigMapping[y].name, value) == 0)
            { /* found a match, so assign to keybindings */
                g_ButtonKeybindings[i] = g_ButtonConfigMapping[y].keyCode;
                foundMapping = true;
                break;
            }
        }

        /* when we haven't found a mapping, error out */
        if (!foundMapping)
        {
            DisplayError("\"%s\" contains an invalid value!", keyName);
            return false;
        }
    }

    return true;
}

/// <summary>
///     Release Resources
/// </summary>
/// <returns></returns>
void pdiRelease(void)
{
}

/// <summary>
///     Updates Input State
/// </summary>
/// <returns></returns>
void pdiUpdate(void)
{
    g_ButtonState = 0;
    int buttonId = 0;

    for (int i = 0; i < 9; i++)
    {
        buttonId = 1 << ((byte)i & 0x1f);
        if (GetAsyncKeyState(g_ButtonKeybindings[i]) & 0x01)
        {
            g_ButtonState |= buttonId | buttonId << 0x10;
        }
    }
}

/// <summary>
///     Returns Button State
/// </summary>
/// <returns></returns>
int pdiGetBtnState(void)
{
    return g_ButtonState;
}

/// <summary>
///     ???
/// </summary>
/// <returns></returns>
int pdiGetDllMode(void)
{
    return 1;
}

