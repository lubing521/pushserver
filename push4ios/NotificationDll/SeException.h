#ifndef __SEEXCEPTION_H__
#define __SEEXCEPTION_H__
#include <string>
using namespace std;

class CSeException //: public CException
{
	//DECLARE_DYNAMIC(CSeException)
public:    
	CSeException(UINT nSeCode, _EXCEPTION_POINTERS* pExcPointers);
	CSeException(CSeException & CseExc);

    UINT GetSeCode(void);
	_EXCEPTION_POINTERS* GetSePointers(void);
	PVOID GetExceptionAddress(void);

	void Delete(void);
	int ReportError(UINT nType = MB_OK, UINT nIDHelp = 0);
	BOOL GetErrorMessage(string & CsErrDescr, PUINT pnHelpContext = NULL);
	BOOL GetErrorMessage(LPTSTR lpszError, UINT nMaxError, PUINT pnHelpContext = NULL);
private:
	UINT m_nSeCode;
	_EXCEPTION_POINTERS* m_pExcPointers;
	#ifdef _DEBUG
	 bool m_bReadyForDelete;
	#endif
};

void SeTranslator(UINT nSeCode, _EXCEPTION_POINTERS* pExcPointers);

#endif //__SEEXCEPTION_H__