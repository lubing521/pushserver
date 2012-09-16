
NotificationServiceps.dll: dlldata.obj NotificationService_p.obj NotificationService_i.obj
	link /dll /out:NotificationServiceps.dll /def:NotificationServiceps.def /entry:DllMain dlldata.obj NotificationService_p.obj NotificationService_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del NotificationServiceps.dll
	@del NotificationServiceps.lib
	@del NotificationServiceps.exp
	@del dlldata.obj
	@del NotificationService_p.obj
	@del NotificationService_i.obj