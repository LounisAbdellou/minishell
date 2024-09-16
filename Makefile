CC = cc
NAME = minishell
CFLAGS = -Wall -Wextra -Werror -Iincludes
LIBFT = ./libft/libft.a

SRC_DIR = src
OBJ_DIR = obj
FRONT_DIR = front
BUILTINS_DIR = builtin
PARSING_DIR = parsing
STRUCT_DIR = struct
EXEC_DIR = exec

FRONT = $(addprefix $(FRONT_DIR)/, prompt.c signal.c)
BUILTINS = $(addprefix $(BUILTINS_DIR)/, utils.c ft_export.c ft_env.c ft_unset.c ft_echo.c ft_cd.c ft_pwd.c ft_exit.c)
PARSING = $(addprefix $(PARSING_DIR)/, parsing.c tokenizer.c tokenizer_utils.c analyzer_utils.c expand_utils.c parse_tree.c setter_cmd.c setter_cmd_utils.c free_parse.c heredoc.c)
STRUCT = $(addprefix $(STRUCT_DIR)/, lst_word.c lst_op.c lst_cmd.c lst_file.c init_env.c entry_lst.c)
EXEC = $(addprefix $(EXEC_DIR)/, execute.c execute_utils.c execute_error.c wildcard.c)
SRCS = $(addprefix $(SRC_DIR)/, $(FRONT) $(PARSING) $(STRUCT) $(EXEC) $(BUILTINS) main.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	@make -C libft
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) -lreadline

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
	mkdir -p $(OBJ_DIR)/$(FRONT_DIR)
	mkdir -p $(OBJ_DIR)/$(BUILTINS_DIR)
	mkdir -p $(OBJ_DIR)/$(PARSING_DIR)
	mkdir -p $(OBJ_DIR)/$(STRUCT_DIR)
	mkdir -p $(OBJ_DIR)/$(EXEC_DIR)

clean:
	@make clean -C libft
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(LIBFT)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
