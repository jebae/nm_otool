#include "otool.h"

static int	print_macho(
	const char *filename, unsigned char *content)
{
	ft_printf("%s:\n", filename);
	return (print_text_section(content));
}

static int	print_archive(
	const char *filename, unsigned char *content, long long size)
{
	t_ar_header		ar;
	long long		i;
	unsigned char	*ptr;

	ft_printf("Archive : %s\n", filename);
	i = SARMAG + ft_strlen(AR_EFMT1);
	ft_memcpy(&ar, content + i, sizeof(t_ar_header));
	i += sizeof(t_ar_header) + ft_atoull(ar.ar_size);
	while (i < size)
	{
		i += ft_strlen(AR_EFMT1);
		ft_memcpy(&ar, content + i, sizeof(t_ar_header));
		i += sizeof(t_ar_header);
		ptr = content + i;
		ft_printf("%s(%s):\n", filename, ptr);
		ptr += ft_strlen((char *)ptr) + 1;
		ptr += 8 - (ptr - content) % 8;
		while (*(unsigned int *)ptr != 0xfeedfacf)
			ptr += 4;
		if (print_text_section(ptr) == -1)
			return (-1);
		i += ft_atoull(ar.ar_size);
	}
	return (0);
}

int			print(const char *filename)
{
	int				type;
	int				res;
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
		res = print_macho(filename, content);
	else if (type == SH_FILE_TYPE_ARCHIVE)
		res = print_archive(filename, content, st.st_size);
	else
	{
		ft_printf("ft_otool: %s: is not an object file\n", filename);
		res = -1;
	}
	munmap(content, st.st_size);
	return res;
}

