include(ExternalProject)
message("[projects.cmake]")
set(ST_MULTICONTEXT DUAL_CORE CACHE STRING "Type of multi-context")
message("   BUILD_TARGET: " ${BUILD_TARGET})
message("   BUILD_CONTEXT: " ${BUILD_CONTEXT})
message("   CMAKE_SOURCE_DIR: " ${CMAKE_SOURCE_DIR})
message("   PROJECT_SOURCE_DIR: " ${PROJECT_SOURCE_DIR})
string(TOLOWER "${BUILD_TARGET}" BUILD_TARGET_LOWER)
if(${BUILD_TARGET} MATCHES STM32H747I_DISCO)
    message("   Build target: STM32H747I Discovery")
    if((${BUILD_CONTEXT} MATCHES .*CM7.*) OR (NOT DEFINED BUILD_CONTEXT))
        message("   Build context: CM7")
        ExternalProject_Add(stm32-knight-iap-touchgfx-cm7
            BINARY_DIR                  ${CMAKE_SOURCE_DIR}/build/cm7/build
            SOURCE_DIR                  ${PROJECT_SOURCE_DIR}/target/${BUILD_TARGET_LOWER}/cm7
            PREFIX                      cm7
            CONFIGURE_HANDLED_BY_BUILD  true
            INSTALL_COMMAND             ""
            CMAKE_ARGS                  -DCMAKE_EXPORT_COMPILE_COMMANDS=ON 
                                        -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}
                                        -DBUILD_CONTEXT=${BUILD_CONTEXT}
            BUILD_ALWAYS                true
        )
        set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_CLEAN_FILES "${CMAKE_SOURCE_DIR}/build")
        set(ST_DUAL_CORE_CM7_PROJECT_BUILD_TARGET ${CMAKE_SOURCE_DIR}/build/cm7/build/stm32-knight-iap-touchgfx-cm7${CMAKE_EXECUTABLE_SUFFIX_CXX} CACHE FILEPATH "Path to project target")
    endif()
endif()
