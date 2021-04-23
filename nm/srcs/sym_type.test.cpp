#include <gtest/gtest.h>
#include "nm.h"

TEST(get_type_specifier, DISABLED_cp)
{
	int					fd = open("/bin/cp", O_RDONLY);
	struct stat			st;
	unsigned char		*content;
	t_symtab_command	syc;
	t_sym				**list;
	char				**sect_table;

	fstat(fd, &st);
	content = (unsigned char *)malloc(st.st_size);
	read(fd, content, st.st_size);

	if (!get_symtab_command(content, &syc))
		return ;

	list = get_sym_list(content, &syc);
	sect_table = create_sect_table(content);

	for (unsigned int i=0; i < syc.nsyms; i++)
	{
		printf("%s %c\n", list[i]->name,
			get_type_specifier(list[i], sect_table));
	}

	free_sym_list(list, syc.nsyms);
	free(sect_table);
	free(content);
	close(fd);
}
