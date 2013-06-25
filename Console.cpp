// Console.cpp: implementation of the CConsole class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Console.h"
#include <io.h>
#include <fcntl.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#define STR_OK      "[OK]   \t\t"
#define STR_BAD     "[BAD]  \t\t"
int a = 3;
CConsole::CConsole()
{
    ::AllocConsole();
    m_hOutput = ::GetStdHandle(STD_OUTPUT_HANDLE);
    int nOutput = _open_osfhandle(long(m_hOutput), _O_TEXT);
    FILE *pStdout = _fdopen(nOutput, "w");
    *stdout = *pStdout;
    ::setvbuf(stdout, NULL, _IONBF, 0);
}

CConsole::~CConsole()
{
    
}

BOOL CConsole::SetBufferSize(SHORT nCols, SHORT nRows)
{
	//set screen buffer size
    COORD bufferSize;
    bufferSize.X = nCols;
    bufferSize.Y = nRows;
    return ::SetConsoleScreenBufferSize(m_hOutput, bufferSize);	
}


BOOL CConsole::SetWindowSize(SHORT nCols, SHORT nRows)
{
    SMALL_RECT srConsole;
    srConsole.Left      = 0;
    srConsole.Top       = 0;
    srConsole.Right     = nCols;
    srConsole.Bottom    = nRows;
    return ::SetConsoleWindowInfo(m_hOutput, TRUE, &srConsole);
}

BOOL CConsole::GetScreenInfo(CONSOLE_SCREEN_BUFFER_INFO &sizeInfo)
{
    return ::GetConsoleScreenBufferInfo(m_hOutput, &sizeInfo);
}

BOOL CConsole::PrintInColor(ETextColor nColor, LPCTSTR szFormat, ...)
{
    ::SetConsoleTextAttribute(m_hOutput, nColor);
    
    va_list ap;
    va_start(ap, szFormat);
    int retval = vprintf(szFormat, ap);
    va_end(ap);

    ::SetConsoleTextAttribute(m_hOutput, RED|GREEN|BLUE);
    return TRUE;
}

BOOL CConsole::ClearLine(SHORT nRow/*=-1*/)
{
    CONSOLE_SCREEN_BUFFER_INFO screenInfo;
    GetScreenInfo(screenInfo);
    if(-1 == nRow)
    {
        nRow = screenInfo.dwCursorPosition.Y;
    }

    COORD cursorPos;
    cursorPos.X = 0;
    cursorPos.Y = nRow;

    DWORD dwChars;
    ::FillConsoleOutputCharacter(m_hOutput, ' ', screenInfo.dwSize.X, cursorPos, &dwChars);
    ::SetConsoleCursorPosition(m_hOutput, cursorPos);

    return TRUE;
}

BOOL CConsole::SetCursorPos( int nCol, int nRow )
{
    COORD cursorPos;
    cursorPos.X = nCol;
    cursorPos.Y = nRow;
    return ::SetConsoleCursorPosition(m_hOutput, cursorPos);
}

BOOL CConsole::PrintResult(BOOL bOK, LPCTSTR szFormat, ...)
{
    if(bOK)
        PrintInColor(GREEN, STR_OK);
    else
        PrintInColor(RED, STR_BAD);

    va_list ap;
    va_start(ap, szFormat);
    int retval = vprintf(szFormat, ap);
    va_end(ap);

    return retval;
}
