cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

#------------------------------------------------------------------------
# project name
#------------------------------------------------------------------------

project(notmuch-tests)

#------------------------------------------------------------------------
# build definitions
#------------------------------------------------------------------------
if(NOT CMAKE_BUILD_TYPE)
        set(CMAKE_BUILD_TYPE Debug CACHE STRING
      "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel."
      FORCE)
endif(NOT CMAKE_BUILD_TYPE)

string( REPLACE "-DNDEBUG" "" CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO}")

option (FORCE_COLORED_OUTPUT "Always produce ANSI-colored output (GNU/Clang only)." TRUE)
if (${FORCE_COLORED_OUTPUT})
    if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
       add_compile_options (-fdiagnostics-color=always)
    elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
       add_compile_options (-fcolor-diagnostics)
    endif ()
endif ()

#------------------------------------------------------------------------
# library dependencies
#------------------------------------------------------------------------
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})


find_package(Boost 1.67 REQUIRED COMPONENTS unit_test_framework)

include(BoostTestHelpers)

find_package(Notmuch REQUIRED)


#------------------------------------------------------------------------
# module dependencies
#------------------------------------------------------------------------

#------------------------------------------------------------------------
# include & link directories
#------------------------------------------------------------------------

#------------------------------------------------------------------------
# build configuration
#------------------------------------------------------------------------

add_definitions(-DBOOST_TEST_DYN_LINK)


#------------------------------------------------------------------------
# build
#------------------------------------------------------------------------

enable_testing()

#I like to keep test files in a separate source directory called test
file(GLOB test_srcs RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} src/*.cpp)

#Run through each source
foreach(test ${test_srcs})

  add_boost_test(TARGET test_target
                 SRC ${test}
                 DEPENDENCY_LIBS ${Notmuch_LIBRARY})

endforeach(test)




