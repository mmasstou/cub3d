#include <stdio.h>

int main()
{
	int index = 0;
	int jndex = 0;

	while (index <= 120)
	{
		jndex = 0;
		while (jndex <= 150)
		{
			if (index == 0 || jndex == 0 || index == 120 || jndex == 150)
				printf("1");
			else
				printf("0");
			jndex++;
		}
		printf("\n");
		index++;
	}
	
}