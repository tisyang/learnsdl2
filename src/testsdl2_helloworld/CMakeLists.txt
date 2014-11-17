set(targetname testsdl2_helloworld)
aux_source_directory(. DIR_SRCS)
add_executable(${targetname} ${DIR_SRCS})
# link libraries
target_link_libraries(${targetname} mingw32 SDL2main SDL2)
# avoid console window
set_target_properties(${targetname}
	PROPERTIES
	LINK_FLAGS "-mwindows")
