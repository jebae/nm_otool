#include "shared.h"

unsigned char	*read_file(const char *filename, struct stat *st)
{
	int				fd;
	unsigned char	*content;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (NULL);
	if (fstat(fd, st) != 0)
	{
		close(fd);
		return (NULL);
	}
	content = (unsigned char *)mmap(
		NULL, st->st_size, PROT_READ, MAP_SHARED, fd, 0);
	if (content == MAP_FAILED)
		return (NULL);
	close(fd);
	return (content);
}

int				get_file_type(unsigned char *file_content)
{
	unsigned int	magic;

	magic = *(unsigned int *)file_content;
	if (magic == 0xfeedfacf)
		return (SH_FILE_TYPE_MACHO);
	else if (ft_memcmp(file_content, "!<arch>\n", 8) == 0)
		return (SH_FILE_TYPE_ARCHIVE);
	return (SH_FILE_TYPE_NON_OBJ);
}
