#include "nm.h"

static void	print_sym_list(
	t_sym **sym_list, char **sect_table, unsigned int nsyms)
{
	unsigned int	i;
	char			type;

	i = 0;
	while (i < nsyms)
	{
		type = get_type_specifier(sym_list[i], sect_table);
		if (type == 'U' || type == 'u')
			ft_printf("%16s %c %s\n", "", type, sym_list[i]->name);
		else if (type != '-')
			ft_printf("%016lx %c %s\n",
				sym_list[i]->addr, type, sym_list[i]->name);
		i++;
	}
}

static int	print_macho(
	const char *filename, unsigned char *content, int print_filename)
{
	t_symtab_command	syc;
	t_sym				**sym_list;
	char				**sect_table;

	if (!get_symtab_command(content, &syc))
		return (-1);
	sym_list = get_sym_list(content, &syc);
	sect_table = create_sect_table(content);
	if (sym_list == NULL || sect_table == NULL)
	{
		if (sym_list)
			free_sym_list(sym_list, syc.nsyms);
		if (sect_table)
			ft_memdel((void **)&sect_table);
		return (-1);
	}
	if (print_filename)
		ft_printf("\n%s\n", filename);
	print_sym_list(sym_list, sect_table, syc.nsyms);
	free_sym_list(sym_list, syc.nsyms);
	ft_memdel((void **)&sect_table);
	return (0);
}

static int	print_archive(
	const char *filename, unsigned char *content, long long size)
{
	t_ar_header		ar;
	long long		i;
	unsigned char	*ptr;

	i = SARMAG + ft_strlen(AR_EFMT1);
	ft_memcpy(&ar, content + i, sizeof(t_ar_header));
	i += sizeof(t_ar_header) + ft_atoull(ar.ar_size);
	while (i < size)
	{
		i += ft_strlen(AR_EFMT1);
		ft_memcpy(&ar, content + i, sizeof(t_ar_header));
		i += sizeof(t_ar_header);
		ptr = content + i;
		ft_printf("\n%s(%s):\n", filename, ptr);
		ptr += ft_strlen((char *)ptr) + 1;
		ptr += 8 - (ptr - content) % 8;
		while (*(unsigned int *)ptr != 0xfeedfacf)
			ptr += 4;
		if (print_macho(filename, ptr, 0) == -1)
			return (-1);
		i += ft_atoull(ar.ar_size);
	}
	return (0);
}

int			print(const char *filename, int print_filename)
{
	int				type;
	int				res;
	unsigned char	*content;
	struct stat		st;

	content = read_file(filename, &st);
	if (content == NULL)
	{
		ft_printf("ft_nm: %s: no such file or directory\n", filename);
		return (-1);
	}
	type = get_file_type(content);
	if (type == SH_FILE_TYPE_MACHO)
		res = print_macho(filename, content, print_filename);
	else if (type == SH_FILE_TYPE_ARCHIVE)
		res = print_archive(filename, content, st.st_size);
	else
	{
		ft_printf("ft_nm: %s: is not an object file\n", filename);
		res = -1;
	}
	munmap(content, st.st_size);
	return res;
}
