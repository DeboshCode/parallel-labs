# parallel-labs

Portable MPI labs for Windows. No system-wide installation required to **run**.

## Structure

```
parallel-labs/
├── tools/
│   ├── mingw/         (gitignored — optional compiler, see below)
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

## Quick start (run only, no compiler needed)

```bat
git clone <repo-url>
cd parallel-labs\lab1
.\ran.bat
```

`lab1.exe` and `msmpi.dll` are included. `ran.bat` uses the bundled
`mpiexec.exe` from `tools\msmpi\bin\` — no system PATH required.

## Working with a specific lab

```bat
cd labN
.\build.bat    :: compile labN.cpp -> labN.exe
.\ran.bat      :: run with 4 MPI processes
```

Both scripts look for tools one level up (`%~dp0..\tools\`):
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

## Optional: set up bundled compiler (w64devkit)

Lets you rebuild on machines without any compiler installed.

1. Download `w64devkit-x64-*.7z.exe` from:
   https://github.com/skeeto/w64devkit/releases/latest
2. Run it and set the output folder to `<repo root>\tools\mingw\`
   so that `tools\mingw\w64devkit\bin\g++.exe` exists.
3. `tools\mingw\` is listed in `.gitignore` — it won't be committed.
