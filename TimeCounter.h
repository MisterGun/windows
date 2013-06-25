// TimeCounter.h: interface for the CTimeCounter class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TIMECOUNTER_H__25F0481C_7315_449A_B956_EB092FE120EE__INCLUDED_)
#define AFX_TIMECOUNTER_H__25F0481C_7315_449A_B956_EB092FE120EE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define _CRT_SECURE_NO_WARNINGS 1

#include <windows.h>
#include <string>
#include <vector>

typedef std::basic_string<TCHAR, std::char_traits<TCHAR>, std::allocator<TCHAR> > TString;
class CTimeCounter  
{
public:
	CTimeCounter()
    {
        memset(&m_liFrequency, 0, sizeof(m_liFrequency));
        memset(&m_liStartCounter, 0, sizeof(m_liStartCounter));
        ::QueryPerformanceFrequency(&m_liFrequency);
    }
    
    ~CTimeCounter()
    {
        Show();
    }


    void Begin(LPCTSTR pszName)
    {
        m_sName = pszName;
        ::QueryPerformanceCounter(&m_liStartCounter);
    }
    
    void End()
    {
        LARGE_INTEGER m_liEndCounter;
        ::QueryPerformanceCounter(&m_liEndCounter);
        double fSecsElapsed = double(m_liEndCounter.QuadPart-m_liStartCounter.QuadPart)/m_liFrequency.QuadPart;
        m_vecNameToSecs.push_back(std::make_pair<TString, double>(m_sName, fSecsElapsed));
    }

    void Show()
    {
        TCHAR szBuf[1024];
        for(size_t i=0; i<m_vecNameToSecs.size(); ++i)
        {
            _stprintf(szBuf, _T("[TimeCounter] %11.6lfs is costed by %s\n"), 
                m_vecNameToSecs[i].second, m_vecNameToSecs[i].first.c_str());
            _tprintf(szBuf);
            OutputDebugString(szBuf);
        }
        m_vecNameToSecs.clear();
    }

private:
    TString                                     m_sName;
    std::vector<std::pair<TString,double> >     m_vecNameToSecs;
    LARGE_INTEGER                               m_liStartCounter;
    LARGE_INTEGER                               m_liFrequency;
};

#endif // !defined(AFX_TIMECOUNTER_H__25F0481C_7315_449A_B956_EB092FE120EE__INCLUDED_)
