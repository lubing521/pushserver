# Microsoft Developer Studio Generated NMAKE File, Based on senderserver.dsp
!IF "$(CFG)" == ""
CFG=senderserver - Win32 Debug
!MESSAGE No configuration specified. Defaulting to senderserver - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "senderserver - Win32 Debug" && "$(CFG)" != "senderserver - Win32 Unicode Debug" && "$(CFG)" != "senderserver - Win32 Release MinSize" && "$(CFG)" != "senderserver - Win32 Release MinDependency" && "$(CFG)" != "senderserver - Win32 Unicode Release MinSize" && "$(CFG)" != "senderserver - Win32 Unicode Release MinDependency"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "senderserver.mak" CFG="senderserver - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "senderserver - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "senderserver - Win32 Unicode Debug" (based on "Win32 (x86) Application")
!MESSAGE "senderserver - Win32 Release MinSize" (based on "Win32 (x86) Application")
!MESSAGE "senderserver - Win32 Release MinDependency" (based on "Win32 (x86) Application")
!MESSAGE "senderserver - Win32 Unicode Release MinSize" (based on "Win32 (x86) Application")
!MESSAGE "senderserver - Win32 Unicode Release MinDependency" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "senderserver - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\senderserver.exe" "$(OUTDIR)\senderserver.bsc" ".\Debug\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\client.obj"
	-@erase "$(INTDIR)\client.sbr"
	-@erase "$(INTDIR)\ClientManager.obj"
	-@erase "$(INTDIR)\ClientManager.sbr"
	-@erase "$(INTDIR)\db.obj"
	-@erase "$(INTDIR)\db.sbr"
	-@erase "$(INTDIR)\Loader.obj"
	-@erase "$(INTDIR)\Loader.sbr"
	-@erase "$(INTDIR)\log.obj"
	-@erase "$(INTDIR)\log.sbr"
	-@erase "$(INTDIR)\Manager.obj"
	-@erase "$(INTDIR)\Manager.sbr"
	-@erase "$(INTDIR)\SeException.obj"
	-@erase "$(INTDIR)\SeException.sbr"
	-@erase "$(INTDIR)\sender.obj"
	-@erase "$(INTDIR)\sender.sbr"
	-@erase "$(INTDIR)\senderserver.obj"
	-@erase "$(INTDIR)\senderserver.pch"
	-@erase "$(INTDIR)\senderserver.res"
	-@erase "$(INTDIR)\senderserver.sbr"
	-@erase "$(INTDIR)\Server.obj"
	-@erase "$(INTDIR)\Server.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\tools.obj"
	-@erase "$(INTDIR)\tools.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\Worker.obj"
	-@erase "$(INTDIR)\Worker.sbr"
	-@erase "$(OUTDIR)\senderserver.bsc"
	-@erase "$(OUTDIR)\senderserver.exe"
	-@erase "$(OUTDIR)\senderserver.ilk"
	-@erase "$(OUTDIR)\senderserver.pdb"
	-@erase ".\senderserver.h"
	-@erase ".\senderserver.tlb"
	-@erase ".\senderserver_i.c"
	-@erase ".\Debug\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\senderserver.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\senderserver.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\senderserver.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\client.sbr" \
	"$(INTDIR)\ClientManager.sbr" \
	"$(INTDIR)\db.sbr" \
	"$(INTDIR)\Loader.sbr" \
	"$(INTDIR)\log.sbr" \
	"$(INTDIR)\Manager.sbr" \
	"$(INTDIR)\SeException.sbr" \
	"$(INTDIR)\sender.sbr" \
	"$(INTDIR)\senderserver.sbr" \
	"$(INTDIR)\Server.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\tools.sbr" \
	"$(INTDIR)\Worker.sbr"

