# Microsoft Developer Studio Generated NMAKE File, Based on Generator.dsp
!IF "$(CFG)" == ""
CFG=Generator - Win32 Debug
!MESSAGE No configuration specified. Defaulting to Generator - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Generator - Win32 Release" && "$(CFG)" != "Generator - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Generator.mak" CFG="Generator - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Generator - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Generator - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "Generator - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\Generator.exe" "$(OUTDIR)\Generator.bsc"


CLEAN :
	-@erase "$(INTDIR)\Generator.obj"
	-@erase "$(INTDIR)\Generator.pch"
	-@erase "$(INTDIR)\Generator.res"
	-@erase "$(INTDIR)\Generator.sbr"
	-@erase "$(INTDIR)\GeneratorDlg.obj"
	-@erase "$(INTDIR)\GeneratorDlg.sbr"
	-@erase "$(INTDIR)\GeneratorIniFile.obj"
	-@erase "$(INTDIR)\GeneratorIniFile.sbr"
	-@erase "$(INTDIR)\Hlinkctl.obj"
	-@erase "$(INTDIR)\Hlinkctl.sbr"
	-@erase "$(INTDIR)\lav_stas.obj"
	-@erase "$(INTDIR)\lav_stas.sbr"
	-@erase "$(INTDIR)\ModClassListDlg.obj"
	-@erase "$(INTDIR)\ModClassListDlg.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\Generator.bsc"
	-@erase "$(OUTDIR)\Generator.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G3 /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\Generator.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x419 /fo"$(INTDIR)\Generator.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Generator.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\Generator.sbr" \
	"$(INTDIR)\GeneratorDlg.sbr" \
	"$(INTDIR)\GeneratorIniFile.sbr" \
	"$(INTDIR)\Hlinkctl.sbr" \
	"$(INTDIR)\lav_stas.sbr" \
	"$(INTDIR)\ModClassListDlg.sbr" \
	"$(INTDIR)\StdAfx.sbr"

"$(OUTDIR)\Generator.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\Generator.pdb" /machine:I386 /out:"$(OUTDIR)\Generator.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Generator.obj" \
	"$(INTDIR)\GeneratorDlg.obj" \
	"$(INTDIR)\GeneratorIniFile.obj" \
	"$(INTDIR)\Hlinkctl.obj" \
	"$(INTDIR)\lav_stas.obj" \
	"$(INTDIR)\ModClassListDlg.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Generator.res"

"$(OUTDIR)\Generator.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Generator - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\Generator.exe" "$(OUTDIR)\Generator.bsc"


CLEAN :
	-@erase "$(INTDIR)\Generator.obj"
	-@erase "$(INTDIR)\Generator.pch"
	-@erase "$(INTDIR)\Generator.res"
	-@erase "$(INTDIR)\Generator.sbr"
	-@erase "$(INTDIR)\GeneratorDlg.obj"
	-@erase "$(INTDIR)\GeneratorDlg.sbr"
	-@erase "$(INTDIR)\GeneratorIniFile.obj"
	-@erase "$(INTDIR)\GeneratorIniFile.sbr"
	-@erase "$(INTDIR)\Hlinkctl.obj"
	-@erase "$(INTDIR)\Hlinkctl.sbr"
	-@erase "$(INTDIR)\lav_stas.obj"
	-@erase "$(INTDIR)\lav_stas.sbr"
	-@erase "$(INTDIR)\ModClassListDlg.obj"
	-@erase "$(INTDIR)\ModClassListDlg.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\Generator.bsc"
	-@erase "$(OUTDIR)\Generator.exe"
	-@erase "$(OUTDIR)\Generator.ilk"
	-@erase "$(OUTDIR)\Generator.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\Generator.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x419 /fo"$(INTDIR)\Generator.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Generator.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\Generator.sbr" \
	"$(INTDIR)\GeneratorDlg.sbr" \
	"$(INTDIR)\GeneratorIniFile.sbr" \
	"$(INTDIR)\Hlinkctl.sbr" \
	"$(INTDIR)\lav_stas.sbr" \
	"$(INTDIR)\ModClassListDlg.sbr" \
	"$(INTDIR)\StdAfx.sbr"

"$(OUTDIR)\Generator.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\Generator.pdb" /debug /machine:I386 /out:"$(OUTDIR)\Generator.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\Generator.obj" \
	"$(INTDIR)\GeneratorDlg.obj" \
	"$(INTDIR)\GeneratorIniFile.obj" \
	"$(INTDIR)\Hlinkctl.obj" \
	"$(INTDIR)\lav_stas.obj" \
	"$(INTDIR)\ModClassListDlg.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Generator.res"

"$(OUTDIR)\Generator.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("Generator.dep")
!INCLUDE "Generator.dep"
!ELSE 
!MESSAGE Warning: cannot find "Generator.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "Generator - Win32 Release" || "$(CFG)" == "Generator - Win32 Debug"
SOURCE=.\Generator.cpp

"$(INTDIR)\Generator.obj"	"$(INTDIR)\Generator.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Generator.pch"


SOURCE=.\Generator.rc

"$(INTDIR)\Generator.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\GeneratorDlg.cpp

"$(INTDIR)\GeneratorDlg.obj"	"$(INTDIR)\GeneratorDlg.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Generator.pch"


SOURCE=.\GeneratorIniFile.cpp

"$(INTDIR)\GeneratorIniFile.obj"	"$(INTDIR)\GeneratorIniFile.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Generator.pch"


SOURCE=.\HLINKCTRL\Hlinkctl.cpp

"$(INTDIR)\Hlinkctl.obj"	"$(INTDIR)\Hlinkctl.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Generator.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\lav_stas.cpp

"$(INTDIR)\lav_stas.obj"	"$(INTDIR)\lav_stas.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Generator.pch"


SOURCE=.\ModClassListDlg.cpp

"$(INTDIR)\ModClassListDlg.obj"	"$(INTDIR)\ModClassListDlg.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Generator.pch"


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "Generator - Win32 Release"

CPP_SWITCHES=/nologo /G3 /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\Generator.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\Generator.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Generator - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\Generator.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\Generator.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

