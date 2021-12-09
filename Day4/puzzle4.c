#include <stdlib.h>
#include <stdio.h>
#include "CodamGNL/get_next_line.h"
#include "puzzle4.h"
#include <strings.h>
#include <fcntl.h>

int count_char(char c, char *str)
{
	int i = 0;
	int count = 0;
	

	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

void print_bingo(bingo *card)
{
	int i = 0; 

	while (i < 25)
	{
		printf("%i ", card->bingo_nummer[i]);
		if ((i + 1) % 5 == 0)
			printf("\n");
		i++;
	}

}
 
void make_card(bingo **head, int *numbers)
{
	bingo	*copy;

	copy = *head;
	while(copy != NULL)
	{
		copy = copy->next;
		printf("in loop\n");
	}
	copy = malloc(sizeof(bingo));
	copy->next = NULL;
	copy->bingo_nummer = numbers;
	bzero(copy->hit, sizeof(int) * 25);
	print_bingo(copy);
}

int check_bingo(bingo *card, int new)
{
	int new_copy = new;
	int i;

	printf("start check bingo\n");
	while(new_copy % 5)
		new_copy--;
	i = new_copy;
	while (card->hit[i] == 1)
	{
		i++;
		if (new_copy + 5 == i)
		{
			printf("FOUND BINGO\n");
			return (1);
		}
	}
	i = new % 5;
	while(card->hit[i] == 1)
	{
		if (i >= 20)
		{
			printf("FOUND BINGO\n");
			return (1);
		}
		i += 5;
	}
	return(0);
}	

void play_bingo(int *nums, int calls, bingo *head)
{
	bingo *copy;
	int i = 0;
	int k = 0;

	printf("LET THE BINGO BEGIN! - calls = %i\n", calls);
	while (i < calls)
	{
		//printf("in first loop\n");
		copy = head;
		while(copy != NULL)
		{
			printf("second loop\n");
			while (k < 25)
			{
				//printf("card num%i - num drawn - %i\n", copy->bingo_nummer[k], nums[i]);
				if (copy->bingo_nummer[k] == nums[i])
				{
					printf("found match\n");
					copy->hit[k] = 1;
					if (check_bingo(copy, k))
						exit(0); 
				}
				k++;
			}
			k = 0;
			copy = copy->next;
		}
		i++;
	}
}

void make_bingo(int fd, int *nums, int calls)
{
	bingo	*bingo_cards = NULL;
	int 	*bing_nums;
	int 	count = 0;
	int		i = 0;
	int ret = 1;
	char *str;

	while (ret == 1)
	{
		ret = get_next_line(fd, &str);
		bing_nums = malloc(sizeof(int) * 25);
		while (count < 25 && ret == 1)
		{
			ret = get_next_line(fd, &str);
			while (str[i])
			{
				if (str[i] == ' ')
					i++;
				bing_nums[count] = atoi(&str[i]);
				while(str[i] && str[i] != ' ')
					i++;
				while (str[i] == ' ')	
					i++;
				count++;
			}
			i = 0;
		}
		make_card(&bingo_cards, bing_nums);
		print_bingo(bingo_cards);
		count = 0;
	}
	play_bingo(nums, calls, bingo_cards);
}

int main(int ac, char **av)
{
	int *nums;
	int	calls;
	char *str;
	int fd;
	int i = 0;
	int k;

	fd = open(av[1], O_RDONLY);
	get_next_line(fd, &str);
	calls = count_char(',', str) + 1;
	nums = calloc(calls, sizeof(int));
	while (av[1][i])
	{
		nums[k] = atoi(&str[i]);
		k++;
		while (str[i] != ',' && str[i])
			i++;
		if (str[i] == ',')
			i++;
	}
	make_bingo(fd, nums, calls);
}