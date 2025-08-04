@echo off
setlocal enableextensions enabledelayedexpansion

set "NAME=magiciseverywhere"

:: (D)ebug, (R)elease
set CONFIG=D

set CFLAGS=/MP /Wall /std:c17 /fp:except- /fp:precise /nologo /I"src/precomp" ^
/wd4711 /wd4255 /wd4505 /wd4820 /wd4191 /wd5045

if %CONFIG%==D set CFLAGS=%CFLAGS% /GS /Zi /Od /D"_DEBUG" /MTd /RTCs
if %CONFIG%==R set CFLAGS=%CFLAGS% /GS- /O2 /Oi /Ot /Gy /MT /D"NDEBUG"

set LFLAGS=/INCREMENTAL:NO /NOLOGO /NOIMPLIB /NOEXP
if %CONFIG%==D SET LFLAGS=%LFLAGS% /DEBUG:FULL
if %CONFIG%==R SET LFLAGS=%LFLAGS%

if exist "%NAME%.exe" del "%NAME%.exe"

if not "%1"=="clean" goto clean_end
if exist "*.pch" del "*.pch"
if exist "*.obj" del "*.obj"
if exist "*.pdb" del "*.pdb"
if exist "precomp.lib" del "precomp.lib"
:clean_end

::
:: Precomp
::
if exist precomp.lib goto precomp_end
cl.exe ^
%CFLAGS% /c "src/precomp/precomp.c" ^
/Fo:"precomp.lib" /Fp:"precomp.pch" /Fd:"precomp.pdb" /Yc"precomp.h"
if errorlevel 1 goto error
:precomp_end

::
:: Exe
::
cl.exe ^
%CFLAGS% /Fp:"precomp.pch" /Fd:"precomp.pdb" /Fe:"%NAME%.exe" /Yu"precomp.h" "src\*.c" ^
/link ^
%LFLAGS% opengl32.lib user32.lib gdi32.lib glu32.lib fmod_vc.lib precomp.lib /subsystem:CONSOLE
if errorlevel 1 goto error

if exist *.obj del *.obj

if "%1"=="run" if exist "%NAME%.exe" "%NAME%.exe"

goto end

:error

if exist *.obj del *.obj

echo ---------------
echo error
echo ---------------

:end