"$(OUTDIR)\senderserver.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\senderserver.pdb" /debug /machine:I386 /out:"$(OUTDIR)\senderserver.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\client.obj" \
	"$(INTDIR)\ClientManager.obj" \
	"$(INTDIR)\db.obj" \
	"$(INTDIR)\Loader.obj" \
	"$(INTDIR)\log.obj" \
	"$(INTDIR)\Manager.obj" \
	"$(INTDIR)\SeException.obj" \
	"$(INTDIR)\sender.obj" \
	"$(INTDIR)\senderserver.obj" \
	"$(INTDIR)\Server.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\tools.obj" \
	"$(INTDIR)\Worker.obj" \
	"$(INTDIR)\senderserver.res" \
	".\WS2_32.LIB" \
	".\libmysql.lib" \
	".\mysqlclient.lib"

"$(OUTDIR)\senderserver.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Debug
TargetPath=.\Debug\senderserver.exe
InputPath=.\Debug\senderserver.exe
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	"$(TargetPath)" /RegServer 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	echo Server registration done! 
<< 
	

!ELSEIF  "$(CFG)" == "senderserver - Win32 Unicode Debug"

OUTDIR=.\DebugU
INTDIR=.\DebugU
# Begin Custom Macros
OutDir=.\DebugU
# End Custom Macros

ALL : "$(OUTDIR)\senderserver.exe" ".\senderserver.tlb" ".\senderserver.h" ".\senderserver_i.c" ".\DebugU\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\client.obj"
	-@erase "$(INTDIR)\ClientManager.obj"
	-@erase "$(INTDIR)\db.obj"
	-@erase "$(INTDIR)\Loader.obj"
	-@erase "$(INTDIR)\log.obj"
	-@erase "$(INTDIR)\Manager.obj"
	-@erase "$(INTDIR)\SeException.obj"
	-@erase "$(INTDIR)\sender.obj"
	-@erase "$(INTDIR)\senderserver.obj"
	-@erase "$(INTDIR)\senderserver.pch"
	-@erase "$(INTDIR)\senderserver.res"
	-@erase "$(INTDIR)\Server.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\tools.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\Worker.obj"
	-@erase "$(OUTDIR)\senderserver.exe"
	-@erase "$(OUTDIR)\senderserver.ilk"
	-@erase "$(OUTDIR)\senderserver.pdb"
	-@erase ".\senderserver.h"
	-@erase ".\senderserver.tlb"
	-@erase ".\senderserver_i.c"
	-@erase ".\DebugU\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_UNICODE" /Fp"$(INTDIR)\senderserver.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\senderserver.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\senderserver.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /entry:"wWinMainCRTStartup" /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\senderserver.pdb" /debug /machine:I386 /out:"$(OUTDIR)\senderserver.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\client.obj" \
	"$(INTDIR)\ClientManager.obj" \
	"$(INTDIR)\db.obj" \
	"$(INTDIR)\Loader.obj" \
	"$(INTDIR)\log.obj" \
	"$(INTDIR)\Manager.obj" \
	"$(INTDIR)\SeException.obj" \
	"$(INTDIR)\sender.obj" \
	"$(INTDIR)\senderserver.obj" \
	"$(INTDIR)\Server.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\tools.obj" \
	"$(INTDIR)\Worker.obj" \
	"$(INTDIR)\senderserver.res" \
	".\WS2_32.LIB" \
	".\libmysql.lib" \
	".\mysqlclient.lib"

"$(OUTDIR)\senderserver.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\DebugU
TargetPath=.\DebugU\senderserver.exe
InputPath=.\DebugU\senderserver.exe
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	if "%OS%"=="" goto NOTNT 
	if not "%OS%"=="Windows_NT" goto NOTNT 
	"$(TargetPath)" /RegServer 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	echo Server registration done! 
	goto end 
	:NOTNT 
	echo Warning : Cannot register Unicode EXE on Windows 95 
	:end 
<< 
	

!ELSEIF  "$(CFG)" == "senderserver - Win32 Release MinSize"

OUTDIR=.\ReleaseMinSize
INTDIR=.\ReleaseMinSize
# Begin Custom Macros
OutDir=.\ReleaseMinSize
# End Custom Macros

