//////////////////////////////////////////////////////////////////////////////////////////
//���ߺ����ļ�
//
////////////
//���е�ʱ�亯�������˱�׼��C����
//
#include "stdafx.h"
#include <winbase.h>


#include <time.h>
#include <stdlib.h>
#include "tools.h"
#include <direct.h> 
#include <string>
#include "api.h"


using namespace std;

#ifdef MEMMAP
HANDLE hMapFile;
void* pvFile=0;
unsigned char *pmapbuf=0;
unsigned char *pmapbuf_head=0;
UINT imemfilelen;
#define FILE_CACHE_SIZE 0x00A00000  /*  0x01E00000= 30MB */ 

void iniMemMapFile()
{
	//�����ļ����ڴ�ӳ���ļ���
	hMapFile=CreateFileMapping(
		(HANDLE)0xFFFFFFFF,
		NULL,
		PAGE_READWRITE, //��ӳ���ļ����ж�д
		(DWORD)(FILE_CACHE_SIZE>>32),
		(DWORD)(FILE_CACHE_SIZE & 0xFFFFFFFF), //������������64λ������֧�ֵ�����ļ�����Ϊ16EB
		NULL);
	if(hMapFile==INVALID_HANDLE_VALUE)
	{
		//AfxMessageBox("Can't create file mapping.Error%d:\n", GetLastError());
		OutputDebugStr("CreateFileMapping fail!");
		return;
	}
	
	//���ļ�����ӳ�䵽���̵ĵ�ַ�ռ�
	pvFile=MapViewOfFile(
		hMapFile,
		FILE_MAP_READ|FILE_MAP_WRITE,
		0,
		0,
		0);
	pmapbuf = (unsigned char*)pvFile;
	pmapbuf_head =  pmapbuf;
	imemfilelen = 0;
	
	OutputDebugStr("ini ok!");
}

bool writetoMemMapFile(const char* buf,int len)
{
	imemfilelen += len;
	//OutputDebugStr("imemfilelen= %d",imemfilelen);
	
	if (NULL!=pmapbuf && imemfilelen <FILE_CACHE_SIZE)
	{		
		memcpy(pmapbuf, buf,len);// imemfilelen);
		//OutputDebugStr("pmapbuf= %p",pmapbuf);
		pmapbuf += len;
		//OutputDebugStr("==>%p\n",pmapbuf);
		
	}
	else
	{	
		OutputDebugStr("writelogfile");
		writelogfile();
		return false;
	}
	return true;
}

///�ڴ�ӳ���ļ�����дһ�δ���
bool writelogfile()
{
#ifdef WIN32
#define MAXTIMELEN 23
#else
#define MAXTIMELEN 19
#endif
	
	if (0==imemfilelen || 0==pmapbuf_head)
	{
		return false;
	}
    char sfile[256];
	char ndate[24];
	memset(ndate,0,sizeof(ndate));
	memset(sfile,0,sizeof(sfile));
	strcpy(sfile,getExePath().c_str());
	strcat(sfile,"\\");
	/*ȡʱ��*/
	getnowdate(ndate);	
	left(ndate,0,10,sfile+strlen(sfile));
	mkdir(sfile);
	strcat(sfile,"\\");
	left(ndate,11,2,sfile+strlen(sfile));
	//strcat(sfile,getnowdate(ndate));
	strcat(sfile,".log");
	
	FILE *fp;
	fp = fopen(sfile,"a+");
	if(fp == NULL)
	{
#ifdef _DEBUG
		char gtext[40];
		sprintf(gtext,"fail to fopen(%s,\"a+\")!",sfile);
		OutputDebugStr(gtext);
#endif	
		return false;
	}
	
	fprintf(fp,"%s\t%s\n",ndate,pmapbuf_head);
	
	fclose(fp);
	
	imemfilelen=0;
	pmapbuf    = pmapbuf_head;
	return true;
}

#endif

/*ȡ��ǰʱ�� ��ʽ:YYYY-MM-DD HH:MI:SS:mmm*/
char *getnowdate(char *nowdate)
{
	
#ifdef WIN32	
	SYSTEMTIME   st; 
	GetLocalTime(&st);
	char ndate[24];
	memset(ndate,0,sizeof(ndate));
	sprintf(ndate,"%04d-%02d-%02d %02d:%02d:%02d:%03d",
		st.wYear,
		st.wMonth,
		st.wDay,
		st.wHour,
		st.wMinute,
		st.wSecond,
		st.wMilliseconds);
#else
	time_t timer;
	struct tm *ltm;
	char ndate[20];
	memset(ndate,0,sizeof(ndate));
	timer = time(NULL);
	ltm = localtime(&timer);
	sprintf(ndate,"%04d-%02d-%02d %02d:%02d:%02d",
		ltm->tm_year + 1900,
		ltm->tm_mon + 1,
		ltm->tm_mday,
		ltm->tm_hour,
		ltm->tm_min,
		ltm->tm_sec);
	
	
#endif
	strcpy(nowdate,ndate);
	
	return nowdate;
}

char getday()
{
	time_t timer;
	struct tm *ltm;
	timer = time(NULL);
	ltm = localtime(&timer);
	return (char) ltm->tm_mday;
}

