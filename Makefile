# detecting OS to compile on Linux
UNAME = $(shell uname)

SRCS_FOLDER = srcs
OBJS_FOLDER = bin

SRCS = 	lexer.c \
		lex_functions.c \
		lex_functions2.c \
		token_utils.c \
		debug.c

OBJS = $(addprefix $(OBJS_FOLDER)/, $(SRCS:.c=.o))

NAME = minishell
INCLUDES = includes

HEADERS_LIST= $(addprefix $(INCLUDES)/, $(SRCS_LIST:.c=.h))
# La liste des .h marche comme ca, mais c'est pas opti. Faudrait que seul le .o correspondant
# au .h modifie soit recompile.

RM = rm -f
CC = clang
CFLAGS = -Werror -Wall -Wextra -g -I $(INCLUDES) -I$(LIBFT)/includes #-fsanitize=address
LIBFT	= libft

$(OBJS_FOLDER)/%.o: $(SRCS_FOLDER)/%.c $(INCLUDES)/minishell.h $(HEADERS_LIST) $(LIBFT)/$(LIBFT).a
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

all: libft_ $(NAME) 

ifeq ($(UNAME), Linux)
$(NAME) : $(OBJS) $(INCLUDES) $(SRCS_FOLDER)/main.c | libft_
	$(CC) $(CFLAGS) -lreadline -L$(LIBFT)  $(OBJS) $(SRCS_FOLDER)/main.c -o $(NAME) -lft
else
$(NAME) : $(OBJS) $(INCLUDES) $(SRCS_FOLDER)/main.c | libft_
	$(CC) $(CFLAGS) -lreadline -L$(LIBFT) -lft $(OBJS) $(SRCS_FOLDER)/main.c -o $(NAME)
endif

libft_:
	$(MAKE) -C $(LIBFT)

clean:
	$(MAKE) clean -C $(LIBFT)
	$(RM) -r $(OBJS_FOLDER)
	$(RM) -r $(NAME).dSYM

fclean: clean
	$(MAKE) fclean -C $(LIBFT)
	$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean re all
