/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   feedback.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 04:49:36 by ldulling          #+#    #+#             */
/*   Updated: 2024/06/10 05:09:56 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FEEDBACK_H
# define FEEDBACK_H

# include "philo.h"

void	print_wrong_arg_num(int argc);
void	print_invalid_arg(char *target, char *msg);
void	print_nothing_to_do(t_rules *rules);

#endif
