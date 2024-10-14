#include <libc.h>
#include "../libft/libft.h"
#include <errno.h>
int	ft_cd(char *path)
{
	if (chdir(path) == -1)
	{
		printf("minishell: cd: %s: %s\n", path, strerror(errno));
		return (1);
	}
	return (0);
}

int main(int ac, char **av)
{
	printf("%s\n\n", getcwd(NULL, 0));
	ft_cd(av[1]);
	printf("\n%s\n\n", getcwd(NULL, 0));
	return 0;
}