# Microsoft Developer Studio Generated NMAKE File, Based on NotificationDll.dsp
!IF "$(CFG)" == ""
CFG=NotificationDll - Win32 Debug
!MESSAGE No configuration specified. Defaulting to NotificationDll - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "NotificationDll - Win32 Debug" && "$(CFG)" != "NotificationDll - Win32 Unicode Debug" && "$(CFG)" != "NotificationDll - Win32 Release MinSize" && "$(CFG)" != "NotificationDll - Win32 Release MinDependency" && "$(CFG)" != "NotificationDll - Win32 Unicode Release MinSize" && "$(CFG)" != "NotificationDll - Win32 Unicode Release MinDependency"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "NotificationDll.mak" CFG="NotificationDll - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "NotificationDll - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "NotificationDll - Win32 Unicode Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "NotificationDll - Win32 Release MinSize" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "NotificationDll - Win32 Release MinDependency" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "NotificationDll - Win32 Unicode Release MinSize" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "NotificationDll - Win32 Unicode Release MinDependency" (based on "Win32 (x86) Dynamic-Link Library")
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

!IF  "$(CFG)" == "NotificationDll - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\NotificationDll.dll" "$(OUTDIR)\NotificationDll.bsc" ".\Debug\regsvr32.trg"


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
	-@erase "$(INTDIR)\NotificationDll.obj"
	-@erase "$(INTDIR)\NotificationDll.pch"
	-@erase "$(INTDIR)\NotificationDll.res"
	-@erase "$(INTDIR)\NotificationDll.sbr"
	-@erase "$(INTDIR)\Notify.obj"
	-@erase "$(INTDIR)\Notify.sbr"
	-@erase "$(INTDIR)\SeException.obj"
	-@erase "$(INTDIR)\SeException.sbr"
	-@erase "$(INTDIR)\sender.obj"
	-@erase "$(INTDIR)\sender.sbr"
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
	-@erase "$(OUTDIR)\NotificationDll.bsc"
	-@erase "$(OUTDIR)\NotificationDll.dll"
	-@erase "$(OUTDIR)\NotificationDll.exp"
	-@erase "$(OUTDIR)\NotificationDll.ilk"
	-@erase "$(OUTDIR)\NotificationDll.lib"
	-@erase "$(OUTDIR)\NotificationDll.map"
	-@erase "$(OUTDIR)\NotificationDll.pdb"
	-@erase ".\NotificationDll.h"
	-@erase ".\NotificationDll.tlb"
	-@erase ".\NotificationDll_i.c"
	-@erase ".\Debug\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\NotificationDll.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\NotificationDll.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\NotificationDll.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\client.sbr" \
	"$(INTDIR)\ClientManager.sbr" \
	"$(INTDIR)\db.sbr" \
	"$(INTDIR)\Loader.sbr" \
	"$(INTDIR)\log.sbr" \
	"$(INTDIR)\Manager.sbr" \
	"$(INTDIR)\NotificationDll.sbr" \
	"$(INTDIR)\Notify.sbr" \
	"$(INTDIR)\SeException.sbr" \
	"$(INTDIR)\sender.sbr" \
	"$(INTDIR)\Server.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\tools.sbr" \
	"$(INTDIR)\Worker.sbr"

"$(OUTDIR)\NotificationDll.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\NotificationDll.pdb" /map:"$(INTDIR)\NotificationDll.map" /debug /machine:I386 /def:".\NotificationDll.def" /out:"$(OUTDIR)\NotificationDll.dll" /implib:"$(OUTDIR)\NotificationDll.lib" /MAPINFO:LINES /MAPINFO:EXPORTS /OPT:REF 
DEF_FILE= \
	".\NotificationDll.def"
LINK32_OBJS= \
	"$(INTDIR)\client.obj" \
	"$(INTDIR)\ClientManager.obj" \
	"$(INTDIR)\db.obj" \
	"$(INTDIR)\Loader.obj" \
	"$(INTDIR)\log.obj" \
	"$(INTDIR)\Manager.obj" \
	"$(INTDIR)\NotificationDll.obj" \
	"$(INTDIR)\Notify.obj" \
	"$(INTDIR)\SeException.obj" \
	"$(INTDIR)\sender.obj" \
	"$(INTDIR)\Server.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\tools.obj" \
	"$(INTDIR)\Worker.obj" \
	"$(INTDIR)\NotificationDll.res" \
	".\libeay32.lib" \
	".\ssleay32.lib"

"$(OUTDIR)\NotificationDll.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Debug
TargetPath=.\Debug\NotificationDll.dll
InputPath=.\Debug\NotificationDll.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "NotificationDll - Win32 Unicode Debug"