ALL : "$(OUTDIR)\senderserver.exe" ".\senderserver.tlb" ".\senderserver.h" ".\senderserver_i.c" ".\ReleaseMinSize\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\client.obj"
	-@erase "$(INTDIR)\ClientManager.obj"
	-@erase "$(INTDIR)\db.obj"
	-@erase "$(INTDIR)\Loader.obj"
	-@erase "$(INTDIR)\log.obj"
	-@erase "$(INTDIR)\Manager.obj"
	-@erase "$(INTDIR)\SeException.obj"
	-@erase "$(INTDIR)\sender.obj"
	-@erase "$(INTDIR)\senderserver.obj"
	-@erase "$(INTDIR)\senderserver.pch"
	-@erase "$(INTDIR)\senderserver.res"
	-@erase "$(INTDIR)\Server.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\tools.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\Worker.obj"
	-@erase "$(OUTDIR)\senderserver.exe"
	-@erase ".\senderserver.h"
	-@erase ".\senderserver.tlb"
	-@erase ".\senderserver_i.c"
	-@erase ".\ReleaseMinSize\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_ATL_DLL" /Fp"$(INTDIR)\senderserver.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\senderserver.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\senderserver.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\senderserver.pdb" /machine:I386 /out:"$(OUTDIR)\senderserver.exe" 
LINK32_OBJS= \
	"$(INTDIR)\client.obj" \
	"$(INTDIR)\ClientManager.obj" \
	"$(INTDIR)\db.obj" \
	"$(INTDIR)\Loader.obj" \
	"$(INTDIR)\log.obj" \
	"$(INTDIR)\Manager.obj" \
	"$(INTDIR)\SeException.obj" \
	"$(INTDIR)\sender.obj" \
	"$(INTDIR)\senderserver.obj" \
	"$(INTDIR)\Server.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\tools.obj" \
	"$(INTDIR)\Worker.obj" \
	"$(INTDIR)\senderserver.res" \
	".\WS2_32.LIB" \
	".\libmysql.lib" \
	".\mysqlclient.lib"

"$(OUTDIR)\senderserver.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseMinSize
TargetPath=.\ReleaseMinSize\senderserver.exe
InputPath=.\ReleaseMinSize\senderserver.exe
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	"$(TargetPath)" /RegServer 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	echo Server registration done! 
<< 
	

!ELSEIF  "$(CFG)" == "senderserver - Win32 Release MinDependency"

OUTDIR=.\ReleaseMinDependency
INTDIR=.\ReleaseMinDependency
# Begin Custom Macros
OutDir=.\ReleaseMinDependency
# End Custom Macros

ALL : "$(OUTDIR)\senderserver.exe" ".\senderserver.tlb" ".\senderserver.h" ".\senderserver_i.c" ".\ReleaseMinDependency\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\client.obj"
	-@erase "$(INTDIR)\ClientManager.obj"
	-@erase "$(INTDIR)\db.obj"
	-@erase "$(INTDIR)\Loader.obj"
	-@erase "$(INTDIR)\log.obj"
	-@erase "$(INTDIR)\Manager.obj"
	-@erase "$(INTDIR)\SeException.obj"
	-@erase "$(INTDIR)\sender.obj"
	-@erase "$(INTDIR)\senderserver.obj"
	-@erase "$(INTDIR)\senderserver.pch"
	-@erase "$(INTDIR)\senderserver.res"
	-@erase "$(INTDIR)\Server.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\tools.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\Worker.obj"
	-@erase "$(OUTDIR)\senderserver.exe"
	-@erase ".\senderserver.h"
	-@erase ".\senderserver.tlb"
	-@erase ".\senderserver_i.c"
	-@erase ".\ReleaseMinDependency\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_ATL_STATIC_REGISTRY" /Fp"$(INTDIR)\senderserver.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\senderserver.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\senderserver.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\senderserver.pdb" /machine:I386 /out:"$(OUTDIR)\senderserver.exe" 
LINK32_OBJS= \
	"$(INTDIR)\client.obj" \
	"$(INTDIR)\ClientManager.obj" \
	"$(INTDIR)\db.obj" \
	"$(INTDIR)\Loader.obj" \
	"$(INTDIR)\log.obj" \
	"$(INTDIR)\Manager.obj" \
	"$(INTDIR)\SeException.obj" \
	"$(INTDIR)\sender.obj" \
	"$(INTDIR)\senderserver.obj" \
	"$(INTDIR)\Server.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\tools.obj" \
	"$(INTDIR)\Worker.obj" \
	"$(INTDIR)\senderserver.res" \
	".\WS2_32.LIB" \
	".\libmysql.lib" \
	".\mysqlclient.lib"

