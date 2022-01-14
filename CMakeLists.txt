# Set the minimum version of CMake that can be used
# To find the cmake version run
# $ cmake --version
cmake_minimum_required(VERSION 3.5)

# Set the project name
project (HW3)

# GoogleTest requires at least C++11
set(CMAKE_CXX_STANDARD 11)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

enable_testing()

# Create a sources variable with a link to all cpp files to compile
set(SOURCES
	test.cpp 
)

# Add an executable
add_executable(HW3 ${SOURCES})


include_directories(HW3_headers    
        ${PROJECT_SOURCE_DIR}
)

target_link_libraries(
  HW3
  gtest
  gtest_main
)

include(GoogleTest)
gtest_discover_tests(HW3)
