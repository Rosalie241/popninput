//
// popninput - https://github.com/Rosalie241/popninput
//  Copyright (C) 2021 Rosalie Wanders <rosalie@mailbox.org>
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License version 3.
//  You should have received a copy of the GNU General Public License
//  along with this program. If not, see <https://www.gnu.org/licenses/>.
//

#include <windows.h>
#include <stdio.h>
#include <stdbool.h>

static void DisplayError(const char* fmt, ...)
{
    char buf[1000];

    va_list args;
    va_start(args, fmt);
    vsprintf(buf, fmt, args);
    va_end(args);

    MessageBoxA(NULL, buf, "popninput", MB_OK | MB_ICONERROR);
}

/// <summary>
///     Initializes Input
/// </summary>
bool pdiInitialize(HINSTANCE hinst, void* param2)
{
    DisplayError("pdiInitialize");
    return true;
}

/// <summary>
///     Release Resources
/// </summary>
/// <returns></returns>
void pdiRelease(void)
{
    DisplayError("pdiRelease");
}

/// <summary>
///     Updates Input State
/// </summary>
/// <returns></returns>
void pdiUpdate(void)
{
    DisplayError("pdiUpdate");
}

/// <summary>
///     Returns Button State
/// </summary>
/// <returns></returns>
int pdiGetBtnState(void)
{
    DisplayError("pdiGetBtnState");
    return 0;
}

/// <summary>
///     ???
/// </summary>
/// <returns></returns>
int pdiGetDllMode(void)
{
    DisplayError("pdiGetDllMode");
    return 1;
}

/// <summary>
///     ???
/// </summary>
/// <param name="param1"></param>
void pdiSetDbgMode(void* param1)
{
    DisplayError("pdiSetDbgMode");
}

/// <summary>
///     Load Input Config
/// </summary>
/// <param name=""></param>
/// <returns></returns>
bool pdiLoadConfig(void)
{
    DisplayError("pdiLoadConfig");
    return true;
}

/// <summary>
///     ???
/// </summary>
/// <param name=""></param>
/// <returns></returns>
void* pdiGetConfigSoftware(void)
{
    DisplayError("pdiGetConfigSoftware");
    return NULL;
}


/// <summary>
///     ???
/// </summary>
/// <param name=""></param>
/// <returns></returns>
bool pdiIsJoyConnect(void)
{
    DisplayError("pdiIsJoyConnect");
    return true;
}

/// <summary>
///     ???
/// </summary>
/// <param name="hModule"></param>
void pdiCreateDesktopShortcut(HMODULE hModule)
{
    DisplayError("pdiCreateDesktopShortcut");
}

/// <summary>
///     ???
/// </summary>
/// <param name=""></param>
void pdiDeleteDesktopShortcut(void)
{
    DisplayError("pdiDeleteDesktopShortcut");
}

struct tagPDI_CONFIGDATA
{
    // TODO: struct is 8 bytes
};

/// <summary>
///     ???
/// </summary>
/// <param name=""></param>
/// <returns></returns>
struct tagPDI_CONFIGDATA* pdiGetConfig(void)
{
    DisplayError("pdiGetConfig");
    return NULL;
}

/// <summary>
///     ???
/// </summary>
/// <param name=""></param>
/// <returns></returns>
int pdiSaveConfig(void)
{
    DisplayError("pdiSaveConfig");
    return 1;
}
