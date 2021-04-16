#ifndef SHARED_H
# define SHARED_H

# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/mman.h>
# include <mach-o/loader.h>
#ifdef __cplusplus
extern "C"
{
#endif
# include "libft.h"
# include "ft_printf.h"
#ifdef __cplusplus
}
#endif

# define SH_FILE_TYPE_NON_OBJ	0
# define SH_FILE_TYPE_MACHO		1
# define SH_FILE_TYPE_ARCHIVE	2

typedef struct mach_header_64		t_mach_header;
typedef struct load_command			t_load_command;
typedef struct segment_command_64	t_segment_command;
typedef struct section_64			t_section;

unsigned char	*read_file(const char *filename, struct stat *st);
int				get_file_type(unsigned char *file_content);

#endif
