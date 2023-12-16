#pragma once

#include <windows.h>
#include <wchar.h>
#include <string>

namespace OpenEngine {
    std::string UnicodeToAnsi(const std::wstring& str)
    {
        char* pElementText;
        int    iTextLen;
        // 宽字节转多字节
        iTextLen = WideCharToMultiByte(CP_ACP, 0,
            str.c_str(),
            -1,
            nullptr,
            0,
            nullptr,
            nullptr);

        pElementText = new char[iTextLen + 1];
        memset((void*)pElementText, 0, sizeof(char) * (size_t)(iTextLen + 1));
        ::WideCharToMultiByte(CP_ACP,
            0,
            str.c_str(),
            -1,
            pElementText,
            iTextLen,
            nullptr,
            nullptr);

        std::string strText;
        strText = pElementText;
        delete[] pElementText;
        return strText;
    }

    std::wstring AnsiToUnicode(const std::string& str)
    {
        wchar_t* pElementText;
        int    iTextLen;
        // 宽字节转多字节
        iTextLen = MultiByteToWideChar(CP_ACP, 0,
            str.c_str(),
            -1,
            nullptr,
            0);

        pElementText = new wchar_t[iTextLen + 1];
        memset((void*)pElementText, 0, sizeof(char) * (size_t)(iTextLen + 1));
        ::MultiByteToWideChar(CP_ACP,
            0,
            str.c_str(),
            -1,
            pElementText,
            iTextLen);

        std::wstring strText;
        strText = pElementText;
        delete[] pElementText;
        return strText;
    }

    std::string UnicodeToUtf8(LPCWSTR lpszWideStr)
    {
        int nLen = ::WideCharToMultiByte(CP_UTF8, 0, lpszWideStr, -1,
            nullptr, 0, nullptr, nullptr);

        char* buffer = new char[nLen + 1];
        ::ZeroMemory(buffer, nLen + 1);

        ::WideCharToMultiByte(CP_UTF8, 0, lpszWideStr, -1,
            buffer, nLen, nullptr, nullptr);

        std::string multStr = buffer;
        delete[] buffer;
        return multStr;
    }

    std::wstring Utf8ToUnicode(const std::string& str)
    {
        int nLen = ::MultiByteToWideChar(CP_UTF8, 0, str.c_str(), str.length(),
            nullptr, 0);

        WCHAR* buffer = new WCHAR[nLen + 1];
        ::ZeroMemory(buffer, sizeof(WCHAR) * (nLen + 1));

        ::MultiByteToWideChar(CP_UTF8, 0, str.c_str(), str.length(),
            buffer, nLen);

        std::wstring wideStr = buffer;
        delete[] buffer;
        return wideStr;
    }

    std::string AnsiToUtf8(const std::string& str) {
        return UnicodeToUtf8(AnsiToUnicode(str).c_str());
    }

    std::string Utf8ToAnsi(const std::string& str) {
        return UnicodeToAnsi(Utf8ToUnicode(str));
    }
}