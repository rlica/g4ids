cp -f ../CMakeLists.txt_OSX ../CMakeLists.txt
rm -f CMakeCache.txt
#cmake -DGeant4_DIR=/usr/local/share/Geant4-10.0.3 -DCMAKE_BUILD_TYPE=Debug ../
cmake -DGeant4_DIR=/opt/local/share/Geant4 -DCMAKE_BUILD_TYPE=Debug ../ 
make clean && make -j8 
