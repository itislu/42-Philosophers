/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_pub.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 09:25:52 by ldulling          #+#    #+#             */
/*   Updated: 2024/07/31 18:32:28 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_PUB_H
# define INPUT_PUB_H

# include "typedefs.h"
# include <stdbool.h>

bool	parse_rules(t_rules *rules, int argc, char *argv[]);
void	print_nothing_to_do(t_rules *rules);

#endif
