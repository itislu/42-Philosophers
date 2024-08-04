/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iseven.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 11:22:01 by ldulling          #+#    #+#             */
/*   Updated: 2024/08/04 11:26:15 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils_priv.h"

/**
 * The ft_iseven function checks if an integer is even.
 *
 * @param value    The integer to check.
 *
 * @return         Returns true if the integer is even, false if it is odd.
 */
bool	ft_iseven(int value)
{
	return (!(value & 1));
}
