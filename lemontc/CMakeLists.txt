cmake_minimum_required(VERSION 3.5)
add_library(lemontc io.cpp counting.cpp)
if(CODE_COVERAGE AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(lemontc PRIVATE --coverage)
    target_link_libraries(lemontc INTERFACE --coverage)
endif()
target_link_libraries(lemontc INTERFACE ${LEMON_LIBRARY})
add_executable(lemon-tc lemon-tc.cpp)
target_link_libraries(lemon-tc lemontc)


install(DIRECTORY ./ DESTINATION include/lemontc
        FILES_MATCHING PATTERN "*.h")
install(TARGETS lemon-tc lemontc
        RUNTIME DESTINATION bin
        ARCHIVE DESTINATION lib)
