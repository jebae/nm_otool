#include <gtest/gtest.h>
#include "nm.h"

TEST(get_sym_list, DISABLED_cp)
{
	int					fd = open("/bin/cp", O_RDONLY);
	struct stat			st;
	unsigned char		*content;
	t_symtab_command	syc;
	t_sym				**list;

	fstat(fd, &st);
	content = (unsigned char *)malloc(st.st_size);
	read(fd, content, st.st_size);

	if (!get_symtab_command(content, &syc))
		return ;

	list = get_sym_list(content, &syc);

	for (unsigned int i=0; i < syc.nsyms; i++)
	{
		printf("name %s\n", list[i]->name);
		printf("type 0x%x\n", list[i]->type);
		printf("addr 0x%020lx\n", list[i]->addr);
		printf("n_sect %d\n", list[i]->n_sect);
	}

	free_sym_list(list, syc.nsyms);
	free(content);
	close(fd);
}
