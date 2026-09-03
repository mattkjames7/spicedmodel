cmake_minimum_required(VERSION 3.20)

project(spicedmodel LANGUAGES CXX)

set(BUILD_TESTING OFF CACHE BOOL "Build bundled SPICED tests" FORCE)
add_subdirectory(spicedmodel/__data/spiced)

# scikit-build-core installs this component directly into the wheel. The
# submodule's development files and CMake package are intentionally omitted.
install(
    TARGETS spiced ann
    LIBRARY DESTINATION spicedmodel/__data/spiced/lib COMPONENT Python
    RUNTIME DESTINATION spicedmodel/__data/spiced/lib COMPONENT Python
)
