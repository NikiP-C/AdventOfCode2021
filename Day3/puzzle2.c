#include "CodamGNL/get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <strings.h>
#include <math.h>
#include <stdlib.h>

#define SIZE 12
#define AMOUNTH 1000

int convert(long long bin)
{
	int rem;
	int dec = 0;
	int i = 0;

	while(bin != 0)
	{
		rem = bin % 10;
		bin  = bin / 10;
		dec += rem * pow(2, i);
		i++;
	}
	return (dec);
}

// char *get_common_value(char **str)
// {
// 	int i = 0;
// 	int k = 0;
// 	int ones[SIZE];
// 	char	*gamma;

// 	gamma = calloc(SIZE + 1, 1);
// 	bzero(ones, sizeof(int) * SIZE);
// 	while (str[i] != NULL)
// 	{
// 		while (str[i][k] != 0)
// 		{
// 			if (str[i][k] == '1')
// 				ones[k] += 1;
// 			k++;
// 		}
// 		i++;
// 		k = 0;
// 	}
// 	i = 0;
// 	while (i < SIZE)
// 	{
// 		if (ones[i] < AMOUNTH / 2)
// 			gamma[i] = '0';
// 		else
// 			gamma[i] = '1';
// 		i++;
// 	}
// 	return (gamma);
// }

char	most_common(char **str, int *still_considered, int loc, int total)
{
	int i = 0;
	int ones = 0;

	while (i < AMOUNTH)
	{
		while(still_considered[i] == -1 && i < AMOUNTH)
			i++;
		if (i >= AMOUNTH)
			break;
		if (str[i][loc] == '1')
			ones++;
		i++;
	}
	if (total % 2)
		total += 1;
	if (ones >= total / 2)
		return('1');
	return('0');
}

int	scrubber(char **str)
{
	int 	still_considered[AMOUNTH];
	int 	total = AMOUNTH;
	int 	i = 0;
	int 	num = 0;
	char	common;

	while (i < AMOUNTH)
	{
		still_considered[i] = i;
		i++;
	}
	i = 0;
	while (i < SIZE)
	{
		while (still_considered[num] == -1)
				num++;
		common = most_common(str, still_considered, i, total);
		while (num < AMOUNTH)
		{
			if (str[num][i] == common)
			{
				still_considered[num] = -1;
				total--;
				if (total == 1)
				{
						num = 0;
					while (still_considered[num] == -1)
						num++;
					printf("total = %d, scrub = %s\n", total, str[num]);
					return (num);
				}
			}
			num++;
			while (still_considered[num] == -1)
				num++;
		}
		i++;
		num = 0;
	}
	return (num);
}

int	oxygen(char **str)
{
	int 	still_considered[AMOUNTH];
	int 	total = AMOUNTH;
	int 	i = 0;
	int 	num = 0;
	char	common;

	while (i < AMOUNTH)
	{
		still_considered[i] = i;
		i++;
	}
	i = 0;
	while (i < SIZE)
	{
		while (still_considered[num] == -1)
				num++;
		common = most_common(str, still_considered, i, total);
		while (num < AMOUNTH)
		{
			if (str[num][i] != common)
			{
				still_considered[num] = -1;
				total--;
				if (total == 1)
				{
						num = 0;
					while (still_considered[num] == -1)
						num++;
					printf("total = %d, ox = %s\n", total, str[num]);
					return (num);
				}
			}
			num++;
			while (still_considered[num] == -1)
				num++;
		}
		i++;
		num = 0;
	}
	return (num);
}

int main(void)
{
	int 	fd;
	char 	*str[1001];
	int 	i = 0;
	int		ret = 1;
	int		ox;
	int		scrub;

	fd = open("input.txt", O_RDONLY);
	i = 0;
	while (ret == 1)
	{
		ret = get_next_line(fd, &str[i]);
		i++;
	}
	str[i] = NULL;
	ox = oxygen(str);
	scrub = scrubber(str);
	printf("ox = %s, scrub = %s\n", str[ox], str[scrub]);
	ox = convert(atoll(str[ox]));
	scrub = convert(atoll(str[scrub]));
	printf("ox = %d, scrub = %d, answer = %d\n", ox, scrub, ox * scrub);
	return (0);
}