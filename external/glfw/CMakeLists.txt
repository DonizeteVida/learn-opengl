include(FetchContent)

FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw
    GIT_TAG 3.5.1
    GIT_SHALLOW FALSE
)

FetchContent_MakeAvailable(glfw)