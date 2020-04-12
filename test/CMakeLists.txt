project(arugula_test)

file(GLOB TEST_SRC
    "smoke/*.cpp"
)

add_executable(smoke catch.hpp ${TEST_SRC} smoke_morph/test_transformers.cpp)
target_link_libraries(smoke arugula_lib)

add_custom_target(valgrind
  COMMAND valgrind --leak-check=yes ./smoke
  DEPENDS smoke
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)
