#include <iostream> 
#include <vector>
#include <Windows.h>
#include <Tlhelp32.h>

using namespace std;

bool AreSameRECT (RECT& lhs, RECT& rhs){
    return (lhs.bottom == rhs.bottom && lhs.left == lhs.left && lhs.right == rhs.right && lhs.top == rhs.top) ? true : false;
}


bool IsFullscreenAndMaximized(HWND hWnd)
{
    RECT screen_bounds;
    GetWindowRect(GetDesktopWindow(), &screen_bounds);

    RECT app_bounds;
    GetWindowRect(hWnd, &app_bounds);

    if(hWnd != GetDesktopWindow() && hWnd != GetShellWindow()) {
        return AreSameRECT(app_bounds, screen_bounds);
    }

    return false;
}

BOOL CALLBACK CheckFullScreenMode ( HWND hwnd, LPARAM lParam )
{
    if( IsFullscreenAndMaximized(GetForegroundWindow()) )
    {
        * (bool*) lParam = true;
        return FALSE; 
    }
    return TRUE;
}


int main() {
    cout << "Wait for the window to be maximized..." << endl;
    Sleep(1000);
    bool bThereIsAFullscreenWin = false;
    EnumWindows( (WNDENUMPROC) CheckFullScreenMode, (LPARAM) &bThereIsAFullscreenWin );
    if (bThereIsAFullscreenWin) {
        cout << "Fullscreen window detected!" << endl;
    }
    else {
        cout << "No fullscreen window detected!" << endl;
    }
    cout << bThereIsAFullscreenWin;
}