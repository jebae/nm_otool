#include <gtest/gtest.h>
#include "otool.h"

using namespace std;

class PrintTextSection: public ::testing::Test
{
protected:
	void	print_real_otool(const char *filename)
	{
		int			pid;
		int			status;
		const char	*args[] = {"otool", "-t", NULL, NULL};

		args[2] = filename;
		if ((pid = fork()) == 0)
		{
			if (execv("/usr/bin/otool", (char *const *)args) == -1)
				cerr << "execv failed" << endl;
		}
		else if (pid > 0)
		{
			waitpid(pid, &status, 0);
		}
		else
			cerr << "fork failed" << endl;
	}

	void	print_ft_otool(const char *filename)
	{
		struct stat		st;
		unsigned char	*content = read_file(filename, &st);

		lstat(filename, &st);
		print_text_section(content);
		munmap(content, st.st_size);
	}
};

TEST_F(PrintTextSection, DISABLED_macho)
{
	const char *filename = (const char *)"/bin/cp";

	print_ft_otool(filename);
	print_real_otool(filename);
}