/*ȡ��ǰʱ�� ��ʽ:YYYYMMDDHHMISS*/
char *getadddate(char *nowdate,int subtime)
{
	time_t timer;
	struct tm *ltm;
	char ndate[20];
	
	memset(ndate,0,sizeof(nowdate));
	timer = time(NULL) + subtime;
	ltm = localtime(&timer);
	sprintf(ndate,"%04d%02d%02d%02d%02d%02d",
		ltm->tm_year + 1900,
		ltm->tm_mon + 1,
		ltm->tm_mday,
		ltm->tm_hour,
		ltm->tm_min,
		ltm->tm_sec);
	strcpy(nowdate,ndate);
	
	return nowdate;
}

/*ȡ��һ��*/
char *nextdate(char *nowday,int between_day,char *next)
{
	time_t t_day;
	struct tm tmptr;
	struct tm *tmp;
	int tday;
	
	tday = atoi(nowday);
	
	tmptr.tm_year=tday/10000 - 1900;
	tday%=10000;
	tmptr.tm_mon=tday/100 - 1;
	tmptr.tm_mday=tday%100;
	tmptr.tm_hour=0;
	tmptr.tm_min=0;
	tmptr.tm_sec=0;
	tmptr.tm_isdst=0;
	
	t_day = mktime(&tmptr);
	
	t_day+=24*3600*between_day;
	
	tmp=localtime(&t_day);
	
	sprintf(next,"%04d%02d%02d",tmp->tm_year+1900,
		tmp->tm_mon + 1,
		tmp->tm_mday);
	
	return next;
}

/*ȥ���س���*/
char *chop(char *str)
{
	int len;
	
	len = strlen(str);
	while(1){
		if(str[len-1] == '\r' || str[len-1] == '\n')
		{
			len --;
		}
		else	{
			break;
		}
	}
	str[len] = '\0';
	return str;
}

/*ȥ���ַ�������ض��ַ�*/
char *ltrim(char *str,char ch)
{
	int pos,i;
	
	for(pos=0;str[pos] != '\0' && str[pos] == ch;pos++);
	if(pos == 0)
	{
		return str;
	}
	for(i=0;str[pos + i] != '\0';i++)
	{
		str[i] = str[pos + i];
	}
	str[i] = '\0';
	
	return str;
}

/*ȥ���ַ����ҵ��ض��ַ�*/
char *rtrim(char *str,char ch)
{
	int len;
	
	len = strlen(str);
	
	while(1){
		if(str[len-1] == ch)
		{
			len --;
		}
		else	{
			break;
		}
	}
	str[len] = '\0';
	return str;
}

/*ȥ���ַ������ߵ��ض��ַ�*/
char *trim(char *str,char ch)
{
	ltrim(str,ch);
	rtrim(str,ch);
	
	return str;
}

/*ȥ���ַ�����Ŀո�,�س��ַ�*/
char *ltrim_BLANK(char *str)
{
	int pos,i;
	
	for(pos=0;str[pos] != '\0' && str[pos] == ' '|| str[pos] == '\t';pos++);
	if(pos == 0)
	{
		return str;
	}
	for(i=0;str[pos + i] != '\0';i++)
	{
		str[i] = str[pos + i];
	}
	str[i] = '\0';
	
	return str;
}

/*ȥ���ַ����ҵĿո�,�س��ַ�*/
char *rtrim_BLANK(char *str)
{
	int len;
	
	len = strlen(str);
	
	while(1){
		if(str[len-1] == ' ' || str[len-1] == '\t')
		{
			len --;
		}
		else	{
			break;
		}
	}
	str[len] = '\0';
	return str;
}

char *trim_BLANK(char *str)
{
	ltrim_BLANK(str);
	rtrim_BLANK(str);
	
	return str;
}

/*ȡ��ߵ��ַ���*/
char *left(char *str,int start,int len,char *des)
{
	int slen;
	
	slen = strlen(str);
	if(slen < start)
	{
		des[0] = '\0';
	}
	else
	{
		strncpy(des,str + start,len);
		des[len] = '\0';
	}
	
	return des;
}

/*ȡ�ұߵ��ַ���*/
char *right(char *str,int start,int len,char *des)
{
	int slen,pos;
	
	slen = strlen(str);
	if(slen -start - len < 0)
	{
		pos = 0;
	}
	else	{
		pos = slen - start - len;
	}
	strncpy(des,str + pos,len);
	des[len] = '\0';
	return des;
}

