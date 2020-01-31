file(GLOB module_files
	"include/*.h"
	"source/*.cpp"
)

# Set Properties->General->Configuration Type to DLL
add_library (Components STATIC ${module_files})

add_dependencies(Components ModuleRendering)
add_dependencies(Components ModuleInput)
add_dependencies(Components Weapons)

target_link_libraries(Components Utilities)
target_link_libraries(Components Weapons)
target_link_libraries(Components ModuleInput)
target_link_libraries(Components ModuleRendering)

# Properties->Linker->Input->Additional Dependencies
foreach(_LIB ${CONAN_LIBS_RELEASE})
    target_link_libraries(Components optimized ${_LIB})
endforeach()
foreach(_LIB ${CONAN_LIBS_DEBUG})
    target_link_libraries(Components debug ${_LIB})
endforeach()

# Creates a folder "executables" and adds target
# project (app.vcproj) under it
set_property(TARGET Components PROPERTY FOLDER "executables")

# Properties->General->Output Directory
set_target_properties(Components PROPERTIES
                      RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

