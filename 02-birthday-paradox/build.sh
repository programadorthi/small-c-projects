# Delete build directory
# $ ./build.sh clean
if [ "$1" == 'clean' ]; then
    rm -rf build
    exit
fi

# Check if is to generate debug symbols
dbg=
if [ "$1" == 'debug' ]; then
    dbg=-g
fi

# Create build directory if it doesn't exists
if [ ! -d build ]; then
    mkdir build
fi

# Enter build directory
cd build

# Compile and link executable
gcc ../birthday-paradox.c -o birthday-paradox $dbg -Wall -Wextra -pedantic -std=c11

# Exit build directory
cd ..

# Run the program
if [ "$1" == 'debug' ]; then
   gdb build/birthday-paradox
elif [ "$1" == 'run' ]; then
   ./build/birthday-paradox
fi