/*д��־�ļ�*/
int writelog(const char* path,const char *type,const char *msg)
{
	
	// 	writetoMemMapFile(msg,strlen(msg));
	// 
	// 	return 1;
	
	////////////////////////////////
	char nowdate[24];
	char fname[250];
	char str[100];
	
	FILE *fp;
	
	char dir[256];     //	"TCPLOG/";
#ifdef WIN32
#define MAXTIMELEN 23
#else
#define MAXTIMELEN 19
#endif
	
	strcpy(dir,path);
	char * p= dir+ strlen(dir)-1;
	if ('\\' != *p)
	{
		strcat(dir,"\\");
	}
	strcat(dir,type);
	
	mkdir(dir);		
	
	strcat(dir,"\\");
	
	
	/*ȡʱ��*/
	getnowdate(nowdate);	
	left(nowdate,0,10,dir+strlen(dir));
	mkdir(dir);
	
	/*ȡ�ļ���*/
	sprintf(fname,"%s\\%s_",dir,type);
	left(nowdate,11,2,str);
	
	strcat(fname,str);
	strcat(fname,".log");
	
	/*д�ļ���־*/
	fp = fopen(fname,"a+");
	if(fp == NULL)
	{
#ifdef _DEBUG
		char gtext[40];
		sprintf(gtext,"fail to fopen(%s,\"a+\")!",fname);
		DEBUGOUT(gtext);
#endif	
		return 0;
	}
	
	fprintf(fp,"%s\t%s\n",left(nowdate,0,MAXTIMELEN,str),msg);
	
	fclose(fp);
	
	return 1;
}


/*�ָ����*/
int splitarg(char *str,char *argv[],int maxlen)
{
	int arnum,pos,i;
	
	pos = 0;
	arnum = 0;
	
	while(str[pos] != '\0')
	{
		/*ȥ�������*/
		for(i=0;str[pos+i] == ' ' ||
			str[pos+i] == '\t' ||
			str[pos+i] == '-' ||
			str[pos+i] == '_' ;i++);
		pos += i;
		
		/*�ﵽ���ֵ*/
		if(arnum + 1 >= maxlen)
		{
			argv[arnum] = str + pos;
			arnum ++;
			break;
		}
		
		if(str[pos] == '\0')
		{
			break;
		}
		
		argv[arnum] = str + pos;
		++arnum ;
		
		for(i=0;str[pos+i] != ' ' &&
			str[pos+i] != '\t' &&
			str[pos+i] != '-' &&
			str[pos+i] != '_' &&
			str[pos+i] != '\0';i++);
		pos += i;
		if(str[pos] == '\0')
		{
			break;
		}
		
		str[pos] = '\0';		
		++pos ;
	}
	
	return arnum;
}

int splitstring(char *str,char *spstr,char *argv[],int maxlen)
{
	int arnum,pos;
	int splen,slen;
	int is_next;
	
	if(maxlen == 0)
	{
		return 0;
	}
	
	slen = strlen(str);
	splen = strlen(spstr);
	
	if(splen == 0 || slen < splen)
	{
		argv[0] = str;
		return 1;
	}
	
	pos = 0;
	arnum = 0;
	
	while(pos + splen <= slen)
	{
		argv[arnum] = str + pos;
		arnum ++;
		
		/*�ﵽ���ֵ*/
		if(arnum >= maxlen)
		{
			break;
		}
		
		is_next = 0;
		while(pos + splen <= slen)
		{
			if(strncmp(str + pos,spstr,splen) != 0)
			{
				++pos ;
			}
			else	{
				str[pos] = '\0';
				pos += splen;
				is_next = 1;
				break;
			}
		}
		
		/**/
		if(pos + splen > slen && arnum < maxlen && is_next)
		{
			argv[arnum] = str + pos;
			++arnum ;
			break;
		}
	}
	
	return arnum;
}


//////////////////////////////////////////////////////////////////////
//֧��DBCS(���ı���),֧�ֶ��ֽڱ���
//          cl
//	2007.04.24 
//
char *upper(char *str)
{
	int len;
	int i=0;
	
	unsigned int test;
	unsigned char screen; 
	len =strlen(str);
	while(i<len)
	{
		screen = (unsigned char )str[i];
		test   = screen & 0x80;
		
		if(test == 0)                 //�Ǻ���
		{
			if(str[i]>='a' && str[i]<='z')
			{
				str[i] += 'A' - 'a';
			}
			++i; 
		}
		else
		{                       //��ASCII
			i += 2;
		}
	}
	return str;
}
//./~
//�ַ���ת��ΪСд
char *lower(char *str)
{
	int i;
	
	for(i=0;str[i] != '\0'; i++)
	{
		if(str[i]>='A' && str[i]<='Z')
		{
			str[i] += 'a' - 'A';
		}
	}
	
	return str;
}

void make_int_to_char(char *buf,int len,unsigned int val)
{
	int i;
	int tmp_val,vl;
	
	vl = val;
	
	for(i=0;i<len;i++)
	{
		tmp_val = vl & 0xFF;
		buf[len - i - 1] = (char)tmp_val;
		vl >>= 8;
	}
}

unsigned int make_char_to_int(char *buf,int len)
{
	int val;
	int i;
	unsigned char c;
	
	val = 0;
	for(i=0;i<len;i++)
	{
		val <<= 8;
		c = buf[i];
		val += c;
	}
	
	return val;
}