OUTDIR=.\DebugU
INTDIR=.\DebugU
# Begin Custom Macros
OutDir=.\DebugU
# End Custom Macros

ALL : "$(OUTDIR)\NotificationDll.dll" ".\NotificationDll.tlb" ".\NotificationDll.h" ".\NotificationDll_i.c" ".\DebugU\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\client.obj"
	-@erase "$(INTDIR)\ClientManager.obj"
	-@erase "$(INTDIR)\db.obj"
	-@erase "$(INTDIR)\Loader.obj"
	-@erase "$(INTDIR)\log.obj"
	-@erase "$(INTDIR)\Manager.obj"
	-@erase "$(INTDIR)\NotificationDll.obj"
	-@erase "$(INTDIR)\NotificationDll.pch"
	-@erase "$(INTDIR)\NotificationDll.res"
	-@erase "$(INTDIR)\Notify.obj"
	-@erase "$(INTDIR)\SeException.obj"
	-@erase "$(INTDIR)\sender.obj"
	-@erase "$(INTDIR)\Server.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\tools.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\Worker.obj"
	-@erase "$(OUTDIR)\NotificationDll.dll"
	-@erase "$(OUTDIR)\NotificationDll.exp"
	-@erase "$(OUTDIR)\NotificationDll.ilk"
	-@erase "$(OUTDIR)\NotificationDll.lib"
	-@erase "$(OUTDIR)\NotificationDll.pdb"
	-@erase ".\NotificationDll.h"
	-@erase ".\NotificationDll.tlb"
	-@erase ".\NotificationDll_i.c"
	-@erase ".\DebugU\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\NotificationDll.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\NotificationDll.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\NotificationDll.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\NotificationDll.pdb" /debug /machine:I386 /def:".\NotificationDll.def" /out:"$(OUTDIR)\NotificationDll.dll" /implib:"$(OUTDIR)\NotificationDll.lib" /pdbtype:sept 
DEF_FILE= \
	".\NotificationDll.def"
LINK32_OBJS= \
	"$(INTDIR)\client.obj" \
	"$(INTDIR)\ClientManager.obj" \
	"$(INTDIR)\db.obj" \
	"$(INTDIR)\Loader.obj" \
	"$(INTDIR)\log.obj" \
	"$(INTDIR)\Manager.obj" \
	"$(INTDIR)\NotificationDll.obj" \
	"$(INTDIR)\Notify.obj" \
	"$(INTDIR)\SeException.obj" \
	"$(INTDIR)\sender.obj" \
	"$(INTDIR)\Server.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\tools.obj" \
	"$(INTDIR)\Worker.obj" \
	"$(INTDIR)\NotificationDll.res" \
	".\libeay32.lib" \
	".\ssleay32.lib"

"$(OUTDIR)\NotificationDll.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\DebugU
TargetPath=.\DebugU\NotificationDll.dll
InputPath=.\DebugU\NotificationDll.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	if "%OS%"=="" goto NOTNT 
	if not "%OS%"=="Windows_NT" goto NOTNT 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	goto end 
	:NOTNT 
	echo Warning : Cannot register Unicode DLL on Windows 95 
	:end 
<< 
	

!ELSEIF  "$(CFG)" == "NotificationDll - Win32 Release MinSize"

OUTDIR=.\ReleaseMinSize
INTDIR=.\ReleaseMinSize
# Begin Custom Macros
OutDir=.\ReleaseMinSize
# End Custom Macros

ALL : "$(OUTDIR)\NotificationDll.dll" ".\NotificationDll.tlb" ".\NotificationDll.h" ".\NotificationDll_i.c" ".\ReleaseMinSize\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\client.obj"
	-@erase "$(INTDIR)\ClientManager.obj"
	-@erase "$(INTDIR)\db.obj"
	-@erase "$(INTDIR)\Loader.obj"
	-@erase "$(INTDIR)\log.obj"
	-@erase "$(INTDIR)\Manager.obj"
	-@erase "$(INTDIR)\NotificationDll.obj"
	-@erase "$(INTDIR)\NotificationDll.pch"
	-@erase "$(INTDIR)\NotificationDll.res"
	-@erase "$(INTDIR)\Notify.obj"
	-@erase "$(INTDIR)\SeException.obj"
	-@erase "$(INTDIR)\sender.obj"
	-@erase "$(INTDIR)\Server.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\tools.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\Worker.obj"
	-@erase "$(OUTDIR)\NotificationDll.dll"
	-@erase "$(OUTDIR)\NotificationDll.exp"
	-@erase "$(OUTDIR)\NotificationDll.lib"
	-@erase "$(OUTDIR)\NotificationDll.map"
	-@erase "$(OUTDIR)\NotificationDll.pdb"
	-@erase ".\NotificationDll.h"
	-@erase ".\NotificationDll.tlb"
	-@erase ".\NotificationDll_i.c"
	-@erase ".\ReleaseMinSize\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_DLL" /Fp"$(INTDIR)\NotificationDll.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\NotificationDll.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\NotificationDll.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\NotificationDll.pdb" /map:"$(INTDIR)\NotificationDll.map" /debug /machine:I386 /def:".\NotificationDll.def" /out:"$(OUTDIR)\NotificationDll.dll" /implib:"$(OUTDIR)\NotificationDll.lib" /MAPINFO:LINES /MAPINFO:EXPORTS /OPT:REF 
