// c program to simulate MVT memory management technique
#include <stdio.h>
int main()
{
	int ms,mp[10],temp,i,n=0,ch=1;
	printf("Enter the total memory available in Bytes : ");
	scanf("%d",&ms);
	temp=ms;
	for(i=0;ch==1;i++,n++)
	{
		printf("Enter the memory required for process %d in Bytes : ",i+1);
		scanf("%d",&mp[i]);
		if(mp[i]<=temp)
		{
			printf("Memory is allocated for Process %d",i+1);
			temp=temp-mp[i];
		}
		else
		{
			printf("Memory is full");
			break;
		}
		printf("\nDo you want to continue(1/0) :");
		scanf("%d",&ch);
	}
	printf("Total Memory Available : %d",ms);
	printf("\n\nPROCESS \tMEMORY REQUIRED");
	for(i=0;i<n;i++)
	printf("\n\t%d\t\t%d",i+1,mp[i]);
	printf("\n\nTotal Memory Allocated is %d",ms-temp);
	printf("\nTotal External Fragmentation is %d\n",temp);
	return 0;
}
