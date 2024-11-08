/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmalyana <gmalyana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 18:42:38 by gmalyana          #+#    #+#             */
/*   Updated: 2024/11/07 17:39:16 by gmalyana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	invalid_identifier(char *func, char *identifier)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(func, 2);
	ft_putstr_fd(": `", 2);
	ft_putstr_fd(identifier, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

bool	is_key_valid(char *key)
{
	if (ft_isalpha(*key) == false && *key != '_')//?
		return (false);
	while (*key)
	{
		if (ft_isalnum(*key) == false && *key != '_')
			return (false);
		key++;
	}
	return (true);
}
