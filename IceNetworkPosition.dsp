# Microsoft Developer Studio Project File - Name="IceNetworkPosition" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=IceNetworkPosition - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "IceNetworkPosition.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "IceNetworkPosition.mak" CFG="IceNetworkPosition - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "IceNetworkPosition - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "IceNetworkPosition - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName "IceNetworkPosition"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "IceNetworkPosition - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ""
# PROP Intermediate_Dir ""
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I "\n4\pkg\MrServers\MrVista\include" /D "MFCRelease" /D "NDEBUG" /D WINVER=0x500 /D _WIN32_WINNT=0x500 /D "WIN32" /D "_AFXDLL" /D "_WINDOWS" /D "WinNT400" /D "MSVC60" /D AFX_NOVTABLE= /D PARC_MODULE_NAME=IceNetworkPosition /D "_RWTOOLSDLL" /D "_UNICODE" /D "UNICODE" /D "O_DLL_PCLASS_ONLY" /D "ICEIDEAFUNCTORS_EXPORTS" /D "BUILD_IceNetworkPosition" /D "_WINDLL" /D "CSA_HAS_DLL" /D "ACE_HAS_DLL" /D "BUILD_IceScanFunctors" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o"\n4\pkg\MrServers\MrVista\Ice\Ice.bsc"
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /machine:I386 /out:"\n4\x86\prod\bin\IceNetworkPosition.evp"

!ELSEIF  "$(CFG)" == "IceNetworkPosition - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "\n4\x86\prod\bin"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "\n4_opensource\STLport\stlport" /I "\n4\pkg" /I "\n4\tool" /I "\n4_prod\x86\prod\include" /I "\n4\x86\delivery\include" /I "\n4_deli_$(arch_num_version)\x86\delivery\include" /I "\n4\x86\extsw\MedCom\include" /I "\SWF_extern\SDK\include" /I "\n4\pkg\MrServers\MrVista\include" /I "\n4\pkg\MrServers\MrVista\Ice\IceIdeaFunctors\IceNetworkPosition" /I "\n4\x86\extsw\MedCom\versant\vds605/h" /I "\n4\x86\extsw\include" /D "MFCDebug" /D "_DEBUG" /D "RWDEBUG" /D WINVER=0x500 /D _WIN32_WINNT=0x500 /D "WIN32" /D "_WINDOWS" /D "WinNT400" /D "MSVC60" /D AFX_NOVTABLE= /D PARC_MODULE_NAME=IceNetworkPosition /D "_RWTOOLSDLL" /D "_UNICODE" /D "UNICODE" /D "O_DLL_PCLASS_ONLY" /D "ICEIDEAFUNCTORS_EXPORTS" /D "BUILD_IceNetworkPosition" /D "CSA_HAS_DLL" /D "ACE_HAS_DLL" /D "BUILD_IceScanFunctors" /FR /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o"\n4\pkg\MrServers\MrVista\Ice\IceIdeaFunctors\IceNetworkPosition\x86\IceNetworkPosition.bsc"
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 rwtoold.lib aced.lib liboscfe.lib mscchk.lib mscvcch.lib i18nd.lib IceAlgosd.lib IceBasicd.lib IceImageReconFunctorsd.lib IceUtilsd.lib MrParcd.lib IceScanFunctors.lib MrEvaTransformCoordinatesd.lib MrBasicObjectsd.lib libMES4BVd.lib /nologo /dll /debug /machine:I386 /out:"\n4\x86\prod\bin\IceNetworkPositiond.dll" /pdbtype:sept /libpath:"\n4_prod\x86\prod\lib" /libpath:"\n4\x86\extsw\MedCom\lib" /libpath:"\n4_deli_$(arch_num_version)\x86\delivery\lib" /libpath:"\SWF_extern\SDK\lib" /libpath:""/n4/x86/extsw/MedCom/lib"" /libpath:""/n4_deli_$(arch_num_version)/x86/delivery/lib""
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "IceNetworkPosition - Win32 Release"
# Name "IceNetworkPosition - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\NetworkPositionConfigurator.cpp
# End Source File
# Begin Source File

SOURCE=.\NetworkPositionFunctor.cpp
# End Source File
# Begin Source File

SOURCE=.\NetworkPositionObjectMap.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\NetworkPositionConfigurator.h
# End Source File
# Begin Source File

SOURCE=.\NetworkPositionData.h
# End Source File
# Begin Source File

SOURCE=.\NetworkPositionFunctor.h
# End Source File
# End Group
# Begin Group "XProtocols"

# PROP Default_Filter "evp"
# Begin Source File

SOURCE=..\..\..\Config\IceConfigurators\IceProgramNetworkPosition.evp
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe;txt;mk;imk;trs"
# Begin Source File

SOURCE=.\Makefile.imk
# End Source File
# Begin Source File

SOURCE=.\makefile.trs
# End Source File
# End Group
# End Target
# End Project