int myUTF8_to_UNICODE(unsigned short* unicode, unsigned char* utf8, int len)
{
    int length;
    unsigned char* t = utf8;
	
    length = 0;
    while (utf8 - t < len){
        //one byte.ASCII as a, b, c, 1, 2, 3 ect
        if ( *(unsigned char *) utf8 <= 0x7f ) {
            //expand with 0s.
            *unicode++ = *utf8++;
        }
        //2 byte.
        else if ( *(unsigned char *) utf8 <= 0xdf ) {
            *unicode++ = ((*(unsigned char *) utf8 & 0x1f) << 6) + ((*(unsigned char *) (utf8 + 1)) & 0x3f);
            utf8 += 2;
        }
        //3 byte.Chinese may use 3 byte.
        else {
            *unicode++ = ((int) (*(unsigned char *) utf8 & 0x0f) << 12) +
                ((*(unsigned char *) (utf8 + 1) & 0x3f) << 6) +
                (*(unsigned char *) (utf8 + 2) & 0x3f);
            utf8 += 3;
        }
        length++;
    }
	
    *unicode = 0;
    
    return (length);
}

void UTF_8ToUnicode(WCHAR* pOut,char *pText)
{
    char* uchar = (char *)pOut;
	
    uchar[1] = ((pText[0] & 0x0F) << 4) + ((pText[1] >> 2) & 0x0F);
    uchar[0] = ((pText[1] & 0x03) << 6) + (pText[2] & 0x3F);
	
    return;
}

void UnicodeToUTF_8(char* pOut,WCHAR* pText)
{
    // ע�� WCHAR�ߵ��ֵ�˳��,���ֽ���ǰ�����ֽ��ں�
    char* pchar = (char *)pText;
	
    pOut[0] = (0xE0 | ((pchar[1] & 0xF0) >> 4));
    pOut[1] = (0x80 | ((pchar[1] & 0x0F) << 2)) + ((pchar[0] & 0xC0) >> 6);
    pOut[2] = (0x80 | (pchar[0] & 0x3F));
	
    return;
}
void UnicodeToGB2312(char* pOut,WCHAR uData)
{
    WideCharToMultiByte(CP_ACP,NULL,&uData,1,pOut,sizeof(WCHAR),NULL,NULL);
    return;
}

void Gb2312ToUnicode(WCHAR* pOut,char *gbBuffer)
{
    ::MultiByteToWideChar(CP_ACP,MB_PRECOMPOSED,gbBuffer,2,pOut,1);
    return;
}
///////////////////////////////////////////////////////////////////////////////////
//��Ϊ��Urlʹ��
char  CharToInt(char ch){
	if(ch>='0' && ch<='9')return (char)(ch-'0');
	if(ch>='a' && ch<='f')return (char)(ch-'a'+10);
	if(ch>='A' && ch<='F')return (char)(ch-'A'+10);
	return -1;
}
char StrToBin(char *str){
	char tempWord[2];
	char chn;
	
	tempWord[0] = CharToInt(str[0]);                         //make the B to 11 -- 00001011
	tempWord[1] = CharToInt(str[1]);                         //make the 0 to 0  -- 00000000
	
	chn = (tempWord[0] << 4) | tempWord[1];                //to change the BO to 10110000
	
	return chn;
}


//UTF_8 תgb2312
void UTF_8ToGB2312(string &pOut, char *pText, int pLen)
{
	try
	{
		char buf[4];
		char* rst = new char[pLen + (pLen >> 2) + 2];
		if (!rst)
		{
			LogExt(CRITICAL_LEVEL,TEXT("UTF_8ToGB2312 new exception15!\n"));
			
		}
		memset(buf,0,4);
		memset(rst,0,pLen + (pLen >> 2) + 2);
		
		int i =0;
		int j = 0;
		
		while(i < pLen)
		{
			if(*(pText + i) >= 0)
			{
				
				rst[j++] = pText[i++];
			}
			else                 
			{
				WCHAR Wtemp;
				
				
				UTF_8ToUnicode(&Wtemp,pText + i);
				
				UnicodeToGB2312(buf,Wtemp);
				
				unsigned short int tmp = 0;
				tmp = rst[j] = buf[0];
				tmp = rst[j+1] = buf[1];
				tmp = rst[j+2] = buf[2];
				
				//newBuf[j] = Ctemp[0];
				//newBuf[j + 1] = Ctemp[1];
				
				i += 3;    
				j += 2;   
			}
			
		}
		rst[j]='\0';
		pOut = rst; 
		delete []rst;
		
	}
	catch(...)
	{
		
		LogExt(CRITICAL_LEVEL,TEXT("UTF_8ToGB2312 exception16!\n"));
		
		
	}
}

//GB2312 תΪ UTF-8
void GB2312ToUTF_8(string& pOut,char *pText, int pLen)
{
    char buf[4];
    memset(buf,0,4);
	
    pOut.empty();
	
    int i = 0;
    while(i < pLen)
    {
        //�����Ӣ��ֱ�Ӹ��ƾͿ���
        if( pText[i] >= 0)
        {
            char asciistr[2]={0};
            asciistr[0] = (pText[i++]);
            pOut.append(asciistr);
        }
        else
        {
            WCHAR pbuffer;
            Gb2312ToUnicode(&pbuffer,pText+i);
			
            UnicodeToUTF_8(buf,&pbuffer);
			
            pOut.append(buf);
			
            i += 2;
        }
    }
	
    return;
}
//��str����Ϊ��ҳ�е� GB2312 url encode ,Ӣ�Ĳ��䣬����˫�ֽ�  ��%3D%AE%88
string UrlGB2312(char * str)
{
    string dd;
    size_t len = strlen(str);
    for (size_t i=0;i<len;i++)
    {
        if(isalnum((BYTE)str[i]))
        {
            char tempbuff[2];
            sprintf(tempbuff,"%c",str[i]);
            dd.append(tempbuff);
        }
        else if (isspace((BYTE)str[i]))
        {
            dd.append("+");
        }
        else
        {
            char tempbuff[4];
            sprintf(tempbuff,"%%%X%X",((BYTE*)str)[i] >>4,((BYTE*)str)[i] %16);
            dd.append(tempbuff);
        }
		
    }
    return dd;
}

