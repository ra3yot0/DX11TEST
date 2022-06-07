@echo off
setlocal enabledelayedexpansion

set kCL="C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.32.31326\bin\Hostx64\x64\cl.exe"
set kLIB="C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.32.31326\bin\Hostx64\x64\lib.exe"
set kOptInclude=^
/I "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.32.31326\include" ^
/I "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.32.31326\Auxiliary" ^
/I "C:\Program Files (x86)\Windows Kits\10\Include\10.0.22000.0\ucrt" ^
/I "C:\Program Files (x86)\Windows Kits\10\Include\10.0.22000.0\um" ^
/I "C:\Program Files (x86)\Windows Kits\10\Include\10.0.22000.0\shared" ^
/I "C:\Program Files (x86)\Windows Kits\10\Include\10.0.22000.0\winrt" ^
/I "C:\Program Files (x86)\Windows Kits\10\Include\10.0.22000.0\cppwinrt"
set kOptLibrary=/link ^
/LIBPATH:"C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.32.31326\lib\x64" ^
/LIBPATH:"C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.32.31326\Auxiliary" ^
/LIBPATH:"C:\Program Files (x86)\Windows Kits\10\Lib\10.0.22000.0\ucrt\x64" ^
/LIBPATH:"C:\Program Files (x86)\Windows Kits\10\Lib\10.0.22000.0\um\x64" ^
/LIBPATH:"."

set kDelimiter= 
set pathFiles=
if exist "..\src\*.cpp" (
    for /f "tokens=* delims=" %%x in ('dir ..\src\*.cpp /S /B') do (
        set pathFiles=!pathFiles!%%x!kDelimiter!
    )
)

if "!pathFiles!"=="" (
    echo There is no file that should be compiled.
    exit /B
)

!kCL! /EHsc /Fe:main.exe !kOptInclude! !pathFiles! !kOptLibrary!
del *.obj