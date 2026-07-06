set(_VCPKG_DIR "${CMAKE_CURRENT_LIST_DIR}/../vcpkg")

if(NOT EXISTS "${_VCPKG_DIR}/scripts/buildsystems/vcpkg.cmake")
    message(STATUS "vcpkg not found locally -- fetching it now (one-time setup, may take a minute)...")

    find_package(Git QUIET)
    if(NOT GIT_EXECUTABLE)
        message(FATAL_ERROR "Git is required to bootstrap vcpkg but was not found on PATH.")
    endif()

    execute_process(
        COMMAND "${GIT_EXECUTABLE}" clone --depth 1 https://github.com/microsoft/vcpkg.git "${_VCPKG_DIR}"
        RESULT_VARIABLE _clone_result
    )
    if(NOT _clone_result EQUAL 0)
        message(FATAL_ERROR "Failed to clone vcpkg (git exit code ${_clone_result}).")
    endif()

    if(WIN32)
        execute_process(
            COMMAND "${_VCPKG_DIR}/bootstrap-vcpkg.bat" -disableMetrics
            RESULT_VARIABLE _bootstrap_result
        )
    else()
        execute_process(
            COMMAND sh "${_VCPKG_DIR}/bootstrap-vcpkg.sh" -disableMetrics
            RESULT_VARIABLE _bootstrap_result
        )
    endif()
    if(NOT _bootstrap_result EQUAL 0)
        message(FATAL_ERROR "Failed to bootstrap vcpkg (exit code ${_bootstrap_result}).")
    endif()

    message(STATUS "vcpkg is ready.")
endif()

include("${_VCPKG_DIR}/scripts/buildsystems/vcpkg.cmake")
