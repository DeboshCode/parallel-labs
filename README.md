# parallel-labs

Portable MPI labs for Windows. No system-wide installation required to **build or run**.

## Structure

```
parallel-labs/
├── tools/
│   ├── mingw/         (committed — w64devkit 2.8.0, portable compiler)
│   └── msmpi/         (committed — headers, lib, mpiexec, msmpi.dll)
├── lab1/
│   ├── lab1.cpp
│   ├── lab1.exe       (pre-built)
│   ├── msmpi.dll
│   ├── build.bat
│   └── ran.bat
├── new_lab.bat
├── .gitignore
└── README.md
```

## Quick start

```bat
git clone https://github.com/DeboshCode/parallel-labs.git
cd parallel-labs\lab1
.\ran.bat
```

`lab1.exe`, `msmpi.dll` and `mpiexec.exe` are included in the repo.
No compiler or MS-MPI installation needed on the target machine.

## Working with a specific lab

```bat
cd labN
.\build.bat    :: compile labN.cpp -> labN.exe  (uses bundled w64devkit)
.\ran.bat      :: run with 4 MPI processes       (uses bundled mpiexec)
```

Both scripts search for tools one level up (`%~dp0..\tools\`):
- **build.bat**: bundled w64devkit → system g++ → error
- **ran.bat**: bundled mpiexec → system MPI → PATH → error

## Adding a new lab

From the repo root:

```bat
.\new_lab.bat 2
```

This creates `lab2\` with:
- `lab2.cpp` — MPI skeleton (Init / Comm_rank / Comm_size / Finalize)
- `msmpi.dll` — copied from `tools\msmpi\bin\`
- `build.bat` / `ran.bat` — pre-configured for lab2

Then:

```bat
cd lab2
.\build.bat
.\ran.bat
```
