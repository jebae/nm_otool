#include "nm.h"

static unsigned int	get_section_count(
	unsigned char *file_content, long long offset, unsigned int ncmds)
{
	t_segment_command	sc;
	unsigned int		i;
	unsigned int		cnt;

	cnt = 0;
	i = 0;
	while (i < ncmds)
	{
		ft_memcpy(&sc, file_content + offset, sizeof(t_segment_command));
		if (sc.cmd == LC_SEGMENT_64)
			cnt += sc.nsects;
		offset += sc.cmdsize;
		i++;
	}
	return (cnt);
}

static void			iterate_commands(
	unsigned char *file_content, long long offset,
	unsigned int ncmds, char **table)
{
	t_segment_command	sc;
	t_section			*section;
	unsigned int		i;
	unsigned int		j;
	unsigned int		idx;

	idx = 0;
	i = 0;
	while (i < ncmds)
	{
		ft_memcpy(&sc, file_content + offset, sizeof(t_segment_command));
		if (sc.cmd == LC_SEGMENT_64 && !(j = 0))
		{
			while (j < sc.nsects)
			{
				section = (t_section *)(file_content + offset +
					sizeof(t_segment_command) + sizeof(t_section) * j);
				table[idx++] = section->sectname;
				j++;
			}
		}
		offset += sc.cmdsize;
		i++;
	}
}

char	**create_sect_table(unsigned char *file_content)
{
	char			**table;
	t_mach_header	mach_header;
	long long		offset;
	unsigned int	sect_cnt;

	ft_memcpy(&mach_header, file_content, sizeof(t_mach_header));
	offset = sizeof(t_mach_header);
	sect_cnt = get_section_count(file_content, offset, mach_header.ncmds);
	table = (char **)ft_memalloc(sizeof(char *) * (sect_cnt + 1));
	if (table == NULL)
		return (NULL);
	iterate_commands(file_content, offset, mach_header.ncmds, table);
	return (table);
}
