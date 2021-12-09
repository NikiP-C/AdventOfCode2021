#include "CodamGNL/get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
	char *str = NULL;
	int	ret = 1;
	int fd;
	int current;
	int	total1 = 0;
	int total2 = 0;
	int total3 = 0;
	int increase_count = 0;
	int count = 1;

	fd = open("input.txt", O_RDONLY);
	while (ret == 1)
	{
		ret = get_next_line(fd, &str);
		current = atoi(str);
		total2 += current;
		if (count != 1)
			total3 += current;
		if (count >= 3)
		{
			if (count > 3)
				if (total1 < total2)
					increase_count++;
			total1 = total2;
			total2 = total3;
			total3 = current;
		}
		count++;
	}
	printf("amount increase %d\n", increase_count);
}
