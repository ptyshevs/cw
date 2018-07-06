include libft/constants.mk libft/colors.mk

ASM = asm
CW = corewar

LIBFT = libft
LIBFTA = $(LIBFT)/libft.a
LIBFT_INCDIR = $(LIBFT)/includes

HEADERS = cw.h op.h asm.h viz.h structs.h
INCDIR = includes
INCLUDES = $(addprefix $(INCDIR)/, $(HEADERS))

ASM_FILENAMES = asm asm_prerequisites asm_validate asm_io \
    asm_cut asm_cut_more asm_cut_indirect \
    asm_is_smth asm_tk asm_tk_helper asm_tk_validate \
    asm_instr asm_tk_stringify asm_errors asm_errors_more \
    asm_label_deref asm_write

ASM_SRCDIR = asm_src
ASM_SOURCES = $(patsubst %, $(ASM_SRCDIR)/%.c, $(ASM_FILENAMES))
ASM_BIN = $(patsubst %, $(ODIR)/%.o, $(ASM_FILENAMES))

CW_FILENAMES = corewar cw_cli cw_errors cw_parse cw_parse_helpers cw_communicate \
    cw_bot_read cw_map cw_log cw_log_helpers cw_proc cw_args cw_args_helpers \
    cw_instr cw_dump cw_time cw_game_loop cw_game_period cw_misc cw_log_more \
    cw_func_op cw_func_load cw_func_live_store cw_func_fork cw_map_helpers

CW_SRCDIR = cw_src
CW_SOURCES = $(patsubst %, $(CW_SRCDIR)/%.c, $(CW_FILENAMES))
CW_BIN = $(patsubst %, $(ODIR)/%.o, $(CW_FILENAMES))

VIZ_FILENAMES = viz viz_more viz_color viz_colors_more viz_components viz_helpers

VIZ_SRCDIR = viz_src
VIZ_SOURCES = $(patsubst %, $(VIZ_SRCDIR)/%.c, $(VIZ_FILENAMES))
VIZ_BIN = $(patsubst %, $(ODIR)/%.o, $(VIZ_FILENAMES))

BOTH_SRC =
BOTH_SRCDIR = src
BOTH_SOURCES = $(addprefix $(BOTH_SRCDIR)/, $(BOTH_SRC))
BOTH_BIN = $(BOTH_SOURCES:.c=.o)

.PHONY = $(LIBFT)

all: $(LIBFTA) $(ASM) $(CW)

$(LIBFTA):
	@make -C libft

$(ASM): $(LIBFTA) $(ASM_BIN)
	@echo ""
	@$(CC) $(FLAGS) $^ -o $@ -I $(LIBFT_INCDIR) -I $(INCDIR) -L $(LIBFT) -l ft
	@echo ${GREEN}[$(ASM) is up to date.]${NC}

$(CW): $(LIBFTA) $(CW_BIN) $(VIZ_BIN)
	@echo ""
	@$(CC) $(FLAGS) $^ -o $@ -I $(LIBFT_INCDIR) -I $(INCDIR) -L $(LIBFT) -l ft -l ncurses
	@echo ${GREEN}[$(CW) is up to date.]${NC}

$(ODIR)/%.o: $(ASM_SRCDIR)/%.c $(INCLUDES)
	@mkdir -p $(ODIR)
	@/bin/echo -n "."
	@$(CC) $(FLAGS) -c $< -o $@ -I $(LIBFT_INCDIR) -I $(INCDIR)

$(ODIR)/%.o: $(CW_SRCDIR)/%.c $(INCLUDES)
	@mkdir -p $(ODIR)
	@/bin/echo -n "."
	@$(CC) $(FLAGS) -c $< -o $@ -I $(LIBFT_INCDIR) -I $(INCDIR)

$(ODIR)/%.o: $(VIZ_SRCDIR)/%.c $(INCLUDES)
	@mkdir -p $(ODIR)
	@/bin/echo -n "."
	@$(CC) $(FLAGS) -c $< -o $@ -I $(LIBFT_INCDIR) -I $(INCDIR)

clean:
	@echo ${RED}"[Removing *.o files]"${NC}
	@rm -rf $(ODIR)
	@make clean -C $(LIBFT)

fclean: clean
	@echo ${RED}"[Removing $(ASM)]"${NC}
	@rm -rf $(ASM)
	@echo ${RED}"[Removing $(CW)]"${NC}
	@rm -rf $(CW)
	@make fclean -C $(LIBFT)

re: fclean all
