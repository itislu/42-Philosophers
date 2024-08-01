/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pub.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:13:48 by ldulling          #+#    #+#             */
/*   Updated: 2024/08/01 23:07:57 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_PUB_H
# define UTILS_PUB_H

# include <stdbool.h>
# include <stddef.h>
# include <unistd.h>

int		ft_atoi(const char *nptr);
void	ft_free_and_null(void **ptr);
int		ft_isdigit(int c);
bool	ft_isoverflow_int(const char *nptr);
int		ft_issign(int c);
int		ft_isspace(int c);
void	ft_putstr_fd(char *s, int fd);
char	*ft_strchr(const char *s, int c);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

#endif
