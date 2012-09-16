# Microsoft Developer Studio Generated NMAKE File, Based on NotificationService.dsp
!IF "$(CFG)" == ""
CFG=NotificationService - Win32 Debug
!MESSAGE No configuration specified. Defaulting to NotificationService - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "NotificationService - Win32 Debug" && "$(CFG)" != "NotificationService - Win32 Unicode Debug" && "$(CFG)" != "NotificationService - Win32 Release MinSize" && "$(CFG)" != "NotificationService - Win32 Release MinDependency" && "$(CFG)" != "NotificationService - Win32 Unicode Release MinSize" && "$(CFG)" != "NotificationService - Win32 Unicode Release MinDependency"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "NotificationService.mak" CFG="NotificationService - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "NotificationService - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "NotificationService - Win32 Unicode Debug" (based on "Win32 (x86) Application")
!MESSAGE "NotificationService - Win32 Release MinSize" (based on "Win32 (x86) Application")
!MESSAGE "NotificationService - Win32 Release MinDependency" (based on "Win32 (x86) Application")
!MESSAGE "NotificationService - Win32 Unicode Release MinSize" (based on "Win32 (x86) Application")
!MESSAGE "NotificationService - Win32 Unicode Release MinDependency" (based on "Win32 (x86) Application")
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

!IF  "$(CFG)" == "NotificationService - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\NotificationService.exe" ".\NotificationService.tlb" ".\NotificationService.h" ".\NotificationService_i.c" ".\Debug\regsvr32.trg"

!ELSE 

ALL : "$(OUTDIR)\NotificationService.exe" ".\NotificationService.tlb" ".\NotificationService.h" ".\NotificationService_i.c" ".\Debug\regsvr32.trg"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\NotificationService.obj"
	-@erase "$(INTDIR)\NotificationService.pch"
	-@erase "$(INTDIR)\NotificationService.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\NotificationService.exe"
	-@erase "$(OUTDIR)\NotificationService.ilk"
	-@erase "$(OUTDIR)\NotificationService.map"
	-@erase "$(OUTDIR)\NotificationService.pdb"
	-@erase ".\NotificationService.h"
	-@erase ".\NotificationService.tlb"
	-@erase ".\NotificationService_i.c"
	-@erase ".\Debug\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\NotificationService.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\NotificationService.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\NotificationService.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\NotificationService.pdb" /map:"$(INTDIR)\NotificationService.map" /debug /machine:I386 /out:"$(OUTDIR)\NotificationService.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\NotificationService.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\NotificationService.res"

"$(OUTDIR)\NotificationService.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Debug
TargetPath=.\Debug\NotificationService.exe
InputPath=.\Debug\NotificationService.exe
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	"$(TargetPath)" /RegServer 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	echo Server registration done! 
<< 
	

!ELSEIF  "$(CFG)" == "NotificationService - Win32 Unicode Debug"

OUTDIR=.\DebugU
INTDIR=.\DebugU
# Begin Custom Macros
OutDir=.\DebugU
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\NotificationService.exe" ".\NotificationService.tlb" ".\NotificationService.h" ".\NotificationService_i.c" ".\DebugU\regsvr32.trg"

!ELSE 

ALL : "$(OUTDIR)\NotificationService.exe" ".\NotificationService.tlb" ".\NotificationService.h" ".\NotificationService_i.c" ".\DebugU\regsvr32.trg"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\NotificationService.obj"
	-@erase "$(INTDIR)\NotificationService.pch"
	-@erase "$(INTDIR)\NotificationService.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\NotificationService.exe"
	-@erase "$(OUTDIR)\NotificationService.ilk"
	-@erase "$(OUTDIR)\NotificationService.pdb"
	-@erase ".\NotificationService.h"
	-@erase ".\NotificationService.tlb"
	-@erase ".\NotificationService_i.c"
	-@erase ".\DebugU\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_UNICODE" /Fp"$(INTDIR)\NotificationService.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\NotificationService.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\NotificationService.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /entry:"wWinMainCRTStartup" /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\NotificationService.pdb" /debug /machine:I386 /out:"$(OUTDIR)\NotificationService.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\NotificationService.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\NotificationService.res"

"$(OUTDIR)\NotificationService.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\DebugU
TargetPath=.\DebugU\NotificationService.exe
InputPath=.\DebugU\NotificationService.exe
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
	

!ELSEIF  "$(CFG)" == "NotificationService - Win32 Release MinSize"

