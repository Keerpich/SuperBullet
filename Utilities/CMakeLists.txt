file(GLOB module_files
	"include/*.h"
	"source/*.cpp"
)

# Set Properties->General->Configuration Type to DLL
add_library (Utilities STATIC ${module_files})

#add_dependencies(Components ModuleRendering)

# Properties->Linker->Input->Additional Dependencies
foreach(_LIB ${CONAN_LIBS_RELEASE})
    target_link_libraries(Utilities optimized ${_LIB})
endforeach()
foreach(_LIB ${CONAN_LIBS_DEBUG})
    target_link_libraries(Utilities debug ${_LIB})
endforeach()

# Creates a folder "executables" and adds target
# project (app.vcproj) under it
set_property(TARGET Utilities PROPERTY FOLDER "executables")

# Properties->General->Output Directory
set_target_properties(Utilities PROPERTIES
                      RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

