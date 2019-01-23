# Microsoft Developer Studio Generated NMAKE File, Based on Montgomery.dsp
!IF "$(CFG)" == ""
CFG=Montgomery - Win32 Debug
!MESSAGE No configuration specified. Defaulting to Montgomery - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Montgomery - Win32 Release" && "$(CFG)" != "Montgomery - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Montgomery.mak" CFG="Montgomery - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Montgomery - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Montgomery - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "Montgomery - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\Montgomery.exe"


CLEAN :
	-@erase "$(INTDIR)\common.obj"
	-@erase "$(INTDIR)\mon.obj"
	-@erase "$(INTDIR)\Montgomery.obj"
	-@erase "$(INTDIR)\Montgomery.pch"
	-@erase "$(INTDIR)\Montgomery.res"
	-@erase "$(INTDIR)\MontgomeryDlg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\Montgomery.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\Montgomery.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\Montgomery.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Montgomery.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\Montgomery.pdb" /machine:I386 /out:"$(OUTDIR)\Montgomery.exe" 
LINK32_OBJS= \
	"$(INTDIR)\common.obj" \
	"$(INTDIR)\mon.obj" \
	"$(INTDIR)\Montgomery.obj" \
	"$(INTDIR)\MontgomeryDlg.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Montgomery.res"

"$(OUTDIR)\Montgomery.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Montgomery - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\Montgomery.exe"


CLEAN :
	-@erase "$(INTDIR)\common.obj"
	-@erase "$(INTDIR)\mon.obj"
	-@erase "$(INTDIR)\Montgomery.obj"
	-@erase "$(INTDIR)\Montgomery.pch"
	-@erase "$(INTDIR)\Montgomery.res"
	-@erase "$(INTDIR)\MontgomeryDlg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\Montgomery.exe"
	-@erase "$(OUTDIR)\Montgomery.ilk"
	-@erase "$(OUTDIR)\Montgomery.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\Montgomery.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\Montgomery.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Montgomery.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\Montgomery.pdb" /debug /machine:I386 /out:"$(OUTDIR)\Montgomery.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\common.obj" \
	"$(INTDIR)\mon.obj" \
	"$(INTDIR)\Montgomery.obj" \
	"$(INTDIR)\MontgomeryDlg.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Montgomery.res"

"$(OUTDIR)\Montgomery.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("Montgomery.dep")
!INCLUDE "Montgomery.dep"
!ELSE 
!MESSAGE Warning: cannot find "Montgomery.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "Montgomery - Win32 Release" || "$(CFG)" == "Montgomery - Win32 Debug"
SOURCE=.\common.cpp

"$(INTDIR)\common.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Montgomery.pch"


SOURCE=.\mon.cpp

"$(INTDIR)\mon.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Montgomery.pch"


SOURCE=.\Montgomery.cpp

"$(INTDIR)\Montgomery.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Montgomery.pch"


SOURCE=.\Montgomery.rc

"$(INTDIR)\Montgomery.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\MontgomeryDlg.cpp

"$(INTDIR)\MontgomeryDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Montgomery.pch"


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "Montgomery - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\Montgomery.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\Montgomery.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Montgomery - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\Montgomery.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\Montgomery.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

