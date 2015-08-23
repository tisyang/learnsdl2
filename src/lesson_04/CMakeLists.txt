# use current dir name as targetname
get_filename_component(targetname ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" targetname ${targetname})

aux_source_directory(. DIR_SRCS)
add_executable(${targetname} ${DIR_SRCS})
# link libraries
target_link_libraries(${targetname} mingw32 SDL2main SDL2)
set_target_properties(${targetname}
	PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
