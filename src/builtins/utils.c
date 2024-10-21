/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmalyana <gmalyana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 23:13:31 by gmalyana          #+#    #+#             */
/*   Updated: 2024/10/20 19:03:04 by gmalyana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	is_key_valid(char *key)
{
	if (ft_isalpha(*key) == false && *key != '_')
		return (false);
	while (*key)
	{
		if (ft_isalnum(*key) == false && *key != '_')
			return (false);
		key++;
	}
	return (true);
}
