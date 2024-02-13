##############
#
# Compiler
#
##############
CC	= clang	# on school dumps, cc is aliased to clang
CFLAGS	= -Wall -Wextra -Werror  \
	-I$(INCDIR) \
	-g \
	# -fsanitize=address \
	# -O2 \

CLFLAGS	= 


##############
#
# Project files
#
##############
SRCDIR	= src
OBJDIR	= build
INCDIR	= src

OBJ	= $(addprefix $(OBJDIR)/, $(SRC:.c=.o))
NAME = minishell
SRC	= main.c \
		env.c \
		error.c \
		exec.c \
		expend.c \
		fill_nodes.c \
		get_next_line.c \
		get_next_line_utils.c \
		get_params.c \
		heredoc.c \
		parse_args.c \
		signal.c \
		builtins/builtins_1.c \
		commandes/cmd_custom.c \
		commandes/ft_cmdsubsplit.c \
		commandes/ft_cmdtrim.c \
		commandes/get_cmd.c \
		utils/ft_strtrim_all.c \
		utils/utils_1.c \
		utils/ft_matrix.c \
		utils/ft_matrix_2.c 

# lifbt
LFTDIR = $(SRCDIR)/libft
LFT = $(LFTDIR)/libft.a
CFLAGS += -I$(LFTDIR)
CLFLAGS += -L$(LFTDIR) -lft

GCDIR = $(SRCDIR)/gc
GC = $(LFTDIR)/gc.a
CFLAGS += -I$(GCDIR)
CLFLAGS += -L$(GCDIR) -lgc

##############
#
# Build
#
##############

.PHONY:	all clean fclean re

all:	$(GC) $(LFT) $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $^ $(CLFLAGS) -lreadline

clean:
	rm -rf $(OBJDIR)
	make -C $(LFTDIR) clean
	make -C $(GCDIR) clean

fclean:	clean
	rm -f $(NAME)
	make -C $(LFTDIR) fclean
	make -C $(GCDIR) fclean


re:	fclean all

#
# project srcs build
#
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ -c $<

# lifbt
$(LFT):
	make -C $(LFTDIR)

$(GC):
	make -C $(GCDIR)
