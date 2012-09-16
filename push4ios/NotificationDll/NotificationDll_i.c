/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Tue Sep 11 11:23:05 2012
 */
/* Compiler settings for F:\hly\PushSubsystem\Notification4IOS\NotificationDll\NotificationDll.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )
#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

const IID IID_INotify = {0x9FD8910B,0x01BF,0x40F1,{0xB3,0x8C,0x93,0x66,0x11,0xC8,0xDF,0xC2}};


const IID LIBID_NOTIFICATIONDLLLib = {0x66B2C5F4,0x5360,0x49E7,{0xB1,0xE9,0x01,0xA8,0xA1,0xB9,0x0D,0x61}};


const CLSID CLSID_Notify = {0xA26B7E05,0x9E4A,0x4297,{0x82,0x25,0x56,0x73,0xAC,0xFA,0x22,0xF8}};


#ifdef __cplusplus
}
#endif

