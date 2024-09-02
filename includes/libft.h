/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labdello <labdello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 13:28:39 by labdello          #+#    #+#             */
/*   Updated: 2024/09/17 18:04:01 by labdello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <stdarg.h>
# include <fcntl.h>
# include <limits.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

size_t		ft_nbrlen(int nbr);
size_t		ft_hexlen(unsigned int hex);
size_t		ft_tablen(char **tab);
size_t		ft_strlen(const char *str);
size_t		get_line_count(int fd);
size_t		ft_strlcpy(char *dest, char *src, size_t n);
size_t		ft_strlcat(char *dest, char *src, size_t n);
long long	ft_atoll(char *str);
int			ft_abs(int nb);
int			ft_isnbr(char *str);
int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_isalnum(int c);
int			ft_isascii(int c);
int			ft_isprint(int c);
int			ft_isspace(int c);
int			ft_islower(int c);
int			ft_isupper(int c);
int			ft_ischr(char *str, char c);
int			ft_tolower(int c);
int			ft_toupper(int c);
int			ft_atoi(const char *str);
int			ft_strcmp(char *s1, char *s2);
int			ft_printf(const char *format, ...);
int			ft_strncmp(char *s1, char *s2, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
int			ft_count_occ(char *str, char c);
int			ft_countt_occ(char **tab, char c);
char		*ft_itoa(int n);
char		*get_next_line(int fd);
char		*ft_strndup(char const *s, size_t n);
char		*ft_strnstr(char *str, char *needle, size_t n);
char		*ft_strdup(char *str);
char		*ft_strnew(size_t size);
char		*ft_strcat(char *dest, char *src);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char		*ft_strchr(const char *str, int c);
char		*ft_strrchr(const char *str, int c);
char		**ft_split(char const *s, char c);
char		*ft_strtrim(char const *s, char const *set);
char		*ft_strjoin_sep(char *s1, char *s2, char *sep);
char		*ft_getenv(char *var_name, char **env);
void		ft_strrev(char *s);
void		ft_putendl_fd(char const *s, int fd);
void		ft_putchar_fd(char c, int fd);
void		ft_bzero(void *s, size_t n);
void		ft_putnbr_fd(int n, int fd);
void		ft_putstr_fd(char const *s, int fd);
void		ft_striteri(char *s, void (*f)(unsigned int, char *));
void		*ft_calloc(size_t nmemb, size_t size);
void		*ft_memchr(const void *s, int c, size_t n);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		*ft_memmove(void *dest, const void *src, size_t n);
void		*ft_memset(void *s, int value, size_t n);
void		ft_puthex_fd(unsigned int hex, int capitilize, int fd);
char		**ft_tabdup(char **src_tab);
void		ft_free_tab(char **tab);
void		ft_print_tab(char **tab);
void		ft_print_2dtab(char ***tab);
int			ft_lstsize(t_list *lst);
t_list		*ft_lstlast(t_list *lst);
t_list		*ft_lstnew(void *content);
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
void		ft_lstadd_front(t_list **lst, t_list *new);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstdelone(t_list *lst, void (*del)(void*));
void		ft_lstclear(t_list **lst, void (*del)(void*));
void		ft_lstiter(t_list *lst, void (*f)(void *));

#endif