OUTDIR=.\ReleaseMinSize
INTDIR=.\ReleaseMinSize
# Begin Custom Macros
OutDir=.\ReleaseMinSize
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\NotificationService.exe" ".\NotificationService.tlb" ".\NotificationService.h" ".\NotificationService_i.c" ".\ReleaseMinSize\regsvr32.trg"

!ELSE 

ALL : "$(OUTDIR)\NotificationService.exe" ".\NotificationService.tlb" ".\NotificationService.h" ".\NotificationService_i.c" ".\ReleaseMinSize\regsvr32.trg"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\NotificationService.obj"
	-@erase "$(INTDIR)\NotificationService.pch"
	-@erase "$(INTDIR)\NotificationService.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\NotificationService.exe"
	-@erase ".\NotificationService.h"
	-@erase ".\NotificationService.tlb"
	-@erase ".\NotificationService_i.c"
	-@erase ".\ReleaseMinSize\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_ATL_DLL" /Fp"$(INTDIR)\NotificationService.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\NotificationService.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\NotificationService.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\NotificationService.pdb" /machine:I386 /out:"$(OUTDIR)\NotificationService.exe" 
LINK32_OBJS= \
	"$(INTDIR)\NotificationService.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\NotificationService.res"

"$(OUTDIR)\NotificationService.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseMinSize
TargetPath=.\ReleaseMinSize\NotificationService.exe
InputPath=.\ReleaseMinSize\NotificationService.exe
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	"$(TargetPath)" /RegServer 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	echo Server registration done! 
<< 
	

!ELSEIF  "$(CFG)" == "NotificationService - Win32 Release MinDependency"

OUTDIR=.\ReleaseMinDependency
INTDIR=.\ReleaseMinDependency
# Begin Custom Macros
OutDir=.\ReleaseMinDependency
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\NotificationService.exe" ".\NotificationService.tlb" ".\NotificationService.h" ".\NotificationService_i.c" ".\ReleaseMinDependency\regsvr32.trg"

!ELSE 

ALL : "$(OUTDIR)\NotificationService.exe" ".\NotificationService.tlb" ".\NotificationService.h" ".\NotificationService_i.c" ".\ReleaseMinDependency\regsvr32.trg"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\NotificationService.obj"
	-@erase "$(INTDIR)\NotificationService.pch"
	-@erase "$(INTDIR)\NotificationService.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\NotificationService.exe"
	-@erase ".\NotificationService.h"
	-@erase ".\NotificationService.tlb"
	-@erase ".\NotificationService_i.c"
	-@erase ".\ReleaseMinDependency\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_ATL_STATIC_REGISTRY" /Fp"$(INTDIR)\NotificationService.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\NotificationService.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\NotificationService.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\NotificationService.pdb" /machine:I386 /out:"$(OUTDIR)\NotificationService.exe" 
LINK32_OBJS= \
	"$(INTDIR)\NotificationService.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\NotificationService.res"

"$(OUTDIR)\NotificationService.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseMinDependency
TargetPath=.\ReleaseMinDependency\NotificationService.exe
InputPath=.\ReleaseMinDependency\NotificationService.exe
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	"$(TargetPath)" /RegServer 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	echo Server registration done! 
<< 
	

!ELSEIF  "$(CFG)" == "NotificationService - Win32 Unicode Release MinSize"

OUTDIR=.\ReleaseUMinSize
INTDIR=.\ReleaseUMinSize
# Begin Custom Macros
OutDir=.\ReleaseUMinSize
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\NotificationService.exe" ".\NotificationService.tlb" ".\NotificationService.h" ".\NotificationService_i.c" ".\ReleaseUMinSize\regsvr32.trg"

!ELSE 

ALL : "$(OUTDIR)\NotificationService.exe" ".\NotificationService.tlb" ".\NotificationService.h" ".\NotificationService_i.c" ".\ReleaseUMinSize\regsvr32.trg"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\NotificationService.obj"
	-@erase "$(INTDIR)\NotificationService.pch"
	-@erase "$(INTDIR)\NotificationService.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\NotificationService.exe"
	-@erase ".\NotificationService.h"
	-@erase ".\NotificationService.tlb"
	-@erase ".\NotificationService_i.c"
	-@erase ".\ReleaseUMinSize\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_UNICODE" /D "_ATL_DLL" /Fp"$(INTDIR)\NotificationService.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\NotificationService.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\NotificationService.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\NotificationService.pdb" /machine:I386 /out:"$(OUTDIR)\NotificationService.exe" 
