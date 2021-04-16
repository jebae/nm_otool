#ifndef OTOOL_H
# define OTOOL_H

#ifdef __cplusplus
extern "C"
{
#endif
# include "shared.h"
#ifdef __cplusplus
}
#endif

int		print_text_section(unsigned char *file_content);
int		print(const char *filename);

#endif
