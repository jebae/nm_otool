#include <gtest/gtest.h>
#include "shared.h"

TEST(read_file, file_exist)
{
	const char		*filename = (const char *)"./Makefile";
	int				fd = open(filename, O_RDONLY);
	struct stat		st;
	unsigned char	*buf;
	unsigned char	*content;

	lstat(filename, &st);
	buf = (unsigned char *)malloc(st.st_size);
	read(fd, buf, st.st_size);

	content = read_file(filename, &st);

	ASSERT_EQ(memcmp(content, buf, st.st_size), 0);

	ASSERT_NE(munmap(content, st.st_size), -1);
	free(buf);
	close(fd);
}

TEST(read_file, file_not_exist)
{
	const char		*filename = (const char *)"not_exist";
	unsigned char	*content;
	struct stat		st;

	content = read_file(filename, &st);

	ASSERT_EQ((long)content, NULL);
}
