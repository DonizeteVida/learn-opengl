macro(example name)
    add_executable(${name} ${name}.cpp)
    target_link_libraries(${name} learn-opengl)
endmacro()

example(001_hello_world)
example(002_triangle)