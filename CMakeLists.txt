cmake_minimum_required(VERSION 3.9)

include_directories(includes libft/includes)

set(INCLUDES includes/op.h includes/cw.h)
aux_source_directory(src SRC)
add_subdirectory(libft)

add_executable(cw ${SRC} ${INCLUDES})
target_link_libraries(cw ft)