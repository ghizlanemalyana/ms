/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmalyana <gmalyana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 20:16:18 by gmalyana          #+#    #+#             */
/*   Updated: 2024/09/22 18:48:45 by gmalyana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// void	ft_unset(t_shell *shell, char **av)
// {
// 	int		i;
// 	t_list	*tmp;
// 	t_list	*prev;

// 	i = 1;
// 	while (av[i])
// 	{
// 		tmp = shell->env;
// 		prev = NULL;
// 		while (tmp)
// 		{
// 			if (!ft_strncmp(((t_env *)tmp->content)->key, av[i], ft_strlen(av[i]))
// 				&& ((t_env *)tmp->content)->key[ft_strlen(av[i])] == '=')
// 			{
// 				if (prev)
// 					prev->next = tmp->next;
// 				else
// 					shell->env = tmp->next;
// 				free(((t_env *)tmp->content)->key);
// 				free(((t_env *)tmp->content)->value);
// 				free(tmp->content);
// 				free(tmp);
// 				break ;
// 			}
// 			prev = tmp;
// 			tmp = tmp->next;
// 		}
// 		i++;
// 	}
// }
// int main(int argc, char **argv)
// {
// 	int i = 0;
// 	int j = 1;
// 	t_shell *shell;
// 	if (argv[i] == NULL)
// 		return 1;
// 	else if (argv[1] == "unset" && argv[2] == NULL)
// 	{
// 		return 1;
// 	}
// 	else ((ft_strchr(argv[1], 'u')) == "unset" && argv[i][j] != '\0')
// 	{
// 		ft_unset(shell, argv);
// 	}
// 	return 0;
// }

void ft_unset(t_shell *shell, char **av)
{
    int i;
    t_list *tmp;
    t_list *prev;
    size_t key_len;

    i = 1;
    while (av[i])
    {
        tmp = shell->env;
        prev = NULL;
        key_len = ft_strlen(av[i]);
        while (tmp)
        {
            t_env *env = (t_env *)tmp->content;
            if (!ft_strncmp(env->key, av[i], key_len) && env->key[key_len] == '=')
            {
                if (prev)
                    prev->next = tmp->next;
                else
                    shell->env = tmp->next;
                free(env->key);
                free(env->value);
                free(env);
                free(tmp);
                break;
            }
            prev = tmp;
            tmp = tmp->next;
        }
        i++;
    }
}
// main function to check the unset.

// int main(int argc, char **argv)
// {
//     t_shell *shell = NULL;

//     if (argc < 2)
//         return 1;
//     else if (strcmp(argv[1], "unset") == 0 && argc == 2)
//         return 1;
//     else if (strcmp(argv[1], "unset") == 0 && argc > 2)
//         ft_unset(shell, argv + 1);
//     else
//     {
//         fprintf(stderr, "Unknown command or incorrect usage.\n");
//         return 1;
//     }
//     return 0;
// }
