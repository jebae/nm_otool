#include <gtest/gtest.h>
#include "shared.h"

TEST(get_file_type, macho)
{
	const char		*filename = (const char *)"/bin/cp";
	struct stat		st;
	unsigned char	*buf;
	int				fd = open(filename, O_RDONLY);

	lstat(filename, &st);
	buf = (unsigned char *)malloc(st.st_size);
	read(fd, buf, st.st_size);

	ASSERT_EQ(get_file_type(buf), SH_FILE_TYPE_MACHO);

	free(buf);
	close(fd);
}

TEST(get_file_type, archive)
{
	const char		*filename = (const char *)"/usr/local/lib/libgtest.a";
	struct stat		st;
	unsigned char	*buf;
	int				fd = open(filename, O_RDONLY);

	lstat(filename, &st);
	buf = (unsigned char *)malloc(st.st_size);
	read(fd, buf, st.st_size);

	ASSERT_EQ(get_file_type(buf), SH_FILE_TYPE_ARCHIVE);

	free(buf);
	close(fd);
}

TEST(get_file_type, invalid)
{
	const char		*filename = (const char *)"./Makefile";
	struct stat		st;
	unsigned char	*buf;
	int				fd = open(filename, O_RDONLY);

	lstat(filename, &st);
	buf = (unsigned char *)malloc(st.st_size);
	read(fd, buf, st.st_size);

	ASSERT_EQ(get_file_type(buf), SH_FILE_TYPE_NON_OBJ);

	free(buf);
	close(fd);
}
