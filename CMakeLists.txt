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
file(GLOB sources ${PROJECT_SOURCE_DIR}/*.cpp)
file(GLOB headers ${PROJECT_SOURCE_DIR}/*.hh)

file(GLOB MACRO_FILES "${CMAKE_SOURCE_DIR}/*.mac")

#----------------------------------------------------------------------------
# Add the executable, and link it to the Geant4 libraries
#
add_executable(main main.cpp VolumeConstruction.cpp physics.cpp action.cpp generator.cpp 
	DetectorConstruction.cpp run.cpp ${sources} ${headers})
#add_executable(main main.cpp ${source} ${headers})

target_link_libraries(main ${Geant4_LIBRARIES})

#----------------------------------------------------------------------------
# Copy each .mac file to the output directory after build
#
#foreach(mac_file ${MACRO_FILES})
#    add_custom_command(TARGET main POST_BUILD
#        COMMAND ${CMAKE_COMMAND} -E copy
#        ${mac_file}
#        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIG>
#        COMMENT "Copying ${mac_file} to runtime directory"
#    )
#endforeach()


#----------------------------------------------------------------------------
# For internal Geant4 use - but has no effect if you build this
# example standalone
#
add_custom_target(ResearchProject DEPENDS main)