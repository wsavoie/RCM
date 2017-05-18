cmake_minimum_required (VERSION 2.8)
project (RCM)

# configure a header file to pass some of the CMake settings
# to the source code


set(IRRLICHT_PATH "" CACHE FILEPATH "path to Irrlicht Folder")
set(GTENGINE_PATH "" CACHE FILEPATH "path to GTEngine folder")
set(OGRE_PATH "" CACHE FILEPATH "path to OGRE folder")

set(GTENGINE_LIB_CONFIGPATH "" CACHE FILEPATH "path to GTEngine directory with configuration folders containing lib files")
set(IRRLICHT_LIB_DIR "" CACHE FILEPATH "path to irrlicht directory with lib files")
set(OGRE_LIB_CONFIGDIR "" CACHE FILEPATH "path to ogre directory with configuration folders containing lib files")

SET(IRRLICHT_INC "${IRRLICHT_PATH}/include")

SET(OGRE_INC "${OGRE_PATH}/OgreMain/include" 
			"${OGRE_PATH}/Samples/Common/include"
			"${OGRE_PATH}/build/include")

# find_package(GTEngine)
file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")
file(GLOB HEADERS "${PROJECT_SOURCE_DIR}/include/*.h")


include_directories(
"${GTENGINE_PATH}/Source" 
"${GTENGINE_PATH}/Include"
 ${PROJECT_BINARY_DIR}
 "${PROJECT_SOURCE_DIR}/src"
 "${PROJECT_SOURCE_DIR}/include"
 ${OGRE_INC}
 ${IRRLICHT_INC}
 )

add_executable (RCM 
${SOURCES}
${HEADERS}
${INCLUDEDIRS}
)

# link_directories("${IRRLICHT_LIB_DIR}" "${OGRE_LIB_CONFIGDIR}/$<CONFIGURATION>" "${GTENGINE_LIB_CONFIGPATH}/$<CONFIGURATION>/")
target_link_libraries(RCM "${GTENGINE_LIB_CONFIGPATH}/$<CONFIGURATION>/*.lib" "${OGRE_LIB_CONFIGDIR}/$<CONFIGURATION>/*.lib"  "${IRRLICHT_LIB_DIR}/*.lib" )

# add_executable (RCM ${SOURCES})
# foreach(PROGRAM ${RCMCODE})

  # message(STATUS "...add ${PROGRAM}")


  # add_executable(${PROGRAM}  "${PROJECT_SOURCE_DIR}\src\${PROGRAM}.cpp" ${HEADERS} ${SOURCES})
  # source_group(""  FILES "${PROGRAM}.cpp")

  # # set_target_properties(${PROGRAM} PROPERTIES
    # # FOLDER demos
    # # COMPILE_FLAGS "${CHRONO_CXX_FLAGS}"
    # # COMPILE_DEFINITIONS "CHRONO_DATA_DIR=\"${CHRONO_DATA_DIR}\""
    # # LINK_FLAGS "${CHRONO_CXX_FLAGS} ${CHRONO_LINKER_FLAGS}"
  # # )

  # target_link_libraries(${PROGRAM})
  
  # #install(TARGETS ${PROGRAM} DESTINATION bin)

# endforeach(PROGRAM)	

