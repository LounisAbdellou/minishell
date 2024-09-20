NAME = libft.a
CC = cc
AR = ar rcs
CFLAGS = -Wall -Wextra -Werror -I ../includes

SRCS = ft_nbrlen.c ft_strlen.c ft_strlcpy.c ft_strlcat.c ft_abs.c ft_isalpha.c \
	   ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_islower.c \
	   ft_isupper.c ft_isnbr.c ft_tolower.c ft_toupper.c ft_atoi.c ft_atoll.c \
	   ft_strcmp.c ft_strncmp.c ft_memcmp.c ft_itoa.c ft_free_tab.c \
	   ft_strndup.c ft_strnstr.c ft_strdup.c ft_tablen.c \
	   ft_strnew.c ft_strcat.c ft_substr.c ft_count_occ.c ft_countt_occ.c \
	   ft_strjoin.c ft_strmapi.c ft_strchr.c ft_strrchr.c \
	   *ft_split.c ft_strtrim.c ft_strrev.c ft_putendl_fd.c \
	   ft_putchar_fd.c ft_bzero.c ft_putnbr_fd.c ft_putstr_fd.c \
	   ft_striteri.c ft_calloc.c ft_memchr.c get_next_line.c get_line_count.c \
	   ft_memcpy.c ft_memmove.c ft_memset.c ft_lstsize.c ft_hexlen.c \
	   ft_lstnew.c ft_lstadd_front.c ft_lstadd_back.c ft_puthex_fd.c\
	   ft_lstlast.c ft_lstdelone.c ft_lstclear.c \
	   ft_lstiter.c ft_lstmap.c ft_printf/main.c ft_printf/utils.c \
	   ft_printf/handlers.c ft_print_tab.c ft_print_2dtab.c ft_strjoin_sep.c \
	   ft_isspace.c ft_tabdup.c ft_getenv.c ft_ischr.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

clean:
	rm -f $(OBJS) $(OBJSB)

fclean:		clean
	rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean re
