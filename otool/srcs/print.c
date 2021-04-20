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
			return (handle_err(content, size));
		i += ft_atoull(ar.ar_size);
	}
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
	else if (type == SH_FILE_TYPE_ARCHIVE)
		return (print_archive(filename, content, st.st_size));
	else
	{
		ft_printf("ft_otool: %s: is not an object file\n", filename);
		return (handle_err(content, st.st_size));
	}
}

