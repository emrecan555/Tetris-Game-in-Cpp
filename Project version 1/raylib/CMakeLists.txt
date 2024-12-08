project(raylib)

set(RAYLIB_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(RAYLIB_INCLUDE_DIR ${RAYLIB_SOURCE_DIR}/include)

add_library(raylib STATIC IMPORTED GLOBAL)

if(WIN32)
    set_target_properties(raylib PROPERTIES
        IMPORTED_LOCATION ${RAYLIB_SOURCE_DIR}/lib/raylib.lib
    )
elseif(UNIX AND NOT APPLE)
    set_target_properties(raylib PROPERTIES
        IMPORTED_LOCATION ${RAYLIB_SOURCE_DIR}/lib/raylib.a
    )
elseif(APPLE)
    set_target_properties(raylib PROPERTIES
        IMPORTED_LOCATION ${RAYLIB_SOURCE_DIR}/lib/raylib.a
    )
endif()

target_include_directories(raylib INTERFACE ${RAYLIB_INCLUDE_DIR})