DEF_FILE= \
	".\NotificationDll.def"
LINK32_OBJS= \
	"$(INTDIR)\client.obj" \
	"$(INTDIR)\ClientManager.obj" \
	"$(INTDIR)\db.obj" \
	"$(INTDIR)\Loader.obj" \
	"$(INTDIR)\log.obj" \
	"$(INTDIR)\Manager.obj" \
	"$(INTDIR)\NotificationDll.obj" \
	"$(INTDIR)\Notify.obj" \
	"$(INTDIR)\SeException.obj" \
	"$(INTDIR)\sender.obj" \
	"$(INTDIR)\Server.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\tools.obj" \
	"$(INTDIR)\Worker.obj" \
	"$(INTDIR)\NotificationDll.res" \
	".\libeay32.lib" \
	".\ssleay32.lib"

"$(OUTDIR)\NotificationDll.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseMinSize
TargetPath=.\ReleaseMinSize\NotificationDll.dll
InputPath=.\ReleaseMinSize\NotificationDll.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "NotificationDll - Win32 Release MinDependency"

OUTDIR=.\ReleaseMinDependency
INTDIR=.\ReleaseMinDependency
# Begin Custom Macros
OutDir=.\ReleaseMinDependency
# End Custom Macros

ALL : "$(OUTDIR)\NotificationDll.dll" ".\NotificationDll.tlb" ".\NotificationDll.h" ".\NotificationDll_i.c" ".\ReleaseMinDependency\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\client.obj"
	-@erase "$(INTDIR)\ClientManager.obj"
	-@erase "$(INTDIR)\db.obj"
	-@erase "$(INTDIR)\Loader.obj"
	-@erase "$(INTDIR)\log.obj"
	-@erase "$(INTDIR)\Manager.obj"
	-@erase "$(INTDIR)\NotificationDll.obj"
	-@erase "$(INTDIR)\NotificationDll.pch"
	-@erase "$(INTDIR)\NotificationDll.res"
	-@erase "$(INTDIR)\Notify.obj"
	-@erase "$(INTDIR)\SeException.obj"
	-@erase "$(INTDIR)\sender.obj"
	-@erase "$(INTDIR)\Server.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\tools.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\Worker.obj"
	-@erase "$(OUTDIR)\NotificationDll.dll"
	-@erase "$(OUTDIR)\NotificationDll.exp"
	-@erase "$(OUTDIR)\NotificationDll.lib"
	-@erase "$(OUTDIR)\NotificationDll.map"
	-@erase "$(OUTDIR)\NotificationDll.pdb"
	-@erase ".\NotificationDll.h"
	-@erase ".\NotificationDll.tlb"
	-@erase ".\NotificationDll_i.c"
	-@erase ".\ReleaseMinDependency\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /Fp"$(INTDIR)\NotificationDll.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\NotificationDll.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\NotificationDll.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\NotificationDll.pdb" /map:"$(INTDIR)\NotificationDll.map" /debug /machine:I386 /def:".\NotificationDll.def" /out:"$(OUTDIR)\NotificationDll.dll" /implib:"$(OUTDIR)\NotificationDll.lib" /MAPINFO:LINES /MAPINFO:EXPORTS /OPT:REF 
DEF_FILE= \
	".\NotificationDll.def"
LINK32_OBJS= \
	"$(INTDIR)\client.obj" \
	"$(INTDIR)\ClientManager.obj" \
	"$(INTDIR)\db.obj" \
	"$(INTDIR)\Loader.obj" \
	"$(INTDIR)\log.obj" \
	"$(INTDIR)\Manager.obj" \
	"$(INTDIR)\NotificationDll.obj" \
	"$(INTDIR)\Notify.obj" \
	"$(INTDIR)\SeException.obj" \
	"$(INTDIR)\sender.obj" \
	"$(INTDIR)\Server.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\tools.obj" \
	"$(INTDIR)\Worker.obj" \
	"$(INTDIR)\NotificationDll.res" \
	".\libeay32.lib" \
	".\ssleay32.lib"

