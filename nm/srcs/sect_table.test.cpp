#include <gtest/gtest.h>
#include "nm.h"

TEST(create_sect_table, DISABLED_cp)
{
	int				fd = open("/bin/cp", O_RDONLY);
	struct stat		st;
	unsigned char	*file_content;
	char			**table;

	fstat(fd, &st);
	file_content = (unsigned char *)malloc(st.st_size);

	read(fd, file_content, st.st_size);

	table = create_sect_table(file_content);
	ASSERT_NE((long)table, NULL);

	char **name = table;

	while (*name != NULL)
	{
		printf("%s\n", *name);
		name++;
	}

	free(table);
	free(file_content);
	close(fd);
}
