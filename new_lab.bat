@echo off
setlocal

set "ROOT=%~dp0"

if "%~1"=="" (
    echo Usage: new_lab.bat ^<number^>
    echo Example: new_lab.bat 2
    exit /b 1
)

set "N=%~1"
set "LABDIR=%ROOT%lab%N%"

if exist "%LABDIR%" (
    echo [new_lab] ERROR: %LABDIR% already exists.
    exit /b 1
)

echo [new_lab] Creating lab%N%\...
mkdir "%LABDIR%"

copy /y "%ROOT%tools\mpi_skeleton.cpp"   "%LABDIR%\lab%N%.cpp"  >nul
copy /y "%ROOT%tools\msmpi\bin\msmpi.dll" "%LABDIR%\msmpi.dll"   >nul
copy /y "%ROOT%tools\template_build.bat"  "%LABDIR%\build.bat"    >nul
copy /y "%ROOT%tools\template_ran.bat"    "%LABDIR%\ran.bat"      >nul

echo [new_lab] Done. Files created:
echo   lab%N%\lab%N%.cpp
echo   lab%N%\msmpi.dll
echo   lab%N%\build.bat
echo   lab%N%\ran.bat
echo.
echo Next steps:
echo   cd lab%N%
echo   .\build.bat
echo   .\ran.bat
