#! /bin/bash

# Allow this script to be run from different working directory without messing up relative paths
scriptdir="$(dirname "$0")"
cd "$scriptdir"

echo -e "\nRunning cmake...\n"
cmake .. -GUnix\ Makefiles -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_BUILD_TYPE=Release

echo -e "\nBuilding tests...\n"
cmake --build .
