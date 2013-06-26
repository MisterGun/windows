// TimeCounter.h: interface for the CTimeCounter class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TIMECOUNTER_H__9C175895_617A_4AE0_A66C_D1926AB88409__INCLUDED_)
#define AFX_TIMECOUNTER_H__9C175895_617A_4AE0_A66C_D1926AB88409__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <windows.h>
#include <stdio.h>
#include <tchar.h>
class CTimeCounter  
{
    enum {MAXLEN = 256};
public:
//Constructors
	CTimeCounter(const TCHAR *pszName = NULL){
        ::QueryPerformanceFrequency(&m_liFrequency);
        ::QueryPerformanceCounter(&m_liStartCounter);
        if(pszName){
            _tcscpy(m_szName, pszName);
        }else{
            memset(m_szName, 0, sizeof(m_szName));
        }

        m_bAlreadyShow = false;
    }
    
    virtual ~CTimeCounter(){
        if(!m_bAlreadyShow){
            ShowCounter();
        }
    }
    
//Operations

    //Finish Counter
    double Finish(){
        double interval = ShowCounter();
        m_bAlreadyShow = true;
        return interval;
    }
    
    //Refresh Counter
    void Refresh(const TCHAR *pszName = NULL){
        ::QueryPerformanceCounter(&m_liStartCounter);
        if(pszName){
            _tcscpy(m_szName, pszName);
        }
        m_bAlreadyShow = false;
    }
    
private:
    double ShowCounter(){
        LARGE_INTEGER liEndCounter;
        ::QueryPerformanceCounter(&liEndCounter);

        double interval = double(liEndCounter.QuadPart - m_liStartCounter.QuadPart);
         TCHAR szBuf[MAXLEN];
         _stprintf(szBuf, _T("[TimeCounter] %11.9lfs is costed by %s\n"), interval/m_liFrequency.QuadPart, m_szName);
         OutputDebugString(szBuf);
        _tprintf(_T("[TimeCounter] %11.9fs is costed by %s\n"), interval/m_liFrequency.QuadPart, m_szName);
        return interval;
    }
    
private:
    TCHAR           m_szName[150];
    bool            m_bAlreadyShow;
    LARGE_INTEGER   m_liStartCounter;
    LARGE_INTEGER   m_liFrequency;
};

#endif // !defined(AFX_TIMECOUNTER_H__9C175895_617A_4AE0_A66C_D1926AB88409__INCLUDED_)