"$(OUTDIR)\senderserver.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseMinDependency
TargetPath=.\ReleaseMinDependency\senderserver.exe
InputPath=.\ReleaseMinDependency\senderserver.exe
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	"$(TargetPath)" /RegServer 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	echo Server registration done! 
<< 
	

!ELSEIF  "$(CFG)" == "senderserver - Win32 Unicode Release MinSize"

OUTDIR=.\ReleaseUMinSize
INTDIR=.\ReleaseUMinSize
# Begin Custom Macros
OutDir=.\ReleaseUMinSize
# End Custom Macros

ALL : "$(OUTDIR)\senderserver.exe" ".\senderserver.tlb" ".\senderserver.h" ".\senderserver_i.c" ".\ReleaseUMinSize\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\client.obj"
	-@erase "$(INTDIR)\ClientManager.obj"
	-@erase "$(INTDIR)\db.obj"
	-@erase "$(INTDIR)\Loader.obj"
	-@erase "$(INTDIR)\log.obj"
	-@erase "$(INTDIR)\Manager.obj"
	-@erase "$(INTDIR)\SeException.obj"
	-@erase "$(INTDIR)\sender.obj"
	-@erase "$(INTDIR)\senderserver.obj"
	-@erase "$(INTDIR)\senderserver.pch"
	-@erase "$(INTDIR)\senderserver.res"
	-@erase "$(INTDIR)\Server.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\tools.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\Worker.obj"
	-@erase "$(OUTDIR)\senderserver.exe"
	-@erase ".\senderserver.h"
	-@erase ".\senderserver.tlb"
	-@erase ".\senderserver_i.c"
	-@erase ".\ReleaseUMinSize\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_UNICODE" /D "_ATL_DLL" /Fp"$(INTDIR)\senderserver.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\senderserver.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\senderserver.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\senderserver.pdb" /machine:I386 /out:"$(OUTDIR)\senderserver.exe" 
LINK32_OBJS= \
	"$(INTDIR)\client.obj" \
	"$(INTDIR)\ClientManager.obj" \
	"$(INTDIR)\db.obj" \
	"$(INTDIR)\Loader.obj" \
	"$(INTDIR)\log.obj" \
	"$(INTDIR)\Manager.obj" \
	"$(INTDIR)\SeException.obj" \
	"$(INTDIR)\sender.obj" \
	"$(INTDIR)\senderserver.obj" \
	"$(INTDIR)\Server.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\tools.obj" \
	"$(INTDIR)\Worker.obj" \
	"$(INTDIR)\senderserver.res" \
	".\WS2_32.LIB" \
	".\libmysql.lib" \
	".\mysqlclient.lib"

"$(OUTDIR)\senderserver.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseUMinSize
TargetPath=.\ReleaseUMinSize\senderserver.exe
InputPath=.\ReleaseUMinSize\senderserver.exe
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	if "%OS%"=="" goto NOTNT 
	if not "%OS%"=="Windows_NT" goto NOTNT 
	"$(TargetPath)" /RegServer 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	echo Server registration done! 
	goto end 
	:NOTNT 
	echo Warning : Cannot register Unicode EXE on Windows 95 
	:end 
<< 
	

!ELSEIF  "$(CFG)" == "senderserver - Win32 Unicode Release MinDependency"

OUTDIR=.\ReleaseUMinDependency
INTDIR=.\ReleaseUMinDependency
# Begin Custom Macros
OutDir=.\ReleaseUMinDependency
# End Custom Macros

