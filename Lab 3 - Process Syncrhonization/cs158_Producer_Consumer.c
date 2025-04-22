// program to simulate producer-consumer problem
#include <stdio.h>
#include <stdlib.h>
int mutex=1,full=0,empty,x=0;
void producer()
{
	mutex--;
	full++;
	empty--;
	x++;
	printf("Producer produces item %d",x);
	mutex++;
}
void consumer()
{
	mutex--;
	full--;
	empty++;
	printf("Consumer consumes item %d",x);
	mutex++;
}
int main()
{
	int n,i;
	printf("Enter the buffer size : ");
	scanf("%d",&empty);
	printf("1. Producer");
	printf("\n2. Consumer");
	printf("\n3. Exit");
	#pragma omp critical
	for(i=1;i>0;i++)
	{
		printf("\nEnter your choice : ");
		scanf("%d",&n);
		switch(n)
		{
			case 1:
			{
				if(mutex==1 && empty!=0)
				producer();
				else
				printf("Buffer is full");
				break;
			}
			case 2:
			{
				if(mutex==1 && full!=0)
				consumer();
				else
				printf("Buffer is empty");
				break;
			}
			case 3:
			{
				exit(0);
				break;
			}
		}
	}
}