//��str����Ϊ��ҳ�е� UTF-8 url encode ,Ӣ�Ĳ��䣬�������ֽ�  ��%3D%AE%88

string UrlUTF8(char * str)
{
    string tt;
    string dd;
    GB2312ToUTF_8(tt,str,(int)strlen(str));
	
    size_t len=tt.length();
    for (size_t i=0;i<len;i++)
    {
        if(isalnum((BYTE)tt.at(i)))
        {
            char tempbuff[2]={0};
            sprintf(tempbuff,"%c",(BYTE)tt.at(i));
            dd.append(tempbuff);
        }
        else if (isspace((BYTE)tt.at(i)))
        {
            dd.append("+");
        }
        else
        {
            char tempbuff[4];
            sprintf(tempbuff,"%%%X%X",((BYTE)tt.at(i)) >>4,((BYTE)tt.at(i)) %16);
            dd.append(tempbuff);
        }
		
    }
    return dd;
}
//��url GB2312����
string UrlGB2312Decode(string str)
{
	string output="";
	char tmp[2];
	int i=0,idx=0,len=str.length();
	
	while(i<len){
		if(str[i]=='%'){
			tmp[0]=str[i+1];
			tmp[1]=str[i+2];
			output += StrToBin(tmp);
			i=i+3;
		}
		else if(str[i]=='+'){
			output+=' ';
			i++;
		}
		else{
			output+=str[i];
			i++;
		}
	}
	
	return output;
}
//��url utf8����
string UrlUTF8Decode(string str)
{
	string output="";
	
    string temp =UrlGB2312Decode(str);//
	
    UTF_8ToGB2312(output,(char *)temp.data(),strlen(temp.data()));
	
    return output;
	
}

///////////////////////////////////////////////////////////////////////////////////
//�ָ��ַ���2003.2.28
int comminute(char *msg,char msgbuf[200][200],int split_num)
{
	int i=0,j=0,k=0,t=0,m=0;
	unsigned int gb1,gb2;
	char buf[3];
	
	unsigned int msglen=strlen(msg);
	while ((unsigned int)i<msglen)///strlen(msg)
	{
		buf[0]=msg[i];
		gb1 = (unsigned int)buf[0];
		gb2= gb1 & 0x80;
		if(j<split_num)
		{
			if (gb2==0) 		//��ASCII
			{
				++i;
				++j;
				++t;
			}
			else 	//��GB����
			{
				i+=2;
				++j;
				t+=2;
			}
		}
		else	{
			strncpy(msgbuf[m],msg+k,t);
			msgbuf[m][t]='\0';
			k+=t;
			//TRACE("%s\n",msgbuf[m]);
			++m;
			j=0;
			t=0;
		}
	}
	if(j<=split_num)
	{
		strncpy(msgbuf[m],msg+k,t+1);
		msgbuf[m][t+1]='\0';
		//TRACE("%s\n",msgbuf[m]);
		++m;
	}
	return m;
}
// ��ȡָ���ָ���֮���ִ�
// index		���ִ���������0��ʼ
// separator	��ָ���ָ�����
// pBuf			����ȡ���ݵ�Դ�ִ�
// pData		����ȡ�������ִ�
// ����			����ȡ�����ִ��׵�ַ
char *ExtractData(int index, char separator,const char *pBuf, char *pData)
{
	int i=0,j=0;
	
	
	while (pBuf[i] != 0)
	{
		if (index == 0)
		{
			if (pBuf[i] == separator)
			{
				break;
			}
			pData[j] = pBuf[i];
			j++;
		}
		else if (pBuf[i] == separator)
		{
			index--;
		}
		i++;
	}
	pData[j] = 0;
	return pData;
}


/*�����ݰ���ָ����ŵ�����ȡ����ת��WORD��*/
WORD DataStr2WORD(char *pBuf, const BYTE bSeparator, WORD wIndex)
{
	char tempStr[256];
	WORD wAns;
	BYTE *p = (BYTE *)(&wAns);
	
	
	ExtractData(wIndex,bSeparator,pBuf,tempStr);
	if (strlen(tempStr) <= 0)
	{
		return -1;
	}
	
	sscanf(tempStr, "%x", &wAns);
	
	return wAns;
}

DWORD DataStr2DWORD(char *pBuf, const BYTE bSeparator, WORD wIndex)
{
	
	char tempStr[256];
	DWORD wAns;
	BYTE *p = (BYTE *)(&wAns);
	
	
	ExtractData(wIndex,bSeparator,pBuf,tempStr);
	if (strlen(tempStr) <= 0)
	{
		return -1;
	}
	
	sscanf(tempStr, "%x", &wAns);
	
	return wAns;
}