ALL : "$(OUTDIR)\senderserver.exe" ".\senderserver.tlb" ".\senderserver.h" ".\senderserver_i.c" ".\ReleaseUMinDependency\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\client.obj"
	-@erase "$(INTDIR)\ClientManager.obj"
	-@erase "$(INTDIR)\db.obj"
	-@erase "$(INTDIR)\Loader.obj"
	-@erase "$(INTDIR)\log.obj"
	-@erase "$(INTDIR)\Manager.obj"
	-@erase "$(INTDIR)\SeException.obj"
	-@erase "$(INTDIR)\sender.obj"
	-@erase "$(INTDIR)\senderserver.obj"
	-@erase "$(INTDIR)\senderserver.pch"
	-@erase "$(INTDIR)\senderserver.res"
	-@erase "$(INTDIR)\Server.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\tools.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\Worker.obj"
	-@erase "$(OUTDIR)\senderserver.exe"
	-@erase ".\senderserver.h"
	-@erase ".\senderserver.tlb"
	-@erase ".\senderserver_i.c"
	-@erase ".\ReleaseUMinDependency\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /Fp"$(INTDIR)\senderserver.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\senderserver.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\senderserver.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\senderserver.pdb" /machine:I386 /out:"$(OUTDIR)\senderserver.exe" 
LINK32_OBJS= \
	"$(INTDIR)\client.obj" \
	"$(INTDIR)\ClientManager.obj" \
	"$(INTDIR)\db.obj" \
	"$(INTDIR)\Loader.obj" \
	"$(INTDIR)\log.obj" \
	"$(INTDIR)\Manager.obj" \
	"$(INTDIR)\SeException.obj" \
	"$(INTDIR)\sender.obj" \
	"$(INTDIR)\senderserver.obj" \
	"$(INTDIR)\Server.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\tools.obj" \
	"$(INTDIR)\Worker.obj" \
	"$(INTDIR)\senderserver.res" \
	".\WS2_32.LIB" \
	".\libmysql.lib" \
	".\mysqlclient.lib"

"$(OUTDIR)\senderserver.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseUMinDependency
TargetPath=.\ReleaseUMinDependency\senderserver.exe
InputPath=.\ReleaseUMinDependency\senderserver.exe
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	if "%OS%"=="" goto NOTNT 
	if not "%OS%"=="Windows_NT" goto NOTNT 
	"$(TargetPath)" /RegServer 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	echo Server registration done! 
	goto end 
	:NOTNT 
	echo Warning : Cannot register Unicode EXE on Windows 95 
	:end 
<< 
	

!ENDIF 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("senderserver.dep")
!INCLUDE "senderserver.dep"
!ELSE 
!MESSAGE Warning: cannot find "senderserver.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "senderserver - Win32 Debug" || "$(CFG)" == "senderserver - Win32 Unicode Debug" || "$(CFG)" == "senderserver - Win32 Release MinSize" || "$(CFG)" == "senderserver - Win32 Release MinDependency" || "$(CFG)" == "senderserver - Win32 Unicode Release MinSize" || "$(CFG)" == "senderserver - Win32 Unicode Release MinDependency"
SOURCE=.\client.cpp

!IF  "$(CFG)" == "senderserver - Win32 Debug"


"$(INTDIR)\client.obj"	"$(INTDIR)\client.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\senderserver.pch"


!ELSEIF  "$(CFG)" == "senderserver - Win32 Unicode Debug"


"$(INTDIR)\client.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\senderserver.pch"


!ELSEIF  "$(CFG)" == "senderserver - Win32 Release MinSize"


"$(INTDIR)\client.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\senderserver.pch"


!ELSEIF  "$(CFG)" == "senderserver - Win32 Release MinDependency"


"$(INTDIR)\client.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\senderserver.pch"


!ELSEIF  "$(CFG)" == "senderserver - Win32 Unicode Release MinSize"


"$(INTDIR)\client.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\senderserver.pch"


!ELSEIF  "$(CFG)" == "senderserver - Win32 Unicode Release MinDependency"


"$(INTDIR)\client.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\senderserver.pch"


!ENDIF 

SOURCE=.\ClientManager.cpp

!IF  "$(CFG)" == "senderserver - Win32 Debug"


"$(INTDIR)\ClientManager.obj"	"$(INTDIR)\ClientManager.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\senderserver.pch"


!ELSEIF  "$(CFG)" == "senderserver - Win32 Unicode Debug"