"$(OUTDIR)\NotificationDll.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseMinDependency
TargetPath=.\ReleaseMinDependency\NotificationDll.dll
InputPath=.\ReleaseMinDependency\NotificationDll.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "NotificationDll - Win32 Unicode Release MinSize"

OUTDIR=.\ReleaseUMinSize
INTDIR=.\ReleaseUMinSize
# Begin Custom Macros
OutDir=.\ReleaseUMinSize
# End Custom Macros

ALL : "$(OUTDIR)\NotificationDll.dll" ".\NotificationDll.tlb" ".\NotificationDll.h" ".\NotificationDll_i.c" ".\ReleaseUMinSize\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\client.obj"
	-@erase "$(INTDIR)\ClientManager.obj"
	-@erase "$(INTDIR)\db.obj"
	-@erase "$(INTDIR)\Loader.obj"
	-@erase "$(INTDIR)\log.obj"
	-@erase "$(INTDIR)\Manager.obj"
	-@erase "$(INTDIR)\NotificationDll.obj"
	-@erase "$(INTDIR)\NotificationDll.pch"
	-@erase "$(INTDIR)\NotificationDll.res"
	-@erase "$(INTDIR)\Notify.obj"
	-@erase "$(INTDIR)\SeException.obj"
	-@erase "$(INTDIR)\sender.obj"
	-@erase "$(INTDIR)\Server.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\tools.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\Worker.obj"
	-@erase "$(OUTDIR)\NotificationDll.dll"
	-@erase "$(OUTDIR)\NotificationDll.exp"
	-@erase "$(OUTDIR)\NotificationDll.lib"
	-@erase ".\NotificationDll.h"
	-@erase ".\NotificationDll.tlb"
	-@erase ".\NotificationDll_i.c"
	-@erase ".\ReleaseUMinSize\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\NotificationDll.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\NotificationDll.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\NotificationDll.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\NotificationDll.pdb" /machine:I386 /def:".\NotificationDll.def" /out:"$(OUTDIR)\NotificationDll.dll" /implib:"$(OUTDIR)\NotificationDll.lib" 
DEF_FILE= \
	".\NotificationDll.def"
LINK32_OBJS= \
	"$(INTDIR)\client.obj" \
	"$(INTDIR)\ClientManager.obj" \
	"$(INTDIR)\db.obj" \
	"$(INTDIR)\Loader.obj" \
	"$(INTDIR)\log.obj" \
	"$(INTDIR)\Manager.obj" \
	"$(INTDIR)\NotificationDll.obj" \
	"$(INTDIR)\Notify.obj" \
	"$(INTDIR)\SeException.obj" \
	"$(INTDIR)\sender.obj" \
	"$(INTDIR)\Server.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\tools.obj" \
	"$(INTDIR)\Worker.obj" \
	"$(INTDIR)\NotificationDll.res" \
	".\libeay32.lib" \
	".\ssleay32.lib"

"$(OUTDIR)\NotificationDll.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseUMinSize
TargetPath=.\ReleaseUMinSize\NotificationDll.dll
InputPath=.\ReleaseUMinSize\NotificationDll.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	if "%OS%"=="" goto NOTNT 
	if not "%OS%"=="Windows_NT" goto NOTNT 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	goto end 
	:NOTNT 
	echo Warning : Cannot register Unicode DLL on Windows 95 
	:end 
<< 
	

!ELSEIF  "$(CFG)" == "NotificationDll - Win32 Unicode Release MinDependency"

OUTDIR=.\ReleaseUMinDependency
INTDIR=.\ReleaseUMinDependency
# Begin Custom Macros
OutDir=.\ReleaseUMinDependency
# End Custom Macros

