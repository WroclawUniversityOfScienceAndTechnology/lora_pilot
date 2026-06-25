cmake_minimum_required(VERSION 3.22)
set(UTEST_NAME tests_ut_libs_utils_app_info)

set(TEST_SRCS
    ${PROJECT_ROOT_DIR}/src/libs/utils/app_info/app_info.cpp
)

set(UT_SRCS
    ut_app_info.cpp
)

add_executable(${UTEST_NAME}
    ${TEST_SRCS}
    ${UT_SRCS}
)

target_link_libraries(${UTEST_NAME}
    ${CONAN_LIBS}
    MockEspOtaOps
)

add_test(NAME ${UTEST_NAME}
        COMMAND  $<TARGET_FILE:${UTEST_NAME}>)

target_include_directories(${UTEST_NAME}
    PRIVATE
        ${SOURCES_DIR}
        ${PROJECT_ROOT_DIR}/src/libs/utils/app_info/
)