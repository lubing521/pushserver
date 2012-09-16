/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Mon Sep 10 17:57:42 2012
 */
/* Compiler settings for F:\hly\PushSubsystem\Notification4IOS\NotificationService\NotificationService.idl:
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

const IID LIBID_NOTIFICATIONSERVICELib = {0xD7A6B873,0x84AD,0x413E,{0xAB,0x3D,0x96,0xDF,0x33,0x9B,0xB6,0x01}};


#ifdef __cplusplus
}
#endif

