cmake_minimum_required (VERSION 2.8)
project (RCM)

# configure a header file to pass some of the CMake settings
# to the source code



# find_package(GTEngine)
file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")
file(GLOB HEADERS "${PROJECT_SOURCE_DIR}/include/*.h")

set(GTENGINE_PATH "" CACHE FILEPATH "path to include files for GTEngine")
include_directories("${GTENGINE_PATH}/Source" "${GTENGINE_PATH}/Include" ${PROJECT_BINARY_DIR} "${PROJECT_SOURCE_DIR}/src" "${PROJECT_SOURCE_DIR}/include" )




add_executable (RCM 
${SOURCES}
${HEADERS}
${INCLUDEDIRS}
)

set(GTENGINE_LIB_CONFIGPATH "" CACHE FILEPATH "path to any gtengine lib will correct for configuration type")

target_link_libraries(RCM "${GTENGINE_LIB_CONFIGPATH}/../$<CONFIGURATION>/*.lib")

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