"$(INTDIR)\ClientManager.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\senderserver.pch"


!ELSEIF  "$(CFG)" == "senderserver - Win32 Release MinSize"


"$(INTDIR)\ClientManager.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\senderserver.pch"


!ELSEIF  "$(CFG)" == "senderserver - Win32 Release MinDependency"


"$(INTDIR)\ClientManager.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\senderserver.pch"


!ELSEIF  "$(CFG)" == "senderserver - Win32 Unicode Release MinSize"


"$(INTDIR)\ClientManager.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\senderserver.pch"


!ELSEIF  "$(CFG)" == "senderserver - Win32 Unicode Release MinDependency"


"$(INTDIR)\ClientManager.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\senderserver.pch"


!ENDIF 

SOURCE=.\db.cpp

!IF  "$(CFG)" == "senderserver - Win32 Debug"


"$(INTDIR)\db.obj"	"$(INTDIR)\db.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\senderserver.pch"


!ELSEIF  "$(CFG)" == "senderserver - Win32 Unicode Debug"


"$(INTDIR)\db.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\senderserver.pch"


!ELSEIF  "$(CFG)" == "senderserver - Win32 Release MinSize"


"$(INTDIR)\db.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\senderserver.pch"


!ELSEIF  "$(CFG)" == "senderserver - Win32 Release MinDependency"


"$(INTDIR)\db.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\senderserver.pch"


!ELSEIF  "$(CFG)" == "senderserver - Win32 Unicode Release MinSize"


"$(INTDIR)\db.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\senderserver.pch"


!ELSEIF  "$(CFG)" == "senderserver - Win32 Unicode Release MinDependency"


"$(INTDIR)\db.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\senderserver.pch"


!ENDIF 

SOURCE=.\Loader.cpp

!IF  "$(CFG)" == "senderserver - Win32 Debug"


"$(INTDIR)\Loader.obj"	"$(INTDIR)\Loader.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\senderserver.pch"


!ELSEIF  "$(CFG)" == "senderserver - Win32 Unicode Debug"


"$(INTDIR)\Loader.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\senderserver.pch"


!ELSEIF  "$(CFG)" == "senderserver - Win32 Release MinSize"


"$(INTDIR)\Loader.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\senderserver.pch"


!ELSEIF  "$(CFG)" == "senderserver - Win32 Release MinDependency"


"$(INTDIR)\Loader.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\senderserver.pch"


!ELSEIF  "$(CFG)" == "senderserver - Win32 Unicode Release MinSize"


"$(INTDIR)\Loader.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\senderserver.pch"


!ELSEIF  "$(CFG)" == "senderserver - Win32 Unicode Release MinDependency"


"$(INTDIR)\Loader.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\senderserver.pch"


!ENDIF 

SOURCE=.\log.cpp

!IF  "$(CFG)" == "senderserver - Win32 Debug"


"$(INTDIR)\log.obj"	"$(INTDIR)\log.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\senderserver.pch"


!ELSEIF  "$(CFG)" == "senderserver - Win32 Unicode Debug"


"$(INTDIR)\log.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\senderserver.pch"


!ELSEIF  "$(CFG)" == "senderserver - Win32 Release MinSize"


"$(INTDIR)\log.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\senderserver.pch"


!ELSEIF  "$(CFG)" == "senderserver - Win32 Release MinDependency"


"$(INTDIR)\log.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\senderserver.pch"


!ELSEIF  "$(CFG)" == "senderserver - Win32 Unicode Release MinSize"


"$(INTDIR)\log.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\senderserver.pch"


!ELSEIF  "$(CFG)" == "senderserver - Win32 Unicode Release MinDependency"


"$(INTDIR)\log.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\senderserver.pch"


!ENDIF 

SOURCE=.\Manager.cpp

!IF  "$(CFG)" == "senderserver - Win32 Debug"


"$(INTDIR)\Manager.obj"	"$(INTDIR)\Manager.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\senderserver.pch"


!ELSEIF  "$(CFG)" == "senderserver - Win32 Unicode Debug"


"$(INTDIR)\Manager.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\senderserver.pch"


