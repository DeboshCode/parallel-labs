@echo off
setlocal

set "LAB=%~dp0"
set "ROOT=%LAB%.."

for %%I in ("%LAB%.") do set "LABNAME=%%~nxI"
set "SRC=%LAB%%LABNAME%.cpp"
set "OUT=%LAB%%LABNAME%.exe"
set "MSMPI_INC=%ROOT%\tools\msmpi\include"
set "MSMPI_LIB=%ROOT%\tools\msmpi\lib\x64"

if exist "%ROOT%\tools\mingw\w64devkit\bin\g++.exe" (
    set "GPP=%ROOT%\tools\mingw\w64devkit\bin\g++.exe"
    echo [build] Using bundled g++ ^(w64devkit^)
) else (
    where g++ >nul 2>&1
    if errorlevel 1 (
        echo [build] ERROR: g++ not found. See README.md.
        exit /b 1
    )
    set "GPP=g++"
    echo [build] Using system g++
)

"%GPP%" "%SRC%" -o "%OUT%" -I"%MSMPI_INC%" -L"%MSMPI_LIB%" -lmsmpi
if errorlevel 1 (
    echo [build] FAILED.
    exit /b 1
)
echo [build] OK: %LABNAME%.exe
