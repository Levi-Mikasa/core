file(GLOB UTILS_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c"
)

add_library(utils STATIC
    ${UTILS_SOURCES}
)

target_include_directories(utils
    PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

target_link_libraries(utils
    PUBLIC 
    ${PROJECT_LIBS}
)