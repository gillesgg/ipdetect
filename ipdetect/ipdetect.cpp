// ipdetect.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <ws2spi.h>
#include <windows.h>
#include <vector>

bool supportIPv6() 
{
    INT iNuminfo = 0;
    DWORD bufferSize = 0;
    std::vector<BYTE> protocolInfo;
    INT iErrno = NO_ERROR;
    LPWSAPROTOCOL_INFOW lpProtocolInfo = nullptr;

    while ((iNuminfo = WSCEnumProtocols(nullptr, lpProtocolInfo, &bufferSize,&iErrno)) == SOCKET_ERROR) 
    {
        if (iErrno == WSAENOBUFS) {
            protocolInfo.resize(bufferSize, 0);
            lpProtocolInfo = reinterpret_cast<LPWSAPROTOCOL_INFOW>(protocolInfo.data());
        }
        else 
        {
            std::cerr << "WSCEnumProtocols failed with error: " << iErrno << std::endl;
            WSACleanup();
            exit(1);
        }
    }

    for (INT i = 0; i < iNuminfo; ++i) 
    {       
        std::wcout << R"(protocol=)" << lpProtocolInfo[i].szProtocol << std::endl;

        if (lpProtocolInfo[i].iAddressFamily == AF_INET6) return true;
    }
    return false;
}



int main()
{
    if (supportIPv6() == true)
    {
        std::cout << "IPv6 is supported" << std::endl;
    }
}