ALL : "$(OUTDIR)\NotificationDll.dll" ".\NotificationDll.tlb" ".\NotificationDll.h" ".\NotificationDll_i.c" ".\ReleaseUMinDependency\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\client.obj"
	-@erase "$(INTDIR)\ClientManager.obj"
	-@erase "$(INTDIR)\db.obj"
	-@erase "$(INTDIR)\Loader.obj"
	-@erase "$(INTDIR)\log.obj"
	-@erase "$(INTDIR)\Manager.obj"
	-@erase "$(INTDIR)\NotificationDll.obj"
	-@erase "$(INTDIR)\NotificationDll.pch"
	-@erase "$(INTDIR)\NotificationDll.res"
	-@erase "$(INTDIR)\Notify.obj"
	-@erase "$(INTDIR)\SeException.obj"
	-@erase "$(INTDIR)\sender.obj"
	-@erase "$(INTDIR)\Server.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\tools.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\Worker.obj"
	-@erase "$(OUTDIR)\NotificationDll.dll"
	-@erase "$(OUTDIR)\NotificationDll.exp"
	-@erase "$(OUTDIR)\NotificationDll.lib"
	-@erase ".\NotificationDll.h"
	-@erase ".\NotificationDll.tlb"
	-@erase ".\NotificationDll_i.c"
	-@erase ".\ReleaseUMinDependency\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\NotificationDll.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\NotificationDll.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\NotificationDll.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\NotificationDll.pdb" /machine:I386 /def:".\NotificationDll.def" /out:"$(OUTDIR)\NotificationDll.dll" /implib:"$(OUTDIR)\NotificationDll.lib" 
DEF_FILE= \
	".\NotificationDll.def"
LINK32_OBJS= \
	"$(INTDIR)\client.obj" \
	"$(INTDIR)\ClientManager.obj" \
	"$(INTDIR)\db.obj" \
	"$(INTDIR)\Loader.obj" \
	"$(INTDIR)\log.obj" \
	"$(INTDIR)\Manager.obj" \
	"$(INTDIR)\NotificationDll.obj" \
	"$(INTDIR)\Notify.obj" \
	"$(INTDIR)\SeException.obj" \
	"$(INTDIR)\sender.obj" \
	"$(INTDIR)\Server.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\tools.obj" \
	"$(INTDIR)\Worker.obj" \
	"$(INTDIR)\NotificationDll.res" \
	".\libeay32.lib" \
	".\ssleay32.lib"

"$(OUTDIR)\NotificationDll.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseUMinDependency
TargetPath=.\ReleaseUMinDependency\NotificationDll.dll
InputPath=.\ReleaseUMinDependency\NotificationDll.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	if "%OS%"=="" goto NOTNT 
	if not "%OS%"=="Windows_NT" goto NOTNT 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	goto end 
	:NOTNT 
	echo Warning : Cannot register Unicode DLL on Windows 95 
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

MTL_PROJ=

!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("NotificationDll.dep")
!INCLUDE "NotificationDll.dep"
!ELSE 
!MESSAGE Warning: cannot find "NotificationDll.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "NotificationDll - Win32 Debug" || "$(CFG)" == "NotificationDll - Win32 Unicode Debug" || "$(CFG)" == "NotificationDll - Win32 Release MinSize" || "$(CFG)" == "NotificationDll - Win32 Release MinDependency" || "$(CFG)" == "NotificationDll - Win32 Unicode Release MinSize" || "$(CFG)" == "NotificationDll - Win32 Unicode Release MinDependency"
SOURCE=.\client.cpp

!IF  "$(CFG)" == "NotificationDll - Win32 Debug"


"$(INTDIR)\client.obj"	"$(INTDIR)\client.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\NotificationDll.pch"


!ELSEIF  "$(CFG)" == "NotificationDll - Win32 Unicode Debug"


"$(INTDIR)\client.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\NotificationDll.pch"


!ELSEIF  "$(CFG)" == "NotificationDll - Win32 Release MinSize"


"$(INTDIR)\client.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\NotificationDll.pch"


!ELSEIF  "$(CFG)" == "NotificationDll - Win32 Release MinDependency"


"$(INTDIR)\client.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\NotificationDll.pch"


!ELSEIF  "$(CFG)" == "NotificationDll - Win32 Unicode Release MinSize"


"$(INTDIR)\client.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\NotificationDll.pch"


!ELSEIF  "$(CFG)" == "NotificationDll - Win32 Unicode Release MinDependency"


"$(INTDIR)\client.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\NotificationDll.pch"


!ENDIF 

SOURCE=.\ClientManager.cpp

!IF  "$(CFG)" == "NotificationDll - Win32 Debug"


"$(INTDIR)\ClientManager.obj"	"$(INTDIR)\ClientManager.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\NotificationDll.pch"


!ELSEIF  "$(CFG)" == "NotificationDll - Win32 Unicode Debug"


"$(INTDIR)\ClientManager.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\NotificationDll.pch"


!ELSEIF  "$(CFG)" == "NotificationDll - Win32 Release MinSize"


"$(INTDIR)\ClientManager.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\NotificationDll.pch"


