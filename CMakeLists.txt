cmake_minimum_required(VERSION 3.9)

include_directories(includes libft/includes)

set(INCLUDES includes/op.h includes/cw.h includes/asm.h)
set(CW_SRC src/corewar.c)

set(ASM_SRC src/asm.c src/asm_prerequisites.c)
add_subdirectory(libft)

add_executable(cw ${CW_SRC} ${INCLUDES})
add_executable(asm ${ASM_SRC} ${INCLUDES})

target_link_libraries(cw ft)
target_link_libraries(asm ft)
