cp -f ../CMakeLists.txt_LINUX ../CMakeLists.txt
rm -f CMakeCache.txt
#cmake -DGeant4_DIR=/usr/local/share/Geant4-10.0.3 -DCMAKE_BUILD_TYPE=Debug ../
cmake -DGeant4_DIR=$G4INSTALL ../
make clean && make
