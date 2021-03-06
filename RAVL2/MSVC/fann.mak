


#--------------------------
# Compiler and flags etc
#--------------------------
CC = cl.exe

LD = lib.exe

INCLUDES =  /I "include\Win32" /I "include" /I "c:/Program Files/Microsoft Visual Studio 8/VC/ATLMFC/INCLUDE" /I "c:/Program Files/Microsoft Visual Studio 8/VC/INCLUDE" /I "c:/Program Files/Microsoft Visual Studio 8/VC/PlatformSDK/include" /I "c:/Program Files/Microsoft Visual Studio 8/SDK/v2.0/include" /I "C:\Program Files\Microsoft Platform SDK for Windows Server 2003 R2\Include" 

DEFINES = /D "NDEBUG" /D "_LIB" /D "VISUAL_CPP" /D "WIN32" /D "RAVL_USE_GTK2=1" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_SCL_SECURE=0" /D "_UNICODE" /D "UNICODE"


OPTFLAGS = /nologo /c /O2 /Ob1 /EHsc /MD /TP

DEBUGFLAGS = /nologo /c /Ob1 /EHsc /MD /TP

#-----------------------------------------------------------------------------
# OK lets define some of our output directories and define script to make them
#-----------------------------------------------------------------------------
DEBUGOBJDIR = C:\Build/win32/debug/obj/fann
DEBUGLIBDIR = C:\Build/win32/debug/lib

OPTOBJDIR = C:\Build/win32/opt/obj/fann
OPTLIBDIR = C:\Build/win32/opt/lib


opt:: setupfann  $(OPTOBJDIR)/floatfann.obj
	@echo -- making $(OPTLIBDIR)/fann.lib
	$(LD) /NOLOGO /out:$(OPTLIBDIR)/fann.lib $(OPTOBJDIR)/*.obj


debug:: setupfann  $(DEBUGOBJDIR)/floatfann.obj 
	@echo -- making $(DEBUGLIBDIR)/fann.lib
	$(LD) /NOLOGO /out:$(DEBUGLIBDIR)/fann.lib $(DEBUGOBJDIR)/*.obj

setupfann::
        echo --- creating dir for fann
        @if not exist "$(DEBUGOBJDIR)" mkdir "$(DEBUGOBJDIR)"
        @if not exist "$(DEBUGLIBDIR)" mkdir "$(DEBUGLIBDIR)"
        @if not exist "$(OPTOBJDIR)" mkdir "$(OPTOBJDIR)"
        @if not exist "$(OPTLIBDIR)" mkdir "$(OPTLIBDIR)"



$(OPTOBJDIR)/floatfann.obj: .././PatternRec/fann/floatfann.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/floatfann.obj .././PatternRec/fann/floatfann.c

$(DEBUGOBJDIR)/floatfann.obj: .././PatternRec/fann/floatfann.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/floatfann.obj .././PatternRec/fann/floatfann.c


