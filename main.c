#include "minishell.h"

int main()
{
	char *val = getcwd(NULL, 0);
	chdir("1/2/3");
	char *val2 = getcwd(NULL, 0);
	chdir("..");
	char *val3 = getcwd(NULL, 0);
}