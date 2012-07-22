
senderserverps.dll: dlldata.obj senderserver_p.obj senderserver_i.obj
	link /dll /out:senderserverps.dll /def:senderserverps.def /entry:DllMain dlldata.obj senderserver_p.obj senderserver_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del senderserverps.dll
	@del senderserverps.lib
	@del senderserverps.exp
	@del dlldata.obj
	@del senderserver_p.obj
	@del senderserver_i.obj
