/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:13:48 by ldulling          #+#    #+#             */
/*   Updated: 2024/05/21 19:22:56 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <limits.h>
# include <stdbool.h>
# include <unistd.h>

# define WHITESPACE	" \f\n\r\t\v"

int		ft_atoi(const char *nptr);
long	ft_atol(const char *nptr);
int		ft_isdigit(int c);
bool	ft_isoverflow_int(const char *nptr);
bool	ft_isoverflow_long(const char *nptr);
int		ft_issign(int c);
int		ft_isspace(int c);
void	ft_putstr_fd(char *s, int fd);
char	*ft_strchr(const char *s, int c);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

#endif
