include libft/constants.mk libft/colors.mk

ASM = asm
CW = corewar

LIBFT = libft
LIBFTA = $(LIBFT)/libft.a
LIBFT_INCDIR = $(LIBFT)/includes

HEADERS = cw.h op.h
INCDIR = includes
INCLUDES = $(addprefix $(INCDIR)/, $(HEADERS))

ASM_FILENAMES = asm

ASM_SRCDIR = src
ASM_SOURCES = $(patsubst %, $(ASM_SRCDIR)/%.c, $(ASM_FILENAMES))
ASM_BIN = $(patsubst %, $(ODIR)/%.o, $(ASM_FILENAMES))

CW_FILENAMES = corewar
CW_SRCDIR = src
CW_SOURCES = $(patsubst %, $(CW_SRCDIR)/%.c, $(CW_FILENAMES))
CW_BIN = $(patsubst %, $(ODIR)/%.o, $(CW_FILENAMES))

BOTH_SRC = op.c
BOTH_SRCDIR = src
BOTH_SOURCES = $(addprefix $(BOTH_SRCDIR)/, $(BOTH_SRC))
BOTH_BIN = $(BOTH_SOURCES:.c=.o)

.PHONY = $(LIBFT)

all: $(LIBFTA) $(ASM) $(CW)

$(LIBFTA):
	@make -C libft

$(ASM): $(ASM_BIN)
	@echo ""
	@$(CC) $(FLAGS) $^ -o $@ -I $(LIBFT_INCDIR) -I $(INCDIR) -L $(LIBFT) -l ft
	@echo ${GREEN}[$(ASM) is up to date.]${NC}

$(CW): $(CW_BIN)
	@echo ""

	@$(CC) $(FLAGS) $^ -o $@ -I $(LIBFT_INCDIR) -I $(INCDIR) -L $(LIBFT) -l ft
	@echo ${GREEN}[$(CW) is up to date.]${NC}

$(ODIR)/%.o: $(ASM_SRCDIR)/%.c $(INCLUDES)
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
