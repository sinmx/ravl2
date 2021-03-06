


#--------------------------
# Compiler and flags etc
#--------------------------
CC = cl.exe

LD = lib.exe

INCLUDES =  /I "include\Win32" /I "include" /I "c:/Program Files/Microsoft Visual Studio 8/VC/ATLMFC/INCLUDE" /I "c:/Program Files/Microsoft Visual Studio 8/VC/INCLUDE" /I "c:/Program Files/Microsoft Visual Studio 8/VC/PlatformSDK/include" /I "c:/Program Files/Microsoft Visual Studio 8/SDK/v2.0/include" /I "C:\GTKWIN32\include" 

DEFINES = /D "NDEBUG" /D "_LIB" /D "VISUAL_CPP" /D "WIN32" /D "RAVL_USE_GTK2=1" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_SCL_SECURE=0" /D "_UNICODE" /D "UNICODE"


OPTFLAGS = /nologo /c /O2 /Ob1 /EHsc /MD /TP

DEBUGFLAGS = /nologo /c /Ob1 /EHsc /MD /TP

#-----------------------------------------------------------------------------
# OK lets define some of our output directories and define script to make them
#-----------------------------------------------------------------------------
DEBUGOBJDIR = C:\Build/win32/debug/obj/RavlZLib
DEBUGLIBDIR = C:\Build/win32/debug/lib

OPTOBJDIR = C:\Build/win32/opt/obj/RavlZLib
OPTLIBDIR = C:\Build/win32/opt/lib


opt:: setupRavlZLib  $(OPTOBJDIR)/Compress.obj
	@echo -- making $(OPTLIBDIR)/RavlZLib.lib
	$(LD) /NOLOGO /out:$(OPTLIBDIR)/RavlZLib.lib $(OPTOBJDIR)/*.obj


debug:: setupRavlZLib  $(DEBUGOBJDIR)/Compress.obj 
	@echo -- making $(DEBUGLIBDIR)/RavlZLib.lib
	$(LD) /NOLOGO /out:$(DEBUGLIBDIR)/RavlZLib.lib $(DEBUGOBJDIR)/*.obj

setupRavlZLib::
        echo --- creating dir for RavlZLib
        @if not exist "$(DEBUGOBJDIR)" mkdir "$(DEBUGOBJDIR)"
        @if not exist "$(DEBUGLIBDIR)" mkdir "$(DEBUGLIBDIR)"
        @if not exist "$(OPTOBJDIR)" mkdir "$(OPTOBJDIR)"
        @if not exist "$(OPTLIBDIR)" mkdir "$(OPTLIBDIR)"



$(OPTOBJDIR)/Compress.obj: .././OS/Compress/Compress.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Compress.obj .././OS/Compress/Compress.cc

$(DEBUGOBJDIR)/Compress.obj: .././OS/Compress/Compress.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Compress.obj .././OS/Compress/Compress.cc


