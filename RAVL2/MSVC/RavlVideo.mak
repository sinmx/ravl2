


#--------------------------
# Compiler and flags etc
#--------------------------
CC = cl.exe

LD = lib.exe

INCLUDES =  /I "include\Win32" /I "include" /I "c:/Program Files/Microsoft Visual Studio 8/VC/ATLMFC/INCLUDE" /I "c:/Program Files/Microsoft Visual Studio 8/VC/INCLUDE" /I "c:/Program Files/Microsoft Visual Studio 8/VC/PlatformSDK/include" /I "c:/Program Files/Microsoft Visual Studio 8/SDK/v2.0/include" 

DEFINES = /D "NDEBUG" /D "_LIB" /D "VISUAL_CPP" /D "WIN32" /D "RAVL_USE_GTK2=1" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_SCL_SECURE=0" /D "_UNICODE" /D "UNICODE"


OPTFLAGS = /nologo /c /O2 /Ob1 /EHsc /MD /TP

DEBUGFLAGS = /nologo /c /Ob1 /EHsc /MD /TP

#-----------------------------------------------------------------------------
# OK lets define some of our output directories and define script to make them
#-----------------------------------------------------------------------------
DEBUGOBJDIR = C:\Build/win32/debug/obj/RavlVideo
DEBUGLIBDIR = C:\Build/win32/debug/lib

OPTOBJDIR = C:\Build/win32/opt/obj/RavlVideo
OPTLIBDIR = C:\Build/win32/opt/lib


opt:: setupRavlVideo  $(OPTOBJDIR)/ShotBoundHistInt.obj
	@echo -- making $(OPTLIBDIR)/RavlVideo.lib
	$(LD) /NOLOGO /out:$(OPTLIBDIR)/RavlVideo.lib $(OPTOBJDIR)/*.obj


debug:: setupRavlVideo  $(DEBUGOBJDIR)/ShotBoundHistInt.obj 
	@echo -- making $(DEBUGLIBDIR)/RavlVideo.lib
	$(LD) /NOLOGO /out:$(DEBUGLIBDIR)/RavlVideo.lib $(DEBUGOBJDIR)/*.obj

setupRavlVideo::
        echo --- creating dir for RavlVideo
        @if not exist "$(DEBUGOBJDIR)" mkdir "$(DEBUGOBJDIR)"
        @if not exist "$(DEBUGLIBDIR)" mkdir "$(DEBUGLIBDIR)"
        @if not exist "$(OPTOBJDIR)" mkdir "$(OPTOBJDIR)"
        @if not exist "$(OPTLIBDIR)" mkdir "$(OPTLIBDIR)"



$(OPTOBJDIR)/ShotBoundHistInt.obj: .././CompVision/ShotBoundary/ShotBoundHistInt.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ShotBoundHistInt.obj .././CompVision/ShotBoundary/ShotBoundHistInt.cc

$(DEBUGOBJDIR)/ShotBoundHistInt.obj: .././CompVision/ShotBoundary/ShotBoundHistInt.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ShotBoundHistInt.obj .././CompVision/ShotBoundary/ShotBoundHistInt.cc


