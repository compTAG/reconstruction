set(EXAMPLES
    height-filtration
    reconstruct-complex
)

foreach(example ${EXAMPLES})
    add_executable(${example} ${example}.cpp)
    target_link_libraries(${example} ${LIBRARIES})
endforeach()
