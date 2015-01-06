# get and build all subdirectories
file(GLOB allfiles RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *)
foreach(child ${allfiles})
    if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${child})
        add_subdirectory(${child})
    endif()
endforeach()

