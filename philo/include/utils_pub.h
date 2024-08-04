/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pub.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:13:48 by ldulling          #+#    #+#             */
/*   Updated: 2024/08/04 11:26:40 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_PUB_H
# define UTILS_PUB_H

# include <stdbool.h>
# include <stddef.h>
# include <unistd.h>

int			ft_atoi(const char *nptr);
void		ft_free_and_null(void **ptr);
int			ft_isdigit(int c);
bool		ft_iseven(int value);
bool		ft_isodd(int value);
bool		ft_isoverflow_int(const char *nptr);
int			ft_issign(int c);
int			ft_isspace(int c);
long long	ft_max(long long a, long long b);
void		ft_putstr_fd(char *s, int fd);
long long	ft_round_down_even(long long value);
char		*ft_strchr(const char *s, int c);
size_t		ft_strlen(const char *s);
int			ft_strncmp(const char *s1, const char *s2, size_t n);

#endif