!ELSEIF  "$(CFG)" == "NotificationDll - Win32 Release MinDependency"


"$(INTDIR)\ClientManager.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\NotificationDll.pch"


!ELSEIF  "$(CFG)" == "NotificationDll - Win32 Unicode Release MinSize"


"$(INTDIR)\ClientManager.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\NotificationDll.pch"


!ELSEIF  "$(CFG)" == "NotificationDll - Win32 Unicode Release MinDependency"


"$(INTDIR)\ClientManager.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\NotificationDll.pch"


!ENDIF 

SOURCE=.\db.cpp

!IF  "$(CFG)" == "NotificationDll - Win32 Debug"


"$(INTDIR)\db.obj"	"$(INTDIR)\db.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\NotificationDll.pch"


!ELSEIF  "$(CFG)" == "NotificationDll - Win32 Unicode Debug"


"$(INTDIR)\db.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\NotificationDll.pch"


!ELSEIF  "$(CFG)" == "NotificationDll - Win32 Release MinSize"


"$(INTDIR)\db.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\NotificationDll.pch"


!ELSEIF  "$(CFG)" == "NotificationDll - Win32 Release MinDependency"


"$(INTDIR)\db.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\NotificationDll.pch"


!ELSEIF  "$(CFG)" == "NotificationDll - Win32 Unicode Release MinSize"


"$(INTDIR)\db.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\NotificationDll.pch"


!ELSEIF  "$(CFG)" == "NotificationDll - Win32 Unicode Release MinDependency"


"$(INTDIR)\db.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\NotificationDll.pch"


!ENDIF 

SOURCE=.\Loader.cpp

!IF  "$(CFG)" == "NotificationDll - Win32 Debug"


"$(INTDIR)\Loader.obj"	"$(INTDIR)\Loader.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\NotificationDll.pch"


!ELSEIF  "$(CFG)" == "NotificationDll - Win32 Unicode Debug"


"$(INTDIR)\Loader.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\NotificationDll.pch"


!ELSEIF  "$(CFG)" == "NotificationDll - Win32 Release MinSize"


"$(INTDIR)\Loader.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\NotificationDll.pch"


!ELSEIF  "$(CFG)" == "NotificationDll - Win32 Release MinDependency"


"$(INTDIR)\Loader.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\NotificationDll.pch"


!ELSEIF  "$(CFG)" == "NotificationDll - Win32 Unicode Release MinSize"


"$(INTDIR)\Loader.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\NotificationDll.pch"


!ELSEIF  "$(CFG)" == "NotificationDll - Win32 Unicode Release MinDependency"


"$(INTDIR)\Loader.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\NotificationDll.pch"


!ENDIF 

SOURCE=.\log.cpp

!IF  "$(CFG)" == "NotificationDll - Win32 Debug"


"$(INTDIR)\log.obj"	"$(INTDIR)\log.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\NotificationDll.pch"


!ELSEIF  "$(CFG)" == "NotificationDll - Win32 Unicode Debug"


"$(INTDIR)\log.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\NotificationDll.pch"


!ELSEIF  "$(CFG)" == "NotificationDll - Win32 Release MinSize"


"$(INTDIR)\log.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\NotificationDll.pch"


!ELSEIF  "$(CFG)" == "NotificationDll - Win32 Release MinDependency"


"$(INTDIR)\log.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\NotificationDll.pch"


!ELSEIF  "$(CFG)" == "NotificationDll - Win32 Unicode Release MinSize"


"$(INTDIR)\log.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\NotificationDll.pch"


!ELSEIF  "$(CFG)" == "NotificationDll - Win32 Unicode Release MinDependency"


"$(INTDIR)\log.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\NotificationDll.pch"


!ENDIF 

SOURCE=.\Manager.cpp

!IF  "$(CFG)" == "NotificationDll - Win32 Debug"


"$(INTDIR)\Manager.obj"	"$(INTDIR)\Manager.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\NotificationDll.pch"


!ELSEIF  "$(CFG)" == "NotificationDll - Win32 Unicode Debug"


"$(INTDIR)\Manager.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\NotificationDll.pch"


!ELSEIF  "$(CFG)" == "NotificationDll - Win32 Release MinSize"


"$(INTDIR)\Manager.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\NotificationDll.pch"


!ELSEIF  "$(CFG)" == "NotificationDll - Win32 Release MinDependency"


"$(INTDIR)\Manager.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\NotificationDll.pch"


!ELSEIF  "$(CFG)" == "NotificationDll - Win32 Unicode Release MinSize"


"$(INTDIR)\Manager.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\NotificationDll.pch"