/*�����ݰ���ָ����ŵ�����ȡ����ת��BYTE��*/
BYTE DataStr2BYTE(char *pBuf, const BYTE bSeparator, WORD wIndex)
{
	char tempStr[256];
	char *stop;
	memset(tempStr, 0, sizeof(tempStr));
	
	ExtractData(wIndex,bSeparator,pBuf,tempStr);
	if (strlen(tempStr) <= 0)
	{
		return -1;
	}
	return (BYTE)strtol(tempStr, &stop, BASE_TYPE16);
}

char *DataStr2Number(char *des,const char *pBuf, const BYTE bSeparator, WORD wIndex)
{
	return	ExtractData(wIndex,bSeparator,pBuf,des);
}

char *DataStr2Time(char *des,const char* pBuf, const BYTE bSeparator, WORD wIndex)
{
	char szTime[80];
	memset(&szTime[0], 0, sizeof(szTime));
	
	ExtractData(wIndex,bSeparator,pBuf,szTime);
	if (strlen(szTime) <= 0)
	{
		return des;
	}
	
	///<����ʱ���
	int nCounts = 0;
	for(int nIndex = 0; nIndex < WORKTIME_LEN; nIndex += 2)
	{
		BYTE bBegin, bEnd;
		bBegin = ChartoByte(szTime[nIndex]);
		bEnd = ChartoByte(szTime[nIndex + 1]);
		
		des[nCounts++] = bBegin << 4 | bEnd;
	}
	
	return des;
}

/************************************************************************/
/* ��ȡ��������IP��ַ������                                             */
/************************************************************************/
char *DataStr2Ip(char *des,const char* pBuf, const BYTE bSeparator, WORD wIndex)
{
	return ExtractData(wIndex,bSeparator,pBuf,des);
}

/************************************************************************/
/* ��ȡ����λ��/IP��Ϣ                                                     */
/************************************************************************/
char *DataStr2Content(char *des,const char* pBuf, const BYTE bSeparator, WORD wIndex)
{
	return	ExtractData(wIndex,bSeparator,pBuf,des);
}

/************************************************************************/
/* GY:����, TD:ͨ��                                                     */
/************************************************************************/


DWORD Latitude_GY2TD(char *p)
{
	double degree;
	unsigned long data;
	DWORD dwAns;
	BYTE *pData = (BYTE*)&data;
	BYTE *pAns = (BYTE*)&dwAns;
	
	
	sscanf(p,"%08x",&data);   
	
	
	degree = ((double)data) / 600000.0;
	
	
	data = (long)(degree * (60.0*30000));
	
	
	pAns[0] = pData[3];
	pAns[1] = pData[2];
	pAns[2] = pData[1];
	pAns[3] = pData[0];
	
#ifdef _DEBUG
	char gtext[40];
	sprintf(gtext,"LA_GY2TD = %08x\n",dwAns);
	DEBUGOUT(gtext);
#endif
	
	return dwAns;
}


DWORD Longitude_GY2TD(char *p)
{
	double degree;
	unsigned long data;
	DWORD dwAns;
	BYTE *pData = (BYTE*)&data;
	BYTE *pAns = (BYTE*)&dwAns;
	
	
	sscanf(p,"%08x",&data);   
	
	
	degree = ((double)data) / 600000.0;
	
	
	data = (long)(degree * (60.0*30000));
	
	
	pAns[0] = pData[3];
	pAns[1] = pData[2];
	pAns[2] = pData[1];
	pAns[3] = pData[0];
	
#ifdef _DEBUG
	char gtext[40];
	sprintf(gtext,"LO_GY2TD = %08x\n",dwAns);
	DEBUGOUT(gtext);
#endif
	
	return dwAns;
}

/*�����ݰ���ָ����ŵ�����ȡ����ת��Longitude*/
DWORD DataStr2Longitude(char *pBuf, const BYTE bSeparator, WORD wIndex)
{
	char tempStr[256];
	
	
	ExtractData(wIndex,bSeparator,pBuf,tempStr);
	if (strlen(tempStr) <= 0)
	{
		return NULL;
	}
	return Longitude_GY2TD(tempStr);
}


/*�����ݰ���ָ����ŵ�����ȡ����ת��Latitude*/
DWORD DataStr2Latitude(char *pBuf, const BYTE bSeparator, WORD wIndex)
{
	char tempStr[256];
	
	
	ExtractData(wIndex,bSeparator,pBuf,tempStr);
	if (strlen(tempStr) <= 0)
	{
		return NULL;
	}
	return Latitude_GY2TD(tempStr);
}


BYTE ChartoByte(char c)
{
	BYTE val = 0;
	
	
	if( c >= 'a' && c <='z')
		val = c - 'a' + 10;
	else if( c >= 'A' && c <='Z')
		val = c - 'A' + 10;
	else if( c >= '0' && c <='9')
		val = c - '0';
	
	
	return val;		
}


