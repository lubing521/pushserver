#ifndef _TOOLS_H
#define _TOOLS_H
#include <string>
using namespace std ;

#include "SeException.h"


BOOL Unicode16ToAnsiL(WCHAR *in_Src, INT in_SrcLen, CHAR *out_Dst, INT in_MaxLen);
void GetFromID(char *simno, const char* data);
void exceptiontolog (CSeException *e);
// 转换进制
#define BASE_TYPE16		(16)		// 16进制
#define WORKTIME_LEN (8)

char *getnowdate(char *nowdate);
char *getadddate(char *nowdate,int subtime);
char getday();
char *nextdate(char *nowday,int between_day,char *next);

char * chop(char *str);
char *ltrim(char *str,char ch);
char *rtrim(char *str,char ch);
char *trim(char *str,char ch);
char *ltrim_BLANK(char *str);
char *rtrim_BLANK(char *str);
char *trim_BLANK(char *str);

char *left(char *str,int start,int len,char *des);
char *right(char *str,int start,int len,char *des);

int splitarg(char *str,char *argv[],int maxlen);
int splitstring(char *str,char *spstr,char *argv[],int maxlen);
int splitdbstring(char *str,char *str1,char *str2,char *argv[]);

int findstr(char *str,char *sear_str);
char *upper(char *str);
char *lower(char *str);


int writelog(const char* path,const char *type,const char *msg);


int comminute(char *msg,char msgbuf[200][200],int split_num);

int StrToHex(char *pIn,char *pOut,int len);
WORD Str2HexWord(char *p);
char *DataStr2Time(char *des,const char* pBuf, const BYTE bSeparator, WORD wIndex);
char *DataStr2Number(char *des,const char* pBuf, const BYTE bSeparator, WORD wIndex);
BYTE DataStr2BYTE(char *pBuf, const BYTE bSeparator, WORD wIndex);
DWORD DataStr2DWORD(char *pBuf, const BYTE bSeparator, WORD wIndex);
WORD DataStr2WORD(char *pBuf, const BYTE bSeparator, WORD wIndex);
DWORD DataStr2Latitude(char *pBuf, const BYTE bSeparator, WORD wIndex);
DWORD DataStr2Longitude(char *pBuf, const BYTE bSeparator, WORD wIndex);
char *DataStr2Ip(char *des,const char *pBuf, const BYTE bSeparator, WORD wIndex);
char *DataStr2Content(char *des,const char *pBuf, const BYTE bSeparator, WORD wIndex);
 char *ExtractData(int index, char separator, const char *pBuf, char *pData);


char *To_NumberType(char* des, BYTE *bType);
char *To_NumberCount(char* des,BYTE *bCounts);
char *To_PaType(char* des,BYTE * pType);
char *To_Number(char* des,const BYTE *pbStr, int nLen);
void FillWord(BYTE *p,BYTE pos,WORD d);
void FillDWord(BYTE *p,BYTE pos,DWORD d);

char* Hexchartobinarychar(const char*src,char*des,int len);//'0''A'=>'a'
char *binarychartoHexchar(const char*src,char*des,int len); //'a'=>'0''A'
BYTE ChartoByte(char c);
unsigned short checksum(unsigned short *buffer,int size);

//CString getExePathName(void);
string getExePath(void);

void LogExt(int loglevel,const char* lpszFormat,...);
int writelogimmediatly(const char *msg);
#ifdef MEMMAP
// extern HANDLE hMapFile;
// extern void* pvFile;
// extern unsigned char *pmapbuf;
// extern unsigned char *pmapbuf_head;
// extern UINT imemfilelen;
// void iniMemMapFile();
// void closeMMapFile();
// bool writetoMemMapFile(const char* buf,int len);
// bool writelogfile();
#endif


class CChineseCode  

{  
	
public:  
	
	static void UTF_8ToUnicode(wchar_t* pOut,char *pText);  // 把UTF-8转换成Unicode  
	
	static void UnicodeToUTF_8(char* pOut,wchar_t* pText);  //Unicode 转换成UTF-8  
	
	static void UnicodeToGB2312(char* pOut,wchar_t uData);  // 把Unicode 转换成 GB2312    
	
	static void Gb2312ToUnicode(wchar_t* pOut,char *gbBuffer);// GB2312 转换成　Unicode  
	
	static void GB2312ToUTF_8(string& pOut,char *pText, int pLen);//GB2312 转为 UTF-8  
	
	static void UTF_8ToGB2312(string &pOut, char *pText, int pLen);//UTF-8 转为 GB2312  
	
};  
     

#endif



