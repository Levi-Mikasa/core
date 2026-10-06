message(STATUS ">>> Configuring TTS")

file(GLOB TTS_SOURCE CONFIGURE_DEPENDS 
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c"
)   

add_library(TTS STATIC
    ${TTS_SOURCE}
)

target_include_directories(TTS
    PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

set_property(GLOBAL APPEND
    PROPERTY SERVICES_REGISTRY
    "TTS|TTS_thread|tts.h"
)

set_property(GLOBAL APPEND
    PROPERTY RESOURCES_REGISTRY
    "QUEUE,LLM|TTS,0,TTS"
)

set_property(GLOBAL APPEND
    PROPERTY RESOURCES_REGISTRY
    "EVENT,LLM|TTS,1,TTS"
)