WORD Str2HexWord(char *p)
{
	WORD val;
	
	
	val = ChartoByte(p[0]) << 12 |
		ChartoByte(p[1]) << 8  |
		ChartoByte(p[2]) << 4  |
		ChartoByte(p[3]);
	
	
	return val;
}
int StrToHex(char *pIn,char *pOut,int len)
{
	int i = 0;
	for(i=0;i<len/2;i++)
	{
		pOut[i] = ChartoByte(pIn[2*i]) << 4 | ChartoByte(pIn[2*i+1]);
	}
	
	return len/2;
}

/************************************************************************/
/* ���绰��������ת�����ַ���                                           */
/************************************************************************/
char *To_NumberType(char* des, BYTE *bType)
{	
	sprintf(des, "%02x", bType[0]);
	return des;
}

/************************************************************************/
/* ���绰��������ת�����ַ���                                           */
/************************************************************************/
char *To_NumberCount(char* des,BYTE *bCounts)
{
	sprintf(des, "%02x", bCounts[0]);
	return des;
}
/************************************************************************/
/* ���������ת�����ַ���                                               */
/************************************************************************/
char *To_PaType(char* des,BYTE * pType)
{
	sprintf(des, "%02x", pType[0]);
	return des;
}

/************************************************************************/
/* ���绰����ת�����ַ���                                               */
/************************************************************************/
char *To_Number(char* des,const BYTE *pbStr, int nLen)
{
	for(int nIndex = 0; nIndex < nLen; ++ nIndex)
	{
		sprintf(&des[nIndex],"%d",pbStr[nIndex] - '0');
		
	}
	return des;
}


void FillWord(BYTE *p,BYTE pos,WORD d)
{
	BYTE *p1 = (BYTE*)&d;
	
	p = p + pos;
	
	p[0] = p1[1];
	p[1] = p1[0];
}


void FillDWord(BYTE *p,BYTE pos,DWORD d)
{
	BYTE *p1 = (BYTE*)&d;
	
	p = p + pos;
	
	p[0] = p1[3];
	p[1] = p1[2];
	p[2] = p1[1];
	p[3] = p1[0];
}

string getExePath(void)
{
	DWORD   dwRetVal    =   0;
	string path; 
	path.resize(MAX_PATH+1);
	dwRetVal = ::GetModuleFileName(
		NULL,		// module handle (default is current application)
		(char*)path.c_str(),// string buffer
		MAX_PATH);	// maximum length
	
	basic_string <char>::size_type nPos=path.find_last_of('\\');
	string subpath=path.substr(0,nPos);
	
	
	
	if ( 0 == dwRetVal ){
		subpath.empty();
	}  
	return subpath;
}
/* int doit(int, char **)
{
char host_name[255];
//��ȡ������������
if (gethostname(host_name, sizeof(host_name)) == SOCKET_ERROR) {
printf("Error %d when getting local host name. ", WSAGetLastError());
return 1;
}
printf("Host name is: %s ", host_name);

	 //�����������ݿ��еõ���Ӧ�ġ�������
	 struct hostent *phe = gethostbyname(host_name);
	 if (phe == 0) {
	 printf("Yow! Bad host lookup.");
	 return 1;
	 }
	 
	   //ѭ���ó����ػ�������IP��ַ
	   for (int i = 0; phe->h_addr_list[i] != 0; ++i) {
	   struct in_addr addr;
	   memcpy(&addr, phe->h_addr_list[i], sizeof(struct in_addr));
	   printf("Address %d : %s " , i, inet_ntoa(addr));
	   }
	   
		 return 0;
}  */

//����У���
unsigned short checksum(unsigned short *buffer,int size)
{
	unsigned long cksum=0;
	while(size>1)
	{
		cksum +=  *buffer++;
		size   -=  sizeof(unsigned short);
	}
	if(size)
	{
		cksum  +=  *(unsigned char *)buffer;
	}
	//��32λ��ת����16
	while (cksum>>16)
		cksum=(cksum>>16)+(cksum & 0xffff);
	
	return (unsigned short) (~cksum);
}
/***************************/
/* unicode-ansi conversion */
/***************************/
BOOL Unicode16ToAnsi(WCHAR *in_Src, CHAR *out_Dst, INT in_MaxLen)
{
	
    INT  lv_Len;
    BOOL lv_UsedDefault;
	
	if (in_MaxLen <= 0)
		return FALSE;
	
	// let windows find out the meaning of ansi
	// - the SrcLen=-1 triggers WCTMB to add a eos to Dst and fails if MaxLen is too small.
	// - if SrcLen is specified then no eos is added
	// - if (SrcLen+1) is specified then the eos IS added
	lv_Len = WideCharToMultiByte(
		CP_ACP, 0, in_Src, -1, out_Dst, in_MaxLen, 0, &lv_UsedDefault);
	
	// validate
	if (lv_Len < 0)
		lv_Len = 0;
	
	// ensure eos, watch out for a full buffersize
	// - if the buffer is full without an eos then clear the output like WCTMB does
	//   in case of too small outputbuffer
	// - unfortunately there is no way to let WCTMB return shortened strings,
	//   if the outputbuffer is too small then it fails completely
	if (lv_Len < in_MaxLen)
		out_Dst[lv_Len] = 0;
	else if (out_Dst[in_MaxLen-1])
		out_Dst[0] = 0;
	
	// return whether invalid chars were present
	return !lv_UsedDefault;
}
BOOL Unicode16ToAnsiL(WCHAR *in_Src, INT in_SrcLen, CHAR *out_Dst, INT in_MaxLen)
{
    INT  lv_Len;
    BOOL lv_UsedDefault;
	
	// do NOT decrease maxlen for the eos
	if (in_MaxLen <= 0)
		return FALSE;
	
	// let windows find out the meaning of ansi
	// - the SrcLen=-1 triggers WCTMB to add a eos to Dst and fails if MaxLen is too small.
	// - if SrcLen is specified then no eos is added
	// - if (SrcLen+1) is specified then the eos IS added
	lv_Len = WideCharToMultiByte(
		CP_ACP, 0, in_Src, in_SrcLen, out_Dst, in_MaxLen, 0, &lv_UsedDefault);
	
	// validate
	if (lv_Len < 0)
		lv_Len = 0;
	
	// ensure eos, watch out for a full buffersize
	// - if the buffer is full without an eos then clear the output like WCTMB does
	//   in case of too small outputbuffer
	// - unfortunately there is no way to let WCTMB return shortened strings,
	//   if the outputbuffer is too small then it fails completely
	if (lv_Len < in_MaxLen)
		out_Dst[lv_Len] = 0;
	else if (out_Dst[in_MaxLen-1])
		out_Dst[0] = 0;
	
	// return whether invalid chars were present
	return !lv_UsedDefault;
}