!ELSEIF  "$(CFG)" == "NotificationDll - Win32 Unicode Release MinDependency"


"$(INTDIR)\Manager.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\NotificationDll.pch"


!ENDIF 

SOURCE=.\NotificationDll.cpp

!IF  "$(CFG)" == "NotificationDll - Win32 Debug"


"$(INTDIR)\NotificationDll.obj"	"$(INTDIR)\NotificationDll.sbr" : $(SOURCE) "$(INTDIR)" ".\NotificationDll.h" ".\NotificationDll_i.c" "$(INTDIR)\NotificationDll.pch"


!ELSEIF  "$(CFG)" == "NotificationDll - Win32 Unicode Debug"


"$(INTDIR)\NotificationDll.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\NotificationDll.pch"


!ELSEIF  "$(CFG)" == "NotificationDll - Win32 Release MinSize"


"$(INTDIR)\NotificationDll.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\NotificationDll.pch"


!ELSEIF  "$(CFG)" == "NotificationDll - Win32 Release MinDependency"


"$(INTDIR)\NotificationDll.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\NotificationDll.pch"


!ELSEIF  "$(CFG)" == "NotificationDll - Win32 Unicode Release MinSize"


"$(INTDIR)\NotificationDll.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\NotificationDll.pch"


!ELSEIF  "$(CFG)" == "NotificationDll - Win32 Unicode Release MinDependency"


"$(INTDIR)\NotificationDll.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\NotificationDll.pch"


!ENDIF 

SOURCE=.\NotificationDll.idl
MTL_SWITCHES=/tlb ".\NotificationDll.tlb" /h "NotificationDll.h" /iid "NotificationDll_i.c" /Oicf 

".\NotificationDll.tlb"	".\NotificationDll.h"	".\NotificationDll_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


SOURCE=.\NotificationDll.rc

"$(INTDIR)\NotificationDll.res" : $(SOURCE) "$(INTDIR)" ".\NotificationDll.tlb"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\Notify.cpp

!IF  "$(CFG)" == "NotificationDll - Win32 Debug"


"$(INTDIR)\Notify.obj"	"$(INTDIR)\Notify.sbr" : $(SOURCE) "$(INTDIR)" ".\NotificationDll.h" "$(INTDIR)\NotificationDll.pch"


!ELSEIF  "$(CFG)" == "NotificationDll - Win32 Unicode Debug"


"$(INTDIR)\Notify.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\NotificationDll.pch"


!ELSEIF  "$(CFG)" == "NotificationDll - Win32 Release MinSize"


"$(INTDIR)\Notify.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\NotificationDll.pch"


!ELSEIF  "$(CFG)" == "NotificationDll - Win32 Release MinDependency"


"$(INTDIR)\Notify.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\NotificationDll.pch"


!ELSEIF  "$(CFG)" == "NotificationDll - Win32 Unicode Release MinSize"


"$(INTDIR)\Notify.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\NotificationDll.pch"


!ELSEIF  "$(CFG)" == "NotificationDll - Win32 Unicode Release MinDependency"


"$(INTDIR)\Notify.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\NotificationDll.pch"


!ENDIF 

SOURCE=.\SeException.cpp

!IF  "$(CFG)" == "NotificationDll - Win32 Debug"


"$(INTDIR)\SeException.obj"	"$(INTDIR)\SeException.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\NotificationDll.pch"


!ELSEIF  "$(CFG)" == "NotificationDll - Win32 Unicode Debug"


"$(INTDIR)\SeException.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\NotificationDll.pch"


!ELSEIF  "$(CFG)" == "NotificationDll - Win32 Release MinSize"


"$(INTDIR)\SeException.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\NotificationDll.pch"


!ELSEIF  "$(CFG)" == "NotificationDll - Win32 Release MinDependency"


"$(INTDIR)\SeException.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\NotificationDll.pch"


!ELSEIF  "$(CFG)" == "NotificationDll - Win32 Unicode Release MinSize"


"$(INTDIR)\SeException.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\NotificationDll.pch"


!ELSEIF  "$(CFG)" == "NotificationDll - Win32 Unicode Release MinDependency"


"$(INTDIR)\SeException.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\NotificationDll.pch"


!ENDIF 

SOURCE=.\sender.cpp

!IF  "$(CFG)" == "NotificationDll - Win32 Debug"


"$(INTDIR)\sender.obj"	"$(INTDIR)\sender.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\NotificationDll.pch"


!ELSEIF  "$(CFG)" == "NotificationDll - Win32 Unicode Debug"


"$(INTDIR)\sender.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\NotificationDll.pch"


