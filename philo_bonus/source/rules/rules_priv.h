/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules_priv.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 04:49:36 by ldulling          #+#    #+#             */
/*   Updated: 2024/08/09 15:26:36 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RULES_PRIV_H
# define RULES_PRIV_H

# include "typedefs.h"
# include "utils_pub.h"
# include <stdbool.h>
# include <stdio.h>
# include <unistd.h>

void	print_wrong_arg_num(int argc);
void	print_invalid_arg(char *target, char *msg);

#endif
