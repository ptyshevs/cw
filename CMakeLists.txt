cmake_minimum_required(VERSION 3.9)

include_directories(includes libft/includes)

set(INCLUDES includes/op.h includes/cw.h includes/asm.h)

aux_source_directory(asm_src ASM_SRC)
aux_source_directory(cw_src CW_SRC)
aux_source_directory(viz_src VIZ_SRC)

add_subdirectory(libft)

add_executable(cw ${CW_SRC} ${VIZ_SRC} ${INCLUDES})
add_executable(asm ${ASM_SRC} ${INCLUDES})

target_link_libraries(cw ft ncurses)
target_link_libraries(asm ft)