!ELSEIF  "$(CFG)" == "NotificationDll - Win32 Release MinSize"


"$(INTDIR)\sender.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\NotificationDll.pch"


!ELSEIF  "$(CFG)" == "NotificationDll - Win32 Release MinDependency"


"$(INTDIR)\sender.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\NotificationDll.pch"


!ELSEIF  "$(CFG)" == "NotificationDll - Win32 Unicode Release MinSize"


"$(INTDIR)\sender.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\NotificationDll.pch"


!ELSEIF  "$(CFG)" == "NotificationDll - Win32 Unicode Release MinDependency"


"$(INTDIR)\sender.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\NotificationDll.pch"


!ENDIF 

SOURCE=.\Server.cpp

!IF  "$(CFG)" == "NotificationDll - Win32 Debug"


"$(INTDIR)\Server.obj"	"$(INTDIR)\Server.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\NotificationDll.pch"


!ELSEIF  "$(CFG)" == "NotificationDll - Win32 Unicode Debug"


"$(INTDIR)\Server.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\NotificationDll.pch"


!ELSEIF  "$(CFG)" == "NotificationDll - Win32 Release MinSize"


"$(INTDIR)\Server.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\NotificationDll.pch"


!ELSEIF  "$(CFG)" == "NotificationDll - Win32 Release MinDependency"


"$(INTDIR)\Server.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\NotificationDll.pch"


!ELSEIF  "$(CFG)" == "NotificationDll - Win32 Unicode Release MinSize"


"$(INTDIR)\Server.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\NotificationDll.pch"


!ELSEIF  "$(CFG)" == "NotificationDll - Win32 Unicode Release MinDependency"


"$(INTDIR)\Server.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\NotificationDll.pch"


!ENDIF 

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "NotificationDll - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\NotificationDll.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\NotificationDll.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "NotificationDll - Win32 Unicode Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\NotificationDll.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\NotificationDll.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "NotificationDll - Win32 Release MinSize"

CPP_SWITCHES=/nologo /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_DLL" /Fp"$(INTDIR)\NotificationDll.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\NotificationDll.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "NotificationDll - Win32 Release MinDependency"

CPP_SWITCHES=/nologo /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /Fp"$(INTDIR)\NotificationDll.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\NotificationDll.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "NotificationDll - Win32 Unicode Release MinSize"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\NotificationDll.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\NotificationDll.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "NotificationDll - Win32 Unicode Release MinDependency"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\NotificationDll.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\NotificationDll.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\tools.cpp

!IF  "$(CFG)" == "NotificationDll - Win32 Debug"


"$(INTDIR)\tools.obj"	"$(INTDIR)\tools.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\NotificationDll.pch"


!ELSEIF  "$(CFG)" == "NotificationDll - Win32 Unicode Debug"


"$(INTDIR)\tools.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\NotificationDll.pch"


!ELSEIF  "$(CFG)" == "NotificationDll - Win32 Release MinSize"


"$(INTDIR)\tools.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\NotificationDll.pch"


!ELSEIF  "$(CFG)" == "NotificationDll - Win32 Release MinDependency"


"$(INTDIR)\tools.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\NotificationDll.pch"


!ELSEIF  "$(CFG)" == "NotificationDll - Win32 Unicode Release MinSize"


"$(INTDIR)\tools.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\NotificationDll.pch"


!ELSEIF  "$(CFG)" == "NotificationDll - Win32 Unicode Release MinDependency"


"$(INTDIR)\tools.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\NotificationDll.pch"


!ENDIF 

SOURCE=.\Worker.cpp

!IF  "$(CFG)" == "NotificationDll - Win32 Debug"


"$(INTDIR)\Worker.obj"	"$(INTDIR)\Worker.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\NotificationDll.pch"


!ELSEIF  "$(CFG)" == "NotificationDll - Win32 Unicode Debug"


"$(INTDIR)\Worker.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\NotificationDll.pch"


!ELSEIF  "$(CFG)" == "NotificationDll - Win32 Release MinSize"


"$(INTDIR)\Worker.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\NotificationDll.pch"


!ELSEIF  "$(CFG)" == "NotificationDll - Win32 Release MinDependency"


"$(INTDIR)\Worker.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\NotificationDll.pch"


!ELSEIF  "$(CFG)" == "NotificationDll - Win32 Unicode Release MinSize"


"$(INTDIR)\Worker.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\NotificationDll.pch"


!ELSEIF  "$(CFG)" == "NotificationDll - Win32 Unicode Release MinDependency"


"$(INTDIR)\Worker.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\NotificationDll.pch"


!ENDIF 


!ENDIF 

