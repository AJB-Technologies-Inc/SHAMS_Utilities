include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG f8d7d77
)

FetchContent_MakeAvailable(googletest)