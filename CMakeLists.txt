# $Id: CMakeLists.txt 68058 2013-03-13 14:47:43Z gcosmo $

#----------------------------------------------------------------------------
# Setup the project
#
SET(ROOT_DIR "/home/razvan/root/")
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(g4ids)


set  (CMAKE_CXX_FLAGS "-w")

#----------------------------------------------------------------------------
# Find Geant4 package, activating all available UI and Vis drivers by default
# You can set WITH_GEANT4_UIVIS to OFF via the command line or ccmake/cmake-gui
# to build a batch mode only executable
#
option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()

#----------------------------------------------------------------------------
# Setup Geant4 include directories and compile definitions
# Setup include directory for this project
#

include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include/)
include_directories(${ROOT_DIR}/include/)
include_directories(/usr/local/include/)
include_directories(/home/razvan/geant4/install/include/Geant4/)
include_directories(/home/razvan/CADMesh/install/include/)
#----------------------------------------------------------------------------
# Locate sources and headers for this project + link ROOT .h
# NB: headers are included so they will show up in IDEs
#
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)
file(GLOB headers ${ROOT_DIR}/include/*.h)
#----------------------------------------------------------------------------
# Add the executable, and link it to the Geant4 libraries
#
add_executable(g4ids g4ids.cc ${sources} ${headers})
target_link_libraries(g4ids ${Geant4_LIBRARIES})
target_link_libraries(g4ids ${ROOT_DIR}/lib/libTree.so)
target_link_libraries(g4ids ${ROOT_DIR}/lib/libRIO.so)
target_link_libraries(g4ids ${ROOT_DIR}/lib/libCore.so)
target_link_libraries(g4ids ${ROOT_DIR}/lib/libMathCore.so)
target_link_libraries(g4ids /home/razvan/CADMesh/install/lib/libcadmesh.so)

#----------------------------------------------------------------------------
# Copy all scripts to the build directory, i.e. the directory in which we
# build B4a. This is so that we can run the executable directly because it
# relies on these scripts being in the current working directory.
#
set(g4ids_SCRIPTS
  vrml.mac
  vis.mac
  gui.mac
  noGUI.mac
  icons.mac
  init.mac
  init_vis.mac
  root2ascii.C
  root2ascii.h
  )

foreach(_script ${g4ids_SCRIPTS})
  configure_file(
    ${PROJECT_SOURCE_DIR}/macros/${_script}
    ${PROJECT_BINARY_DIR}/${_script}
    COPYONLY
    )
endforeach()
#----------------------------------------------------------------------------
# Install the executable to 'bin' directory under CMAKE_INSTALL_PREFIX
#
install(TARGETS g4ids DESTINATION bin)
