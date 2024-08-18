CC = cc
NAME = minishell
CFLAGS = -Wall -Wextra -Werror -Iincludes
LIBFT = ./libft/libft.a

SRCDIR = src
OBJDIR = obj

SRCS = $(addprefix $(SRCDIR)/, main.c)
OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	@make -C libft
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	@make clean -C libft
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(LIBFT)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
