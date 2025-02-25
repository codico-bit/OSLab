// program to execute the Banker's algorithm
#include <stdio.h>
int main()
{
	// P0, P1 and P2 are the process names here
	int n,m,i,j,k;
	n=3; // number of processes
	m=3; // number of resources
	int alloc[3][3]={{1,2,1},  //P0  //Allocation Matrix
			 {2,0,1},  //P1
			 {2,2,1}}; //P2
	int max[3][3]={{2,2,4},  //P0  //Maximum Matrix
		       {2,1,3},  //P1
		       {3,4,1}}; //P2
	int total[3]={5,5,5};  //Total Matrix
	int avail[3];  //Available Matrix
	for(i=0;i<m;i++)
	avail[i]=total[i];
	for(i=0;i<n;i++)
	for(j=0;j<m;j++)
	avail[j]=avail[j]-alloc[i][j];
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
