// program to execute the Banker's algorithm user-interactive
#include <stdio.h>
int main()
{
	// P0, P1, P2, ...., Pn are the process names here
	int n,m,i,j,k; // n is the number of processes and m is the number of resources
	printf("Enter the number of processes and resources : ");
	scanf("%d %d",&n,&m);
	int alloc[n][m],max[n][m],total[m],avail[m];
	printf("Enter the allocation matrix : "); //Allocation Matrix
	for(i=0;i<n;i++)
	for(j=0;j<m;j++)
	scanf("%d",&alloc[i][j]);
	printf("Enter the maximum matrix : "); //Maximum Matrix
	for(i=0;i<n;i++)
	for(j=0;j<m;j++)
	scanf("%d",&max[i][j]);
	printf("Enter the total matrix : "); //Total Matrix
	for(i=0;i<m;i++)
	scanf("%d",&total[i]);
	for(i=0;i<m;i++)
	avail[i]=total[i];
	for(i=0;i<n;i++)
	for(j=0;j<m;j++)
	avail[j]=avail[j]-alloc[i][j]; //Available Matrix
	int flags[n],temp[n],index=0;
	for(k=0;k<n;k++)
	flags[k]=0;
	int need[n][m];
	for(i=0;i<n;i++)
	for(j=0;j<m;j++)
	need[i][j]=max[i][j]-alloc[i][j];
	int y=0;
	for(k=0;k<n;k++)
	for(i=0;i<n;i++)
	{
		if(flags[i]==0)
		{
			int flag=0;
			for(j=0;j<m;j++)
			{
				if(need[i][j]>avail[j])
				{
					flag=1;
					break;
				}
			}
			if(flag==0)
			{
				temp[index++]=i;
				for(y=0;y<m;y++)
				avail[y]+=alloc[i][y];
				flags[i]=1;
			}
		}
	}
	int flag=1;
	for(i=0;i<n;i++)
	{
		if(flags[i]==0)
		{
			flag=0;
			printf("The following system is not safe.");
			break;
		}
	}
	if(flag==1)
	{
		printf("Following is the SAFE Sequence :\n");
		printf("P%d",temp[0]);
		for(i=1;i<n;i++)
		printf(" -> P%d",temp[i]);
		printf("\n");
	}
	return 0;
}
