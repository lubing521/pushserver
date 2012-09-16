
NotificationDllps.dll: dlldata.obj NotificationDll_p.obj NotificationDll_i.obj
	link /dll /out:NotificationDllps.dll /def:NotificationDllps.def /entry:DllMain dlldata.obj NotificationDll_p.obj NotificationDll_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del NotificationDllps.dll
	@del NotificationDllps.lib
	@del NotificationDllps.exp
	@del dlldata.obj
	@del NotificationDll_p.obj
	@del NotificationDll_i.obj
