// Console.h: interface for the CConsole class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONSOLE_H__6FB2EE27_6F52_4D60_ACA5_8072D2DD3DD6__INCLUDED_)
#define AFX_CONSOLE_H__6FB2EE27_6F52_4D60_ACA5_8072D2DD3DD6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CConsole  
{
public:
    enum ETextColor
    {
         BLUE  = 1,
         GREEN = 2,
         RED   = 4,
    };

	CConsole();
	virtual ~CConsole();

	BOOL SetBufferSize(SHORT nCols, SHORT nRows);
	BOOL SetWindowSize(SHORT nCols, SHORT nRows);
	BOOL GetScreenInfo(CONSOLE_SCREEN_BUFFER_INFO &bufferInfo);
    BOOL ClearLine(SHORT nRow = -1);
    BOOL SetCursorPos(int nCol, int nRow);
    BOOL PrintInColor(ETextColor nColor, LPCTSTR szFormat, ...);
    BOOL PrintResult(BOOL bOK, LPCTSTR szFormat, ...);
private:
	HANDLE		m_hOutput;
};

#endif // !defined(AFX_CONSOLE_H__6FB2EE27_6F52_4D60_ACA5_8072D2DD3DD6__INCLUDED_)
