@echo off
setlocal

set "LAB=%~dp0"
set "ROOT=%LAB%.."

for %%I in ("%LAB%.") do set "LABNAME=%%~nxI"
set "EXE=%LAB%%LABNAME%.exe"

if exist "%ROOT%\tools\msmpi\bin\mpiexec.exe" (
    set "MPIEXEC=%ROOT%\tools\msmpi\bin\mpiexec.exe"
    echo [run] Using bundled mpiexec
) else if exist "C:\Program Files\Microsoft MPI\Bin\mpiexec.exe" (
    set "MPIEXEC=C:\Program Files\Microsoft MPI\Bin\mpiexec.exe"
    echo [run] Using system mpiexec
) else (
    where mpiexec >nul 2>&1
    if errorlevel 1 (
        echo [run] ERROR: mpiexec not found. See README.md.
        exit /b 1
    )
    set "MPIEXEC=mpiexec"
    echo [run] Using mpiexec from PATH
)

"%MPIEXEC%" -n 4 "%EXE%"