!ELSEIF  "$(CFG)" == "senderserver - Win32 Release MinSize"


"$(INTDIR)\Manager.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\senderserver.pch"


!ELSEIF  "$(CFG)" == "senderserver - Win32 Release MinDependency"


"$(INTDIR)\Manager.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\senderserver.pch"


!ELSEIF  "$(CFG)" == "senderserver - Win32 Unicode Release MinSize"


"$(INTDIR)\Manager.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\senderserver.pch"


!ELSEIF  "$(CFG)" == "senderserver - Win32 Unicode Release MinDependency"


"$(INTDIR)\Manager.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\senderserver.pch"


!ENDIF 

SOURCE=.\SeException.cpp

!IF  "$(CFG)" == "senderserver - Win32 Debug"


"$(INTDIR)\SeException.obj"	"$(INTDIR)\SeException.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\senderserver.pch"


!ELSEIF  "$(CFG)" == "senderserver - Win32 Unicode Debug"


"$(INTDIR)\SeException.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\senderserver.pch"


!ELSEIF  "$(CFG)" == "senderserver - Win32 Release MinSize"


"$(INTDIR)\SeException.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\senderserver.pch"


!ELSEIF  "$(CFG)" == "senderserver - Win32 Release MinDependency"


"$(INTDIR)\SeException.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\senderserver.pch"


!ELSEIF  "$(CFG)" == "senderserver - Win32 Unicode Release MinSize"


"$(INTDIR)\SeException.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\senderserver.pch"


!ELSEIF  "$(CFG)" == "senderserver - Win32 Unicode Release MinDependency"


"$(INTDIR)\SeException.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\senderserver.pch"


!ENDIF 

SOURCE=.\sender.cpp

!IF  "$(CFG)" == "senderserver - Win32 Debug"


"$(INTDIR)\sender.obj"	"$(INTDIR)\sender.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\senderserver.pch"


!ELSEIF  "$(CFG)" == "senderserver - Win32 Unicode Debug"


"$(INTDIR)\sender.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\senderserver.pch"


!ELSEIF  "$(CFG)" == "senderserver - Win32 Release MinSize"


"$(INTDIR)\sender.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\senderserver.pch"


!ELSEIF  "$(CFG)" == "senderserver - Win32 Release MinDependency"


"$(INTDIR)\sender.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\senderserver.pch"


!ELSEIF  "$(CFG)" == "senderserver - Win32 Unicode Release MinSize"


"$(INTDIR)\sender.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\senderserver.pch"


!ELSEIF  "$(CFG)" == "senderserver - Win32 Unicode Release MinDependency"


"$(INTDIR)\sender.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\senderserver.pch"


!ENDIF 

SOURCE=.\senderserver.cpp

!IF  "$(CFG)" == "senderserver - Win32 Debug"


"$(INTDIR)\senderserver.obj"	"$(INTDIR)\senderserver.sbr" : $(SOURCE) "$(INTDIR)" ".\senderserver.h" ".\senderserver_i.c" "$(INTDIR)\senderserver.pch"


!ELSEIF  "$(CFG)" == "senderserver - Win32 Unicode Debug"


"$(INTDIR)\senderserver.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\senderserver.pch"


!ELSEIF  "$(CFG)" == "senderserver - Win32 Release MinSize"


"$(INTDIR)\senderserver.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\senderserver.pch"


!ELSEIF  "$(CFG)" == "senderserver - Win32 Release MinDependency"


"$(INTDIR)\senderserver.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\senderserver.pch"


!ELSEIF  "$(CFG)" == "senderserver - Win32 Unicode Release MinSize"


"$(INTDIR)\senderserver.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\senderserver.pch"


!ELSEIF  "$(CFG)" == "senderserver - Win32 Unicode Release MinDependency"


"$(INTDIR)\senderserver.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\senderserver.pch"


!ENDIF 

SOURCE=.\senderserver.idl
MTL_SWITCHES=/tlb ".\senderserver.tlb" /h "senderserver.h" /iid "senderserver_i.c" /Oicf 

".\senderserver.tlb"	".\senderserver.h"	".\senderserver_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


