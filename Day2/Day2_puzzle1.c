#include "CodamGNL/get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int get_num(char *str)
{
	int i = 0;

	while ((str[i] < '0' || str[i] > '9') && str[i] != 0)
	{
		i++;
	}
	return (atoi(&str[i]));
}

int main(void)
{
	int		depth = 0;
	int		forward = 0;
	int		ret = 1;
	int		num;
	char	*str;
	int 	fd;

	fd = open("input.txt", O_RDONLY);
	while (ret == 1)
	{
		ret = get_next_line(fd, &str);
		num = get_num(str);
		printf("num = %d\n", num);
		if (str[0] == 'f')
			forward += num;
		if (str[0] == 'd')
			depth += num;
		if (str[0] == 'u')
		{	
			depth -= num;
			if (depth < 0)
				depth = 0;
		}
	}
	printf("forward = %d, depth = %d, answer = %d\n", forward, depth, forward * depth);
}
