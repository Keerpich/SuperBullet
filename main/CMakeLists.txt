# Set Properties->General->Configuration Type to Application(.exe)
# Creates app.exe with the listed sources (main.cxx)
# Adds sources to the Solution Explorer

file(GLOB main_files
	"include/*.h"
	"source/*.cpp"
)

add_executable (main ${main_files})

add_dependencies(main ModuleWindow)
add_dependencies(main ModuleRendering)
add_dependencies(main Components)

# Properties->Linker->Input->Additional Dependencies
foreach(_LIB ${CONAN_LIBS_RELEASE})
    target_link_libraries(main 
		optimized ${_LIB} 
		optimized ${PROJECT_BINARY_DIR}/ModuleWindow/Release/ModuleWindow.lib 
		optimized ${PROJECT_BINARY_DIR}/ModuleRendering/Release/ModuleRendering.lib
		optimized ${PROJECT_BINARY_DIR}/Components/Release/Components.lib
	)
endforeach()
foreach(_LIB ${CONAN_LIBS_DEBUG})
    target_link_libraries(main 
		debug ${_LIB} 
		debug ${PROJECT_BINARY_DIR}/ModuleWindow/Debug/ModuleWindow.lib 
		debug ${PROJECT_BINARY_DIR}/ModuleRendering/Debug/ModuleRendering.lib
		debug ${PROJECT_BINARY_DIR}/Components/Debug/Components.lib
	)
	
endforeach()

# Creates a folder "executables" and adds target
# project (app.vcproj) under it
set_property(TARGET main PROPERTY FOLDER "executables")

# Properties->General->Output Directory
set_target_properties(main PROPERTIES
                      RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

# Copies SFML dlls
add_custom_command(TARGET main POST_BUILD
					COMMAND ${CMAKE_COMMAND} -E copy_directory
					${CONAN_SFML_ROOT_RELEASE}/bin/ $<TARGET_FILE_DIR:main>)

					
# Copies Assets to exe file location
add_custom_command(TARGET main POST_BUILD
					COMMAND ${CMAKE_COMMAND} -E copy_directory
					${CMAKE_CURRENT_SOURCE_DIR}/../Assets $<TARGET_FILE_DIR:main>/Assets)

# Copies Assets to project location
add_custom_command(TARGET main POST_BUILD
					COMMAND ${CMAKE_COMMAND} -E copy_directory
					${CMAKE_CURRENT_SOURCE_DIR}/../Assets ${PROJECT_BINARY_DIR}/main/Assets)


# Adds logic to INSTALL.vcproj to copy app.exe to destination directory
install (TARGETS main
         RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/_install)