SOURCE=.\senderserver.rc

"$(INTDIR)\senderserver.res" : $(SOURCE) "$(INTDIR)" ".\senderserver.tlb"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\Server.cpp

!IF  "$(CFG)" == "senderserver - Win32 Debug"


"$(INTDIR)\Server.obj"	"$(INTDIR)\Server.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\senderserver.pch"


!ELSEIF  "$(CFG)" == "senderserver - Win32 Unicode Debug"


"$(INTDIR)\Server.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\senderserver.pch"


!ELSEIF  "$(CFG)" == "senderserver - Win32 Release MinSize"


"$(INTDIR)\Server.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\senderserver.pch"


!ELSEIF  "$(CFG)" == "senderserver - Win32 Release MinDependency"


"$(INTDIR)\Server.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\senderserver.pch"


!ELSEIF  "$(CFG)" == "senderserver - Win32 Unicode Release MinSize"


"$(INTDIR)\Server.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\senderserver.pch"


!ELSEIF  "$(CFG)" == "senderserver - Win32 Unicode Release MinDependency"


"$(INTDIR)\Server.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\senderserver.pch"


!ENDIF 

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "senderserver - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\senderserver.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\senderserver.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "senderserver - Win32 Unicode Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_UNICODE" /Fp"$(INTDIR)\senderserver.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\senderserver.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "senderserver - Win32 Release MinSize"

CPP_SWITCHES=/nologo /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_ATL_DLL" /Fp"$(INTDIR)\senderserver.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\senderserver.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "senderserver - Win32 Release MinDependency"

CPP_SWITCHES=/nologo /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_ATL_STATIC_REGISTRY" /Fp"$(INTDIR)\senderserver.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\senderserver.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "senderserver - Win32 Unicode Release MinSize"

CPP_SWITCHES=/nologo /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_UNICODE" /D "_ATL_DLL" /Fp"$(INTDIR)\senderserver.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\senderserver.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "senderserver - Win32 Unicode Release MinDependency"

CPP_SWITCHES=/nologo /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /Fp"$(INTDIR)\senderserver.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\senderserver.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\tools.cpp

!IF  "$(CFG)" == "senderserver - Win32 Debug"


"$(INTDIR)\tools.obj"	"$(INTDIR)\tools.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\senderserver.pch"


!ELSEIF  "$(CFG)" == "senderserver - Win32 Unicode Debug"


"$(INTDIR)\tools.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\senderserver.pch"


!ELSEIF  "$(CFG)" == "senderserver - Win32 Release MinSize"


"$(INTDIR)\tools.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\senderserver.pch"


!ELSEIF  "$(CFG)" == "senderserver - Win32 Release MinDependency"


"$(INTDIR)\tools.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\senderserver.pch"


!ELSEIF  "$(CFG)" == "senderserver - Win32 Unicode Release MinSize"


"$(INTDIR)\tools.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\senderserver.pch"


!ELSEIF  "$(CFG)" == "senderserver - Win32 Unicode Release MinDependency"


"$(INTDIR)\tools.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\senderserver.pch"


!ENDIF 

SOURCE=.\Worker.cpp

!IF  "$(CFG)" == "senderserver - Win32 Debug"


"$(INTDIR)\Worker.obj"	"$(INTDIR)\Worker.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\senderserver.pch"


!ELSEIF  "$(CFG)" == "senderserver - Win32 Unicode Debug"


"$(INTDIR)\Worker.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\senderserver.pch"


!ELSEIF  "$(CFG)" == "senderserver - Win32 Release MinSize"


"$(INTDIR)\Worker.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\senderserver.pch"


!ELSEIF  "$(CFG)" == "senderserver - Win32 Release MinDependency"


"$(INTDIR)\Worker.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\senderserver.pch"


!ELSEIF  "$(CFG)" == "senderserver - Win32 Unicode Release MinSize"


"$(INTDIR)\Worker.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\senderserver.pch"


!ELSEIF  "$(CFG)" == "senderserver - Win32 Unicode Release MinDependency"


"$(INTDIR)\Worker.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\senderserver.pch"


!ENDIF 


!ENDIF 

