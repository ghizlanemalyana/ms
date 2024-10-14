/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmalyana <gmalyana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 17:08:30 by gmalyana          #+#    #+#             */
/*   Updated: 2024/09/02 20:07:49 by gmalyana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../minishell.h"

// void	ft_print_env(t_list *env)
// {
// 	t_env	*tmp;

// 	while (tmp)
// 	{
// 		tmp = (t_env *)env->content;
// 		if (tmp->value != NULL)
// 			printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
// 		else
// 			printf("declare -x %s\n", tmp->key);
// 		env = env->next;
// 	}
// }

// void 	ft_export_add(t_list **env, char *key, char *value)
// {
// 	t_env	*new_env;
// 	t_list	*new;

// 	new_env = malloc(sizeof(t_env));
// 	if (!new_env)
// 		return ;
// 	if (value != NULL)
// 		new_env->key = ft_substr(key, 0, ft_strchr(key, '=') - key);
// 	else
// 		new_env->key = key;
// 	new_env->value = value;
// 	new = ft_lstnew(new_env);
// 	if (!new)
// 	{
// 		free(new_env);
// 		return ;
// 	}
// 	ft_lstadd_back(env, new);
// }


// void	ft_export(t_shell *shell, char **av)
// {
// 	if (av[1] == NULL)
// 		ft_print_env(shell->env);
// 	else
// 	{
// 		while (av)
// 		{        
			
// 			if (ft_strchr(av, '='))
// 				ft_export_add(shell->env, av, ft_strchr(av, '=') + 1);
// 			else
// 				ft_export_add(shell->env, av, NULL);
// 			av++;
// 		}
// 	}
// }

