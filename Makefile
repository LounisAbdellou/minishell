CC = cc
NAME = minishell
CFLAGS = -Wall -Wextra -Werror -Iincludes
LIBFT = ./libft/libft.a

SRC_DIR = src
OBJ_DIR = obj
FRONT_DIR = front

FRONT = $(addprefix $(FRONT_DIR)/, prompt.c signal.c)
SRCS = $(addprefix $(SRC_DIR)/, $(FRONT) main.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	@make -C libft
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) -lreadline

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJ_DIR)
	mkdir -p $(OBJ_DIR)/$(FRONT_DIR)

clean:
	@make clean -C libft
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(LIBFT)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
