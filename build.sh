#!/bin/bash

function print_usage(){
    local usage="Usage: ./build.sh [-r] [-i install_path]\n
    -r: reset build directory.\n
    -i: set library install directory.\n"
    echo -e $usage
}

INSTALL="./install/"
RESET=0

OPTIONS=$(getopt -o ri: -- "$@")
[ $? -eq 0 ] || {
    print_usage
    exit 1
}

eval set -- $OPTIONS
while [ $# -gt 0 ]; do
    case "$1" in
        -r|--reset)
            RESET=1
            ;;
        -i|--install)
            INSTALL="$2"
            shift
            ;;
        --)
            shift
            ;;
        *)
            echo -e "Unknown argument\n"
            print_usage
            exit 1
            ;;
    esac
    shift
done

[ $RESET -eq 1 ] && [ -d ./build/ ] && rm -rf ./build/
cmake -S . -B ./build -D CMAKE_EXPORT_COMPILE_COMMANDS=ON -D CMAKE_INSTALL_PREFIX="$INSTALL"
[ -z "$INSTALL" ] || cmake --build ./build --target install