LINK32_OBJS= \
	"$(INTDIR)\NotificationService.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\NotificationService.res"

"$(OUTDIR)\NotificationService.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseUMinSize
TargetPath=.\ReleaseUMinSize\NotificationService.exe
InputPath=.\ReleaseUMinSize\NotificationService.exe
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
	

!ELSEIF  "$(CFG)" == "NotificationService - Win32 Unicode Release MinDependency"

OUTDIR=.\ReleaseUMinDependency
INTDIR=.\ReleaseUMinDependency
# Begin Custom Macros
OutDir=.\ReleaseUMinDependency
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\NotificationService.exe" ".\NotificationService.tlb" ".\NotificationService.h" ".\NotificationService_i.c" ".\ReleaseUMinDependency\regsvr32.trg"

!ELSE 

ALL : "$(OUTDIR)\NotificationService.exe" ".\NotificationService.tlb" ".\NotificationService.h" ".\NotificationService_i.c" ".\ReleaseUMinDependency\regsvr32.trg"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\NotificationService.obj"
	-@erase "$(INTDIR)\NotificationService.pch"
	-@erase "$(INTDIR)\NotificationService.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\NotificationService.exe"
	-@erase ".\NotificationService.h"
	-@erase ".\NotificationService.tlb"
	-@erase ".\NotificationService_i.c"
	-@erase ".\ReleaseUMinDependency\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /Fp"$(INTDIR)\NotificationService.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\NotificationService.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\NotificationService.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\NotificationService.pdb" /machine:I386 /out:"$(OUTDIR)\NotificationService.exe" 
LINK32_OBJS= \
	"$(INTDIR)\NotificationService.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\NotificationService.res"

"$(OUTDIR)\NotificationService.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseUMinDependency
TargetPath=.\ReleaseUMinDependency\NotificationService.exe
InputPath=.\ReleaseUMinDependency\NotificationService.exe
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
!IF EXISTS("NotificationService.dep")
!INCLUDE "NotificationService.dep"
!ELSE 
!MESSAGE Warning: cannot find "NotificationService.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "NotificationService - Win32 Debug" || "$(CFG)" == "NotificationService - Win32 Unicode Debug" || "$(CFG)" == "NotificationService - Win32 Release MinSize" || "$(CFG)" == "NotificationService - Win32 Release MinDependency" || "$(CFG)" == "NotificationService - Win32 Unicode Release MinSize" || "$(CFG)" == "NotificationService - Win32 Unicode Release MinDependency"
SOURCE=.\NotificationService.cpp

"$(INTDIR)\NotificationService.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\NotificationService.pch"


SOURCE=.\NotificationService.idl
MTL_SWITCHES=/tlb ".\NotificationService.tlb" /h "NotificationService.h" /iid "NotificationService_i.c" /Oicf 

".\NotificationService.tlb"	".\NotificationService.h"	".\NotificationService_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


SOURCE=.\NotificationService.rc

"$(INTDIR)\NotificationService.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "NotificationService - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\NotificationService.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\NotificationService.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "NotificationService - Win32 Unicode Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_UNICODE" /Fp"$(INTDIR)\NotificationService.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\NotificationService.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "NotificationService - Win32 Release MinSize"

CPP_SWITCHES=/nologo /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_ATL_DLL" /Fp"$(INTDIR)\NotificationService.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\NotificationService.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "NotificationService - Win32 Release MinDependency"

CPP_SWITCHES=/nologo /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_ATL_STATIC_REGISTRY" /Fp"$(INTDIR)\NotificationService.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\NotificationService.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "NotificationService - Win32 Unicode Release MinSize"

CPP_SWITCHES=/nologo /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_UNICODE" /D "_ATL_DLL" /Fp"$(INTDIR)\NotificationService.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\NotificationService.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "NotificationService - Win32 Unicode Release MinDependency"

CPP_SWITCHES=/nologo /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /Fp"$(INTDIR)\NotificationService.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\NotificationService.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

!IF  "$(CFG)" == "NotificationService - Win32 Debug"

!ELSEIF  "$(CFG)" == "NotificationService - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "NotificationService - Win32 Release MinSize"

!ELSEIF  "$(CFG)" == "NotificationService - Win32 Release MinDependency"

!ELSEIF  "$(CFG)" == "NotificationService - Win32 Unicode Release MinSize"

!ELSEIF  "$(CFG)" == "NotificationService - Win32 Unicode Release MinDependency"

!ENDIF 


!ENDIF 

