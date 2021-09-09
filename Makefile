SRCS_FOLDER = srcs/
SRCS_LIST = lexer.c

SRCS = $(addprefix $(SRCS_FOLDER), $(SRCS_LIST))

OBJS = $(SRCS:.c=.o)

NAME = minishell
HEADER = includes
RM = rm -f
CC = clang
CFLAGS = -Werror -Wall -Wextra -g -I $(HEADER) -I$(LIBFT)/includes
LIBFT	= libft

%.o: %.c $(HEADER)/minishell.h $(LIBFT)/$(LIBFT).a
	$(CC) $(CFLAGS) -c $< -o $@

all: libft_ $(NAME)

$(NAME) : $(OBJS) $(HEADER) main.c | libft_
	$(CC) $(CFLAGS) -lreadline $(OBJS) main.c -o $(NAME)

libft_:
	$(MAKE) -C $(LIBFT)

clean:
	$(RM) $(OBJS)
	$(RM) -r $(NAME).dSYM

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean re all
