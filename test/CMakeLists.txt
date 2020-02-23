project(arugula_test)

file(GLOB TEST_SRC
    "smoke/*.cpp"
)

add_executable(smoke catch.hpp ${TEST_SRC})
target_link_libraries(smoke arugula_lib)
