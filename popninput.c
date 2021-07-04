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

//
// Library functions
//

/// <summary>
///     Initializes Input
/// </summary>
bool pdiInitialize(HINSTANCE hinst, void* param2)
{
    return true;
}

/// <summary>
///     Release Resources
/// </summary>
/// <returns></returns>
void pdiRelease(void)
{
}

int g_ButtonKeybindings[] = 
{
    0x41,
    0x57,
    0x53,
    0x45,
    0x44,
    0x52,
    0x46,
    0x54,
    0x47
};

// button layout (index 0-8)
//
//      {button 1} {button 3} {button 5} {button 7}
//  {button 0} {button 2} {button 4} {button 6} {button 8}
//
//


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

