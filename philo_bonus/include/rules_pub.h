/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules_pub.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 09:25:52 by ldulling          #+#    #+#             */
/*   Updated: 2024/08/09 15:26:22 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RULES_PUB_H
# define RULES_PUB_H

# include "typedefs.h"
# include <stdbool.h>

bool	parse_rules(t_rules *rules, int argc, char *argv[]);
void	print_nothing_to_do(t_rules *rules);

#endif
