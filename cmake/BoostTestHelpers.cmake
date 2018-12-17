
function(add_boost_test)

    set(oneValueArgs SRC NAME)
    set(multiValueArgs DEPENDENCY_SRCS DEPENDENCY_LIBS)
    cmake_parse_arguments(add_boost_test "" "${oneValueArgs}" "${multiValueArgs}" ${ARGN} )

    set(TEST_NAME_OUT ${add_boost_test_NAME})
    set(SOURCE_FILE_NAME ${add_boost_test_SRC})
    set(DEPENDENCY_LIBS ${add_boost_test_DEPENDENCY_LIBS})
    set(DEPENDENCY_SRCS ${add_boost_test_DEPENDENCY_SRCS})
    get_filename_component(TEST_EXECUTABLE_NAME ${SOURCE_FILE_NAME} NAME_WE)

    add_executable(${TEST_EXECUTABLE_NAME} ${SOURCE_FILE_NAME} ${DEPENDENCY_SRCS})

    target_link_libraries(${TEST_EXECUTABLE_NAME}
                          ${DEPENDENCY_LIBS}
                          ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

    file(READ "${SOURCE_FILE_NAME}" SOURCE_FILE_CONTENTS)
    string(REGEX MATCHALL "BOOST_AUTO_TEST_CASE\\( *([A-Za-z_0-9]+) *\\)"
           FOUND_TESTS ${SOURCE_FILE_CONTENTS})

    foreach(HIT ${FOUND_TESTS})
        string(REGEX REPLACE ".*\\( *([A-Za-z_0-9]+) *\\).*" "\\1" TEST_NAME ${HIT})

        add_test(NAME "${TEST_EXECUTABLE_NAME}.${TEST_NAME}"
                 COMMAND ${TEST_EXECUTABLE_NAME} --run_test=${TEST_NAME} --catch_system_error=yes)
    endforeach()

    set(${TEST_NAME_OUT} ${TEST_EXECUTABLE_NAME})

endfunction(add_boost_test)
