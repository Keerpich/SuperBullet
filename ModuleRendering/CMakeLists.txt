# Set Properties->General->Configuration Type to DLL
add_library (ModuleRendering STATIC 
	include/Drawable.h 
	source/Drawable.cpp
	include/CircleShape.h
	source/CircleShape.cpp
	include/Sprite.h
	source/Sprite.cpp
	include/RectangleShape.h
	source/RectangleShape.cpp
	include/ConvexShape.h
	source/ConvexShape.cpp
)

# Properties->Linker->Input->Additional Dependencies
foreach(_LIB ${CONAN_LIBS_RELEASE})
    target_link_libraries(ModuleRendering optimized ${_LIB})
endforeach()
foreach(_LIB ${CONAN_LIBS_DEBUG})
    target_link_libraries(ModuleRendering debug ${_LIB})
endforeach()

# Creates a folder "executables" and adds target
# project (app.vcproj) under it
set_property(TARGET ModuleRendering PROPERTY FOLDER "executables")

# Properties->General->Output Directory
set_target_properties(ModuleRendering PROPERTIES
                      RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

