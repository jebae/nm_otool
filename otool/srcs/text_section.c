#include "otool.h"
# include <stdio.h>

static int	extract_text_section(
	unsigned char *file_content, long long offset,
	unsigned int nsects, t_section *section)
{
	unsigned int	i;

	i = 0;
	while (i < nsects)
	{
		ft_memcpy(section, file_content + offset, sizeof(t_section));
		if (ft_strcmp(section->segname, "__TEXT") == 0
			&& ft_strcmp(section->sectname, "__text") == 0)
			return (1);
		offset += sizeof(t_section);
		i++;
	}
	return (0);
}

static int	get_text_section(unsigned char *file_content, t_section *section)
{
	t_mach_header		mach_header;
	t_load_command		lc;
	t_segment_command	sc;
	long long			offset;
	unsigned int		i;

	ft_memcpy(&mach_header, file_content, sizeof(t_mach_header));
	offset = sizeof(t_mach_header);
	i = 0;
	while (i < mach_header.ncmds)
	{
		ft_memcpy(&lc, file_content + offset, sizeof(t_load_command));
		if (lc.cmd == LC_SEGMENT_64)
		{
			ft_memcpy(&sc, file_content + offset, sizeof(t_segment_command));
			if (extract_text_section(
				file_content, offset + sizeof(t_segment_command),
				sc.nsects, section))
				return (1);
		}
		offset += lc.cmdsize;
		i++;
	}
	return (0);
}

static void	print_by_16byte(
	t_section *section, unsigned char *buf, unsigned long long	block_64byte)
{
	unsigned long long	i;
	int					j;

	block_64byte = section->size / 16;
	i = 0;
	while (i < block_64byte)
	{
		ft_printf("%016llx        ", section->addr + i * 16);
		j = 0;
		while (j < 16)
		{
			ft_printf("%02x ", buf[16 * i + j]);
			j++;
		}
		ft_printf("\n");
		i++;
	}
}

static void	print_rest(t_section *section, unsigned char *buf, unsigned long long block_64byte)
{
	unsigned int		rest;
	unsigned int		i;
	unsigned long long	last_block_offset;

	rest = section->size % 16;
	if (rest == 0)
		return ;
	last_block_offset = block_64byte * 16;
	ft_printf("%016llx        ", section->addr + last_block_offset);
	i = 0;
	while (i < rest)
	{
		ft_printf("%02x ", buf[last_block_offset + i]);
		i++;
	}
	ft_printf("\n");
}

int			print_text_section(unsigned char *file_content)
{
	t_section			section;
	unsigned long long	block_64byte;
	unsigned char		*buf;

	if (!get_text_section(file_content, &section))
		return (-1);
	buf = (unsigned char *)ft_memalloc(section.size);
	if (buf == NULL)
		return (-1);
	ft_memcpy(buf, file_content + section.offset, section.size);
	ft_printf("Contents of (__TEXT, __text) section\n");
	block_64byte = section.size / 16;
	print_by_16byte(&section, buf, block_64byte);
	print_rest(&section, buf, block_64byte);
	ft_memdel((void **)&buf);
	return (0);
}
