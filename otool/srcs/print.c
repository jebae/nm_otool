#include "otool.h"

static int	handle_err(unsigned char *content, long long size)
{
	munmap(content, size);
	return (-1);
}

static int	print_macho(
	const char *filename, unsigned char *content, long long size)
{
	ft_printf("%s:\n", filename);
	if (print_text_section(content) == -1)
		return (handle_err(content, size));
	return (0);
}

int			print(const char *filename)
{
	int				type;
	unsigned char	*content;
	struct stat		st;

	content = read_file(filename, &st);
	if (content == NULL)
	{
		ft_printf("ft_otool: %s: no such file or directory\n", filename);
		return (-1);
	}
	type = get_file_type(content);
	if (type == SH_FILE_TYPE_MACHO)
		return (print_macho(filename, content, st.st_size));
	else
	{
		ft_printf("ft_otool: %s: is not an object file\n", filename);
		return (handle_err(content, st.st_size));
	}
}

