# add_subdirectory            (pybind11)


if                          (CMAKE_LIBRARY_OUTPUT_DIRECTORY)        # to work with pip
    set                     (MODULE_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
else                        ()
    set                     (MODULE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
endif                       ()

file                        (MAKE_DIRECTORY "${MODULE_OUTPUT_DIRECTORY}/reconstruction")
file                        (GLOB DIONYSUS_PYTHON "${CMAKE_CURRENT_SOURCE_DIR}/reconstruction/*.py")
add_custom_target           (reconstruction ALL ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/reconstruction ${MODULE_OUTPUT_DIRECTORY}/reconstruction DEPENDS ${RECONSTRUCTION_PYTHON})

pybind11_add_module         (
                            _reconstruction reconstruction.cpp
                             test.cpp
                             point.cpp
                             reconstruction_tester.cpp
                            )
set_target_properties       (_reconstruction PROPERTIES OUTPUT_NAME reconstruction/_reconstruction)
