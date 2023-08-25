/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 13:20:33 by vhovhann          #+#    #+#             */
/*   Updated: 2023/08/25 19:48:57 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>
# include <limits.h>
# include <stdio.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

void	ft_bzero(void *s, size_t n);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

void	*ft_memset(void *b, int c, size_t len);
void	*ft_memcpy(void *dst, void *src, size_t n);
void	*ft_memmove(void *dst, void *src, size_t len);
void	*ft_memchr(void *s, int c, size_t n);
void	*ft_calloc(size_t count, size_t size);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));

int		ft_memcmp(void *s1, void *s2, size_t n);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);
int		ft_strncmp(char *s1, char *s2, unsigned int n);
int		ft_strcmp(char *s1, char *s2);
int		ft_atoi(char *str);

size_t	ft_strlen(char *s);
size_t	ft_strlcpy(char *dst, char *src, size_t dstsize);
size_t	ft_strlcat(char *dst, char *src, size_t dstsize);

char	*ft_strchr(char *s, int c);
char	*ft_strrchr(char *s, int c);
char	*ft_strnstr(char *haystack, char *needle, size_t len);
char	*ft_strdup(char *s1);
char	*ft_substr(char *s, unsigned int start, size_t len);
char	*ft_strjoin(char *s1, char *s2, int flag);
char	*ft_strtrim(char *s1, char *set);
char	*ft_itoa(int n);
char	*ft_itul(long long n);
char	*ft_strmapi(char *s, char (*f)(unsigned int, char));

char	**ft_split(char *s, char c);
char	**ft_split_2(char *s, char c);

t_list	*ft_lstnew(void *content);
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
void	ft_list_push_back(t_list **begin_list, void *data);

int		ft_lstsize(t_list *lst);

#endif