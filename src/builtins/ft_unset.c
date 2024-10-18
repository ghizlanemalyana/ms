/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmalyana <gmalyana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 20:16:18 by gmalyana          #+#    #+#             */
/*   Updated: 2024/10/18 23:29:40 by gmalyana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int ft_unset(t_shell *shell, char **av)
{
    int status;

    status = SUCCESS;
    while (*av)
    {
        if (is_valid_key(*av))
        {
            unset_env(&shell->env, *av);
        }
        else
        {
            status = FAILURE;
            ft_printf("minishell: unset: `%s': not a valid identifier\n", *av); //! write to stderr
        }
        av++;
    }
    return (status);
}
