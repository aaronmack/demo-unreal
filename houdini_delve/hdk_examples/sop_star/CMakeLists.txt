set( library_name SOP_Star )

# Code generation for the embedded DS file in SOP_Star.C.
houdini_generate_proto_headers( FILES SOP_Star.C )

# Add a library and its source files.
add_library( ${library_name} SHARED
    SOP_Star.C
    SOP_Star.h
)

# Link against the Houdini libraries, and add required include directories and
# compile definitions.
target_link_libraries( ${library_name} Houdini )

# Include ${CMAKE_CURRENT_BINARY_DIR} for the generated header.
target_include_directories( ${library_name} PRIVATE
    ${CMAKE_CURRENT_BINARY_DIR}
)

# Sets several common target properties, such as the library's output directory.
houdini_configure_target( ${library_name} )
