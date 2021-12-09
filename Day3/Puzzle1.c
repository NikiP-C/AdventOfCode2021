#include "CodamGNL/get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <strings.h>
#include <math.h>
#include <stdlib.h>


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

int main(void)
{
	int fd;
	int ones[12];
	int total;
	char gamma[13];
	int dec_gamma;
	char epsilon[13];
	int dec_epsilon;
	char *str;
	int i = 0;
	int ret = 1;
	bzero(ones, sizeof(int) * 12);

	fd = open("input.txt", O_RDONLY);
	while (ret == 1)
	{
		ret = get_next_line(fd, &str);
		while (str[i] != 0)
		{
			if (str[i] == '1')
				ones[i] += 1;
			i++;
		}
		total++;
		i = 0;
	}
	while (i < 12)
	{
		if (ones[i] > (total / 2))
		{
			gamma[i] = '1';
			epsilon[i] = '0';
		}
		else
		{
			gamma[i] = '0';
			epsilon[i] = '1';
		} 
		i++;
	}
	gamma[i] = 0;
	epsilon[i] = 0;
	printf("total = %d, gamma = %s, epsilon = %s\n", total, gamma, epsilon);
	printf("total = %d, gamma = %lld, epsilon = %lld\n", total, atoll(gamma), atoll(epsilon));
	dec_gamma = convert(atoll(gamma));
	dec_epsilon = convert(atoll(epsilon));
	printf("dec gamme = %d, dec epsilon = %d, answer = %d\n", dec_gamma, dec_epsilon, dec_epsilon * dec_gamma);
	return (0);
}