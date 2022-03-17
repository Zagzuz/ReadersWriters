#include <windows.h>
#include <strsafe.h>
#include <string>


inline std::string last_error()
{
    LPVOID lpMsgBuf;
    DWORD dw = GetLastError();

    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER |
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        dw,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR)&lpMsgBuf,
        0, NULL);

    std::string err(static_cast<char*>(lpMsgBuf));

    LocalFree(lpMsgBuf);
    ExitProcess(dw);

    return err;
}
