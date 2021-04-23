#ifndef NM_H
# define NM_H

# include <mach-o/nlist.h>
# include "shared.h"

typedef struct					s_nlist
{
	unsigned int	n_strx;
	unsigned char	n_type;
	unsigned char	n_sect;
	unsigned short	n_desc;
	unsigned long	n_value;
}								t_nlist;

typedef struct					s_sym
{
	char			*name;
	unsigned char	type;
	unsigned long	addr;
	unsigned char	n_sect;
}								t_sym;

typedef struct symtab_command	t_symtab_command;

char			**create_sect_table(unsigned char *file_content);

int				get_symtab_command(
	unsigned char *file_content, t_symtab_command *syc);

t_sym			**get_sym_list(
	unsigned char *file_content, t_symtab_command *syc);

void			free_sym_list(t_sym **list, unsigned int nsyms);
char			get_type_specifier(t_sym *sym, char **sect_table);
int				print(const char *filename, int print_filename);

#endif
