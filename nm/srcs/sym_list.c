#include "nm.h"
#include <stdio.h>

int				get_symtab_command(
	unsigned char *file_content, t_symtab_command *syc)
{
	t_mach_header		mach_header;
	long long			offset;
	unsigned int		i;

	ft_memcpy(&mach_header, file_content, sizeof(t_mach_header));
	offset = sizeof(t_mach_header);
	i = 0;
	while (i < mach_header.ncmds)
	{
		ft_memcpy(syc, file_content + offset, sizeof(t_symtab_command));
		if (syc->cmd == LC_SYMTAB)
			return (1);
		offset += syc->cmdsize;
		i++;
	}
	return (0);
}

void			free_sym_list(t_sym **list, unsigned int nsyms)
{
	unsigned int	i;

	i = 0;
	while (i < nsyms)
	{
		if (list[i])
			ft_memdel((void **)&list[i]);
		else
			break ;
		i++;
	}
	ft_memdel((void **)&list);
}

static int		cmp(t_sym *a, t_sym *b)
{
	return ft_strcmp(a->name, b->name);
}

static t_sym	**handle_err(t_sym **list, unsigned int nsyms)
{
	free_sym_list(list, nsyms);
	return (NULL);
}

t_sym			**get_sym_list(
	unsigned char *file_content, t_symtab_command *syc)
{
	t_sym			**list;
	t_nlist			*sym_data;
	char			*strtab;
	unsigned int	i;

	list = (t_sym **)ft_memalloc(sizeof(t_sym *) * syc->nsyms);
	if (list == NULL)
		return (NULL);
	sym_data = (t_nlist *)(file_content + syc->symoff);
	strtab = (char *)(file_content + syc->stroff);
	i = 0;
	while (i < syc->nsyms)
	{
		list[i] = (t_sym *)ft_memalloc(sizeof(t_sym));
		if (list[i] == NULL)
			return (handle_err(list, syc->nsyms));
		list[i]->name = strtab + sym_data->n_strx;
		list[i]->type = sym_data->n_type;
		list[i]->addr = sym_data->n_value;
		list[i]->n_sect = sym_data->n_sect;
		sym_data++;
		i++;
	}
	quick_sort((void **)list, 0, syc->nsyms - 1, (t_sort_cmp)cmp);
	return (list);
}
