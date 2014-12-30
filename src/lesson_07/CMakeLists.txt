set(targetname lesson_07)
aux_source_directory(. DIR_SRCS)
add_executable(${targetname} ${DIR_SRCS})
# link libraries
target_link_libraries(${targetname} mingw32 SDL2main SDL2 SDL2_image)
