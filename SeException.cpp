#include "stdafx.h"
#include <eh.h>
//#include <windows.h>
#include <assert.h>

#include "SeException.h"
#include "api.h"
#include "log.h"

extern Clog g_log;

#ifdef _DEBUG
//#define new DEBUG_NEW
#endif

#undef THIS_FILE
static char THIS_FILE[] = __FILE__;

// #define CASE(nSeCode,CsString) case EXCEPTION_##nSeCode: \
// 										CsString.Format(_T("Exception %s (0x%.8x) at address 0x%.8x."),_T(#nSeCode),EXCEPTION_##nSeCode,m_pExcPointers->ExceptionRecord->ExceptionAddress); \
// 										break;

#define CASE(nSeCode,buffer) case EXCEPTION_##nSeCode: \
if ( EXCEPTION_##nSeCode == EXCEPTION_ACCESS_VIOLATION ) \
{ \
sprintf(buffer,_T("Exception %s (0x%.8X) at address 0x%.8X. %s 0x%.8X"), \
_T(#nSeCode),\
EXCEPTION_##nSeCode,\
m_pExcPointers->ExceptionRecord->ExceptionAddress, \
m_pExcPointers->ExceptionRecord->ExceptionInformation[0] ? _T("\r\nUnable to write location:") : _T("\r\nUnable to read location:"), \
m_pExcPointers->ExceptionRecord->ExceptionInformation[1] ); \
} \
else \
{ \
sprintf(buffer,_T("Exception %s (0x%.8X) at address 0x%.8X."), \
_T(#nSeCode),\
EXCEPTION_##nSeCode,\
m_pExcPointers->ExceptionRecord->ExceptionAddress); \
} \
break;

void exceptiontolog (CSeException *e)
{
	TCHAR trcMsg[512];
	e->GetErrorMessage(trcMsg,512);
	LogExt(DEBUG_ONLY_LEVEL,trcMsg);
	//e->ReportError();
	e->Delete();
}

bool __stdcall IsValidAddress(const void* lp, UINT nBytes,bool bReadWrite  = TRUE )
{
	// simple version using Win-32 APIs for pointer validation.
	return (lp != NULL && !IsBadReadPtr(lp, nBytes) &&
		(!bReadWrite || !IsBadWritePtr((LPVOID)lp, nBytes)));
}


void SeTranslator(UINT nSeCode, _EXCEPTION_POINTERS* pExcPointers)
{

	throw new CSeException(nSeCode,pExcPointers);
}

//IMPLEMENT_DYNAMIC(CSeException,CException)

CSeException::CSeException(UINT nSeCode, _EXCEPTION_POINTERS* pExcPointers)
{ 
	m_nSeCode = nSeCode;
	m_pExcPointers = pExcPointers;
}

CSeException::CSeException(CSeException & CseExc)
{
	m_nSeCode = CseExc.m_nSeCode;
	m_pExcPointers = CseExc.m_pExcPointers;
}

UINT CSeException::GetSeCode()
{
	return m_nSeCode;
}

_EXCEPTION_POINTERS* CSeException::GetSePointers()
{
	return m_pExcPointers;
}

PVOID CSeException::GetExceptionAddress()
{
	return m_pExcPointers->ExceptionRecord->ExceptionAddress;
}

void CSeException::Delete(void)
{
#ifdef _DEBUG
	m_bReadyForDelete = TRUE;
#endif
	delete this;
}

int CSeException::ReportError(UINT nType/* = MB_OK*/, UINT nIDHelp/* = 0*/)
{
	//string strMessage;
	//GetErrorMessage(strMessage);
	return 0;
}

BOOL CSeException::GetErrorMessage(string & CsErrDescr, PUINT pnHelpContext /*= NULL*/)
{
	BOOL rc = TRUE;

	if (pnHelpContext != NULL)
		*pnHelpContext = 0;
	char  buffer[88];
	switch (m_nSeCode)    {   
		CASE(ACCESS_VIOLATION,buffer);
		CASE(DATATYPE_MISALIGNMENT,buffer);
		CASE(BREAKPOINT,buffer);
		CASE(SINGLE_STEP,buffer);
		CASE(ARRAY_BOUNDS_EXCEEDED,buffer);
		CASE(FLT_DENORMAL_OPERAND,buffer);
		CASE(FLT_DIVIDE_BY_ZERO,buffer);
		CASE(FLT_INEXACT_RESULT,buffer);
		CASE(FLT_INVALID_OPERATION,buffer);
		CASE(FLT_OVERFLOW,buffer);
		CASE(FLT_STACK_CHECK,buffer);
		CASE(FLT_UNDERFLOW,buffer);
		CASE(INT_DIVIDE_BY_ZERO,buffer);
		CASE(INT_OVERFLOW,buffer);
		CASE(PRIV_INSTRUCTION,buffer);
		CASE(IN_PAGE_ERROR,buffer);
		CASE(ILLEGAL_INSTRUCTION,buffer);
		CASE(NONCONTINUABLE_EXCEPTION,buffer);
		CASE(STACK_OVERFLOW,buffer);
		CASE(INVALID_DISPOSITION,buffer);
		CASE(GUARD_PAGE,buffer);
		CASE(INVALID_HANDLE,buffer);
	default:
		CsErrDescr = _T("Unknown exception.");
		rc = FALSE;
		break;
	}
	
	CsErrDescr=buffer;

	g_log.log(CsErrDescr.c_str(),DEBUG_ONLY_LEVEL);
	return rc;
}
BOOL __stdcall IsValidString(LPCSTR lpsz, int nLength /* = -1 */)
{
	if (lpsz == NULL)
		return FALSE;
	return ::IsBadStringPtr(lpsz, nLength) == 0;
}
BOOL CSeException::GetErrorMessage(LPTSTR lpszError, UINT nMaxError, PUINT pnHelpContext/* = NULL*/)
{
	assert(lpszError != NULL && IsValidString(lpszError, nMaxError));

	if (pnHelpContext != NULL)
		*pnHelpContext = 0;

	string strMessage;
	GetErrorMessage(strMessage);

	if ((UINT)strMessage.size() >= nMaxError) {
		lpszError[0] = 0;
		return FALSE;
	} else {
		lstrcpyn(lpszError, strMessage.c_str(), nMaxError);
		return TRUE;
	}
}