//////////////////////////////


void CChineseCode::UTF_8ToUnicode(wchar_t* pOut,char *pText)  
{  
	char* uchar = (char *)pOut;  
	
	uchar[1] = ((pText[0] & 0x0F) << 4) + ((pText[1] >> 2) & 0x0F);  
	uchar[0] = ((pText[1] & 0x03) << 6) + (pText[2] & 0x3F);  
	
	return;  
}  

void CChineseCode::UnicodeToUTF_8(char* pOut,wchar_t* pText)  
{  
	// ע�� WCHAR�ߵ��ֵ�˳��,���ֽ���ǰ�����ֽ��ں�  
    
	char* pchar = (char *)pText;  
	
	pOut[0] = (0xE0 | ((pchar[1] & 0xF0) >> 4));  
	pOut[1] = (0x80 | ((pchar[1] & 0x0F) << 2)) + ((pchar[0] & 0xC0) >> 6);  
	pOut[2] = (0x80 | (pchar[0] & 0x3F));  
	
	return;  
}  

void CChineseCode::UnicodeToGB2312(char* pOut,wchar_t uData)  
{  
	WideCharToMultiByte(CP_ACP,NULL,&uData,1,pOut,sizeof(wchar_t),NULL,NULL);  
	
	return;  
}        

void CChineseCode::Gb2312ToUnicode(wchar_t* pOut,char *gbBuffer)  
{  
	::MultiByteToWideChar(CP_ACP,MB_PRECOMPOSED,gbBuffer,2,pOut,1);  
	return ;  
}  

void CChineseCode::GB2312ToUTF_8(string& pOut,char *pText, int pLen)  
{  
	char buf[4];  
	
	int nLength = pLen* 3;  
	
	char* rst = new char[nLength];  
	
	memset(buf,0,4);  
	memset(rst,0,nLength);  
	
	int i = 0;  
	int j = 0;        
	
	while(i < pLen)  
	{  
		//�����Ӣ��ֱ�Ӹ��ƾͿ���  
		if( *(pText + i) >= 0)  
		{  
			rst[j++] = pText[i++];  
		}  
		else  
		{  
			wchar_t pbuffer;  
			
			Gb2312ToUnicode(&pbuffer,pText+i);  
			UnicodeToUTF_8(buf,&pbuffer);  
			
			unsigned short int tmp = 0;  
			
			tmp = rst[j] = buf[0];  
			tmp = rst[j+1] = buf[1];  
			tmp = rst[j+2] = buf[2];      
			
			j += 3;  
			i += 2;  
		}  
	}  
	rst[j] = '\0';  
	
	
	//���ؽ��  
	pOut = rst;                
	delete []rst;     
	
	return;  
	
}  

void CChineseCode::UTF_8ToGB2312(string &pOut, char *pText, int pLen)  
{  
	
	char * newBuf = new char[pLen];  
	char Ctemp[4];  
	memset(Ctemp,0,4);  
	
	int i =0;  
	int j = 0;  
	
	while(i < pLen)  
	{  
		if(pText > 0)  
		{  
			newBuf[j++] = pText[i++];                          
		}  
		else                    
		{  
			WCHAR Wtemp;  
			
			UTF_8ToUnicode(&Wtemp,pText + i);        
			UnicodeToGB2312(Ctemp,Wtemp);                
			
			newBuf[j] = Ctemp[0];  
			newBuf[j + 1] = Ctemp[1];    
			
			i += 3;      
			j += 2;     
		}  
	}  
	
	newBuf[j] = '\0';    
	pOut = newBuf;    
	delete []newBuf;  
	return;    
}
