file(GLOB MODEL_SOURCE CONFIGURE_DEPEND
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*c"
)

add_library(MODEL STATIC
    ${MODEL_SOURCE}
)

target_include_directories(MODEL
    PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

set_property(GLOBAL APPEND
    PROPERTY SERVICES_REGISTRY
    "MODEL|MODEL_thread|model.h"
)