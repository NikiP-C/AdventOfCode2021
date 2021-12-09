# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <strings.h>

void	print_counter(unsigned long long *counters)
{
	int i = 0;
	unsigned long long total = 0;

	while (i < 9)
	{
		printf("counter %i = %llu\n", i, counters[i]);
		total += counters[i];
		i++;
	}
	printf("total = %llu\n", total);
}

int main(int ac, char **av)
{
	int i = 0;
	int days = 256;
	int start_value;
	unsigned long long	counter[9];
	unsigned long long save;

	bzero(counter, sizeof(unsigned long long) * 9);
	if (ac < 2)
		return (0);

	while (av[1][i])
	{
		start_value = atoi(&av[1][i]);
		counter[start_value]++;
		i++;
		if (av[1][i] == ',')
			i++;
	}
	while (days)
	{
		save = counter[0];
		counter[0] = counter[1];
		counter[1] = counter[2];
		counter[2] = counter[3];
		counter[3] = counter[4];
		counter[4] = counter[5];
		counter[5] = counter[6];
		counter[6] = counter[7] + save;
		counter[7] = counter[8];
		counter[8] = save;
		days--;
	}
	print_counter(counter);
}
