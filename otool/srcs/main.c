#include "otool.h"

int			main(int argc, char **argv)
{
	int		i;

	if (argc <= 1)
	{
		ft_printf("ft_otool: at least one file must be specified\n");
		return (1);
	}
	i = 1;
	while (i < argc)
	{
		if (print(argv[i]) == -1)
			return (1);
		i++;
	}
	return (0);
}
