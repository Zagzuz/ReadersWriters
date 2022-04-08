#ifndef UTILS_LASTERROR_H
#define UTILS_LASTERROR_H

#include <windows.h>
#include <string>

namespace rw::utils
{
    inline std::string lasterror()
    {
        LPVOID lpMsgBuf = nullptr;
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
} // namespace rw::utils

#endif // UTILS_LASTERROR_H
