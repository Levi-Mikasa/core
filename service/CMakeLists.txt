# add_subdirectory(LLM)
# add_subdirectory(STT)
# add_subdirectory(TTS)

file(GLOB SERVICE_DIRS
    LIST_DIRECTORIES true
    CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*"
)

message(STATUS "SERVICE_DIRS = ${SERVICE_DIRS}")

foreach(dir ${SERVICE_DIRS})

    if(IS_DIRECTORY ${dir})

        if(EXISTS "${dir}/CMakeLists.txt")
            add_subdirectory(${dir})
        endif()

    endif()

endforeach()


get_property(SERVICES
    GLOBAL
    PROPERTY SERVICE_REGISTRY
)

message(STATUS "Registered services: ${SERVICES}")
