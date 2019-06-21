# Set Properties->General->Configuration Type to Application(.exe)
# Creates app.exe with the listed sources (main.cxx)
# Adds sources to the Solution Explorer
add_executable (main main.cpp)

# Properties->Linker->Input->Additional Dependencies
foreach(_LIB ${CONAN_LIBS_RELEASE})
    target_link_libraries(main optimized ${_LIB})
endforeach()
foreach(_LIB ${CONAN_LIBS_DEBUG})
    target_link_libraries(main debug ${_LIB})
endforeach()

# Creates a folder "executables" and adds target
# project (app.vcproj) under it
set_property(TARGET main PROPERTY FOLDER "executables")

# Properties->General->Output Directory
set_target_properties(main PROPERTIES
                      RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

# Adds logic to INSTALL.vcproj to copy app.exe to destination directory
install (TARGETS main
         RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/_install)
