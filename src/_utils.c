#include "../minishell.h"

# define GREEN "\033[0;32m"
# define RESET "\033[0m"

void	print_tokens(t_list *tokens)
{
	t_list	*node;
	t_token	*token;

	node = tokens;
	while (node)
	{
		token = node->content;
		if (token->type == ARG)
		{
			printf("\033[1;32mARG\033[0m\n");
			printf("  content: \033[1;94m%s\033[0m\n", token->content);
			if (token->linked || token->quoted || token->expandable)
			{
				printf("  status: ");
				if (token->quoted)
					printf(GREEN"quoted "RESET);
				if (token->expandable)
					printf(GREEN"expandable"RESET);
				printf("\n");
			}
		}
		else if (token->type == PIPE)
			printf("\033[0;93mPIPE\033[0m\n");
		else if (token->type == REDIR_OUT)
			printf("\033[0;95mREDIR OUT\033[0m\n");
		else if (token->type == REDIR_IN)
			printf("\033[0;95mREDIR IN\033[0m\n");
		else if (token->type == APPEND)
			printf("\033[0;96mAPPEND\033[0m\n");
		else if (token->type == HEREDOC)
			printf("\033[0;96mHEREDOC\033[0m\n");
		node = node->next;
		if (node)
			printf("\n");
	}
}