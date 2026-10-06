file(GLOB CORE_SOURCE CONFIGRUE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.c"    
)

get_property(SERVICES
    GLOBAL
    PROPERTY SERVICES_REGISTRY
)
set(SERVICE_SOURCE
    "${CMAKE_CURRENT_BINARY_DIR}/service_registry.c"
)
set(RESOURCE_SOURCE
    "${CMAKE_CURRENT_BINARY_DIR}/resource_registry.c"
)

set(SERVICE_REGISTRY
    "${CMAKE_CURRENT_BINARY_DIR}/service_registry.c"
)

set(SERVICE_INCLUDES "")
set(SERVICE_DEFINITIONS "")
set(SERVICE_ENUM "")
set(THREAD_INDEX 0)



foreach(service ${SERVICES})

    string(REPLACE "|" ";" DATA "${service}")

    list(GET DATA 0 NAME)
    list(GET DATA 1 THREAD)
    list(GET DATA 2 HEADER)

    message(STATUS
        "Register: ${NAME}, ${THREAD}, ${HEADER}"
    )

    string(APPEND SERVICE_INCLUDES
        "#include \"${HEADER}\"\n"
    )

    string(APPEND SERVICE_DEFINITIONS
        "    { .name = \"${NAME}\", .thread = ${THREAD} , .data = ${NAME} },\n"
    )

    string(APPEND SERVICE_ENUM
        "   ${NAME} = 1 << ${THREAD_INDEX},\n"
    )
    math(EXPR THREAD_INDEX "${THREAD_INDEX} + 1")

endforeach()

message(STATUS "INCLUDES = ${SERVICE_INCLUDES}")
message(STATUS "DEFINITIONS = ${SERVICE_DEFINITIONS}")

configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/service_registry.c.in"
    "${SERVICE_REGISTRY}"
    @ONLY
)

set(RESOURCE_REGISTRY "${CMAKE_CURRENT_BINARY_DIR}/resource_registry.c")

get_property(RESOURCE
    GLOBAL
    PROPERTY RESOURCES_REGISTRY
)

set(UNIQUE_RESOURCES "")

foreach(resource ${RESOURCE})

    list(FIND UNIQUE_RESOURCES "${resource}" index)

    if(index EQUAL -1)
        list(APPEND UNIQUE_RESOURCES "${resource}")
        string(REPLACE "|" ";" DATAED "${service}")

        string(REPLACE "," ";" DATAS "${resource}")

        list(GET DATAS 0 TYPE)
        list(GET DATAS 1 THREAD_TYPE)
        list(GET DATAS 2 INDEX)
        list(GET DATAS 3 NAMES)
        string(APPEND RESOURCE_DATA
        "{.type = ${TYPE} , .thread = ${THREAD_TYPE} , .index = ${INDEX} ,.belong = ${NAMES}},\n"
        )

        message(STATUS "UNIQUE_RESOURCES = ${DATAS}")
        
    endif()
    

    message(STATUS "RESOURCE_DATA = ${resource}")
endforeach()


configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/resource_registry.c.in"
    "${RESOURCE_REGISTRY}"
    @ONLY
)



message(STATUS "SERVICES = ${SERVICES}")
message(STATUS "SERVICES DATA = ${RESOURCE}")

set(RESOURCE_H "${CMAKE_CURRENT_BINARY_DIR}/resource_registry.h")
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/resource_registry.h.in"
    "${RESOURCE_H}"
    @ONLY
)



add_library(core STATIC
    ${CORE_SOURCE}
    ${SERVICE_SOURCE}
    ${RESOURCE_SOURCE}
)

target_include_directories(core
    PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}"
    PRIVATE
    "${CMAKE_CURRENT_BINARY_DIR}"
)

target_link_libraries(core
    PRIVATE
    LLM
    STT
    TTS
    MODEL
)

