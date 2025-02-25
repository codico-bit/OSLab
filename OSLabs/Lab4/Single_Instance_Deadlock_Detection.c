// program to detect deadlock in a single instance resource allocation graph using wait for graph
#include <stdio.h>
#include <stdbool.h>
int n,m,rag[20][20],wfg[20][20];
bool is_cycle_util(int process,bool visited[],bool stack[])
{
	visited[process]=true;
	stack[process]=true;
	for(int i=0;i<n;i++)
	{
		if(wfg[process][i])
		{
			if(!visited[i] && is_cycle_util(i,visited,stack))
			return true;
			else if(stack[i])
			return true;
		}
	}
	stack[process]=false;
	return false;
}
bool is_deadlock_detected()
{
	bool visited[n];
	for(int l=0;l<n;l++)
	visited[l]=false;
	for(int i=0;i<n;i++)
	{
		if(!visited[i])
		{
			bool stack[n];
			for(int a=0;a<n;a++)
			stack[a]=false;
			if(is_cycle_util(i,visited,stack))
			return true;
		}
	}
	return false;
}
int main()
{
	printf("Enter the number of processes : ");
	scanf("%d",&n);
	printf("Enter the number of resources : ");
	scanf("%d",&m);
	for(int i=0;i<n;i++)
	for(int j=0;j<m;j++)
	rag[i][j]=0;
	for(int i=0;i<n;i++)
	for(int j=0;j<n;j++)
	wfg[i][j]=0;
	printf("1. 0 for no edge");
	printf("\n2. 1 for edge from resource to process");
	printf("\n3. 2 for edge from process to resource");
	printf("\nEnter the edges for every pair of vertices : ");
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		scanf("%d",&rag[i][j]);
	}
	for(int i=0;i<n;i++)
	for(int j=0;j<m;j++)
	for(int k=0;k<n;k++)
	{
		if(rag[i][j]==2 && rag[j][k]==1)
		wfg[i][k]=1;
	}
	if(is_deadlock_detected())
	printf("Deadlock detected!\n");
	else
	printf("No deadlock detected!\n");
	return 0;
}
