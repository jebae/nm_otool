#include "nm.h"

static char		get_type_in_section(
	unsigned char n_sect, char **sect_table)
{
	n_sect--;
	if (ft_strcmp(sect_table[n_sect], "__text") == 0)
		return ('T');
	else if (ft_strcmp(sect_table[n_sect], "__data") == 0)
		return ('D');
	else if (ft_strcmp(sect_table[n_sect], "__bss") == 0)
		return ('B');
	return ('S');
}

char			get_type_specifier(t_sym *sym, char **sect_table)
{
	int				is_internal;
	char			ch;
	unsigned char	type;

	type = sym->type;
	is_internal = (type & N_EXT) ? 0 : 1;
	if (type & N_STAB)
		return ('-');
	else if ((type & N_TYPE) == N_UNDF)
	{
		if (is_internal)
			return ('?');
		ch = 'U';
	}
	else if ((type & N_TYPE) == N_SECT)
		ch = get_type_in_section(sym->n_sect, sect_table);
	else if ((type & N_TYPE) == N_ABS)
		ch = 'A';
	else if ((type & N_TYPE) == N_INDR)
		ch = 'I';
	if (is_internal)
		return (ch + ('a' - 'A'));
	return (ch);
}
