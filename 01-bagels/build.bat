@rem Avoid each command been printed during execution
@echo off

@rem Check if to delete the build directory
@if "%1" == "clean" (
    rm -rf build
    goto finish
)

@rem Variable to flag compiler to generate debug symbols
set dbg=
@if "%1" == "debug" (
    set dbg=/Zi
)

@rem Create build directory
mkdir build

@rem Enter build directory
pushd build

@rem Compile and generate executables inside build directory
@rem https://learn.microsoft.com/en-us/cpp/build/walkthrough-compile-a-c-program-on-the-command-line?view=msvc-170
cl ..\bagels.c /std:c11 %dbg% 

@rem Exit build directory
popd

@rem Run the program
@if "%1" == "debug" (
    devenv /debugexe build\bagels.exe
)
@if "%1" == "run" (
    .\build\bagels.exe
)

:finish
