message(STATUS ">>> Configuring STT")

file(GLOB STT_SOURCE CONFIGURE_DEPENDS 
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c"
)   

add_library(STT STATIC
    ${STT_SOURCE}
)

target_include_directories(STT
    PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    utils
)

target_link_libraries(STT
    PRIVATE
    utils
)

set_property(GLOBAL APPEND
    PROPERTY SERVICES_REGISTRY
    "STT|STT_thread|stt.h"
)

set_property(GLOBAL APPEND
    PROPERTY RESOURCES_REGISTRY
    "QUEUE,LLM|STT,0,STT"
)