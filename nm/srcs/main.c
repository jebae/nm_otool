#include "nm.h"

int		main(int argc, char **argv)
{
	int		i;
	int		print_filename;

	if (argc <= 1)
	{
		if (print("a.out", 0) == -1)
			return (1);
		return (0);
	}
	print_filename = (argc > 2) ? 1 : 0;
	i = 1;
	while (i < argc)
	{
		print(argv[i], print_filename);
		i++;
	}
	return (0);
}
