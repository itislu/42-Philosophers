/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_max.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 11:02:14 by ldulling          #+#    #+#             */
/*   Updated: 2024/08/04 11:17:12 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * The ft_max function returns the maximum of two integers.
 *
 * @param a    The first integer to compare.
 * @param b    The second integer to compare.
 *
 * @return     Returns the larger of the two integers.
 */
long long	ft_max(long long a, long long b)
{
	if (a > b)
		return (a);
	else
		return (b);
}
