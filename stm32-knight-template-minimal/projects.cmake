set(ST_MULTICONTEXT DUAL_CORE CACHE STRING "Type of multi-context")
message("   BUILD_CONTEXT: " ${BUILD_CONTEXT})
message("   CMAKE_SOURCE_DIR: " ${CMAKE_SOURCE_DIR})
message("   PROJECT_SOURCE_DIR: " ${PROJECT_SOURCE_DIR})
#-----------------------Build CM7 Project-----------------------#
if((${BUILD_CONTEXT} MATCHES .*CM7.*) OR (NOT DEFINED BUILD_CONTEXT))
    message("   Build context: " CM7)
    ExternalProject_Add(stm32-knight-template-minimal-cm7
        BINARY_DIR                  ${CMAKE_SOURCE_DIR}/build/cm7/build
        SOURCE_DIR                  ${PROJECT_SOURCE_DIR}/target/stm32h747i_disco/cm7
        PREFIX                      cm7
        CONFIGURE_HANDLED_BY_BUILD  true
        INSTALL_COMMAND             ""
        CMAKE_ARGS                  -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
    )
	set(ST_DUAL_CORE_CM7_PROJECT_BUILD_TARGET ${CMAKE_SOURCE_DIR}/build/cm7/build/stm32-knight-template-minimal-cm7${CMAKE_EXECUTABLE_SUFFIX_CXX} CACHE FILEPATH "Path to cm7 project target")
endif()