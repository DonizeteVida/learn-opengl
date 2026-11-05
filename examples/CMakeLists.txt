macro(example name)
    add_executable(${name} ${name}.cpp)
    target_link_libraries(${name} learn-opengl)
endmacro()

macro(examples)
    foreach(name ${ARGN})
        example(${name})
    endforeach()
endmacro()

examples(
    001_hello_world
    002_triangle
    003_triangle_times_2
)
