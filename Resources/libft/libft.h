/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasstou <mmasstou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 15:38:29 by mmasstou          #+#    #+#             */
/*   Updated: 2022/09/02 09:28:46 by mmasstou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

// includes Libc:
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# define BUFFER_SIZE  1

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;
// get_next_line
char	*get_next_line(int fd);
char	*read_file(char *buffer_static, int fd);
char	*get_line(char *buffer_static);
char	*update_buffer(char *buffer_static);
int		cheak_buffer(char *str);
// ft_printf
int		ft_printf(const char *format, ...);
/***************Libc functions***********/
int		ft_arraylen(char **array);
// ft_is

int		ft_isalnum(int a);
int		ft_isalpha(int v);
int		ft_isascii(int i);
int		ft_isdigit(int d);
int		ft_isprint(int p);
int		ft_is_in(char c, char *str);
char	*ft_strrejoin(char *str1, char *str2);
void	ft_swap(int *x, int *y);
// ft_str
size_t	ft_strlcat(char *dest, const char *src, size_t size);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strcmp(const char *s1, const char *s2);
size_t	ft_strlen(const char *str);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
char	*ft_strnstr(const char *src, const char *to_find, size_t size);
char	*ft_strstr(char *str, char *to_find);
char	*ft_strchr(const char *str, int nbr);
char	*ft_strrchr(const char *str, int nbr);
char	*ft_strdup(const char *s);
// ft_mem
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
void	*ft_memset(void *s, int c, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t len);
void	*ft_calloc(size_t count, size_t size);
void	ft_bzero(void *s, size_t n);
// ft_to
int		ft_tolower(char l);
int		ft_toupper(char u);
// ft_cvt
int		ft_atoi(const char *str);
/***************Additional functions***********/
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strtrim(char const *s1, char const *set);
// ft_put
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	*ft_itoa(int n);
char	**ft_split(char const *s, char delimiter);

/************** Bonus part ***********/
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstadd_back(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
#endif
