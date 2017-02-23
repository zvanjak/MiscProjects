# Microsoft Developer Studio Generated NMAKE File, Format Version 40001
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

!IF "$(CFG)" == ""
CFG=jezpro1 - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to jezpro1 - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "jezpro1 - Win32 Release" && "$(CFG)" !=\
 "jezpro1 - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "JEZPRO1.MAK" CFG="jezpro1 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "jezpro1 - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "jezpro1 - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 
################################################################################
# Begin Project
# PROP Target_Last_Scanned "jezpro1 - Win32 Debug"
RSC=rc.exe
CPP=cl.exe

!IF  "$(CFG)" == "jezpro1 - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
OUTDIR=.
INTDIR=.

ALL : "$(OUTDIR)\JEZPRO1.exe"

CLEAN : 
	-@erase ".\JEZPRO1.exe"
	-@erase ".\jezsyn.obj"
	-@erase ".\jezmain.obj"
	-@erase ".\jezlex.obj"

# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /YX /c
CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE"\
 /Fp"JEZPRO1.pch" /YX /c 
# ADD BASE RSC /l 0x41a /d "NDEBUG"
# ADD RSC /l 0x41a /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/JEZPRO1.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:console /incremental:no\
 /pdb:"$(OUTDIR)/JEZPRO1.pdb" /machine:I386 /out:"$(OUTDIR)/JEZPRO1.exe" 
LINK32_OBJS= \
	"$(INTDIR)/jezsyn.obj" \
	"$(INTDIR)/jezmain.obj" \
	"$(INTDIR)/jezlex.obj"

"$(OUTDIR)\JEZPRO1.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "jezpro1 - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
OUTDIR=.
INTDIR=.

ALL : "$(OUTDIR)\JEZPRO1.exe"

CLEAN : 
	-@erase ".\vc40.pdb"
	-@erase ".\vc40.idb"
	-@erase ".\JEZPRO1.exe"
	-@erase ".\jezsyn.obj"
	-@erase ".\jezmain.obj"
	-@erase ".\jezlex.obj"
	-@erase ".\JEZPRO1.ilk"
	-@erase ".\JEZPRO1.pdb"

# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /YX /c
CPP_PROJ=/nologo /MLd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE"\
 /Fp"JEZPRO1.pch" /YX /c 
# ADD BASE RSC /l 0x41a /d "_DEBUG"
# ADD RSC /l 0x41a /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/JEZPRO1.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:console /incremental:yes\
 /pdb:"$(OUTDIR)/JEZPRO1.pdb" /debug /machine:I386 /out:"$(OUTDIR)/JEZPRO1.exe" 
LINK32_OBJS= \
	"$(INTDIR)/jezsyn.obj" \
	"$(INTDIR)/jezmain.obj" \
	"$(INTDIR)/jezlex.obj"

"$(OUTDIR)\JEZPRO1.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx.obj:
   $(CPP) $(CPP_PROJ) $<  

.c.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cpp.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cxx.sbr:
   $(CPP) $(CPP_PROJ) $<  

################################################################################
# Begin Target

# Name "jezpro1 - Win32 Release"
# Name "jezpro1 - Win32 Debug"

!IF  "$(CFG)" == "jezpro1 - Win32 Release"

!ELSEIF  "$(CFG)" == "jezpro1 - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\jezmain.c
DEP_CPP_JEZMA=\
	".\jezpro.h"\
	

"$(INTDIR)\jezmain.obj" : $(SOURCE) $(DEP_CPP_JEZMA) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\jezlex.c
DEP_CPP_JEZLE=\
	".\jezpro.h"\
	

"$(INTDIR)\jezlex.obj" : $(SOURCE) $(DEP_CPP_JEZLE) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\jezsyn.c
DEP_CPP_JEZSY=\
	".\jezpro.h"\
	

"$(INTDIR)\jezsyn.obj" : $(SOURCE) $(DEP_CPP_JEZSY) "$(INTDIR)"


# End Source File
# End Target
# End Project
################################################################################
