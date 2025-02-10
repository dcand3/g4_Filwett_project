#----------------------------------------------------------------------------
# Setup the project
cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

project(ResearchProject)

#----------------------------------------------------------------------------
# Set Geant4_DIR to the installation directory of Geant4
# (directory where Geant4config.cmake is located)
set(Geant4_DIR "D:/Prog_Files/projects/geant4/install/lib/cmake/Geant4")

find_package(Geant4 REQUIRED ui_all vis_all)

#----------------------------------------------------------------------------
# Setup Geant4 include directories and compile definitions
# Setup include directory for this project
#

include(${Geant4_USE_FILE})
#include_directories(${PROJECT_SOURCE_DIR}/include

#----------------------------------------------------------------------------
# Locate sources and headers for this project
# NB: headers are included so they will show up in IDEs
#
file(GLOB sources ${PROJECT_SOURCE_DIR}/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/*.hh)

#----------------------------------------------------------------------------
# Add the executable, and link it to the Geant4 libraries
#
add_executable(main main.cpp VolumeConstruction.cpp physics.cpp action.cpp generator.cpp 
	DetectorConstruction.cpp run.cpp ElectricField.cpp ${sources} ${headers})
#add_executable(action.cpp generator.cpp ${sources} ${headers})
target_link_libraries(main ${Geant4_LIBRARIES})

#----------------------------------------------------------------------------
# For internal Geant4 use - but has no effect if you build this
# example standalone
#
add_custom_target(ResearchProject DEPENDS main)