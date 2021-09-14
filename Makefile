SRCS_FOLDER = srcs
SRCS_LIST = lexer.c \
			lex_functions.c \
			debug.c

SRCS = $(addprefix $(SRCS_FOLDER)/, $(SRCS_LIST))

OBJS = $(SRCS:.c=.o)

NAME = minishell
INCLUDES = includes

HEADERS_LIST= $(addprefix $(INCLUDES)/, $(SRCS_LIST:.c=.h))
# La liste des .h marche comme ca, mais c'est pas opti. Faudrait que seul le .o correspondant
# au .h modifie soit recompile.

RM = rm -f
CC = clang
CFLAGS = -Werror -Wall -Wextra -g -I $(INCLUDES) -I$(LIBFT)/includes
LIBFT	= libft

%.o: %.c $(INCLUDES)/minishell.h $(HEADERS_LIST) $(LIBFT)/$(LIBFT).a
	$(CC) $(CFLAGS) -c $< -o $@

all: libft_ $(NAME)

$(NAME) : $(OBJS) $(INCLUDES) $(SRCS_FOLDER)/main.c | libft_
	$(CC) $(CFLAGS) -lreadline -L$(LIBFT) -lft $(OBJS) $(SRCS_FOLDER)/main.c -o $(NAME)

libft_:
	$(MAKE) -C $(LIBFT)

clean:
	$(MAKE) clean -C $(LIBFT)
	$(RM) $(OBJS)
	$(RM) -r $(NAME).dSYM

fclean: clean
	$(MAKE) fclean -C $(LIBFT)
	$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean re all
