project(RayTracingInOneWeekend)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/color.cpp
    src/types.cpp
    src/sphere.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE
    include)

target_link_libraries(${PROJECT_NAME} PRIVATE
    spdlog::spdlog
    Eigen3::Eigen)