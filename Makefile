# detecting OS to compile on Linux
UNAME = $(shell uname)

SRCS_FOLDER = srcs
OBJS_FOLDER = bin

SRCS = 	tokenizer/lexer.c \
		tokenizer/lex_functions.c \
		tokenizer/lex_functions2.c \
		tokenizer/token_utils.c \
		tokenizer/variable_expansion.c \
		tokenizer/variable_expansion2.c \
		tokenizer/buffers.c \
		tokenizer/debug.c \
		tokenizer/error_message.c \
		parser/parser.c \
		parser/debug.c \
		parser/array_utils.c \
		parser/parse_funcs.c \
		signal/signals.c \
		execution/free.c \
		execution/main_exec/exec.c \
		execution/main_exec/final_exec.c \
		execution/main_exec/exec_utils.c \
		execution/plugs/heredocs.c \
		execution/plugs/wait_pid.c \
		execution/plugs/inputs_manip.c \
		execution/plugs/outputs_manip.c \
		execution/builtins/check_functions.c \
		execution/builtins/exec_builtin.c \
		execution/builtins/cd/cd.c \
		execution/builtins/pwd/pwd.c \
		execution/builtins/export_/export.c \
		execution/builtins/env_/env.c \
		execution/builtins/echo/echo.c \
		execution/builtins/unset/unset.c \
		execution/builtins/key_mooves.c \
		execution/array_manip/env.c \
		execution/array_manip/cmd_path.c \
		execution/array_manip/replace_pwd.c \

OBJS = $(addprefix $(OBJS_FOLDER)/, $(SRCS:.c=.o))

NAME = minishell
INCLUDES = includes

HEADERS_LIST = $(addprefix $(INCLUDES)/, minishell.h execution.h lexer.h parser.h signals.h)
# La liste des .h marche comme ca, mais c'est pas opti. Faudrait que seul le .o correspondant
# au .h modifie soit recompile.

RM = rm -f
CC = clang
CFLAGS = -Werror -Wall -Wextra -I$(INCLUDES) -I$(LIBFT)/includes #-g3 -fsanitize=address
LIBFT	= libft
#readline stuffs:
LDFLAGS="-L$(HOME)/.brew/opt/readline/lib"
CPPFLAGS="-I$(HOME)/.brew/opt/readline/include"

$(OBJS_FOLDER)/%.o: $(SRCS_FOLDER)/%.c $(HEADERS_LIST) $(LIBFT)/$(LIBFT).a
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

all: libft_ $(NAME) 

ifeq ($(UNAME), Linux)
$(NAME) : $(OBJS) $(INCLUDES) $(SRCS_FOLDER)/main.c | libft_
	$(CC) $(CFLAGS) -lreadline $(LDFLAGS) $(CPPFLAGS) -L$(LIBFT)  $(OBJS) $(SRCS_FOLDER)/main.c -o $(NAME) -lft
else
$(NAME) : $(OBJS) $(INCLUDES) $(SRCS_FOLDER)/main.c | libft_
	$(CC) $(CFLAGS) -lreadline $(LDFLAGS) $(CPPFLAGS) -L$(LIBFT) -lft $(OBJS) $(SRCS_FOLDER)/main.c -o $(NAME)
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
